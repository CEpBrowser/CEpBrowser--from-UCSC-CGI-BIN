/*****************************************************************************
 * Copyright (C) 2000 Jim Kent.  This source code may be freely used         *
 * for personal, academic, and non-profit purposes.  Commercial use          *
 * permitted only by explicit agreement with Jim Kent (jim_kent@pacbell.net) *
 *****************************************************************************/
/* hgGene.c was originally generated by the autoSql program, which also 
 * generated hgGene.h and hgGene.sql.  This module links the database and the RAM 
 * representation of objects. */
#include "common.h"
#include "jksql.h"
#include "hgGene.h"

static char const rcsid[] = "$Id: hgGene.c,v 1.5 2005/04/13 06:25:54 markd Exp $";

void geneFinderStaticLoad(char **row, struct geneFinder *ret)
/* Load a row from geneFinder table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->id = sqlUnsigned(row[0]);
ret->name = row[1];
}

struct geneFinder *geneFinderLoad(char **row)
/* Load a geneFinder from row fetched with select * from geneFinder
 * from database.  Dispose of this with geneFinderFree(). */
{
struct geneFinder *ret;

AllocVar(ret);
ret->id = sqlUnsigned(row[0]);
ret->name = cloneString(row[1]);
return ret;
}

struct geneFinder *geneFinderCommaIn(char **pS)
/* Create a geneFinder out of a comma separated string. */
{
struct geneFinder *ret;
char *s = *pS;

AllocVar(ret);
ret->id = sqlUnsignedComma(&s);
ret->name = sqlStringComma(&s);
*pS = s;
return ret;
}

void geneFinderFree(struct geneFinder **pEl)
/* Free a single dynamically allocated geneFinder such as created
 * with geneFinderLoad(). */
{
struct geneFinder *el;

if ((el = *pEl) == NULL) return;
freeMem(el->name);
freez(pEl);
}

void geneFinderFreeList(struct geneFinder **pList)
/* Free a list of dynamically allocated geneFinder's */
{
struct geneFinder *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    geneFinderFree(&el);
    }
*pList = NULL;
}

void geneFinderOutput(struct geneFinder *el, FILE *f, char sep, char lastSep) 
/* Print out geneFinder.  Separate fields with sep. Follow last field with lastSep. */
{
fprintf(f, "%u", el->id);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->name);
if (sep == ',') fputc('"',f);
fputc(lastSep,f);
}

struct hgGene *hgGeneLoad(char **row)
/* Load a hgGene from row fetched with select * from hgGene
 * from database.  Dispose of this with hgGeneFree(). */
{
struct hgGene *ret;
int sizeOne;

AllocVar(ret);
ret->transcriptCount = sqlUnsigned(row[8]);
ret->id = sqlUnsigned(row[0]);
ret->name = cloneString(row[1]);
ret->geneFinder = sqlUnsigned(row[2]);
ret->startBac = sqlUnsigned(row[3]);
ret->startPos = sqlUnsigned(row[4]);
ret->endBac = sqlUnsigned(row[5]);
ret->endPos = sqlUnsigned(row[6]);
ret->orientation = sqlSigned(row[7]);
sqlUnsignedDynamicArray(row[9], &ret->transcripts, &sizeOne);
assert(sizeOne == ret->transcriptCount);
return ret;
}

struct hgGene *hgGeneCommaIn(char **pS)
/* Create a hgGene out of a comma separated string. */
{
struct hgGene *ret;
char *s = *pS;
int i;

AllocVar(ret);
ret->id = sqlUnsignedComma(&s);
ret->name = sqlStringComma(&s);
ret->geneFinder = sqlUnsignedComma(&s);
ret->startBac = sqlUnsignedComma(&s);
ret->startPos = sqlUnsignedComma(&s);
ret->endBac = sqlUnsignedComma(&s);
ret->endPos = sqlUnsignedComma(&s);
ret->orientation = sqlSignedComma(&s);
ret->transcriptCount = sqlUnsignedComma(&s);
s = sqlEatChar(s, '{');
AllocArray(ret->transcripts, ret->transcriptCount);
for (i=0; i<ret->transcriptCount; ++i)
    {
    ret->transcripts[i] = sqlUnsignedComma(&s);
    }
s = sqlEatChar(s, '}');
s = sqlEatChar(s, ',');
*pS = s;
return ret;
}

