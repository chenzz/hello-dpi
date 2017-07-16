#include "configfiledao.h"

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
#include <sstream>
#include "constans.h"
#include <cstring>
#include "globalvariables.h"

using namespace std;

ConfigFileDao::ConfigFileDao()
{
}


char * buildConfigFilePath(int vendorId, int productId)
{
    char hexVendorId[33];
    sprintf(hexVendorId, "%x", vendorId);

    char hexProductId[33];
    sprintf(hexProductId, "%x", productId);

    //构造配置文件路径
    char* configFile = new char[300];
    strcat(configFile, SYSTEM_CONFIG_FILE_PATH);
    strcat(configFile, "/DisplayVendorID-");
    strcat(configFile, hexVendorId);
    strcat(configFile, "/DisplayProductID-");
    strcat(configFile, hexProductId);

    return configFile;
}

vector<pair<string, string> *>* ConfigFileDao::getResolutionList(int vendorId, int productId)
{
    map<string, boost::any> dict;
    vector<pair<string, string>*>* resultList = new vector<pair<string, string>*>();
    char* configFilePath = buildConfigFilePath(vendorId, productId);

    ifstream fin(configFilePath);
    //文件不存在
    if (!fin) {
        //创建文件所在文件夹
        string configFileDirPath = string(configFilePath);
        configFileDirPath = configFileDirPath.substr(0, configFileDirPath.find_last_of("\/"));
        Utils::execShellCmd(string("mkdir -p ") + configFileDirPath);

        //把sample文件 copy 到系统路径下
        string sampleConfigFilePath = appHome + "/Contents/Resources/DisplayProductID-a02e";

        string cmd = "cp " + sampleConfigFilePath + " " + configFilePath;
        qDebug() << QString::fromStdString(cmd);
        Utils::execShellCmd(cmd);
    }

//    cout << configFilePath << endl;
    Plist::readPlist(configFilePath, dict);
    boost::any temp = (dict["scale-resolutions"]);
    std::vector<boost::any> resolutionArray = boost::any_cast<std::vector<boost::any>>(temp);

    //处理奇数行的数据 （因为偶数行的数据都是奇数行的两倍）
    for (int i = 0; i < resolutionArray.size(); i+=2)
    {
        vector<char> crResolution = boost::any_cast<vector<char>>(resolutionArray[i]);

        string resolution;

//        //如果数据的列数不是16列，说明数据错误
//        if (crResolution.size() != 16)
//        {
//            return NULL;
//        }

        //处理前8组数据，因为后8组数据都是固定的数值
        //只需要第3、4组数据和7、8组数据
        //每两组数据合并成一组数据
        char buffer[50];
        sprintf(buffer, "%d", Utils::chars2Short(crResolution[2], crResolution[3]));
        string width = string(buffer);
        sprintf(buffer, "%d", Utils::chars2Short(crResolution[6], crResolution[7]));
        string height = string(buffer);
        resultList->push_back(new pair<string, string>(width, height));
    }

    return resultList;
}

/**
 * @brief createMessage
 * @param dict
 * PListCpp的测试代码
 */
static void createMessage(map<string, boost::any>& dict)
{
        Plist::Date date;
        date.setTimeFromAppleEpoch(338610664);

        dict["testDate"] = date;
        dict["testInt"] = int(-3455);
        dict["testInt32"] = int32_t(-3455);
        dict["testInt64"] = int64_t(-3455);
        dict["testShort"] = short(3455);
        dict["testLong"] = long(-3455);
        dict["testDouble"] = 1.34223;
        dict["testFloat"] = 1.34223f;
        dict["testBoolTrue"] = true;
        dict["testBoolFalse"] = false;
        std::ifstream stream(TEST_IMAGE, std::ios::binary);
        if(!stream)
            throw std::runtime_error("Can't open file: testImage.png");

        int start = stream.tellg();
        stream.seekg(0, std::ifstream::end);
        int size = ((int) stream.tellg()) - start;
        std::vector<char> actualData(size);
        if(size > 0)
        {
            stream.seekg(0, std::ifstream::beg);
            stream.read( (char *)&actualData[0], size );
        }
        else
        {
            throw std::runtime_error("Can't read zero length data");
        }

        dict["testImage"] = actualData;
        vector<boost::any> array(2);
        array[0] = 34;
        array[1] = string("string item in array");
        dict["testArray"] = array;
        dict["testString"] = string("hello there");
        dict["testEmptyString"] = string("");

        map<string, boost::any> innerDict;
        innerDict["test string"] = string("inner dict item");
        dict["testDict"] = innerDict;

        innerDict.clear();
        array.resize(256);

        for(int i = 0; i < 256; ++i)
        {
            stringstream ss;
            if(i < 10)
                ss<<"00";
            if((i >= 10) && (i < 100))
                ss<<"0";
            ss<<i;
            array[i] = i;
            innerDict[ss.str()] = i;
        }
        dict["testArrayLarge"] = array;
        dict["testDictLarge"] = innerDict;

}

