#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdbool.h>

void setCursor(int x, int y);
void SG(int[][19]);
int getDirection(int ix, int iy);
int startY = 1;

int main() {
	int game[19][19] = { 0 };
	int order = 1;		//1 = 흑, 0 = 백
	int x = 0;
	int y = 0;

	printf("---------------- 오목 ----------------");
	setCursor(44, 5);
	printf("위치변경 : 방향키");
	setCursor(44, 6);
	printf("위치변경 완료 : 스페이스 바");

	while (true) {
		SG(game);

		setCursor(46, 0);
		printf("흑돌");
		setCursor(46, 3);
		printf("백돌");

		if (order) {
			setCursor(44, 3);
			puts(" ");
			setCursor(44, 0);
			puts(">");
		}
		else {
			setCursor(44, 0);
			puts(" ");
			setCursor(44, 3);
			puts(">");
		}
		int xy = getDirection(x, y);
		x = xy / 100;
		y = xy % 100;
		game[x][y] = order + 1;
		order = !order;		//순서 변경
	}
}

//커서위치 변경
void setCursor(int x, int y) {
	COORD p;
	p.X = x;
	p.Y = y + startY;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

//게임판 보여주기
void SG(int num[][19]) {
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 19; j++) {
			switch (num[i][j]) {
			case 0:
				setCursor(i * 2, j);
				puts("\u00D7");
				break;
			case 1:
				setCursor(i * 2, j);
				puts("\u25CF");
				break;
			case 2:
				setCursor(i * 2, j);
				puts("\u25CB");
				break;
			}
		}
		printf("\n");
	}
}

//방향키, 엔터 입력받기
int getDirection(int ix, int iy) {
	char c;
	int x = ix;
	int y = iy;
	setCursor(x * 2, y);

	while (true) {
		c = _getch();
		if (c == -32) {
			c = _getch();
			switch (c) {
			case 80:		//위
				if (y >= 0 && y < 18) {
					y++;
				}
				break;

			case 77:		//오른쪽
				if (x >= 0 && x < 18) {
					x++;
				}
				break;

			case 72:		//아래
				if (y > 0 && y <= 18) {
					y--;
				}
				break;

			case 75:		//왼쪽
				if (x > 0 && x <= 18) {
					x--;
				}
				break;
			}
			setCursor(x * 2, y);

			c = 0;
		}

		if (c == ' ') {
			break;
		}
	}
	return 100 * x + y;
}