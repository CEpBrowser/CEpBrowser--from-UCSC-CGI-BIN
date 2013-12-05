/* hgPcr - In-silico PCR CGI for UCSC. */
#include "common.h"
#include "hash.h"
#include "errabort.h"
#include "errCatch.h"
#include "hCommon.h"
#include "dystring.h"
#include "jksql.h"
#include "linefile.h"
#include "dnautil.h"
#include "fa.h"
#include "psl.h"
#include "gfPcrLib.h"
#include "cheapcgi.h"
#include "htmshell.h"
#include "hdb.h"
#include "hui.h"
#include "cart.h"
#include "dbDb.h"
#include "blatServers.h"
#include "targetDb.h"
#include "pcrResult.h"
#include "trashDir.h"
#include "web.h"
#include "botDelay.h"
#include "oligoTm.h"

static char const rcsid[] = "$Id: hgPcr.c,v 1.29 2009/09/23 18:42:17 angie Exp $";

struct cart *cart;	/* The user's ui state. */
struct hash *oldVars = NULL;

void usage()
/* Explain usage and exit. */
{
errAbort(
  "hgPcr - In-silico PCR CGI for UCSC\n"
  "usage:\n"
  "   hgPcr XXX\n"
  "options:\n"
  "   -xxx=XXX\n"
  );
}

struct pcrServer
/* Information on a server running on genomic assembly sequence. */
   {
   struct pcrServer *next;  /* Next in list. */
   char *db;		/* Database name. */
   char *genome;	/* Genome name. */
   char *description;	/* Assembly description */
   char *host;		/* Name of machine hosting server. */
   char *port;		/* Port that hosts server. */
   char *seqDir;	/* Directory of sequence files. */
   };

struct targetPcrServer
/* Information on a server running on non-genomic sequence, e.g. mRNA,
 * that has been aligned to a particular genomic assembly. */
   {
   struct targetPcrServer *next;  /* Next in list. */
   char *host;		/* Name of machine hosting server. */
   char *port;		/* Port that hosts server. */
   struct targetDb *targetDb;     /* All of the info about the target. */
   };

struct pcrServer *getServerList()
/* Get list of available servers. */
{
struct pcrServer *serverList = NULL, *server;
struct sqlConnection *conn = hConnectCentral();
struct sqlResult *sr;
char **row;

/* Do a little join to get data to fit into the pcrServer. */
sr = sqlGetResult(conn, 
   "select dbDb.name,dbDb.genome,dbDb.description,blatServers.host,"
   "blatServers.port,dbDb.nibPath "
   "from dbDb,blatServers where "
   "dbDb.name = blatServers.db "
   "and blatServers.canPcr = 1 order by dbDb.orderKey" );
while ((row = sqlNextRow(sr)) != NULL)
    {
    AllocVar(server);
    server->db = cloneString(row[0]);
    server->genome = cloneString(row[1]);
    server->description = cloneString(row[2]);
    server->host = cloneString(row[3]);
    server->port = cloneString(row[4]);
    server->seqDir = cloneString(row[5]);
    slAddHead(&serverList, server);
    }
sqlFreeResult(&sr);
hDisconnectCentral(&conn);
if (serverList == NULL)
    errAbort("Sorry, no PCR servers are available");
slReverse(&serverList);
return serverList;
}

struct pcrServer *findServer(char *db, struct pcrServer *serverList)
/* Return server for given database.  Db can either be
 * database name or description. */
{
struct pcrServer *server;
for (server = serverList; server != NULL; server = server->next)
    {
    if (sameString(db, server->db))
        return server;
    }
errAbort("Can't find a server for PCR database %s\n", db);
return NULL;
}

