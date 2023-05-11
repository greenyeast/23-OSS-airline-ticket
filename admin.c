#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// #include "admin.h"

// 항공편 생성
// 항공편 정보 변경
// 항공편 삭제

// typedef struct{
//     User *user; // 아니면 user typedef struct 포인터
//     Airplane *airplane; // airplane typedef struct 포인터 
//     int passengers;    // 탑승인원 수
//     char seatNum[5];    // a1, a2, ...
// } Ticket;

// typedef struct{
//     char userId[20];
//     char pw[20];
//     char name[20];
//     int age;
// } User;

// 비행기 고유 데이터
typedef struct{
    char airPlaneName[100];  // HAN122,
    char gate;    // A,B...
    char department[100]; // 목적지
    char departureTime[10];  // 출발시간
    int seatNum;    // 좌석 수, 최대 좌석수는 180좌석, 입력받을때는 줄수로 입력받을 것.
    char seatName[26][5];  // isalpha() 사용
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
    air_index = loadFile(airplane);

    listAirplane(airplane, air_index);

    c_Airplane(airplane, air_index);
    air_index++;
    c_Airplane(airplane, air_index);
    air_index++;
    c_Airplane(airplane, air_index);
    air_index++;

    listAirplane(airplane, air_index);
    saveFile(airplane, air_index);


    return 0;
}

void listAirplane(Airplane *ap[], int index){
    printf("번호\t출발시간\t목적지\t편명\t게이트\t남은좌석\n");
    for(int i = 0; i < index; i++){
        printf("%d\t", i+1);
        readAirplane(ap[i]);
    }
    
}

void readAirplane(Airplane *ap){
    printf("%s\t\t%s\t%s\t%c\t%d\n", ap->departureTime, ap->department, ap->airPlaneName, ap->gate, ap->seatNum);
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
    printf("비행기 명 : ");
    fgets(ap[index]->airPlaneName, 100, stdin);
    ap[index]->airPlaneName[strlen(ap[index]->airPlaneName) - 1] = '\0';
    printf("목적지 : ");
    fgets(ap[index]->department, 100, stdin);
    ap[index]->department[strlen(ap[index]->department) - 1] = '\0';
    printf("출발시간 : ");
    fgets(ap[index]->departureTime, 100, stdin);
    ap[index]->departureTime[strlen(ap[index]->departureTime) - 1] = '\0';
    printf("좌석 갯수 (줄 갯수) : ");
    scanf(" %d", &sit);
    getchar();
    ap[index]->seatNum = 5*sit;
    for(int i = 0; i < sit; i++){
        for(int j = 0; j < 5; j++){
            ap[index]->seatName[i][j] = 'O'; // 모두 빈자리로 초기화.
        }
    }
    printf("탑승 게이트 (ex. A,B,C ...) : ");
    scanf(" %c", &ap[index]->gate);
    getchar();

    //출발시간을 기준으로 오름차순 정렬
    while(index && strcmp(ap[index] -> departureTime, ap[index-1] -> departureTime) < 0){      //index가 0이거나 이전 배열의 출발시간이 더 작으면 반복문 탈출
        Airplane *temp;
        temp = ap[index];
        ap[index] = ap[index-1];
        ap[index-1] = temp;
        index--;
    }

    printf("저장되었습니다.\n");
}

void d_Airplane(Airplane *ap[], int index, int M_index){

    // 데이터를 한칸씩 앞당김
    for(int i = 0; i < M_index; i++){
        ap[i] = ap[i+1];
    }
    //초기화 후 메모리 해제
    memset(ap[M_index],0,sizeof(Airplane));
    free(ap[M_index]);
}

void saveFile(Airplane *ap[], int index){
    FILE * file = fopen("airplane.txt", "w");
    if(file == NULL){
        printf("에러발생\n");
        return;
    }
    for(int i = 0; i < index; i++){
        //항공편 정보 저장
        fprintf(file, "%s,%s,%s,%d,%c,",
            ap[i]->airPlaneName, 
            ap[i]->department, 
            ap[i]->departureTime,
            ap[i]->seatNum,
            ap[i]->gate
        );

        //예약된 좌석 저장
        for(int j = 0; j < (ap[i]->seatNum)/5; j++){
            for(int k = 0; k < 5; k++){
                fprintf(file, "%c", ap[i]->seatName[j][k]);
            }
        }
        fprintf(file,"\n");
    }
    fclose(file);
    printf("저장되었습니다.\n");
}

int loadFile(Airplane *ap[]){
    FILE * file = fopen("airplane.txt", "r");
    char line[350];
    char seat[150];
    int index = 0;
    if(file == NULL){
        printf("\n=> 파일 없음\n");
        return 0;
    }
    while(fgets(line,sizeof(line),file)){
        int i = index;
        ap[i] = (Airplane *)malloc(sizeof(Airplane));
        sscanf(line," %[^,],%[^,],%[^,],%d,%c,%s\n",
                ap[i]->airPlaneName,
                ap[i]->department,
                ap[i]->departureTime,
                &ap[i]->seatNum,
                &ap[i]->gate,
                seat
        );

        for(int j = 0; j < (ap[i]->seatNum)/5; j++){
            for(int k = 0; k < 5; k++){
                sscanf(seat, "%c", &ap[i]->seatName[j][k]);
            }
        }

        //출발시간을 기준으로 오름차순 정렬
        while(i && strcmp(ap[i] -> departureTime, ap[i-1] -> departureTime) < 0){      //index가 0이거나 이전 배열의 출발시간이 더 작으면 반복문 탈출
            Airplane *temp;
            temp = ap[i];
            ap[i] = ap[i-1];
            ap[i-1] = temp;
            i--;
        }
        index++;
    }


    fclose(file);
    printf("=> 로딩 성공!\n");
    return index;
}
