using namespace std;

vector<string> GLname;
vector<pair<string, string>> strGL;
vector<pair<string, int>> intGL;
vector<pair<string, double>> doubleGL;
void Variable(string command, int line) {
	if (!command.find("int")) {
		string tempname = command.substr(3);
		AddInter(tempname,line);
	}
	else if (!command.find("double")) {
		string tempname = command.substr(6);
		AddDoubler(tempname, line);
	}
	else if (!command.find("string")) {
		string tempname = command.substr(6);
		AddStringer(tempname, line);
	}
}
void AddInter(string str, int line) {
	for (const auto& tempGLname : splitString(str, ',')) {
		string temp = removeCharacter(tempGLname, ';');
		temp = removeCharacter(temp, ' ');
		if (FindTwiceGL(splitString(temp, '=')[0])) {
			if (temp.find('=') != string::npos) {
				intGL.push_back(make_pair(splitString(temp, '=')[0], stoi(GetExpression(splitString(temp, '=')[1]))));
				GLname.push_back(splitString(temp, '=')[0]);
			}
			else {
				intGL.push_back(make_pair(temp, 0));
				GLname.push_back(temp);
			}
		}
	}
}
void AddStringer(string str, int line) {
	for (const auto& tempGLname : splitString(str, ',')) {
		string temp = removeCharacter(tempGLname, ';');
		temp = removeCharacter(temp, ' ');
		if (FindTwiceGL(splitString(temp, '=')[0])) {
			if (temp.find('=')!=string::npos) {
				strGL.push_back(make_pair(splitString(temp, '=')[0], replacString(GetExpression(splitString(temp, '=')[1]), "\"", "")));
				GLname.push_back(splitString(temp, '=')[0]);
			}
			else {
				strGL.push_back(make_pair(temp, ""));
				GLname.push_back(temp);
			}
		}
	}
}
void AddDoubler(string str, int line) {
	for (const auto& tempGLname : splitString(str, ',')) {
		string temp = removeCharacter(tempGLname, ';');
		temp = removeCharacter(temp, ' ');
		if (FindTwiceGL(splitString(temp, '=')[0])) {
			if (temp.find('=') != string::npos) {
				doubleGL.push_back(make_pair(splitString(temp, '=')[0], stod(GetExpression(splitString(temp, '=')[1]))));
				GLname.push_back(splitString(temp, '=')[0]);
			}
			else {
				doubleGL.push_back(make_pair(temp, 0));
				GLname.push_back(temp);
			}
		}
	}
}

bool FindTwiceGL(string newname) {
	for (const auto& temp : GLname) {
		if (temp == newname) {
			Error("Have the same variable name!\nName: " + newname);
			return false;
		}
	}
	return true;
}

bool FindGL(string newname) {
	for (const auto& temp : GLname) {
		if (temp == newname) {
			return true;
		}
	}
	Error("Not Find The Variable!\nName: " + newname);
	return false;
}

string GetVariable(string name) {
	if (FindGL(name)) {
		for (const auto& temp : strGL) {
			if (temp.first == name) {
				return temp.second;
			}
		}
		for (const auto& temp : intGL) {
			if (temp.first == name) {
				return to_string(temp.second);
			}
		}
		for (const auto& temp : doubleGL) {
			if (temp.first == name) {
				return to_string(temp.second);
			}
		}
	}
	Error("Variable not found: " + name);
}

string GetVariableType(string name) {
	if (FindGL(name)) {
		for (const auto& temp : strGL) {
			if (temp.first == name) {
				return "str";
			}
		}
		for (const auto& temp : intGL) {
			if (temp.first == name) {
				return "int";
			}
		}
		for (const auto& temp : doubleGL) {
			if (temp.first == name) {
				return "dou";
			}
		}
	}
	Error("Variable not found: " + name);
}

bool IfNum(string numstr) {
	try {
		stoi(numstr);
		return true;
	}
	catch (...) {
		return false;
	}
}

string GetExpression(string exp) {
	vector<string> expitem = splitString(exp, '+');
	string res = "";
	for (const auto& temp : expitem) {
		if (temp.find("\"") != string::npos || IfNum(temp)) {
			res += temp;
		}
		else {
			res += GetVariable(temp);
		}
	}
	return res;
}

void SetVariableValue(string name,string Value) {
	if (FindGL(name)) {
		string type = GetVariableType(name);
		if (type == "int") {
			int i = 0;
			for (const auto& temp : intGL) {
				if (temp.first == name) {
					intGL[i].second = stoi(Value);
				}
				i++;
			}
		}
		if (type == "str") {
			int i = 0;
			for (const auto& temp : strGL) {
				if (temp.first == name) {
					strGL[i].second = Value;
				}
				i++;
			}
		}
		if (type == "dou") {
			int i = 0;
			for (const auto& temp : doubleGL) {
				if (temp.first == name) {
					doubleGL[i].second = stod(Value);
				}
				i++;
			}
		}
	}
}