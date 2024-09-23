#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <iostream>
#include <windows.h> // for SetConsoleOutputCP on Windows

int main()
{
   SetConsoleOutputCP(65001);
   //設定中文
//-----------------------1. Initial variable-----------------------//   
    char input_img[] = "lena256.raw";                 // Input  raw image name
    FILE* input_file;
    int width = 256;
    int height = 256;    
    // give space
    unsigned char img_lena[width][height];

    input_file = fopen(input_img, "rb");

    if (input_file == NULL) {
        puts("載入檔案錯誤！");
        system("PAUSE");
        exit(0);
    }
    fread(img_lena, 1, width * height, input_file);

    // input file
    fclose(input_file); // close

    // positioon
    printf("像素值是 %d\n",  img_lena[78][199]);

  //-----------------------4. Release memory-----------------------//
    for (int i = 0; i < height; ++i) {
        delete[] img_lena[i];
    }
    delete[] img_lena;

    return 0;
}
