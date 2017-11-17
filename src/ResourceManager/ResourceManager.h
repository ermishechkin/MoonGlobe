#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <unordered_map>
#include <string>
#include <memory>
#include <iostream>

#include <Corrade/PluginManager/Manager.h>
#include <Magnum/Trade/AbstractImporter.h>
#include <Magnum/Trade/ImageData.h>
#include <Magnum/TextureFormat.h>
#include <Magnum/Texture.h>
#include <Magnum/Text/AbstractFont.h>
#include <Magnum/Text/DistanceFieldGlyphCache.h>
#include <MagnumPlugins/FreeTypeFont/FreeTypeFont.h>



typedef std::string TextureId;
class AAssetManager;

namespace Moonglobe
{

class ResourceManager;

class ResourceManagerDestroyer
{
public:
    ~ResourceManagerDestroyer() { delete instance; }
    void initialize(ResourceManager* manager) { instance = manager; }

private:
    ResourceManager* instance = nullptr;
};

// singleton
class ResourceManager
{
public:
    static ResourceManager& instance();
    static void clear();

    static void setAssetManager(AAssetManager *mgr);
    bool freeTexture(TextureId texture_id);
    std::shared_ptr<Magnum::Texture2D> getTexture(TextureId texture_id);

    void fillGlyphCache(Magnum::Text::GlyphCache& cache);
    std::shared_ptr<Magnum::Text::AbstractFont> getFont();

private:
    ResourceManager();
    ~ResourceManager();

    void loadFont();
    void fillHashTable(size_t zoom_level, size_t rows, size_t columns);
    std::shared_ptr<Magnum::Texture2D> loadTexture(TextureId texture_id);

    bool font_is_loaded;
    static std::shared_ptr<Magnum::Text::AbstractFont> font_importer;
    Magnum::PluginManager::Manager<Magnum::Text::AbstractFont> font_plugin_manager;

    std::unordered_map<TextureId, std::string> id_to_filename;
    static std::shared_ptr<Magnum::Trade::AbstractImporter> importer;
    std::unordered_map<TextureId, std::shared_ptr<Magnum::Texture2D>> textures;

    static ResourceManager* manager;
    static AAssetManager *assetManager;
    friend ResourceManagerDestroyer;
    static ResourceManagerDestroyer destroyer;
};

} // end Moonglobe

#endif
