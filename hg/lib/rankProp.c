/* rankProp.c was originally generated by the autoSql program, which also 
 * generated rankProp.h and rankProp.sql.  This module links the database and
 * the RAM representation of objects. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "rankProp.h"

static char const rcsid[] = "$Id: rankProp.c,v 1.4 2004/12/23 18:37:53 markd Exp $";

void rankPropStaticLoad(char **row, struct rankProp *ret)
/* Load a row from rankProp table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->query = row[0];
ret->target = row[1];
ret->score = atof(row[2]);
}

struct rankProp *rankPropLoad(char **row)
/* Load a rankProp from row fetched with select * from rankProp
 * from database.  Dispose of this with rankPropFree(). */
{
struct rankProp *ret;

AllocVar(ret);
ret->query = cloneString(row[0]);
ret->target = cloneString(row[1]);
ret->score = atof(row[2]);
return ret;
}

struct rankProp *rankPropLoadAll(char *fileName) 
/* Load all rankProp from a whitespace-separated file.
 * Dispose of this with rankPropFreeList(). */
{
struct rankProp *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[3];

while (lineFileRow(lf, row))
    {
    el = rankPropLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct rankProp *rankPropLoadAllByChar(char *fileName, char chopper) 
/* Load all rankProp from a chopper separated file.
 * Dispose of this with rankPropFreeList(). */
{
struct rankProp *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[3];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = rankPropLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct rankProp *rankPropCommaIn(char **pS, struct rankProp *ret)
/* Create a rankProp out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new rankProp */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->query = sqlStringComma(&s);
ret->target = sqlStringComma(&s);
ret->score = sqlFloatComma(&s);
*pS = s;
return ret;
}

void rankPropFree(struct rankProp **pEl)
/* Free a single dynamically allocated rankProp such as created
 * with rankPropLoad(). */
{
struct rankProp *el;

if ((el = *pEl) == NULL) return;
freeMem(el->query);
freeMem(el->target);
freez(pEl);
}

void rankPropFreeList(struct rankProp **pList)
/* Free a list of dynamically allocated rankProp's */
{
struct rankProp *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    rankPropFree(&el);
    }
*pList = NULL;
}

void rankPropOutput(struct rankProp *el, FILE *f, char sep, char lastSep) 
/* Print out rankProp.  Separate fields with sep. Follow last field with lastSep. */
{
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->query);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->target);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%g", el->score);
fputc(lastSep,f);
}

/* -------------------------------- End autoSql Generated Code -------------------------------- */

