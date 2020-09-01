#include "size.hpp"
#include <string>

std::string sizeToString(Size size){
    switch (size)
    {
    case Size::NONE:
        return " ";
    case Size::SMALL:
        return "●";
    case Size::MEDIUM:
        return "▲";
    case Size::LARGE:
        return "■";
    default:
        return " ";
    }
}