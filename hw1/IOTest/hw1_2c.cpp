#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <iostream>
#include <windows.h> // for SetConsoleOutputCP on Windows

const int WIDTH = 256;
const int HEIGHT = 256;
const int BLOCK_SIZE = 64; // 每個方塊的邊長是 64

// 旋轉區塊 90 度
void rotateBlock(unsigned char block[BLOCK_SIZE][BLOCK_SIZE]) {
    unsigned char temp[BLOCK_SIZE][BLOCK_SIZE];
    
    // 90 度旋轉
    for (int i = 0; i < BLOCK_SIZE; ++i) {
        for (int j = 0; j < BLOCK_SIZE; ++j) {
            temp[BLOCK_SIZE - 1 - j][i] = block[i][j];
        }
    }

    // 將旋轉後的結果複製回原陣列
    for (int i = 0; i < BLOCK_SIZE; ++i) {
        for (int j = 0; j < BLOCK_SIZE; ++j) {
            block[i][j] = temp[i][j];
        }
    }
}

// 將影像分割成 16 個區塊，對每個區塊旋轉後重新保存
int main()
{
    SetConsoleOutputCP(65001); // 設置控制台顯示中文

    //-----------------------1. 初始化變數-----------------------//   
    char input_img[] = "lena256_flipped.raw";                 // Input raw image name
    char output_img[] = "lena256rotate.raw";             // Output raw image name
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

    // 分割並旋轉每個區塊
    for (int block_row = 0; block_row < 4; ++block_row) {
        for (int block_col = 0; block_col < 4; ++block_col) {
            unsigned char block[BLOCK_SIZE][BLOCK_SIZE];
            
            // 提取出 64x64 的區塊
            for (int i = 0; i < BLOCK_SIZE; ++i) {
                for (int j = 0; j < BLOCK_SIZE; ++j) {
                    block[i][j] = img_lena[block_row * BLOCK_SIZE + i][block_col * BLOCK_SIZE + j];
                }
            }
            if ((block_row==0 && block_col==0)||(block_row==1 && block_col==0)||(block_row==2 && block_col==1)||(block_row==0 && block_col==3)){
            // 旋轉這個區塊
                rotateBlock(block);
            }
            
            else if((block_row==3 && block_col==0)||(block_row==3 && block_col==2)||(block_row==0 && block_col==2)||(block_row==1 && block_col==2)||(block_row==3 && block_col==3)||(block_row==2 && block_col==2)){
                rotateBlock(block);
                rotateBlock(block);
             
             }
             else{
                rotateBlock(block);
                rotateBlock(block); 
                rotateBlock(block);
             }
            
            // 將旋轉後的區塊存回影像陣列
            for (int i = 0; i < BLOCK_SIZE; ++i) {
                for (int j = 0; j < BLOCK_SIZE; ++j) {
                    img_lena[block_row * BLOCK_SIZE + i][block_col * BLOCK_SIZE + j] = block[i][j];
                }
            }
        }
    }

    // 保存處理後的影像數據到新檔案
    output_file = fopen(output_img, "wb");
    fwrite(img_lena, 1, WIDTH * HEIGHT, output_file);
    fclose(output_file);

    printf("影像處理完成並保存至 %s\n", output_img);

    return 0;
}
