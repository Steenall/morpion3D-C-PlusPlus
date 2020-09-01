# if !defined(__COLOR__)
#define __COLOR__
#include <string>
    enum Color{
        RED,
        GREEN,
        BLUE,
        YELLOW,
        MAGENTA,
        CYAN,
        WHITE
    };
    std::string colorToString(Color color);
#endif