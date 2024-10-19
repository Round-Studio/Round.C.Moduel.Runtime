#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif
#include "AbstractClass.h"
#include "Variable.h"
#include "Running.h"
#include "Win32.h"

using namespace std;
wstring StringToString(const string& str) {
    if (str.empty()) return wstring();
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
    wstring wstr(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstr[0], size_needed);
    return wstr;
}

string removeCharacter(const string& input, char character) {
    string result;
    for (char ch : input) {
        if (ch != character) {
            result += ch;
        }
    }
    return result;
}

string extractTextBetweenParentheses(const string& input) {
    size_t startPos = input.find("(");
    size_t endPos = input.find(")", startPos);

    if (startPos != string::npos && endPos != string::npos && startPos < endPos) {
        startPos = startPos + 1;
        return input.substr(startPos, endPos - startPos);
    }

    return "";
}

string ReadAllText(string path) {
    ifstream file(path);
    string str;

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            str += line + "\n";
        }
        file.close();
    }
    else {
        Error("Not Find File: \"" + path + "\" !");
    }

    return str;
}

vector<string> splitString(string str,char strchar) {
    vector<string> result;
    istringstream iss(str);
    string token;
    while (getline(iss, token, strchar)) {
        result.push_back(token);
    }
    return result;
}

string replacString(string str,string oldstr, string newstr) {
    while (str.find(oldstr)!=string::npos) {
        string::size_type pos = str.find(oldstr);
        if (pos != std::string::npos) {
            str.replace(pos, oldstr.length(), newstr);
        }
    }

    return str;
}

vector<string> ReadAllLines(string path) {
    vector<string> arr;
    ifstream file(path);

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            arr.push_back(line);
        }
        file.close();
    }
    else {
        Error("Not Find File: \"" + path + "\" !");
    }

    return arr;
}

void Error(string Message) {
    MessageBox(NULL, StringToString(Message).c_str(), L"Error", 0 + 16);
    throw runtime_error(Message);
}