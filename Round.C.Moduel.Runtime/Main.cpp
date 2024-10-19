#include "include.h"

using namespace std;

int main(int argc, char* argv[]) {
	try {
		if (argc != 1) {
			vector<string> fileline = ReadAllLines(argv[1]);
			for (int line = 0; line <= fileline.size() - 1; line++) {
				executeCommand(fileline[line], line);
			}
		}
		else {
			return 1;
		}
	}
	catch (runtime_error e) {
		MessageBoxA(NULL, e.what(), "RCS Runtime Error", 16);
	}
}