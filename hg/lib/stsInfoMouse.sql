# stsInfoMouse.sql was originally generated by the autoSql program, which also 
# generated stsInfoMouse.c and stsInfoMouse.h.  This creates the database representation of
# an object which can be loaded and saved from RAM in a fairly 
# automatic way.

#Constant STS marker information
CREATE TABLE stsInfoMouse (
    identNo int unsigned not null,	# UCSC identification number
    name varchar(255) not null,	# Official UCSC name
    MGIPrimerID int unsigned not null,	# sts Primer's MGI ID or 0 if N/A
    primerName varchar(255) not null,	# sts Primer's name
    primerSymbol varchar(255) not null,	# sts Primer's symbol
    primer1 varchar(255) not null,	# primer1 sequence
    primer2 varchar(255) not null,	# primer2 sequence
    distance varchar(255) not null,	# Length of STS sequence
    sequence int unsigned not null,	# Whether the full sequence is available (1) or not (0) for STS
    MGIMarkerID int unsigned not null,	# sts Marker's MGI ID or 0 if N/A
    stsMarkerSymbol varchar(255) not null,	# symbol of  STS marker
    Chr varchar(255) not null,	# Chromosome in Genetic map
    geneticPos float not null,	# Position in Genetic map. -2 if N/A, -1 if syntenic 
    stsMarkerName varchar(255) not null,	# Name of sts Marker.
    LocusLinkID int unsigned not null,	# Locuslink Id, 0 if N/A
              #Indices
    PRIMARY KEY(identNo),
    INDEX(MGIMarkerID),	
    INDEX(MGIPrimerID)
);
