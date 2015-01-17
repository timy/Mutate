#include "config.h"
#include "widget.h"

std::string getHomePath()
{
    QStringList environment = QProcess::systemEnvironment();
    QString str;
    std::string pathHome;
    foreach (str, environment) {
        if (str.startsWith("HOME=")) {
            pathHome = str.toStdString().substr(5, str.size());
        }
    }
    return pathHome;
}

void CenterToScreen(QWidget* widget)
{
    if (!widget)
        return;
    QDesktopWidget* desktop = QApplication::desktop();
    QRect desk_rect = desktop->screenGeometry(desktop->screenNumber(QCursor::pos()));
    int x = desk_rect.left() + (desk_rect.width() - widget->width()) / 2;
    int y = (int)(0.2 * (desk_rect.height() - beginheight - rowsize * (MAXPRINTSIZE - 1)));
    widget->move(x, y);
}
