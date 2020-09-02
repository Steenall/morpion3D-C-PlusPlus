#include <iostream>
#include "board.hpp"
#include "player.hpp"
#include "color.hpp"

void cleanDisplay(){
    std::cout << "\033[H\033[2J"<<std::ends;;
}

Player creerJoueur(){
    std::string nom;
    char couleur;
    do{
        std::cout << "Veuillez rentrez votre nom" << std::endl;
        std::cin >> nom;
        std::cin.clear();
    }while(nom.empty());
    do{
        std::cout << "Veuillez rentrez une couleur :" << std::endl;
        std::cout << colorToString(Color::RED) << "0: rouge    " << std::ends;
        std::cout << colorToString(Color::GREEN) << "1: vert    " << std::ends;
        std::cout << colorToString(Color::BLUE) << "2: bleu    " << std::ends;
        std::cout << colorToString(Color::YELLOW) << "3: jaune    " << std::ends;
        std::cout << colorToString(Color::MAGENTA) << "4: magenta    " << std::ends;
        std::cout << colorToString(Color::CYAN) << "5: cyan" << colorToString(Color::WHITE) << std::endl;
        std::cin >> couleur;
        std::cin.clear();
    }while(couleur<48||couleur>54);
    cleanDisplay();
    return Player(nom,(Color)(((int) couleur)-48));
}

int saisirLigne(){
    char value=0;
    do{
        std::cout << "Veuillez rentrer la ligne" << std::endl;
        std::cin >> value;
        std::cin.clear();
    }while(value!='1'&&value!='2'&&value!='3');
    return ((int) value)-49;
}

char saisirColonne(){
    char value;
    do{
        std::cout << "Veuillez rentrer la colonne" << std::endl;
        std::cin >> value;
        std::cin.clear();
    }while(value!='a'&&value!='A'&&value!='b'&&value!='B'&&value!='c'&&value!='C');
    if(value=='a'||value=='b'||value=='c')value-=32;
    return value;
}

Size saisirSize(){
    char value=0;
    do{
        std::cout << "Veuillez rentrer une taille (1: petite, 2: moyenne, 3: grande)" << std::endl;
        std::cin >>value;
    }while(value!='1'&&value!='2'&&value!='3');
    return (Size) (((int) value)-48);
}

void lancerLaPartie(){
    Board (*board)=new Board(creerJoueur(),creerJoueur());
    char answer;
    bool end =false;
    do{
        cleanDisplay();
        std::cout << colorToString((*board).getCurrentPlayer().getColor()) << (*board).getCurrentPlayer().getName() << colorToString(Color::WHITE) << "à toi de jouer" << std::endl;
        (*board).affichePlateau();
        std::cout << "Veux tu placer (P), déplacer (D) ou abandonner(A) ?" << std::endl;
        do{
            std::cin >> answer;
            std::cin.clear();
        }while(answer!='a'&&answer!='A'&&answer!='d'&&answer!='D'&&answer!='P'&&answer!='p');
        if(answer=='d'||answer=='D'){
            int sLine=saisirLigne();
            char sColonne=saisirColonne();
            int dLine =saisirLigne();
            char dColonne =saisirColonne();
            std::cout << (*board).movePiece(sLine,sColonne,dLine,dColonne) << std::endl;
        }else if(answer=='p'||answer=='P'){
            Size taille=saisirSize();
            int sLine=saisirLigne();
            char sColonne=saisirColonne();
            std::cout << (*board).placePiece(taille,sLine,sColonne) << std::endl;
        }else{
            end=true;
        }
    }while((*board).getWinner()==-1||!end);
}


void menu(){
    bool end=false;
    do{
        cleanDisplay();
        std::cout << colorToString(Color::CYAN) << "___  ___                 _               ___________ " << std::endl;
        std::cout << "|  \\/  |                (_)             |____ |  _  \\" << std::endl;
        std::cout << "| .  . | ___  _ __ _ __  _  ___  _ __       / / | | |" << std::endl;
        std::cout << "| |\\/| |/ _ \\| '__| '_ \\| |/ _ \\| '_ \\      \\ \\ | | |" << std::endl;
        std::cout << "| |  | | (_) | |  | |_) | | (_) | | | | .___/ / |/ /" << std::endl;
        std::cout << "\\_|  |_/\\___/|_|  | .__/|_|\\___/|_| |_| \\____/|___/" << std::endl;
        std::cout << "                  | |" << std::endl;
        std::cout << "                  |_|                                " << std::endl;
        end=true;
        std::cout << "\033[35;01m   Menu\n    \033[34;01m1 - Jouer\n    \033[0;01m2 - Options\n    \033[31;01m3 - Quitter\n\n\033[37;01m" << std::endl;
        int val=0;
        std::cin >> val;
        std::cin.clear();
        switch(val){
			case 1:
				std::cout << "\033[H\033[2J" << std::ends;
				lancerLaPartie();
                break;
			case 2:
				std::cout << "\033[H\033[2J" << std::ends;
				std::cout << "\033[31;01mIl n'y a pas d'options pour le moment\033[0;01m\n" << std::ends;
				break;
			case 3:
				std::cout << "\033[H\033[2J" << std::ends;
				exit(0);
			default:
				std::cout << "\033[H\033[2J" << std::ends;
				break;
		}
    }while(end!=true);
}

int main(){
    Player player1= Player("Test1",Color::BLUE);
    Player player2= Player("Test1",Color::RED);
    Board board=Board(player1,player2);
    board.placePiece(Size::SMALL,2,'A');
    board.placePiece(Size::MEDIUM,2,'A');
    board.placePiece(Size::SMALL,3,'C');
    board.placePiece(Size::LARGE,1,'A');
    board.placePiece(Size::NONE,3,'B');
    board.affichePlateau();
    menu();
    return 0;
}
