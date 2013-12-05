/* rmskOut.c was originally generated by the autoSql program, which also 
 * generated rmskOut.h and rmskOut.sql.  This module links the database and the RAM 
 * representation of objects. */

#include "common.h"
#include "jksql.h"
#include "obscure.h"
#include "linefile.h"
#include "rmskOut.h"
#include "binRange.h"

static char const rcsid[] = "$Id: rmskOut.c,v 1.9 2006/03/09 21:11:21 angie Exp $";

void rmskOutStaticLoad(char **row, struct rmskOut *ret)
/* Load a row from rmskOut table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->swScore = sqlUnsigned(row[0]);
ret->milliDiv = sqlUnsigned(row[1]);
ret->milliDel = sqlUnsigned(row[2]);
ret->milliIns = sqlUnsigned(row[3]);
ret->genoName = row[4];
ret->genoStart = sqlUnsigned(row[5]);
ret->genoEnd = sqlUnsigned(row[6]);
ret->genoLeft = sqlSigned(row[7]);
strcpy(ret->strand, row[8]);
ret->repName = row[9];
ret->repClass = row[10];
ret->repFamily = row[11];
ret->repStart = sqlSigned(row[12]);
ret->repEnd = sqlSigned(row[13]);
ret->repLeft = sqlSigned(row[14]);
strcpy(ret->id, row[15]);
}

struct rmskOut *rmskOutLoad(char **row)
/* Load a rmskOut from row fetched with select * from rmskOut
 * from database.  Dispose of this with rmskOutFree(). */
{
struct rmskOut *ret;

AllocVar(ret);
ret->swScore = sqlUnsigned(row[0]);
ret->milliDiv = sqlUnsigned(row[1]);
ret->milliDel = sqlUnsigned(row[2]);
ret->milliIns = sqlUnsigned(row[3]);
ret->genoName = cloneString(row[4]);
ret->genoStart = sqlUnsigned(row[5]);
ret->genoEnd = sqlUnsigned(row[6]);
ret->genoLeft = sqlSigned(row[7]);
strcpy(ret->strand, row[8]);
ret->repName = cloneString(row[9]);
ret->repClass = cloneString(row[10]);
ret->repFamily = cloneString(row[11]);
ret->repStart = sqlSigned(row[12]);
ret->repEnd = sqlSigned(row[13]);
ret->repLeft = sqlSigned(row[14]);
strcpy(ret->id, row[15]);
return ret;
}

struct rmskOut *rmskOutCommaIn(char **pS, struct rmskOut *ret)
/* Create a rmskOut out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new rmskOut */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->swScore = sqlUnsignedComma(&s);
ret->milliDiv = sqlUnsignedComma(&s);
ret->milliDel = sqlUnsignedComma(&s);
ret->milliIns = sqlUnsignedComma(&s);
ret->genoName = sqlStringComma(&s);
ret->genoStart = sqlUnsignedComma(&s);
ret->genoEnd = sqlUnsignedComma(&s);
ret->genoLeft = sqlSignedComma(&s);
sqlFixedStringComma(&s, ret->strand, sizeof(ret->strand));
ret->repName = sqlStringComma(&s);
ret->repClass = sqlStringComma(&s);
ret->repFamily = sqlStringComma(&s);
ret->repStart = sqlSignedComma(&s);
ret->repEnd = sqlSignedComma(&s);
ret->repLeft = sqlSignedComma(&s);
sqlFixedStringComma(&s, ret->id, sizeof(ret->id));
*pS = s;
return ret;
}

void rmskOutFree(struct rmskOut **pEl)
/* Free a single dynamically allocated rmskOut such as created
 * with rmskOutLoad(). */
{
struct rmskOut *el;

if ((el = *pEl) == NULL) return;
freeMem(el->genoName);
freeMem(el->repName);
freeMem(el->repClass);
freeMem(el->repFamily);
freez(pEl);
}

void rmskOutFreeList(struct rmskOut **pList)
/* Free a list of dynamically allocated rmskOut's */
{
struct rmskOut *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    rmskOutFree(&el);
    }
*pList = NULL;
}

