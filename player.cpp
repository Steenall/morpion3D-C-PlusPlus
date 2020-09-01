#include "player.hpp"
#include <string>
#include <iostream>

Player::Player(){
    pColor=new Color(Color::BLUE);
    pName=new std::string("Player");
}

Player::Player(const std::string name, const Color color){
    pName= new std::string(name);
    pColor=new Color(color);
    pHouse=new short int(0);
    short int temp=1;
    for(int i=0;i<nbTypePiece;i++){
        (*pHouse)+=temp*nbPieceParType;
        temp*=10;
    }
}

Color Player::getColor() {
    return *pColor;
}

int Player::getPiecesInHouse(const Size pieceSize){
    short int temp;
    switch (pieceSize)
    {
    case Size::SMALL:
        temp = (*pHouse)%10;
        break;
    case Size::MEDIUM:
        temp = ((*pHouse)/10)%10;
        break;
    case Size::LARGE:
        temp = (*pHouse)/100;
        break;
    default:
        temp = 0;
    }
    return temp;
}

bool Player::retirePiece(const Size pieceSize){
    if(getPiecesInHouse(pieceSize)!=0){
        short int temp;
        switch (pieceSize)
        {
        case Size::SMALL:
            temp = 1;
            break;
        case Size::MEDIUM:
            temp = 10;
            break;
        case Size::LARGE:
            temp = 100;
            break;
        }
        (*pHouse)-=temp;
        return true;
    }else{
        return false;
    }
}


Player::~Player(){
    /*delete pName;
    delete pColor;
    delete pHouse;
    pName=nullptr;
    pColor=nullptr;
    pHouse=nullptr;*/
}