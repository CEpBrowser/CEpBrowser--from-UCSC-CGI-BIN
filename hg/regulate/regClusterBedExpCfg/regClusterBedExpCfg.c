/* regClusterBedExpCfg - Create config file for hgBedsToBedExps from list of files.. */
#include "common.h"
#include "linefile.h"
#include "hash.h"
#include "options.h"
#include "obscure.h"
#include "sqlNum.h"
#include "hmmstats.h"

static char const rcsid[] = "$Id: regClusterBedExpCfg.c,v 1.2 2010/05/05 00:50:37 kent Exp $";

boolean encodeList = FALSE;
boolean tabList = FALSE;
char *cellLetter = NULL;

#define SCORE_COL_IX 6

struct hash *cellLetterHash;

void usage()
/* Explain usage and exit. */
{
errAbort(
  "regClusterBedExpCfg - Create config file for hgBedsToBedExps from list of files.\n"
  "usage:\n"
  "   regClusterBedExpCfg inputFileList output.cfg\n"
  "options:\n"
  "   -cellLetter=file.tab - two column file of form <letter> <name> for cell lines\n"
  "           If not present the first letter of the cell name will be used\n"
  "   -tabList - the inputFileList is in three column format of form:\n"
  "           <fileName> <cell> <factor>\n"
  "   -encodeList - the inputFileList is of format you might get from cut and paste of\n"
  "        encode downloads page - tab separated with following columns:\n"
  "             <relDate> <fileName> <fileSize> <submitDate> <metadata>\n"
  "        where the metadata component is in the format:\n"
  "              this=that; that=two words; that=whatever\n"
  "        and the antibody and cell tags in the metadata are used\n"
  );
}

static struct optionSpec options[] = {
   {"encodeList", OPTION_BOOLEAN},
   {"tabList", OPTION_BOOLEAN},
   {"cellLetter", OPTION_STRING},
   {NULL, 0},
};

char *cellAbbreviation(char *cell)
/* Return abbreviated version of cell-name */
{
if (cellLetterHash != NULL)
    {
    char *val = hashFindVal(cellLetterHash, cell);
    if (val == NULL)
        errAbort("cell %s isn't in %s", cell, cellLetter);
    return val;
    }
else
    {
    static char buf[2];
    buf[0] = cell[0];
    buf[1] = 0;
    return buf;
    }
}

int commonPrefixSize(struct slName *list)
/* Return length of common prefix */
{
if (list == NULL)
    return 0;
int commonSize = strlen(list->name);
struct slName *el, *lastEl = list;
for (el = list->next; el != NULL; el = el->next)
    {
    int sameSize = countSame(el->name, lastEl->name);
    commonSize = min(sameSize, commonSize);
    lastEl = el;
    }
return commonSize;
}

int countSameAtEnd(char *a, char *b)
/* Count number of characters at end of strings that are same in each string. */
{
int count = 0;
char *aEnd = a + strlen(a);
char *bEnd = b + strlen(b);
while  (--aEnd >= a && --bEnd >= b)
    {
    if (*aEnd != *bEnd)
        break;
    ++count;
    }
return count;
}

int commonSuffixSize(struct slName *list)
/* Return length of common suffix */
{
if (list == NULL)
    return 0;
int commonSize = strlen(list->name);
struct slName *el, *lastEl = list;
for (el = list->next; el != NULL; el = el->next)
    {
    int sameSize = countSameAtEnd(el->name, lastEl->name);
    commonSize = min(sameSize, commonSize);
    lastEl = el;
    }
return commonSize;
}

void camelParseTwo(char *in, char **retA, char **retB)
/* Parse out CamelCased in into a and b.  */
{
char *s = in;
char *aStart = s;
char *bStart = NULL;
char c;
while ((c = *(++s)) != 0)
    {
    if (isupper(c))
        {
	bStart = s;
	break;
        }
    }
if (bStart == NULL)
   errAbort("Couldn't find start of second word in %s", in);
*retA = cloneStringZ(aStart, bStart - aStart);
*retB = cloneString(bStart);
}

double calcNormScoreFactor(char *fileName, int scoreCol)
/* Figure out what to multiply things by to get a nice browser score (0-1000) */
{
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[scoreCol+1];
double sum = 0, sumSquares = 0;
int n = 0;
double minVal=0, maxVal=0;
while (lineFileRow(lf, row))
    {
    double x = sqlDouble(row[scoreCol]);
    if (n == 0)
        minVal = maxVal = x;
    if (x < minVal) minVal = x;
    if (x > maxVal) maxVal = x;
    sum += x;
    sumSquares += x*x;
    n += 1;
    }
lineFileClose(&lf);
double std = calcStdFromSums(sum, sumSquares, n);
double mean = sum/n;
double highEnd = mean + std;
if (highEnd > maxVal) highEnd = maxVal;
return 1000.0/highEnd;
}

