/* blatServers.c was originally generated by the autoSql program, which also 
 * generated blatServers.h and blatServers.sql.  This module links the database and
 * the RAM representation of objects. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "blatServers.h"

static char const rcsid[] = "$Id: blatServers.c,v 1.3 2005/04/13 06:25:50 markd Exp $";

void blatServersStaticLoad(char **row, struct blatServers *ret)
/* Load a row from blatServers table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->db = row[0];
ret->host = row[1];
ret->port = sqlSigned(row[2]);
ret->isTrans = sqlSigned(row[3]);
}

struct blatServers *blatServersLoad(char **row)
/* Load a blatServers from row fetched with select * from blatServers
 * from database.  Dispose of this with blatServersFree(). */
{
struct blatServers *ret;

AllocVar(ret);
ret->db = cloneString(row[0]);
ret->host = cloneString(row[1]);
ret->port = sqlSigned(row[2]);
ret->isTrans = sqlSigned(row[3]);
return ret;
}

struct blatServers *blatServersLoadAll(char *fileName) 
/* Load all blatServers from a tab-separated file.
 * Dispose of this with blatServersFreeList(). */
{
struct blatServers *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[4];

while (lineFileRow(lf, row))
    {
    el = blatServersLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct blatServers *blatServersLoadWhere(struct sqlConnection *conn, char *table, char *where)
/* Load all blatServers from table that satisfy where clause. The
 * where clause may be NULL in which case whole table is loaded
 * Dispose of this with blatServersFreeList(). */
{
struct blatServers *list = NULL, *el;
struct dyString *query = dyStringNew(256);
struct sqlResult *sr;
char **row;

dyStringPrintf(query, "select * from %s", table);
if (where != NULL)
    dyStringPrintf(query, " where %s", where);
sr = sqlGetResult(conn, query->string);
while ((row = sqlNextRow(sr)) != NULL)
    {
    el = blatServersLoad(row);
    slAddHead(&list, el);
    }
slReverse(&list);
sqlFreeResult(&sr);
dyStringFree(&query);
return list;
}

struct blatServers *blatServersCommaIn(char **pS, struct blatServers *ret)
/* Create a blatServers out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new blatServers */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->db = sqlStringComma(&s);
ret->host = sqlStringComma(&s);
ret->port = sqlSignedComma(&s);
ret->isTrans = sqlSignedComma(&s);
*pS = s;
return ret;
}

void blatServersFree(struct blatServers **pEl)
/* Free a single dynamically allocated blatServers such as created
 * with blatServersLoad(). */
{
struct blatServers *el;

if ((el = *pEl) == NULL) return;
freeMem(el->db);
freeMem(el->host);
freez(pEl);
}

void blatServersFreeList(struct blatServers **pList)
/* Free a list of dynamically allocated blatServers's */
{
struct blatServers *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    blatServersFree(&el);
    }
*pList = NULL;
}

void blatServersOutput(struct blatServers *el, FILE *f, char sep, char lastSep) 
/* Print out blatServers.  Separate fields with sep. Follow last field with lastSep. */
{
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->db);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->host);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%d", el->port);
fputc(sep,f);
fprintf(f, "%d", el->isTrans);
fputc(lastSep,f);
}

