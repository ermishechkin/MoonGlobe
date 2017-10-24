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

#include "configure.h"

typedef std::string TextureId;

namespace Moonglobe
{

class ResourceManager;

class ResourceManagerDestroyer
{
public:
    ~ResourceManagerDestroyer() { delete instance; }
    void initialize(ResourceManager* manager) { instance = manager; }

private:
    ResourceManager* instance;
};

// signleton
class ResourceManager
{
public:
    static ResourceManager& instance();

    bool freeTexture(TextureId texture_id);
    std::shared_ptr<Magnum::Texture2D> getTexture(TextureId texture_id);

private:
    std::shared_ptr<Magnum::Texture2D> loadTexture(TextureId texture_id);

    ResourceManager();
    ~ResourceManager();

    Magnum::PluginManager::Manager<Magnum::Trade::AbstractImporter> plugin_manager;
    std::shared_ptr<Magnum::Trade::AbstractImporter> importer;
    std::unordered_map<TextureId, std::string> id_to_filename;
    std::unordered_map<TextureId, std::shared_ptr<Magnum::Texture2D>> textures;
    static ResourceManager* manager;
    friend ResourceManagerDestroyer;
    static ResourceManagerDestroyer destroyer;
};

} // end Moonglobe

#endif
