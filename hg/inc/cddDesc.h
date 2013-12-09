/* cddDesc.h was originally generated by the autoSql program, which also 
 * generated cddDesc.c and cddDesc.sql.  This header links the database and
 * the RAM representation of objects. */

#ifndef CDDDESC_H
#define CDDDESC_H

#define CDDDESC_NUM_COLS 6

struct cddDesc
/* Conserved Domain Description */
    {
    struct cddDesc *next;  /* Next in singly linked list. */
    unsigned cddid;	/* identifier */
    char *accession;	/* accession */
    char *cddname;	/* Name of domain */
    char *name;	/* hit name */
    char *cdddesc;	/* descriptive name */
    unsigned cddlength;	/* length */
    };

void cddDescStaticLoad(char **row, struct cddDesc *ret);
/* Load a row from cddDesc table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct cddDesc *cddDescLoad(char **row);
/* Load a cddDesc from row fetched with select * from cddDesc
 * from database.  Dispose of this with cddDescFree(). */

struct cddDesc *cddDescLoadAll(char *fileName);
/* Load all cddDesc from whitespace-separated file.
 * Dispose of this with cddDescFreeList(). */

struct cddDesc *cddDescLoadAllByChar(char *fileName, char chopper);
/* Load all cddDesc from chopper separated file.
 * Dispose of this with cddDescFreeList(). */

#define cddDescLoadAllByTab(a) cddDescLoadAllByChar(a, '\t');
/* Load all cddDesc from tab separated file.
 * Dispose of this with cddDescFreeList(). */

struct cddDesc *cddDescCommaIn(char **pS, struct cddDesc *ret);
/* Create a cddDesc out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new cddDesc */

void cddDescFree(struct cddDesc **pEl);
/* Free a single dynamically allocated cddDesc such as created
 * with cddDescLoad(). */

void cddDescFreeList(struct cddDesc **pList);
/* Free a list of dynamically allocated cddDesc's */

void cddDescOutput(struct cddDesc *el, FILE *f, char sep, char lastSep);
/* Print out cddDesc.  Separate fields with sep. Follow last field with lastSep. */

#define cddDescTabOut(el,f) cddDescOutput(el,f,'\t','\n');
/* Print out cddDesc as a line in a tab-separated file. */

#define cddDescCommaOut(el,f) cddDescOutput(el,f,',',',');
/* Print out cddDesc as a comma separated list including final comma. */

/* -------------------------------- End autoSql Generated Code -------------------------------- */

#endif /* CDDDESC_H */