void hgGeneFree(struct hgGene **pEl)
/* Free a single dynamically allocated hgGene such as created
 * with hgGeneLoad(). */
{
struct hgGene *el;

if ((el = *pEl) == NULL) return;
freeMem(el->name);
freeMem(el->transcripts);
freez(pEl);
}

void hgGeneFreeList(struct hgGene **pList)
/* Free a list of dynamically allocated hgGene's */
{
struct hgGene *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    hgGeneFree(&el);
    }
*pList = NULL;
}

void hgGeneOutput(struct hgGene *el, FILE *f, char sep, char lastSep) 
/* Print out hgGene.  Separate fields with sep. Follow last field with lastSep. */
{
int i;
fprintf(f, "%u", el->id);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->name);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%u", el->geneFinder);
fputc(sep,f);
fprintf(f, "%u", el->startBac);
fputc(sep,f);
fprintf(f, "%u", el->startPos);
fputc(sep,f);
fprintf(f, "%u", el->endBac);
fputc(sep,f);
fprintf(f, "%u", el->endPos);
fputc(sep,f);
fprintf(f, "%d", el->orientation);
fputc(sep,f);
fprintf(f, "%u", el->transcriptCount);
fputc(sep,f);
if (sep == ',') fputc('{',f);
for (i=0; i<el->transcriptCount; ++i)
    {
    fprintf(f, "%u", el->transcripts[i]);
    fputc(',', f);
    }
if (sep == ',') fputc('}',f);
fputc(lastSep,f);
}

struct hgTranscript *hgTranscriptLoad(char **row)
/* Load a hgTranscript from row fetched with select * from hgTranscript
 * from database.  Dispose of this with hgTranscriptFree(). */
{
struct hgTranscript *ret;
int sizeOne;

AllocVar(ret);
ret->exonCount = sqlUnsigned(row[12]);
ret->id = sqlUnsigned(row[0]);
ret->name = cloneString(row[1]);
ret->hgGene = sqlUnsigned(row[2]);
ret->startBac = sqlUnsigned(row[3]);
ret->startPos = sqlUnsigned(row[4]);
ret->endBac = sqlUnsigned(row[5]);
ret->endPos = sqlUnsigned(row[6]);
ret->cdsStartBac = sqlUnsigned(row[7]);
ret->cdsStartPos = sqlUnsigned(row[8]);
ret->cdsEndBac = sqlUnsigned(row[9]);
ret->cdsEndPos = sqlUnsigned(row[10]);
ret->orientation = sqlSigned(row[11]);
sqlUnsignedDynamicArray(row[13], &ret->exonStartBacs, &sizeOne);
assert(sizeOne == ret->exonCount);
sqlUnsignedDynamicArray(row[14], &ret->exonStartPos, &sizeOne);
assert(sizeOne == ret->exonCount);
sqlUnsignedDynamicArray(row[15], &ret->exonEndBacs, &sizeOne);
assert(sizeOne == ret->exonCount);
sqlUnsignedDynamicArray(row[16], &ret->exonEndPos, &sizeOne);
assert(sizeOne == ret->exonCount);
return ret;
}

