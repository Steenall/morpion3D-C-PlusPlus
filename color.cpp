#include "color.hpp"
#include <string>
std::string colorToString(Color color){
    std::string temp;
    switch (color){
        case Color::RED:
            temp="\033[31m";
            break;
        case Color::GREEN:
            temp="\033[32m";
            break;
        case Color::BLUE:
            temp="\033[34m";
            break;
        case Color::YELLOW:
            temp="\033[93m";
            break;
        case Color::MAGENTA:
            temp="\033[95m";
            break;
        case Color::CYAN:
            temp="\033[96m";
            break;
        default:
            temp="\033[39m";
            break;
    }
    return temp;
}