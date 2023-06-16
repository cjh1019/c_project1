#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>

void P(char* c, int x, int y);
void SG(int [][19]);

int main() {
	int game[19][19] = { 0 };
	game[4][4] = 1;
	game[6][4] = 2;

	SG(game);
}

void P(char* c, int x, int y) {
	COORD p;
	p.X = x;
	p.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
	puts(c);
}

void SG(int num[][19]) {
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 19; j++) {
			switch(num[i][j]) {
			case 0:
				P("-", i * 2, j);
				P("+", i * 2 + 1, j);
				break;
			case 1:
				P("¡Ü", i * 2, j);
				break;
			case 2:
				P("¡Û", i * 2, j);
				break;
			}
		}
		printf("\n");
	}
}