struct targetPcrServer *getTargetServerList(char *db, char *name)
/* Get list of available non-genomic-assembly target pcr servers associated 
 * with db (and name, if not NULL).  There may be none -- that's fine. */
{
struct targetPcrServer *serverList = NULL, *server;
struct sqlConnection *conn = hConnectCentral();
struct sqlConnection *conn2 = hAllocConn(db);
struct sqlResult *sr;
char **row;
char query[2048];

safef(query, sizeof(query),
      "select b.host, b.port, t.* from targetDb as t, blatServers as b "
      "where b.db = t.name and t.db = '%s' and b.canPcr = 1 "
      "%s%s%s"
      "order by t.priority",
      db,
      isNotEmpty(name) ? "and t.name = '" : "",
      isNotEmpty(name) ? name : "",
      isNotEmpty(name) ? "' " : "");
sr = sqlGetResult(conn, query);
while ((row = sqlNextRow(sr)) != NULL)
    {
    /* Keep this server only if its timestamp is newer than the tables
     * and file on which it depends. */
    struct targetDb *target = targetDbMaybeLoad(conn2, row+2);
    if (target != NULL)
	{
	AllocVar(server);
	server->host = cloneString(row[0]);
	server->port = cloneString(row[1]);
	server->targetDb = target;
	slAddHead(&serverList, server);
	}
    }
sqlFreeResult(&sr);
hDisconnectCentral(&conn);
hFreeConn(&conn2);
slReverse(&serverList);
return serverList;
}

void doHelp()
/* Print up help page */
{
puts(
"In-Silico PCR searches a sequence database with a pair of\n"
"PCR primers, using an indexing strategy for fast performance.\n"
"\n"
"<H3>Configuration Options</H3>\n"
"<B>Genome and Assembly</B> - The sequence database to search.<BR>\n"
"<B>Target</B> - If available, choose to query transcribed sequences.<BR>\n" 
"<B>Forward Primer</B> - Must be at least 15 bases in length.<BR>\n"
"<B>Reverse Primer</B> - On the opposite strand from the forward primer. Minimum length of 15 bases.<BR>\n"
"<B>Max Product Size</B> - Maximum size of amplified region.<BR>\n"
"<B>Min Perfect Match</B> - Number of bases that match exactly on 3' end of primers.  Minimum match size is 15.<BR>\n"
"<B>Min Good Match</B> - Number of bases on 3' end of primers where at least 2 out of 3 bases match.<BR>\n"
"<B>Flip Reverse Primer</B> - Invert the sequence order of the reverse primer and complement it.<BR>\n"
"\n"
"<H3>Output</H3>\n"
"When successful, the search returns a sequence output file in fasta format \n"
"containing all sequence in the database that lie between and include the \n"
"primer pair.  The fasta header describes the region in the database\n"
"and the primers.  The fasta body is capitalized in areas where the primer\n"
"sequence matches the database sequence and in lower-case elsewhere.  Here\n"
"is an example from human:<BR>\n"
"<TT><PRE>\n"
">chr22:31000551+31001000  TAACAGATTGATGATGCATGAAATGGG CCCATGAGTGGCTCCTAAAGCAGCTGC\n"
"TtACAGATTGATGATGCATGAAATGGGgggtggccaggggtggggggtga\n"
"gactgcagagaaaggcagggctggttcataacaagctttgtgcgtcccaa\n"
"tatgacagctgaagttttccaggggctgatggtgagccagtgagggtaag\n"
"tacacagaacatcctagagaaaccctcattccttaaagattaaaaataaa\n"
"gacttgctgtctgtaagggattggattatcctatttgagaaattctgtta\n"
"tccagaatggcttaccccacaatgctgaaaagtgtgtaccgtaatctcaa\n"
"agcaagctcctcctcagacagagaaacaccagccgtcacaggaagcaaag\n"
"aaattggcttcacttttaaggtgaatccagaacccagatgtcagagctcc\n"
"aagcactttgctctcagctccacGCAGCTGCTTTAGGAGCCACTCATGaG\n"
"</PRE></TT>\n"
"The + between the coordinates in the fasta header indicates \n"
"this is on the positive strand.  \n"
);
}

#define ORGFORM_KEEP_ORG "document.orgForm.org.value = " \
    " document.mainForm.org.options[document.mainForm.org.selectedIndex].value; "
#define ORGFORM_KEEP_DB " document.orgForm.db.value = " \
    " document.mainForm.db.options[document.mainForm.db.selectedIndex].value; "
#define ORGFORM_KEEP_PARAMS \
    " document.orgForm.wp_f.value = document.mainForm.wp_f.value; " \
    " document.orgForm.wp_r.value = document.mainForm.wp_r.value; " \
    " document.orgForm.wp_size.value = document.mainForm.wp_size.value; " \
    " document.orgForm.wp_perfect.value = document.mainForm.wp_perfect.value; " \
    " document.orgForm.wp_good.value = document.mainForm.wp_good.value; "
