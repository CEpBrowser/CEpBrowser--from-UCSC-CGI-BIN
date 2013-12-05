/* tilingPath.c was originally generated by the autoSql program, which also 
 * generated tilingPath.h and tilingPath.sql.  This module links the database and
 * the RAM representation of objects. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "tilingPath.h"

static char const rcsid[] = "$Id: tilingPath.c,v 1.3 2005/04/13 06:25:58 markd Exp $";

void tilingPathStaticLoad(char **row, struct tilingPath *ret)
/* Load a row from tilingPath table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->chrom = row[0];
ret->accession = row[1];
ret->clone = row[2];
ret->contig = row[3];
ret->chromIx = sqlSigned(row[4]);
}

struct tilingPath *tilingPathLoad(char **row)
/* Load a tilingPath from row fetched with select * from tilingPath
 * from database.  Dispose of this with tilingPathFree(). */
{
struct tilingPath *ret;

AllocVar(ret);
ret->chrom = cloneString(row[0]);
ret->accession = cloneString(row[1]);
ret->clone = cloneString(row[2]);
ret->contig = cloneString(row[3]);
ret->chromIx = sqlSigned(row[4]);
return ret;
}

struct tilingPath *tilingPathLoadAll(char *fileName) 
/* Load all tilingPath from a tab-separated file.
 * Dispose of this with tilingPathFreeList(). */
{
struct tilingPath *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[5];

while (lineFileRow(lf, row))
    {
    el = tilingPathLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct tilingPath *tilingPathLoadWhere(struct sqlConnection *conn, char *table, char *where)
/* Load all tilingPath from table that satisfy where clause. The
 * where clause may be NULL in which case whole table is loaded
 * Dispose of this with tilingPathFreeList(). */
{
struct tilingPath *list = NULL, *el;
struct dyString *query = dyStringNew(256);
struct sqlResult *sr;
char **row;

dyStringPrintf(query, "select * from %s", table);
if (where != NULL)
    dyStringPrintf(query, " where %s", where);
sr = sqlGetResult(conn, query->string);
while ((row = sqlNextRow(sr)) != NULL)
    {
    el = tilingPathLoad(row);
    slAddHead(&list, el);
    }
slReverse(&list);
sqlFreeResult(&sr);
dyStringFree(&query);
return list;
}

struct tilingPath *tilingPathCommaIn(char **pS, struct tilingPath *ret)
/* Create a tilingPath out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new tilingPath */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->chrom = sqlStringComma(&s);
ret->accession = sqlStringComma(&s);
ret->clone = sqlStringComma(&s);
ret->contig = sqlStringComma(&s);
ret->chromIx = sqlSignedComma(&s);
*pS = s;
return ret;
}

void tilingPathFree(struct tilingPath **pEl)
/* Free a single dynamically allocated tilingPath such as created
 * with tilingPathLoad(). */
{
struct tilingPath *el;

if ((el = *pEl) == NULL) return;
freeMem(el->chrom);
freeMem(el->accession);
freeMem(el->clone);
freeMem(el->contig);
freez(pEl);
}

void tilingPathFreeList(struct tilingPath **pList)
/* Free a list of dynamically allocated tilingPath's */
{
struct tilingPath *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    tilingPathFree(&el);
    }
*pList = NULL;
}

void tilingPathOutput(struct tilingPath *el, FILE *f, char sep, char lastSep) 
/* Print out tilingPath.  Separate fields with sep. Follow last field with lastSep. */
{
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->chrom);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->accession);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->clone);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->contig);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%d", el->chromIx);
fputc(lastSep,f);
}

