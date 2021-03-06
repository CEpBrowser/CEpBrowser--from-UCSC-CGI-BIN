/* ScrambleFa - scramble the order of records in an fa file. */
#include "common.h"
#include "fa.h"

static char const rcsid[] = "$Id: scrambleFa.c,v 1.3 2003/06/10 17:19:33 kent Exp $";

void scrambleFa(char *inName, char *outName)
/* scrambleFa - scramble the order of records in an fa file. */
{
struct dnaSeq *seqList, *seq;
int seqCount;
int seqIx;
FILE *out;

seqList = faReadAllDna(inName);
out = mustOpen(outName, "w");
seqCount = slCount(seqList);
while (seqCount > 0)
    {
    seqIx = rand()%seqCount;
    seq = slElementFromIx(seqList, seqIx);
    faWriteNext(out, seq->name, seq->dna, seq->size);
    slRemoveEl(&seqList, seq);
    --seqCount;
    }
fclose(out);
}

void usage()
/* Explain usage and exit. */
{
errAbort("scrambleFa - scramble the order of records in an fa file\n"
         "usage:\n"
	 "    scrambleFa in.fa out.fa");
}

int main(int argc, char *argv[])
/* Process command line. */
{
if (argc != 3)
    usage();
scrambleFa(argv[1], argv[2]);
return 0;
}
