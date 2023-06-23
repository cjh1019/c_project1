#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <stdbool.h>
#include <conio.h>

void setCursor(int x, int y);
void showGame(int[][19]);
int getDirection(int ix, int iy);
int startY = 1;

int main() {
	int game[19][19] = { 0 };
	int order = 0;		//0 = 흑, 1 = 백
	int x = 0;
	int y = 0;

	printf("---------------- 오목 ----------------");
	setCursor(44, 5);
	printf("위치변경 : 방향키");
	setCursor(44, 6);
	printf("위치변경 완료 : 스페이스 바");

	while (true) {
		//게임판 표시
		showGame(game);

		setCursor(46, 0);
		printf("흑돌");
		setCursor(46, 3);
		printf("백돌");

		//순서 표시
		if (order) {
			setCursor(44, 0);
			printf(" ");
			setCursor(44, 3);
			printf(">");
		}
		else {
			setCursor(44, 0);
			printf(">");
			setCursor(44, 3);
			printf(" ");
		}

		//입력받기
		while (true) {
			int xy = getDirection(x, y);
			x = xy / 100;		//입력받은 x값 저장
			y = xy % 100;		//입력받은 y값 저장

			if (game[x][y] == 0) {
				game[x][y] = (order ? 1 : -1);
				setCursor(44, 16);
				printf("                ");
				break;
			}
			else {
				setCursor(44, 16);
				printf("다른곳에 두세요!");
			}
		}

		if (isWin(game, x, y, (order ? 1 : -1))) {
			showGame(game);
			break;
		}
		order = ~order;		//순서 변경
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
void showGame(int num[][19]) {
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
			case -1:
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

//이겼는지 판단
int isWin(int num[][19], int x, int y, int BW) {
	int count;

	for (int direction = 1; direction <= 4; direction ++) {
		count = 0;

		if (direction == 1) {		//기울기=-1인 대각선
			for (int i = 0; i < 5; i++) {
				if (x + i == 19 || y + i == 19)	break;

				if (num[x + i][y + i] == BW) {
					count++;
				}
				else break;
			}

			if (count < 5) {
				for (int i = 1; i < 5; i++) {
					if (x - i == -1 || y - i == -1)	break;

					if (num[x - i][y - i] == BW) {
						count++;
					}
					else break;
				}
			}
		}

		else if (direction == 2) {		//수직
			for (int i = 0; i < 5; i++) {
				if (x + i == 19) break;

				if (num[x + i][y] == BW) {
					count++;
				}
				else break;
			}

			if (count < 5) {
				for (int i = 1; i < 5; i++) {
					if (x - i == -1) break;

					if (num[x - i][y] == BW) {
						count++;
					}
					else break;
				}
			}
		}

		else if (direction == 3) {		//수평
			for (int i = 0; i < 5; i++) {
				if (y + i == 19) break;

				if (num[x][y + i] == BW) {
					count++;
				}
				else break;
			}

			if (count < 5) {
				for (int i = 1; i < 5; i++) {
					if (y - i == -1) break;

					if (num[x][y - i] == BW) {
						count++;
					}
					else break;
				}
			}
		}

		else {		//기울기=1인 대각선
			for (int i = 0; i < 5; i++) {
				if (x + i == 19 || y - i == -1)	break;

				if (num[x + i][y - i] == BW) {
					count++;
				}
				else break;
			}

			if (count < 5) {
				for (int i = 1; i < 5; i++) {
					if (x - i == -1 || y + i == 19)	break;


					if (num[x - i][y + i] == BW) {
						count++;
					}
					else break;
				}
			}
		}

		if (count == 5)	return 1;
		else return 0;
	}
}