#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <iostream>
#include <windows.h> // for SetConsoleOutputCP on Windows

int main()
{
    SetConsoleOutputCP(65001);
    char  input_img[] = "lena256.raw";                 // Input  raw image name     
    FILE* input_file;
    int width = 256;
    int height = 256;
    int size = width * height;
    unsigned char* img_lena = new unsigned char[size]; // 陣列來儲存影像數據

    input_file = fopen(input_img, "rb");

    if (input_file == NULL) {
        puts("載入檔案錯誤！");
        system("PAUSE");
        exit(0);
    }

    fread(img_lena, 1, size, input_file);
    fclose(input_file); // 關閉檔案
    
    // 計算一維陣列中對應的位置

    // 顯示該位置的像素值
    printf("像素值 %d\n",img_lena[16888]);

    delete[] img_lena;

    return 0;
}
