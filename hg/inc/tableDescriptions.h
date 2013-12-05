/* tableDescriptions.h was originally generated by the autoSql program, which also 
 * generated tableDescriptions.c and tableDescriptions.sql.  This header links the database and
 * the RAM representation of objects. */

#ifndef TABLEDESCRIPTIONS_H
#define TABLEDESCRIPTIONS_H

#define TABLEDESCRIPTIONS_NUM_COLS 3

struct tableDescriptions
/* Descriptive information about database tables from autoSql / gbdDescriptions */
    {
    struct tableDescriptions *next;  /* Next in singly linked list. */
    char *tableName;	/* Name of table (with chr*_ replaced with chrN_) */
    char *autoSqlDef;	/* Contents of autoSql (.as) table definition file */
    char *gbdAnchor;	/* Anchor for table description in gbdDescriptions.html */
    };

void tableDescriptionsStaticLoad(char **row, struct tableDescriptions *ret);
/* Load a row from tableDescriptions table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct tableDescriptions *tableDescriptionsLoad(char **row);
/* Load a tableDescriptions from row fetched with select * from tableDescriptions
 * from database.  Dispose of this with tableDescriptionsFree(). */

struct tableDescriptions *tableDescriptionsLoadAll(char *fileName);
/* Load all tableDescriptions from whitespace-separated file.
 * Dispose of this with tableDescriptionsFreeList(). */

struct tableDescriptions *tableDescriptionsLoadAllByChar(char *fileName, char chopper);
/* Load all tableDescriptions from chopper separated file.
 * Dispose of this with tableDescriptionsFreeList(). */

#define tableDescriptionsLoadAllByTab(a) tableDescriptionsLoadAllByChar(a, '\t');
/* Load all tableDescriptions from tab separated file.
 * Dispose of this with tableDescriptionsFreeList(). */

struct tableDescriptions *tableDescriptionsCommaIn(char **pS, struct tableDescriptions *ret);
/* Create a tableDescriptions out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new tableDescriptions */

void tableDescriptionsFree(struct tableDescriptions **pEl);
/* Free a single dynamically allocated tableDescriptions such as created
 * with tableDescriptionsLoad(). */

void tableDescriptionsFreeList(struct tableDescriptions **pList);
/* Free a list of dynamically allocated tableDescriptions's */

void tableDescriptionsOutput(struct tableDescriptions *el, FILE *f, char sep, char lastSep);
/* Print out tableDescriptions.  Separate fields with sep. Follow last field with lastSep. */

#define tableDescriptionsTabOut(el,f) tableDescriptionsOutput(el,f,'\t','\n');
/* Print out tableDescriptions as a line in a tab-separated file. */

#define tableDescriptionsCommaOut(el,f) tableDescriptionsOutput(el,f,',',',');
/* Print out tableDescriptions as a comma separated list including final comma. */

/* -------------------------------- End autoSql Generated Code -------------------------------- */

#endif /* TABLEDESCRIPTIONS_H */

