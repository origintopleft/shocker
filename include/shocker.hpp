#pragma once
#include <string>
#include <QtWidgets>

namespace shocker {
    namespace battery {
        extern int get_level();
        extern std::string get_icon();
    }

    namespace ui {
        extern void show_battery_window();
        extern QApplication* qapp;
    }
}
