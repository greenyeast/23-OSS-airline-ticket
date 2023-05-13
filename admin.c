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
    char departure[100]; // �͹���
    char arrival[100]; // ������
    char dateTime[20];  // ��߽ð�
    int seatNum;    // �¼� ��, �ִ� �¼����� 180�¼�, �Է¹������� �ټ��� �Է¹��� ��.
    int remain_seat; //���� �¼� ��.
    // char seatName[26][5];  // isalpha() ���
} Airplane;

void readAirplane(Airplane *ap);
void c_Airplane(Airplane *ap[], int index);
void listAirplane(Airplane *ap[], int index);
void d_Airplane(Airplane *ap[], int index, int M_index);
void saveFile(Airplane *ap[], int index);
int loadFile(Airplane *ap[]);

int main(){
    Airplane *airplane[100];
    int air_index = 0;
    // air_index = loadFile(airplane);

    // listAirplane(airplane, air_index);

    c_Airplane(airplane, air_index);
    air_index++;

    listAirplane(airplane, air_index);

    c_Airplane(airplane, air_index);
    air_index++;

    listAirplane(airplane, air_index);
    // saveFile(airplane, air_index);


    return 0;
}

void listAirplane(Airplane *ap[], int index){
    printf("��ȣ\t����Ͻ�\t�����\t������\t���\t����Ʈ\t�����¼�/�� �¼�\n");
    for(int i = 0; i < index; i++){
        printf("%d\t", i+1);
        readAirplane(ap[i]);
    }
    
}

void readAirplane(Airplane *ap){
    printf("%s\t\t%s\t%s\t%c\t%d/%d\n", ap->dateTime, ap->arrival, ap->airPlaneName, ap->gate, ap->remain_seat, ap->seatNum);
    // for(int i = 0; i < (ap->seatNum)/5; i++){
    //     for(int j = 0; j < 5; j++){
    //         printf("%c", ap->seatName[i][j]);
    //     }
    //     printf("\n");
    // }
}

void c_Airplane(Airplane *ap[], int index){
    int sit;
    ap[index] = (Airplane *) malloc(sizeof(Airplane));

    printf("����Ͻ� (ex.2023-05-13 17:30) : ");
    fgets(ap[index]->dateTime, 100, stdin);
    ap[index]->dateTime[strlen(ap[index]->dateTime) - 1] = '\0';

    printf("����� : ");
    fgets(ap[index]->departure, 100, stdin);
    ap[index]->departure[strlen(ap[index]->departure) - 1] = '\0';

    printf("������ : ");
    fgets(ap[index]->arrival, 100, stdin);
    ap[index]->arrival[strlen(ap[index]->arrival) - 1] = '\0';

    printf("�װ��� �� : ");
    fgets(ap[index]->airPlaneName, 100, stdin);
    ap[index]->airPlaneName[strlen(ap[index]->airPlaneName) - 1] = '\0';

    printf("ž�� ����Ʈ (ex. A,B,C ...) : ");
    scanf(" %c", &ap[index]->gate);
    getchar();

    printf("�ִ� ���� �¼��� : ");
    scanf(" %d", &sit);
    getchar();
    ap[index]->seatNum = ap[index]->remain_seat = sit;


    //��߽ð��� �������� �������� ����
    while(index && strcmp(ap[index] -> dateTime, ap[index-1] -> dateTime) < 0){      //index�� 0�̰ų� ���� �迭�� ��߽ð��� �� ������ �ݺ��� Ż��
        Airplane *temp;
        temp = ap[index];
        ap[index] = ap[index-1];
        ap[index-1] = temp;
        index--;
    }

    printf("�װ����� �߰��Ǿ����ϴ�.\n");
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

void saveFile(Airplane *ap[], int index){
    FILE * file = fopen("airplane.txt", "w");
    if(file == NULL){
        printf("�����߻�\n");
        return;
    }
    for(int i = 0; i < index; i++){
        //�װ��� ���� ���� - Date, Time, �����, ������, �װ���, ����Ʈ, �ܿ��¼�/���¼� 
        fprintf(file, "%s,%s,%s,%d,%c,",
            ap[i]->airPlaneName, 
            ap[i]->arrival, 
            ap[i]->dateTime,
            ap[i]->seatNum,
            ap[i]->gate
        );
        fprintf(file,"\n");
    }
    fclose(file);
    printf("����Ǿ����ϴ�.\n");
}

int loadFile(Airplane *ap[]){
    FILE * file = fopen("airplane.txt", "r");
    char line[350];
    char seat[150];
    int index = 0;
    if(file == NULL){
        printf("\n=> ���� ����\n");
        return 0;
    }
    while(fgets(line,sizeof(line),file)){
        int i = index;
        ap[i] = (Airplane *)malloc(sizeof(Airplane));
        sscanf(line," %[^,],%[^,],%[^,],%d,%c,%s\n",
                ap[i]->airPlaneName,
                ap[i]->arrival,
                ap[i]->dateTime,
                &ap[i]->seatNum,
                &ap[i]->gate,
                seat
        );

        //��߽ð��� �������� �������� ����
        while(i && strcmp(ap[i] -> dateTime, ap[i-1] -> dateTime) < 0){      //index�� 0�̰ų� ���� �迭�� ��߽ð��� �� ������ �ݺ��� Ż��
            Airplane *temp;
            temp = ap[i];
            ap[i] = ap[i-1];
            ap[i-1] = temp;
            i--;
        }
        index++;
    }


    fclose(file);
    printf("=> �ε� ����!\n");
    return index;
}
