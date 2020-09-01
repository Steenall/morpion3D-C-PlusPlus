# if !defined(__SIZE__)
#define __SIZE__
    #include <string>
    enum Size{
        NONE,
        SMALL,
        MEDIUM,
        LARGE
    };
    std::string sizeToString(Size size);
#endif