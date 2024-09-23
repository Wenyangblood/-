#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <iostream>
#include <windows.h> // for SetConsoleOutputCP on Windows

const int WIDTH = 256;
const int HEIGHT = 256;

// 將整張影像進行上下顛倒
void flipVertical(unsigned char img[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT / 2; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            // 交換第 i 行和第 HEIGHT - 1 - i 行的像素
            unsigned char temp = img[i][j];
            img[i][j] = img[HEIGHT - 1 - i][j];
            img[HEIGHT - 1 - i][j] = temp;
        }
    }
}

// 將整張影像進行左右相反
void flipHorizontal(unsigned char img[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH / 2; ++j) {
            // 交換第 i 行中的第 j 列和第 WIDTH - 1 - j 列的像素
            unsigned char temp = img[i][j];
            img[i][j] = img[i][WIDTH - 1 - j];
            img[i][WIDTH - 1 - j] = temp;
        }
    }
}

// 主程式
int main()
{
    SetConsoleOutputCP(65001); // 設置控制台顯示中文

    //-----------------------1. 初始化變數-----------------------//   
    char input_img[] = "lena256.raw";                 // Input raw image name
    char output_img[] = "lena256_flipped.raw";        // Output raw image name
    FILE* input_file;
    FILE* output_file;

    unsigned char img_lena[HEIGHT][WIDTH]; // 使用 2D 陣列來保存影像數據

    // 打開輸入檔案
    input_file = fopen(input_img, "rb");

    if (input_file == NULL) {
        puts("載入檔案錯誤！");
        system("PAUSE");
        exit(0);
    }

    // 讀取影像檔案到 2D 陣列中
    fread(img_lena, 1, WIDTH * HEIGHT, input_file);
    fclose(input_file);

    // 進行上下顛倒
    flipVertical(img_lena);

    // 進行左右相反
    flipHorizontal(img_lena);

    // 保存處理後的影像數據到新檔案
    output_file = fopen(output_img, "wb");
    fwrite(img_lena, 1, WIDTH * HEIGHT, output_file);
    fclose(output_file);

    printf("影像處理完成並保存至 %s\n", output_img);

    return 0;
}
