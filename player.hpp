# if !defined(__PLAYER__)
#define __PLAYER__
    #include <string>
    #include "color.hpp"
    #include "size.hpp"
    #define nbTypePiece 3
    #define nbPieceParType 2
    class Player{
        public :
            Player();
            Player(const std::string name, const Color color);
            Color getColor();
            int getPiecesInHouse(const Size pieceSize);
            bool retirePiece(const Size pieceSize);
            ~Player();
        private :
            std::string *pName;
            Color *pColor;
            short int *pHouse;
    };
#endif