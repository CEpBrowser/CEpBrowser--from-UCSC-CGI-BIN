/* sangRange.h was originally generated by the autoSql program, which also 
 * generated sangRange.c and sangRange.sql.  This header links the database and the RAM 
 * representation of objects. */

#ifndef SANGRANGE_H
#define SANGRANGE_H

struct sangRange
/* Information on a size ranges of a Sanger O+O insert */
    {
    struct sangRange *next;  /* Next in singly linked list. */
    char name[8];	/* name of range */
    unsigned minSize;	/* minimum size */
    unsigned maxSize;	/* maximum size */
    };

void sangRangeStaticLoad(char **row, struct sangRange *ret);
/* Load a row from sangRange table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct sangRange *sangRangeLoad(char **row);
/* Load a sangRange from row fetched with select * from sangRange
 * from database.  Dispose of this with sangRangeFree(). */

struct sangRange *sangRangeCommaIn(char **pS, struct sangRange *ret);
/* Create a sangRange out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new sangRange */

void sangRangeFree(struct sangRange **pEl);
/* Free a single dynamically allocated sangRange such as created
 * with sangRangeLoad(). */

void sangRangeFreeList(struct sangRange **pList);
/* Free a list of dynamically allocated sangRange's */

void sangRangeOutput(struct sangRange *el, FILE *f, char sep, char lastSep);
/* Print out sangRange.  Separate fields with sep. Follow last field with lastSep. */

#define sangRangeTabOut(el,f) sangRangeOutput(el,f,'\t','\n');
/* Print out sangRange as a line in a tab-separated file. */

#define sangRangeCommaOut(el,f) sangRangeOutput(el,f,',',',');
/* Print out sangRange as a comma separated list including final comma. */

#endif /* SANGRANGE_H */

