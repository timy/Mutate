#include <qxtglobalshortcut/qxtglobalshortcut.h>
#include <QApplication>
#include <QDesktopWidget>
#include <QObject>
#include <vector>
#include <QMessageBox>
#include <QProcess>
#include <iostream>
#include <memory>
#include <QIcon>
#include <QDir>
#include "widget.h"
#include "hotkey.h"
#include "returnbyscript.h"
#include "setting.h"
#include "singleapplication.h"
#include "config_parse.h"
#include "config.h"

using namespace std;

int main(int argc, char *argv[])
{
    qRegisterMetaType<QItemSelection>("QItemSelection");
    SingleApplication a(argc, argv, "WEI.QIANG");
    QDir *config = new QDir;
    if (!config->exists(QString::fromStdString(CFG_PATH)))
        config->mkdir(QString::fromStdString(CFG_PATH));
    delete config;
    if (a.isRunning()) {
        QMessageBox* x = new QMessageBox();
        x->setText(QObject::tr("One application may be running! Please try again."));
        x->exec();
        return -1;
    }
    a.setWindowIcon(QIcon(SEARCHICON));
    a.setQuitOnLastWindowClosed(false);
    std::shared_ptr<Widget> w(new Widget);
    try {
        shared_ptr<ConfigParse> cp(new ConfigParse(CFG_FILE));
        w->Height = std::stof(cp->getValue("default","Height"));
        for (const string& keyword: cp->getSections()) {
            if (keyword == "default") {
                string default_key = cp->getValue(keyword, "HotKey");
                QxtGlobalShortcut *shortcut =
                    new QxtGlobalShortcut(QKeySequence(default_key.c_str()), w.get());
                QObject::connect(shortcut, &QxtGlobalShortcut::activated,
                                 w.get(), &Widget::hotkeyPressed);
            }
            else {
                string default_key = cp->getValue(keyword, "HotKey");
                if (!default_key.empty()) {
                    QxtGlobalShortcut *shortcut;
                    if (cp->getValue(keyword, "Argument") == "need") {
                        shortcut = new QxtGlobalShortcut(QKeySequence(default_key.c_str()),
                                                         w.get(), keyword, true);
                    }
                    else {
                        shortcut = new QxtGlobalShortcut(QKeySequence(default_key.c_str()),
                                                         w.get(), keyword, false);
                    }
                    QObject::connect(shortcut, SIGNAL(activated(std::string, bool)),
                                     w.get(), SLOT(OtherhotkeyPressed(std::string, bool)));
                }
            }
        }
    }
    catch(...) {
        QxtGlobalShortcut *shortcut = new QxtGlobalShortcut(QKeySequence("Alt+d"), w.get());
        QObject::connect(shortcut, &QxtGlobalShortcut::activated,
                         w.get(), &Widget::hotkeyPressed);
    }
    std::shared_ptr<SearchApp> s(new SearchApp(w.get()));
    s->start();
    w->hotkeyPressed();
    return a.exec();
}
