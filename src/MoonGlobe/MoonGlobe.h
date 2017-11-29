#ifndef MOON_GLOBE_H
#define MOON_GLOBE_H

#include <vector>
#include <memory>
#include <unordered_map>
#include <Magnum/Renderer.h>
#include "Fragment/Fragment.h"

typedef size_t ZoomLevel;

class MoonGlobe
{
public:
    MoonGlobe();

    void draw(MyShader& shader, const Camera& camera);
    void set_scale(int level);

private:
    void refreshFragments();
    void generateFragments();
    std::string get_texture_id(ZoomLevel level, size_t row, size_t column);

    size_t current_rows;
    size_t current_columns;
    std::unordered_map<int, std::pair<int, int>> row_and_columns;

    ZoomLevel zoom_level;
    std::vector<std::shared_ptr<Fragment>> fragments;

};

#endif
