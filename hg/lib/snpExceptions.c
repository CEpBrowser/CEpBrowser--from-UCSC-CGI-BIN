/* snpExceptions.c was originally generated by the autoSql program, which also 
 * generated snpExceptions.h and snpExceptions.sql.  This module links the database and
 * the RAM representation of objects. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "snpExceptions.h"

static char const rcsid[] = "$Id: snpExceptions.c,v 1.1 2004/12/24 12:26:01 daryl Exp $";

void snpExceptionsStaticLoad(char **row, struct snpExceptions *ret)
/* Load a row from snpExceptions table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->exceptionId = sqlUnsigned(row[0]);
ret->query = row[1];
ret->num = sqlUnsigned(row[2]);
ret->description = row[3];
ret->resultPath = row[4];
}

struct snpExceptions *snpExceptionsLoad(char **row)
/* Load a snpExceptions from row fetched with select * from snpExceptions
 * from database.  Dispose of this with snpExceptionsFree(). */
{
struct snpExceptions *ret;

AllocVar(ret);
ret->exceptionId = sqlUnsigned(row[0]);
ret->query = cloneString(row[1]);
ret->num = sqlUnsigned(row[2]);
ret->description = cloneString(row[3]);
ret->resultPath = cloneString(row[4]);
return ret;
}

struct snpExceptions *snpExceptionsLoadAll(char *fileName) 
/* Load all snpExceptions from a whitespace-separated file.
 * Dispose of this with snpExceptionsFreeList(). */
{
struct snpExceptions *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[5];

while (lineFileRow(lf, row))
    {
    el = snpExceptionsLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct snpExceptions *snpExceptionsLoadAllByChar(char *fileName, char chopper) 
/* Load all snpExceptions from a chopper separated file.
 * Dispose of this with snpExceptionsFreeList(). */
{
struct snpExceptions *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[5];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = snpExceptionsLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct snpExceptions *snpExceptionsLoadByQuery(struct sqlConnection *conn, char *query)
/* Load all snpExceptions from table that satisfy the query given.  
 * Where query is of the form 'select * from example where something=something'
 * or 'select example.* from example, anotherTable where example.something = 
 * anotherTable.something'.
 * Dispose of this with snpExceptionsFreeList(). */
{
struct snpExceptions *list = NULL, *el;
struct sqlResult *sr;
char **row;

sr = sqlGetResult(conn, query);
while ((row = sqlNextRow(sr)) != NULL)
    {
    el = snpExceptionsLoad(row);
    slAddHead(&list, el);
    }
slReverse(&list);
sqlFreeResult(&sr);
return list;
}

void snpExceptionsSaveToDb(struct sqlConnection *conn, struct snpExceptions *el, char *tableName, int updateSize)
/* Save snpExceptions as a row to the table specified by tableName. 
 * As blob fields may be arbitrary size updateSize specifies the approx size
 * of a string that would contain the entire query. Arrays of native types are
 * converted to comma separated strings and loaded as such, User defined types are
 * inserted as NULL. Note that strings must be escaped to allow insertion into the database.
 * For example "autosql's features include" --> "autosql\'s features include" 
 * If worried about this use snpExceptionsSaveToDbEscaped() */
{
struct dyString *update = newDyString(updateSize);
dyStringPrintf(update, "insert into %s values ( %u,'%s',%u,'%s','%s')", 
	tableName,  el->exceptionId,  el->query,  el->num,  el->description,  el->resultPath);
sqlUpdate(conn, update->string);
freeDyString(&update);
}

void snpExceptionsSaveToDbEscaped(struct sqlConnection *conn, struct snpExceptions *el, char *tableName, int updateSize)
/* Save snpExceptions as a row to the table specified by tableName. 
 * As blob fields may be arbitrary size updateSize specifies the approx size.
 * of a string that would contain the entire query. Automatically 
 * escapes all simple strings (not arrays of string) but may be slower than snpExceptionsSaveToDb().
 * For example automatically copies and converts: 
 * "autosql's features include" --> "autosql\'s features include" 
 * before inserting into database. */ 
{
struct dyString *update = newDyString(updateSize);
char  *query, *description, *resultPath;
query = sqlEscapeString(el->query);
description = sqlEscapeString(el->description);
resultPath = sqlEscapeString(el->resultPath);

dyStringPrintf(update, "insert into %s values ( %u,'%s',%u,'%s','%s')", 
	tableName, el->exceptionId ,  query, el->num ,  description,  resultPath);
sqlUpdate(conn, update->string);
freeDyString(&update);
freez(&query);
freez(&description);
freez(&resultPath);
}

struct snpExceptions *snpExceptionsCommaIn(char **pS, struct snpExceptions *ret)
/* Create a snpExceptions out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new snpExceptions */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->exceptionId = sqlUnsignedComma(&s);
ret->query = sqlStringComma(&s);
ret->num = sqlUnsignedComma(&s);
ret->description = sqlStringComma(&s);
ret->resultPath = sqlStringComma(&s);
*pS = s;
return ret;
}

void snpExceptionsFree(struct snpExceptions **pEl)
/* Free a single dynamically allocated snpExceptions such as created
 * with snpExceptionsLoad(). */
{
struct snpExceptions *el;

if ((el = *pEl) == NULL) return;
freeMem(el->query);
freeMem(el->description);
freeMem(el->resultPath);
freez(pEl);
}

void snpExceptionsFreeList(struct snpExceptions **pList)
/* Free a list of dynamically allocated snpExceptions's */
{
struct snpExceptions *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    snpExceptionsFree(&el);
    }
*pList = NULL;
}

void snpExceptionsOutput(struct snpExceptions *el, FILE *f, char sep, char lastSep) 
/* Print out snpExceptions.  Separate fields with sep. Follow last field with lastSep. */
{
fprintf(f, "%u", el->exceptionId);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->query);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%u", el->num);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->description);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->resultPath);
if (sep == ',') fputc('"',f);
fputc(lastSep,f);
}

/* -------------------------------- End autoSql Generated Code -------------------------------- */

