#include <fstream>
#include <string>
#include <sstream>

#include <QtWidgets>
#include <QFont>

#include <boost/algorithm/string/trim.hpp>

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

    // TODO: not hard code this
    std::ifstream battfile("/sys/class/power_supply/sony_controller_battery_f4:93:9f:99:10:90/capacity");
    std::stringstream battstream;
    battstream << battfile.rdbuf();
    battfile.close();

    QIcon::setThemeName("breeze-dark");

    std::string batt = battstream.str();
    boost::algorithm::trim(batt);
    int battint = std::stoi(batt);

    std::string str_batticon = "battery-";
    if (battint == 100) { str_batticon += "100"; }
    else {
        str_batticon += "0";
        str_batticon += batt.at(0); // percentage rounded down
        str_batticon += "0";
    }

    std::ifstream chargefile("/sys/class/power_supply/sony_controller_battery_f4:93:9f:99:10:90/status");
    std::stringstream chargestream;
    chargestream << chargefile.rdbuf();
    chargefile.close();

    std::string charge = chargestream.str();
    boost::algorithm::trim(charge);
    if (charge == "Charging") { str_batticon += "-charging"; }

    // for the label
    batt += "%";

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

    qwin->setStyleSheet(
    "border-radius: 15px;"
    "margin-left: 0px;;"
    "margin-right: 0px;"
    "background-color: rgba(51, 51, 51, 175);"
    "color: #cfcfcf;"
    "text-align: center;"
    );

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
