using namespace std;

bool run = true;
void executeCommand(const string& command, int line) {
	if (!command.find("@set")) {
		try {
			vector<string> setcommand = splitString(command, ' ');
			if (setcommand[1] == "console") {
				HWND hwnd = GetConsoleWindow();
				if (setcommand[2] == "false") {
					ShowWindow(hwnd, SW_HIDE);
				}
				else {
					ShowWindow(hwnd, SW_SHOW);
				}
			}
		}
		catch (...) {
			Error("There was a crash!");
		}
	}else if (command.find(';') == string::npos) {
		string wskg = "";
		for (int i = 0; i <= command.size() - 1; i++)
		{
			wskg += " ";
		}
		cout << "Not Find the \";\" in line " << line << endl << command << endl << wskg << "^" << endl;
		run = false;
	}
	else {
		if (run) {
			string vars = splitString(command, '=')[0];
			vars = removeCharacter(vars, ' ');
			if (!command.find("print")) {
				cout << removeCharacter(GetExpression(extractTextBetweenParentheses(command)), '\"') << endl;
			}else if (!command.find("input")) {
				string temp;
				cout << removeCharacter(GetExpression(extractTextBetweenParentheses(command)), '\"');
				getline(cin, temp);
			}
			else if (!command.find("window")) {
				CreateAndShowWindow(GetModuleHandle(NULL), removeCharacter(splitString(extractTextBetweenParentheses(command), ',')[0],'\"'), stoi(splitString(extractTextBetweenParentheses(command), ',')[1]), stoi(splitString(extractTextBetweenParentheses(command), ',')[2]));
			}
			else if (!command.find("messagebox")) {
				RunMessageBox(command, line);
			}
			else if (command.find("int") || command.find("string") || command.find("double")) {
				Variable(command, line);
			}
		}
	}
}