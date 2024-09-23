#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <iostream>
#include <windows.h> // for SetConsoleOutputCP on Windows
#include <algorithm>
#include <typeinfo>
#include <stdlib.h>
#include <time.h> 
int main()
{
    SetConsoleOutputCP(65001);
    //-----------------------1. 初始化變數-----------------------//
    char  input_img[] = "lena256.raw";                 // Input  raw image name
    char output_img[] = "lena256bright2.raw";              // Output raw image name
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
    srand(time(NULL)); //亂數時間
    fread(img_lena, 1, size, input_file);
    for(int i = 0;i<size;i++)
    {
        
        char b =rand()%161 -80;
        unsigned char a= 0;
       img_lena[i]= std::min(img_lena[i]-100,255);

    //    img_lena[i] = std::max(img_lena[i], a);
    }
    output_file = fopen(output_img, "wb");
	fwrite(img_lena, 1, size, output_file);



    //-----------------------4. 釋放記憶體-----------------------//
    delete[] img_lena;
    fclose(input_file);
	fclose(output_file);
    return 0;
}
