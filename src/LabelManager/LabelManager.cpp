#include "LabelManager/LabelManager.h"
#include "configure.h"
#include <iostream>

LabelManager::LabelManager()
    : _manager(MAGNUM_PLUGINS_FONT_DIR)
    , _cache(Vector2i(2048), Vector2i(512), 22)
{
    Magnum::PluginManager::Manager<Magnum::Text::AbstractFont> manager{MAGNUM_PLUGINS_FONT_DIR};
    // std::cout << manager.pluginDirectory() << "\n";
    _font = manager.loadAndInstantiate("JpegImporter");
    if (!_font)
        std::exit(1);

    /* Open the font and fill glyph cache */
    Magnum::Utility::Resource rs("fonts");
    if(!_font->openSingleData(rs.getRaw("DejaVuSans.ttf"), 110.0f)) {
        Error() << "Cannot open font file";
        std::exit(1);
    }

    _font->fillGlyphCache(_cache, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789:-+,.!°ěäЗдравстуймиγειασουτνκόμ ");

    Magnum::Renderer::enable(Renderer::Feature::Blending);
    Magnum::Renderer::setBlendFunction(Renderer::BlendFunction::SourceAlpha, Renderer::BlendFunction::OneMinusSourceAlpha);
    Magnum::Renderer::setBlendEquation(Renderer::BlendEquation::Add, Renderer::BlendEquation::Add);
}


void LabelManager::draw(Magnum::Matrix4& transformation, Magnum::Matrix4& projection)
{
    return;

    _shader.setTransformationProjectionMatrix(projection * transformation);

    Label label("abcdef");
    label.setFont(_font, _cache);
    label.draw(_shader, _cache);
}
