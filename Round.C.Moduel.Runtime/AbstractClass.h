#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <Windows.h>	
#include <locale>
#include <map>
#include <codecvt>
#include <vector>
#include <sstream>
#include <cstdio>

using namespace std;
void Error(string Message);
string ReadAllText(string path);
vector<string> ReadAllLines(string path);
vector<string> splitString(string str, char strchar);
string replacString(string str, string oldstr, string newstr);
string removeCharacter(const string& input, char character);
string extractTextBetweenParentheses(const string& input);
wstring StringToString(const string& str);

void Variable(string str, int line);
void AddStringer(string str, int line);
void AddInter(string str, int line);
void AddDoubler(string str, int line);
bool FindTwiceGL(string newname);
string GetVariable(string newname);
string GetExpression(string exp);
string GetVariableType(string name);

void RunMessageBox(string command, int line);
void ShowMessageBox(string Text, string Title,int ButtonIcon);
void CreateAndShowWindow(HINSTANCE hInstance,string title,int wid,int hei);