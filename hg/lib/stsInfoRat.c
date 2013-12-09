/* stsInfoRat.c was originally generated by the autoSql program, which also 
 * generated stsInfoRat.h and stsInfoRat.sql.  This module links the database and
 * the RAM representation of objects. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "stsInfoRat.h"

static char const rcsid[] = "$Id: stsInfoRat.c,v 1.3 2005/04/13 06:25:57 markd Exp $";

void stsInfoRatStaticLoad(char **row, struct stsInfoRat *ret)
/* Load a row from stsInfoRat table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->identNo = sqlUnsigned(row[0]);
ret->name = row[1];
ret->RGDId = sqlUnsigned(row[2]);
ret->RGDName = row[3];
ret->UiStsId = sqlUnsigned(row[4]);
ret->nameCount = sqlUnsigned(row[5]);
ret->alias = row[6];
ret->primer1 = row[7];
ret->primer2 = row[8];
ret->distance = row[9];
ret->sequence = sqlUnsigned(row[10]);
ret->organis = row[11];
ret->fhhName = row[12];
ret->fhhChr = row[13];
ret->fhhGeneticPos = atof(row[14]);
ret->shrspName = row[15];
ret->shrspChr = row[16];
ret->shrspGeneticPos = atof(row[17]);
ret->rhName = row[18];
ret->rhChr = row[19];
ret->rhGeneticPos = atof(row[20]);
ret->RHLOD = atof(row[21]);
ret->GeneName = row[22];
ret->GeneID = row[23];
ret->clone = row[24];
}

struct stsInfoRat *stsInfoRatLoad(char **row)
/* Load a stsInfoRat from row fetched with select * from stsInfoRat
 * from database.  Dispose of this with stsInfoRatFree(). */
{
struct stsInfoRat *ret;

AllocVar(ret);
ret->identNo = sqlUnsigned(row[0]);
ret->name = cloneString(row[1]);
ret->RGDId = sqlUnsigned(row[2]);
ret->RGDName = cloneString(row[3]);
ret->UiStsId = sqlUnsigned(row[4]);
ret->nameCount = sqlUnsigned(row[5]);
ret->alias = cloneString(row[6]);
ret->primer1 = cloneString(row[7]);
ret->primer2 = cloneString(row[8]);
ret->distance = cloneString(row[9]);
ret->sequence = sqlUnsigned(row[10]);
ret->organis = cloneString(row[11]);
ret->fhhName = cloneString(row[12]);
ret->fhhChr = cloneString(row[13]);
ret->fhhGeneticPos = atof(row[14]);
ret->shrspName = cloneString(row[15]);
ret->shrspChr = cloneString(row[16]);
ret->shrspGeneticPos = atof(row[17]);
ret->rhName = cloneString(row[18]);
ret->rhChr = cloneString(row[19]);
ret->rhGeneticPos = atof(row[20]);
ret->RHLOD = atof(row[21]);
ret->GeneName = cloneString(row[22]);
ret->GeneID = cloneString(row[23]);
ret->clone = cloneString(row[24]);
return ret;
}

struct stsInfoRat *stsInfoRatLoadAll(char *fileName) 
/* Load all stsInfoRat from a tab-separated file.
 * Dispose of this with stsInfoRatFreeList(). */
{
struct stsInfoRat *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[25];

while (lineFileRow(lf, row))
    {
    el = stsInfoRatLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct stsInfoRat *stsInfoRatCommaIn(char **pS, struct stsInfoRat *ret)
/* Create a stsInfoRat out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new stsInfoRat */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->identNo = sqlUnsignedComma(&s);
ret->name = sqlStringComma(&s);
ret->RGDId = sqlUnsignedComma(&s);
ret->RGDName = sqlStringComma(&s);
ret->UiStsId = sqlUnsignedComma(&s);
ret->nameCount = sqlUnsignedComma(&s);
ret->alias = sqlStringComma(&s);
ret->primer1 = sqlStringComma(&s);
ret->primer2 = sqlStringComma(&s);
ret->distance = sqlStringComma(&s);
ret->sequence = sqlUnsignedComma(&s);
ret->organis = sqlStringComma(&s);
ret->fhhName = sqlStringComma(&s);
ret->fhhChr = sqlStringComma(&s);
ret->fhhGeneticPos = sqlFloatComma(&s);
ret->shrspName = sqlStringComma(&s);
ret->shrspChr = sqlStringComma(&s);
ret->shrspGeneticPos = sqlFloatComma(&s);
ret->rhName = sqlStringComma(&s);
ret->rhChr = sqlStringComma(&s);
ret->rhGeneticPos = sqlFloatComma(&s);
ret->RHLOD = sqlFloatComma(&s);
ret->GeneName = sqlStringComma(&s);
ret->GeneID = sqlStringComma(&s);
ret->clone = sqlStringComma(&s);
*pS = s;
return ret;
}

void stsInfoRatFree(struct stsInfoRat **pEl)
/* Free a single dynamically allocated stsInfoRat such as created
 * with stsInfoRatLoad(). */
{
struct stsInfoRat *el;

if ((el = *pEl) == NULL) return;
freeMem(el->name);
freeMem(el->RGDName);
freeMem(el->alias);
freeMem(el->primer1);
freeMem(el->primer2);
freeMem(el->distance);
freeMem(el->organis);
freeMem(el->fhhName);
freeMem(el->fhhChr);
freeMem(el->shrspName);
freeMem(el->shrspChr);
freeMem(el->rhName);
freeMem(el->rhChr);
freeMem(el->GeneName);
freeMem(el->GeneID);
freeMem(el->clone);
freez(pEl);
}

void stsInfoRatFreeList(struct stsInfoRat **pList)
/* Free a list of dynamically allocated stsInfoRat's */
{
struct stsInfoRat *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    stsInfoRatFree(&el);
    }
*pList = NULL;
}

void stsInfoRatOutput(struct stsInfoRat *el, FILE *f, char sep, char lastSep) 
/* Print out stsInfoRat.  Separate fields with sep. Follow last field with lastSep. */
{
fprintf(f, "%u", el->identNo);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->name);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%u", el->RGDId);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->RGDName);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%u", el->UiStsId);
fputc(sep,f);
fprintf(f, "%u", el->nameCount);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->alias);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->primer1);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->primer2);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->distance);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%u", el->sequence);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->organis);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->fhhName);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->fhhChr);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%f", el->fhhGeneticPos);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->shrspName);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->shrspChr);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%f", el->shrspGeneticPos);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->rhName);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->rhChr);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%f", el->rhGeneticPos);
fputc(sep,f);
fprintf(f, "%f", el->RHLOD);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->GeneName);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->GeneID);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->clone);
if (sep == ',') fputc('"',f);
fputc(lastSep,f);
}

/* -------------------------------- End autoSql Generated Code -------------------------------- */

