/* hugoMulti.c was originally generated by the autoSql program, which also 
 * generated hugoMulti.h and hugoMulti.sql.  This module links the database and the RAM 
 * representation of objects. */

#include "common.h"
#include "jksql.h"
#include "hugoMulti.h"

static char const rcsid[] = "$Id: hugoMulti.c,v 1.4 2006/04/29 16:45:46 angie Exp $";

void hugoMultiStaticLoad(char **row, struct hugoMulti *ret)
/* Load a row from hugoMulti table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->hgnc = sqlUnsigned(row[0]);
ret->symbol = row[1];
ret->name = row[2];
ret->map = row[3];
ret->omimId = row[4];
ret->pmId1 = sqlUnsigned(row[5]);
ret->pmId2 = sqlUnsigned(row[6]);
ret->refSeqAcc = row[7];
ret->aliases = row[8];
ret->locusLinkId = sqlUnsigned(row[9]);
ret->gdbId = row[10];
ret->swissProt = row[11];
}

struct hugoMulti *hugoMultiLoad(char **row)
/* Load a hugoMulti from row fetched with select * from hugoMulti
 * from database.  Dispose of this with hugoMultiFree(). */
{
struct hugoMulti *ret;

AllocVar(ret);
ret->hgnc = sqlUnsigned(row[0]);
ret->symbol = cloneString(row[1]);
ret->name = cloneString(row[2]);
ret->map = cloneString(row[3]);
ret->omimId = cloneString(row[4]);
ret->pmId1 = sqlUnsigned(row[5]);
ret->pmId2 = sqlUnsigned(row[6]);
ret->refSeqAcc = cloneString(row[7]);
ret->aliases = cloneString(row[8]);
ret->locusLinkId = sqlUnsigned(row[9]);
ret->gdbId = cloneString(row[10]);
ret->swissProt = cloneString(row[11]);
return ret;
}

struct hugoMulti *hugoMultiCommaIn(char **pS, struct hugoMulti *ret)
/* Create a hugoMulti out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new hugoMulti */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->hgnc = sqlUnsignedComma(&s);
ret->symbol = sqlStringComma(&s);
ret->name = sqlStringComma(&s);
ret->map = sqlStringComma(&s);
ret->omimId = sqlStringComma(&s);
ret->pmId1 = sqlUnsignedComma(&s);
ret->pmId2 = sqlUnsignedComma(&s);
ret->refSeqAcc = sqlStringComma(&s);
ret->aliases = sqlStringComma(&s);
ret->locusLinkId = sqlUnsignedComma(&s);
ret->gdbId = sqlStringComma(&s);
ret->swissProt = sqlStringComma(&s);
*pS = s;
return ret;
}

void hugoMultiFree(struct hugoMulti **pEl)
/* Free a single dynamically allocated hugoMulti such as created
 * with hugoMultiLoad(). */
{
struct hugoMulti *el;

if ((el = *pEl) == NULL) return;
freeMem(el->symbol);
freeMem(el->name);
freeMem(el->map);
freeMem(el->omimId);
freeMem(el->refSeqAcc);
freeMem(el->aliases);
freeMem(el->gdbId);
freeMem(el->swissProt);
freez(pEl);
}

void hugoMultiFreeList(struct hugoMulti **pList)
/* Free a list of dynamically allocated hugoMulti's */
{
struct hugoMulti *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    hugoMultiFree(&el);
    }
*pList = NULL;
}

void hugoMultiOutput(struct hugoMulti *el, FILE *f, char sep, char lastSep) 
/* Print out hugoMulti.  Separate fields with sep. Follow last field with lastSep. */
{
fprintf(f, "%u", el->hgnc);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->symbol);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->name);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->map);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->omimId);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%u", el->pmId1);
fputc(sep,f);
fprintf(f, "%u", el->pmId2);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->refSeqAcc);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->aliases);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%u", el->locusLinkId);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->gdbId);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->swissProt);
if (sep == ',') fputc('"',f);
fputc(lastSep,f);
}

