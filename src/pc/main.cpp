#include "pc/PCMoonGlobeApplication.h"
#include <iostream>
#include "Fragment/Fragment.h"
// MAGNUM_APPLICATION_MAIN(Magnum::PCMoonGlobeApplication)
#include <Magnum/Magnum.h>

int main(int argc, char** argv) {
    CORRADE_PLUGIN_IMPORT(FreeTypeFont);
    CORRADE_PLUGIN_IMPORT(JpegImporter);

    std::cout << "kek1" << std::endl;
    Magnum::PCMoonGlobeApplication app({argc, argv});
    std::cout << "kek2" << std::endl;
    return app.exec();
}

// int WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
//     if(FAILED(Windows::Foundation::Initialize(RO_INIT_MULTITHREADED)))
//         return 1;
//     return SDL_WinRTRunApp(main, nullptr);
// }
