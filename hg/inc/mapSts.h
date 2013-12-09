/* mapSts.h was originally generated by the autoSql program, which also 
 * generated mapSts.c and mapSts.sql.  This header links the database and the RAM 
 * representation of objects. */

#ifndef MAPSTS_H
#define MAPSTS_H

struct mapSts
/* An STS based map in relationship to golden path */
    {
    struct mapSts *next;  /* Next in singly linked list. */
    char *chrom;	/* Chromosome */
    unsigned chromStart;	/* Start position in chrom */
    unsigned chromEnd;	/* End position in chrom */
    char *name;	/* Name of STS marker */
    unsigned score;	/* Score of a marker - depends on how many contigs it hits */
    unsigned identNo;	/* Identification number of STS */
    char *rhChrom;	/* Chromosome number from the RH map - 0 if there is none */
    float distance;	/* Distance from the RH map */
    char *ctgAcc;	/* Contig accession number */
    char *otherAcc;	/* Accession number of other contigs that the marker hits */
    };

void mapStsStaticLoad(char **row, struct mapSts *ret);
/* Load a row from mapSts table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct mapSts *mapStsLoad(char **row);
/* Load a mapSts from row fetched with select * from mapSts
 * from database.  Dispose of this with mapStsFree(). */

struct mapSts *mapStsCommaIn(char **pS, struct mapSts *ret);
/* Create a mapSts out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new mapSts */

void mapStsFree(struct mapSts **pEl);
/* Free a single dynamically allocated mapSts such as created
 * with mapStsLoad(). */

void mapStsFreeList(struct mapSts **pList);
/* Free a list of dynamically allocated mapSts's */

void mapStsOutput(struct mapSts *el, FILE *f, char sep, char lastSep);
/* Print out mapSts.  Separate fields with sep. Follow last field with lastSep. */

#define mapStsTabOut(el,f) mapStsOutput(el,f,'\t','\n');
/* Print out mapSts as a line in a tab-separated file. */

#define mapStsCommaOut(el,f) mapStsOutput(el,f,',',',');
/* Print out mapSts as a comma separated list including final comma. */

#endif /* MAPSTS_H */

