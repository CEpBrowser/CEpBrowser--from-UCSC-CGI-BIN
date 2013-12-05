/* cnpSebat.c was originally generated by the autoSql program, which also 
 * generated cnpSebat.h and cnpSebat.sql.  This module links the database and
 * the RAM representation of objects. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "cnpSebat.h"

static char const rcsid[] = "$Id: cnpSebat.c,v 1.1 2005/07/10 02:02:54 daryl Exp $";

void cnpSebatStaticLoad(char **row, struct cnpSebat *ret)
/* Load a row from cnpSebat table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->chrom = row[0];
ret->chromStart = sqlUnsigned(row[1]);
ret->chromEnd = sqlUnsigned(row[2]);
ret->name = row[3];
ret->probes = sqlUnsigned(row[4]);
ret->individuals = sqlUnsigned(row[5]);
}

struct cnpSebat *cnpSebatLoad(char **row)
/* Load a cnpSebat from row fetched with select * from cnpSebat
 * from database.  Dispose of this with cnpSebatFree(). */
{
struct cnpSebat *ret;

AllocVar(ret);
ret->chrom = cloneString(row[0]);
ret->chromStart = sqlUnsigned(row[1]);
ret->chromEnd = sqlUnsigned(row[2]);
ret->name = cloneString(row[3]);
ret->probes = sqlUnsigned(row[4]);
ret->individuals = sqlUnsigned(row[5]);
return ret;
}

struct cnpSebat *cnpSebatLoadAll(char *fileName) 
/* Load all cnpSebat from a whitespace-separated file.
 * Dispose of this with cnpSebatFreeList(). */
{
struct cnpSebat *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[6];

while (lineFileRow(lf, row))
    {
    el = cnpSebatLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct cnpSebat *cnpSebatLoadAllByChar(char *fileName, char chopper) 
/* Load all cnpSebat from a chopper separated file.
 * Dispose of this with cnpSebatFreeList(). */
{
struct cnpSebat *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[6];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = cnpSebatLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct cnpSebat *cnpSebatLoadByQuery(struct sqlConnection *conn, char *query)
/* Load all cnpSebat from table that satisfy the query given.  
 * Where query is of the form 'select * from example where something=something'
 * or 'select example.* from example, anotherTable where example.something = 
 * anotherTable.something'.
 * Dispose of this with cnpSebatFreeList(). */
{
struct cnpSebat *list = NULL, *el;
struct sqlResult *sr;
char **row;

sr = sqlGetResult(conn, query);
while ((row = sqlNextRow(sr)) != NULL)
    {
    el = cnpSebatLoad(row);
    slAddHead(&list, el);
    }
slReverse(&list);
sqlFreeResult(&sr);
return list;
}

void cnpSebatSaveToDb(struct sqlConnection *conn, struct cnpSebat *el, char *tableName, int updateSize)
/* Save cnpSebat as a row to the table specified by tableName. 
 * As blob fields may be arbitrary size updateSize specifies the approx size
 * of a string that would contain the entire query. Arrays of native types are
 * converted to comma separated strings and loaded as such, User defined types are
 * inserted as NULL. Note that strings must be escaped to allow insertion into the database.
 * For example "autosql's features include" --> "autosql\'s features include" 
 * If worried about this use cnpSebatSaveToDbEscaped() */
{
struct dyString *update = newDyString(updateSize);
dyStringPrintf(update, "insert into %s values ( '%s',%u,%u,'%s',%u,%u)", 
	tableName,  el->chrom,  el->chromStart,  el->chromEnd,  el->name,  el->probes,  el->individuals);
sqlUpdate(conn, update->string);
freeDyString(&update);
}

void cnpSebatSaveToDbEscaped(struct sqlConnection *conn, struct cnpSebat *el, char *tableName, int updateSize)
/* Save cnpSebat as a row to the table specified by tableName. 
 * As blob fields may be arbitrary size updateSize specifies the approx size.
 * of a string that would contain the entire query. Automatically 
 * escapes all simple strings (not arrays of string) but may be slower than cnpSebatSaveToDb().
 * For example automatically copies and converts: 
 * "autosql's features include" --> "autosql\'s features include" 
 * before inserting into database. */ 
{
struct dyString *update = newDyString(updateSize);
char  *chrom, *name;
chrom = sqlEscapeString(el->chrom);
name = sqlEscapeString(el->name);

dyStringPrintf(update, "insert into %s values ( '%s',%u,%u,'%s',%u,%u)", 
	tableName,  chrom, el->chromStart , el->chromEnd ,  name, el->probes , el->individuals );
sqlUpdate(conn, update->string);
freeDyString(&update);
freez(&chrom);
freez(&name);
}

struct cnpSebat *cnpSebatCommaIn(char **pS, struct cnpSebat *ret)
/* Create a cnpSebat out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new cnpSebat */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->chrom = sqlStringComma(&s);
ret->chromStart = sqlUnsignedComma(&s);
ret->chromEnd = sqlUnsignedComma(&s);
ret->name = sqlStringComma(&s);
ret->probes = sqlUnsignedComma(&s);
ret->individuals = sqlUnsignedComma(&s);
*pS = s;
return ret;
}

void cnpSebatFree(struct cnpSebat **pEl)
/* Free a single dynamically allocated cnpSebat such as created
 * with cnpSebatLoad(). */
{
struct cnpSebat *el;

if ((el = *pEl) == NULL) return;
freeMem(el->chrom);
freeMem(el->name);
freez(pEl);
}

void cnpSebatFreeList(struct cnpSebat **pList)
/* Free a list of dynamically allocated cnpSebat's */
{
struct cnpSebat *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    cnpSebatFree(&el);
    }
*pList = NULL;
}

void cnpSebatOutput(struct cnpSebat *el, FILE *f, char sep, char lastSep) 
/* Print out cnpSebat.  Separate fields with sep. Follow last field with lastSep. */
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
fprintf(f, "%u", el->probes);
fputc(sep,f);
fprintf(f, "%u", el->individuals);
fputc(lastSep,f);
}

/* -------------------------------- End autoSql Generated Code -------------------------------- */

