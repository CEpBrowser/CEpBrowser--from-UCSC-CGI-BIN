/* mahoney.h was originally generated by the autoSql program, which also 
 * generated mahoney.c and mahoney.sql.  This header links the database and
 * the RAM representation of objects. */

#ifndef MAHONEY_H
#define MAHONEY_H

#define MAHONEY_NUM_COLS 19

struct mahoney
/* Tabular data from Paul Gray/Mahoney spread sheet */
    {
    struct mahoney *next;  /* Next in singly linked list. */
    char *empty;	/* Always blank */
    int mtf;	/* mahoney id */
    char *sameAs;	/* comma sep list of ids */
    char *geneName;	/* HUGO name if available */
    char *domain;	/* Domain that marks it as a transcription factor */
    char *genbank;	/* genbank (including refSeq) ID */
    char *locusId;	/* locus link id */
    char *unigene;	/* unigene id */
    char *fragSize;	/* PCR product size */
    char *linzyme;	/* Restriction enzyme to linearize */
    char *rnaPol;	/* DNA->RNA enzyme, usually T7 */
    char *cloneVector;	/* Cloning vector */
    char *seqVerified;	/* X if true */
    char *startLoc;	/* start base pair location */
    char *endLoc;	/* end base pair location */
    char *fPrimer;	/* Forward primer */
    char *rPrimer;	/* Reverse primer */
    char *fAdaptor;	/* Start adapter enzyme */
    char *rAdaptor;	/* End adapter enzyme */
    };

void mahoneyStaticLoad(char **row, struct mahoney *ret);
/* Load a row from mahoney table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct mahoney *mahoneyLoad(char **row);
/* Load a mahoney from row fetched with select * from mahoney
 * from database.  Dispose of this with mahoneyFree(). */

struct mahoney *mahoneyLoadAll(char *fileName);
/* Load all mahoney from whitespace-separated file.
 * Dispose of this with mahoneyFreeList(). */

struct mahoney *mahoneyLoadAllByChar(char *fileName, char chopper);
/* Load all mahoney from chopper separated file.
 * Dispose of this with mahoneyFreeList(). */

#define mahoneyLoadAllByTab(a) mahoneyLoadAllByChar(a, '\t');
/* Load all mahoney from tab separated file.
 * Dispose of this with mahoneyFreeList(). */

struct mahoney *mahoneyCommaIn(char **pS, struct mahoney *ret);
/* Create a mahoney out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new mahoney */

void mahoneyFree(struct mahoney **pEl);
/* Free a single dynamically allocated mahoney such as created
 * with mahoneyLoad(). */

void mahoneyFreeList(struct mahoney **pList);
/* Free a list of dynamically allocated mahoney's */

void mahoneyOutput(struct mahoney *el, FILE *f, char sep, char lastSep);
/* Print out mahoney.  Separate fields with sep. Follow last field with lastSep. */

#define mahoneyTabOut(el,f) mahoneyOutput(el,f,'\t','\n');
/* Print out mahoney as a line in a tab-separated file. */

#define mahoneyCommaOut(el,f) mahoneyOutput(el,f,',',',');
/* Print out mahoney as a comma separated list including final comma. */

/* -------------------------------- End autoSql Generated Code -------------------------------- */

#endif /* MAHONEY_H */