void makeConfigFromFileList(char *input, char *output)
/* makeConfigFromFileList - Create config file for hgBedsToBedExps from list of files.. */
{
FILE *f = mustOpen(output, "w");
struct slName *in, *inList = readAllLines(input);
int commonPrefix = commonPrefixSize(inList);
int commonSuffix = commonSuffixSize(inList);
for (in = inList; in != NULL; in = in->next)
    {
    char *s = in->name;
    int len = strlen(s);
    char *midString = cloneStringZ(s+commonPrefix, len - commonPrefix - commonSuffix);
    char *factor, *cell;
    camelParseTwo(midString, &cell, &factor);
    fprintf(f, "%s\t%s\t", factor, cell);
    fprintf(f, "%s\t", cellAbbreviation(cell));
    fprintf(f, "file\t%d\t", SCORE_COL_IX);
    fprintf(f, "%g\t", calcNormScoreFactor(in->name, SCORE_COL_IX));
    fprintf(f, "%s\n", in->name);
    }
carefulClose(&f);
}

void makeConfigFromTabList(char *input, char *output)
/* makeConfigFromFileList - Create config file for hgBedsToBedExps from list of file/cell/ab. */
{
struct lineFile *lf = lineFileOpen(input, TRUE);
char *row[3];
FILE *f = mustOpen(output, "w");

while (lineFileRow(lf, row))
    {
    char *fileName = row[0];
    char *cell = row[1];
    char *factor = row[2];
    verbose(2, "%s\n", fileName);
    fprintf(f, "%s\t%s\t", factor, cell);
    fprintf(f, "%s\t", cellAbbreviation(cell));
    fprintf(f, "file\t%d\t", SCORE_COL_IX);
    fprintf(f, "%g\t", calcNormScoreFactor(fileName, SCORE_COL_IX));
    fprintf(f, "%s\n", fileName);
    }
lineFileClose(&lf);
carefulClose(&f);
}

void makeConfigFromEncodeList(char *input, char *output)
/* create config file for hgBedsToBedExps from tab-separated file of format
 *         <relDate> <fileName> <fileSize> <submitDate> <metadata> */
{
FILE *f = mustOpen(output, "w");
struct lineFile *lf = lineFileOpen(input, TRUE);
char *line;

while (lineFileNextReal(lf, &line))
    {
    /* Parse out line into major components. */
    char *releaseDate = nextWord(&line);
    char *fileName = nextWord(&line);
    char *fileSize = nextWord(&line);
    char *submitDate = nextWord(&line);
    char *metadata = trimSpaces(line);
    if (isEmpty(metadata))
        errAbort("line %d of %s is truncated", lf->lineIx, lf->fileName);

    verbose(2, "releaseDate=%s; fileName=%s; fileSize=%s; submitDate=%s; %s\n", 
    	releaseDate, fileName, fileSize, submitDate, metadata);


    /* Loop through metadata looking for cell and antibody.  Metadata
     * is in format this=that; that=two words; that=whatever */
    char *cell = NULL, *antibody = NULL;
    for (;;)
        {
	/* Find terminating semicolon if any replace it with zero, and
	 * note position for next time around loop. */
	metadata = skipLeadingSpaces(metadata);
	if (isEmpty(metadata))
	    break;
	char *semi = strchr(metadata, ';');
	if (semi != NULL)
	   *semi++ = 0;

	/* Parse out name/value pair. */
	char *name = metadata;
	char *value = strchr(metadata, '=');
	if (value == NULL)
	   errAbort("Missing '=' in metadata after tag %s in line %d of %s", 
	   	name, lf->lineIx, lf->fileName);
	*value++ = 0;
	name = trimSpaces(name);
	value = trimSpaces(value);

	/* Look for our tags. */
	if (sameString(name, "cell"))
	    cell = value;
	else if (sameString(name, "antibody"))
	    antibody = value;

	metadata = semi;
	}
    if (cell == NULL) 
        errAbort("No cell in metadata line %d of %s", lf->lineIx, lf->fileName);
    if (antibody == NULL) 
        errAbort("No antibody in metadata line %d of %s", lf->lineIx, lf->fileName);

    fprintf(f, "%s\t%s\t", antibody, cell);
    fprintf(f, "%s\t", cellAbbreviation(cell));
    fprintf(f, "file\t%d\t", SCORE_COL_IX);
    fprintf(f, "%g\t", calcNormScoreFactor(fileName, SCORE_COL_IX));
    fprintf(f, "%s\n", fileName);
    }
carefulClose(&f);
}

void regClusterBedExpCfg(char *input, char *output)
/* regClusterBedExpCfg - Create config file for hgBedsToBedExps from list of files.. */
{
if (cellLetter)
    cellLetterHash = hashTwoColumnFile(cellLetter);
if (encodeList)
    makeConfigFromEncodeList(input, output);
else if (tabList)
    makeConfigFromTabList(input, output);
else
    makeConfigFromFileList(input, output);
}
 
int main(int argc, char *argv[])
/* Process command line. */
{
optionInit(&argc, argv, options);
if (argc != 3)
    usage();
encodeList = optionExists("encodeList");
tabList = optionExists("tabList");
cellLetter = optionVal("cellLetter", cellLetter);
regClusterBedExpCfg(argv[1], argv[2]);
return 0;
}
