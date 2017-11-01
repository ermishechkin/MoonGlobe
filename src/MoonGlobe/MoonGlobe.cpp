#include "MoonGlobe/MoonGlobe.h"


MoonGlobe::MoonGlobe()
    : zoom_level(2)
{
    row_and_columns.insert(std::make_pair(1, std::make_pair(2,  4)));
    row_and_columns.insert(std::make_pair(2, std::make_pair(5, 10)));
    row_and_columns.insert(std::make_pair(3, std::make_pair(10, 20)));
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

std::string MoonGlobe::get_texture_id(ZoomLevel level, size_t row, size_t column)
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
            compute_decart_coord(l_b);
            compute_decart_coord(l_t);
            compute_decart_coord(r_t);
            compute_decart_coord(r_b);
            // print_coord(l_b);
            std::string texture_id = get_texture_id(zoom_level, i, j);
            std::cout << "\n" << texture_id;
            std::shared_ptr<Fragment> f(new Fragment(l_b, l_t, r_t, r_b, texture_id));
            fragments.push_back(f);
        }
    }
    std::cout << fragments.size();
}

void MoonGlobe::draw(MyShader& shader, const Camera& camera)
{
    refreshFragments();
    static int i = 0;
    // for (int j = 0; j <= i && i < fragments.size(); j++) {
            // if (fragment->isVisible(camera)) {
                // fragments[j]->draw(shader);
            // } else {
                // fragment.erase()
            // }
    // }
    // i++;

    for (auto& fragment: fragments) {
        // if (fragment->isVisible(camera)) {
            fragment->draw(shader);
        // } else {
            // fragment.erase()
        // }
    }
}
