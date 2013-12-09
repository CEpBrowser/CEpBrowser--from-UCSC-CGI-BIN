/* kg1ToKg2.c was originally generated by the autoSql program, which also 
 * generated kg1ToKg2.h and kg1ToKg2.sql.  This module links the database and
 * the RAM representation of objects. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "kg1ToKg2.h"

static char const rcsid[] = "$Id: kg1ToKg2.c,v 1.1 2007/03/27 05:20:50 kent Exp $";

void kg1ToKg2StaticLoad(char **row, struct kg1ToKg2 *ret)
/* Load a row from kg1ToKg2 table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->oldId = row[0];
ret->oldChrom = row[1];
ret->oldStart = sqlSigned(row[2]);
ret->oldEnd = sqlSigned(row[3]);
ret->newId = row[4];
ret->status = row[5];
ret->note = row[6];
}

struct kg1ToKg2 *kg1ToKg2Load(char **row)
/* Load a kg1ToKg2 from row fetched with select * from kg1ToKg2
 * from database.  Dispose of this with kg1ToKg2Free(). */
{
struct kg1ToKg2 *ret;

AllocVar(ret);
ret->oldId = cloneString(row[0]);
ret->oldChrom = cloneString(row[1]);
ret->oldStart = sqlSigned(row[2]);
ret->oldEnd = sqlSigned(row[3]);
ret->newId = cloneString(row[4]);
ret->status = cloneString(row[5]);
ret->note = cloneString(row[6]);
return ret;
}

struct kg1ToKg2 *kg1ToKg2LoadAll(char *fileName) 
/* Load all kg1ToKg2 from a whitespace-separated file.
 * Dispose of this with kg1ToKg2FreeList(). */
{
struct kg1ToKg2 *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[7];

while (lineFileRow(lf, row))
    {
    el = kg1ToKg2Load(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct kg1ToKg2 *kg1ToKg2LoadAllByChar(char *fileName, char chopper) 
/* Load all kg1ToKg2 from a chopper separated file.
 * Dispose of this with kg1ToKg2FreeList(). */
{
struct kg1ToKg2 *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[7];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = kg1ToKg2Load(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct kg1ToKg2 *kg1ToKg2CommaIn(char **pS, struct kg1ToKg2 *ret)
/* Create a kg1ToKg2 out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new kg1ToKg2 */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->oldId = sqlStringComma(&s);
ret->oldChrom = sqlStringComma(&s);
ret->oldStart = sqlSignedComma(&s);
ret->oldEnd = sqlSignedComma(&s);
ret->newId = sqlStringComma(&s);
ret->status = sqlStringComma(&s);
ret->note = sqlStringComma(&s);
*pS = s;
return ret;
}

void kg1ToKg2Free(struct kg1ToKg2 **pEl)
/* Free a single dynamically allocated kg1ToKg2 such as created
 * with kg1ToKg2Load(). */
{
struct kg1ToKg2 *el;

if ((el = *pEl) == NULL) return;
freeMem(el->oldId);
freeMem(el->oldChrom);
freeMem(el->newId);
freeMem(el->status);
freeMem(el->note);
freez(pEl);
}

void kg1ToKg2FreeList(struct kg1ToKg2 **pList)
/* Free a list of dynamically allocated kg1ToKg2's */
{
struct kg1ToKg2 *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    kg1ToKg2Free(&el);
    }
*pList = NULL;
}

void kg1ToKg2Output(struct kg1ToKg2 *el, FILE *f, char sep, char lastSep) 
/* Print out kg1ToKg2.  Separate fields with sep. Follow last field with lastSep. */
{
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->oldId);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->oldChrom);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%d", el->oldStart);
fputc(sep,f);
fprintf(f, "%d", el->oldEnd);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->newId);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->status);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->note);
if (sep == ',') fputc('"',f);
fputc(lastSep,f);
}

/* -------------------------------- End autoSql Generated Code -------------------------------- */

