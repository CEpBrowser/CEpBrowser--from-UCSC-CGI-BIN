/* estOrientInfo.h was originally generated by the autoSql program, which also 
 * generated estOrientInfo.c and estOrientInfo.sql.  This header links the database and
 * the RAM representation of objects. */

#ifndef ESTORIENTINFO_H
#define ESTORIENTINFO_H

struct lm;
struct sqlConnection;

#define EST_ORIENT_INFO_NUM_COLS 9

struct estOrientInfo
/* Extra information on ESTs - calculated by polyInfo program */
    {
    struct estOrientInfo *next;  /* Next in singly linked list. */
    char *chrom;	/* Human chromosome or FPC contig */
    unsigned chromStart;	/* Start position in chromosome */
    unsigned chromEnd;	/* End position in chromosome */
    char *name;	/* Accession of EST */
    short intronOrientation;	/* Orientation of introns with respect to EST */
    short sizePolyA;	/* Number of trailing A's */
    short revSizePolyA;	/* Number of trailing A's on reverse strand */
    short signalPos;	/* Position of start of polyA signal relative to end of EST or 0 if no signal */
    short revSignalPos;	/* PolyA signal position on reverse strand if any */
    };

void estOrientInfoStaticLoad(char **row, struct estOrientInfo *ret);
/* Load a row from estOrientInfo table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct estOrientInfo *estOrientInfoLoad(char **row);
/* Load a estOrientInfo from row fetched with select * from estOrientInfo
 * from database.  Dispose of this with estOrientInfoFree(). */

struct estOrientInfo *estOrientInfoLoadAll(char *fileName);
/* Load all estOrientInfo from a tab-separated file.
 * Dispose of this with estOrientInfoFreeList(). */

struct estOrientInfo *estOrientInfoLoadWhere(struct sqlConnection *conn, char *table, char *where);
/* Load all estOrientInfo from table that satisfy where clause. The
 * where clause may be NULL in which case whole table is loaded
 * Dispose of this with estOrientInfoFreeList(). */

struct estOrientInfo *estOrientInfoCommaIn(char **pS, struct estOrientInfo *ret);
/* Create a estOrientInfo out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new estOrientInfo */

void estOrientInfoFree(struct estOrientInfo **pEl);
/* Free a single dynamically allocated estOrientInfo such as created
 * with estOrientInfoLoad(). */

void estOrientInfoFreeList(struct estOrientInfo **pList);
/* Free a list of dynamically allocated estOrientInfo's */

void estOrientInfoOutput(struct estOrientInfo *el, FILE *f, char sep, char lastSep);
/* Print out estOrientInfo.  Separate fields with sep. Follow last field with lastSep. */

#define estOrientInfoTabOut(el,f) estOrientInfoOutput(el,f,'\t','\n');
/* Print out estOrientInfo as a line in a tab-separated file. */

#define estOrientInfoCommaOut(el,f) estOrientInfoOutput(el,f,',',',');
/* Print out estOrientInfo as a comma separated list including final comma. */

/* ----- end autoSql generated part --------------- */

struct estOrientInfo *estOrientInfoLoadLm(char **row, struct lm *lm);
/* Load a estOrientInfo row into local memory struct. */

char *estOrientInfoGetCreateSql(char *table, int chromIdxLen);
/* Get SQL to create an estOrientInfo table. chromIdxLen is the number of
 * chars at that start of chrom to use for the index. */

#endif /* ESTORIENTINFO_H */