//把width和height这两个变量转换成对应的 char数组
vector<char> convertWidthHeight2CharArrayInPlist(pair<string, string> resolution)
{
    //获取width和height
    string width = resolution.first;
    string height = resolution.second;

    //string 转成 unsigned short
    unsigned short usWidth = (unsigned short)stoi(width);
    unsigned short usHeight = (unsigned short)stoi(height);

    //一个short转成两个char
    pair<unsigned char, unsigned char> charPairWidth = Utils::short2Chars(usWidth);
    pair<unsigned char, unsigned char> charPairHeight = Utils::short2Chars(usHeight);

    //手动构造符合系统配置规范的char数组
    vector<char> resolutionItem;
    resolutionItem.push_back(0);
    resolutionItem.push_back(0);
    resolutionItem.push_back(charPairWidth.first);
    resolutionItem.push_back(charPairWidth.second);
    resolutionItem.push_back(0);
    resolutionItem.push_back(0);
    resolutionItem.push_back(charPairHeight.first);
    resolutionItem.push_back(charPairHeight.second);
    resolutionItem.push_back(0);
    resolutionItem.push_back(0);
    resolutionItem.push_back(0);
    resolutionItem.push_back(1);
    resolutionItem.push_back(0);
    resolutionItem.push_back(32);
    resolutionItem.push_back(0);
    resolutionItem.push_back(0);

    return resolutionItem;
}

//添加新的分辨率配置项
void ConfigFileDao::addResolutionItem(int vendorId, int productId, pair<string, string> resolution)
{
    char *configFilePath = buildConfigFilePath(vendorId, productId);

    //解析现有的配置文件
    map<string, boost::any> dict;
    Plist::readPlist(configFilePath, dict);

    //解析出resoutionLists
    boost::any temp = dict["scale-resolutions"];
    vector<boost::any> resolutionArray = boost::any_cast<std::vector<boost::any>>(temp);

    //把width和height这两个变量转换成对应的 char数组
    vector<char> resolutionItem1 = convertWidthHeight2CharArrayInPlist(resolution);
    resolutionArray.push_back(resolutionItem1);

    //把width*2和height*2 这两个变量转换成对应的 char数组
    pair<string, string> resolution2 = pair<string, string>(to_string(stoi(resolution.first)*2), to_string(stoi(resolution.second)*2));
    vector<char> resolutionItem2 = convertWidthHeight2CharArrayInPlist(resolution2);
    resolutionArray.push_back(resolutionItem2);

    //P.S. 这里遇到一个坑：
    //vector<unsigned char> 不能序列化， vector<char> 才可以
    //这是因为plistcpp 认定 vector<char>才是data类型

    dict["scale-resolutions"] = resolutionArray;

    Plist::writePlistXML(buildConfigFilePath(vendorId, productId), dict);
}

//删除现有的分辨率配置项
void ConfigFileDao::removeResolutionItem(int vendorId, int productId, pair<string, string> resolution)
{
    char *configFilePath = buildConfigFilePath(vendorId, productId);

    //解析现有的配置文件
    map<string, boost::any> dict;
    Plist::readPlist(configFilePath, dict);

    //解析出resoutionLists
    boost::any temp = dict["scale-resolutions"];
    vector<boost::any> resolutionArray = boost::any_cast<std::vector<boost::any>>(temp);

    //处理奇数行的数据 （因为偶数行的数据都是奇数行的两倍）
    vector<boost::any>::iterator it;
//    for (int i = 0; i < resolutionArray.size(); i+=2)
    for (it = resolutionArray.begin(); it != resolutionArray.end(); it++)
    {
        vector<char> crResolution = boost::any_cast<vector<char>>(*it);

//        //如果数据的列数不是16列，说明数据错误
//        if (crResolution.size() != 16)
//        {
//            return NULL;
//        }

        //处理前8组数据，因为后8组数据都是固定的数值
        //只需要第3、4组数据和7、8组数据
        //每两组数据合并成一组数据
        char buffer[50];
        sprintf(buffer, "%d", Utils::chars2Short(crResolution[2], crResolution[3]));
        string width = string(buffer);
        sprintf(buffer, "%d", Utils::chars2Short(crResolution[6], crResolution[7]));
        string height = string(buffer);

        if (width == resolution.first && height == resolution.second)
        {
            it = resolutionArray.erase(it);
            resolutionArray.erase(it);
            break;
        }
    }

    //P.S. 这里遇到一个坑：
    //vector<unsigned char> 不能序列化， vector<char> 才可以
    //这是因为plistcpp 认定 vector<char>才是data类型

    dict["scale-resolutions"] = resolutionArray;

    Plist::writePlistXML(buildConfigFilePath(vendorId, productId), dict);
}

