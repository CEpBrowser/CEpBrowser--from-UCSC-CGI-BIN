/* Test program to see if synmap is reading correctly */
#include "common.h"
#include "synMap.h"

static char const rcsid[] = "$Id: synMapTest.c,v 1.2 2003/05/06 07:22:35 kate Exp $";

void usage()
{
errAbort("synMapTest - tries to read in a synMap file like those produced\n"
	 "by Sanja and Robert for the mouse-human synteny map.\n"
	 "usage:\n"
	 "\tsynMapTest <file>\n");
}

int main(int argc, char *argv[])
{
struct synMap *smList = NULL;
if(argc != 2)
    usage();
warn("Loading from file %s.", argv[1]);
smList = synMapLoadAll(argv[1]);
warn("Loaded %d synMaps.", slCount(smList));
synMapFreeList(&smList);
warn("Done.");
return 0;
}
