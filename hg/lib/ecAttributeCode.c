/* ecAttributeCode.c was originally generated by the autoSql program, which also 
 * generated ecAttributeCode.h and ecAttributeCode.sql.  This module links the database and
 * the RAM representation of objects. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "ecAttributeCode.h"

static char const rcsid[] = "$Id: ecAttributeCode.c,v 1.1 2005/10/17 00:12:09 baertsch Exp $";

void ecAttributeCodeStaticLoad(char **row, struct ecAttributeCode *ret)
/* Load a row from ecAttributeCode table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

strcpy(ret->type, row[0]);
ret->description = row[1];
}

struct ecAttributeCode *ecAttributeCodeLoad(char **row)
/* Load a ecAttributeCode from row fetched with select * from ecAttributeCode
 * from database.  Dispose of this with ecAttributeCodeFree(). */
{
struct ecAttributeCode *ret;

AllocVar(ret);
strcpy(ret->type, row[0]);
ret->description = cloneString(row[1]);
return ret;
}

struct ecAttributeCode *ecAttributeCodeLoadAll(char *fileName) 
/* Load all ecAttributeCode from a whitespace-separated file.
 * Dispose of this with ecAttributeCodeFreeList(). */
{
struct ecAttributeCode *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[2];

while (lineFileRow(lf, row))
    {
    el = ecAttributeCodeLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct ecAttributeCode *ecAttributeCodeLoadAllByChar(char *fileName, char chopper) 
/* Load all ecAttributeCode from a chopper separated file.
 * Dispose of this with ecAttributeCodeFreeList(). */
{
struct ecAttributeCode *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[2];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = ecAttributeCodeLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct ecAttributeCode *ecAttributeCodeCommaIn(char **pS, struct ecAttributeCode *ret)
/* Create a ecAttributeCode out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new ecAttributeCode */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
sqlFixedStringComma(&s, ret->type, sizeof(ret->type));
ret->description = sqlStringComma(&s);
*pS = s;
return ret;
}

void ecAttributeCodeFree(struct ecAttributeCode **pEl)
/* Free a single dynamically allocated ecAttributeCode such as created
 * with ecAttributeCodeLoad(). */
{
struct ecAttributeCode *el;

if ((el = *pEl) == NULL) return;
freeMem(el->description);
freez(pEl);
}

void ecAttributeCodeFreeList(struct ecAttributeCode **pList)
/* Free a list of dynamically allocated ecAttributeCode's */
{
struct ecAttributeCode *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    ecAttributeCodeFree(&el);
    }
*pList = NULL;
}

void ecAttributeCodeOutput(struct ecAttributeCode *el, FILE *f, char sep, char lastSep) 
/* Print out ecAttributeCode.  Separate fields with sep. Follow last field with lastSep. */
{
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->type);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->description);
if (sep == ',') fputc('"',f);
fputc(lastSep,f);
}

/* -------------------------------- End autoSql Generated Code -------------------------------- */

