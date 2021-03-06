/* hgsqlTableDate - touch file with date from table. */
#include "common.h"
#include "linefile.h"
#include "hash.h"
#include "options.h"
#include "jksql.h"
#include "utime.h"
#include "hdb.h"

static char const rcsid[] = "$Id: hgsqlTableDate.c,v 1.1 2010/06/03 23:18:41 braney Exp $";

void usage()
/* Explain usage and exit. */
{
errAbort(
  "hgsqlTableDate - touch file with date from table\n"
  "usage:\n"
  "   hgsqlTableDate database table file\n"
  "options:\n"
  );
}

static struct optionSpec options[] = {
   {NULL, 0},
};

void hgsqlTableDate(char *database, char *table, char *file)
/* hgsqlTableDate - touch file with date from table. */
{
struct sqlConnection *conn = hAllocConn(database);
time_t tableTime = sqlTableUpdateTime(conn, table);
struct utimbuf buf;

buf.actime = tableTime;
buf.modtime = tableTime;

if (utime(file, &buf) < 0)

    errAbort("utime failed. %s:%s\n",file, strerror(errno));
}

int main(int argc, char *argv[])
/* Process command line. */
{
optionInit(&argc, argv, options);
if (argc != 4)
    usage();
hgsqlTableDate(argv[1],argv[2],argv[3]);
return 0;
}
