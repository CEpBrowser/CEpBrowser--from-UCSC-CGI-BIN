/* linesToRa - output ra stanzas from single lines with pipe separated fields */
#include "common.h"
#include "linefile.h"
#include "options.h"

static char const rcsid[] = "$Header: /projects/compbio/cvsroot/kent/src/utils/raToLines/linesToRa.c,v 1.2 2009/01/23 23:42:39 kate Exp $";

void usage()
/* Explain usage and exit. */
{
errAbort(
  "linesToRa - generate .ra format from lines with pipe-separated fields\n"
  "usage:\n"
  "   linesToRa in.txt out.ra\n"
  );
}

static struct optionSpec options[] = {
   {NULL, 0},
};

void linesToRa(char *inFile, char *outFile)
/* Input lines with pipe-separated fields and ouptut ra stanzas */
{
struct lineFile *lf = lineFileOpen(inFile, TRUE);
FILE *of = mustOpen(outFile, "w");
char *line, *start;
char *words[256];
int wordCt;

while (lineFileNext(lf, &line, NULL))
    {
    start = skipLeadingSpaces(line);
    if (*start == 0)
        {
        fputs("\n", of);
        }
    else if (startsWith("#", start))
        {
        fputs(line, of);
        fputc('\n', of);
        }
    else
        {
        int size = ArraySize(words);
        wordCt = chopByChar(line, '|', words, size);
        if (wordCt >= size)
            errAbort("#words in line exceeds buffer size(%d): %s\n", 
                                size, line);
        int i;
        for (i = 0; i < wordCt; i++)
            {
            fputs(words[i], of);
            fputc('\n', of);
            }
        fputc('\n', of);
        }
    }
fflush(of);
carefulClose(&of);
}

int main(int argc, char *argv[])
/* Process command line. */
{
optionInit(&argc, argv, options);
if (argc != 3)
    usage();
linesToRa(argv[1], argv[2]);
return 0;
}
