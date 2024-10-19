#include <Windows.h>

using namespace std;
void RunMessageBox(string command, int line) {
	vector<string> tempcommand = splitString(extractTextBetweenParentheses(command), ',');
	ShowMessageBox(GetExpression(tempcommand[0]), removeCharacter(GetExpression(tempcommand[1]),'\"'), stoi(tempcommand[2]));
}

void ShowMessageBox(string Text, string Title,int ButtonIcon) {
	MessageBox(NULL, StringToString(removeCharacter(replacString(Text,"\\n","\n"), '\"')).c_str(), StringToString(Title).c_str(), ButtonIcon);
}

// ���ڹ��̺���
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

// ��������ʾ���ڵĺ���
void CreateAndShowWindow(HINSTANCE hInstance,string title,int wid,int hei) {
    WNDCLASSEX wc;

    // ���崰����
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDC_ICON);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = L"RCSWindow";
    wc.hIconSm = LoadIcon(NULL, IDC_ICON);

    // ע�ᴰ����
    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, L"Window Registration Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
        return;
    }

    // ��������
    HWND hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        L"RCSWindow",
        StringToString(title).c_str(),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, wid, hei,
        NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) {
        MessageBox(NULL, L"Window Creation Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
        return;
    }

    // ��ʾ����
    ShowWindow(hwnd, SW_SHOWDEFAULT);
    UpdateWindow(hwnd);

    // ��Ϣѭ��
    MSG Msg;
    while (GetMessage(&Msg, NULL, 0, 0) > 0) {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
}