/* mgcLibrary.h was originally generated by the autoSql program, which also 
 * generated mgcLibrary.c and mgcLibrary.sql.  This header links the database and
 * the RAM representation of objects. */

#ifndef MGCLIBRARY_H
#define MGCLIBRARY_H

#define MGCLIBRARY_NUM_COLS 30

struct mgcLibrary
/* table of libraries */
    {
    struct mgcLibrary *next;  /* Next in singly linked list. */
    int id_lib;	/* NCBI assigned id */
    char *flc_id;	/* library name assigned by CGAP */
    char *id_rna;	/* rna sample used to make library */
    int id_vendor;	/* id of vendor */
    int id_method;	/* lib prep method id */
    signed char normal;	/* is library normalized */
    char *commnt;	/* comments about library success or failure */
    float rate_success;	/* % success */
    float human_repeats;	/* % Human repetitive elements */
    float mito_rna;	/* % mitochondrial contamination */
    float ecoli;	/* % bacterial contamination */
    float yeast;	/* % yeast contamination */
    float mouse;	/* % mouse contamination */
    float diversity;	/* library diversity */
    float uniqueness;	/* library uniqueness */
    int genes;	/* number of genes in library */
    int discover;	/* number of genes discovered */
    int flc_disc;	/* number of genes discovered within FLC */
    int novel;	/* number of novel genes discovered */
    float future;	/* % probability of finding new genes in lib */
    float internal_primed;	/* % internal priming */
    float full_length;	/* % full length */
    float priority;	/* priority score for going forward */
    int id_unigene;	/* unigene library id */
    char *organism;	/* organism name */
    char *vector;	/* vector name */
    char *host;	/* host name */
    float vec_contam;	/* % vector contamination */
    float mean_insize;	/* mean insert size */
    char *linker;	/* linker sequence */
    };

void mgcLibraryStaticLoad(char **row, struct mgcLibrary *ret);
/* Load a row from mgcLibrary table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct mgcLibrary *mgcLibraryLoad(char **row);
/* Load a mgcLibrary from row fetched with select * from mgcLibrary
 * from database.  Dispose of this with mgcLibraryFree(). */

struct mgcLibrary *mgcLibraryLoadAll(char *fileName);
/* Load all mgcLibrary from whitespace-separated file.
 * Dispose of this with mgcLibraryFreeList(). */

struct mgcLibrary *mgcLibraryCommaIn(char **pS, struct mgcLibrary *ret);
/* Create a mgcLibrary out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new mgcLibrary */

void mgcLibraryFree(struct mgcLibrary **pEl);
/* Free a single dynamically allocated mgcLibrary such as created
 * with mgcLibraryLoad(). */

void mgcLibraryFreeList(struct mgcLibrary **pList);
/* Free a list of dynamically allocated mgcLibrary's */

void mgcLibraryOutput(struct mgcLibrary *el, FILE *f, char sep, char lastSep);
/* Print out mgcLibrary.  Separate fields with sep. Follow last field with lastSep. */

#define mgcLibraryTabOut(el,f) mgcLibraryOutput(el,f,'\t','\n');
/* Print out mgcLibrary as a line in a tab-separated file. */

#define mgcLibraryCommaOut(el,f) mgcLibraryOutput(el,f,',',',');
/* Print out mgcLibrary as a comma separated list including final comma. */

/* -------------------------------- End autoSql Generated Code -------------------------------- */

struct mgcLibraryTbl
/* table of mgcLibrary objects, hashed by id_lib */
{
    struct hash *idHash;       /* hash by id_lib */
};

struct mgcLibraryTbl *mgcLibraryTblLoad(char *fileName);
/* load a file of mgcLibrary objects, building a hash */

void mgcLibraryTblFree(struct mgcLibraryTbl **mltPtr);
/* free a mgcLibraryTbl object */

struct mgcLibrary *mgcLibraryTblFind(struct mgcLibraryTbl *mlt,
                                     int libraryId);
/* Find a mgcLibrary object by libraryId, or NULL if not found */

#endif /* MGCLIBRARY_H */

