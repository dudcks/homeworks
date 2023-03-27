//#pragma once
//#define _CRT_SECURE_NO_WARNINGS
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <conio.h>
//#include <memory.h>
//#include <time.h>
//#include <ctype.h>
//
//#define DIM	9
//
//enum LabelType { Empty = 0, Bomb = 9 };
//enum MaskType { Hide = 0, Open, Flag };
//int	MineMapMask[DIM][DIM]; //�÷��� ǥ��
//int	MineMapLabel[DIM][DIM]; //���� ��ġ�� �ֺ� ���� �� ���
//int	nx = DIM, ny = DIM;
//int	nBomb = DIM;
//
//inline int& mask(int x, int y) { return MineMapMask[y][x]; }
//inline int& label(int x, int y) { return MineMapLabel[y][x]; }
//inline bool	isValid(int x, int y) { return (x >= 0 && x < nx && y >= 0 && y < ny); } //������ ��ġ�� ������ �������� �ִ��� Ȯ��
//inline bool	isBomb(int x, int y) { return isValid(x, y) && label(x, y) == Bomb; }   //������ ��ġ�� ������ �������� �ְ� lable �� ��ź�� ������ 1
//inline bool	isEmpty(int x, int y) { return isValid(x, y) && label(x, y) == Empty; }
//
//void dig(int x, int y) { //����ũ open �Լ�
//	if (isValid(x, y) && mask(x, y) != Open) { //����ũ open�̸� ����x
//		mask(x, y) = Open;  //����ũ open
//		if (label(x, y) == 0) { 
//			dig(x - 1, y - 1);
//			dig(x - 1, y);
//			dig(x - 1, y + 1);
//			dig(x, y - 1);
//			dig(x, y + 1);
//			dig(x + 1, y - 1);
//			dig(x + 1, y);
//			dig(x + 1, y + 1);  //�ֺ� labe �� 0 ���� ����ִ� lable ��� open
//		}
//	}
//}
//void mark(int x, int y) { //�÷��� ǥ�� �Լ�
//	if (isValid(x, y) && mask(x, y) == Hide)
//		mask(x, y) = Flag;
//}
//int getBombCount() { //����ڰ� �÷����� ����� ���� ���� �Լ�
//	int count = 0;
//	for (int y = 0; y < ny; y++)
//		for (int x = 0; x < nx; x++)
//			if (mask(x, y) == Flag) count++;
//	return count; //����ڰ� �÷����� ������ ����
//}
//void print() { //����ȭ�� ����Լ�
//	system("cls"); //�� �Լ� �������� ��¹��� ��� ����
//	printf("   �߰�:%2d   ��ü:%2d\n", getBombCount(), nBomb); //����ڰ� ǥ���� �÷��׼��� ���� ���ڼ��� ���
//	printf("    �� �� �� �� �� �� �� �� ��\n");
//	for (int y = 0; y < ny; y++) {
//		printf("%2c ", 'A' + y); 
//		for (int x = 0; x < nx; x++) {
//			if (mask(x, y) == Hide)	printf(" ��"); 
//			else if (mask(x, y) == Flag) printf(" ��");
//			else {
//				if (isBomb(x, y)) printf(" ��"); //���ڰ� ������ ��� 
//				else if (isEmpty(x, y)) printf("  "); // �ֺ��� ���ڰ� ���ٸ� ��ĭ(lable = 0)
//				else printf("%2d", label(x, y));  // �ֺ� ���ڼ� ���(lable != 0)
//			}
//		}
//		printf("\n");
//	}
//}
//int countNbrBombs(int x, int y) { //�ֺ� ���� ���� ǥ�� �Լ�
//	int count = 0;
//	for (int yy = y - 1; yy <= y + 1; yy++)
//		for (int xx = x - 1; xx <= x + 1; xx++)
//			if (isValid(xx, yy) && label(xx, yy) == Bomb)  // x,y �߽����� 9ĭ Ȯ�� >> ������ ���� ������ ��ź�� ������ count ����(���ڰ��� ī��Ʈ)
//				count++;
//	return count;
//}
//void init(int total = 9) { //������ �ʱ�ȭ �Լ�
//	srand((unsigned int)time(NULL));
//	for (int y = 0; y < ny; y++)
//		for (int x = 0; x < nx; x++) {
//			mask(x, y) = Hide;//mask �迭 all hide=0, lable �迭 all 0(empty)
//			label(x, y) = 0;
//		} //������ �ʱ�ȭ
//	nBomb = total;
//	for (int i = 0; i < nBomb; i++) {
//		int x, y;
//		do {
//			x = rand() % nx;
//			y = rand() % ny;
//		} while (label(x, y) != Empty);//�ߺ�����
//		label(x, y) = Bomb;//���ڼ�ġ �迭�� 9 ����
//	}
//	for (int y = 0; y < ny; y++)
//		for (int x = 0; x < nx; x++)
//			if (label(x, y) == Empty) //���ڰ� ���ٸ�
//				label(x, y) = countNbrBombs(x, y);//�ֺ� ��ź���� Ȯ��(��ü ������ Ȯ��)�� ���
//}
//bool getPos(int& x, int& y) {  //���� Ȯ�� or �÷��� ���� �Լ�
//	printf("\n����(P)��(A-I)��(1-9)\n      �Է� --> ");
//	bool isBomb = false;
//	y = toupper(_getch()) - 'A'; //y��ġ �Է�(A ~ I)
//	if (y == 'P' - 'A') {						// p �Է½� �÷��� ǥ��
//		isBomb = true;							// �÷��� true�� ����
//		y = toupper(_getche()) - 'A';			// y��ġ �Է� (A ~ I)
//	}
//	x = _getch() - '1'; //x��ġ Ȯ�� (1 ~ 9)
//	return isBomb;
//}
//int checkDone() { //�����ִ� hide ����ũ Ȯ�� >> ���ڰ� ��������, �� ã�Ҵ���, �� ã�Ҵ��� Ȯ���ϴ� �Լ�
//	int count = 0;
//	for (int y = 0; y < ny; y++)
//		for (int x = 0; x < nx; x++) {
//			if (mask(x, y) != Open) count++; //open �ƴ� ����ũ >> count ����(�����ִ� hide ����ũ ���� üũ)
//			else if (isBomb(x, y)) return -1; //mask�� open�̰� �ش���ġ�� ���ڰ� ������ -1 ����
//		}
//	return (count == nBomb) ? 1 : 0; //���� ������ �����ִ� hide ����ũ ���� �� >> ���ڸ� �� ã������ 1 �ƴϸ� 0 ����
//}
//void playMineSweeper(int total) {
//	int x, y, status;
//	init(total);//������ ����
//	do {
//		print();
//		bool isBomb = getPos(x, y); //��ġ ����(�÷��� = 1 or dig = 0)
//		if (isBomb) mark(x, y); //�÷��� ǥ�ø� �ߴٸ� isBomb=true >> x,y�̿� mark �迭�� ��� ǥ��
//		else		  dig(x, y);//�÷��� ǥ�ð� �ƴϸ� isBomb=false  >> dig
//		status = checkDone(); 
//	} while (status == 0); // 1�̸� ���� �� ã��, 0�̸� ��ã�� , -1�̸� ���� ���� ���ڰ� �����ų� ���ڸ� ��� ã���� ����
//	print();
//	if (status < 0)
//		printf("\n����: ���� ����!!!\n\n");
//	else	printf("\n����: Ž�� ����!!!\n\n");
//}
//void main()
//{
//	int total;
//	printf(" <Mine Sweeper>\n");
//	printf(" �ż��� �� ������ ���� �Է� : ");
//	scanf("%d", &total);
//	playMineSweeper(total);
//}