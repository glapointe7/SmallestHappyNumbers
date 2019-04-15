#ifndef STYLE_HPP
#define	STYLE_HPP

#include <ostream>

namespace Style
{   
    using ColorInteger = uint16_t;
    
    enum class ForegroundColor : ColorInteger
    {
        BLACK = 30, 
        RED      = 31,
        GREEN    = 32,
        YELLOW   = 33,
        BLUE     = 34,
        MAGENTA = 35, 
        CYAN = 36, 
        LIGHT_GRAY = 37,
        DEFAULT  = 39,
        DARK_GRAY = 90, 
        LIGHT_RED = 91, 
        LIGHT_GREEN = 92,
        LIGHT_YELLOW = 93, 
        LIGHT_BLUE = 94, 
        LIGHT_MAGENTA = 95, 
        LIGHT_CYAN = 96, 
        WHITE = 97
    };

    enum class BackgroundColor : ColorInteger
    {
        RED      = 41,
        GREEN    = 42,
        BLUE     = 44,
        DEFAULT  = 49
    };
    
    inline std::ostream& operator<<(std::ostream& os, ForegroundColor foreground_color) 
    {
        return os << "\033[" << static_cast<ColorInteger>(foreground_color) << "m";
    }
    
    inline std::ostream& operator<<(std::ostream& os, const BackgroundColor background_color) 
    {
        return os << "\033[" << static_cast<ColorInteger>(background_color) << "m";
    }
    
    inline std::string ResetToDefault()
    {
        return "\033[0m";
    }
}

#endif