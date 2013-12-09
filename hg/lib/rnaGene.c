/* rnaGene.c was originally generated by the autoSql program, which also 
 * generated rnaGene.h and rnaGene.sql.  This module links the database and the RAM 
 * representation of objects. */

#include "common.h"
#include "jksql.h"
#include "rnaGene.h"

static char const rcsid[] = "$Id: rnaGene.c,v 1.4 2005/04/13 06:25:56 markd Exp $";

void rnaGeneStaticLoad(char **row, struct rnaGene *ret)
/* Load a row from rnaGene table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->chrom = row[0];
ret->chromStart = sqlUnsigned(row[1]);
ret->chromEnd = sqlUnsigned(row[2]);
ret->name = row[3];
ret->score = sqlUnsigned(row[4]);
strcpy(ret->strand, row[5]);
ret->source = row[6];
ret->type = row[7];
ret->fullScore = atof(row[8]);
ret->isPsuedo = sqlUnsigned(row[9]);
}

struct rnaGene *rnaGeneLoad(char **row)
/* Load a rnaGene from row fetched with select * from rnaGene
 * from database.  Dispose of this with rnaGeneFree(). */
{
struct rnaGene *ret;

AllocVar(ret);
ret->chrom = cloneString(row[0]);
ret->chromStart = sqlUnsigned(row[1]);
ret->chromEnd = sqlUnsigned(row[2]);
ret->name = cloneString(row[3]);
ret->score = sqlUnsigned(row[4]);
strcpy(ret->strand, row[5]);
ret->source = cloneString(row[6]);
ret->type = cloneString(row[7]);
ret->fullScore = atof(row[8]);
ret->isPsuedo = sqlUnsigned(row[9]);
return ret;
}

struct rnaGene *rnaGeneCommaIn(char **pS, struct rnaGene *ret)
/* Create a rnaGene out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new rnaGene */
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
ret->source = sqlStringComma(&s);
ret->type = sqlStringComma(&s);
ret->fullScore = sqlSignedComma(&s);
ret->isPsuedo = sqlUnsignedComma(&s);
*pS = s;
return ret;
}

void rnaGeneFree(struct rnaGene **pEl)
/* Free a single dynamically allocated rnaGene such as created
 * with rnaGeneLoad(). */
{
struct rnaGene *el;

if ((el = *pEl) == NULL) return;
freeMem(el->chrom);
freeMem(el->name);
freeMem(el->source);
freeMem(el->type);
freez(pEl);
}

void rnaGeneFreeList(struct rnaGene **pList)
/* Free a list of dynamically allocated rnaGene's */
{
struct rnaGene *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    rnaGeneFree(&el);
    }
*pList = NULL;
}

void rnaGeneOutput(struct rnaGene *el, FILE *f, char sep, char lastSep) 
/* Print out rnaGene.  Separate fields with sep. Follow last field with lastSep. */
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
fprintf(f, "%s", el->source);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->type);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%f", el->fullScore);
fputc(sep,f);
fprintf(f, "%u", el->isPsuedo);
fputc(lastSep,f);
}

