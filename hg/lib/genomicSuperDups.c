/* genomicSuperDups.c was originally generated by the autoSql program, which also 
 * generated genomicSuperDups.h and genomicSuperDups.sql.  This module links the database and
 * the RAM representation of objects. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "genomicSuperDups.h"

static char const rcsid[] = "$Id: genomicSuperDups.c,v 1.3 2005/04/13 06:25:53 markd Exp $";

void genomicSuperDupsStaticLoad(char **row, struct genomicSuperDups *ret)
/* Load a row from genomicSuperDups table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->chrom = row[0];
ret->chromStart = sqlUnsigned(row[1]);
ret->chromEnd = sqlUnsigned(row[2]);
ret->name = row[3];
ret->score = sqlUnsigned(row[4]);
strcpy(ret->strand, row[5]);
ret->otherChrom = row[6];
ret->otherStart = sqlUnsigned(row[7]);
ret->otherEnd = sqlUnsigned(row[8]);
ret->otherSize = sqlUnsigned(row[9]);
ret->uid = sqlUnsigned(row[10]);
ret->posBasesHit = sqlUnsigned(row[11]);
ret->testResult = row[12];
ret->verdict = row[13];
ret->chits = row[14];
ret->ccov = row[15];
ret->alignfile = row[16];
ret->alignL = sqlUnsigned(row[17]);
ret->indelN = sqlUnsigned(row[18]);
ret->indelS = sqlUnsigned(row[19]);
ret->alignB = sqlUnsigned(row[20]);
ret->matchB = sqlUnsigned(row[21]);
ret->mismatchB = sqlUnsigned(row[22]);
ret->transitionsB = sqlUnsigned(row[23]);
ret->transversionsB = sqlUnsigned(row[24]);
ret->fracMatch = atof(row[25]);
ret->fracMatchIndel = atof(row[26]);
ret->jcK = atof(row[27]);
ret->k2K = atof(row[28]);
}

struct genomicSuperDups *genomicSuperDupsLoad(char **row)
/* Load a genomicSuperDups from row fetched with select * from genomicSuperDups
 * from database.  Dispose of this with genomicSuperDupsFree(). */
{
struct genomicSuperDups *ret;

AllocVar(ret);
ret->chrom = cloneString(row[0]);
ret->chromStart = sqlUnsigned(row[1]);
ret->chromEnd = sqlUnsigned(row[2]);
ret->name = cloneString(row[3]);
ret->score = sqlUnsigned(row[4]);
strcpy(ret->strand, row[5]);
ret->otherChrom = cloneString(row[6]);
ret->otherStart = sqlUnsigned(row[7]);
ret->otherEnd = sqlUnsigned(row[8]);
ret->otherSize = sqlUnsigned(row[9]);
ret->uid = sqlUnsigned(row[10]);
ret->posBasesHit = sqlUnsigned(row[11]);
ret->testResult = cloneString(row[12]);
ret->verdict = cloneString(row[13]);
ret->chits = cloneString(row[14]);
ret->ccov = cloneString(row[15]);
ret->alignfile = cloneString(row[16]);
ret->alignL = sqlUnsigned(row[17]);
ret->indelN = sqlUnsigned(row[18]);
ret->indelS = sqlUnsigned(row[19]);
ret->alignB = sqlUnsigned(row[20]);
ret->matchB = sqlUnsigned(row[21]);
ret->mismatchB = sqlUnsigned(row[22]);
ret->transitionsB = sqlUnsigned(row[23]);
ret->transversionsB = sqlUnsigned(row[24]);
ret->fracMatch = atof(row[25]);
ret->fracMatchIndel = atof(row[26]);
ret->jcK = atof(row[27]);
ret->k2K = atof(row[28]);
return ret;
}

