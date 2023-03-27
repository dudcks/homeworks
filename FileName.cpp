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
inline bool	isValid(int x, int y) { return (x >= 0 && x < nx && y >= 0 && y < ny); } //지뢰판 범위내에 있는지 확인
inline bool	isBomb(int x, int y) { return isValid(x, y) && label(x, y) == Bomb; }  //지뢰판 범위내에 있고 폭탄이 있다면 1 return
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
	printf("   발견:%2d   전체:%2d\n", getBombCount(), nBomb);
	printf("    ① ② ③ ④ ⑤ ⑥ ⑦ ⑧ ⑨\n");
	for (int y = 0; y < ny; y++) {
		printf("%2c ", 'A' + y);
		for (int x = 0; x < nx; x++) {
			if (mask(x, y) == Hide)	printf(" □");
			else if (mask(x, y) == Flag) printf("¤");
			else {
				if (isBomb(x, y)) printf(" ※");
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
			if (isValid(xx, yy) && label(xx, yy) == Bomb)  // x,y 중심으로 9칸 확인 >> 지뢰판 범위 내에서 폭탄이 있으면 count 증가(지뢰개수 카운트)
				count++;
	return count;
}
void init(int total = 9) {
	srand((unsigned int)time(NULL));
	for (int y = 0; y < ny; y++)
		for (int x = 0; x < nx; x++) {
			mask(x, y) = Hide;//mask 배열 다 hide로 lable 배열 다 0(empty)
			label(x, y) = 0;
		} //지뢰판 초기화
	nBomb = total;
	for (int i = 0; i < nBomb; i++) {
		int x, y;
		do {
			x = rand() % nx;
			y = rand() % ny;
		} while (label(x, y) != Empty);//중복방지
		label(x, y) = Bomb;//지뢰설치
	}
	for (int y = 0; y < ny; y++)
		for (int x = 0; x < nx; x++)
			if (label(x, y) == Empty)
				label(x, y) = countNbrBombs(x, y);//주변 폭탄개수 확인(전체 지뢰판 확인)
}
bool getPos(int& x, int& y) {
	printf("\n지뢰(P)행(A-I)열(1-9)\n      입력 --> ");
	bool isBomb = false;
	y = toupper(_getch()) - 'A'; //y위치 입력(A ~ I)
	if (y == 'P' - 'A') { // p 입력시 플래그 표시
		isBomb = true; // 플래그 true로 변경
		y = toupper(_getche()) - 'A'; // y위치 입력 (A ~ I)
	}
	x = _getch() - '1'; //x위치 확인 (1 ~ 9)
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
	init(total);//지뢰판 설정
	do {
		print();
		bool isBomb = getPos(x, y); //isbomb 플래그 표시(플래그 표시위치 x,y에 저장됨
		if (isBomb) mark(x, y); //플래그 표시를 했다면x,t이용 mark 배열에 저장
		else		  dig(x, y);//플래스 표시가 아니면 dig
		status = checkDone(); 
	} while (status == 0);
	print();
	if (status < 0)
		printf("\n실패: 지뢰 폭발!!!\n\n");
	else	printf("\n성공: 탐색 성공!!!\n\n");
}
void main()
{
	int total;
	printf(" <Mine Sweeper>\n");
	printf(" 매설할 총 지뢰의 개수 입력 : ");
	scanf("%d", &total);
	playMineSweeper(total);
}