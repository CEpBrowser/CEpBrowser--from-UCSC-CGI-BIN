/* wikiTrack.h was originally generated by the autoSql program, which also 
 * generated wikiTrack.c and wikiTrack.sql.  This header links the database and
 * the RAM representation of objects. */

#ifndef WIKITRACK_H
#define WIKITRACK_H

#ifndef JKSQL_H
#include "jksql.h"
#endif
#ifndef HTMLPAGE_H
#include "htmlPage.h"
#endif
#ifndef CART_H
#include "cart.h"
#endif

#define WIKITRACK_NUM_COLS 16

struct wikiTrack
/* wikiTrack bed 6+ structure */
    {
    struct wikiTrack *next;  /* Next in singly linked list. */
    unsigned short bin;	/* used for efficient position indexing */
    char *chrom;	/* Reference sequence chromosome or scaffold */
    unsigned chromStart;	/* Start position in chromosome */
    unsigned chromEnd;	/* End position in chromosome */
    char *name;	/* Name of item */
    unsigned score;	/* Score from 0-1000 */
    char strand[2];	/* + or - */
    char *db;	/* database for item */
    char *owner;	/* creator of item */
    char *color;	/* rgb color of item (currently unused) */
    char *class;	/* classification of item (browser group) */
    char *creationDate;	/* date item created */
    char *lastModifiedDate;	/* date item last updated */
    char *descriptionKey;	/* name of wiki description page */
    unsigned id;	/* auto-increment item ID */
    char *geneSymbol;	/* knownGene kgXref geneSymbol name */
    };

void wikiTrackStaticLoad(char **row, struct wikiTrack *ret);
/* Load a row from wikiTrack table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct wikiTrack *wikiTrackLoad(char **row);
/* Load a wikiTrack from row fetched with select * from wikiTrack
 * from database.  Dispose of this with wikiTrackFree(). */

struct wikiTrack *wikiTrackLoadAll(char *fileName);
/* Load all wikiTrack from whitespace-separated file.
 * Dispose of this with wikiTrackFreeList(). */

struct wikiTrack *wikiTrackLoadAllByChar(char *fileName, char chopper);
/* Load all wikiTrack from chopper separated file.
 * Dispose of this with wikiTrackFreeList(). */

#define wikiTrackLoadAllByTab(a) wikiTrackLoadAllByChar(a, '\t');
/* Load all wikiTrack from tab separated file.
 * Dispose of this with wikiTrackFreeList(). */

struct wikiTrack *wikiTrackLoadByQuery(struct sqlConnection *conn, char *query);
/* Load all wikiTrack from table that satisfy the query given.  
 * Where query is of the form 'select * from example where something=something'
 * or 'select example.* from example, anotherTable where example.something = 
 * anotherTable.something'.
 * Dispose of this with wikiTrackFreeList(). */

void wikiTrackSaveToDb(struct sqlConnection *conn, struct wikiTrack *el, char *tableName, int updateSize);
/* Save wikiTrack as a row to the table specified by tableName. 
 * As blob fields may be arbitrary size updateSize specifies the approx size
 * of a string that would contain the entire query. Arrays of native types are
 * converted to comma separated strings and loaded as such, User defined types are
 * inserted as NULL. Note that strings must be escaped to allow insertion into the database.
 * For example "autosql's features include" --> "autosql\'s features include" 
 * If worried about this use wikiTrackSaveToDbEscaped() */

void wikiTrackSaveToDbEscaped(struct sqlConnection *conn, struct wikiTrack *el, char *tableName, int updateSize);
/* Save wikiTrack as a row to the table specified by tableName. 
 * As blob fields may be arbitrary size updateSize specifies the approx size.
 * of a string that would contain the entire query. Automatically 
 * escapes all simple strings (not arrays of string) but may be slower than wikiTrackSaveToDb().
 * For example automatically copies and converts: 
 * "autosql's features include" --> "autosql\'s features include" 
 * before inserting into database. */ 

struct wikiTrack *wikiTrackCommaIn(char **pS, struct wikiTrack *ret);
/* Create a wikiTrack out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new wikiTrack */

void wikiTrackFree(struct wikiTrack **pEl);
/* Free a single dynamically allocated wikiTrack such as created
 * with wikiTrackLoad(). */

void wikiTrackFreeList(struct wikiTrack **pList);
/* Free a list of dynamically allocated wikiTrack's */

void wikiTrackOutput(struct wikiTrack *el, FILE *f, char sep, char lastSep);
/* Print out wikiTrack.  Separate fields with sep. Follow last field with lastSep. */

#define wikiTrackTabOut(el,f) wikiTrackOutput(el,f,'\t','\n');
/* Print out wikiTrack as a line in a tab-separated file. */

#define wikiTrackCommaOut(el,f) wikiTrackOutput(el,f,',',',');
/* Print out wikiTrack as a comma separated list including final comma. */

/* -------------------------------- End autoSql Generated Code -------------------------------- */

