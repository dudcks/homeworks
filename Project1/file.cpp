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
inline bool	isValid(int x, int y) { return (x >= 0 && x < nx&& y >= 0 && y < ny); } //선택한 위치가 지뢰판 범위내에 있는지 확인
inline bool	isBomb(int x, int y,int labelarr[][DIM]) { return isValid(x, y) && label(x, y, labelarr) == Bomb; }   //선택한 위치가 지뢰판 범위내에 있고 lable 에 폭탄이 있으면 1
inline bool	isEmpty(int x, int y,int labelarr [][DIM]) { return isValid(x, y) && label(x, y, labelarr) == Empty; }

void dig(int x, int y, int maskarr[][DIM], int labelarr[][DIM]) { //마스크 open 함수
	if (isValid(x, y) && mask(x, y, maskarr) != Open) { //마스크 open이면 실행x
		mask(x, y,maskarr) = Open;  //마스크 open
		if (label(x, y, labelarr) == 0) {
			dig(x - 1, y - 1, maskarr, labelarr);
			dig(x - 1, y, maskarr, labelarr);
			dig(x - 1, y + 1, maskarr, labelarr);
			dig(x, y - 1, maskarr, labelarr);
			dig(x, y + 1, maskarr, labelarr);
			dig(x + 1, y - 1, maskarr, labelarr);
			dig(x + 1, y, maskarr, labelarr);
			dig(x + 1, y + 1, maskarr, labelarr);  //주변 labe 중 0 값이 들어있는 lable 모두 open
		}
	}
}
void mark(int x, int y,int maskarr[][DIM]) { //플래그 표시 함수
	if (isValid(x, y) && mask(x, y,maskarr) == Hide)
		mask(x, y, maskarr) = Flag;
}
int getBombCount(int maskarr[][DIM]) { //사용자가 플래그한 깃발의 개수 리턴 함수
	int count = 0;
	for (int y = 0; y < ny; y++)
		for (int x = 0; x < nx; x++)
			if (mask(x, y,maskarr) == Flag) count++;
	return count; //사용자가 플래그한 갯수를 리턴
}
void print(int maskarr[][DIM], int labelarr[][DIM]) { //게임화면 출력함수
	system("cls"); //이 함수 전까지의 출력물을 모두 지움
	printf("   발견:%2d   전체:%2d\n", getBombCount(maskarr), nBomb); //사용자가 표시한 플래그수와 실제 지뢰수를 출력
	printf("    ① ② ③ ④ ⑤ ⑥ ⑦ ⑧ ⑨\n");
	for (int y = 0; y < ny; y++) {
		printf("%2c ", 'A' + y);
		for (int x = 0; x < nx; x++) {
			if (mask(x, y, maskarr) == Hide)	printf(" □");
			else if (mask(x, y, maskarr) == Flag) printf(" ¤");
			else {
				if (isBomb(x, y,labelarr)) printf(" ※"); //지뢰가 터지면 출력 
				else if (isEmpty(x, y,labelarr)) printf("  "); // 주변에 지뢰가 없다면 빈칸(lable = 0)
				else printf("%2d", label(x, y,labelarr));  // 주변 지뢰수 출력(lable != 0)
			}
		}
		printf("\n");
	}
}
int countNbrBombs(int x, int y, int labelarr[][DIM]) { //주변 지뢰 개수 표시 함수
	int count = 0;
	for (int yy = y - 1; yy <= y + 1; yy++)
		for (int xx = x - 1; xx <= x + 1; xx++)
			if (isValid(xx, yy) && label(xx, yy,labelarr) == Bomb)  // x,y 중심으로 9칸 확인 >> 지뢰판 범위 내에서 폭탄이 있으면 count 증가(지뢰개수 카운트)
				count++;
	return count;
}
void init(int maskarr[][DIM], int labelarr[][DIM], int total = 9) { //지뢰판 초기화 함수
	srand((unsigned int)time(NULL));
	for (int y = 0; y < ny; y++)
		for (int x = 0; x < nx; x++) {
			mask(x, y,maskarr) = Hide;//mask 배열 all hide=0, lable 배열 all 0(empty)
			label(x, y,labelarr) = 0;
		} //지뢰판 초기화
	nBomb = total;
	for (int i = 0; i < nBomb; i++) {
		int x, y;
		do {
			x = rand() % nx;
			y = rand() % ny;
		} while (label(x, y,labelarr) != Empty);//중복방지
		label(x, y,labelarr) = Bomb;//지뢰설치 배열에 9 저장
	}
	for (int y = 0; y < ny; y++)
		for (int x = 0; x < nx; x++)
			if (label(x, y,labelarr) == Empty) //지뢰가 없다면
				label(x, y,labelarr) = countNbrBombs(x, y,labelarr);//주변 폭탄개수 확인(전체 지뢰판 확인)후 기록
}
bool getPos(int& x, int& y) {  //지뢰 확인 or 플래그 선택 함수
	printf("\n지뢰(P)행(A-I)열(1-9)\n      입력 --> ");
	bool isBomb = false;
	y = toupper(_getch()) - 'A'; //y위치 입력(A ~ I)
	if (y == 'P' - 'A') {						// p 입력시 플래그 표시
		isBomb = true;							// 플래그 true로 변경
		y = toupper(_getche()) - 'A';			// y위치 입력 (A ~ I)
	}
	x = _getch() - '1'; //x위치 확인 (1 ~ 9)
	return isBomb;
}
int checkDone(int maskarr[][DIM],int labelarr[][DIM]) { //남아있는 hide 마스크 확인 >> 지뢰가 터졌는지, 다 찾았는지, 덜 찾았는지 확인하느 함수
	int count = 0;
	for (int y = 0; y < ny; y++)
		for (int x = 0; x < nx; x++) {
			if (mask(x, y,maskarr) != Open) count++; //open 아닌 마스크 >> count 증가(남아있는 hide 마스크 개수 체크)
			else if (isBomb(x, y,labelarr)) return -1; //mask가 open이고 해당위치에 지뢰가 있으면 -1 리턴
		}
	return (count == nBomb) ? 1 : 0; //지뢰 개수와 남아있는 hide 마스크 개수 비교 >> 지뢰를 다 찾았으면 1 아니며 0 리턴
}
void playMineSweeper(int total,int maskarr[][DIM],int labelarr[][DIM]) {
	int x, y, status;
	init(maskarr,labelarr,total);//지뢰판 설정
	do {
		print(maskarr, labelarr);
		bool isBomb = getPos(x, y); //위치 선택(플래그 = 1 or dig = 0)
		if (isBomb) mark(x, y,maskarr); //플래그 표시를 했다면 isBomb=true >> x,y이용 mark 배열에 깃발 표시
		else		  dig(x, y,maskarr,labelarr);//플래스 표시가 아니면 isBomb=false  >> dig
		status = checkDone(maskarr,labelarr);
	} while (status == 0); // 1이면 지뢰 다 찾음, 0이면 덜찾음 , -1이면 지뢰 터짐 지뢰가 터지거나 지뢰를 모두 찾으면 종료
	print(maskarr, labelarr);
	if (status < 0)
		printf("\n실패: 지뢰 폭발!!!\n\n");
	else	printf("\n성공: 탐색 성공!!!\n\n");
}
void main()
{
	int	MineMapMask[DIM][DIM]; //플래그 표시 maskarr
	int	MineMapLabel[DIM][DIM]; //지뢰 위치와 주변 지뢰 수 기록 labelarr
	int total;
	printf(" <Mine Sweeper>\n");
	printf(" 매설할 총 지뢰의 개수 입력 : ");
	scanf("%d", &total);
	playMineSweeper(total, MineMapMask, MineMapLabel);
}