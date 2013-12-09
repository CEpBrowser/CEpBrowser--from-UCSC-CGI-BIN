/* pushQ.c was originally generated by the autoSql program, which also 
 * generated pushQ.h and pushQ.sql.  This module links the database and
 * the RAM representation of objects. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "pushQ.h"

static char const rcsid[] = "$Id: pushQ.c,v 1.14 2009/12/02 21:42:04 galt Exp $";

void pushQStaticLoad(char **row, struct pushQ *ret)
/* Load a row from pushQ table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

safecpy(ret->qid, sizeof(ret->qid), row[0]);
safecpy(ret->pqid, sizeof(ret->pqid), row[1]);
safecpy(ret->priority, sizeof(ret->priority), row[2]);
ret->rank = sqlUnsigned(row[3]);
safecpy(ret->qadate, sizeof(ret->qadate), row[4]);
safecpy(ret->newYN, sizeof(ret->newYN), row[5]);
ret->track = row[6];
ret->dbs = row[7];
ret->tbls = row[8];
ret->cgis = row[9];
ret->files = row[10];
ret->sizeMB = sqlUnsigned(row[11]);
safecpy(ret->currLoc, sizeof(ret->currLoc), row[12]);
safecpy(ret->makeDocYN, sizeof(ret->makeDocYN), row[13]);
safecpy(ret->onlineHelp, sizeof(ret->onlineHelp), row[14]);
safecpy(ret->ndxYN, sizeof(ret->ndxYN), row[15]);
safecpy(ret->joinerYN, sizeof(ret->joinerYN), row[16]);
ret->stat = row[17];
safecpy(ret->sponsor, sizeof(ret->sponsor), row[18]);
safecpy(ret->reviewer, sizeof(ret->reviewer), row[19]);
safecpy(ret->extSource, sizeof(ret->extSource), row[20]);
ret->openIssues = row[21];
ret->notes = row[22];
safecpy(ret->pushState, sizeof(ret->pushState), row[23]);
safecpy(ret->initdate, sizeof(ret->initdate), row[24]);
safecpy(ret->lastdate, sizeof(ret->lastdate), row[25]);
ret->bounces = sqlUnsigned(row[26]);
safecpy(ret->lockUser, sizeof(ret->lockUser), row[27]);
safecpy(ret->lockDateTime, sizeof(ret->lockDateTime), row[28]);
ret->releaseLog = row[29];
ret->featureBits = row[30];
ret->releaseLogUrl = row[31];
}

struct pushQ *pushQLoad(char **row)
/* Load a pushQ from row fetched with select * from pushQ
 * from database.  Dispose of this with pushQFree(). */
{
struct pushQ *ret;

AllocVar(ret);
safecpy(ret->qid, sizeof(ret->qid), row[0]);
safecpy(ret->pqid, sizeof(ret->pqid), row[1]);
safecpy(ret->priority, sizeof(ret->priority), row[2]);
ret->rank = sqlUnsigned(row[3]);
safecpy(ret->qadate, sizeof(ret->qadate), row[4]);
safecpy(ret->newYN, sizeof(ret->newYN), row[5]);
ret->track = cloneString(row[6]);
ret->dbs = cloneString(row[7]);
ret->tbls = cloneString(row[8]);
ret->cgis = cloneString(row[9]);
ret->files = cloneString(row[10]);
ret->sizeMB = sqlUnsigned(row[11]);
safecpy(ret->currLoc, sizeof(ret->currLoc), row[12]);
safecpy(ret->makeDocYN, sizeof(ret->makeDocYN), row[13]);
safecpy(ret->onlineHelp, sizeof(ret->onlineHelp), row[14]);
safecpy(ret->ndxYN, sizeof(ret->ndxYN), row[15]);
safecpy(ret->joinerYN, sizeof(ret->joinerYN), row[16]);
ret->stat = cloneString(row[17]);
safecpy(ret->sponsor, sizeof(ret->sponsor), row[18]);
safecpy(ret->reviewer, sizeof(ret->reviewer), row[19]);
safecpy(ret->extSource, sizeof(ret->extSource), row[20]);
ret->openIssues = cloneString(row[21]);
ret->notes = cloneString(row[22]);
safecpy(ret->pushState, sizeof(ret->pushState), row[23]);
safecpy(ret->initdate, sizeof(ret->initdate), row[24]);
safecpy(ret->lastdate, sizeof(ret->lastdate), row[25]);
ret->bounces = sqlUnsigned(row[26]);
safecpy(ret->lockUser, sizeof(ret->lockUser), row[27]);
safecpy(ret->lockDateTime, sizeof(ret->lockDateTime), row[28]);
ret->releaseLog = cloneString(row[29]);
ret->featureBits = cloneString(row[30]);
ret->releaseLogUrl = cloneString(row[31]);
return ret;
}

