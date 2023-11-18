#include<../../includes.h>
#include<../../func.h>

HWND targetWindow = NULL;

const char* textToType;


BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    wchar_t className[256];
    wchar_t windowText[256];

    GetClassNameW(hwnd, className, sizeof(className) / sizeof(className[0]));
    GetWindowTextW(hwnd, windowText, sizeof(windowText) / sizeof(windowText[0]));

    wprintf(L"Window Class: %s, Title: %s\n", className, windowText);

    // Check if the window title contains the target application name
    wchar_t* targetAppName = (wchar_t*)lParam;

    if (wcsstr(windowText, targetAppName) != NULL) {
        // Save the target window handle
        targetWindow = hwnd;
    }

    return TRUE;
}
int wmain() {

    printf("[Whatspammer] Welcome to Whatspammer. \n[Whatspammer] Made by Ayush Jain.\n");

    const char* filename = "spam.txt";

    const char* defaultData = "Hello, World!";

    FILE* fileCheck = fopen(filename, "r");

    if (fileCheck == NULL) {

        writeStringToFile(filename, defaultData);

        printf("[Whatspammer] File created with default data.\n");
        
        printf("[Whatspammer] Edit the spam.txt and add what you desire.\n");

        printf("[Whatspammer] Press any key to continue...");

        getchar();

    }
    else {

        fclose(fileCheck);

        printf("[Whatspammer] Checking File, Please wait!\n");

        Sleep(3000);

        printf("[Whatspammer] File already exists.\n");

    }

    int spamtime = 0;

    printf("[Whatspammer] Data is being read from spam.txt.\n");

    printf("[Whatspammer] Enter Number of Spams: ");

    scanf_s("%d", &spamtime);

    int speed, usersped;

    printf("[Whatspammer] Enter Spam Speed: ");
    scanf_s("%d", &usersped);

    if (usersped == NULL) {
        speed = 100;
    }
    else {
        speed = usersped;
    }

    char* readString = readStringFromFile(filename);

    if (readString != NULL) {

        printf("[Whatspammer] String read from file: %s\n", readString);

    }

    wprintf(L"[Whatspammer] Enter the application: ");

    wchar_t input[256];
    wscanf_s(L"%s", input);

    // Enumerate all windows
    EnumWindows(EnumWindowsProc, (LPARAM)input);

    if (targetWindow != NULL) {
        // Bring the target window to the foreground
        ShowWindow(targetWindow, SW_RESTORE);
        SetForegroundWindow(targetWindow);
        wprintf(L"[Whatspammer] %s window found and brought to the foreground.\n", input);
    }
    else {
        wprintf(L"[Whatspammer] %s window not found.\n", input);
    }

    Sleep(1000);

    //bringApplicationToFront();
    //SetForegroundWindow(targetWindow);

    //bringApplicationToFront();
    SetForegroundWindow(targetWindow);

    Sleep(1000);

    printf("[Whatspammer] Starting counter...");

    for (int a = 1; a <= spamtime; a++) {
        printf("[Whatspammer] Spammed %d times...\n", a);
        //bringApplicationToFront();
        SetForegroundWindow(targetWindow);
        typeString(readString, speed);
        
    }

    free(readString);
}
