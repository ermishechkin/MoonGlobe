#include "LabelManager/LabelManager.h"
#include "configure.h"
#include <iostream>
#include <cmath>
#include <Coords/Coords.h>
#include <tuple>
#include <Corrade/Utility/Resource.h>
#include <sstream>
#include <vector>

LabelManager::LabelManager()
    : _cache(Vector2i(2048), Vector2i(512), 22)
{
    Corrade::Utility::Resource rs("features");
    std::stringstream in(rs.get("parsed"));

    std::vector<int> a(20, 0);
    std::string name, diametr, latt, longt;
    for (int i = 0; i < 9000; i++) {
        in >> name;
        in >> diametr;
        while (!('0' <= diametr[0] && diametr[0] <= '9')) {
            name += diametr;
            in >> diametr;
        }
        int index = std::stod(diametr) / 10;
        if (0 <= index && index < 20)
            a[index]++;
        in >> latt >> longt;
        // Error() << name << " " << diametr << " " << latt << " " << longt << "\n";
        float theta = (std::stof(latt) + 90.0) / 90.0 * M_PI;
        float phi = (std::stof(longt) + 180.0) / 360.0 * 2 * M_PI;;
        Coords c(theta, phi);
        compute_decart_coord(c, 1.001);

        labels.push_back(std::shared_ptr<Label> (new Label(name, std::stod(diametr), {c.x, c.y, c.z})));
    }
    for (el: a)
        Error() << el << " ";

    set_scale(1);
}

void LabelManager::set_scale(float scale)
{
    Moonglobe::ResourceManager& manager = Moonglobe::ResourceManager::instance();
    auto font = manager.getFont();
    manager.fillGlyphCache(_cache);

    for (auto& label: labels) {
        label->set_scale(scale);
        label->set_font(scale, font, _cache);
    }
}

void LabelManager::draw(const Magnum::Matrix4& transformation, const Magnum::Matrix4& projection)
{
    Moonglobe::ResourceManager& manager = Moonglobe::ResourceManager::instance();
    auto font = manager.getFont();
    manager.fillGlyphCache(_cache);

    auto state = projection * transformation;
    for (auto& label: labels) {
        if (label->is_visible()) {
            label->draw(_shader, _cache, state);
        }
    }
}
