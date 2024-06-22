#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable:4996)
#define MAX 190

int f_data(struct plan *ary, char *name); // ���� ������ �Է�
int calendar(int input, int *index, struct plan *ary, int cnt); // �޷°� ���� ���
int date_check(struct plan *ary, int *index, int d, int cnt); // �޷� ��� �� ������ �ִ� ������ üũ
void search_month(struct plan *ary, int cnt); // ���� ��ȸ
void showall_month(struct plan *ary, int cnt); // ��ü ��ȸ
void search_contents(struct plan *ary, int *cnt, char code, int *index_max); // ���뺰 ��ȸ
char input_code(); // �ڵ� �Է�(�޴�)
void d_day(struct tm t, struct plan p); // d-day ���
void add_plan(struct plan pl[], int *c, int *index_max); // ���� �߰�
void delete_plan(struct plan pl[], int indexary[], int n, int *cnt); // ���� ����
void save(struct plan *s, int *cnt, int index_max); // ���Ͽ� ������ ����
void reset(); // ����� ���� �⺻������ �ʱ�ȭ
void resetcheck(); // �ʱ�ȭ ��Ȯ�� �޼���
int input_change(); // ���ڿ� �Է°��� ������
int valid_month(int d); // ��ȿ�� �� �Է°����� Ȯ��
int valid_date(int m, int d); // ��ȿ�� �� �Է°����� Ȯ��

struct plan {

	int start_month, start_date;
	int final_month, final_date;
	int index;
	char contents[MAX];

};

struct tm *now;

void main() {

	int cnt, index_max;
	char t;
	struct plan ary[MAX];
	time_t ct;
	ct = time(NULL);
	now = localtime(&ct);

	cnt = f_data(ary, "user.txt");
	index_max = cnt-1;

	printf("\n  < MADE BY LYJDY >\n");


	do {
		
		printf("  -----------------------------------------------------------------------------------------------------------\n  *������ ��¥: %d�� %d��", now->tm_mon+1, now->tm_mday);
		printf("\n  *�Է¸޴� \n\n  A. ��ü ���� ��ȸ \n  B. �� �� ���� ��ȸ \n  C. ���� �� ���� ��ȸ [D-day] \n  D. ���� �߰� \n  E. ���� ���� \n  F. ���� �ʱ�ȭ \n  X. ���α׷� ����\n\n");
		printf("  �ڵ带 �Է��ϼ��� > ");
		t = input_code();
		printf("\n  -----------------------------------------------------------------------------------------------------------\n" );

		switch (t) {
		case 'a': case 'A': showall_month(ary, cnt); break;
		case 'b': case 'B': search_month(ary, cnt); break;
		case 'c': case 'C': search_contents(ary, &cnt, 's', &index_max); break;
		case 'd': case 'D': add_plan(ary, &cnt, &index_max); break;
		case 'e': case 'E': search_contents(ary, &cnt, 'd', &index_max); break;
		case 'f': case 'F': resetcheck(); break;
		case 'x': case 'X': break;
		default:printf("  �Է� �� ����\n");
		}

		cnt = f_data(ary, "user.txt");
		index_max = cnt - 1;

	} while (!(t == 'x' || t == 'X'));

}

void resetcheck() {
	char t;
	printf("  ���� �ʱ�ȭ�Ͻðڽ��ϱ�? Y/N > ");
	t = input_code();
	if (t == 'y' || t == 'Y') reset();
	else printf("��ҵǾ����ϴ�.\n\n");
}

void search_month(struct plan *ary, int cnt) {
	char input_data[20];
	int check, c, i;
	int input_month;
	int check_month[MAX];
	check = 0;
	do {
		if (check) printf("  9 ~ 12, 1 ~ 2 ������ ������ �Է����ּ��� > ");
		else printf("  ��,,, ���� �Է��Ͻÿ� > ");

		scanf("%s", input_data);

		input_month = atoi(input_data);

		for (i = 0, c = 0; i <= cnt; i++)
			if (ary[i].start_month == input_month) check_month[c++] = i;
		check++;
	} while (calendar(input_month, check_month, ary, c));


}

void showall_month(struct plan *ary, int cnt) {
	int i,c;
	int check_month[MAX];
	for (i = 0, c = 0; i <= cnt; i++)
		if (ary[i].start_month == 9) check_month[c++] = i;
	calendar(9, check_month, ary, c);

	for (i = 0, c = 0; i <= cnt; i++)
		if (ary[i].start_month == 10) check_month[c++] = i;
	calendar(10, check_month, ary, c);

	for (i = 0, c = 0; i <= cnt; i++)
		if (ary[i].start_month == 11) check_month[c++] = i;
	calendar(11, check_month, ary, c);

	for (i = 0, c = 0; i <= cnt; i++)
		if (ary[i].start_month == 12) check_month[c++] = i;
	calendar(12, check_month, ary, c);

	for (i = 0, c = 0; i <= cnt; i++)
		if (ary[i].start_month == 1) check_month[c++] = i;
	calendar(1, check_month, ary, c);

	for (i = 0, c = 0; i <= cnt; i++)
		if (ary[i].start_month == 2) check_month[c++] = i;
	calendar(2, check_month, ary, c);


}