struct pushQ *pushQLoadAll(char *fileName) 
/* Load all pushQ from a whitespace-separated file.
 * Dispose of this with pushQFreeList(). */
{
struct pushQ *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[32];

while (lineFileRow(lf, row))
    {
    el = pushQLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct pushQ *pushQLoadAllByChar(char *fileName, char chopper) 
/* Load all pushQ from a chopper separated file.
 * Dispose of this with pushQFreeList(). */
{
struct pushQ *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[32];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = pushQLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct pushQ *pushQLoadByQuery(struct sqlConnection *conn, char *query)
/* Load all pushQ from table that satisfy the query given.  
 * Where query is of the form 'select * from example where something=something'
 * or 'select example.* from example, anotherTable where example.something = 
 * anotherTable.something'.
 * Dispose of this with pushQFreeList(). */
{
struct pushQ *list = NULL, *el;
struct sqlResult *sr;
char **row;

sr = sqlGetResult(conn, query);
while ((row = sqlNextRow(sr)) != NULL)
    {
    el = pushQLoad(row);
    slAddHead(&list, el);
    }
slReverse(&list);
sqlFreeResult(&sr);
return list;
}

void pushQSaveToDb(struct sqlConnection *conn, struct pushQ *el, char *tableName, int updateSize)
/* Save pushQ as a row to the table specified by tableName. 
 * As blob fields may be arbitrary size updateSize specifies the approx size
 * of a string that would contain the entire query. Arrays of native types are
 * converted to comma separated strings and loaded as such, User defined types are
 * inserted as NULL. Note that strings must be escaped to allow insertion into the database.
 * For example "autosql's features include" --> "autosql\'s features include" 
 * If worried about this use pushQSaveToDbEscaped() */
{
struct dyString *update = newDyString(updateSize);
dyStringPrintf(update, "insert into %s values ( '%s','%s','%s',%u,'%s','%s','%s','%s',%s,'%s',%s,%u,'%s','%s','%s','%s','%s','%s','%s','%s','%s',%s,%s,'%s','%s','%s',%u,'%s','%s',%s,%s,%s)", 
	tableName,  el->qid,  el->pqid,  el->priority,  el->rank,  el->qadate,  el->newYN,  el->track,  el->dbs,  el->tbls,  el->cgis,  el->files,  el->sizeMB,  el->currLoc,  el->makeDocYN,  el->onlineHelp,  el->ndxYN,  el->joinerYN,  el->stat,  el->sponsor,  el->reviewer,  el->extSource,  el->openIssues,  el->notes,  el->pushState,  el->initdate,  el->lastdate,  el->bounces,  el->lockUser,  el->lockDateTime,  el->releaseLog,  el->featureBits,  el->releaseLogUrl);
sqlUpdate(conn, update->string);
freeDyString(&update);
}

void pushQSaveToDbEscaped(struct sqlConnection *conn, struct pushQ *el, char *tableName, int updateSize)
/* Save pushQ as a row to the table specified by tableName. 
 * As blob fields may be arbitrary size updateSize specifies the approx size.
 * of a string that would contain the entire query. Automatically 
 * escapes all simple strings (not arrays of string) but may be slower than pushQSaveToDb().
 * For example automatically copies and converts: 
 * "autosql's features include" --> "autosql\'s features include" 
 * before inserting into database. */ 
{
struct dyString *update = newDyString(updateSize);
char  *qid, *pqid, *priority, *qadate, *newYN, *track, *dbs, *tbls, *cgis, *files, *currLoc, *makeDocYN, *onlineHelp, *ndxYN, *joinerYN, *stat, *sponsor, *reviewer, *extSource, *openIssues, *notes, *pushState, *initdate, *lastdate, *lockUser, *lockDateTime, *releaseLog, *featureBits, *releaseLogUrl;
qid = sqlEscapeString(el->qid);
pqid = sqlEscapeString(el->pqid);
priority = sqlEscapeString(el->priority);
qadate = sqlEscapeString(el->qadate);
newYN = sqlEscapeString(el->newYN);
track = sqlEscapeString(el->track);
dbs = sqlEscapeString(el->dbs);
tbls = sqlEscapeString(el->tbls);
cgis = sqlEscapeString(el->cgis);
files = sqlEscapeString(el->files);
currLoc = sqlEscapeString(el->currLoc);
makeDocYN = sqlEscapeString(el->makeDocYN);
onlineHelp = sqlEscapeString(el->onlineHelp);
ndxYN = sqlEscapeString(el->ndxYN);
joinerYN = sqlEscapeString(el->joinerYN);
stat = sqlEscapeString(el->stat);
sponsor = sqlEscapeString(el->sponsor);
reviewer = sqlEscapeString(el->reviewer);
extSource = sqlEscapeString(el->extSource);
openIssues = sqlEscapeString(el->openIssues);
notes = sqlEscapeString(el->notes);
pushState = sqlEscapeString(el->pushState);
initdate = sqlEscapeString(el->initdate);
lastdate = sqlEscapeString(el->lastdate);
lockUser = sqlEscapeString(el->lockUser);
lockDateTime = sqlEscapeString(el->lockDateTime);
releaseLog = sqlEscapeString(el->releaseLog);
featureBits = sqlEscapeString(el->featureBits);
releaseLogUrl = sqlEscapeString(el->releaseLogUrl);

dyStringPrintf(update, "insert into %s values ( '%s','%s','%s',%u,'%s','%s','%s','%s','%s','%s','%s',%u,'%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s',%u,'%s','%s','%s','%s','%s')", 
	tableName,  qid,  pqid,  priority,  el->rank,  qadate,  newYN,  track,  dbs,  tbls,  cgis,  files,  el->sizeMB,  currLoc,  makeDocYN,  onlineHelp,  ndxYN,  joinerYN,  stat,  sponsor,  reviewer,  extSource,  openIssues,  notes,  pushState,  initdate,  lastdate,  el->bounces,  lockUser,  lockDateTime,  releaseLog,  featureBits,  releaseLogUrl);
sqlUpdate(conn, update->string);
freeDyString(&update);
freez(&qid);
freez(&pqid);
freez(&priority);
freez(&qadate);
freez(&newYN);
freez(&track);
freez(&dbs);
freez(&tbls);
freez(&cgis);
freez(&files);
freez(&currLoc);
freez(&makeDocYN);
freez(&onlineHelp);
freez(&ndxYN);
freez(&joinerYN);
freez(&stat);
freez(&sponsor);
freez(&reviewer);
freez(&extSource);
freez(&openIssues);
freez(&notes);
freez(&pushState);
freez(&initdate);
freez(&lastdate);
freez(&lockUser);
freez(&lockDateTime);
freez(&releaseLog);
freez(&featureBits);
freez(&releaseLogUrl);
}

struct pushQ *pushQCommaIn(char **pS, struct pushQ *ret)
/* Create a pushQ out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new pushQ */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
sqlFixedStringComma(&s, ret->qid, sizeof(ret->qid));
sqlFixedStringComma(&s, ret->pqid, sizeof(ret->pqid));
sqlFixedStringComma(&s, ret->priority, sizeof(ret->priority));
ret->rank = sqlUnsignedComma(&s);
sqlFixedStringComma(&s, ret->qadate, sizeof(ret->qadate));
sqlFixedStringComma(&s, ret->newYN, sizeof(ret->newYN));
ret->track = sqlStringComma(&s);
ret->dbs = sqlStringComma(&s);
ret->tbls = sqlStringComma(&s);
ret->cgis = sqlStringComma(&s);
ret->files = sqlStringComma(&s);
ret->sizeMB = sqlUnsignedComma(&s);
sqlFixedStringComma(&s, ret->currLoc, sizeof(ret->currLoc));
sqlFixedStringComma(&s, ret->makeDocYN, sizeof(ret->makeDocYN));
sqlFixedStringComma(&s, ret->onlineHelp, sizeof(ret->onlineHelp));
sqlFixedStringComma(&s, ret->ndxYN, sizeof(ret->ndxYN));
sqlFixedStringComma(&s, ret->joinerYN, sizeof(ret->joinerYN));
ret->stat = sqlStringComma(&s);
sqlFixedStringComma(&s, ret->sponsor, sizeof(ret->sponsor));
sqlFixedStringComma(&s, ret->reviewer, sizeof(ret->reviewer));
sqlFixedStringComma(&s, ret->extSource, sizeof(ret->extSource));
ret->openIssues = sqlStringComma(&s);
ret->notes = sqlStringComma(&s);
sqlFixedStringComma(&s, ret->pushState, sizeof(ret->pushState));
sqlFixedStringComma(&s, ret->initdate, sizeof(ret->initdate));
sqlFixedStringComma(&s, ret->lastdate, sizeof(ret->lastdate));
ret->bounces = sqlUnsignedComma(&s);
sqlFixedStringComma(&s, ret->lockUser, sizeof(ret->lockUser));
sqlFixedStringComma(&s, ret->lockDateTime, sizeof(ret->lockDateTime));
ret->releaseLog = sqlStringComma(&s);
ret->featureBits = sqlStringComma(&s);
ret->releaseLogUrl = sqlStringComma(&s);
*pS = s;
return ret;
}

void pushQFree(struct pushQ **pEl)
/* Free a single dynamically allocated pushQ such as created
 * with pushQLoad(). */
{
struct pushQ *el;

if ((el = *pEl) == NULL) return;
freeMem(el->track);
freeMem(el->dbs);
freeMem(el->tbls);
freeMem(el->cgis);
freeMem(el->files);
freeMem(el->stat);
freeMem(el->openIssues);
freeMem(el->notes);
freeMem(el->releaseLog);
freeMem(el->featureBits);
freeMem(el->releaseLogUrl);
freez(pEl);
}

void pushQFreeList(struct pushQ **pList)
/* Free a list of dynamically allocated pushQ's */
{
struct pushQ *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    pushQFree(&el);
    }
*pList = NULL;
}

void pushQOutput(struct pushQ *el, FILE *f, char sep, char lastSep) 
/* Print out pushQ.  Separate fields with sep. Follow last field with lastSep. */
{
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->qid);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->pqid);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->priority);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%u", el->rank);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->qadate);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->newYN);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->track);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->dbs);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->tbls);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->cgis);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->files);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%u", el->sizeMB);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->currLoc);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->makeDocYN);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->onlineHelp);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->ndxYN);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->joinerYN);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->stat);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->sponsor);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->reviewer);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->extSource);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->openIssues);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->notes);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->pushState);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->initdate);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->lastdate);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%u", el->bounces);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->lockUser);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->lockDateTime);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->releaseLog);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->featureBits);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->releaseLogUrl);
if (sep == ',') fputc('"',f);
fputc(lastSep,f);
}

