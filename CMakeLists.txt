cmake_minimum_required(VERSION 2.8.12)

if (NOT PC_BUILD)
    message(android_version)
    #----------------------- compile options ------------------------
    set(CMAKE_CXX_STANDARD 14)

    #----------------------- add libs ------------------------

    #module_path for magnum, magnum-plugins, corrade
    set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/modules/)

    # lib components
    set(WITH_FREETYPEFONT              ON)
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
        Magnum::Magnum
    )

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

else()
    message(PC_VERSION)
    project(m2-sphere)
    get_filename_component(M2_ROOT "${CMAKE_SOURCE_DIR}" ABSOLUTE)

    if (NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE Debug)# CACHE String)
    endif()

    if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        set(M2_DEBUG ON)
        set(M2_BIN_DIR "${M2_ROOT}/bin/Debug")
        set(M2_LIB_DIR "${M2_ROOT}/bin/Debug/libs")
        set(CMAKE_CONFIGURATION_TYPES "Debug" CACHE STRING "" FORCE)
    elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
        set(M2_RELEASE ON)
        set(M2_BIN_DIR "${M2_ROOT}/bin/Release")
        set(M2_LIB_DIR "${M2_ROOT}/bin/Release/libs")
        set(CMAKE_CONFIGURATION_TYPES "Release" CACHE STRING "" FORCE)
    else()
        message(FATAL_ERROR "Invalid CMAKE_BUILD_TYPE value (Debug|Release)")
    endif()

    message(STATUS "binaries output: " ${M2_BIN_DIR})
    message(STATUS "libraries output: " ${M2_LIB_DIR})

    # ---------------------------  paths  ---------------------------
    set(CMAKE_EXECUTABLE_OUTPUT_DIRECTORY_DEBUG   ${M2_BIN_DIR})
    set(CMAKE_EXECUTABLE_OUTPUT_DIRECTORY_RELEASE ${M2_BIN_DIR})
    set(CMAKE_EXECUTABLE_OUTPUT_PATH              ${M2_BIN_DIR})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG      ${M2_LIB_DIR})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE    ${M2_LIB_DIR})
    set(CMAKE_LIBRARY_OUTPUT_PATH                 ${M2_LIB_DIR})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG      ${M2_BIN_DIR})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE    ${M2_BIN_DIR})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY            ${M2_BIN_DIR})

    #----------------------- compile options ------------------------
    set(CMAKE_CXX_STANDARD 14)


    #----------------------- add libs ------------------------

    #module_path for magnum, magnum-plugins, corrade
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/libs/modules/")
    set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/bin/libs)

    # lib components
    set(WITH_TEXT            ON)
    set(WITH_FREETYPEFONT    ON)
    set(WITH_SHADERS         ON)
    set(WITH_MESHTOOLS       ON)
    set(WITH_PRIMITIVES      ON)
    set(WITH_TGAIMPORTER     ON)
    set(WITH_SDL2APPLICATION ON)
    set(WITH_JPEGIMPORTER    ON)
    # set(WITH_PNGIMPORTER     ON)
    set(WITH_JPEGIMPORTER    ON CACHE BOOL "22" FORCE)

    # set target mobile version OpenGL
    set(TARGET_GLES ON)
    set(BUILD_STATIC ON)
    set(BUILD_PLUGINS_STATIC ON)
    # set(BUILD_STATIC ON CACHE BOOL "" FORCE)
    # set(BUILD_PLUGINS_STATIC ON CACHE BOOL "" FORCE)


    add_subdirectory(libs/freetype2)
    add_subdirectory(libs/libjpeg)
    find_package(JPEG REQUIRED)
    add_subdirectory(libs/corrade)
    add_subdirectory(libs/magnum)
    add_subdirectory(libs/magnum-plugins)

    find_package(Magnum REQUIRED
        Primitives
        MeshTools
        Shaders
        Text
        Sdl2Application)

    find_package(MagnumPlugins REQUIRED
                 JpegImporter
                 FreeTypeFont)

    # message(${UNIX})
    message(Magnum_Plugins_dir: ${MagnumPlugins_JpegImporter_FOUND})
    message(Magnum_Plugins_dir: ${MagnumPlugins_FreeTypeFont_FOUND})

    #wtf?
    set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)

    # set(MAGNUM_PLUGINS_IMPORTER_DIR "${M2_LIB_DIR}")

    set(LIBS ${LIBS}
        MagnumPlugins::FreeTypeFont
        MagnumPlugins::JpegImporter
        freetype
        JPEG
        Magnum
        Magnum::Application
        Magnum::Primitives
        Magnum::Shaders
        Magnum::MeshTools
        Magnum::Text
    )

    message(${LIBS})
    #----------------------- apply configurations files ------------------------
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/configure.h.cmake
        ${CMAKE_CURRENT_SOURCE_DIR}/src/configure.h)

    include_directories(${CMAKE_CURRENT_BINARY_DIR}/src)

    #----------------------- add resources ------------------------
    corrade_add_resource(RES_LEVEL1 resources/level1.conf)
    corrade_add_resource(RES_LEVEL2 resources/level2.conf)
    corrade_add_resource(RES_LEVEL3 resources/level3.conf)
    corrade_add_resource(FONT resources/font.conf)
    corrade_add_resource(FEATURES resources/features.conf)
    set(RESOURCES ${FONT} ${RES_LEVEL1} ${RES_LEVEL2} ${FEATURES}) # ${RES_LEVEL3})

    #----------------------- sources ------------------------
    set(SOURCES
        src/pc/main.cpp
        src/Label/Label.cpp
        src/Camera/Camera.cpp
        src/Fragment/Fragment.cpp
        src/MoonGlobe/MoonGlobe.cpp
        src/Utils/MeshGenerators.cpp
        src/Utils/to_str.cpp
        src/pc/PCMoonGlobeApplication.cpp
        src/LabelManager/LabelManager.cpp
        src/ResourceManager/ResourceManager.cpp
    )

    #----------------------- headers ---------------------------
    include_directories(libs/magnum/src/)
    include_directories(src)

    #----------------------- add target ------------------------
    add_executable(${PROJECT_NAME} ${SOURCES} ${RESOURCES})

    #----------------------- link libraries to target ------------------------
    target_link_libraries(${PROJECT_NAME} ${LIBS})
endif()
