include ../../../inc/common.mk

# recursive target to do install to DEST, with extra excludes EXCL.

CSS_FILES=HGStyle.css autocomplete.css blueStyle.css floretStyle.css jquery-ui.css jquery.contextmenu.css ui.dropdownchecklist.css 

user:
	if test -d ${DOCUMENTROOT}-${USER}; then \
	    ${MAKE} doInstall DEST=${DOCUMENTROOT}-${USER}/style; \
	fi

alpha:
	${GITUP}
	${MAKE} doInstall DEST=${DOCUMENTROOT}/style

beta:
	${GITUP} 
	${MAKE} doInstall DEST=${DOCUMENTROOT}/style

clean:

compile:

install:
	${MAKE} doInstall DEST=${DOCUMENTROOT}/style

doInstall:
	@mkdir -p ${DEST}/
	./cpAndLinkToResourceFiles.pl -destDir=${DEST} ${CSS_FILES}