struct genomicSuperDups *genomicSuperDupsLoadAll(char *fileName) 
/* Load all genomicSuperDups from a tab-separated file.
 * Dispose of this with genomicSuperDupsFreeList(). */
{
struct genomicSuperDups *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[29];

while (lineFileRow(lf, row))
    {
    el = genomicSuperDupsLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct genomicSuperDups *genomicSuperDupsLoadWhere(struct sqlConnection *conn, char *table, char *where)
/* Load all genomicSuperDups from table that satisfy where clause. The
 * where clause may be NULL in which case whole table is loaded
 * Dispose of this with genomicSuperDupsFreeList(). */
{
struct genomicSuperDups *list = NULL, *el;
struct dyString *query = dyStringNew(256);
struct sqlResult *sr;
char **row;

dyStringPrintf(query, "select * from %s", table);
if (where != NULL)
    dyStringPrintf(query, " where %s", where);
sr = sqlGetResult(conn, query->string);
while ((row = sqlNextRow(sr)) != NULL)
    {
    el = genomicSuperDupsLoad(row);
    slAddHead(&list, el);
    }
slReverse(&list);
sqlFreeResult(&sr);
dyStringFree(&query);
return list;
}

struct genomicSuperDups *genomicSuperDupsCommaIn(char **pS, struct genomicSuperDups *ret)
/* Create a genomicSuperDups out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new genomicSuperDups */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->chrom = sqlStringComma(&s);
ret->chromStart = sqlUnsignedComma(&s);
ret->chromEnd = sqlUnsignedComma(&s);
ret->name = sqlStringComma(&s);
ret->score = sqlUnsignedComma(&s);
sqlFixedStringComma(&s, ret->strand, sizeof(ret->strand));
ret->otherChrom = sqlStringComma(&s);
ret->otherStart = sqlUnsignedComma(&s);
ret->otherEnd = sqlUnsignedComma(&s);
ret->otherSize = sqlUnsignedComma(&s);
ret->uid = sqlUnsignedComma(&s);
ret->posBasesHit = sqlUnsignedComma(&s);
ret->testResult = sqlStringComma(&s);
ret->verdict = sqlStringComma(&s);
ret->chits = sqlStringComma(&s);
ret->ccov = sqlStringComma(&s);
ret->alignfile = sqlStringComma(&s);
ret->alignL = sqlUnsignedComma(&s);
ret->indelN = sqlUnsignedComma(&s);
ret->indelS = sqlUnsignedComma(&s);
ret->alignB = sqlUnsignedComma(&s);
ret->matchB = sqlUnsignedComma(&s);
ret->mismatchB = sqlUnsignedComma(&s);
ret->transitionsB = sqlUnsignedComma(&s);
ret->transversionsB = sqlUnsignedComma(&s);
ret->fracMatch = sqlFloatComma(&s);
ret->fracMatchIndel = sqlFloatComma(&s);
ret->jcK = sqlFloatComma(&s);
ret->k2K = sqlFloatComma(&s);
*pS = s;
return ret;
}

void genomicSuperDupsFree(struct genomicSuperDups **pEl)
/* Free a single dynamically allocated genomicSuperDups such as created
 * with genomicSuperDupsLoad(). */
{
struct genomicSuperDups *el;

if ((el = *pEl) == NULL) return;
freeMem(el->chrom);
freeMem(el->name);
freeMem(el->otherChrom);
freeMem(el->testResult);
freeMem(el->verdict);
freeMem(el->chits);
freeMem(el->ccov);
freeMem(el->alignfile);
freez(pEl);
}

void genomicSuperDupsFreeList(struct genomicSuperDups **pList)
/* Free a list of dynamically allocated genomicSuperDups's */
{
struct genomicSuperDups *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    genomicSuperDupsFree(&el);
    }
*pList = NULL;
}

void genomicSuperDupsOutput(struct genomicSuperDups *el, FILE *f, char sep, char lastSep) 
/* Print out genomicSuperDups.  Separate fields with sep. Follow last field with lastSep. */
{
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->chrom);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%u", el->chromStart);
fputc(sep,f);
fprintf(f, "%u", el->chromEnd);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->name);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%u", el->score);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->strand);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->otherChrom);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%u", el->otherStart);
fputc(sep,f);
fprintf(f, "%u", el->otherEnd);
fputc(sep,f);
fprintf(f, "%u", el->otherSize);
fputc(sep,f);
fprintf(f, "%u", el->uid);
fputc(sep,f);
fprintf(f, "%u", el->posBasesHit);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->testResult);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->verdict);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->chits);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->ccov);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->alignfile);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%u", el->alignL);
fputc(sep,f);
fprintf(f, "%u", el->indelN);
fputc(sep,f);
fprintf(f, "%u", el->indelS);
fputc(sep,f);
fprintf(f, "%u", el->alignB);
fputc(sep,f);
fprintf(f, "%u", el->matchB);
fputc(sep,f);
fprintf(f, "%u", el->mismatchB);
fputc(sep,f);
fprintf(f, "%u", el->transitionsB);
fputc(sep,f);
fprintf(f, "%u", el->transversionsB);
fputc(sep,f);
fprintf(f, "%f", el->fracMatch);
fputc(sep,f);
fprintf(f, "%f", el->fracMatchIndel);
fputc(sep,f);
fprintf(f, "%f", el->jcK);
fputc(sep,f);
fprintf(f, "%f", el->k2K);
fputc(lastSep,f);
}

