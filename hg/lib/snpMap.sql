# snpMap.sql was originally generated by the autoSql program, which also 
# generated snpMap.c and snpMap.h.  This creates the database representation of
# an object which can be loaded and saved from RAM in a fairly 
# automatic way.

#SNP positions from various sources
CREATE TABLE snpMap (
    bin        smallint unsigned not null, 
    chrom      varchar(255) not null,	# Chromosome or 'unknown'
    chromStart int unsigned not null,	# Start position in chrom
    chromEnd   int unsigned not null,	# End position in chrom
    name       varchar(255) not null,	# Name of SNP - rsId or Affy name
    source     enum (
		 'BAC_OVERLAP',         # dbSnp
		 'MIXED',               # dbSnp
		 'RANDOM',              # dbSnp
		 'OTHER',               # dbSnp
		 'Affy10K',             # Affymetrix
		 'Affy120K',            # Affymetrix
		 'unknown'              # default value
		 ) not null default 'unknown',
    type       enum (
		 'SNP',                 # Single Nucleotide Polymorphism
		 'INDEL',               # Insertion or Deletion
		 'SEGMENTAL',           # Segmental Duplication
		 'unknown'              # default value
		 ) not null default 'unknown',
              #Indices
    INDEX(chrom(12),bin),
    INDEX(chrom(12),chromStart),
    INDEX(name)
);

