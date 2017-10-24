#ifndef MOON_GLOBE_H
#define MOON_GLOBE_H

#include <vector>
#include <memory>
// #include <unordered_set>
#include "Fragment/Fragment.h"

typedef size_t ZoomLevel;

class MoonGlobe
{
public:
    MoonGlobe();

    void draw(MyShader& shader);
    // void set_scale();

private:
    void refreshFragments();
    void generateFragments();

    int current_rows;
    int current_columns;
    ZoomLevel zoom_level;
    std::vector<std::shared_ptr<Fragment>> fragments;

};

#endif
