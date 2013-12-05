/* ooWeedZero - Weed out phase zero clones from geno.lst. */
#include "common.h"
#include "linefile.h"
#include "hash.h"
#include "cheapcgi.h"
#include "ooUtils.h"
#include "portable.h"
#include "obscure.h"

static char const rcsid[] = "$Id: ooWeedZero.c,v 1.4 2003/05/06 07:22:33 kate Exp $";

void usage()
/* Explain usage and exit. */
{
errAbort(
  "ooWeedZero - Weed out phase zero clones from geno.lst\n"
  "usage:\n"
  "   ooWeedZero sequence.inf ooDir\n"
  "options:\n"
  "   -dupes=checkGoldDupes.out - removes a particular accession, zero or not.\n"
  "          Can occur multiple times.\n"
  );
}

struct weed
/* Something that needs weeding. */
    {
    struct weed *next;
    char *cloneName;	/* Name of clone. */
    char *ctgDir;	/* Name of file that needs weeding. */
    };
struct weed *weedList;

struct clone
/* Info on a clone */
    {
    struct clone *next;
    char *name;
    int phase;
    };
struct clone *cloneList = NULL;
struct hash *cloneHash;

struct clone *readSeqInfo(char *fileName)
/* Read sequence.info file into clone list. */
{
struct lineFile *lf = lineFileOpen(fileName, TRUE);
struct clone *cloneList = NULL, *clone;
char *row[10];

while (lineFileRow(lf, row))
    {
    chopSuffix(row[0]);
    AllocVar(clone);
    clone->name = cloneString(row[0]);
    clone->phase = atoi(row[3]);
    slAddHead(&cloneList, clone);
    }
lineFileClose(&lf);
slReverse(&cloneList);
return cloneList;
}

void oneContig(char *dir, char *chrom, char *contig)
/* Build weed list one contig at a time. */
{
char fileName[512];
struct weed *weed;
boolean gotWeed = FALSE;
struct lineFile *lf;
char *row[1];
char root[128];
struct clone *clone;

sprintf(fileName, "%s/geno.lst", dir);
lf = lineFileOpen(fileName, TRUE);
while (lineFileRow(lf, row))
    {
    splitPath(trimSpaces(row[0]), NULL, root, NULL);
    if ((clone = hashFindVal(cloneHash, root)) != NULL)
        {
	if (clone->phase == 0)
	    {
	    AllocVar(weed);
	    weed->cloneName = cloneString(clone->name);
	    weed->ctgDir = cloneString(dir);
	    slAddHead(&weedList, weed);
	    }
	}
    }
lineFileClose(&lf);
}

void weedFile(char *fileName, char *pattern)
/* Read file/weed file/write file. */
{
char bakFileName[512];
FILE *f;
char *line;
struct lineFile *lf;

if (fileExists(fileName))
    {
    sprintf(bakFileName, "%s.bak", fileName);
    if (rename(fileName, bakFileName) != 0)
       errAbort("Couldn't make backup of %s", fileName);
    f = mustOpen(fileName, "w");
    lf = lineFileOpen(bakFileName, TRUE);
    while (lineFileNext(lf, &line, NULL))
	{
	if (!stringIn(pattern, line))
	    fprintf(f, "%s\n", line);
	else
	    {
	    uglyf("%s:%d  %s\n", lf->fileName, lf->lineIx, line);
	    }
	}
    fclose(f);
    lineFileClose(&lf);
    }
}

void weedDir(struct weed *weed)
/* Weed files in dir. */
{
char fileName[512];
static char *gardens[] = {
    "geno.lst.noNt", "geno.lst", "self.psl", "pairedReads.psl", "mrna.psl", "est.psl", "bacEnd.psl",
    "info", "info.noNt", "nt.noNt", "cloneEnds", "cloneOverlap", "cloneInfo"};
int i;

printf("%s in %s\n", weed->cloneName, weed->ctgDir);
for (i=0; i<ArraySize(gardens); ++i)
    {
    sprintf(fileName, "%s/%s", weed->ctgDir, gardens[i]);
    weedFile(fileName, weed->cloneName);
    }
}

struct weed *dupesToWeeds(char *fileName)
/* Turn file generated by checkGoldDupes to weed list. */
{
struct weed *list = NULL, *weed;
char *words[6];
int wordCount;
struct lineFile *lf = lineFileOpen(fileName, TRUE);

while ((wordCount = lineFileChop(lf, words)) != 0)
    {
    if (sameString(words[1], "duplicates"))
       break;
    lineFileExpectWords(lf, 6, wordCount);
    chopSuffix(words[0]);
    AllocVar(weed);
    weed->cloneName = cloneString(words[0]);
    weed->ctgDir = cloneString(words[3]);
    slAddHead(&list, weed);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

void ooWeedZero(char *seqInfo, char *ooDir)
/* ooWeedZero - Weed out phase zero clones from geno.lst. */
{
struct clone *clone;
struct weed *weed;
struct slName *specificList = cgiStringList("acc"), *specific;
struct slName *cgiStringList(char *varName);

cloneHash = newHash(0);
cloneList = readSeqInfo(seqInfo);
for (clone = cloneList; clone != NULL; clone = clone->next)
    hashAdd(cloneHash, clone->name, clone);
if (cgiVarExists("dupes"))
    weedList = dupesToWeeds(cgiString("dupes"));
else
    {
    ooToAllContigs(ooDir, oneContig);
    slReverse(&weedList);
    }
for (weed = weedList; weed != NULL; weed = weed->next)
    {
    weedDir(weed);
    }
}

int main(int argc, char *argv[])
/* Process command line. */
{
cgiSpoof(&argc, argv);
if (argc != 3)
    usage();
ooWeedZero(argv[1], argv[2]);
return 0;
}
