/* cutter.h was originally generated by the autoSql program, which also 
 * generated cutter.c and cutter.sql.  This header links the database and
 * the RAM representation of objects. */

#ifndef CUTTER_H
#define CUTTER_H

#ifndef JKSQL_H
#include "jksql.h"
#endif

#define CUTTER_NUM_COLS 14

struct cutter
/* Restriction Enzymes */
    {
    struct cutter *next;  /* Next in singly linked list. */
    char *name;	/* Name of Enzyme */
    unsigned size;	/* Size of recognition sequence */
    unsigned matchSize;	/* size without N's */
    char *seq;	/* Recognition sequence */
    unsigned cut;	/* Cut site on the plus strand */
    int overhang;	/* Overhang size and direction */
    unsigned char palindromic;	/* 1 if it's panlidromic, 0 if not. */
    unsigned char semicolon;	/* REBASE record: 0 if primary isomer, 1 if not. */
    unsigned numSciz;	/* Number of isoschizomers */
    char **scizs;	/* Names of isoschizomers */
    unsigned numCompanies;	/* Number of companies selling this enzyme */
    char *companies;	/* Company letters */
    unsigned numRefs;	/* Number of references */
    unsigned *refs;	/* Reference numbers */
    };

struct cutter *cutterLoad(char **row);
/* Load a cutter from row fetched with select * from cutter
 * from database.  Dispose of this with cutterFree(). */

struct cutter *cutterLoadAll(char *fileName);
/* Load all cutter from whitespace-separated file.
 * Dispose of this with cutterFreeList(). */

struct cutter *cutterLoadAllByChar(char *fileName, char chopper);
/* Load all cutter from chopper separated file.
 * Dispose of this with cutterFreeList(). */

#define cutterLoadAllByTab(a) cutterLoadAllByChar(a, '\t');
/* Load all cutter from tab separated file.
 * Dispose of this with cutterFreeList(). */

struct cutter *cutterLoadByQuery(struct sqlConnection *conn, char *query);
/* Load all cutter from table that satisfy the query given.  
 * Where query is of the form 'select * from example where something=something'
 * or 'select example.* from example, anotherTable where example.something = 
 * anotherTable.something'.
 * Dispose of this with cutterFreeList(). */

void cutterSaveToDb(struct sqlConnection *conn, struct cutter *el, char *tableName, int updateSize);
/* Save cutter as a row to the table specified by tableName. 
 * As blob fields may be arbitrary size updateSize specifies the approx size
 * of a string that would contain the entire query. Arrays of native types are
 * converted to comma separated strings and loaded as such, User defined types are
 * inserted as NULL. Note that strings must be escaped to allow insertion into the database.
 * For example "autosql's features include" --> "autosql\'s features include" 
 * If worried about this use cutterSaveToDbEscaped() */

void cutterSaveToDbEscaped(struct sqlConnection *conn, struct cutter *el, char *tableName, int updateSize);
/* Save cutter as a row to the table specified by tableName. 
 * As blob fields may be arbitrary size updateSize specifies the approx size.
 * of a string that would contain the entire query. Automatically 
 * escapes all simple strings (not arrays of string) but may be slower than cutterSaveToDb().
 * For example automatically copies and converts: 
 * "autosql's features include" --> "autosql\'s features include" 
 * before inserting into database. */ 

struct cutter *cutterCommaIn(char **pS, struct cutter *ret);
/* Create a cutter out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new cutter */

void cutterFree(struct cutter **pEl);
/* Free a single dynamically allocated cutter such as created
 * with cutterLoad(). */

void cutterFreeList(struct cutter **pList);
/* Free a list of dynamically allocated cutter's */

void cutterOutput(struct cutter *el, FILE *f, char sep, char lastSep);
/* Print out cutter.  Separate fields with sep. Follow last field with lastSep. */

#define cutterTabOut(el,f) cutterOutput(el,f,'\t','\n');
/* Print out cutter as a line in a tab-separated file. */

#define cutterCommaOut(el,f) cutterOutput(el,f,',',',');
/* Print out cutter as a comma separated list including final comma. */

/* -------------------------------- End autoSql Generated Code -------------------------------- */

struct slName *findIsoligamers(struct cutter *enz, struct cutter *enzList);
/* Find isoligamers to an enzyme in a list of enzymes.  */

struct cutter *readGcg(char *gcgFile);
/* Parse a GCG file and load it into cutters format. */

struct bed *matchEnzymes(struct cutter *cutters, struct dnaSeq *seq, int startOffset);
/* Match the enzymes to sequence and return a bed list in all cases. */

void cullCutters(struct cutter **enzList, boolean semicolon, struct slName *justThese, int matchSize);
/* Reduce the list of enzymes based on different options. */

#endif /* CUTTER_H */

