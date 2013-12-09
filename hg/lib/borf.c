/* borf.c was originally generated by the autoSql program, which also 
 * generated borf.h and borf.sql.  This module links the database and
 * the RAM representation of objects. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "borf.h"
#include "hdb.h"
#include "dnaseq.h"
#include "fa.h"
#include "portable.h"

static char const rcsid[] = "$Id: borf.c,v 1.7 2008/09/03 19:19:19 markd Exp $";
static char *_bestOrfExe = "/projects/compbio/bin/bestorf.linux/bestorf";
static char *_bestOrfParam = "/projects/compbio/bin/bestorf.linux/hume.dat";

void borfStaticLoad(char **row, struct borf *ret)
/* Load a row from borf table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->name = row[0];
ret->size = sqlSigned(row[1]);
strcpy(ret->strand, row[2]);
ret->feature = row[3];
ret->cdsStart = sqlSigned(row[4]);
ret->cdsEnd = sqlSigned(row[5]);
ret->score = atof(row[6]);
ret->orfStart = sqlSigned(row[7]);
ret->orfEnd = sqlSigned(row[8]);
ret->cdsSize = sqlSigned(row[9]);
strcpy(ret->frame, row[10]);
ret->protein = row[11];
}

struct borf *borfLoad(char **row)
/* Load a borf from row fetched with select * from borf
 * from database.  Dispose of this with borfFree(). */
{
struct borf *ret;

AllocVar(ret);
ret->name = cloneString(row[0]);
ret->size = sqlSigned(row[1]);
strcpy(ret->strand, row[2]);
ret->feature = cloneString(row[3]);
ret->cdsStart = sqlSigned(row[4]);
ret->cdsEnd = sqlSigned(row[5]);
ret->score = atof(row[6]);
ret->orfStart = sqlSigned(row[7]);
ret->orfEnd = sqlSigned(row[8]);
ret->cdsSize = sqlSigned(row[9]);
strcpy(ret->frame, row[10]);
if(ret->cdsSize != 0)
    ret->protein = cloneString(row[11]);
return ret;
}

struct borf *borfLoadAll(char *fileName) 
/* Load all borf from a tab-separated file.
 * Dispose of this with borfFreeList(). */
{
struct borf *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[12];

while (lineFileChopNextTab(lf, row, ArraySize(row)))
    {
    el = borfLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct borf *borfLoadWhere(struct sqlConnection *conn, char *table, char *where)
/* Load all borf from table that satisfy where clause. The
 * where clause may be NULL in which case whole table is loaded
 * Dispose of this with borfFreeList(). */
{
struct borf *list = NULL, *el;
struct dyString *query = dyStringNew(256);
struct sqlResult *sr;
char **row;

dyStringPrintf(query, "select * from %s", table);
if (where != NULL)
    dyStringPrintf(query, " where %s", where);
sr = sqlGetResult(conn, query->string);
while ((row = sqlNextRow(sr)) != NULL)
    {
    el = borfLoad(row);
    slAddHead(&list, el);
    }
slReverse(&list);
sqlFreeResult(&sr);
dyStringFree(&query);
return list;
}

struct borf *borfCommaIn(char **pS, struct borf *ret)
/* Create a borf out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new borf */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->name = sqlStringComma(&s);
ret->size = sqlSignedComma(&s);
sqlFixedStringComma(&s, ret->strand, sizeof(ret->strand));
ret->feature = sqlStringComma(&s);
ret->cdsStart = sqlSignedComma(&s);
ret->cdsEnd = sqlSignedComma(&s);
ret->score = sqlFloatComma(&s);
ret->orfStart = sqlSignedComma(&s);
ret->orfEnd = sqlSignedComma(&s);
ret->cdsSize = sqlSignedComma(&s);
sqlFixedStringComma(&s, ret->frame, sizeof(ret->frame));
ret->protein = sqlStringComma(&s);
*pS = s;
return ret;
}

void borfFree(struct borf **pEl)
/* Free a single dynamically allocated borf such as created
 * with borfLoad(). */
{
struct borf *el;

if ((el = *pEl) == NULL) return;
freeMem(el->name);
freeMem(el->feature);
freeMem(el->protein);
freez(pEl);
}

void borfFreeList(struct borf **pList)
/* Free a list of dynamically allocated borf's */
{
struct borf *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    borfFree(&el);
    }
*pList = NULL;
}

void borfOutput(struct borf *el, FILE *f, char sep, char lastSep) 
/* Print out borf.  Separate fields with sep. Follow last field with lastSep. */
{
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->name);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%d", el->size);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->strand);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
if (el->feature != NULL)
    fprintf(f, "%s", el->feature);
