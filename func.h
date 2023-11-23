#pragma once
#include<../../includes.h>

void typeString(const char* str, int spamSpeed);
char* readStringFromFile(const char* filename);
void writeStringToFile(const char* filename, const char* data);
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);
