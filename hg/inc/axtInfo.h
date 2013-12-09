/* axtInfo.h was originally generated by the autoSql program, which also 
 * generated axtInfo.c and axtInfo.sql.  This header links the database and
 * the RAM representation of objects. */

#ifndef AXTINFO_H
#define AXTINFO_H

#ifndef JKSQL_H
#include "jksql.h"
#endif 

struct axtInfo
/* Axt alignment names and sizes */
    {
    struct axtInfo *next;  /* Next in singly linked list. */
    char species[26];	/* long name of species */
    char alignment[36];	/* name of alignment */
    char *chrom;	/* chromosome name */
    char *fileName;	/* axt  file name  */
    };

void axtInfoStaticLoad(char **row, struct axtInfo *ret);
/* Load a row from axtInfo table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct axtInfo *axtInfoLoad(char **row);
/* Load a axtInfo from row fetched with select * from axtInfo
 * from database.  Dispose of this with axtInfoFree(). */

struct axtInfo *axtInfoLoadAll(char *fileName);
/* Load all axtInfo from a tab-separated file.
 * Dispose of this with axtInfoFreeList(). */

struct axtInfo *axtInfoLoadWhere(struct sqlConnection *conn, char *table, char *where);
/* Load all axtInfo from table that satisfy where clause. The
 * where clause may be NULL in which case whole table is loaded
 * Dispose of this with axtInfoFreeList(). */

struct axtInfo *axtInfoCommaIn(char **pS, struct axtInfo *ret);
/* Create a axtInfo out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new axtInfo */

void axtInfoFree(struct axtInfo **pEl);
/* Free a single dynamically allocated axtInfo such as created
 * with axtInfoLoad(). */

void axtInfoFreeList(struct axtInfo **pList);
/* Free a list of dynamically allocated axtInfo's */

void axtInfoOutput(struct axtInfo *el, FILE *f, char sep, char lastSep);
/* Print out axtInfo.  Separate fields with sep. Follow last field with lastSep. */

#define axtInfoTabOut(el,f) axtInfoOutput(el,f,'\t','\n');
/* Print out axtInfo as a line in a tab-separated file. */

#define axtInfoCommaOut(el,f) axtInfoOutput(el,f,',',',');
/* Print out axtInfo as a comma separated list including final comma. */

#endif /* AXTINFO_H */

