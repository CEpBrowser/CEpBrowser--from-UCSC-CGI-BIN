/* geneBands.h was originally generated by the autoSql program, which also 
 * generated geneBands.c and geneBands.sql.  This header links the database and
 * the RAM representation of objects. */

#ifndef GENEBANDS_H
#define GENEBANDS_H

struct geneBands
/* Band locations of known genes */
    {
    struct geneBands *next;  /* Next in singly linked list. */
    char *name;	/* Name of gene - hugo if possible */
    char *mrnaAcc;	/* RefSeq mrna accession */
    int count;	/* Number of times this maps to the genome */
    char **bands;	/* List of bands this maps to */
    };

struct geneBands *geneBandsLoad(char **row);
/* Load a geneBands from row fetched with select * from geneBands
 * from database.  Dispose of this with geneBandsFree(). */

struct geneBands *geneBandsLoadAll(char *fileName);
/* Load all geneBands from a tab-separated file.
 * Dispose of this with geneBandsFreeList(). */

struct geneBands *geneBandsLoadWhere(struct sqlConnection *conn, char *table, char *where);
/* Load all geneBands from table that satisfy where clause. The
 * where clause may be NULL in which case whole table is loaded
 * Dispose of this with geneBandsFreeList(). */

struct geneBands *geneBandsCommaIn(char **pS, struct geneBands *ret);
/* Create a geneBands out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new geneBands */

void geneBandsFree(struct geneBands **pEl);
/* Free a single dynamically allocated geneBands such as created
 * with geneBandsLoad(). */

void geneBandsFreeList(struct geneBands **pList);
/* Free a list of dynamically allocated geneBands's */

void geneBandsOutput(struct geneBands *el, FILE *f, char sep, char lastSep);
/* Print out geneBands.  Separate fields with sep. Follow last field with lastSep. */

#define geneBandsTabOut(el,f) geneBandsOutput(el,f,'\t','\n');
/* Print out geneBands as a line in a tab-separated file. */

#define geneBandsCommaOut(el,f) geneBandsOutput(el,f,',',',');
/* Print out geneBands as a comma separated list including final comma. */

#endif /* GENEBANDS_H */

