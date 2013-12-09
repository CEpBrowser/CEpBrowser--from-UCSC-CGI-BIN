# metaDb.sql was originally generated by the autoSql program, which also
# generated metaDb.c and metaDb.h.  This creates the database representation of
# an object which can be loaded and saved from RAM in a fairly
# automatic way.

#This contains metadata for a table, file or other predeclared object type.
CREATE TABLE metaDb (
    obj varchar(255) not null,	        # Object name or ID.
    var varchar(255) not null,	        # Metadata variable name.
    varType     enum (
                 'txt',                 # Most vars are txt
                 'binary'               # some vars are binary
               ) not null default 'txt',
    val longblob not null,	        # Metadata value.
              #Indices
    PRIMARY KEY(obj,var),
    UNIQUE(var,val(32),obj)
);
