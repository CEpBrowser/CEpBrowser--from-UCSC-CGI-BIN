# Build encode validator

include ../../../inc/common.mk

SCRIPT_FILES = \
	doEncodeValidate.pl
CONFIG_FILES = \
	fields.ra \
	labs.ra \
	hg18_chromInfo.txt \
        expVars.ra

CV = cv.ra
CVDIR=../../makeDb/trackDb/cv/alpha

PIPELINE_PATH=/hive/groups/encode/dcc/pipeline
CONFIG_DIR = ${PIPELINE_PATH}/${PIPELINE_DIR}/config

all:
	@${MAKE} --no-print-directory SCRIPTS=${HOME}/bin/scripts PIPELINE_DIR=encpipeline_${USER} scripts config

alpha:
	@${MAKE} --no-print-directory SCRIPTS=${SCRIPTS} PIPELINE_DIR=encpipeline_beta scripts config 

install:
	@${MAKE} --no-print-directory SCRIPTS=${ENCODE_PIPELINE_BIN} PIPELINE_DIR=encpipeline_prod scripts config 

# recursive targets, arguments:
#   SCRIPTS PIPELINE_DIR

scripts: ${SCRIPT_FILES:%=${SCRIPTS}/%}

${SCRIPTS}/%: %
	@mkdir -p $(dir $@)
	chmod +x $<
	perl -c $< 2>&1
	cp -p $< $@.tmp
	mv -f $@.tmp $@

config: ${CONFIG_FILES:%=${CONFIG_DIR}/%} ${CONFIG_DIR}/${CV}

${CONFIG_DIR}/${CV}: ${CVDIR}/${CV}
	cp -p ${CVDIR}/${CV} ${CONFIG_DIR}/cv.ra.tmp
	mv -f  ${CONFIG_DIR}/cv.ra.tmp ${CONFIG_DIR}/cv.ra

${CONFIG_DIR}/%: config/%
	@mkdir -p $(dir $@)
	cp -p $< $@.tmp
	mv -f $@.tmp $@

test:
	cd test && ${MAKE}

clean::
	echo nothing to clean in hg/encode/encodeValidate/
