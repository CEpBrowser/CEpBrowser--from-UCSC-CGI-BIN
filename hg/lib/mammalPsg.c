/* mammalPsg.c was originally generated by the autoSql program, which also 
 * generated mammalPsg.h and mammalPsg.sql.  This module links the database and
 * the RAM representation of objects. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "mammalPsg.h"

static char const rcsid[] = "$Id: mammalPsg.c,v 1.1 2008/07/03 21:52:09 acs Exp $";

struct mammalPsg *mammalPsgLoad(char **row)
/* Load a mammalPsg from row fetched with select * from mammalPsg
 * from database.  Dispose of this with mammalPsgFree(). */
{
struct mammalPsg *ret;

AllocVar(ret);
ret->blockCount = sqlSigned(row[9]);
ret->chrom = cloneString(row[0]);
ret->chromStart = sqlUnsigned(row[1]);
ret->chromEnd = sqlUnsigned(row[2]);
ret->name = cloneString(row[3]);
ret->score = sqlUnsigned(row[4]);
safecpy(ret->strand, sizeof(ret->strand), row[5]);
ret->thickStart = sqlUnsigned(row[6]);
ret->thickEnd = sqlUnsigned(row[7]);
ret->reserved = sqlUnsigned(row[8]);
{
int sizeOne;
sqlSignedDynamicArray(row[10], &ret->blockSizes, &sizeOne);
assert(sizeOne == ret->blockCount);
}
{
int sizeOne;
sqlSignedDynamicArray(row[11], &ret->chromStarts, &sizeOne);
assert(sizeOne == ret->blockCount);
}
ret->lrtAllPValue = sqlFloat(row[12]);
ret->lrtAllIsFdr = sqlUnsigned(row[13]);
ret->lrtPrimateBrPValue = sqlFloat(row[14]);
ret->lrtPrimateBrIsFdr = sqlUnsigned(row[15]);
ret->lrtPrimateClPValue = sqlFloat(row[16]);
ret->lrtPrimateClIsFdr = sqlUnsigned(row[17]);
ret->lrtRodentBrPValue = sqlFloat(row[18]);
ret->lrtRodentBrIsFdr = sqlUnsigned(row[19]);
ret->lrtRodentClPValue = sqlFloat(row[20]);
ret->lrtRodentClIsFdr = sqlUnsigned(row[21]);
ret->lrtHumanPValue = sqlFloat(row[22]);
ret->lrtHumanIsFdr = sqlUnsigned(row[23]);
ret->lrtChimpPValue = sqlFloat(row[24]);
ret->lrtChimpIsFdr = sqlUnsigned(row[25]);
ret->lrtHominidPValue = sqlFloat(row[26]);
ret->lrtHominidIsFdr = sqlUnsigned(row[27]);
ret->lrtMacaquePValue = sqlFloat(row[28]);
ret->lrtMacaqueIsFdr = sqlUnsigned(row[29]);
ret->bestHist = sqlUnsigned(row[30]);
ret->bestHistPP = sqlFloat(row[31]);
ret->nextBestHist = sqlUnsigned(row[32]);
ret->nextBestHistPP = sqlFloat(row[33]);
return ret;
}

