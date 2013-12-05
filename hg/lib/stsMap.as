table stsMap
"STS marker and its position on golden path and various maps"
    (
    string chrom;	"Reference sequence chromosome or scaffold"
    int chromStart;     "Start position in chrom - negative 1 if unpositioned"
    uint chromEnd;	"End position in chrom"
    string name;	"Name of STS marker"
    uint score;         "Score of a marker = 1000 when placed uniquely, else 1500/(#placements) when placed in multiple locations"

    uint identNo;	"Identification number of STS"
    string ctgAcc;	"Contig accession number"
    string otherAcc;	"Accession number of other contigs that the marker hits"

    string genethonChrom;	"Chromosome (no chr) from Genethon map or 0 if none"
    float genethonPos;		"Position on Genethon map"
    string marshfieldChrom;	"Chromosome (no chr) from Marshfield map or 0 if none"
    float marshfieldPos;	"Position on Marshfield map"
    string gm99Gb4Chrom;	"Chromosome (no chr) from GeneMap99 map or 0 if none"
    float gm99Gb4Pos;		"Position on gm99_bg4 map"
    string shgcTngChrom;	"Chromosome (no chr) from shgc_tng map or 0 if none"
    float shgcTngPos;		"Position on shgc_tng map"
    string shgcG3Chrom;		"Chromosome (no chr) from Stanford G3 map or 0 if none"
    float shgcG3Pos;		"Position on shgc_g3 map"
    string wiYacChrom;		"Chromosome (no chr) from Whitehead YAC map or 0 if none"
    float wiYacPos;		"Position on wi_yac map"
    string wiRhChrom;		"Chromosome (no chr) from Whitehead RH map or 0 if none"
    float wiRhPos;		"Position on wi_rh map"
    string fishChrom;		"Chromosome (no chr) from FISH map or 0 if none"
    string beginBand;		"Beginning of range of bands on FISH map"
    string endBand;		"End of range of bands on FISH map"
    string lab;			"Laboratory that placed the FISH clone"
    string decodeChrom;		"Chromosome (no chr) from deCODE genetic map or 0 if none"
    float decodePos;		"Position on deCODE genetic map"
    )
