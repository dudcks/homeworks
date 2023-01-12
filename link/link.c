#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student_info SINFO;

void get_su();
void prin();
void insert_node(SINFO* student);
void delet();

struct student_info {
	char id[16];
	char name[16];
	int score;
	struct studebt_info* next;
};

SINFO* listhead = NULL;

void main() {
	get_su();
	prin();
	delet();
}

void get_su() {
	struct student_info student;
	while (1) {
		printf("�й� �Է�(-1�Է½� ����):");
		scanf("%s", student.id);
		if (strcmp(student.id, "-1") != 0) {
			printf("�̸�:");
			scanf("%s", student.name);
			printf("����:");
			scanf("%d", &student.score);
			insert_node(&student);
		}
		else
			break;
	}
}

void insert_node(SINFO* student) {
	SINFO* temp = (SINFO*)malloc(sizeof(SINFO));
	strcpy(temp->id, student->id);
	strcpy(temp->name, student->name);
	temp->score = student->score;

	SINFO* search;
	SINFO* befor =NULL;
	search = listhead;
	while (search != NULL) {
		if (temp->score < search->score) {
			befor = search;
			search = search->next;
		}
		else
			break;
	}
	if (befor == NULL) {
		temp->next = listhead;
		listhead = temp;
	}
	else {
		temp->next = search;
		befor->next = temp;
	}

	//SINFO* search;
	//SINFO* befor = NULL;
	//search = listhead;
	// �ݺ� sreach�� NULL�� �ƴҶ�����
		//listhead �� temp�� ������ ���Ͽ� tempd.score>=��ġ.score�̸�
			// befor->next=��ġ
			// ��ġ->next=listhead;
			// break;
		//listhead�� ���� ��带 ����Ű�� �Ѵ�.
}

void prin() {
	SINFO *search;
	search = listhead;
	while (search != NULL) {
		printf("%s  %s  %d\n", search->id, search->name, search->score);
		search = search->next;
	}
}

void delet() {
	struct student* temp;
	temp = listhead;
	while (listhead != NULL) {
		listhead = listhead->next;
		free(temp);
		temp = listhead;
	}
}

