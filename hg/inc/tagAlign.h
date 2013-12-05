/* tagAlign.h was originally generated by the autoSql program, which also 
 * generated tagAlign.c and tagAlign.sql.  This header links the database and
 * the RAM representation of objects. */

#ifndef TAGALIGN_H
#define TAGALIGN_H

#define TAGALIGN_NUM_COLS 6

struct tagAlign
/* Tag Alignment format (BED 3+) */
    {
    struct tagAlign *next;  /* Next in singly linked list. */
    char *chrom;	/* Reference sequence chromosome or scaffold */
    unsigned chromStart;	/* Start position in chromosome */
    unsigned chromEnd;	/* End position in chromosome */
    char *sequence;	/* Sequence of this read */
    int score;	/* Indicates mismatches, quality, or other measurement (0-1000) */
    char strand;	/* Orientation of this read (+ or -) */
    };

void tagAlignStaticLoad(char **row, struct tagAlign *ret);
/* Load a row from tagAlign table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct tagAlign *tagAlignLoad(char **row);
/* Load a tagAlign from row fetched with select * from tagAlign
 * from database.  Dispose of this with tagAlignFree(). */

struct tagAlign *tagAlignLoadAll(char *fileName);
/* Load all tagAlign from whitespace-separated file.
 * Dispose of this with tagAlignFreeList(). */

struct tagAlign *tagAlignLoadAllByChar(char *fileName, char chopper);
/* Load all tagAlign from chopper separated file.
 * Dispose of this with tagAlignFreeList(). */

#define tagAlignLoadAllByTab(a) tagAlignLoadAllByChar(a, '\t');
/* Load all tagAlign from tab separated file.
 * Dispose of this with tagAlignFreeList(). */

struct tagAlign *tagAlignCommaIn(char **pS, struct tagAlign *ret);
/* Create a tagAlign out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new tagAlign */

void tagAlignFree(struct tagAlign **pEl);
/* Free a single dynamically allocated tagAlign such as created
 * with tagAlignLoad(). */

void tagAlignFreeList(struct tagAlign **pList);
/* Free a list of dynamically allocated tagAlign's */

void tagAlignOutput(struct tagAlign *el, FILE *f, char sep, char lastSep);
/* Print out tagAlign.  Separate fields with sep. Follow last field with lastSep. */

#define tagAlignTabOut(el,f) tagAlignOutput(el,f,'\t','\n');
/* Print out tagAlign as a line in a tab-separated file. */

#define tagAlignCommaOut(el,f) tagAlignOutput(el,f,',',',');
/* Print out tagAlign as a comma separated list including final comma. */

/* -------------------------------- End autoSql Generated Code -------------------------------- */

#endif /* TAGALIGN_H */

