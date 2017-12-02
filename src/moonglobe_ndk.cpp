#include <jni.h>
#include "MoonGlobeApplication.h"
#include "android/asset_manager_jni.h"

MoonGlobeApplication *app = nullptr;

extern "C" {
    JNIEXPORT void JNICALL Java_com_example_alex_moonmap_CustomGLLib_Init(JNIEnv *env, jobject object, jobject assetManager);
    JNIEXPORT void JNICALL Java_com_example_alex_moonmap_CustomGLLib_Rotate(JNIEnv *env, jobject object, jfloat dx, jfloat dy);
    JNIEXPORT void JNICALL Java_com_example_alex_moonmap_CustomGLLib_Draw(JNIEnv *env, jobject object);
    JNIEXPORT void JNICALL Java_com_example_alex_moonmap_CustomGLLib_Zoom(JNIEnv *env, jobject object, jfloat scale);
}

bool inited = false;

JNIEXPORT void JNICALL
Java_com_example_alex_moonmap_CustomGLLib_Init(JNIEnv *env, jobject, jobject assetManager)
{
    Moonglobe::ResourceManager::clear();
    Moonglobe::ResourceManager::setAssetManager(AAssetManager_fromJava(env, assetManager));
    if (!inited) {
        CORRADE_PLUGIN_IMPORT(JpegImporter);
        CORRADE_PLUGIN_IMPORT(FreeTypeFont);
        inited = true;
    }
    app = new MoonGlobeApplication();
}

JNIEXPORT void JNICALL
Java_com_example_alex_moonmap_CustomGLLib_Rotate(JNIEnv *env, jobject object, jfloat dx, jfloat dy)
{
    app->rotateEvent(dx, dy);
}

JNIEXPORT void JNICALL
Java_com_example_alex_moonmap_CustomGLLib_Draw(JNIEnv *env, jobject object)
{
    app->drawEvent();
}

JNIEXPORT void JNICALL
Java_com_example_alex_moonmap_CustomGLLib_Zoom(JNIEnv *env, jobject object, jfloat scale)
{
    app->zoomEvent(scale);
}
