#if !defined(__BOARD__)
#define __BOARD__
    #define DIMENSIONS 3
    #define NB_PLAYERS 2
    #include "player.hpp"
    #include "size.hpp"
    #include "color.hpp"
    #include "erreur.hpp"
    class Board{
        public :
            Board(const Player player1, const Player player2);
            Board(const Board &other);
            Player getCurrentPlayer() const;
            std::string getMaison(Player player) const;
            Player* getPlayers() const;
            int getWinner();
            //void addPlayer(Player player);
            void affichePlateau();
            Erreur movePiece(const int sourceLine, const char sourceColumn, const int targetLine, const char targetColumn);
            void nextPlayer();
            Erreur placePiece(const Size pieceSize, const int line, const char column);
            ~Board();
        private :
            short int * box;
            Player * players;
            short int  * currentPlayer;
            Size getPiece(const int line, const int column);
            int getPlaceHolder(const int line, const int column);
    };
#endif