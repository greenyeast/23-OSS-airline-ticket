#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// #include "admin.h"

// �װ��� ����
// �װ��� ���� ����
// �װ��� ����

// typedef struct{
//     User *user; // �ƴϸ� user typedef struct ������
//     Airplane *airplane; // airplane typedef struct ������ 
//     int passengers;    // ž���ο� ��
//     char seatNum[5];    // a1, a2, ...
// } Ticket;

// typedef struct{
//     char userId[20];
//     char pw[20];
//     char name[20];
//     int age;
// } User;

// ����� ���� ������
typedef struct{
    char airPlaneName[100];  // HAN122,
    char gate;    // A,B...
    char department[100]; // ������
    char departureTime[10];  // ��߽ð�
    int seatNum;    // �¼� ��, �ִ� �¼����� 180�¼�, �Է¹������� �ټ��� �Է¹��� ��.
    char seatName[26][5];  // isalpha() ���
} Airplane;

void readAirplane(Airplane *ap);
void c_Airplane(Airplane *ap[], int index);
void listAirplane(Airplane *ap[], int index);
void d_Airplane(Airplane *ap[], int index, int M_index);

int main(){
    Airplane *airplane[100];
    int air_index = 0;
    c_Airplane(airplane, air_index);
    air_index++;
    c_Airplane(airplane, air_index);
    air_index++;
    c_Airplane(airplane, air_index);
    air_index++;

    listAirplane(airplane, air_index);

    return 0;
}

void listAirplane(Airplane *ap[], int index){
    printf("��߽ð�\t������\t���\t����Ʈ\t�����¼�\n");
    for(int i = 0; i < index; i++){
        printf("%d ", i+1);
        readAirplane(ap[i]);
    }
    
}

void readAirplane(Airplane *ap){
    printf("%s\t\t%s\t%s\t%c\t%d\n", ap->departureTime, ap->department, ap->airPlaneName, ap->gate, ap->seatNum);
}

void c_Airplane(Airplane *ap[], int index){
    int sit;
    ap[index] = (Airplane *) malloc(sizeof(Airplane));
    printf("����� �� : ");
    fgets(ap[index]->airPlaneName, 100, stdin);
    ap[index]->airPlaneName[strlen(ap[index]->airPlaneName) - 1] = '\0';
    printf("������ : ");
    fgets(ap[index]->department, 100, stdin);
    ap[index]->department[strlen(ap[index]->department) - 1] = '\0';
    printf("��߽ð� : ");
    fgets(ap[index]->departureTime, 100, stdin);
    ap[index]->departureTime[strlen(ap[index]->departureTime) - 1] = '\0';
    printf("�¼� ���� (�� ����) : ");
    scanf(" %d", &sit);
    getchar();
    ap[index]->seatNum = 5*sit;
    for(int i = 0; i < sit; i++){
        for(int j = 0; j < 5; j++){
            ap[index]->seatName[i][j] = 'O'; // ��� ���ڸ��� �ʱ�ȭ.
        }
    }
    printf("ž�� ����Ʈ (ex. A,B,C ...) : ");
    scanf(" %c", &ap[index]->gate);
    getchar();

    //��߽ð��� �������� �������� ����
    while(index && strcmp(ap[index] -> departureTime, ap[index-1] -> departureTime) < 0){      //index�� 0�̰ų� ���� �迭�� ��߽ð��� �� ������ �ݺ��� Ż��
        Airplane *temp;
        temp = ap[index];
        ap[index] = ap[index-1];
        ap[index-1] = temp;
        index--;
    }

    printf("����Ǿ����ϴ�.\n");
}

void d_Airplane(Airplane *ap[], int index, int M_index){

    // �����͸� ��ĭ�� �մ��
    for(int i = 0; i < M_index; i++){
        ap[i] = ap[i+1];
    }
    //�ʱ�ȭ �� �޸� ����
    memset(ap[M_index],0,sizeof(Airplane));
    free(ap[M_index]);
}