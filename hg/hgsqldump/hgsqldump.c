/* hgsqldump - Execute mysqldump using passwords from .hg.conf. */
#include "common.h"
#include "options.h"
#include "sqlProg.h"

static char const rcsid[] = "$Id: hgsqldump.c,v 1.7 2008/03/01 08:08:22 jzhu Exp $";

void usage()
/* Explain usage and exit. */
{
errAbort(
  "hgsqldump - Execute mysqldump using passwords from .hg.conf\n"
  "usage:\n"
  "   hgsqldump [OPTIONS] database [tables]\n"
  "or:\n"
  "   hgsqldump [OPTIONS] --databases [OPTIONS] DB1 [DB2 DB3 ...]\n"
  "or:\n"
  "   hgsqldump [OPTIONS] --all-databases [OPTIONS]\n"
  "Generally anything in command line is passed to mysqldump\n"
  "\tafter an implicit '-u user -ppassword\n"
  "See also: mysqldump\n"
  "Note: directory for results must be writable by mysql.  i.e. 'chmod 777 .'\n"
  "Which is a security risk, so remember to change permissions back after use.\n"
  "e.g.: hgsqldump --all -c --tab=. cb1"
  "\n"
  );
}

int main(int argc, char *argv[])
/* Process command line. */
{
if (argc <= 1)
    usage();

sqlExecProg("mysqldump", NULL, argc-1, argv+1);
return 0;  /* never reaches here */
}
