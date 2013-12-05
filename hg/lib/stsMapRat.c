/* stsMapRat.c was originally generated by the autoSql program, which also 
 * generated stsMapRat.h and stsMapRat.sql.  This module links the database and
 * the RAM representation of objects. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "stsMapRat.h"

static char const rcsid[] = "$Id: stsMapRat.c,v 1.3 2005/04/13 06:25:57 markd Exp $";

void stsMapRatStaticLoad(char **row, struct stsMapRat *ret)
/* Load a row from stsMapRat table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->chrom = row[0];
ret->chromStart = sqlSigned(row[1]);
ret->chromEnd = sqlUnsigned(row[2]);
ret->name = row[3];
ret->score = sqlUnsigned(row[4]);
ret->identNo = sqlUnsigned(row[5]);
ret->ctgAcc = row[6];
ret->otherAcc = row[7];
ret->rhChrom = row[8];
ret->rhPos = atof(row[9]);
ret->rhLod = atof(row[10]);
ret->fhhChr = row[11];
ret->fhhPos = atof(row[12]);
ret->shrspChrom = row[13];
ret->shrspPos = atof(row[14]);
}

struct stsMapRat *stsMapRatLoad(char **row)
/* Load a stsMapRat from row fetched with select * from stsMapRat
 * from database.  Dispose of this with stsMapRatFree(). */
{
struct stsMapRat *ret;

AllocVar(ret);
ret->chrom = cloneString(row[0]);
ret->chromStart = sqlSigned(row[1]);
ret->chromEnd = sqlUnsigned(row[2]);
ret->name = cloneString(row[3]);
ret->score = sqlUnsigned(row[4]);
ret->identNo = sqlUnsigned(row[5]);
ret->ctgAcc = cloneString(row[6]);
ret->otherAcc = cloneString(row[7]);
ret->rhChrom = cloneString(row[8]);
ret->rhPos = atof(row[9]);
ret->rhLod = atof(row[10]);
ret->fhhChr = cloneString(row[11]);
ret->fhhPos = atof(row[12]);
ret->shrspChrom = cloneString(row[13]);
ret->shrspPos = atof(row[14]);
return ret;
}

struct stsMapRat *stsMapRatLoadAll(char *fileName) 
/* Load all stsMapRat from a tab-separated file.
 * Dispose of this with stsMapRatFreeList(). */
{
struct stsMapRat *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[15];

while (lineFileRow(lf, row))
    {
    el = stsMapRatLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct stsMapRat *stsMapRatCommaIn(char **pS, struct stsMapRat *ret)
/* Create a stsMapRat out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new stsMapRat */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->chrom = sqlStringComma(&s);
ret->chromStart = sqlSignedComma(&s);
ret->chromEnd = sqlUnsignedComma(&s);
ret->name = sqlStringComma(&s);
ret->score = sqlUnsignedComma(&s);
ret->identNo = sqlUnsignedComma(&s);
ret->ctgAcc = sqlStringComma(&s);
ret->otherAcc = sqlStringComma(&s);
ret->rhChrom = sqlStringComma(&s);
ret->rhPos = sqlFloatComma(&s);
ret->rhLod = sqlFloatComma(&s);
ret->fhhChr = sqlStringComma(&s);
ret->fhhPos = sqlFloatComma(&s);
ret->shrspChrom = sqlStringComma(&s);
ret->shrspPos = sqlFloatComma(&s);
*pS = s;
return ret;
}

void stsMapRatFree(struct stsMapRat **pEl)
/* Free a single dynamically allocated stsMapRat such as created
 * with stsMapRatLoad(). */
{
struct stsMapRat *el;

if ((el = *pEl) == NULL) return;
freeMem(el->chrom);
freeMem(el->name);
freeMem(el->ctgAcc);
freeMem(el->otherAcc);
freeMem(el->rhChrom);
freeMem(el->fhhChr);
freeMem(el->shrspChrom);
freez(pEl);
}

void stsMapRatFreeList(struct stsMapRat **pList)
/* Free a list of dynamically allocated stsMapRat's */
{
struct stsMapRat *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    stsMapRatFree(&el);
    }
*pList = NULL;
}

void stsMapRatOutput(struct stsMapRat *el, FILE *f, char sep, char lastSep) 
/* Print out stsMapRat.  Separate fields with sep. Follow last field with lastSep. */
{
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->chrom);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%d", el->chromStart);
fputc(sep,f);
fprintf(f, "%u", el->chromEnd);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->name);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%u", el->score);
fputc(sep,f);
fprintf(f, "%u", el->identNo);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->ctgAcc);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->otherAcc);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->rhChrom);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%f", el->rhPos);
fputc(sep,f);
fprintf(f, "%f", el->rhLod);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->fhhChr);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%f", el->fhhPos);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->shrspChrom);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%f", el->shrspPos);
fputc(lastSep,f);
}

/* -------------------------------- End autoSql Generated Code -------------------------------- */

