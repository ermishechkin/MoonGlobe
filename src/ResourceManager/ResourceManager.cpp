#include "ResourceManager/ResourceManager.h"

using namespace Moonglobe;

ResourceManager* ResourceManager::manager = nullptr;
ResourceManagerDestroyer ResourceManager::destroyer;

ResourceManager::ResourceManager()
    : plugin_manager{MAGNUM_PLUGINS_IMPORTER_DIR}
    , importer(plugin_manager.loadAndInstantiate("JpegImporter"))
{
    // load jpeg plugin
    // CORRADE_PLUGIN_IMPORT(JpegImporter) в случае статической линковки
    if (!importer) {
        Magnum::Error() << "Cannot load importer plugin from" << plugin_manager.pluginDirectory();
        std::exit(1);
    }

    fillHashTable(1, 2, 4);
    fillHashTable(2, 5, 10);
    fillHashTable(3, 10, 20);
}

ResourceManager::~ResourceManager()
{
    // delete textures;
}

void ResourceManager::fillHashTable(size_t zoom_level, size_t rows, size_t columns)
{
    std::string level = std::to_string(zoom_level);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            std::string number = std::to_string(i * columns + j);
            std::string texture_id = level + "_" + number;
            std::string filename = "L" + level + "/" + number + ".jpg";
            // std::cout << texture_id << " " << filename << "\n";
            id_to_filename.insert(std::make_pair(texture_id, filename));
        }
    }
}

ResourceManager& ResourceManager::instance()
{
    if (manager == nullptr) {
        // std::cout << "\ncreate ResourceManager\n";
        manager = new ResourceManager();
        destroyer.initialize(manager);
    }
    return *manager;
}

std::shared_ptr<Magnum::Texture2D> ResourceManager::getTexture(TextureId texture_id)
{
    if (textures.find(texture_id) == textures.end()) {
        auto texture_sh_ptr = loadTexture(texture_id);
        textures.insert(std::make_pair(texture_id, texture_sh_ptr));
        return texture_sh_ptr;
    } else {
        return textures[texture_id];
    }
}

std::shared_ptr<Magnum::Texture2D> ResourceManager::loadTexture(TextureId id)
{
    std::cout << "\nloadTexture()" << std::endl;
    // std::cout << "\n texuture_id = " << id;
    std::string filename = id_to_filename[id];

    char s = id[0];

    std::string zoom_level = "level1";
    switch (s) {
        case '2':
            zoom_level = "level2";
            break;
        default:
            zoom_level = "level1";
            break;
    }

    const Magnum::Utility::Resource rs{zoom_level};
    if(!importer->openData(rs.getRaw(filename)))
        Magnum::Error() << "cannot load image\n";

    std::optional<Magnum::Trade::ImageData2D> image = importer->image2D(0);
    CORRADE_INTERNAL_ASSERT(image);

    // вывод параметров картинки
    // Magnum::Math::Vector2<size_t> v1;
    // Magnum::Math::Vector2<size_t> v2;
    // size_t size = 0;
    // std::tie(v1, v2, size) = image->dataProperties();
    //
    // std::cout << "\n" << v1.x() << " " << v1.y();// << " " << v1.z();
    // std::cout << "\n" << v2.x() << " " << v2.y();// << " " << v2.z();
    // std::cout << "\n" << size;

    std::shared_ptr<Magnum::Texture2D> new_texture = std::make_shared<Magnum::Texture2D>();

    // configure texture
    new_texture -> setWrapping(Magnum::Sampler::Wrapping::ClampToBorder)
        .setMagnificationFilter(Magnum::Sampler::Filter::Linear)
        .setMinificationFilter(Magnum::Sampler::Filter::Linear)
        .setStorage(1, Magnum::TextureFormat::Red, image->size())
        .setSubImage(0, {}, *image);

    return new_texture;
}

bool ResourceManager::freeTexture(TextureId id)
{
    textures.erase(id);
    return true;
}
