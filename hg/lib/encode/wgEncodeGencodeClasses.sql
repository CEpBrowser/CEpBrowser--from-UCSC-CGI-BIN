# wgEncodeGencodeClasses.sql was originally generated by the autoSql program, which also
# generated wgEncodeGencodeClasses.c and wgEncodeGencodeClasses.h.  This creates the database representation of
# an object which can be loaded and saved from RAM in a fairly
# automatic way.

#Class for Gencode genes
CREATE TABLE wgEncodeGencodeClasses (
    geneId varchar(255) not null,
    transcriptId varchar(255) not null,
    geneName varchar(255) not null,
    transcriptName varchar(255) not null,
    geneType varchar(255) not null,
    transcriptType varchar(255) not null,
    geneStatus varchar(255) not null,
    transcriptStatus varchar(255) not null,
    level integer,
    class enum('Undefined','Validated_coding','Validated_processed','Validated_processed_pseudogene','Validated_unprocessed_pseudogene','Validated_pseudogene','Havana_coding','Havana_nonsense','Havana_non_coding','Havana_processed_pseudogene','Havana_unprocessed_pseudogene','Havana_pseudogene','Havana_TEC','Havana_polyA','Ensembl_coding','Ensembl_RNA','Ensembl_pseudogene') not null default 'Undefined',
    name varchar(255) not null,
    # indexes
    INDEX(transcriptType),
    INDEX(level,class),
    PRIMARY KEY(name)
);
