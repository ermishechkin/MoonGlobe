#ifndef LABEL_MANAGER_H
#define LABEL_MANAGER_H

#include <vector>

#include <Corrade/PluginManager/Manager.h>

#include "Label/Label.h"

class LabelManager
{
public:
    LabelManager();
    void draw(Magnum::Matrix4& transform, Magnum::Matrix4& projection);

private:
    Magnum::PluginManager::Manager<Magnum::Text::AbstractFont> _manager;
    std::unique_ptr<Text::AbstractFont> _font;

    Magnum::Text::DistanceFieldGlyphCache _cache;
    std::unique_ptr<Text::Renderer2D> _text2;
    Magnum::Shaders::DistanceFieldVector3D _shader;

    // Magnum::Matrix4 _transformation;
    // Magnum::Matrix4 _projection;

};


#endif
