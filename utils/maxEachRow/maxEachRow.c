/* maxEachRow - Output numeric value for each row. */
#include "common.h"
#include "linefile.h"
#include "hash.h"
#include "options.h"

static char const rcsid[] = "$Id: maxEachRow.c,v 1.2 2005/10/27 03:53:24 kent Exp $";

void usage()
/* Explain usage and exit. */
{
errAbort(
  "maxEachRow - Output numeric value for each row\n"
  "usage:\n"
  "   maxEachRow input output\n"
  "options:\n"
  "   -xxx=XXX\n"
  );
}

static struct optionSpec options[] = {
   {NULL, 0},
};

void maxEachRow(char *inName, char *outName)
/* maxEachRow - Output numeric value for each row. */
{
struct lineFile *lf = lineFileOpen(inName, TRUE);
FILE *f = mustOpen(outName, "w");
char *line;
if (lineFileNextReal(lf, &line))
    {
    int rowSize = chopByWhite(line, NULL, 0);
    char **row;
    AllocArray(row, rowSize+1);
    for (;;)
        {
	int thisSize = chopByWhite(line, row, rowSize+1);
	int i;
	double maxVal;
	if (thisSize != rowSize)
	    errAbort("First line has %d words, but line %d has %d words",
	    	rowSize, lf->lineIx, thisSize);
	maxVal = atof(row[0]);
	for (i=1; i<rowSize; ++i)
	    {
	    double val = atof(row[i]);
	    if (val > maxVal)
	        maxVal = val;
	    }
	fprintf(f, "%f\n", maxVal);
	if (!lineFileNextReal(lf, &line))
	    break;
	}
    freez(&row);
    }
carefulClose(&f);
lineFileClose(&lf);
}

int main(int argc, char *argv[])
/* Process command line. */
{
optionInit(&argc, argv, options);
if (argc != 3)
    usage();
maxEachRow(argv[1], argv[2]);
return 0;
}