void search_contents(struct plan *ary, int *cnt, char code, int *index_max) {
	int i, c;
	int indexary[MAX];
	char input_data[20];
	printf("  ��,,, ������ �Է��Ͻÿ� > ");
	scanf("%s", input_data);
	puts("");
	for (i = 0, c=0; i < *cnt; i++)
		if (strstr(ary[i].contents, input_data) != NULL) {
			printf("  %d. ", c + 1);
			d_day(*now, ary[i]);
			printf("%3d�� %3d��  ~  %d�� %3d�� %s\n", ary[i].start_month, ary[i].start_date, ary[i].final_month, ary[i].final_date, ary[i].contents);
			indexary[c++] = i;
		}
	if (code == 'd' && c > 0) { delete_plan(ary, indexary, c, cnt); *index_max = *index_max - 1; save(ary, cnt, *index_max); printf("  �����Ǿ����ϴ�.\n"); }
	else printf("  �˻��� �׸�: %d��\n", c);

}

int f_data(struct plan *ary, char *name) {

	int i;
	FILE *fp;

	fp = fopen(name, "r");

	for (i = 0;!feof(fp); i++) {
		fscanf(fp, "%d %d %d %d %d", &(ary + i)->start_month, &(ary + i)->start_date, &(ary + i)->final_month, &(ary + i)->final_date, &(ary + i)->index);
		fgets((ary + i)->contents, sizeof((ary + i)->contents), fp);
	}
	return i - 1;

}

int calendar(int input, int *index, struct plan *ary, int cnt) {

	int day[3][7] = { { 0, 2, 5, 0, 3, 6 /*����*/ } ,{ 31, 30, 31, 30, 31, 31, 29 }, {9,10,11,12,1,2} };
	int month;
	int max = 0;
	int i, ent, last, j;

	for (i = 0; i < 6; i++)
		if (input == day[2][i]) max = day[1][i + 1], month = i;

	if (max == 0) return 1;

	last = day[1][month] - day[0][month];
	printf("\n%4d���� �޷�\n\n", input);
	printf(" %4s %4s %4s %4s %4s %4s %4s %11s\n\n", "��", "��", "ȭ", "��", "��", "��", "��","����");

	for (i = 0, ent = 1; i < day[0][month]; i++) { //���� ��¥ ���
		printf("%5d", ++last);
		ent++;
	}
	
	for (i = 0, j = 0; i < max ||  j < cnt; i++) {
		if (i < max) {
			if (ent++ % 7 == 0) {
				if (date_check(ary, index, i, cnt)) printf("+%4d", i + 1); //�޷�ǥ��
				else printf("%5d", i + 1);
				if (j < cnt) { printf("%8c %d�� %3d��  ~ %3d�� %3d�� %s\n", '*', ary[*(index + j)].start_month, ary[*(index + j)].start_date, ary[*(index + j)].final_month, ary[*(index + j)].final_date, ary[*(index + j)].contents); }
				else printf("\n\n");
				j++;
			}
			else if(date_check(ary, index, i, cnt)) printf("+%4d", i+1);
			else printf("%5d", i+1);
		}
		else {
			if (ent++ % 7 == 0) {
				printf("%5c", '_');
				if (j < cnt) { printf("%8c %d�� %3d��  ~ %3d�� %3d�� %s\n", '*', ary[*(index + j)].start_month, ary[*(index + j)].start_date, ary[*(index + j)].final_month, ary[*(index + j)].final_date, ary[*(index + j)].contents); }
				else printf("\n\n");
				j++;
			}
			else printf("%5c",'_');
		}
	}
		

	printf("\n\n");
	return 0;
}

int date_check(struct plan *ary, int *index, int d, int cnt) {
	int i;
	for (i = 0; i < cnt; i++) {
		if(d==ary[*(index + i)].start_date) return 1;
	}
	return 0;
}

char input_code() {
	char code[10];
	scanf(" %s", code);
	return code[0];
}

void d_day(struct tm t, struct plan p) {
	int i, j;
	int day[3][10] = { { 3, 6, 1, 4, 0, 2, 5, 0, 3, 6 } ,{ 31, 30, 31, 31, 30, 31, 30, 31, 31, 29 },{ 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 } };
	int dday = p.start_date;
	int dmonth = t.tm_mon;
	int ddate = t.tm_mday;
	if (p.start_month == 1) p.start_month = 13;
	else if (p.start_month == 2) p.start_month = 14;

	//D-Day�� �˻��ϰ� ���� ������ ���� �˻� -> �˻� �� �� �߿� �ϳ� ���� �� -> dday ���.(�����ϴ� �������� D-Day�� ������, ������ �� ������ D-Day�� ������ ���� �ϱ�
	if (dmonth == p.start_month && ddate <= p.start_date || dmonth < p.start_month) {

		for (i = 0; (dmonth)+1 != day[2][i]; i++)
			;

		for (; p.start_month != day[2][i]; i++)
			dday += day[1][i];

		dday -= (t.tm_mday);

		printf("%3c-%d  |",'D', dday);
	}

}