#define ORGFORM_RESET_DB " document.orgForm.db.value = 0; "
#define ORGFORM_RESET_TARGET " document.orgForm.wp_target.value = \"\"; "
#define ORGFORM_SUBMIT " document.orgForm.submit();'";


void showGenomes(char *genome, struct pcrServer *serverList)
/* Put up drop-down list with genomes on it. */
{
struct hash *uniqHash = hashNew(8);
struct pcrServer *server;
char *onChangeText = "onchange='" ORGFORM_KEEP_PARAMS ORGFORM_KEEP_ORG
    ORGFORM_RESET_DB
    ORGFORM_RESET_TARGET
    ORGFORM_SUBMIT;

printf("<SELECT NAME=\"org\" %s>\n", onChangeText);
for (server = serverList; server != NULL; server = server->next)
    {
    if (!hashLookup(uniqHash, server->genome))
        {
	hashAdd(uniqHash, server->genome, NULL);
	printf("  <OPTION%s VALUE=\"%s\">%s</OPTION>\n", 
	    (sameWord(genome, server->genome) ? " SELECTED" : ""), 
	    server->genome, server->genome);
	}
    }
printf("</SELECT>\n");
hashFree(&uniqHash);
}

void showAssemblies(char *genome, char *db, struct pcrServer *serverList,
		    boolean submitOnClick)
/* Put up drop-down list with assemblies on it. */
{
struct pcrServer *server;
char *onChangeText = "onchange='" ORGFORM_KEEP_PARAMS ORGFORM_KEEP_ORG
    ORGFORM_KEEP_DB
    ORGFORM_RESET_TARGET
    ORGFORM_SUBMIT;

printf("<SELECT NAME=\"db\"%s>\n", submitOnClick ? onChangeText : "");
for (server = serverList; server != NULL; server = server->next)
    {
    if (sameWord(genome, server->genome))
	printf("  <OPTION%s VALUE=%s>%s</OPTION>\n", 
	    (sameString(db, server->db) ? " SELECTED" : ""), 
	    server->db, server->description);
    }
printf("</SELECT>\n");
}

void showTargets(char *target, struct targetPcrServer *serverList)
/* Put up drop-down list with targets on it. */
{
struct targetPcrServer *server;

printf("<SELECT NAME=\"wp_target\">\n");
printf("  <OPTION%s VALUE=genome>genome assembly</OPTION>\n", 
       (sameString(target, "genome") ? " SELECTED" : ""));
for (server = serverList; server != NULL; server = server->next)
    {
    printf("  <OPTION%s VALUE=%s>%s</OPTION>\n", 
	   (sameString(target, server->targetDb->name) ? " SELECTED" : ""), 
	   server->targetDb->name, server->targetDb->description);
    }
printf("</SELECT>\n");
}

void redoDbAndOrgIfNoServer(struct pcrServer *serverList, char **pDb, char **pOrg)
/* Check that database and organism are on our serverList.  If not, then update
 * them to first thing that is. */
{
struct pcrServer *server, *orgServer = NULL;
char *organism = *pOrg;
char *db = *pDb;
boolean gotDb = FALSE;

/*  Find first server for our organism */
for (server = serverList; server != NULL; server = server->next)
    {
    if (sameString(server->genome, organism))
         {
	 orgServer = server;
	 break;
	 }
    }

/* If no server, change our organism to the one of the first server in list. */
if (orgServer == NULL)
    {
    orgServer = serverList;
    *pOrg = organism = orgServer->genome;
    }

/* Search for our database. */
for (server = serverList; server != NULL; server = server->next)
    {
    if (sameString(db, server->db))
        {
	gotDb = TRUE;
	break;
	}
    }

/* If no server for db, change db. */
if (!gotDb)
    {
    if (differentString(db, orgServer->db))
	printf("<HR><P><EM><B>Note:</B> In-Silico PCR is not available for %s %s; "
	       "defaulting to %s %s</EM></P><HR>\n",
	       hGenome(db), hFreezeDate(db), organism, hFreezeDate(orgServer->db));
    *pDb = db = orgServer->db;
    }
}

void doGetPrimers(char *db, char *organism, struct pcrServer *serverList,
	char *fPrimer, char *rPrimer, int maxSize, int minPerfect, int minGood,
	boolean flipReverse)
