/* mafToFa - convert maf file to fasta. */
#include "common.h"
#include "linefile.h"
#include "hash.h"
#include "maf.h"
#include "options.h"

static char const rcsid[] = "$Id: mafToFa.c,v 1.2 2009/03/29 05:16:57 mikep Exp $";

boolean stripDotsDashes;

void usage()
/* Explain usage and exit. */
{
errAbort(
  "mafToFa - convert maf file to fasta\n"
  "usage:\n"
  "   mafToFa in.maf out.fa\n"
  "options:\n"
  "   -stripDotsDashes     : remove dot and dash (.-) characters from aligned sequences\n"
  );
}

static struct optionSpec options[] = {
   {"stripDotsDashes", OPTION_BOOLEAN},
   {NULL, 0},
};

char *skipDot(char *src)
/* skip past dot in src name */
{
char *dot = strchr(src, '.');
if (dot == NULL)
    return src;
else
    return dot+1;
}


void mafAliToFa(struct mafAli *maf, FILE *of)
/* convert a MAF alignment to a fa */
{
struct mafComp *c;
for (c = maf->components ; c ; c = c->next )
    {
    int start = c->start;
    int end   = c->start+c->size;
    if (stripDotsDashes)
	{
	stripChar(c->text, '.');
	stripChar(c->text, '-');
	}
    reverseIntRange(&start, &end, c->srcSize);
    fprintf(of, ">%s.%d.%d.%c.%d\n%s\n", c->src, start, end, c->strand, c->srcSize, c->text);
    }
fprintf(of,"\n");
}

void mafToFa(char *inName, char *outName)
/* mafToFa - convert maf file to fasta. */
{
struct mafFile *mf = mafOpen(inName);
FILE *faFh = mustOpen(outName, "w");
struct mafAli *maf;

while ((maf = mafNext(mf)) != NULL)
    {
    mafAliToFa(maf, faFh);
    mafAliFree(&maf);
    }
carefulClose(&faFh);
mafFileFree(&mf);
}

int main(int argc, char *argv[])
/* Process command line. */
{
optionInit(&argc, argv, options);
++argv;
--argc;
if (argc != 2)
    usage();
stripDotsDashes = optionExists("stripDotsDashes");
mafToFa(argv[0], argv[1]);
return 0;
}