else
    fprintf(f, "NA");
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%d", el->cdsStart);
fputc(sep,f);
fprintf(f, "%d", el->cdsEnd);
fputc(sep,f);
fprintf(f, "%f", el->score);
fputc(sep,f);
fprintf(f, "%d", el->orfStart);
fputc(sep,f);
fprintf(f, "%d", el->orfEnd);
fputc(sep,f);
fprintf(f, "%d", el->cdsSize);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->frame);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
if (el->protein != NULL)
    fprintf(f, "%s", el->protein);
else
    fprintf(f, "NA");
if (sep == ',') fputc('"',f);
fputc(lastSep,f);
}

void borfSetExeAndParam(char *exePath, char *paramPath)
/* Set the path to the bestOrf probram and parameter file to be used
   for running borfFromGenomeBed. */
{
_bestOrfExe = exePath;
_bestOrfParam = paramPath;
}

static char *borfMustFindLine(struct lineFile *lf, char *pat)
/* Find line that starts (after skipping white space)
 * with pattern or die trying.  Skip over pat in return*/
{
char *line;
while (lineFileNext(lf, &line, NULL))
    {
    line = skipLeadingSpaces(line);
    if (startsWith(pat, line))
	{
	line += strlen(pat);
	return skipLeadingSpaces(line);
	}
    }
errAbort("borf::borfMustFindLine() - Couldn't find %s in %s\n", pat, lf->fileName);
return NULL;
}


struct borf *borfFromBestorfOutput(char *fileName)
/* Convert bestorf output to borf structure. */
{
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *line = borfMustFindLine(lf, "BESTORF");
char *word=NULL;
char *row[13];
struct borf *borf = NULL;
struct dnaSeq seq;
AllocVar(borf);
ZeroVar(&seq);

line = borfMustFindLine(lf, "Seq name:");
word = nextWord(&line);
borf->name = cloneString(word);                            /* Name */
line = borfMustFindLine(lf, "Length of sequence:");
borf->size = atoi(line);                                /* Size */
lineFileNeedNext(lf, &line, NULL);
line = skipLeadingSpaces(line);
if (startsWith("no reliable", line))
    {
    return borf;
    }
else
    {
    line = borfMustFindLine(lf, "G Str F");
    lineFileSkip(lf, 1);
    lineFileRow(lf, row);
    safef(borf->strand, sizeof(borf->strand),"%s", row[1]); /* Strand. */
    borf->feature = cloneString(row[3]);                    /* Feature. */
    borf->cdsStart = lineFileNeedNum(lf, row, 4) - 1;       /* cdsStart */
    borf->cdsEnd = lineFileNeedNum(lf, row, 6);             /* cdsEnd */
    borf->score = atof(row[7]);                             /* score */
    borf->orfStart = lineFileNeedNum(lf, row, 8) - 1;       /* orfStart */
    borf->orfEnd = lineFileNeedNum(lf, row, 10);            /* orfEnd */
    borf->cdsSize = atoi(row[11]);                          /* cdsSize. */
    safef(borf->frame, sizeof(borf->frame), "%s", row[12]); /* Frame */
    line = borfMustFindLine(lf, "Predicted protein");
    if (!faPepSpeedReadNext(lf, &seq.dna, &seq.size, &seq.name))
	errAbort("Can't find peptide in %s", lf->fileName);
    borf->protein = cloneString(seq.dna);                   /* Protein. */
    }
lineFileClose(&lf);
return borf;
}

struct borf *borfFromGenomeBed(char *db, struct bed *bed)
/* borfBig - Run Victor Solovyev's bestOrf on a genome bed's coordinates. */
{
static char *tmpFa = NULL;
static char *tmpOrf = NULL;
struct borf *borf = NULL;
struct dnaSeq *seq = NULL;
struct dyString *cmd = newDyString(256);
int retVal = 0;
if(tmpFa == NULL)
    tmpFa = cloneString(rTempName("/tmp", "borf", ".fa"));
if(tmpOrf == NULL)
    tmpOrf = cloneString(rTempName("/tmp","borf", ".out"));
seq = hSeqForBed(db, bed);
faWrite(tmpFa, seq->name, seq->dna, seq->size);
dyStringClear(cmd);
dyStringPrintf(cmd, "%s %s %s > %s", _bestOrfExe, _bestOrfParam, tmpFa, tmpOrf);
retVal = system(cmd->string);
borf = borfFromBestorfOutput(tmpOrf);
remove(tmpFa);
remove(tmpOrf);
dyStringFree(&cmd);
dnaSeqFree(&seq);
return borf;
}
