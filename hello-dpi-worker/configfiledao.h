#ifndef HIDPIREADER_H
#define HIDPIREADER_H

#include <list>
#include <vector>

using namespace std;

class ConfigFileDao
{
public:
    ConfigFileDao();
    vector<pair<string, string> *>* getResolutionList(int vendorId, int productId);
    void addResolutionItem(int vendorId, int productId, pair<string, string> resolution);
    void removeResolutionItem(int vendorId, int productId, pair<string, string> resolution);
};

#endif // HIDPIREADER_H
