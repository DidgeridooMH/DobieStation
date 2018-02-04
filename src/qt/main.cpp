#include <QApplication>
#include "emuwindow.hpp"

using namespace std;

int main(int argc, char** argv)
{
    QApplication a(argc, argv);
    EmuWindow* window = new EmuWindow();
    if (argc >= 3)
    {
        const char* bios_name = argv[1];
        const char* ELF_name = argv[2];
        if (window->init(bios_name, ELF_name))
            return 1;
    }
    else
    {
        printf("Arguments: bios_file ELF_file\n");
        return 0;
    }
    bool limitFramerate = true;
    while (window->running())
    {
        //Loop a.processEvents() while instantaneous framerate exceeds 60
        //Only if limit framerate is true
        a.processEvents();
        window->emulate();
        if (limitFramerate)
            window->limitFrameRate();
        window->updateWindowTitle();
        window->resetFrameTime();
    }

    return 0;
}
