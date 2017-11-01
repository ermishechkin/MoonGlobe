#include <jni.h>
#include "MoonGlobeApplication.h"
#include "ResourceManager/ResourceManager.h"

MoonGlobeApplication *app = nullptr;

extern "C" {
    JNIEXPORT void JNICALL Java_com_example_alex_moonmap_CustomGLLib_Init(JNIEnv *env, jobject object);
    JNIEXPORT void JNICALL Java_com_example_alex_moonmap_CustomGLLib_Rotate(JNIEnv *env, jobject object, jfloat dx, jfloat dy);
    JNIEXPORT void JNICALL Java_com_example_alex_moonmap_CustomGLLib_Rotate2(JNIEnv *env, jobject object, jfloat x1, jfloat y1, jfloat x2, jfloat y2);
    JNIEXPORT void JNICALL Java_com_example_alex_moonmap_CustomGLLib_Draw(JNIEnv *env, jobject object);
    JNIEXPORT void JNICALL Java_com_example_alex_moonmap_CustomGLLib_Zoom(JNIEnv *env, jobject object, jfloat scale);
}

JNIEXPORT void JNICALL
Java_com_example_alex_moonmap_CustomGLLib_Init(JNIEnv *, jobject)
{
    Moonglobe::ResourceManager::clear();
    app = new MoonGlobeApplication();
}

JNIEXPORT void JNICALL
Java_com_example_alex_moonmap_CustomGLLib_Rotate(JNIEnv *env, jobject object, jfloat dx, jfloat dy)
{
    app->rotateEvent(dx, dy);
}

JNIEXPORT void JNICALL
Java_com_example_alex_moonmap_CustomGLLib_Rotate2(JNIEnv *env, jobject object, jfloat x1, jfloat y1, jfloat x2, jfloat y2)
{
    app->rotateEvent2(x1, y1, x2, y2);
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
