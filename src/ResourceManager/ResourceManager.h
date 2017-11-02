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

private:
    ResourceManager();
    ~ResourceManager();

    void fillHashTable(size_t zoom_level, size_t rows, size_t columns);


    std::shared_ptr<Magnum::Texture2D> loadTexture(TextureId texture_id);
    Magnum::PluginManager::Manager<Magnum::Trade::AbstractImporter> plugin_manager;
    static std::shared_ptr<Magnum::Trade::AbstractImporter> importer;
    std::unordered_map<TextureId, std::string> id_to_filename;
    std::unordered_map<TextureId, std::shared_ptr<Magnum::Texture2D>> textures;
    static ResourceManager* manager;
    static AAssetManager *assetManager;
    friend ResourceManagerDestroyer;
    static ResourceManagerDestroyer destroyer;
};

} // end Moonglobe

#endif
