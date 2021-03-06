/* Handle details pages for wiggle tracks. */

#include "common.h"
#include "wiggle.h"
#include "cart.h"
#include "hgc.h"
#include "hCommon.h"
#include "hgColors.h"
#include "bigBed.h"
#include "hui.h"

static char const rcsid[] = "$Id: bigBedClick.c,v 1.11 2010/05/11 01:43:28 kent Exp $";


static void bigBedClick(char *fileName, struct trackDb *tdb, 
		     char *item, int start, int bedSize)
/* Handle click in generic bigBed track. */
{
char *chrom = cartString(cart, "c");

/* Open BigWig file and get interval list. */
struct bbiFile *bbi = bigBedFileOpen(fileName);
struct lm *lm = lmInit(0);
struct bigBedInterval *bbList = bigBedIntervalQuery(bbi, chrom, winStart, winEnd, 0, lm);

/* Get bedSize if it's not already defined. */
if (bedSize == 0)
    bedSize = bbi->definedFieldCount;

/* Find particular item in list - matching start, and item if possible. */
struct bigBedInterval *bbMatch = NULL, *bb;
for (bb = bbList; bb != NULL; bb = bb->next)
    {
    if (bb->start == start)
        {
	if (bedSize > 3)
	    {
	    char *name = cloneFirstWordInLine(bb->rest);
	    boolean match = sameString(name, item);
	    freez(&name);
	    if (match)
	        {
		bbMatch = bb;
		break;
		}
	    }
	else
	    {
	    bbMatch = bb;
	    break;
	    }
	}
    }

if (bbMatch != NULL)
    {
    int seq1Seq2Fields = 0;
    // check for seq1 and seq2 in columns 7+8 (eg, pairedTagAlign)
    boolean seq1Seq2 = sameOk(trackDbSetting(tdb, BASE_COLOR_USE_SEQUENCE), "seq1Seq2");
    if (seq1Seq2 && bedSize == 6)
	seq1Seq2Fields = 2;
    char *fields[bedSize+seq1Seq2Fields];
    char startBuf[16], endBuf[16];
    char *rest = cloneString(bbMatch->rest);
    int bbFieldCount = bigBedIntervalToRow(bbMatch, chrom, startBuf, endBuf, fields,
					   bedSize+seq1Seq2Fields); 
    if (bbFieldCount != bedSize+seq1Seq2Fields)
        {
	errAbort("Disagreement between trackDb field count (%d) and %s fieldCount (%d)", 
		bedSize, fileName, bbFieldCount);
	}
    struct bed *bed = bedLoadN(fields, bedSize);
    if (bedSize >= 4)
	printCustomUrl(tdb, item, TRUE);
    bedPrintPos(bed, bedSize, tdb);

    // display seq1 and seq2 
    if (seq1Seq2 && bedSize+seq1Seq2Fields == 8)
        printf("<table><tr><th>Sequence 1</th><th>Sequence 2</th></tr>"
	       "<tr><td> %s </td><td> %s </td></tr></table>", fields[6], fields[7]);
    else if (isNotEmpty(rest))
	{
	char *restFields[256];
	int restCount = chopTabs(rest, restFields);
	int restBedFields = bedSize - 3;
	if (restCount > restBedFields)
	    {
	    int i;
	    printf("<B>Non-BED fields:</B> ");
	    for (i = restBedFields;  i < restCount;  i++)
		printf("%s%s", (i > 0 ? "\t" : ""), restFields[i]);
	    printf("<BR>\n");
	    }
	}
    }
else
    {
    printf("No item %s starting at %d\n", emptyForNull(item), start);
    }

lmCleanup(&lm);
bbiFileClose(&bbi);
}

void genericBigBedClick(struct sqlConnection *conn, struct trackDb *tdb, 
		     char *item, int start, int bedSize)
/* Handle click in generic bigBed track. */
{
char query[256];
safef(query, sizeof(query), "select fileName from %s", tdb->table);
char *fileName = sqlQuickString(conn, query);
if (fileName == NULL)
    errAbort("Missing fileName in %s table", tdb->table);
bigBedClick(fileName, tdb, item, start, bedSize);
}

void bigBedCustomClick(struct trackDb *tdb)
/* Display details for BigWig custom tracks. */
{
char *fileName = trackDbSetting(tdb, "bigDataUrl");
char *item = cartOptionalString(cart, "i");
int start = cartInt(cart, "o");
bigBedClick(fileName, tdb, item, start, 0);
}
