/* tfbsCons.c was originally generated by the autoSql program, which also 
 * generated tfbsCons.h and tfbsCons.sql.  This module links the database and
 * the RAM representation of objects. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "tfbsCons.h"

static char const rcsid[] = "$Id: tfbsCons.c,v 1.4 2005/04/13 06:25:58 markd Exp $";

void tfbsConsStaticLoad(char **row, struct tfbsCons *ret)
/* Load a row from tfbsCons table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->chrom = row[0];
ret->chromStart = sqlUnsigned(row[1]);
ret->chromEnd = sqlUnsigned(row[2]);
ret->name = row[3];
ret->score = sqlUnsigned(row[4]);
strcpy(ret->strand, row[5]);
strcpy(ret->species, row[6]);
strcpy(ret->factor, row[7]);
strcpy(ret->id, row[8]);
}

struct tfbsCons *tfbsConsLoad(char **row)
/* Load a tfbsCons from row fetched with select * from tfbsCons
 * from database.  Dispose of this with tfbsConsFree(). */
{
struct tfbsCons *ret;

AllocVar(ret);
ret->chrom = cloneString(row[0]);
ret->chromStart = sqlUnsigned(row[1]);
ret->chromEnd = sqlUnsigned(row[2]);
ret->name = cloneString(row[3]);
ret->score = sqlUnsigned(row[4]);
strcpy(ret->strand, row[5]);
strcpy(ret->species, row[6]);
strcpy(ret->factor, row[7]);
strcpy(ret->id, row[8]);
return ret;
}

struct tfbsCons *tfbsConsLoadAll(char *fileName) 
/* Load all tfbsCons from a whitespace-separated file.
 * Dispose of this with tfbsConsFreeList(). */
{
struct tfbsCons *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[9];

while (lineFileRow(lf, row))
    {
    el = tfbsConsLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct tfbsCons *tfbsConsLoadAllByChar(char *fileName, char chopper) 
/* Load all tfbsCons from a chopper separated file.
 * Dispose of this with tfbsConsFreeList(). */
{
struct tfbsCons *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[9];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = tfbsConsLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct tfbsCons *tfbsConsLoadByQuery(struct sqlConnection *conn, char *query)
/* Load all tfbsCons from table that satisfy the query given.  
 * Where query is of the form 'select * from example where something=something'
 * or 'select example.* from example, anotherTable where example.something = 
 * anotherTable.something'.
 * Dispose of this with tfbsConsFreeList(). */
{
struct tfbsCons *list = NULL, *el;
struct sqlResult *sr;
char **row;

sr = sqlGetResult(conn, query);
while ((row = sqlNextRow(sr)) != NULL)
    {
    el = tfbsConsLoad(row);
    slAddHead(&list, el);
    }
slReverse(&list);
sqlFreeResult(&sr);
return list;
}

void tfbsConsSaveToDb(struct sqlConnection *conn, struct tfbsCons *el, char *tableName, int updateSize)
/* Save tfbsCons as a row to the table specified by tableName. 
 * As blob fields may be arbitrary size updateSize specifies the approx size
 * of a string that would contain the entire query. Arrays of native types are
 * converted to comma separated strings and loaded as such, User defined types are
 * inserted as NULL. Note that strings must be escaped to allow insertion into the database.
 * For example "autosql's features include" --> "autosql\'s features include" 
 * If worried about this use tfbsConsSaveToDbEscaped() */
{
struct dyString *update = newDyString(updateSize);
dyStringPrintf(update, "insert into %s values ( '%s',%u,%u,'%s',%u,'%s','%s','%s','%s')", 
	tableName,  el->chrom,  el->chromStart,  el->chromEnd,  el->name,  el->score,  el->strand,  el->species,  el->factor,  el->id);
sqlUpdate(conn, update->string);
freeDyString(&update);
}

void tfbsConsSaveToDbEscaped(struct sqlConnection *conn, struct tfbsCons *el, char *tableName, int updateSize)
/* Save tfbsCons as a row to the table specified by tableName. 
 * As blob fields may be arbitrary size updateSize specifies the approx size.
 * of a string that would contain the entire query. Automatically 
 * escapes all simple strings (not arrays of string) but may be slower than tfbsConsSaveToDb().
 * For example automatically copies and converts: 
 * "autosql's features include" --> "autosql\'s features include" 
 * before inserting into database. */ 
{
struct dyString *update = newDyString(updateSize);
char  *chrom, *name, *strand, *species, *factor, *id;
chrom = sqlEscapeString(el->chrom);
name = sqlEscapeString(el->name);
strand = sqlEscapeString(el->strand);
species = sqlEscapeString(el->species);
factor = sqlEscapeString(el->factor);
id = sqlEscapeString(el->id);

dyStringPrintf(update, "insert into %s values ( '%s',%u,%u,'%s',%u,'%s','%s','%s','%s')", 
	tableName,  chrom, el->chromStart , el->chromEnd ,  name, el->score ,  strand,  species,  factor,  id);
sqlUpdate(conn, update->string);
freeDyString(&update);
freez(&chrom);
freez(&name);
freez(&strand);
freez(&species);
freez(&factor);
freez(&id);
}

struct tfbsCons *tfbsConsCommaIn(char **pS, struct tfbsCons *ret)
/* Create a tfbsCons out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new tfbsCons */
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
sqlFixedStringComma(&s, ret->species, sizeof(ret->species));
sqlFixedStringComma(&s, ret->factor, sizeof(ret->factor));
sqlFixedStringComma(&s, ret->id, sizeof(ret->id));
*pS = s;
return ret;
}

void tfbsConsFree(struct tfbsCons **pEl)
/* Free a single dynamically allocated tfbsCons such as created
 * with tfbsConsLoad(). */
{
struct tfbsCons *el;

if ((el = *pEl) == NULL) return;
freeMem(el->chrom);
freeMem(el->name);
freez(pEl);
}

void tfbsConsFreeList(struct tfbsCons **pList)
/* Free a list of dynamically allocated tfbsCons's */
{
struct tfbsCons *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    tfbsConsFree(&el);
    }
*pList = NULL;
}

void tfbsConsOutput(struct tfbsCons *el, FILE *f, char sep, char lastSep) 
/* Print out tfbsCons.  Separate fields with sep. Follow last field with lastSep. */
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
fprintf(f, "%s", el->species);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->factor);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->id);
if (sep == ',') fputc('"',f);
fputc(lastSep,f);
}

/* -------------------------------- End autoSql Generated Code -------------------------------- */

