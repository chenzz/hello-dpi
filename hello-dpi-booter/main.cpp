#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    //构造script路径
    string currentRunningAppPath = argv[0];
    string scriptPath = currentRunningAppPath.substr(0, currentRunningAppPath.find_last_of("/"));
    scriptPath = scriptPath.substr(0, scriptPath.find_last_of("/"));
    scriptPath += "/Resources/HelloDpiBooter.scpt";

    //构造cmd
    char cmd[300];
    sprintf(cmd, "nohup osascript %s > /tmp/temp 2>&1 &", scriptPath.c_str());
    system(cmd);
    return 0;
}
