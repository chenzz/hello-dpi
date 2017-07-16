#include <QCoreApplication>
#include <array>
#include <sstream>
#include <QLayout>
#include <unistd.h>

using namespace std;

class Utils
{
public:
//    static QString base64_encode(QString string)
//    {
//        QByteArray ba;
//        ba.append(string);
//        return ba.toBase64();
//    }

//    static QByteArray base64_decode(QString string)
//    {
//        QByteArray ba;
//        ba.append(string);
//        return ba.fromBase64(ba);
//    }

    //2个char变量转换成1个short
    static unsigned short chars2Short(unsigned char a, unsigned char b)
    {
        short c = (((short)a) << 8) | b;
        return c;
    }

    //1个short变量转换成2个char
    static pair<unsigned char, unsigned char> short2Chars(unsigned short input)
    {
        unsigned char a = (input >> 8) & 0xff;
        unsigned char b = input & 0xff;

        return pair<unsigned char, unsigned char>(a, b);
    }

    //执行shell命令
    static std::string execShellCmd(const char* cmd) {
        std::array<char, 128> buffer;
        std::string result;
        std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
        if (!pipe) throw std::runtime_error("popen() failed!");
        while (!feof(pipe.get())) {
            if (fgets(buffer.data(), 128, pipe.get()) != NULL)
                result += buffer.data();
        }
        return result;
    }

    //执行shell命令
    static std::string execShellCmd(string cmdStr) {

        const char *cmd = cmdStr.c_str();

        execShellCmd(cmd);
    }

    template<typename Out> static void split(const std::string &s, char delim, Out result) {
        std::stringstream ss;
        ss.str(s);
        std::string item;
        while (std::getline(ss, item, delim)) {
            *(result++) = item;
        }
    }

    //切分字符串
    static std::vector<std::string> split(const std::string &s, char delim) {
        std::vector<std::string> elems;
        split(s, delim, std::back_inserter(elems));
        return elems;
    }

    //判断某个字符串是否以某个字符串结尾
    static bool endsWith(string const &fullString, string const &ending) {
        if (fullString.length() >= ending.length()) {
            return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
        } else {
            return false;
        }
    }

    //清空layout
    static void clearLayout(QLayout *layout)
    {
        QLayoutItem *item;
        while((item = layout->takeAt(0)) != NULL)
        {
            if (item->widget()) {
                delete item;
            }
            else if (item->layout()) {
                clearLayout(item->layout());
                delete item;
            }
        }
    }

    static string getCurrentPath()
    {
        char buffer[100];
        char *answer = getcwd(buffer, sizeof(buffer));
        string s_cwd;
        if (answer)
        {
            s_cwd = answer;
        }

        return s_cwd;
    }
};
