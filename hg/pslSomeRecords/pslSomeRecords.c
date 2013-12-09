/* pslSomeRecords - Extract multiple psl records. */
#include "common.h"
#include "linefile.h"
#include "hash.h"
#include "options.h"
#include "obscure.h"
#include "psl.h"

boolean tToo = FALSE;

void usage()
/* Explain usage and exit. */
{
errAbort(
  "pslSomeRecords - Extract multiple psl records\n"
  "usage:\n"
  "   pslSomeRecords pslIn listFile pslOut\n"
  "where:\n"
  "   pslIn is the input psl file\n"
  "   listFile is a file with a qName (rna accession usually)\n"
  "          on each line\n"
  "   pslOut is the output psl file\n"
  "options:\n"
  "   -tToo - if set, the list file is two column, qName and tName.\n"
  "           In this case only records matching on both q and t are\n"
  "           output\n"
  );
}

static struct optionSpec options[] = {
   {"tToo", OPTION_BOOLEAN},
   {NULL, 0},
};

struct hash *hashLines(char *fileName)
/* Read all lines in file and put them in a hash. */
{
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[1];
struct hash *hash = newHash(0);
while (lineFileRow(lf, row))
    hashAdd(hash, row[0], NULL);
lineFileClose(&lf);
return hash;
}

void pslSomeRecords(char *pslIn, char *listName, char *pslOut)
/* pslSomeRecords - Extract multiple psl records. */
{
struct hash *hash;
if (tToo)
    hash = hashTwoColumnFile(listName);
else
    hash = hashWordsInFile(listName, 16);
struct lineFile *lf = pslFileOpen(pslIn);
FILE *f = mustOpen(pslOut, "w");
struct psl *psl;

while ((psl = pslNext(lf) ) != NULL)
    {
    if (tToo)
        {
	char *tName = hashFindVal(hash, psl->qName);
	if (tName != NULL && sameString(psl->tName, tName))
	    pslTabOut(psl, f);
	}
    else
	{
	if (hashLookup(hash, psl->qName))
	    pslTabOut(psl, f);
	}
    pslFree(&psl);
    }
}

int main(int argc, char *argv[])
/* Process command line. */
{
optionInit(&argc, argv, options);
if (argc != 4)
    usage();
tToo = optionExists("tToo");
pslSomeRecords(argv[1], argv[2], argv[3]);
return 0;
}