void usersStaticLoad(char **row, struct users *ret)
/* Load a row from users table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

safecpy(ret->user, sizeof(ret->user), row[0]);
safecpy(ret->password, sizeof(ret->password), row[1]);
safecpy(ret->role, sizeof(ret->role), row[2]);
ret->contents = row[3];
}

struct users *usersLoad(char **row)
/* Load a users from row fetched with select * from users
 * from database.  Dispose of this with usersFree(). */
{
struct users *ret;

AllocVar(ret);
safecpy(ret->user, sizeof(ret->user), row[0]);
safecpy(ret->password, sizeof(ret->password), row[1]);
safecpy(ret->role, sizeof(ret->role), row[2]);
ret->contents = cloneString(row[3]);
return ret;
}

struct users *usersLoadAll(char *fileName) 
/* Load all users from a whitespace-separated file.
 * Dispose of this with usersFreeList(). */
{
struct users *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[4];

while (lineFileRow(lf, row))
    {
    el = usersLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct users *usersLoadAllByChar(char *fileName, char chopper) 
/* Load all users from a chopper separated file.
 * Dispose of this with usersFreeList(). */
{
struct users *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[4];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = usersLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct users *usersLoadByQuery(struct sqlConnection *conn, char *query)
/* Load all users from table that satisfy the query given.  
 * Where query is of the form 'select * from example where something=something'
 * or 'select example.* from example, anotherTable where example.something = 
 * anotherTable.something'.
 * Dispose of this with usersFreeList(). */
{
struct users *list = NULL, *el;
struct sqlResult *sr;
char **row;

sr = sqlGetResult(conn, query);
while ((row = sqlNextRow(sr)) != NULL)
    {
    el = usersLoad(row);
    slAddHead(&list, el);
    }
slReverse(&list);
sqlFreeResult(&sr);
return list;
}

void usersSaveToDb(struct sqlConnection *conn, struct users *el, char *tableName, int updateSize)
/* Save users as a row to the table specified by tableName. 
 * As blob fields may be arbitrary size updateSize specifies the approx size
 * of a string that would contain the entire query. Arrays of native types are
 * converted to comma separated strings and loaded as such, User defined types are
 * inserted as NULL. Note that strings must be escaped to allow insertion into the database.
 * For example "autosql's features include" --> "autosql\'s features include" 
 * If worried about this use usersSaveToDbEscaped() */
{
struct dyString *update = newDyString(updateSize);
dyStringPrintf(update, "insert into %s values ( '%s','%s','%s',%s)", 
	tableName,  el->user,  el->password,  el->role,  el->contents);
sqlUpdate(conn, update->string);
freeDyString(&update);
}

void usersSaveToDbEscaped(struct sqlConnection *conn, struct users *el, char *tableName, int updateSize)
/* Save users as a row to the table specified by tableName. 
 * As blob fields may be arbitrary size updateSize specifies the approx size.
 * of a string that would contain the entire query. Automatically 
 * escapes all simple strings (not arrays of string) but may be slower than usersSaveToDb().
 * For example automatically copies and converts: 
 * "autosql's features include" --> "autosql\'s features include" 
 * before inserting into database. */ 
{
struct dyString *update = newDyString(updateSize);
char  *user, *password, *role, *contents;
user = sqlEscapeString(el->user);
password = sqlEscapeString(el->password);
role = sqlEscapeString(el->role);
contents = sqlEscapeString(el->contents);

dyStringPrintf(update, "insert into %s values ( '%s','%s','%s','%s')", 
	tableName,  user,  password,  role,  contents);
sqlUpdate(conn, update->string);
freeDyString(&update);
freez(&user);
freez(&password);
freez(&role);
freez(&contents);
}

struct users *usersCommaIn(char **pS, struct users *ret)
/* Create a users out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new users */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
sqlFixedStringComma(&s, ret->user, sizeof(ret->user));
sqlFixedStringComma(&s, ret->password, sizeof(ret->password));
sqlFixedStringComma(&s, ret->role, sizeof(ret->role));
ret->contents = sqlStringComma(&s);
*pS = s;
return ret;
}

void usersFree(struct users **pEl)
/* Free a single dynamically allocated users such as created
 * with usersLoad(). */
{
struct users *el;

if ((el = *pEl) == NULL) return;
freeMem(el->contents);
freez(pEl);
}

void usersFreeList(struct users **pList)
/* Free a list of dynamically allocated users's */
{
struct users *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    usersFree(&el);
    }
*pList = NULL;
}

void usersOutput(struct users *el, FILE *f, char sep, char lastSep) 
/* Print out users.  Separate fields with sep. Follow last field with lastSep. */
{
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->user);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->password);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->role);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->contents);
if (sep == ',') fputc('"',f);
fputc(lastSep,f);
}

/* -------------------------------- End autoSql Generated Code -------------------------------- */

