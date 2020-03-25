#include <iostream>
#include <unistd.h>

#include <QtWidgets>
#include <QFont>

#include "external/joystick.hpp"
#include "shocker.hpp"

using namespace shocker;

QApplication* shocker::ui::qapp;

int main(int argc, char** argv) {
    ui::qapp = new QApplication(argc, argv);
    bool joy_available = false;
    Joystick* js;
    while (!joy_available) {
        js = new Joystick();
        joy_available = js->isFound();
        if (!joy_available) {
            delete js; // no leaks
            usleep(1000);
        }
    }
    std::cout << "controller picked up" << std::endl;

    JoystickEvent js_event;
    while (true) {
        if (js->sample(&js_event)) {
            if (js_event.isButton() && js_event.number == 10 && js_event.value == 1) {
                shocker::ui::show_battery_window();
                break;
            }
        }
        usleep(750);
    }
    return ui::qapp->exec();
}
