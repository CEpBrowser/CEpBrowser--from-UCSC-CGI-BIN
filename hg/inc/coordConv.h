/**
 \file

 coordConv.h was originally generated by the autoSql program, which also 
 generated coordConv.c and coordConv.sql.  This header links the database and
 the RAM representation of objects. 

 <p>Specifications from Jim's email:
 <pre>
 Date: Thu, 28 Jun 2001 09:54:05 -0700
 From: Jim Kent <jim_kent@pacbell.net>
 To: tom <tom@cyber-dyne.com>, genecats@cse.ucsc.edu
 Subject: Re: [Genecats] cross-lifting hg coordinate upgrader
 
 Chuck - the first thing to do is just to make a libary routine
 with a simple command line tester that takes for input
 a single set of coordinates,  an old .nib directory, and
 a new .nib directory,  and returns a list of matching
 places in the new .nib directory.   The library routine
 can be called repeatedly if you want to process a
 list of input coordinates.
 
 It might well at *some* point be worthwhile to apply
 this routine, and a blast output parser, to convert
 from a NCBI blast return to a list of browser
 coordinates.   It sounds like it would be useful
 to Tom and others, but we have to wiegh it
 against all the other things.   In particular
 we may not need to do it because NCBI may
 link directly from their mapviewer to our
 genome browser.
 
 </pre>

*/

#ifndef COORDCONV_H
#define COORDCONV_H

/** Specify a location in a particular draft of the genome */
struct coordConv
    {
    struct coordConv *next;  /** Next in singly linked list. */
    char *chrom;	/** Chromosome Name */
    unsigned chromStart;	/** Start in Chromosome */
    unsigned chromEnd;	/** End in Chromosome */
    char *version;	/** Version of Assembly, i.e. hg4, hg5 */
    char *date;	/** Date of version, i.e. Dec 12, 2000 */
    char *nibDir;	/** Direcory where nib files for assembly are stored */
    char *optional;	/** Optional Information */
    };

/** Report stucture containing information for conversions */
struct coordConvRep
{
    struct coordConvRep *next; /** next in list */
    struct coordConv *from; /** origninal coordinates to change */
    struct coordConv *to; /** placement of old coordConv on new draft genome */
    struct dnaSeq *midSeq,*upSeq,*downSeq; /** 3 in order from 5' to 3' */
    unsigned midStart,upStart,downStart; /** starting position of dnaSeqs in old chrom */
    int seqSize; /** Size of sequence being aligned to genome. */
    struct psl *midPsl,*upPsl,*downPsl; /** alignments for each of the dnaSeqs */
    char *msg; /** optional message or url */
    boolean good; /** TRUE if "to" coordConv is valid, i.e. conversion was successful */
};

void coordConvStaticLoad(char **row, struct coordConv *ret);
/** Load a row from coordConv table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct coordConv *coordConvLoad(char **row);
/** Load a coordConv from row fetched with select * from coordConv
 * from database.  Dispose of this with coordConvFree(). */

struct coordConv *coordConvLoadAll(char *fileName);
/** Load all coordConv from a tab-separated file.
 * Dispose of this with coordConvFreeList(). */

struct coordConv *coordConvCommaIn(char **pS, struct coordConv *ret);
/** Create a coordConv out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new coordConv */

void coordConvFree(struct coordConv **pEl);
/** Free a single dynamically allocated coordConv such as created
 * with coordConvLoad(). */

void coordConvFreeList(struct coordConv **pList);
/** Free a list of dynamically allocated coordConv's */

void coordConvOutput(struct coordConv *el, FILE *f, char sep, char lastSep);
/** Print out coordConv.  Separate fields with sep. Follow last field with lastSep. */

#define coordConvTabOut(el,f) coordConvOutput(el,f,'\t','\n');
/** Print out coordConv as a line in a tab-separated file. */

#define coordConvCommaOut(el,f) coordConvOutput(el,f,',',',');
/** Print out coordConv as a comma separated list including final comma. */

/*-------------End autoSql Generated Section------------------*/


struct coordConvRep *coordConvConvertPos(char *chr, unsigned chromStart, unsigned chromEnd, char *oldDb, char *newDb,
					 char *blatHost, char *port, char *nibDir);
/**
  convert coordinates from old draft to new draft. If sucessful,
  coordConvRep->to returned will have new coordinates and
  coordConvRep->good == TRUE. Otherwise coordConvRep->to returned
  will have chromosome="unknown" and coordConvRep->good == FALSE, also
  optional will contain
  errormesg. Remember to free with coordConvReportFree().  */

void coordConvRepFree(struct coordConvRep **pEl);
/** free a single dynamically allocated coordConvRep such as created by coordConvConvertPos(). */

void coordConvRepFreeList(struct coordConvRep **pList);
/** free a list of  dynamically allocated coordConvRep */ 

#endif /* COORDCONV_H */

