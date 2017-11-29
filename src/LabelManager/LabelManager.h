#ifndef LABEL_MANAGER_H
#define LABEL_MANAGER_H

#include <vector>
#include <fstream>
#include <Corrade/PluginManager/Manager.h>
#include <ResourceManager/ResourceManager.h>
// #include <MagnumPlugins/FreeTypeFont/FreeTypeFont.h>
#include "Label/Label.h"

class LabelManager
{
public:
    LabelManager();
    void draw(const Magnum::Matrix4& transformation, const Magnum::Matrix4& projection);
    void set_scale(float scale);


private:

    std::vector<std::shared_ptr<Label>> labels;
    Magnum::Text::DistanceFieldGlyphCache _cache;
    Magnum::Shaders::DistanceFieldVector3D _shader;

    // Magnum::Matrix4 _transformation;
    // Magnum::Matrix4 _projection;

};


#endif
