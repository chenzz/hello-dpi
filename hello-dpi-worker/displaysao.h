#ifndef DISPLAYSAO_H
#define DISPLAYSAO_H

#include <iostream>
#include <vector>

using namespace std;

//Dispaly System Access Object
class DisplaySao
{
public:
    DisplaySao();

    vector<pair<string, string>>* getVendorIdProductIdPairList();
};

#endif // DISPLAYSAO_H
