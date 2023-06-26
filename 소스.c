#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <stdbool.h>
#include <conio.h>
#include <time.h>

int play();
void setCursor(int x, int y);
void setColor(int color);
void showGame(int[][19]);
int getDirection(int ix, int iy);
int isWin(int num[][19], int x, int y, int BW);

int startY = 1;

int main() {
	setColor(11);
	printf("---------------- 오목 ----------------");

	setColor(15);
	setCursor(44, 5);
	printf("위치변경 : 방향키");
	setCursor(44, 6);
	printf("위치변경 완료 : 스페이스 바");


	setColor(6);
	setCursor(44, 10);
	printf("------ 메세지 ------");


	time_t start = time(NULL);

	int order = play();

	time_t end = time(NULL);

	setColor(6);
	setCursor(44, 14);
	printf("------ 게임결과 ------");
	setCursor(44, 15);
	if (order)	printf("백돌 승!");
	else	printf("흑돌 승!");
	setCursor(44, 16);
	printf("소요시간 : %dsec", (int)(end - start));

	setCursor(44, 17);
	printf("종료하려면 스페이스바를 누르세요");
	getDirection(44, 16);

	setCursor(44, 20);
	return 0;
}


int play() {
	int game[19][19] = { 0 };
	int order = 0;		//0 = 흑, 1 = 백
	int x = 0;
	int y = 0;

	while (true) {
		//게임판 표시
		showGame(game);

		setColor(15);
		setCursor(46, 0);
		printf("흑돌");
		setCursor(46, 3);
		printf("백돌");

		//순서 표시
		if (order) {
			setColor(15);
			setCursor(44, 0);
			printf(" ");
			setColor(11);
			setCursor(44, 3);
			printf(">");
		}
		else {
			setColor(11);
			setCursor(44, 0);
			printf(">");
			setColor(15);
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
				setCursor(44, 11);
				printf("                ");
				break;
			}
			else {
				setColor(6);
				setCursor(44, 11);
				printf("다른곳에 두세요!");
			}
		}

		if (isWin(game, x, y, (order ? 1 : -1))) {
			showGame(game);
			break;
		}
		order = ~order;		//순서 변경
	}

	return order;
}


//커서위치 변경
void setCursor(int x, int y) {
	COORD p;
	p.X = x;
	p.Y = y + startY;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

//글자 색상 변경
void setColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

//게임판 보여주기
void showGame(int num[][19]) {
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 19; j++) {
			switch (num[i][j]) {
			case 0:
				setColor(4);
				setCursor(i * 2, j);
				puts("\u00D7");
				break;
			case 1:
				setColor(15);
				setCursor(i * 2, j);
				puts("\u25CF");
				break;
			case -1:
				setColor(15);
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
		if (c == -32) {		//첫번째 입력 값이 -32일때
			c = _getch();	//두번째 입력 값 받아서 c에 저장
			switch (c) {
			case 80:		//c가 80일때 = 위
				if (y >= 0 && y < 18) {
					y++;	//y값이 게임판을 넘지 않았을때 y++
				}
				break;

			case 77:		//c가 77일때 = 오른쪽
				if (x >= 0 && x < 18) {
					x++;	//y값이 게임판을 넘지 않았을때 x++
				}
				break;

			case 72:		//c가 72일때 = 아래
				if (y > 0 && y <= 18) {
					y--;	//y값이 게임판을 넘지 않았을때 y--
				}
				break;

			case 75:		//c가 75일때 = 왼쪽
				if (x > 0 && x <= 18) {
					x--;	//y값이 게임판을 넘지 않았을때 x--
				}
				break;
			}
			setCursor(x * 2, y);	//현재 위치 표시
		}

		else if (c == ' ') {	//스페이스 키를 입력 했을 때 = 위치 선택을 완료 했을 때
			break;
		}
	}
	return 100 * x + y;		//x y 값을 한번에 반환
}

//이겼는지 판단
int isWin(int num[][19], int x, int y, int BW) {
	int count;

	for (int direction = 1; direction <= 4; direction++) {
		count = 0;

		if (direction == 1) {		//우하향 대각선
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

		else {		//우상향 대각선
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
	}

	return 0;
}