/* Put up form to get primers. */
{
redoDbAndOrgIfNoServer(serverList, &db, &organism);
struct sqlConnection *conn = hConnectCentral();
boolean gotTargetDb = sqlTableExists(conn, "targetDb");
hDisconnectCentral(&conn);

printf("<FORM ACTION=\"../cgi-bin/hgPcr\" METHOD=\"GET\" NAME=\"mainForm\">\n");
cartSaveSession(cart);

printf("<TABLE BORDER=0 WIDTH=\"96%%\" COLS=7><TR>\n");

printf("%s", "<TD><CENTER>\n");
printf("Genome:<BR>");
showGenomes(organism, serverList);
printf("%s", "</TD>\n");

printf("%s", "<TD><CENTER>\n");
printf("Assembly:<BR>");
showAssemblies(organism, db, serverList, gotTargetDb);
printf("%s", "</TD>\n");

if (gotTargetDb)
    {
    struct targetPcrServer *targetServerList = getTargetServerList(db, NULL);
    if (targetServerList != NULL)
	{
	char *target = cartUsualString(cart, "wp_target", "genome");
	printf("%s", "<TD><CENTER>\n");
	printf("Target:<BR>");
	showTargets(target, targetServerList);
	printf("%s", "</TD>\n");
	}
    else
	cgiMakeHiddenVar("wp_target", "genome");
    }
else
    cgiMakeHiddenVar("wp_target", "genome");

printf("%s", "<TD COLWIDTH=2><CENTER>\n");
printf("Forward Primer:<BR>");
cgiMakeTextVar("wp_f", fPrimer, 22);
printf("%s", "</TD>\n");

printf("%s", "<TD><CENTER COLWIDTH=2>\n");
printf(" Reverse Primer:<BR>");
cgiMakeTextVar("wp_r", rPrimer, 22);
printf("%s", "</TD>\n");

printf("%s", "<TD><CENTER>\n");
printf("&nbsp;<BR>");
cgiMakeButton("Submit", "submit");
printf("%s", "</TD>\n");

printf("</TR></TABLE><BR>");

printf("<TABLE BORDER=0 WIDTH=\"96%%\" COLS=4><TR>\n");
printf("%s", "<TD><CENTER>\n");
printf("Max Product Size: ");
cgiMakeIntVar("wp_size", maxSize, 5);
printf("%s", "</TD>\n");

printf("%s", "<TD><CENTER>\n");
printf(" Min Perfect Match: ");
cgiMakeIntVar("wp_perfect", minPerfect, 2);
printf("%s", "</TD>\n");

printf("%s", "<TD><CENTER>\n");
printf(" Min Good Match: ");
cgiMakeIntVar("wp_good", minGood, 2);
printf("%s", "</TD>\n");

printf("%s", "<TD><CENTER>\n");
printf(" Flip Reverse Primer: ");
cgiMakeCheckBox("wp_flipReverse", flipReverse);
printf("%s", "</TD>\n");
printf("</TR></TABLE><BR>");

printf("</FORM>\n");

/* Put up a second form who's sole purpose is to preserve state
 * when the user flips the genome button. */
printf("<FORM ACTION=\"../cgi-bin/hgPcr\" METHOD=\"GET\" NAME=\"orgForm\">"
       "<input type=\"hidden\" name=\"wp_target\" value=\"\">\n"
       "<input type=\"hidden\" name=\"db\" value=\"\">\n"
       "<input type=\"hidden\" name=\"org\" value=\"\">\n"
       "<input type=\"hidden\" name=\"wp_f\" value=\"\">\n"
       "<input type=\"hidden\" name=\"wp_r\" value=\"\">\n"
       "<input type=\"hidden\" name=\"wp_size\" value=\"\">\n"
       "<input type=\"hidden\" name=\"wp_perfect\" value=\"\">\n"
       "<input type=\"hidden\" name=\"wp_good\" value=\"\">\n"
       "<input type=\"hidden\" name=\"wp_showPage\" value=\"true\">\n");
cartSaveSession(cart);
printf("</FORM>\n");
webNewSection("About In-Silico PCR");
doHelp();
printf("%s", "<P><H3>Author</H3>\n");
printf("%s", "<P>In-Silico PCR was written by "
"<A HREF=\"mailto:kent@soe.ucsc.edu\">Jim Kent</A>.\n"
"Interactive use on this web server is free to all.\n"
"Sources and executables to run batch jobs on your own server are available free\n"
"for academic, personal, and non-profit purposes.  Non-exclusive commercial\n"
"licenses are also available.  Contact Jim for details.</P>\n");
}

