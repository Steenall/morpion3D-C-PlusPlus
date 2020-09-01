#include "board.hpp"
#include <iostream>
#include <string>

Board::Board(Player player1, Player player2) {
    box=new short int[DIMENSIONS*DIMENSIONS]{0};
    currentPlayer = new short int{0};
    players=new Player[NB_PLAYERS];
    players[0]=player1;
    players[1]=player2;
}

Board::Board(const Board &other){
    for(int i=0;i<DIMENSIONS;i++){
        for(int j=0;j<DIMENSIONS;j++){
            box[i*3+j]=other.box[i*3+j];
        }
    }
    Player * tempPlayers=other.getPlayers();
    for(int i=0;i<NB_PLAYERS;i++){
        players[i]=tempPlayers[i];
    }
}

Player Board::getCurrentPlayer() const {
    return players[*currentPlayer];
}

std::string Board::getMaison(Player player) const {
    std::string temp ="";
    int tempNb;
    for(int i=1;i<4;i++){
        tempNb=player.getPiecesInHouse((Size) i);
        for(int j=0;j<tempNb;j++){
            temp+=sizeToString((Size) i);
            temp+=" ";
        }
    }
    return temp;
}

Size Board::getPiece(const int line, const int column){
    if(box[line*3+column]==0)return Size::NONE;
    else if(box[line*3+column]>=100)return Size::LARGE;
    else if(box[line*3+column]>=10)return Size::MEDIUM;
    else return Size::SMALL;
}

int Board::getPlaceHolder(const int line, const int column){
    int temp;
    switch (getPiece(line, column)){
        case Size::SMALL:
            temp=1;
            break;
        case Size::MEDIUM:
            temp=10;
            break;
        case Size::LARGE:
            temp=100;
            break;
        default:
            return Erreur::PAS_DE_PIECE;
            break;
    }
    return (box[line*3+column]/temp)-1;
}

Player* Board::getPlayers() const {
    return players;
}

int Board::getWinner(){
    int temp;
    for(int i=0;i<3;i++){
        //Vérification ligne
        temp=getPlaceHolder(i,0);
        if(temp!=-1&&temp==getPlaceHolder(i,1)&&temp==getPlaceHolder(i,2)){
            return temp;
        }
        //Vérification colonne
        temp=getPlaceHolder(0,i);
        if(temp!=-1&&temp==getPlaceHolder(1,i)&&temp==getPlaceHolder(2,i)){
            return temp;
        }
    }
    //Vérification diagonale
    temp=getPlaceHolder(1,1);
    if(temp!=-1&&((getPlaceHolder(0,0)==temp&&temp==getPlaceHolder(2,2))||(getPlaceHolder(0,2)==temp&&temp==getPlaceHolder(2,0)))){
        return temp;
    }
    return -1;
}

/*void Board::addPlayer(Player player){
    int temp=std::size(players);
    if(temp>=9)return;
    players[std::size(players)]=player;
}*/

void Board::affichePlateau(){
    std::cout << "\t    A   B   C" << std::endl;
    std::cout << "\t  ┌───┬───┬───┐" << std::endl;
    for(int i=0;i<3;i++){
        std::cout << "\t"<< i+1 <<" | " << std::ends;
        for(int j=0;j<3;j++){
            if(getPlaceHolder(i,j)!=PAS_DE_PIECE)std::cout << colorToString(players[getPlaceHolder(i,j)].getColor()) << std::ends;
            std::cout << sizeToString(getPiece(i,j)) << colorToString(Color::WHITE) << " | " << std::ends;
        }
        if(i==0)std::cout << "\tContenu des maisons" << std::endl;
        else std::cout << "\t" << colorToString(players[i-1].getColor()) << getMaison(players[i-1]) << colorToString(Color::WHITE) << std::endl;
        if(i<2)std::cout << "\t  ├───┼───┼───┤" << std::endl;
        else std::cout << "\t  └───┴───┴───┘" << std::endl;
    }
}

Erreur Board::movePiece(const int sourceLine, const int sourceColumn, const int targetLine, const int targetColumn){
    int holderSource=getPlaceHolder(sourceLine,sourceColumn);
    if(holderSource==-1) return PAS_DE_PIECE;
    if(holderSource-1!=(*currentPlayer))return PAS_TA_PIECE;
    Size targetPiece=getPiece(targetLine,targetColumn);
    Size sourcePiece=getPiece(targetLine,targetColumn);
    if(targetPiece<sourcePiece){ 
        int tempSource;
        switch (sourcePiece){
            case Size::SMALL:
                tempSource=1;
                break;
            case Size::MEDIUM:
                tempSource=10;
                break;
            case Size::LARGE:
                tempSource=100;
                break;
        }
        box[sourceLine*3+sourceColumn]-=tempSource*((*currentPlayer)-1);
        box[targetLine*3+targetColumn]+=tempSource*((*currentPlayer)-1);
        nextPlayer();
        return SUCCESS;
    }else return EMPLACEMENT_INDISPONIBLE;
}

void Board::nextPlayer(){
    *currentPlayer=((*currentPlayer)+1)%NB_PLAYERS;
}

Erreur Board::placePiece(const Size pieceSize, const int line, const char column){
    int tempColumn=0;
    switch (column){
        case 'A':
            break;
        case 'B':
            tempColumn=1;
            break;
        case 'C':
            tempColumn=2;
            break;
        default:
            return INTERNAL_ERROR;
    }
    if(getPiece(line,tempColumn)<pieceSize){
        short int temp=0;
        if(pieceSize==Size::SMALL){
            temp=1;
        }else if(pieceSize==Size::MEDIUM){
            temp=10;
        }else if(pieceSize==Size::LARGE){
            temp=100;
        }
        if(players[(*currentPlayer)].getPiecesInHouse(pieceSize)>0){
            box[line*3+tempColumn]+=temp*((*currentPlayer)+1);
            players[(*currentPlayer)].retirePiece(pieceSize);
            nextPlayer();
            return SUCCESS;
        }else{
            return PAS_DE_PIECE_DANS_MAISON;
        }
    }
    return EMPLACEMENT_INDISPONIBLE;
}

Board::~Board(){
    delete[] box;
    delete currentPlayer;
    delete[] players;
    players=nullptr;
    currentPlayer=nullptr;
    box=nullptr;
    
}