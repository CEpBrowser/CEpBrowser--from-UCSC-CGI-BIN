# Build all directories in utils
# test comment
# 	$Id: makefile,v 1.21 2010/06/04 00:12:42 larrym Exp $

include ../../inc/common.mk


SCRIPT_FILES = \
	dumpDb.pl \
	mergeOverlapBed4.pl

# List of directories to build
USE_DIRS = $(DIRS)

DIRS = \
	bedWeedOverlapping \
	chromGraphFromBin \
	chromGraphToBin \
	crTreeIndexBed \
	crTreeSearchBed \
	gapToLift \
	oligoMatch \
	positionalTblCheck \
	safePush \
	toDev64 \
	twoBitMask \
	gff3ToGenePred \
	gff3ToPsl \
	gtfToGenePred \
	automation \
	refreshNamedSessionCustomTracks \
	refSeqGet \
	tdbQuery \
	wigBedToStep \
	pslUniq \
	makeTrackIndex

TEST_DIRS = \
	gff3ToGenePred \
	gff3ToPsl \
	gtfToGenePred \
	refSeqGet


all:: utils

utils: $(USE_DIRS:%=%.utils)
%.utils:
	(cd $* && $(MAKE))

scripts: $(SCRIPT_FILES:%=%.scripts)
%.scripts:
	chmod +x $*
	rm -f ${SCRIPTS}/$*
	cp -p $* ${SCRIPTS}/$*

alpha: scripts all

test::	${TEST_DIRS:%=%.test}
%.test:
	(cd $* && ${MAKE} test)

clean:: $(USE_DIRS:%=%.clean)
	- find . -name '*.o' -exec rm {} \;
%.clean:
	(cd $* && ${MAKE} clean)

