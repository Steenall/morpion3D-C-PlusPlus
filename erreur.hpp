# if !defined(__ERREUR__)
#define __ERREUR__
    enum Erreur{
        INTERNAL_ERROR= -5,
        PAS_DE_PIECE_DANS_MAISON=-4,
        PAS_DE_PIECE=-3,
        PAS_TA_PIECE=-2,
        EMPLACEMENT_INDISPONIBLE=-1,
        SUCCESS=0
    };
#endif