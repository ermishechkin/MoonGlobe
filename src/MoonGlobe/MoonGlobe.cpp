#include "MoonGlobe/MoonGlobe.h"

const std::pair<int, int> row_and_columns[] = {
    {2, 4}, // 2 линии по 4 фотки
    {5, 10} // 5 линий по 10 фоток
};


MoonGlobe::MoonGlobe()
    : zoom_level(1)
{
    refreshFragments();
}

void MoonGlobe::refreshFragments()
{
    current_rows    = row_and_columns[zoom_level].first;
    current_columns = row_and_columns[zoom_level].second;

    if (fragments.size() != current_rows * current_columns) {
        std::cout << "\nrefresh Fragments\n";
        fragments.clear();
        generateFragments();
    }
}

std::string get_texture_id(ZoomLevel level, size_t row, size_t column)
{
    int picture_on_line = row_and_columns[level].second;
    std::string id = std::to_string(level) + "_" +
                     std::to_string(picture_on_line * row + column);
    return id;
}

void MoonGlobe::generateFragments()
{
    float height =     M_PI / current_rows;
    float length = 2 * M_PI / current_columns;


    float phi_step = length;
    float theta_step = height;
    for (size_t i = 0; i < current_rows; i++) {

        for (size_t j = 0; j < current_columns; j++) {
            Coords l_b = {height + i * theta_step,          j * phi_step};
            Coords l_t = {         i * theta_step,          j * phi_step};
            Coords r_t = {         i * theta_step, length + j * phi_step};
            Coords r_b = {height + i * theta_step, length + j * phi_step};
            // print_coord(l_b);
            std::string texture_id = get_texture_id(zoom_level, i, j);
            // std::cout << "\n" << texture_id;
            std::shared_ptr<Fragment> f(new Fragment(l_b, l_t, r_t, r_b, texture_id));
            fragments.push_back(f);
        }
    }
    std::cout << fragments.size();
}

void MoonGlobe::draw(MyShader& shader)
{
    for (auto& fragment: fragments) {
        fragment->draw(shader);
    }
}
