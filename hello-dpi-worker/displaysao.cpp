#include "displaysao.h"
#include <iostream>
#include "utils.cpp"

using namespace std;


//Display System Access Object
DisplaySao::DisplaySao()
{
}


//获取vendorId和productId的组合列表
vector<pair<string, string>>* DisplaySao::getVendorIdProductIdPairList()
{
    string vendorIdQueryResult = Utils::execShellCmd("ioreg -l | grep \"DisplayVendorID\"");
    string productIdQueryResult = Utils::execShellCmd("ioreg -l | grep \"DisplayProductID\"");
    vector<pair<string, string>>* vendorIdProductIdPairList = new vector<pair<string, string>>();

    vector<string> vendorIdLineVector = Utils::split(vendorIdQueryResult, '\n');
    vector<string> productIdLineVector = Utils::split(productIdQueryResult, '\n');

    for (int i = 0; (i < vendorIdLineVector.size()) && (i < productIdLineVector.size()); i++)
    {
        vector<string> vendorIdVector = Utils::split(vendorIdLineVector[i], ' ');
        vector<string> productIdVector = Utils::split(productIdLineVector[i], ' ');

        string vendorId = vendorIdVector[vendorIdVector.size()-1];
        string productId = productIdVector[productIdVector.size()-1];

        vendorIdProductIdPairList->push_back(pair<string, string>(vendorId, productId));
    }

    return vendorIdProductIdPairList;
}
