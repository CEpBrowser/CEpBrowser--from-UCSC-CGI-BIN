include ../../inc/common.mk


O = catUncomment.o 

catUncomment: $(O)
	${CC} ${COPT} ${CFLAGS} -o ${BINDIR}/catUncomment $O ../../lib/$(MACHTYPE)/jkweb.a
	${STRIP} ${BINDIR}/catUncomment${EXE}

clean::
	rm -f ${O}
