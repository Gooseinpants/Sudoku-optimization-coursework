#pragma once
#include <string>
#include <cstring>

std::string ExtractFilePath(char FileName[])
{
    int i, len = strlen(FileName);
    char * buf = (char *)malloc(len);
    for (i = len - 1; i >= 0; i--)
    {
        if (FileName[i] == ('\\'))
            break;
    }
    strncpy(buf, FileName, i + 1);
    buf[i + 1] = '\0';
    std::string res(buf);
    free(buf);
    buf = NULL;
    return res;
}