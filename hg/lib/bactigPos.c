/* bactigPos.c was originally generated by the autoSql program, which also 
 * generated bactigPos.h and bactigPos.sql.  This module links the database and
 * the RAM representation of objects. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "bactigPos.h"

static char const rcsid[] = "$Id: bactigPos.c,v 1.3 2005/04/11 08:13:43 markd Exp $";

void bactigPosStaticLoad(char **row, struct bactigPos *ret)
/* Load a row from bactigPos table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{
ret->chrom = row[0];
ret->chromStart = sqlUnsigned(row[1]);
ret->chromEnd = sqlUnsigned(row[2]);
ret->name = row[3];
ret->startContig = row[4];
ret->endContig = row[5];
}

struct bactigPos *bactigPosLoad(char **row)
/* Load a bactigPos from row fetched with select * from bactigPos
 * from database.  Dispose of this with bactigPosFree(). */
{
struct bactigPos *ret;

AllocVar(ret);
ret->chrom = cloneString(row[0]);
ret->chromStart = sqlUnsigned(row[1]);
ret->chromEnd = sqlUnsigned(row[2]);
ret->name = cloneString(row[3]);
ret->startContig = cloneString(row[4]);
ret->endContig = cloneString(row[5]);
return ret;
}

struct bactigPos *bactigPosLoadAll(char *fileName) 
/* Load all bactigPos from a tab-separated file.
 * Dispose of this with bactigPosFreeList(). */
{
struct bactigPos *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[6];

while (lineFileRow(lf, row))
    {
    el = bactigPosLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct bactigPos *bactigPosCommaIn(char **pS, struct bactigPos *ret)
/* Create a bactigPos out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new bactigPos */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->chrom = sqlStringComma(&s);
ret->chromStart = sqlUnsignedComma(&s);
ret->chromEnd = sqlUnsignedComma(&s);
ret->name = sqlStringComma(&s);
ret->startContig = sqlStringComma(&s);
ret->endContig = sqlStringComma(&s);
*pS = s;
return ret;
}

void bactigPosFree(struct bactigPos **pEl)
/* Free a single dynamically allocated bactigPos such as created
 * with bactigPosLoad(). */
{
struct bactigPos *el;

if ((el = *pEl) == NULL) return;
freeMem(el->chrom);
freeMem(el->name);
freeMem(el->startContig);
freeMem(el->endContig);
freez(pEl);
}

void bactigPosFreeList(struct bactigPos **pList)
/* Free a list of dynamically allocated bactigPos's */
{
struct bactigPos *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    bactigPosFree(&el);
    }
*pList = NULL;
}

void bactigPosOutput(struct bactigPos *el, FILE *f, char sep, char lastSep) 
/* Print out bactigPos.  Separate fields with sep. Follow last field with lastSep. */
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
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->startContig);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->endContig);
if (sep == ',') fputc('"',f);
fputc(lastSep,f);
}

/* -------------------------------- End autoSql Generated Code -------------------------------- */

