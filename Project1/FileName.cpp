#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <memory.h>
#include <time.h>
#include <ctype.h>

#define DIM	9

enum LabelType { Empty = 0, Bomb = 9 };
enum MaskType { Hide = 0, Open, Flag };
int	MineMapMask[DIM][DIM];
int	MineMapLabel[DIM][DIM];
int	nx = DIM, ny = DIM;
int	nBomb = DIM;

inline int& mask(int x, int y) { return MineMapMask[y][x]; }
inline int& label(int x, int y) { return MineMapLabel[y][x]; }
inline bool	isValid(int x, int y) { return (x >= 0 && x < nx && y >= 0 && y < ny); } //������ �������� �ִ��� Ȯ��
inline bool	isBomb(int x, int y) { return isValid(x, y) && label(x, y) == Bomb; }  //������ �������� �ְ� ��ź�� �ִٸ� 1 return
inline bool	isEmpty(int x, int y) { return isValid(x, y) && label(x, y) == Empty; }

void dig(int x, int y) {
	if (isValid(x, y) && mask(x, y) != Open) {
		mask(x, y) = Open;
		if (label(x, y) == 0) {
			dig(x - 1, y - 1);
			dig(x - 1, y);
			dig(x - 1, y + 1);
			dig(x, y - 1);
			dig(x, y + 1);
			dig(x + 1, y - 1);
			dig(x + 1, y);
			dig(x + 1, y + 1);
		}
	}
}
void mark(int x, int y) {
	if (isValid(x, y) && mask(x, y) == Hide)
		mask(x, y) = Flag;
}
int getBombCount() {
	int count = 0;
	for (int y = 0; y < ny; y++)
		for (int x = 0; x < nx; x++)
			if (mask(x, y) == Flag) count++;
	return count;
}
void print() {
	system("cls");
	printf("   �߰�:%2d   ��ü:%2d\n", getBombCount(), nBomb);
	printf("    �� �� �� �� �� �� �� �� ��\n");
	for (int y = 0; y < ny; y++) {
		printf("%2c ", 'A' + y);
		for (int x = 0; x < nx; x++) {
			if (mask(x, y) == Hide)	printf(" ��");
			else if (mask(x, y) == Flag) printf("��");
			else {
				if (isBomb(x, y)) printf(" ��");
				else if (isEmpty(x, y)) printf("  ");
				else printf("%2d", label(x, y));
			}
		}
		printf("\n");
	}
}
int countNbrBombs(int x, int y) {
	int count = 0;
	for (int yy = y - 1; yy <= y + 1; yy++)
		for (int xx = x - 1; xx <= x + 1; xx++)
			if (isValid(xx, yy) && label(xx, yy) == Bomb)  // x,y �߽����� 9ĭ Ȯ�� >> ������ ���� ������ ��ź�� ������ count ����(���ڰ��� ī��Ʈ)
				count++;
	return count;
}
void init(int total = 9) {
	srand((unsigned int)time(NULL));
	for (int y = 0; y < ny; y++)
		for (int x = 0; x < nx; x++) {
			mask(x, y) = Hide;//mask �迭 �� hide�� lable �迭 �� 0(empty)
			label(x, y) = 0;
		} //������ �ʱ�ȭ
	nBomb = total;
	for (int i = 0; i < nBomb; i++) {
		int x, y;
		do {
			x = rand() % nx;
			y = rand() % ny;
		} while (label(x, y) != Empty);//�ߺ�����
		label(x, y) = Bomb;//���ڼ�ġ
	}
	for (int y = 0; y < ny; y++)
		for (int x = 0; x < nx; x++)
			if (label(x, y) == Empty)
				label(x, y) = countNbrBombs(x, y);//�ֺ� ��ź���� Ȯ��(��ü ������ Ȯ��)
}
bool getPos(int& x, int& y) {
	printf("\n����(P)��(A-I)��(1-9)\n      �Է� --> ");
	bool isBomb = false;
	y = toupper(_getch()) - 'A'; //y��ġ �Է�(A ~ I)
	if (y == 'P' - 'A') { // p �Է½� �÷��� ǥ��
		isBomb = true; // �÷��� true�� ����
		y = toupper(_getche()) - 'A'; // y��ġ �Է� (A ~ I)
	}
	x = _getch() - '1'; //x��ġ Ȯ�� (1 ~ 9)
	return isBomb;
}
int checkDone() {
	int count = 0;
	for (int y = 0; y < ny; y++)
		for (int x = 0; x < nx; x++) {
			if (mask(x, y) != Open) count++;
			else if (isBomb(x, y)) return -1;
		}
	return (count == nBomb) ? 1 : 0;
}
void playMineSweeper(int total) {
	int x, y, status;
	init(total);//������ ����
	do {
		print();
		bool isBomb = getPos(x, y); //isbomb �÷��� ǥ��(�÷��� ǥ����ġ x,y�� �����
		if (isBomb) mark(x, y); //�÷��� ǥ�ø� �ߴٸ�x,t�̿� mark �迭�� ����
		else		  dig(x, y);//�÷��� ǥ�ð� �ƴϸ� dig
		status = checkDone(); 
	} while (status == 0);
	print();
	if (status < 0)
		printf("\n����: ���� ����!!!\n\n");
	else	printf("\n����: Ž�� ����!!!\n\n");
}
void main()
{
	int total;
	printf(" <Mine Sweeper>\n");
	printf(" �ż��� �� ������ ���� �Է� : ");
	scanf("%d", &total);
	playMineSweeper(total);
}