void save(struct plan *s, int *cnt, int index_max) {
	
	
	int i, c;
	FILE *fp;
	fp = fopen("user.txt", "w");
	fclose(fp);

	fp = fopen("user.txt", "a");
	for (c = 0; c <= index_max; c++) {
		for (i = 0; i <= *cnt; i++) {

			if (s[i].index == c) { fprintf(fp, "%d %d %d %d %d %s", s[i].start_month, s[i].start_date, s[i].final_month, s[i].final_date, s[i].index, s[i].contents); }

		}
	}
	fclose(fp);
	*cnt = *cnt + 1;

}

void add_plan(struct plan pl[], int *c, int *index_max) {
	int month[MAX];
	int i, j, m;
	int max;
	int fin;
	int check;
	int index;
	/*
	for (i = 0; i <= *c; i++)
		if (pl[i].index == 0)
			break;

	*c = i;
	*/
	(pl[*c].contents)[0] = ' ';
	printf("  �߰��Ϸ��� ������ ������ �Է����ּ���.\n");
	scanf("%c");
	printf("  ���� : ");
	gets((pl[*c].contents)+1);
	printf("  ���� ��: ");
	pl[*c].start_month = valid_month(pl[*c].start_month = input_change());
	printf("  ���� ��: ");
	pl[*c].start_date = valid_date( pl[*c].start_month ,pl[*c].start_date = input_change());
	printf("  ���� ��: ");
	pl[*c].final_month = valid_month(pl[*c].final_month = input_change());
	printf("  ���� ��: ");
	pl[*c].final_date  = valid_date(pl[*c].final_month,pl[*c].final_date = input_change());
	strcat(pl[*c].contents, "\n");

	for (i = 0; i <= *c; i++) {
		if (pl[i].start_month == 1 || pl[i].start_month == 2)
			month[i] = pl[i].start_month + 12;
		else month[i] = pl[i].start_month;
	}

	for (index = 0, check = 1; index <= *index_max && check; index++)
		for (i = 0; i < *c && check; i++)

			if (pl[i].index == index)
					if (month[i] >= month[*c])
					{
						if (pl[i].start_date > pl[*c].start_date || month[i] > month[*c] || pl[i].index == index_max ) {
							pl[*c].index = pl[i].index;
							check = 0;
						}
					}
	

	for (index = *index_max; index >= pl[*c].index; index--) {
		for (i = 0; i < *c; i++)
			if (pl[i].index == index)
				pl[i].index++;
	}

	*index_max = *index_max + 1;
	save(pl, c, *index_max);


}

void delete_plan(struct plan pl[], int indexary[], int n, int *cnt) {
	struct plan p[MAX];
	int i, inputindex;
	char inputdata[2];
	printf("  ������ ���ϴ� ���� ���� ���ڸ� �Է����ּ��� > ");
	scanf("%s", inputdata);

	inputindex = atoi(inputdata);

	while (!(inputindex >= 1 && inputindex <= n)) {
		printf("  �߸� �Է��ϼ̽��ϴ�. �ٽ� �Է����ּ���.\n");
		printf("  ������ ���ϴ� ���� ���� ���ڸ� �Է����ּ���.\n");
		scanf("%s", inputdata);
		inputindex = atoi(inputdata);
	}

	for (i = 0; i < *cnt; i++)
		if (pl[i].index >= pl[indexary[inputindex]].index)
			pl[i].index--;

	pl[indexary[inputindex-1]].index = -1;

}

void reset() {

	char s[MAX];
	FILE *fp1, *fp2;
	fp1 = fopen("default.txt", "r");
	fp2 = fopen("user.txt", "w");
	fclose(fp2);
	fp2 = fopen("user.txt", "a");

	while (!feof(fp1)) {
		fgets(s, sizeof(s), fp1);
		fprintf(fp2, "%s", s);
	}

	fclose(fp1);
	fclose(fp2);

	printf("  ������ �ʱ�ȭ�Ǿ����ϴ�.\n\n");

}

int input_change() {
	int n;
	char s[20];
	scanf("%s", s);
	n = atoi(s);
	return n;
}

int valid_month(int d) {
	while (!(d >= 9 && d <= 12 || d == 1 || d == 2)) {
		printf("  �߸� �Է��Ͽ����ϴ�. �ٽ� �Է����ּ���(��). > ");
		d = input_change();
	}
	return d;
}

int valid_date(int m, int d) {
	int i;
	int day[3][10] = { { 3, 6, 1, 4, 0, 2, 5, 0, 3, 6 } ,
	{ 31, 30, 31, 31, 30, 31, 30, 31, 31, 29 },
	{ 5, 6, 7, 8, 9, 10, 11, 12, 1, 2 }
	};

	for (i = 0; day[2][i] != m; i++)
		;

	while (!(d >= 1 && d <= day[1][i])) {
		printf("  �߸� �Է��Ͽ����ϴ�. �ٽ� �Է����ּ���(��). > ");
		d = input_change();
	}
	return d;
}