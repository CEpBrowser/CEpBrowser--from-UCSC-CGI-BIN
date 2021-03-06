# cdsPick.sql was originally generated by the autoSql program, which also 
# generated cdsPick.c and cdsPick.h.  This creates the database representation of
# an object which can be loaded and saved from RAM in a fairly 
# automatic way.

#Information on CDS that we picked from competing cdsEvidence
CREATE TABLE cdsPick (
    name varchar(255) not null,	# Name of transcript
    start int not null,	# CDS start within transcript, zero based
    end int not null,	# CDS end, non-inclusive
    source varchar(255) not null,	# Source of best evidence
    score double not null,	# Higher is better.
    startComplete tinyint unsigned not null,	# Starts with ATG?
    endComplete tinyint unsigned not null,	# Ends with stop codon?
    swissProt varchar(255) not null,	# Matching swissProt if available.
    uniProt varchar(255) not null,	# Matching uniProt if available.
    refProt varchar(255) not null,	# RefSeq protein if available.
    refSeq varchar(255) not null,	# RefSeq transcript if available.
    ccds varchar(255) not null,	# CCDS accession if available.
              #Indices
    PRIMARY KEY(name)
);
