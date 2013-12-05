/* lowelabTIGROperonScore.c was originally generated by the autoSql program, which also 
 * generated lowelabTIGROperonScore.h and lowelabTIGROperonScore.sql.  This module links the database and
 * the RAM representation of objects. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "lowelabTIGROperonScore.h"

static char const rcsid[] = "$Id: lowelabTIGROperonScore.c,v 1.1 2007/09/18 10:26:42 pchan Exp $";

void lowelabTIGROperonScoreStaticLoad(char **row, struct lowelabTIGROperonScore *ret)
/* Load a row from lowelabTIGROperonScore table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->name = row[0];
ret->gene1 = row[1];
ret->gene2 = row[2];
ret->confidence = sqlSigned(row[3]);
ret->ortholog = sqlSigned(row[4]);
ret->ortholog_link = row[5];
}

struct lowelabTIGROperonScore *lowelabTIGROperonScoreLoad(char **row)
/* Load a lowelabTIGROperonScore from row fetched with select * from lowelabTIGROperonScore
 * from database.  Dispose of this with lowelabTIGROperonScoreFree(). */
{
struct lowelabTIGROperonScore *ret;

AllocVar(ret);
ret->name = cloneString(row[0]);
ret->gene1 = cloneString(row[1]);
ret->gene2 = cloneString(row[2]);
ret->confidence = sqlSigned(row[3]);
ret->ortholog = sqlSigned(row[4]);
ret->ortholog_link = cloneString(row[5]);
return ret;
}

struct lowelabTIGROperonScore *lowelabTIGROperonScoreLoadAll(char *fileName) 
/* Load all lowelabTIGROperonScore from a whitespace-separated file.
 * Dispose of this with lowelabTIGROperonScoreFreeList(). */
{
struct lowelabTIGROperonScore *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[6];

while (lineFileRow(lf, row))
    {
    el = lowelabTIGROperonScoreLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct lowelabTIGROperonScore *lowelabTIGROperonScoreLoadAllByChar(char *fileName, char chopper) 
/* Load all lowelabTIGROperonScore from a chopper separated file.
 * Dispose of this with lowelabTIGROperonScoreFreeList(). */
{
struct lowelabTIGROperonScore *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[6];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = lowelabTIGROperonScoreLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct lowelabTIGROperonScore *lowelabTIGROperonScoreCommaIn(char **pS, struct lowelabTIGROperonScore *ret)
/* Create a lowelabTIGROperonScore out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new lowelabTIGROperonScore */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->name = sqlStringComma(&s);
ret->gene1 = sqlStringComma(&s);
ret->gene2 = sqlStringComma(&s);
ret->confidence = sqlSignedComma(&s);
ret->ortholog = sqlSignedComma(&s);
ret->ortholog_link = sqlStringComma(&s);
*pS = s;
return ret;
}

void lowelabTIGROperonScoreFree(struct lowelabTIGROperonScore **pEl)
/* Free a single dynamically allocated lowelabTIGROperonScore such as created
 * with lowelabTIGROperonScoreLoad(). */
{
struct lowelabTIGROperonScore *el;

if ((el = *pEl) == NULL) return;
freeMem(el->name);
freeMem(el->gene1);
freeMem(el->gene2);
freeMem(el->ortholog_link);
freez(pEl);
}

void lowelabTIGROperonScoreFreeList(struct lowelabTIGROperonScore **pList)
/* Free a list of dynamically allocated lowelabTIGROperonScore's */
{
struct lowelabTIGROperonScore *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    lowelabTIGROperonScoreFree(&el);
    }
*pList = NULL;
}

void lowelabTIGROperonScoreOutput(struct lowelabTIGROperonScore *el, FILE *f, char sep, char lastSep) 
/* Print out lowelabTIGROperonScore.  Separate fields with sep. Follow last field with lastSep. */
{
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->name);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->gene1);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->gene2);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%d", el->confidence);
fputc(sep,f);
fprintf(f, "%d", el->ortholog);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->ortholog_link);
if (sep == ',') fputc('"',f);
fputc(lastSep,f);
}

/* -------------------------------- End autoSql Generated Code -------------------------------- */

