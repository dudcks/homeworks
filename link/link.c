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
		printf("학번 입력(-1입력시 종료):");
		scanf("%s", student.id);
		if (strcmp(student.id, "-1") != 0) {
			printf("이름:");
			scanf("%s", student.name);
			printf("성적:");
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
	// 반복 sreach가 NULL이 아닐때까지
		//listhead 와 temp의 성적을 비교하여 tempd.score>=서치.score이면
			// befor->next=서치
			// 서치->next=listhead;
			// break;
		//listhead가 다음 노드를 가리키게 한다.
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

