/* gwasCatalog.c was originally generated by the autoSql program, which also 
 * generated gwasCatalog.h and gwasCatalog.sql.  This module links the database and
 * the RAM representation of objects. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "gwasCatalog.h"

static char const rcsid[] = "$Id: gwasCatalog.c,v 1.1 2010/01/19 22:57:12 angie Exp $";

/* definitions for cnv column */
static char *values_cnv[] = {"Y", "N", NULL};
static struct hash *valhash_cnv = NULL;

void gwasCatalogStaticLoad(char **row, struct gwasCatalog *ret)
/* Load a row from gwasCatalog table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->chrom = row[0];
ret->chromStart = sqlUnsigned(row[1]);
ret->chromEnd = sqlUnsigned(row[2]);
ret->name = row[3];
ret->pubMedID = sqlUnsigned(row[4]);
ret->author = row[5];
ret->pubDate = row[6];
ret->journal = row[7];
ret->title = row[8];
ret->trait = row[9];
ret->initSample = row[10];
ret->replSample = row[11];
ret->region = row[12];
ret->genes = row[13];
ret->riskAllele = row[14];
ret->riskAlFreq = row[15];
ret->pValue = row[16];
ret->pValueDesc = row[17];
ret->orOrBeta = row[18];
ret->ci95 = row[19];
ret->platform = row[20];
ret->cnv = sqlEnumParse(row[21], values_cnv, &valhash_cnv);
}

struct gwasCatalog *gwasCatalogLoad(char **row)
/* Load a gwasCatalog from row fetched with select * from gwasCatalog
 * from database.  Dispose of this with gwasCatalogFree(). */
{
struct gwasCatalog *ret;

AllocVar(ret);
ret->chrom = cloneString(row[0]);
ret->chromStart = sqlUnsigned(row[1]);
ret->chromEnd = sqlUnsigned(row[2]);
ret->name = cloneString(row[3]);
ret->pubMedID = sqlUnsigned(row[4]);
ret->author = cloneString(row[5]);
ret->pubDate = cloneString(row[6]);
ret->journal = cloneString(row[7]);
ret->title = cloneString(row[8]);
ret->trait = cloneString(row[9]);
ret->initSample = cloneString(row[10]);
ret->replSample = cloneString(row[11]);
ret->region = cloneString(row[12]);
ret->genes = cloneString(row[13]);
ret->riskAllele = cloneString(row[14]);
ret->riskAlFreq = cloneString(row[15]);
ret->pValue = cloneString(row[16]);
ret->pValueDesc = cloneString(row[17]);
ret->orOrBeta = cloneString(row[18]);
ret->ci95 = cloneString(row[19]);
ret->platform = cloneString(row[20]);
ret->cnv = sqlEnumParse(row[21], values_cnv, &valhash_cnv);
return ret;
}

struct gwasCatalog *gwasCatalogLoadAll(char *fileName) 
/* Load all gwasCatalog from a whitespace-separated file.
 * Dispose of this with gwasCatalogFreeList(). */
{
struct gwasCatalog *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[22];

while (lineFileRow(lf, row))
    {
    el = gwasCatalogLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct gwasCatalog *gwasCatalogLoadAllByChar(char *fileName, char chopper) 
/* Load all gwasCatalog from a chopper separated file.
 * Dispose of this with gwasCatalogFreeList(). */
{
struct gwasCatalog *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[22];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = gwasCatalogLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct gwasCatalog *gwasCatalogCommaIn(char **pS, struct gwasCatalog *ret)
/* Create a gwasCatalog out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new gwasCatalog */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->chrom = sqlStringComma(&s);
ret->chromStart = sqlUnsignedComma(&s);
ret->chromEnd = sqlUnsignedComma(&s);
ret->name = sqlStringComma(&s);
ret->pubMedID = sqlUnsignedComma(&s);
ret->author = sqlStringComma(&s);
ret->pubDate = sqlStringComma(&s);
ret->journal = sqlStringComma(&s);
ret->title = sqlStringComma(&s);
ret->trait = sqlStringComma(&s);
ret->initSample = sqlStringComma(&s);
ret->replSample = sqlStringComma(&s);
ret->region = sqlStringComma(&s);
ret->genes = sqlStringComma(&s);
ret->riskAllele = sqlStringComma(&s);
ret->riskAlFreq = sqlStringComma(&s);
ret->pValue = sqlStringComma(&s);
ret->pValueDesc = sqlStringComma(&s);
ret->orOrBeta = sqlStringComma(&s);
ret->ci95 = sqlStringComma(&s);
ret->platform = sqlStringComma(&s);
ret->cnv = sqlEnumComma(&s, values_cnv, &valhash_cnv);
*pS = s;
return ret;
}

void gwasCatalogFree(struct gwasCatalog **pEl)
/* Free a single dynamically allocated gwasCatalog such as created
 * with gwasCatalogLoad(). */
{
struct gwasCatalog *el;

if ((el = *pEl) == NULL) return;
freeMem(el->chrom);
freeMem(el->name);
freeMem(el->author);
freeMem(el->pubDate);
freeMem(el->journal);
freeMem(el->title);
freeMem(el->trait);
freeMem(el->initSample);
freeMem(el->replSample);
freeMem(el->region);
freeMem(el->genes);
freeMem(el->riskAllele);
freeMem(el->riskAlFreq);
freeMem(el->pValue);
freeMem(el->pValueDesc);
freeMem(el->orOrBeta);
freeMem(el->ci95);
freeMem(el->platform);
freez(pEl);
}

void gwasCatalogFreeList(struct gwasCatalog **pList)
/* Free a list of dynamically allocated gwasCatalog's */
{
struct gwasCatalog *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    gwasCatalogFree(&el);
    }
*pList = NULL;
}

void gwasCatalogOutput(struct gwasCatalog *el, FILE *f, char sep, char lastSep) 
/* Print out gwasCatalog.  Separate fields with sep. Follow last field with lastSep. */
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
fprintf(f, "%u", el->pubMedID);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->author);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->pubDate);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->journal);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->title);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->trait);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->initSample);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->replSample);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->region);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->genes);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->riskAllele);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->riskAlFreq);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->pValue);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->pValueDesc);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->orOrBeta);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->ci95);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->platform);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
sqlEnumPrint(f, el->cnv, values_cnv);
if (sep == ',') fputc('"',f);
fputc(lastSep,f);
}

/* -------------------------------- End autoSql Generated Code -------------------------------- */

