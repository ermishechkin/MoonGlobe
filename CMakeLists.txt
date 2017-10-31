cmake_minimum_required(VERSION 2.8.12)

#----------------------- compile options ------------------------
set(CMAKE_CXX_STANDARD 14)


#----------------------- add libs ------------------------

#module_path for magnum, magnum-plugins, corrade
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/modules/)

# lib components
set(WITH_SHADERS                   ON)
set(WITH_MESHTOOLS                 ON)
set(WITH_PRIMITIVES                ON)
set(WITH_TGAIMPORTER               ON)
set(WITH_JPEGIMPORTER              ON)
set(WITH_PNGIMPORTER               ON)
set(WITH_WINDOWLESSEGLAPPLICATION  ON)
set(WITH_JPEGIMPORTER              ON CACHE BOOL "22" FORCE)

# set target mobile version OpenGL
set(TARGET_GLES   ON)
set(TARGET_GLES2 OFF)

set(BUILD_STATIC ON)
set(BUILD_PLUGINS_STATIC ON)
set(BUILD_STATIC ON CACHE BOOL "" FORCE)

add_subdirectory(libjpeg)
find_package(JPEG REQUIRED)
add_subdirectory(libs/corrade)
add_subdirectory(libs/magnum)
add_subdirectory(libs/magnum-plugins)

find_package(Magnum REQUIRED
        Primitives
        MeshTools
        Shaders
        WindowlessEglApplication)

find_package(MagnumPlugins REQUIRED JpegImporter)

#wtf?
set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)

set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)

set(LIBS ${LIBS}
        MagnumPlugins::JpegImporter
        JPEG
        Magnum::WindowlessEglApplication
        Magnum::Primitives
        Magnum::Shaders
        Magnum::MeshTools
        Magnum::Magnum)

#----------------------- add resources ------------------------
corrade_add_resource(RES_LEVEL1 resources/level1.conf)
corrade_add_resource(RES_LEVEL2 resources/level2.conf)

set(RESOURCES ${RES_LEVEL1} ${RES_LEVEL2})

#----------------------- sources ------------------------
set(SOURCES
    src/Utils/to_str.cpp
    src/moonglobe_ndk.cpp
    src/Camera/Camera.cpp
    src/Fragment/Fragment.cpp
    src/MoonGlobe/MoonGlobe.cpp
    src/Utils/MeshGenerators.cpp
    src/MoonGlobeApplication.cpp
    src/ResourceManager/ResourceManager.cpp
)

#----------------------- headers ---------------------------
include_directories(libs/magnum/src/)
include_directories(src)

#----------------------- add target ------------------------
add_library(native-lib SHARED ${SOURCES} ${RESOURCES})

#----------------------- link libraries to target ------------------------
target_link_libraries(native-lib ${LIBS})
