/* segSplitPairwise - Split a segment file pairwise. */
#include "common.h"
#include "hash.h"
#include "linefile.h"
#include "obscure.h"
#include "options.h"
#include "seg.h"

static char const rcsid[] = "$Id: segSplitPairwise.c,v 1.2 2008/04/25 17:26:31 rico Exp $";

void usage()
/* Explain usage and exit. */
{
errAbort(
  "segSplitPairwise - Split a segment file pairwise\n"
  "usage:\n"
  "   segSplitPairwise in.seg out.seg\n"
  "options:\n"
  "   -ref=<S>  Use <S> as the reference species.\n"
  "             Pairs are generated by matching the reference species with\n"
  "             every other species in the same segment block.\n"
  "             (default = first species seen in in.seg)\n"
  "   -number   Number the newly created blocks based on the name of the\n"
  "             block they came from.  If the blocks are not named, they\n"
  "             will be named BlockN (N = 1, 2, 3, ...)\n"
  );
}

static struct optionSpec options[] = {
	{"ref", OPTION_STRING},
	{"number", OPTION_BOOLEAN},
	{NULL, 0},
};

static char    *ref   = NULL;
static boolean number = FALSE;


void segSplitPairwise(char *inSeg, char *outSeg)
/* segSplitPairwise - Split a segment file pairwise. */
{
struct segFile *sf = segOpen(inSeg);
FILE *of = mustOpen(outSeg, "w");
struct segBlock *sb;
struct segBlock newSb;
struct segComp *refComp, *sc, *refSc, *newSc;
char *splitName = NULL;
int sNum, bNum = 1;

segWriteStart(of);

while ((sb = segNext(sf)) != NULL)
	{
	/* Set ref if it wasn't set on the commandline. */
	if (ref == NULL && ((ref = segFirstCompSpecies(sb, '.')) == NULL))
		errAbort("ref is not set and the first segment block has no "
			"components.");

	/* Find and clone the reference species component. */
	refComp = segFindCompSpecies(sb, ref, '.');
	refSc   = cloneSegComp(refComp);

	sNum = 1;
	for (sc = sb->components; sc != NULL; sc = sc->next)
		{
		if (sc == refComp)
			continue;

		/* Clone the current component. */
		newSc       = cloneSegComp(sc);
		newSc->next = NULL;

		/* Point the reference component to the newly cloned component. */
		refSc->next = newSc;

		/* Set up the segment block to hold the two components above. */
		if (number)
			{
			if (sb->name == NULL)
				{
				AllocArray(sb->name, 6 + digitsBaseTen(bNum));
				sprintf(sb->name, "Block%d", bNum);
				}
			AllocArray(splitName, strlen(sb->name) + digitsBaseTen(sNum) + 2);
			sprintf(splitName, "%s.%d", sb->name, sNum++);
			newSb.name = splitName;
			}
		else
			newSb.name = sb->name;

		newSb.val        = sb->val;
		newSb.components = refSc;

		/* Output this new block. */
		segWrite(of, &newSb);

		if (number)
			freeMem(splitName);

		/* Free the cloned component. */
		segCompFree(&newSc);
		}

	/* Free the cloned reference component. */
	segCompFree(&refSc);

	segBlockFree(&sb);
	bNum++;
	}

segWriteEnd(of);
carefulClose(&of);
segFileFree(&sf);
}

int main(int argc, char *argv[])
/* Process command line. */
{
optionInit(&argc, argv, options);

if (argc != 3)
    usage();

ref    = optionVal("ref", ref);
number = optionExists("number");

segSplitPairwise(argv[1], argv[2]);

return(EXIT_SUCCESS);
}
