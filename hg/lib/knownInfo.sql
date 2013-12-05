# knownInfo.sql was originally generated by the autoSql program, which also 
# generated knownInfo.c and knownInfo.h.  This creates the database representation of
# an object which can be loaded and saved from RAM in a fairly 
# automatic way.

#Auxiliary info about a known gene
CREATE TABLE knownInfo (
    name varchar(255) not null,	# connects with genieKnown->name
    transId varchar(255) not null,	# Transcript id. Genie generated ID.
    geneId varchar(255) not null,	# Gene (not trascript) id
    geneName int unsigned not null,	# Connect to geneName table
    productName int unsigned not null,	# Connects to productName table
    proteinId varchar(255) not null,	# Genbank accession of protein?
    ngi varchar(255) not null,	# Genbank gi of nucleotide seq.
    pgi varchar(255) not null,	# Genbank gi of protein seq.
              #Indices
    INDEX(name(20)),
    PRIMARY KEY(transId(20)),
    INDEX(geneName(20)),
    INDEX(productName(20))
);
