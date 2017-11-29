#include "ResourceManager/ResourceManager.h"
#include "Utils/to_str.h"
#include "android/asset_manager.h"


using namespace Moonglobe;

std::shared_ptr<Magnum::Text::AbstractFont> ResourceManager::font_importer;
std::shared_ptr<Magnum::Trade::AbstractImporter> ResourceManager::importer;
ResourceManager* ResourceManager::manager = nullptr;

ResourceManagerDestroyer ResourceManager::destroyer;
AAssetManager *ResourceManager::assetManager = nullptr;

ResourceManager::ResourceManager()
    : font_is_loaded(false)
{
    // std::cout << "kek" << std::endl;
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
    std::string level = to_str(zoom_level);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            std::string number = to_str(i * columns + j);
            std::string texture_id = level + "_" + number;
            std::string filename = "L" + level + "/" + number + ".jpg";
            // std::cout << texture_id << " " << filename << "\n";
            id_to_filename.insert(std::make_pair(texture_id, filename));
        }
    }
}

ResourceManagerDestroyer::~ResourceManagerDestroyer()
{
    delete instance;
}

ResourceManager& ResourceManager::instance()
{
    if (manager == nullptr) {
        // std::cout << "\ncreate ResourceManager\n";
        manager = new ResourceManager();
        destroyer.initialize(manager);
    }

    if (importer == nullptr &&
        font_importer == nullptr)
    {
        Magnum::PluginManager::Manager<Magnum::Trade::AbstractImporter> importer_manager;
        importer = importer_manager.loadAndInstantiate("JpegImporter");
        if (!importer) {
            std::exit(1);
        }
        std::cout << "jpeg_importer_loaded\n" << std::endl;

        // Magnum::PluginManager::Manager<Magnum::Text::AbstractFont> font_plugin_manager;
        font_importer = manager->font_plugin_manager.loadAndInstantiate("FreeTypeFont");
        if (!font_importer)
            std::exit(1);

        font_importer->initialize();
        //Magnum::Text::FreeTypeFont::initialize();
        std::cout << "font_plugin_loaded\n" << std::endl;

    }
    return *manager;
}

void ResourceManager::clear()
{
//    delete manager;
    manager = nullptr;
}

void ResourceManager::setAssetManager(AAssetManager *mgr)
{
    assetManager = mgr;
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
        case '3':
            zoom_level = "level3";
            break;
        default:
            zoom_level = "level1";
            break;
    }

    AAsset *asset = AAssetManager_open(assetManager, filename.c_str(), AASSET_MODE_BUFFER);
    const char *raw_data = reinterpret_cast<const char *>(AAsset_getBuffer(asset));
    off_t data_size = AAsset_getLength(asset);
    Corrade::Containers::ArrayView<const char> data(raw_data, data_size);
    if(!importer->openData(data))
        Magnum::Error() << "cannot load image\n";
    AAsset_close(asset);

    std::cout << filename << std::endl;

    std::optional<Magnum::Trade::ImageData2D> image = importer->image2D(0);
    CORRADE_INTERNAL_ASSERT(image);

    std::shared_ptr<Magnum::Texture2D> new_texture = std::make_shared<Magnum::Texture2D>();

    // configure texture
    new_texture -> setWrapping(Magnum::Sampler::Wrapping::ClampToBorder)
        .setMagnificationFilter(Magnum::Sampler::Filter::Linear)
        .setMinificationFilter(Magnum::Sampler::Filter::Linear)
        .setStorage(1, Magnum::TextureFormat::Luminance, image->size())
        .setSubImage(0, {}, *image);

    return new_texture;
}

void ResourceManager::fillGlyphCache(Magnum::Text::GlyphCache& cache)
{
    static bool filled = false;
    if (filled)
        return;

    filled = true;
    std::cout << "fillGlyphCache()\n";
    if (!font_is_loaded)
        loadFont();

    font_importer->fillGlyphCache(
        cache,
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 "
    );
    std::cout << "end fillGlyphCache()\n";
}

std::shared_ptr<Magnum::Text::AbstractFont> ResourceManager::getFont()
{
    return font_importer;
}

void ResourceManager::loadFont()
{
    font_importer->initialize();
    std::cout << "loadFont()\n";
    Magnum::Utility::Resource rs("fonts");
    if(!font_importer->openSingleData(rs.getRaw("font1.ttf"), 110.0f)) {
        std::cout << "\nCannot open font file\n";
        std::exit(1);
    }
    font_is_loaded = true;
    std::cout << "end loadFont()\n";
}

bool ResourceManager::freeTexture(TextureId id)
{
    textures.erase(id);
    return true;
}
