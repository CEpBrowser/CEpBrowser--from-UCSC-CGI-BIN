/* geneStarts - print start of genes in database. */
#include "common.h"
#include "jksql.h"
#include "genePred.h"

static char const rcsid[] = "$Id: geneStarts.c,v 1.2 2003/05/06 07:41:07 kate Exp $";

void usage()
/* Explain usage and exit. */
{
errAbort(
  "geneStarts - print start of genes in database\n"
  "usage:\n"
  "   geneStarts chromosome start end\n");
}

void geneStarts(char *chromosome, int start, int end)
/* geneStarts - print start of genes in database. */
{
struct sqlConnection *conn = sqlConnect("hg3");
struct sqlResult *sr;
char **row;
char query[256];
struct genePred *gp;

sprintf(query, 
   "select * from genieKnown where chrom = '%s' and txStart >= %d and txStart < %d", 
   chromosome, start, end);
sr = sqlGetResult(conn, query);
while ((row = sqlNextRow(sr)) != NULL)
    {
    gp = genePredLoad(row);
    printf("%s on %s:%d-%d\n", gp->name, gp->chrom, gp->txStart, gp->txEnd);
    }
sqlFreeResult(&sr);
sqlDisconnect(&conn);
}

int main(int argc, char *argv[])
/* Process command line. */
{
if (argc != 4)
    usage();
if (!isdigit(argv[2][0]) || !isdigit(argv[3][0]))
    usage();
geneStarts(argv[1], atoi(argv[2]), atoi(argv[3]));
return 0;
}
