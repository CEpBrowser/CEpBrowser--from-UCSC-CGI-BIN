include ../../../inc/common.mk

L += -lm ${MYSQLLIBS}
MYLIBDIR = ../../../lib/${MACHTYPE}
MYLIBS =  ${MYLIBDIR}/jkhgap.a ${MYLIBDIR}/jkweb.a

A = bedExtendRanges
O = ${A}.o

GOODFILES = bed7.txt bed8.txt chromBoundaries.txt

compile: $(O) $(MYLIBS)
	${CC} ${COPT} ${CFLAGS} -o ${DESTDIR}${BINDIR}/${A}${EXE} $O $(MYLIBS) $L
	${STRIP} ${DESTDIR}${BINDIR}/${A}${EXE}

clean:
	rm -f $(O)

test: good
	

good:
	@for good in $(GOODFILES); do \
		echo "Processing test file: $$good"; \
		${A} hg18 259 stdin < tests/$$good; \
	done