void writePrimers(struct gfPcrOutput *gpo, char *fileName)
/* Write primer sequences to file.  Look at only the first gpo because there
 * is only one set of primers in the input form. */
{
if (gpo == NULL)
    return;
FILE *f = mustOpen(fileName, "w");
fprintf(f, "%s\t%s\n", gpo->fPrimer, gpo->rPrimer);
carefulClose(&f);
}

void writePcrResultTrack(struct gfPcrOutput *gpoList, char *db, char *target)
/* Write trash files and store their name in a cart variable. */
{
char *cartVar = pcrResultCartVar(db);
struct tempName bedTn, primerTn;
char buf[2048];
trashDirFile(&bedTn, "hgPcr", "hgPcr", ".psl");
trashDirFile(&primerTn, "hgPcr", "hgPcr", ".txt");
gfPcrOutputWriteAll(gpoList, "psl", NULL, bedTn.forCgi);
writePrimers(gpoList, primerTn.forCgi);
if (isNotEmpty(target))
    safef(buf, sizeof(buf), "%s %s %s", bedTn.forCgi, primerTn.forCgi, target);
else
    safef(buf, sizeof(buf), "%s %s", bedTn.forCgi, primerTn.forCgi);
cartSetString(cart, cartVar, buf);
}


void doQuery(struct pcrServer *server, struct gfPcrInput *gpi,
	     int maxSize, int minPerfect, int minGood)
/* Send a query to a genomic assembly PCR server and print the results. */
{
struct gfPcrOutput *gpoList =
    gfPcrViaNet(server->host, server->port, server->seqDir, gpi,
		maxSize, minPerfect, minGood);
if (gpoList != NULL)
    {
    char urlFormat[2048];
    safef(urlFormat, sizeof(urlFormat), "%s?%s&db=%s&position=%%s:%%d-%%d"
	  "&hgPcrResult=pack", 
	  hgTracksName(), cartSidUrlString(cart), server->db);
    printf("<TT><PRE>");
    gfPcrOutputWriteAll(gpoList, "fa", urlFormat, "stdout");
    printf("</PRE></TT>");
    writePcrResultTrack(gpoList, server->db, NULL);
    }
else
    {
    printf("No matches to %s %s in %s %s", gpi->fPrimer, gpi->rPrimer, 
	   server->genome, server->description);
    }
}

void doTargetQuery(struct targetPcrServer *server, struct gfPcrInput *gpi,
		   int maxSize, int minPerfect, int minGood)
/* Send a query to a non-genomic target PCR server and print the results. */
{
struct gfPcrOutput *gpoList;
char seqDir[PATH_LEN];
splitPath(server->targetDb->seqFile, seqDir, NULL, NULL);
if (endsWith("/", seqDir))
    seqDir[strlen(seqDir) - 1] = '\0';
gpoList = gfPcrViaNet(server->host, server->port, seqDir, gpi,
		      maxSize, minPerfect, minGood);
if (gpoList != NULL)
    {
    struct gfPcrOutput *gpo;
    char urlFormat[2048];
    printf("The sequences and coordinates shown below are from %s, "
	   "not from the genome assembly.  The links lead to the "
	   "Genome Browser at the position of the entire target "
	   "sequence.<BR>\n",
	   server->targetDb->description);
    printf("<TT><PRE>");
    for (gpo = gpoList;  gpo != NULL;  gpo = gpo->next)
	{
	/* Not used as a format here; we modify the name used for position: */
	safef(urlFormat, sizeof(urlFormat), "%s?%s&db=%s&position=%s"
	      "&hgPcrResult=pack", 
	      hgTracksName(), cartSidUrlString(cart), server->targetDb->db,
	      pcrResultItemAccession(gpo->seqName));
	if (gpo->strand == '-')
	    printf("<EM>Warning: this amplification is on the reverse-"
		   "complement of %s</EM>.\n", gpo->seqName);
	gfPcrOutputWriteOne(gpo, "fa", urlFormat, stdout);
	printf("\n");
	}
    printf("</PRE></TT>");
    writePcrResultTrack(gpoList, server->targetDb->db, server->targetDb->name);
    }
else
    {
    printf("No matches to %s %s in %s", gpi->fPrimer, gpi->rPrimer, 
	   server->targetDb->description);
    }
}

