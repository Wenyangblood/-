#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <iostream>
#include <windows.h> // for SetConsoleOutputCP on Windows

int main()
{
	//-----------------------1. Initial variable-----------------------//
	char  input_img[] = "lena256.raw";                 // Input  raw image name
	char output_img[] = "lena256out.raw";              // Output raw image name
	FILE* input_file;
	FILE* output_file;
	int width = 256;
	int height = 256;
	int size = width * height;
	unsigned char* img_lena = new unsigned char[size]; // array for image data

	//-----------------------2. Read File-----------------------//
	// using fopen as example, fstream works too
	input_file = fopen(input_img, "rb");

	if (input_file == NULL) {
		puts("Loading File Error!");
		system("PAUSE");
		exit(0);
	}

	fread(img_lena, 1, size, input_file);

	//-----------------------3. Save Image as raw format-----------------------//
	output_file = fopen(output_img, "wb");
	fwrite(img_lena, 1, size, output_file);

	//-----------------------4. Release memory-----------------------//
	delete[] img_lena;
	fclose(input_file);
	fclose(output_file);
}