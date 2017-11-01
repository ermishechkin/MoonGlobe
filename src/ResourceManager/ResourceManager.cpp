#include "ResourceManager/ResourceManager.h"
#include "Utils/to_str.h"

using namespace Moonglobe;

std::shared_ptr<Magnum::Trade::AbstractImporter> ResourceManager::importer;
ResourceManager* ResourceManager::manager = nullptr;
ResourceManagerDestroyer ResourceManager::destroyer;

ResourceManager::ResourceManager()
{
    id_to_filename.insert({std::make_pair("0_0", "L1/0.jpg"),
                           std::make_pair("0_1", "L1/1.jpg"),
                           std::make_pair("0_2", "L1/2.jpg"),
                           std::make_pair("0_3", "L1/3.jpg"),
                           std::make_pair("0_4", "L1/4.jpg"),
                           std::make_pair("0_5", "L1/5.jpg"),
                           std::make_pair("0_6", "L1/6.jpg"),
                           std::make_pair("0_7", "L1/7.jpg")});

    std::string level = "1_";
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 10; j++) {
            std::string number = to_str(i * 10 + j);
            std::string texture_id = level + number;
            std::string filename = "L2/" + number + ".jpg";
            // std::cout << texture_id << " " << filename << "\n";
            id_to_filename.insert(std::make_pair(texture_id, filename));
        }
    }
}

ResourceManager::~ResourceManager()
{
    // delete textures;
}

ResourceManagerDestroyer::~ResourceManagerDestroyer()
{
    delete instance;
}

ResourceManager& ResourceManager::instance()
{
    if (importer == nullptr) {
        Magnum::PluginManager::Manager<Magnum::Trade::AbstractImporter> plugin_manager;
        importer = plugin_manager.loadAndInstantiate("JpegImporter");
        if (!importer) {
            std::exit(1);
        }
    }
    if (manager == nullptr) {
        // std::cout << "\ncreate ResourceManager\n";
        manager = new ResourceManager();
        destroyer.initialize(manager);
    }
    return *manager;
}

void ResourceManager::clear()
{
//    delete manager;
    manager = nullptr;
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
    std::cout << "\n texuture_id = " << id;
    std::string filename = id_to_filename[id];

    char s = id[0];

    std::string zoom_level = "level1";
    switch (s) {
        case '1':
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
        .setStorage(1, Magnum::TextureFormat::Luminance, image->size())
        .setSubImage(0, {}, *image);

    return new_texture;
}

bool ResourceManager::freeTexture(TextureId id)
{
    textures.erase(id);
    return true;
}
