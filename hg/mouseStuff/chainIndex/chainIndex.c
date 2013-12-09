/* chainIndex - Create simple two column file index for chain. */
#include "common.h"
#include "linefile.h"
#include "hash.h"
#include "options.h"
#include "chain.h"

static char const rcsid[] = "$Id: chainIndex.c,v 1.1 2005/11/17 16:50:46 kent Exp $";

void usage()
/* Explain usage and exit. */
{
errAbort(
  "chainIndex - Create simple two column file index for chain\n"
  "usage:\n"
  "   chainIndex in.chain out.index\n"
  );
}

static struct optionSpec options[] = {
   {NULL, 0},
};

void chainIndex(char *inChain, char *outIndex)
/* chainIndex - Create simple two column file index for chain. */
{
struct lineFile *lf = lineFileOpen(inChain, TRUE);
FILE *f = mustOpen(outIndex, "w");
struct chain *chain, *lastChain = NULL;
long pos = 0;
struct hash *uniqHash = hashNew(16);

while ((chain = chainRead(lf)) != NULL)
    {
    if (lastChain == NULL || !sameString(chain->tName, lastChain->tName))
	{
	if (hashLookup(uniqHash, chain->tName))
	    {
	    errAbort("%s is not sorted, %s repeated with intervening %s", 
	    	inChain, chain->tName, lastChain->tName);
	    }
	hashAddInt(uniqHash, chain->tName, pos);
        fprintf(f, "%lx\t%s\n", pos, chain->tName);
	}
    chainFree(&lastChain);
    lastChain = chain;
    pos = lineFileTell(lf);
    }
}

int main(int argc, char *argv[])
/* Process command line. */
{
optionInit(&argc, argv, options);
if (argc != 3)
    usage();
chainIndex(argv[1], argv[2]);
return 0;
}
