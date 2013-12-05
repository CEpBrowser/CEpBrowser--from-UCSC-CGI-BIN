table mrnaAli
"An mRNA/genomic alignment"
    (
    uint id;          "Unique ID"
    byte readDir;     "Read direction of mRNA +1 or -1" 
    byte orientation; "Orientation relative to first BAC"
    ubyte hasIntrons; "True if alignment has introns"
    ubyte isEst;      "True if an EST."
    int score;        "Score in something like log-odds form"
    char[12] qAcc;    "GenBank Accession for mRNA sequence"
    uint qId;         "Database ID of mRNA sequence"
    uint qTotalSize;  "Total bases (not just aligned) in mRNA"
    uint qStart;      "Start in mRNA sequence"
    uint qEnd;        "End in mRNA sequence"
    uint tStartBac;   "ID of first genomic BAC in alignment"
    uint tStartPos;   "Start position within first BAC"
    uint tEndBac;     "ID of last genomic BAC in alignment"
    uint tEndPos;     "End position within last BAC"
    uint blockCount; "Number of aligned blocks"
    uint[blockCount] blockSizes; "Size of each block"
    uint[blockCount] qBlockStarts; "Start of each block in mRNA"
    uint[blockCount] tBlockBacs; "BAC each block starts in"
    uint[blockCount] tBlockStarts; "Position within BAC of each block start"
    ushort[blockCount] startGoods; "Number of perfect bases at start of block"
    ushort[blockCount] endGoods; "Number of perfect bases at end of block"
    )

