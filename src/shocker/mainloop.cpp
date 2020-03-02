#include <fstream>
#include <string>
#include <sstream>

#include <boost/algorithm/string/trim.hpp>

#include <QtWidgets>
#include <QFont>

#include "shocker.hpp"

extern char _binary_stylesheet_css_start;
extern char _binary_stylesheet_css_end;
size_t stylesheet_size = (size_t)&_binary_stylesheet_css_end - (size_t)&_binary_stylesheet_css_start;

int main(int argc, char** argv) {
    QApplication* qapp = new QApplication(argc, argv);
    QWidget* qwin = new QWidget;
    qwin->setWindowFlags(Qt::WindowTransparentForInput);
    qwin->setWindowFlags(Qt::FramelessWindowHint);
    qwin->setWindowFlags(Qt::WindowDoesNotAcceptFocus);
    qwin->setWindowFlags(Qt::WindowStaysOnTopHint);
    qwin->setWindowFlags(Qt::X11BypassWindowManagerHint);

    QGridLayout wingrid(qwin);
    wingrid.setColumnMinimumWidth(0, 25);
    wingrid.setColumnStretch(0, 0);
    wingrid.setColumnMinimumWidth(1, 125);
    wingrid.setColumnStretch(1, 1);

    QIcon::setThemeName("breeze-dark");

    int battint = shocker::battery::get_level();
    std::string batt = std::to_string(battint);
    // for the label
    batt += "%";

    std::string str_batticon = shocker::battery::get_icon();

    QIcon batticon = QIcon::fromTheme(str_batticon.c_str());
    QLabel* batticonlabel = new QLabel;
    batticonlabel->setPixmap(batticon.pixmap(24, 24));
    wingrid.addWidget(batticonlabel, 0, 0);

    QLabel* battlabel = new QLabel(batt.c_str());
    QFont labelfont("sans-serif", 24);
    battlabel->setFont(labelfont);
    wingrid.addWidget(battlabel, 0, 1);

    QIcon clockicon = QIcon::fromTheme("clock");
    QLabel* clockiconlabel = new QLabel;
    clockiconlabel->setPixmap(clockicon.pixmap(24, 24));
    wingrid.addWidget(clockiconlabel, 1, 0);

    QDateTime now = QDateTime::currentDateTime();
    QLabel* timelabel = new QLabel(now.toString("hh:mm"));
    timelabel->setFont(labelfont);
    wingrid.addWidget(timelabel, 1, 1);

    QRect scr = qapp->desktop()->screenGeometry();

    char stylesheet[stylesheet_size];
    strncpy(stylesheet, &_binary_stylesheet_css_start, (stylesheet_size - 1));
    stylesheet[stylesheet_size - 1] = 0;

    qapp->setStyleSheet(stylesheet);

    qwin->setGeometry(
        /* X position */ (scr.width() / 2) - 75,
        /* Y position */ scr.height() - 250,
        /* win width  */ 150,
        /* win height */ 50
    );

    qwin->show();

    QTimer* off = new QTimer;
    off->setInterval(1500);
    off->setSingleShot(true);
    QObject::connect(off, SIGNAL(timeout()), qapp, SLOT(quit()));
    off->start();
    return qapp->exec();
}
