
//--------------------------------------------------
// Include
//--------------------------------------------------
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include "clHCA.h"

//--------------------------------------------------
// Convert character strings to decimal numbers and convert them to numbers (simplified version)
//--------------------------------------------------
int atoi(const char *s) {
	int r = 0;
	bool sign = false; if (*s == '+') { s++; }
	else if (*s == '-') { sign = true; s++; }
	while (*s) {
		if (*s >= '0'&&*s <= '9')r = r * 10 + (*s - '0');
		else break;
		s++;
	}
	return sign ? -r : r;
}
float atof(const char *s) {
	int r1 = 0, r2 = 0, c = 1;
	bool sign = false; if (*s == '+') { s++; }
	else if (*s == '-') { sign = true; s++; }
	while (*s) {
		if (*s >= '0'&&*s <= '9')r1 = r1 * 10 + (*s - '0');
		else break;
		s++;
	}
	if (*s == '.') {
		s++;
		while (*s) {
			if (*s >= '0'&&*s <= '9') { r2 = r2 * 10 + (*s - '0'); c *= 10; }
			else break;
			s++;
		}
	}
	float r = r1 + ((c>0) ? r2 / (float)c : 0);
	return sign ? -r : r;
}

//--------------------------------------------------
// Convert character strings to numbers by considering character strings as hexadecimal numbers
//--------------------------------------------------
int atoi16(const char *s) {
	int r = 0;
	bool sign = false; if (*s == '+') { s++; }
	else if (*s == '-') { sign = true; s++; }
	while (*s) {
		if (*s >= '0'&&*s <= '9')r = (r << 4) | (*s - '0');
		else if (*s >= 'A'&&*s <= 'F')r = (r << 4) | (*s - 'A' + 10);
		else if (*s >= 'a'&&*s <= 'f')r = (r << 4) | (*s - 'a' + 10);
		else break;
		s++;
	}
	return sign ? -r : r;
}

//--------------------------------------------------
// Main
//--------------------------------------------------
int main(int argc, char *argv[]) {

	// Command line analysis
	unsigned int count = 0;
	char *filenameOut = NULL;
	//bool decodeFlg=false;
	float volume = 1;
	unsigned int ciphKey1 = 0xE0748978;
	unsigned int ciphKey2 = 0xCF222F1F;
	int mode = 16;
	int loop = 0;
	bool info = false;
	bool decrypt = false;
	for (int i = 1; i<argc; i++) {
		if (argv[i][0] == '-' || argv[i][0] == '/') {
			switch (argv[i][1]) {
			case 'o':if (i + 1<argc) { filenameOut = argv[++i]; }break;
				//case 'd':decodeFlg=true;break;
			case 'v':volume = (float)atof(argv[++i]); break;
			case 'a':if (i + 1<argc) { ciphKey1 = atoi16(argv[++i]); }break;
			case 'b':if (i + 1<argc) { ciphKey2 = atoi16(argv[++i]); }break;
			case 'm':if (i + 1<argc) { mode = atoi(argv[++i]); }break;
			case 'l':if (i + 1<argc) { loop = atoi(argv[++i]); }break;
			case 'i':info = true; break;
			case 'c':decrypt = true; break;
			}
		}
		else if (*argv[i]) {
			argv[count++] = argv[i];
		}
	}

	//if(decodeFlg){

	// Check the input
	if (!count) {
		printf("Error: Please specify input file.\n");
		return -1;
	}

	// Decode
	for (unsigned int i = 0; i<count; i++) {

		// For the second and subsequent files, the output file name option is invalid
		if (i)filenameOut = NULL;

		// Default output file name
		char path[MAX_PATH];
		if (!(filenameOut&&filenameOut[0])) {
			strcpy_s(path, sizeof(path), argv[i]);
			char *d1 = strrchr(path, '\\');
			char *d2 = strrchr(path, '/');
			char *e = strrchr(path, '.');
			if (e&&d1<e&&d2<e)*e = '\0';
			strcat_s(path, sizeof(path), ".wav");
			filenameOut = path;
		}

		// Display header information only
		if (info) {
			printf("%s Header information\n", argv[i]);
			clHCA hca(0, 0);
			hca.PrintInfo(argv[i]);
			printf("\n");
		}

		// Decryption
		else if (decrypt) {
			printf("%s Decrypting ...\n", argv[i]);
			clHCA hca(ciphKey1, ciphKey2);
			if (!hca.Decrypt(argv[i])) {
				printf("Error: Decryption failed.\n");
			}
		}

		// Decode
		else {
			printf("%s Decoding ...\n", argv[i]);
			clHCA hca(ciphKey1, ciphKey2);
			if (!hca.DecodeToWavefile(argv[i], filenameOut, volume, mode, loop)) {
				printf("Error: Decoding failed.\n");
			}
		}

	}

	//}

	return 0;
}
