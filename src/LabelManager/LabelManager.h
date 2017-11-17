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
    void draw(Magnum::Matrix4& transformation, Magnum::Matrix4& projection);

private:

    std::vector<std::shared_ptr<Label>> labels;
    Magnum::Text::DistanceFieldGlyphCache _cache;
    Magnum::Shaders::DistanceFieldVector3D _shader;

    // Magnum::Matrix4 _transformation;
    // Magnum::Matrix4 _projection;

};


#endif
