#ifndef PROGRESSBAR_HPP
#define	PROGRESSBAR_HPP

#include "Style.hpp"

class ProgressBar
{
public:
    explicit ProgressBar(const Style::BackgroundColor background_color)
            : background_color(background_color) { }
    
    void Show(const double percentage) const;
    
protected:
    const Style::BackgroundColor background_color;
};

#endif