struct mammalPsg *mammalPsgLoadAll(char *fileName) 
/* Load all mammalPsg from a whitespace-separated file.
 * Dispose of this with mammalPsgFreeList(). */
{
struct mammalPsg *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[34];

while (lineFileRow(lf, row))
    {
    el = mammalPsgLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct mammalPsg *mammalPsgLoadAllByChar(char *fileName, char chopper) 
/* Load all mammalPsg from a chopper separated file.
 * Dispose of this with mammalPsgFreeList(). */
{
struct mammalPsg *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[34];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = mammalPsgLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct mammalPsg *mammalPsgCommaIn(char **pS, struct mammalPsg *ret)
/* Create a mammalPsg out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new mammalPsg */
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
ret->thickStart = sqlUnsignedComma(&s);
ret->thickEnd = sqlUnsignedComma(&s);
ret->reserved = sqlUnsignedComma(&s);
ret->blockCount = sqlSignedComma(&s);
{
int i;
s = sqlEatChar(s, '{');
AllocArray(ret->blockSizes, ret->blockCount);
for (i=0; i<ret->blockCount; ++i)
    {
    ret->blockSizes[i] = sqlSignedComma(&s);
    }
s = sqlEatChar(s, '}');
s = sqlEatChar(s, ',');
}
{
int i;
s = sqlEatChar(s, '{');
AllocArray(ret->chromStarts, ret->blockCount);
for (i=0; i<ret->blockCount; ++i)
    {
    ret->chromStarts[i] = sqlSignedComma(&s);
    }
s = sqlEatChar(s, '}');
s = sqlEatChar(s, ',');
}
ret->lrtAllPValue = sqlFloatComma(&s);
ret->lrtAllIsFdr = sqlUnsignedComma(&s);
ret->lrtPrimateBrPValue = sqlFloatComma(&s);
ret->lrtPrimateBrIsFdr = sqlUnsignedComma(&s);
ret->lrtPrimateClPValue = sqlFloatComma(&s);
ret->lrtPrimateClIsFdr = sqlUnsignedComma(&s);
ret->lrtRodentBrPValue = sqlFloatComma(&s);
ret->lrtRodentBrIsFdr = sqlUnsignedComma(&s);
ret->lrtRodentClPValue = sqlFloatComma(&s);
ret->lrtRodentClIsFdr = sqlUnsignedComma(&s);
ret->lrtHumanPValue = sqlFloatComma(&s);
ret->lrtHumanIsFdr = sqlUnsignedComma(&s);
ret->lrtChimpPValue = sqlFloatComma(&s);
ret->lrtChimpIsFdr = sqlUnsignedComma(&s);
ret->lrtHominidPValue = sqlFloatComma(&s);
ret->lrtHominidIsFdr = sqlUnsignedComma(&s);
ret->lrtMacaquePValue = sqlFloatComma(&s);
ret->lrtMacaqueIsFdr = sqlUnsignedComma(&s);
ret->bestHist = sqlUnsignedComma(&s);
ret->bestHistPP = sqlFloatComma(&s);
ret->nextBestHist = sqlUnsignedComma(&s);
ret->nextBestHistPP = sqlFloatComma(&s);
*pS = s;
return ret;
}

void mammalPsgFree(struct mammalPsg **pEl)
/* Free a single dynamically allocated mammalPsg such as created
 * with mammalPsgLoad(). */
{
struct mammalPsg *el;

if ((el = *pEl) == NULL) return;
freeMem(el->chrom);
freeMem(el->name);
freeMem(el->blockSizes);
freeMem(el->chromStarts);
freez(pEl);
}

void mammalPsgFreeList(struct mammalPsg **pList)
/* Free a list of dynamically allocated mammalPsg's */
{
struct mammalPsg *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    mammalPsgFree(&el);
    }
*pList = NULL;
}

void mammalPsgOutput(struct mammalPsg *el, FILE *f, char sep, char lastSep) 
/* Print out mammalPsg.  Separate fields with sep. Follow last field with lastSep. */
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
fprintf(f, "%u", el->thickStart);
fputc(sep,f);
fprintf(f, "%u", el->thickEnd);
fputc(sep,f);
fprintf(f, "%u", el->reserved);
fputc(sep,f);
fprintf(f, "%d", el->blockCount);
fputc(sep,f);
{
int i;
if (sep == ',') fputc('{',f);
for (i=0; i<el->blockCount; ++i)
    {
    fprintf(f, "%d", el->blockSizes[i]);
    fputc(',', f);
    }
if (sep == ',') fputc('}',f);
}
fputc(sep,f);
{
int i;
if (sep == ',') fputc('{',f);
for (i=0; i<el->blockCount; ++i)
    {
    fprintf(f, "%d", el->chromStarts[i]);
    fputc(',', f);
    }
if (sep == ',') fputc('}',f);
}
fputc(sep,f);
fprintf(f, "%g", el->lrtAllPValue);
fputc(sep,f);
fprintf(f, "%u", el->lrtAllIsFdr);
fputc(sep,f);
fprintf(f, "%g", el->lrtPrimateBrPValue);
fputc(sep,f);
fprintf(f, "%u", el->lrtPrimateBrIsFdr);
fputc(sep,f);
fprintf(f, "%g", el->lrtPrimateClPValue);
fputc(sep,f);
fprintf(f, "%u", el->lrtPrimateClIsFdr);
fputc(sep,f);
fprintf(f, "%g", el->lrtRodentBrPValue);
fputc(sep,f);
fprintf(f, "%u", el->lrtRodentBrIsFdr);
fputc(sep,f);
fprintf(f, "%g", el->lrtRodentClPValue);
fputc(sep,f);
fprintf(f, "%u", el->lrtRodentClIsFdr);
fputc(sep,f);
fprintf(f, "%g", el->lrtHumanPValue);
fputc(sep,f);
fprintf(f, "%u", el->lrtHumanIsFdr);
fputc(sep,f);
fprintf(f, "%g", el->lrtChimpPValue);
fputc(sep,f);
fprintf(f, "%u", el->lrtChimpIsFdr);
fputc(sep,f);
fprintf(f, "%g", el->lrtHominidPValue);
fputc(sep,f);
fprintf(f, "%u", el->lrtHominidIsFdr);
fputc(sep,f);
fprintf(f, "%g", el->lrtMacaquePValue);
fputc(sep,f);
fprintf(f, "%u", el->lrtMacaqueIsFdr);
fputc(sep,f);
fprintf(f, "%u", el->bestHist);
fputc(sep,f);
fprintf(f, "%g", el->bestHistPP);
fputc(sep,f);
fprintf(f, "%u", el->nextBestHist);
fputc(sep,f);
fprintf(f, "%g", el->nextBestHistPP);
fputc(lastSep,f);
}

/* -------------------------------- End autoSql Generated Code -------------------------------- */

