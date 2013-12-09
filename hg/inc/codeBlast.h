/* codeBlast.h was originally generated by the autoSql program, which also 
 * generated codeBlast.c and codeBlast.sql.  This header links the database and
 * the RAM representation of objects. */

#ifndef CODEBLAST_H
#define CODEBLAST_H

#define CODEBLAST_NUM_COLS 8

struct codeBlast
/* Table storing the codes and positional info for blast runs. */
    {
    struct codeBlast *next;  /* Next in singly linked list. */
    short bin;	/* bin for browser speed up */
    char *chrom;	/* Chromosome or FPC contig */
    unsigned chromStart;	/* Start position in chromosome */
    unsigned chromEnd;	/* End position in chromosome */
    char *name;	/* Name of item */
    unsigned score;	/* Score (0-1000) */
    char strand[2];	/* Strand */
    char *code;	/* BLAST code scores */
    };

void codeBlastStaticLoad(char **row, struct codeBlast *ret);
/* Load a row from codeBlast table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct codeBlast *codeBlastLoad(char **row);
/* Load a codeBlast from row fetched with select * from codeBlast
 * from database.  Dispose of this with codeBlastFree(). */

struct codeBlast *codeBlastLoadAll(char *fileName);
/* Load all codeBlast from whitespace-separated file.
 * Dispose of this with codeBlastFreeList(). */

struct codeBlast *codeBlastLoadAllByChar(char *fileName, char chopper);
/* Load all codeBlast from chopper separated file.
 * Dispose of this with codeBlastFreeList(). */

#define codeBlastLoadAllByTab(a) codeBlastLoadAllByChar(a, '\t');
/* Load all codeBlast from tab separated file.
 * Dispose of this with codeBlastFreeList(). */

struct codeBlast *codeBlastCommaIn(char **pS, struct codeBlast *ret);
/* Create a codeBlast out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new codeBlast */

void codeBlastFree(struct codeBlast **pEl);
/* Free a single dynamically allocated codeBlast such as created
 * with codeBlastLoad(). */

void codeBlastFreeList(struct codeBlast **pList);
/* Free a list of dynamically allocated codeBlast's */

void codeBlastOutput(struct codeBlast *el, FILE *f, char sep, char lastSep);
/* Print out codeBlast.  Separate fields with sep. Follow last field with lastSep. */

#define codeBlastTabOut(el,f) codeBlastOutput(el,f,'\t','\n');
/* Print out codeBlast as a line in a tab-separated file. */

#define codeBlastCommaOut(el,f) codeBlastOutput(el,f,',',',');
/* Print out codeBlast as a comma separated list including final comma. */

/* -------------------------------- End autoSql Generated Code -------------------------------- */

#endif /* CODEBLAST_H */

