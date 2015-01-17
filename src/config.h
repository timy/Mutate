#ifndef CONFIG_H
#define CONFIG_H
#include <QProcess>
#include <sstream>
#include <string>
#include <QDesktopWidget>
#include <QApplication>
#include <QIcon>
#include <QStringList>

#define rowsize 51
#define beginheight 125
#define iconsize 42
#define listwidgety 91
#define PATH getHomePath()

#define ICON ":/icons/icons/search.png"
#define INTERNETICON ":/icons/icons/workflow_openurl.png"
#define SETICON ":/icons/icons/setting.png"
#define SEARCHICON ":/icons/icons/google.png"
#define EXEICON ":/icons/icons/application-x-executable.png"

#define SEARCHURL "https://www.google.com/search?q="

#define CFG_PATH (std::string(PATH) + "/.config/Mutate")
#define FREQUENCEPATH (CFG_PATH + "/frequence")
#define CFG_FILE (CFG_PATH + "/config.ini")
#define URLPATH (CFG_PATH + "/url.history")
#define APPSEARCHPATH ("/usr/share/applications")
//#define APPSEARCHPATH2 ("/usr/share/app-install/desktop")
#define ICONSEARCHPATHS { std::string("/usr/share/icons"),      \
            std::string("/usr/share/app-install/icons"),        \
            PATH + "/.local/share/icons",                       \
            }

#define MAXADDTOLISTSIZE 9
#define MAXSORTSIZE 50
#define MAXPRINTSIZE 9 // max number of rows to display

#define MOVE CenterToScreen(this);

std::string getHomePath();
void CenterToScreen(QWidget* widget);
#endif // CONFIG_H
