/* dbRIP.h was originally generated by the autoSql program, which also 
 * generated dbRIP.c and dbRIP.sql.  This header links the database and
 * the RAM representation of objects. */

#ifndef DBRIP_H
#define DBRIP_H

#ifndef JKSQL_H
#include "jksql.h"
#endif

#define DBRIP_NUM_COLS 22

struct dbRIP
/* Retrotransposon Insertion Polymorphisms in Humans */
    {
    struct dbRIP *next;  /* Next in singly linked list. */
    char *chrom;	/* Chromosome (or contig, scaffold, etc.) */
    unsigned chromStart;	/* Start position in chromosome */
    unsigned chromEnd;	/* End position in chromosome */
    char *name;	/* Database ID */
    unsigned score;	/* Score from 0-1000 */
    char strand[2];	/* + or - */
    char *originalId;	/* original ID */
    char *forwardPrimer;	/* forward Primer */
    char *reversePrimer;	/* reverse Primer */
    char *polyClass;	/* Repeat Class */
    char *polyFamily;	/* Repeat Family */
    char *polySubfamily;	/* Repeat Sub-family */
    char *polySeq;	/* sequence */
    char *polySource;	/* source */
    char *reference;	/* reference */
    char *ascertainingMethod;	/* Ascertaining Method */
    char *remarks;	/* remarks */
    float tm;	/* temperature */
    int filledSize;	/* filled size */
    int emptySize;	/* empty size */
    char *disease;	/* disease */
    char *genoRegion;	/* genome region */
    };

void dbRIPStaticLoad(char **row, struct dbRIP *ret);
/* Load a row from dbRIP table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct dbRIP *dbRIPLoad(char **row);
/* Load a dbRIP from row fetched with select * from dbRIP
 * from database.  Dispose of this with dbRIPFree(). */

struct dbRIP *dbRIPLoadAll(char *fileName);
/* Load all dbRIP from whitespace-separated file.
 * Dispose of this with dbRIPFreeList(). */

struct dbRIP *dbRIPLoadAllByChar(char *fileName, char chopper);
/* Load all dbRIP from chopper separated file.
 * Dispose of this with dbRIPFreeList(). */

#define dbRIPLoadAllByTab(a) dbRIPLoadAllByChar(a, '\t');
/* Load all dbRIP from tab separated file.
 * Dispose of this with dbRIPFreeList(). */

struct dbRIP *dbRIPLoadByQuery(struct sqlConnection *conn, char *query);
/* Load all dbRIP from table that satisfy the query given.  
 * Where query is of the form 'select * from example where something=something'
 * or 'select example.* from example, anotherTable where example.something = 
 * anotherTable.something'.
 * Dispose of this with dbRIPFreeList(). */

void dbRIPSaveToDb(struct sqlConnection *conn, struct dbRIP *el, char *tableName, int updateSize);
/* Save dbRIP as a row to the table specified by tableName. 
 * As blob fields may be arbitrary size updateSize specifies the approx size
 * of a string that would contain the entire query. Arrays of native types are
 * converted to comma separated strings and loaded as such, User defined types are
 * inserted as NULL. Note that strings must be escaped to allow insertion into the database.
 * For example "autosql's features include" --> "autosql\'s features include" 
 * If worried about this use dbRIPSaveToDbEscaped() */

void dbRIPSaveToDbEscaped(struct sqlConnection *conn, struct dbRIP *el, char *tableName, int updateSize);
/* Save dbRIP as a row to the table specified by tableName. 
 * As blob fields may be arbitrary size updateSize specifies the approx size.
 * of a string that would contain the entire query. Automatically 
 * escapes all simple strings (not arrays of string) but may be slower than dbRIPSaveToDb().
 * For example automatically copies and converts: 
 * "autosql's features include" --> "autosql\'s features include" 
 * before inserting into database. */ 

struct dbRIP *dbRIPCommaIn(char **pS, struct dbRIP *ret);
/* Create a dbRIP out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new dbRIP */

void dbRIPFree(struct dbRIP **pEl);
/* Free a single dynamically allocated dbRIP such as created
 * with dbRIPLoad(). */

void dbRIPFreeList(struct dbRIP **pList);
/* Free a list of dynamically allocated dbRIP's */

void dbRIPOutput(struct dbRIP *el, FILE *f, char sep, char lastSep);
/* Print out dbRIP.  Separate fields with sep. Follow last field with lastSep. */

#define dbRIPTabOut(el,f) dbRIPOutput(el,f,'\t','\n');
/* Print out dbRIP as a line in a tab-separated file. */

#define dbRIPCommaOut(el,f) dbRIPOutput(el,f,',',',');
/* Print out dbRIP as a comma separated list including final comma. */

/* ---------------- End autoSql Generated Code ---------------------- */

/* items for trackUi options and filters	*/
#define GENO_REGION	"dbRIP.genoRegion"
#define POLY_SOURCE	"dbRIP.polySource"
#define POLY_SUBFAMILY	"dbRIP.polySubFamily"
#define ETHNIC_GROUP	"dbRIP.ethnicGroup"
#define ETHNIC_GROUP_EXCINC	"dbRIP.ethnicExcInc"
#define dbRIP_DISEASE	"dbRIP.disease"

#define GENO_REGION_DEFAULT	"any"
#define POLY_SOURCE_DEFAULT	"don't care"
#define POLY_SUBFAMILY_DEFAULT	"any"
#define ETHNIC_GROUP_DEFAULT	"any"
#define ETHNIC_NOT_DEFAULT	"include"
#define DISEASE_DEFAULT	"don't care"

#define ALLELE_FREQ_HI	"alleleFreqHi"
#define ALLELE_FREQ_LOW	"alleleFreqLow"

#endif /* DBRIP_H */

