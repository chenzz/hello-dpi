#include <QCoreApplication>
#include <iostream>
#include <cstdlib>
#include <qdebug.h>
#include "boost/any.hpp"
#include "plistcpp/Plist.hpp"
#include <fstream>
#include <qdebug.h>
#include <vector>
#include <cstdlib>
#include <utils.cpp>
#include "configfiledao.h"
#include "displaytab.h"
#include <QApplication>
#include "displaysao.h"
#include <QLabel>
#include "tabcontainer.h"
#include "globalvariables.h"
#include <QMessageBox>

using namespace std;

string appHome;

int main(int argc, char *argv[])
{


//    //读配置文件
//    ConfigFileDao* configFileDao = new ConfigFileDao();
//    vector<pair<string, string>*>* resultVector = configFileDao->getResolutionList(1552, 41006);
//    if (NULL == resultVector)
//    {
//        cout << "解析失败" << endl;
//        return -1;
//    }
//    for (int i = 0; i < resultVector->size(); i++)
//    {
//        pair<string, string>* aPair = resultVector->at(i);
//        cout << aPair->first << " " << aPair->second << endl;
//    }

//    //删除配置项
//    ConfigFileDao* configFileDao = new ConfigFileDao();
//    configFileDao->removeResolutionItem(1552, 41006, pair<string, string>("123", "123"));

      //写系统配置文件
//    configFileDao->addResolutionItem(1552, 41006, pair<string, string>("1600", "900"));

//    ofstream myfile;
//    myfile.open ("/System/Library/Displays/Contents/Resources/Overrides/DisplayVendorID-610/example.txt");
//    myfile << "Writing this to a file.\n";
//    myfile.close();

      //测试DisplayAccessDao
//    DisplaySao* displaySao = new DisplaySao();
//    string vendorId = displaySao->getVendorId();
//    string productId = displaySao->getProductId();

//    cout << vendorId << " " << productId << endl;
//    return 0;


//    启动界面
    QApplication application(argc, argv);

//    appHome = string(argv[0]);
//    appHome = appHome.substr(0, appHome.find_last_of("\/"));
//    appHome = appHome.substr(0, appHome.find_last_of("\/"));
//    appHome = appHome.substr(0, appHome.find_last_of("\/"));

//    DisplayTab tab;
//    tab.show();

    //Enable HiDPI Mode
    Utils::execShellCmd("sudo defaults write /Library/Preferences/com.apple.windowserver.plist DisplayResolutionEnabled -bool true");

    TabContainer containerTab;
    containerTab.show();

    return application.exec();
}