void rmskOutOutput(struct rmskOut *el, FILE *f, char sep, char lastSep) 
/* Print out rmskOut.  Separate fields with sep. Follow last field with lastSep. */
{
fprintf(f, "%u", el->swScore);
fputc(sep,f);
fprintf(f, "%u", el->milliDiv);
fputc(sep,f);
fprintf(f, "%u", el->milliDel);
fputc(sep,f);
fprintf(f, "%u", el->milliIns);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->genoName);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%u", el->genoStart);
fputc(sep,f);
fprintf(f, "%u", el->genoEnd);
fputc(sep,f);
fprintf(f, "%d", el->genoLeft);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->strand);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->repName);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->repClass);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->repFamily);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%d", el->repStart);
fputc(sep,f);
fprintf(f, "%d", el->repEnd);
fputc(sep,f);
fprintf(f, "%d", el->repLeft);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->id);
if (sep == ',') fputc('"',f);
fputc(lastSep,f);
}

/* ------------ End of AutoSQL generated code. ------------------ */

void rmskOutOpenVerify(char *fileName, struct lineFile **retFile, boolean *retEmpty)
/* Open repeat masker .out file and verify that it is good.
 * Set retEmpty if it has header characteristic of an empty file. */
{
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *line;
int lineSize;

lineFileNeedNext(lf, &line, &lineSize);
if (startsWith("There were no", line))
    *retEmpty = TRUE;
if (startsWith("   SW", line))
    {
    line = skipLeadingSpaces(line);
    if (!startsWith("SW", line))
        errAbort("%s doesn't seem to be a RepeatMasker .out file", fileName);
    lineFileSkip(lf, 2);
    *retEmpty = FALSE;
    }
*retFile = lf;
}

static int negParenNum(struct lineFile *lf, char *s)
/* Return number where negative is shown by parenthization. */
{
boolean hasParen = FALSE;
int result;
if (*s == '(')
   {
   hasParen = TRUE;
   ++s;
   }
if (!isdigit(s[0]) && s[0] != '-')
   errAbort("Expecting digit line %d of %s got %s\n", 
   	lf->lineIx, lf->fileName, s);
result = atoi(s);
if (hasParen) 
    result = -result;
return result;
}

static void parseClassAndFamily(char *s, char **retClass, char **retFamily)
/* Separate repeatMasker class/family .*/
{
char *e = strchr(s, '/');
if (e == NULL)
    *retClass = *retFamily = s;
else
    {
    *e++ = 0;
    *retClass = s;
    *retFamily = e;
    }
}

struct rmskOut *rmskOutReadNext(struct lineFile *lf)
/* Read next record from repeat masker file.  Return NULL at EOF. */
{
char *words[32];
int wordCount;
char id;
struct rmskOut *ret;
char *class, *family;

if ((wordCount = lineFileChop(lf, words)) == 0)
    return NULL;
if (wordCount < 14 )
    errAbort("Expecting at least 14 words line %d of %s", lf->lineIx, lf->fileName);
if (wordCount >= 15)
    id = words[14][0];
else
    id = 0;
AllocVar(ret);
ret->swScore = lineFileNeedNum(lf, words, 0);
ret->milliDiv = round(10.0*atof(words[1]));
ret->milliDel = round(10.0*atof(words[2]));
ret->milliIns = round(10.0*atof(words[3]));
ret->genoName = cloneString(words[4]);
ret->genoStart = lineFileNeedNum(lf, words, 5)-1;
ret->genoEnd = lineFileNeedNum(lf, words, 6);
ret->genoLeft = -negParenNum(lf, words[7]);
if (sameString(words[8], "C"))
    ret->strand[0] = '-';
else if (sameString(words[8], "+"))
    ret->strand[0] = '+';
else
    errAbort("Unexpected strand char line %d of %s", lf->lineIx, lf->fileName);
ret->repName = cloneString(words[9]);
parseClassAndFamily(words[10], &class, &family);
ret->repClass = cloneString(class);
ret->repFamily = cloneString(family);
ret->repStart = negParenNum(lf, words[11])-1;
ret->repEnd = sqlSigned(words[12]);
ret->repLeft = -negParenNum(lf, words[13]);
return ret;
}

struct rmskOut *rmskOutRead(char *fileName)
/* Read all records in .out file and return as list. */
{
struct lineFile *lf;
boolean isEmpty;
struct rmskOut *list = NULL, *el;

rmskOutOpenVerify(fileName, &lf, &isEmpty);
if (!isEmpty)
    {
    while ((el = rmskOutReadNext(lf)) != NULL)
       {
       slAddHead(&list, el);
       }
    slReverse(&list);
    }
lineFileClose(&lf);
return list;
}

