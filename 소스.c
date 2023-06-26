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
	printf("---------------- ���� ----------------");

	setColor(15);
	setCursor(44, 5);
	printf("��ġ���� : ����Ű");
	setCursor(44, 6);
	printf("��ġ���� �Ϸ� : �����̽� ��");


	setColor(6);
	setCursor(44, 10);
	printf("------ �޼��� ------");


	time_t start = time(NULL);

	int order = play();

	time_t end = time(NULL);

	setColor(6);
	setCursor(44, 14);
	printf("------ ���Ӱ�� ------");
	setCursor(44, 15);
	if (order)	printf("�鵹 ��!");
	else	printf("�浹 ��!");
	setCursor(44, 16);
	printf("�ҿ�ð� : %dsec", (int)(end - start));

	setCursor(44, 17);
	printf("�����Ϸ��� �����̽��ٸ� ��������");
	getDirection(44, 16);

	setCursor(44, 20);
	return 0;
}


int play() {
	int game[19][19] = { 0 };
	int order = 0;		//0 = ��, 1 = ��
	int x = 0;
	int y = 0;

	while (true) {
		//������ ǥ��
		showGame(game);

		setColor(15);
		setCursor(46, 0);
		printf("�浹");
		setCursor(46, 3);
		printf("�鵹");

		//���� ǥ��
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

		//�Է¹ޱ�
		while (true) {
			int xy = getDirection(x, y);
			x = xy / 100;		//�Է¹��� x�� ����
			y = xy % 100;		//�Է¹��� y�� ����

			if (game[x][y] == 0) {
				game[x][y] = (order ? 1 : -1);
				setCursor(44, 11);
				printf("                ");
				break;
			}
			else {
				setColor(6);
				setCursor(44, 11);
				printf("�ٸ����� �μ���!");
			}
		}

		if (isWin(game, x, y, (order ? 1 : -1))) {
			showGame(game);
			break;
		}
		order = ~order;		//���� ����
	}

	return order;
}


//Ŀ����ġ ����
void setCursor(int x, int y) {
	COORD p;
	p.X = x;
	p.Y = y + startY;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

//���� ���� ����
void setColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

//������ �����ֱ�
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

//����Ű, ���� �Է¹ޱ�
int getDirection(int ix, int iy) {
	char c;
	int x = ix;
	int y = iy;
	setCursor(x * 2, y);

	while (true) {
		c = _getch();
		if (c == -32) {		//ù��° �Է� ���� -32�϶�
			c = _getch();	//�ι�° �Է� �� �޾Ƽ� c�� ����
			switch (c) {
			case 80:		//c�� 80�϶� = ��
				if (y >= 0 && y < 18) {
					y++;	//y���� �������� ���� �ʾ����� y++
				}
				break;

			case 77:		//c�� 77�϶� = ������
				if (x >= 0 && x < 18) {
					x++;	//y���� �������� ���� �ʾ����� x++
				}
				break;

			case 72:		//c�� 72�϶� = �Ʒ�
				if (y > 0 && y <= 18) {
					y--;	//y���� �������� ���� �ʾ����� y--
				}
				break;

			case 75:		//c�� 75�϶� = ����
				if (x > 0 && x <= 18) {
					x--;	//y���� �������� ���� �ʾ����� x--
				}
				break;
			}
			setCursor(x * 2, y);	//���� ��ġ ǥ��
		}

		else if (c == ' ') {	//�����̽� Ű�� �Է� ���� �� = ��ġ ������ �Ϸ� ���� ��
			break;
		}
	}
	return 100 * x + y;		//x y ���� �ѹ��� ��ȯ
}

//�̰���� �Ǵ�
int isWin(int num[][19], int x, int y, int BW) {
	int count;

	for (int direction = 1; direction <= 4; direction++) {
		count = 0;

		if (direction == 1) {		//������ �밢��
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

		else if (direction == 2) {		//����
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

		else if (direction == 3) {		//����
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

		else {		//����� �밢��
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