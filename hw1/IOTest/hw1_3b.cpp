#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <iostream>
#include <windows.h> // for SetConsoleOutputCP on Windows
#include <algorithm>
#include <typeinfo>
int main()
{
    SetConsoleOutputCP(65001);
    //-----------------------1. 初始化變數-----------------------//
    char  input_img[] = "lena256.raw";                 // Input  raw image name
    char output_img[] = "lena256bright1.raw";              // Output raw image name
    FILE* input_file;
    FILE* output_file;
    int width = 256;
    int height = 256;
    int size = width * height;
    unsigned char* img_lena = new unsigned char[size]; // 陣列來儲存影像數據

    //-----------------------2. 讀取檔案-----------------------//
    input_file = fopen(input_img, "rb");

    if (input_file == NULL) {
        puts("載入檔案錯誤！");
        system("PAUSE");
        exit(0);
    }
    fread(img_lena, 1, size, input_file);
    //-----------------------變更亮度-----------------------//
    for(int i = 0;i<size;i++)
    {
       img_lena[i]= std::min({img_lena[i]+76,255});//這邊是std min就是預防溢位
    }
    output_file = fopen(output_img, "wb");
	fwrite(img_lena, 1, size, output_file);

 
    //-----------------------4. 釋放記憶體-----------------------//
    delete[] img_lena;
    fclose(input_file);
	fclose(output_file);
    return 0;
}