/* configuration variables */
#define CFG_WIKI_URL "wikiTrack.URL"
#define CFG_WIKI_BROWSER "wikiTrack.browser"
#define CFG_WIKI_EDITORS "wikiTrack.editors"
#define CFG_WIKI_DB_LIST "wikiTrack.dbList"

/* name of database table in hgcentral */
#define WIKI_TRACK_TABLE "wikiTrack"

/* trackDb settings */
#define WIKI_TRACK_LABEL "Wiki Track"
#define WIKI_TRACK_LONGLABEL "Wiki Track user annotations"
#define WIKI_TRACK_PRIORITY 99.99

/* hgc variables */
#define G_CREATE_WIKI_ITEM "htcCreateWikiItem"
#define G_ADD_WIKI_COMMENTS "htcAddWikiComments"
#define G_DELETE_WIKI_ITEM "htcDeleteWikiItem"

/* hgc and hgGene variables */
#define WIKI_NO_TEXT_RESPONSE "There is currently no text in this page"
#define ADD_ITEM_COMMENT_DEFAULT "add comments"
#define NEW_ITEM_COMMENT "wikiCommentText"
#define NEW_ITEM_SCORE "wikiItemScore"
#define NEW_ITEM_COMMENT_DEFAULT "enter description and comments"
#define NEW_ITEM_NAME "wikiDefaultName"
#define NEW_ITEM_COLOR "wikiItemColor"
#define NEW_ITEM_STRAND "wikiItemStrand"
#define NEW_ITEM_CLASS "wikiItemClass"
#define NEW_ITEM_CATEGORY "[[Category:Genome Annotation]]"
#define ITEM_NOT_CLASSIFIED "Not classified"
#define NO_ITEM_COMMENT_SUPPLIED "(no initial description supplied)"
#define DEFAULT_BROWSER "genome.ucsc.edu"
#define TEST_EMAIL_VERIFIED "GenomeAnnotation:TestEmailVerified"
#define EMAIL_NEEDS_TO_BE_VERIFIED \
	"You must confirm your e-mail address before editing"
#define USER_PREFERENCES_MESSAGE \
    "Please set and validate your e-mail address through your"
#define GENE_CLASS "Genes and Gene Prediction Tracks"
#define LOGIN_EXPIRED \
    "You do not have permission to edit pages, for the following reasons:"

boolean wikiTrackEnabled(char *database, char **wikiUserName);
/*determine if wikiTrack can be used, and is this user logged into the wiki ?*/

char *wikiTrackGetCreateSql(char *tableName);
/* return sql create statement for wiki track with tableName */

char *wikiDbName();
/* return name of database where wiki track is located
    currently this is central.db but the future may be configurable */

struct sqlConnection *wikiConnect();
/* connect to db where wikiTrack table is located
 *	currently this is hConnectCentral() but the future may be
 *	configurable */

void wikiDisconnect(struct sqlConnection **pConn);
/* disconnect from wikiTrack table database */

struct wikiTrack *findWikiItemId(char *wikiItemId);
/* given a wikiItemId return the row from the table */

struct wikiTrack *findWikiItemByGeneSymbol(char *db, char *geneSymbol);
/* given a db and UCSC known gene geneSymbol, find the wiki item */

struct wikiTrack *findWikiItemByName(char *db, char *name);
/* given a db,name pair return the row from the table, can return NULL */

void htmlCloneFormVarSet(struct htmlForm *parent,
	struct htmlForm *clone, char *name, char *val);
/* clone form variable from parent, with new value,
 * if *val is NULL, clone val from parent
 */

char *fetchWikiRawText(char *descriptionKey);
/* fetch page from wiki in raw form as it is in the edit form */

char *fetchWikiRenderedText(char *descriptionKey);
/* fetch page from wiki in rendered form, strip it of edit URLs,
 *	html comments, and test for actual proper return.
 *  returned string can be freed after use */

void displayComments(struct wikiTrack *item);
/* display the rendered comments for this item */

void createPageHelp(char *pageFileName);
/* find the specified html help page and display it, or issue a missing
 *	page message so the site administrator can fix it.
 */

struct htmlPage *fetchEditPage(char *descriptionKey);
/* fetch edit page for descriptionKey page name in wiki */

void prefixComments(struct wikiTrack *item, char *comments, char *userName,
    char *seqName, int winStart, int winEnd, char *database,
	char *extraHeader, char *extraTag);
/* add comments at the beginning of an existing wiki item */

void addDescription(struct wikiTrack *item, char *userName,
    char *seqName, int winStart, int winEnd, struct cart *cart,
	char *database, char *extraHeader, char *extraTag);
/* add description to the end of an existing wiki item */

char *encodedReturnUrl(char *(*hgUrl)());
/* Return a CGI-encoded URL with hgsid.  Free when done.
 *	The given function hgUrl() will construct the actual cgi binary URL
 */

boolean emailVerified(boolean showMessage);
/* TRUE indicates email has been verified for this wiki user */

boolean isWikiEditor(char *userName);
/* check if user name is on list of editors */

char *wikiUrl(struct wikiTrack *item);
/* construct a URL to the wiki page for the specified item
	free the returned string when done with it.  */

#endif /* WIKITRACK_H */
