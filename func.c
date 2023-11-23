#include<../../includes.h>
#include <ctype.h>



void typeString(const char* str, int spamSpeed) {
    for (int i = 0; str[i] != '\0'; i++) {
        SHORT vkCode = VkKeyScan(str[i]);
        BYTE virtualKey = LOBYTE(vkCode);
        BYTE shiftState = HIBYTE(vkCode);

        if (shiftState & 1) {

            keybd_event(VK_SHIFT, 0, KEYEVENTF_UNICODE, 0);
        }

        keybd_event(virtualKey, 0, KEYEVENTF_UNICODE, 0);
        keybd_event(virtualKey, 0, KEYEVENTF_KEYUP, 0);

        if (shiftState & 1) {

            keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
        }

 
    }


    keybd_event(VK_RETURN, 0, KEYEVENTF_UNICODE, 0);
    keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
    Sleep(spamSpeed);
}


char* readStringFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("[Whatspammer] Error opening file for reading");
        return NULL;
    }

    // Find the size of the file
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    // Allocate memory to store the string
    char* buffer = (char*)malloc(file_size + 1); // +1 for null terminator
    if (buffer == NULL) {
        perror("[Whatspammer] Error allocating memory");
        fclose(file);
        return NULL;
    }

    // Read the string from the file
    if (fread(buffer, 1, file_size, file) != file_size) {
        perror("[Whatspammer] Error reading from file");
        free(buffer);
        fclose(file);
        return NULL;
    }

    // Null-terminate the string
    buffer[file_size] = '\0';

    // Close the file
    fclose(file);

    return buffer;
}

void writeStringToFile(const char* filename, const char* data) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("[Whatspammer] Error opening file for writing");
        return;
    }

    // Write the string to the file
    if (fputs(data, file) == EOF) {
        perror("[Whatspammer] Error writing to file");
    }

    // Close the file
    fclose(file);
}