boolean doPcr(struct pcrServer *server, struct targetPcrServer *targetServer,
	char *fPrimer, char *rPrimer, 
	int maxSize, int minPerfect, int minGood, boolean flipReverse)
/* Do the PCR, and show results. */
{
struct errCatch *errCatch = errCatchNew();
boolean ok = FALSE;

hgBotDelay();
if (flipReverse)
    reverseComplement(rPrimer, strlen(rPrimer));
if (errCatchStart(errCatch))
    {
    struct gfPcrInput *gpi;

    AllocVar(gpi);
    gpi->fPrimer = fPrimer;
    gpi->rPrimer = rPrimer;
    if (server != NULL)
	doQuery(server, gpi, maxSize, minPerfect, minGood);
    if (targetServer != NULL)
	doTargetQuery(targetServer, gpi, maxSize, minPerfect, minGood);
    ok = TRUE;
    }
errCatchEnd(errCatch);
if (errCatch->gotError)
    warn("%s", errCatch->message->string);
errCatchFree(&errCatch); 
if (flipReverse)
    reverseComplement(rPrimer, strlen(rPrimer));
webNewSection("Primer Melting Temperatures");
printf("<TT>");
printf("<B>Forward:</B> %4.1f C %s<BR>\n", oligoTm(fPrimer, 50.0, 50.0), fPrimer);
printf("<B>Reverse:</B> %4.1f C %s<BR>\n", oligoTm(rPrimer, 50.0, 50.0), rPrimer);
printf("</TT>");
printf("The temperature calculations are done assuming 50 mM salt and 50 nM annealing "
       "oligo concentration.  The code to calculate the melting temp comes from "
       "<A HREF=\"http://frodo.wi.mit.edu/primer3/input.htm\" target=_blank>"
       "Primer3</A>.");
return ok;
}

void dispatch()
/* Look at input variables and figure out which page to show. */
{
char *db, *organism;
int maxSize = 4000;
int minPerfect = 15;
int minGood = 15;
char *fPrimer = cartUsualString(cart, "wp_f", "");
char *rPrimer = cartUsualString(cart, "wp_r", "");
boolean flipReverse = cartUsualBoolean(cart, "wp_flipReverse", FALSE);
struct pcrServer *serverList = getServerList();

getDbAndGenome(cart, &db, &organism, oldVars);

/* Get variables. */
maxSize = cartUsualInt(cart, "wp_size", maxSize);
minPerfect = cartUsualInt(cart, "wp_perfect", minPerfect);
minGood = cartUsualInt(cart, "wp_good", minGood);
if (minPerfect < 15)
     minPerfect = 15;
if (minGood < minPerfect)
     minGood = minPerfect;

/* Decide based on transient variables what page to put up. 
 * By default put up get primer page. */
if (isNotEmpty(fPrimer) && isNotEmpty(rPrimer) &&
	!cartVarExists(cart, "wp_showPage"))
    {
    struct pcrServer *server = NULL;
    struct targetPcrServer *targetServer = NULL;
    char *target = cartUsualString(cart, "wp_target", "genome");
    if (isEmpty(target) || sameString(target, "genome"))
	server = findServer(db, serverList);
    else
	{
	targetServer = getTargetServerList(db, target);
	if (targetServer == NULL)
	    errAbort("Can't find targetPcr server for db=%s, target=%s",
		     db, target);
	}

    fPrimer = gfPcrMakePrimer(fPrimer);
    rPrimer = gfPcrMakePrimer(rPrimer);
    if (doPcr(server, targetServer, fPrimer, rPrimer,
	      maxSize, minPerfect, minGood, flipReverse))
         return;
    }
doGetPrimers(db, organism, serverList,
	fPrimer, rPrimer, maxSize, minPerfect, minGood, flipReverse);
}

void doMiddle(struct cart *theCart)
/* Write header and body of html page. */
{
cart = theCart;
dnaUtilOpen();
cartWebStart(cart, NULL, "UCSC In-Silico PCR");
dispatch();
cartWebEnd();
}


char *excludeVars[] = {"Submit", "submit", "wp_f", "wp_r", "wp_showPage", NULL};

int main(int argc, char *argv[])
/* Process command line. */
{
oldVars = hashNew(10);
cgiSpoof(&argc, argv);
htmlSetBackground(hBackgroundImage());
cartEmptyShell(doMiddle, hUserCookie(), excludeVars, oldVars);
return 0;
}