void rmskOutWriteHead(FILE *f)
/* Write out rmsk header lines. */
{
fprintf(f,
"   SW  perc perc perc  query      position in query           matching       repeat              position in  repeat\n"
"score  div. del. ins.  sequence    begin     end    (left)    repeat         class/family         begin  end (left)   ID\n"
"\n");
}

static void parenNeg(int num, char *s, size_t sSize)
/* Write number to s, parenthesizing if negative. */
{
if (num <= 0)
   safef(s, sSize, "(%d)", -num);
else
   safef(s, sSize, "%d", num);
}

void rmskOutWriteOneOut(struct rmskOut *rmsk, FILE *f)
/* Write one rmsk in .out format to file. */
{
char genoLeft[24], repStart[24], repLeft[24];
char classFam[128];

parenNeg(-rmsk->genoLeft, genoLeft, sizeof(genoLeft));
parenNeg(rmsk->repStart+1, repStart, sizeof(repStart));
parenNeg(-rmsk->repLeft, repLeft, sizeof(repLeft));
if (sameString(rmsk->repClass, rmsk->repFamily))
    safef(classFam, sizeof(classFam), "%s", rmsk->repClass);
else
    safef(classFam, sizeof(classFam), "%s/%s",
	  rmsk->repClass, rmsk->repFamily);
fprintf(f, 
  "%5d %5.1f %4.1f %4.1f  %-9s %7d %7d %9s %1s  %-14s %-19s %6s %4d %6s %6s\n",
  rmsk->swScore, 0.1*rmsk->milliDiv, 0.1*rmsk->milliDel, 0.1*rmsk->milliIns, 
  rmsk->genoName, rmsk->genoStart+1, rmsk->genoEnd, genoLeft,
  (rmsk->strand[0] == '+' ? "+" : "C"),
  rmsk->repName, classFam, repStart, rmsk->repEnd, repLeft, rmsk->id);
}

void rmskOutWriteAllOut(char *fileName, struct rmskOut *rmskList)
/* Write .out format file containing all in rmskList. */
{
FILE *f = mustOpen(fileName, "w");
struct rmskOut *rmsk;

rmskOutWriteHead(f);
for (rmsk = rmskList; rmsk != NULL; rmsk = rmsk->next)
    rmskOutWriteOneOut(rmsk, f);
fclose(f);
}

struct binKeeper *readRepeats(char *chrom, char *rmskFileName, struct hash *tSizeHash)
/* read all repeats for a chromosome of size size, returns results in binKeeper structure for fast query*/
{
    boolean rmskRet;
    struct lineFile *rmskF = NULL;
    struct rmskOut *rmsk;
    struct binKeeper *bk; 
    int size;

    size = hashIntVal(tSizeHash, chrom);
    bk = binKeeperNew(0, size);
    assert(size > 1);
    rmskOutOpenVerify(rmskFileName ,&rmskF , &rmskRet);
    while ((rmsk = rmskOutReadNext(rmskF)) != NULL)
        {
        binKeeperAdd(bk, rmsk->genoStart, rmsk->genoEnd, rmsk);
        }
    lineFileClose(&rmskF);
    return bk;
}

struct hash *readRepeatsAll(char *sizeFileName, char *rmskDir)
/* read all repeats for a all chromosomes getting sizes from sizeFileNmae , returns results in hash of binKeeper structure for fast query*/
{
boolean rmskRet;
struct binKeeper *bk; 
struct lineFile *rmskF = NULL;
struct rmskOut *rmsk;
struct lineFile *lf = lineFileOpen(sizeFileName, TRUE);
struct hash *hash = newHash(0);
char *row[2];
char rmskFileName[256];

while (lineFileRow(lf, row))
    {
    char *name = row[0];
    int size = lineFileNeedNum(lf, row, 1);

    if (hashLookup(hash, name) != NULL)
        warn("Duplicate %s, ignoring all but first\n", name);
    else
        {
        bk = binKeeperNew(0, size);
        assert(size > 1);
        safef(rmskFileName, sizeof(rmskFileName), "%s/%s.fa.out",rmskDir,name);
        rmskOutOpenVerify(rmskFileName ,&rmskF , &rmskRet);
        while ((rmsk = rmskOutReadNext(rmskF)) != NULL)
            {
            binKeeperAdd(bk, rmsk->genoStart, rmsk->genoEnd, rmsk);
            }
        lineFileClose(&rmskF);
	hashAdd(hash, name, bk);
        }
    }
lineFileClose(&lf);
return hash;
}
