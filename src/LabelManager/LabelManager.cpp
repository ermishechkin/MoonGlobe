#include "LabelManager/LabelManager.h"
#include "configure.h"
#include <iostream>
#include <cmath>
#include <Coords/Coords.h>
#include <tuple>
#include <Corrade/Utility/Resource.h>
#include <sstream>

LabelManager::LabelManager()
    : _cache(Vector2i(2048), Vector2i(512), 22)
{
    Corrade::Utility::Resource rs("features");
    std::stringstream in(rs.get("parsed"));

    std::string name, diametr, latt, longt;
    for (int i = 0; i < 4000; i++) {
        in >> name;
        in >> diametr;
        while (!('0' <= diametr[0] && diametr[0] <= '9')) {
            name += diametr;
            in >> diametr;
        }
        in >> latt >> longt;
        Error() << name << " " << diametr << " " << latt << " " << longt << "\n";
        float theta = (std::stof(latt) + 90.0) / 90.0 * M_PI;
        float phi = (std::stof(longt) + 180.0) / 360.0 * 2 * M_PI;;
        Coords c(theta, phi);
        compute_decart_coord(c);

        labels.push_back(std::shared_ptr<Label> (new Label(name, std::stod(diametr), {c.x, c.y, c.z})));
    }
}


void LabelManager::draw(Magnum::Matrix4& transformation, Magnum::Matrix4& projection)
{
    _shader.setTransformationProjectionMatrix(projection * transformation);
    Moonglobe::ResourceManager& manager = Moonglobe::ResourceManager::instance();

    auto font = manager.getFont();
    static bool cond = false;
    if (!cond) {
        manager.fillGlyphCache(_cache);
        cond = true;
    }

    for (auto& label: labels) {
        if (label->is_visible()) {
            label->setFont(font, _cache);
            auto state = projection * transformation;
            label->draw(_shader, _cache, state);
        }
    }
}
