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

int	nx = DIM, ny = DIM;
int	nBomb = DIM;

inline int& mask(int x, int y,int maskarr[][DIM]) { return maskarr[y][x]; }
inline int& label(int x, int y, int labelarr[][DIM]) { return labelarr[y][x]; }
inline bool	isValid(int x, int y) { return (x >= 0 && x < nx&& y >= 0 && y < ny); } 
inline bool	isBomb(int x, int y,int labelarr[][DIM]) { return isValid(x, y) && label(x, y, labelarr) == Bomb; } 
inline bool	isEmpty(int x, int y,int labelarr [][DIM]) { return isValid(x, y) && label(x, y, labelarr) == Empty; }

void dig(int x, int y, int maskarr[][DIM], int labelarr[][DIM]) { //����ũ open �Լ�
	if (isValid(x, y) && mask(x, y, maskarr) != Open) { //����ũ open�̸� ����x
		mask(x, y,maskarr) = Open;  //����ũ open
		if (label(x, y, labelarr) == 0) {
			dig(x - 1, y - 1, maskarr, labelarr);
			dig(x - 1, y, maskarr, labelarr);
			dig(x - 1, y + 1, maskarr, labelarr);
			dig(x, y - 1, maskarr, labelarr);
			dig(x, y + 1, maskarr, labelarr);
			dig(x + 1, y - 1, maskarr, labelarr);
			dig(x + 1, y, maskarr, labelarr);
			dig(x + 1, y + 1, maskarr, labelarr);  //�ֺ� labe �� 0 ���� ����ִ� lable ��� open
		}
	}
}
void mark(int x, int y,int maskarr[][DIM]) { //�÷��� ǥ�� �Լ�
	if (isValid(x, y) && mask(x, y,maskarr) == Hide)
		mask(x, y, maskarr) = Flag;
}
int getBombCount(int maskarr[][DIM]) { //����ڰ� �÷����� ����� ���� ���� �Լ�
	int count = 0;
	for (int y = 0; y < ny; y++)
		for (int x = 0; x < nx; x++)
			if (mask(x, y,maskarr) == Flag) count++;
	return count; //����ڰ� �÷����� ������ ����
}
void print(int maskarr[][DIM], int labelarr[][DIM]) { //����ȭ�� ����Լ�
	system("cls"); //�� �Լ� �������� ��¹��� ��� ����
	printf("   �߰�:%2d   ��ü:%2d\n", getBombCount(maskarr), nBomb); //����ڰ� ǥ���� �÷��׼��� ���� ���ڼ��� ���
	printf("    �� �� �� �� �� �� �� �� ��\n");
	for (int y = 0; y < ny; y++) {
		printf("%2c ", 'A' + y);
		for (int x = 0; x < nx; x++) {
			if (mask(x, y, maskarr) == Hide)	printf(" ��");
			else if (mask(x, y, maskarr) == Flag) printf(" ��");
			else {
				if (isBomb(x, y,labelarr)) printf(" ��"); //���ڰ� ������ ��� 
				else if (isEmpty(x, y,labelarr)) printf("  "); // �ֺ��� ���ڰ� ���ٸ� ��ĭ(lable = 0)
				else printf("%2d", label(x, y,labelarr));  // �ֺ� ���ڼ� ���(lable != 0)
			}
		}
		printf("\n");
	}
}
int countNbrBombs(int x, int y, int labelarr[][DIM]) { //�ֺ� ���� ���� ǥ�� �Լ�
	int count = 0;
	for (int yy = y - 1; yy <= y + 1; yy++)
		for (int xx = x - 1; xx <= x + 1; xx++)
			if (isValid(xx, yy) && label(xx, yy,labelarr) == Bomb)  // x,y �߽����� 9ĭ Ȯ�� >> ������ ���� ������ ��ź�� ������ count ����(���ڰ��� ī��Ʈ)
				count++;
	return count;
}
void init(int maskarr[][DIM], int labelarr[][DIM], int total = 9) { //������ �ʱ�ȭ �Լ�
	srand((unsigned int)time(NULL));
	for (int y = 0; y < ny; y++)
		for (int x = 0; x < nx; x++) {
			mask(x, y,maskarr) = Hide;//mask �迭 all hide=0, lable �迭 all 0(empty)
			label(x, y,labelarr) = 0;
		} //������ �ʱ�ȭ
	nBomb = total;
	for (int i = 0; i < nBomb; i++) {
		int x, y;
		do {
			x = rand() % nx;
			y = rand() % ny;
		} while (label(x, y,labelarr) != Empty);//�ߺ�����
		label(x, y,labelarr) = Bomb;//���ڼ�ġ �迭�� 9 ����
	}
	for (int y = 0; y < ny; y++)
		for (int x = 0; x < nx; x++)
			if (label(x, y,labelarr) == Empty) //���ڰ� ���ٸ�
				label(x, y,labelarr) = countNbrBombs(x, y,labelarr);//�ֺ� ��ź���� Ȯ��(��ü ������ Ȯ��)�� ���
}
bool getPos(int& x, int& y) {  //���� Ȯ�� or �÷��� ���� �Լ�
	printf("\n����(P)��(A-I)��(1-9)\n      �Է� --> ");
	bool isBomb = false;
	y = toupper(_getch()) - 'A'; //y��ġ �Է�(A ~ I)
	if (y == 'P' - 'A') {						// p �Է½� �÷��� ǥ��
		isBomb = true;							// �÷��� true�� ����
		y = toupper(_getche()) - 'A';			// y��ġ �Է� (A ~ I)
	}
	x = _getch() - '1'; //x��ġ Ȯ�� (1 ~ 9)
	return isBomb;
}
int checkDone(int maskarr[][DIM],int labelarr[][DIM]) { //�����ִ� hide ����ũ Ȯ�� >> ���ڰ� ��������, �� ã�Ҵ���, �� ã�Ҵ��� Ȯ���ϴ� �Լ�
	int count = 0;
	for (int y = 0; y < ny; y++)
		for (int x = 0; x < nx; x++) {
			if (mask(x, y,maskarr) != Open) count++; //open �ƴ� ����ũ >> count ����(�����ִ� hide ����ũ ���� üũ)
			else if (isBomb(x, y,labelarr)) return -1; //mask�� open�̰� �ش���ġ�� ���ڰ� ������ -1 ����
		}
	return (count == nBomb) ? 1 : 0; //���� ������ �����ִ� hide ����ũ ���� �� >> ���ڸ� �� ã������ 1 �ƴϸ� 0 ����
}
void playMineSweeper(int total,int maskarr[][DIM],int labelarr[][DIM]) {
	int x, y, status;
	init(maskarr,labelarr,total);//������ ����
	do {
		print(maskarr, labelarr);
		bool isBomb = getPos(x, y); //��ġ ����(�÷��� = 1 or dig = 0)
		if (isBomb) mark(x, y,maskarr); //�÷��� ǥ�ø� �ߴٸ� isBomb=true >> x,y�̿� mark �迭�� ��� ǥ��
		else		  dig(x, y,maskarr,labelarr);//�÷��� ǥ�ð� �ƴϸ� isBomb=false  >> dig
		status = checkDone(maskarr,labelarr);
	} while (status == 0); // 1�̸� ���� �� ã��, 0�̸� ��ã�� , -1�̸� ���� ���� ���ڰ� �����ų� ���ڸ� ��� ã���� ����
	print(maskarr, labelarr);
	if (status < 0)
		printf("\n����: ���� ����!!!\n\n");
	else	printf("\n����: Ž�� ����!!!\n\n");
}
void main()
{
	int	MineMapMask[DIM][DIM]; //�÷��� ǥ�� maskarr
	int	MineMapLabel[DIM][DIM]; //���� ��ġ�� �ֺ� ���� �� ��� labelarr
	int total;
	printf(" <Mine Sweeper>\n");
	printf(" �ż��� �� ������ ���� �Է� : ");
	scanf("%d", &total);
	playMineSweeper(total, MineMapMask, MineMapLabel);
}