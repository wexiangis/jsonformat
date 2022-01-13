#include <stdio.h>
#include <stdlib.h>
#include "jsonformat.h"

int readFile(const char* file, char* buff, int buffSize)
{
    size_t ret;
    FILE* fp = fopen(file, "r");
    if (!fp)
        return -1;
    ret = fread(buff, 1, buffSize, fp);
    fclose(fp);
    return ret;
}

int writeFile(const char* file, char* buff, int buffSize)
{
    size_t ret;
    FILE* fp = fopen(file, "w+");
    if (!fp)
        return -1;
    ret = fwrite(buff, 1, buffSize, fp);
    fclose(fp);
    return ret;
}

int main(int argc, char** argv)
{
    int inBuffSize;
    int outBuffSize;
    char inBuff[4096] = {0};
    char outBuff[4096] = {0};

    if (argc < 3)
    {
        printf("Usage: %s in.json out.json space(default 4)\r\n", argv[0]);
        return -1;
    }

    inBuffSize = readFile(argv[1], inBuff, sizeof(inBuff));
    if (inBuffSize < 1)
    {
        printf("readFile %s failed", argv[1]);
        return -1;
    }

    printf("%s:\r\n%s\r\n\r\n", argv[1], inBuff);

    outBuffSize = JsonFormat(inBuff, outBuff, sizeof(outBuff), argc > 3 ? atoi(argv[3]) : 4);
    if (outBuffSize < 1)
    {
        printf("JsonFormat failed");
        return -1;
    }

    if (writeFile(argv[2], outBuff, outBuffSize) < 1)
    {
        printf("writeFile %s failed", argv[2]);
        return -1;
    }

    printf("%s:\r\n%s\r\n\r\n", argv[2], outBuff);

    return 0;
}