struct hgTranscript *hgTranscriptCommaIn(char **pS)
/* Create a hgTranscript out of a comma separated string. */
{
struct hgTranscript *ret;
char *s = *pS;
int i;

AllocVar(ret);
ret->id = sqlUnsignedComma(&s);
ret->name = sqlStringComma(&s);
ret->hgGene = sqlUnsignedComma(&s);
ret->startBac = sqlUnsignedComma(&s);
ret->startPos = sqlUnsignedComma(&s);
ret->endBac = sqlUnsignedComma(&s);
ret->endPos = sqlUnsignedComma(&s);
ret->cdsStartBac = sqlUnsignedComma(&s);
ret->cdsStartPos = sqlUnsignedComma(&s);
ret->cdsEndBac = sqlUnsignedComma(&s);
ret->cdsEndPos = sqlUnsignedComma(&s);
ret->orientation = sqlSignedComma(&s);
ret->exonCount = sqlUnsignedComma(&s);
s = sqlEatChar(s, '{');
AllocArray(ret->exonStartBacs, ret->exonCount);
for (i=0; i<ret->exonCount; ++i)
    {
    ret->exonStartBacs[i] = sqlUnsignedComma(&s);
    }
s = sqlEatChar(s, '}');
s = sqlEatChar(s, ',');
s = sqlEatChar(s, '{');
AllocArray(ret->exonStartPos, ret->exonCount);
for (i=0; i<ret->exonCount; ++i)
    {
    ret->exonStartPos[i] = sqlUnsignedComma(&s);
    }
s = sqlEatChar(s, '}');
s = sqlEatChar(s, ',');
s = sqlEatChar(s, '{');
AllocArray(ret->exonEndBacs, ret->exonCount);
for (i=0; i<ret->exonCount; ++i)
    {
    ret->exonEndBacs[i] = sqlUnsignedComma(&s);
    }
s = sqlEatChar(s, '}');
s = sqlEatChar(s, ',');
s = sqlEatChar(s, '{');
AllocArray(ret->exonEndPos, ret->exonCount);
for (i=0; i<ret->exonCount; ++i)
    {
    ret->exonEndPos[i] = sqlUnsignedComma(&s);
    }
s = sqlEatChar(s, '}');
s = sqlEatChar(s, ',');
*pS = s;
return ret;
}

void hgTranscriptFree(struct hgTranscript **pEl)
/* Free a single dynamically allocated hgTranscript such as created
 * with hgTranscriptLoad(). */
{
struct hgTranscript *el;

if ((el = *pEl) == NULL) return;
freeMem(el->name);
freeMem(el->exonStartBacs);
freeMem(el->exonStartPos);
freeMem(el->exonEndBacs);
freeMem(el->exonEndPos);
freez(pEl);
}

void hgTranscriptFreeList(struct hgTranscript **pList)
/* Free a list of dynamically allocated hgTranscript's */
{
struct hgTranscript *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    hgTranscriptFree(&el);
    }
*pList = NULL;
}

void hgTranscriptOutput(struct hgTranscript *el, FILE *f, char sep, char lastSep) 
/* Print out hgTranscript.  Separate fields with sep. Follow last field with lastSep. */
{
int i;
fprintf(f, "%u", el->id);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->name);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%u", el->hgGene);
fputc(sep,f);
fprintf(f, "%u", el->startBac);
fputc(sep,f);
fprintf(f, "%u", el->startPos);
fputc(sep,f);
fprintf(f, "%u", el->endBac);
fputc(sep,f);
fprintf(f, "%u", el->endPos);
fputc(sep,f);
fprintf(f, "%u", el->cdsStartBac);
fputc(sep,f);
fprintf(f, "%u", el->cdsStartPos);
fputc(sep,f);
fprintf(f, "%u", el->cdsEndBac);
fputc(sep,f);
fprintf(f, "%u", el->cdsEndPos);
fputc(sep,f);
fprintf(f, "%d", el->orientation);
fputc(sep,f);
fprintf(f, "%u", el->exonCount);
fputc(sep,f);
if (sep == ',') fputc('{',f);
for (i=0; i<el->exonCount; ++i)
    {
    fprintf(f, "%u", el->exonStartBacs[i]);
    fputc(',', f);
    }
if (sep == ',') fputc('}',f);
fputc(sep,f);
if (sep == ',') fputc('{',f);
for (i=0; i<el->exonCount; ++i)
    {
    fprintf(f, "%u", el->exonStartPos[i]);
    fputc(',', f);
    }
if (sep == ',') fputc('}',f);
fputc(sep,f);
if (sep == ',') fputc('{',f);
for (i=0; i<el->exonCount; ++i)
    {
    fprintf(f, "%u", el->exonEndBacs[i]);
    fputc(',', f);
    }
if (sep == ',') fputc('}',f);
fputc(sep,f);
if (sep == ',') fputc('{',f);
for (i=0; i<el->exonCount; ++i)
    {
    fprintf(f, "%u", el->exonEndPos[i]);
    fputc(',', f);
    }
if (sep == ',') fputc('}',f);
fputc(lastSep,f);
}

