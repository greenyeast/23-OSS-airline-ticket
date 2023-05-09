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
    int no;
    char airPlaneName[100];  // HAN122,
    char gate;    // A,B...
    char department[100]; // 목적지
    char departureTime[10];  // 출발시간
    int seatNum;    // 좌석 수, 최대 좌석수는 180좌석, 입력받을때는 줄수로 입력받을 것.
    char seatName[26][5];  // isalpha() 사용
} Airplane;

void readAirplane(Airplane *ap);
void c_Airplane(Airplane *ap[], int index);

int main(){
    Airplane *airplane[100];
    int air_index = 0;
    c_Airplane(airplane, air_index);
    readAirplane(airplane[air_index]);

    return 0;
}

void readAirplane(Airplane *ap){
    printf("%d\t%s\t%s\t%s\t%c\t%d\n",ap->no , ap->departureTime, ap->department, ap->airPlaneName, ap->gate, ap->seatNum);
}

void c_Airplane(Airplane *ap[], int index){
    int sit;
    ap[index] = (Airplane *) malloc(sizeof(Airplane));
    ap[index]->no = index+1;
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
    
    printf("저장되었습니다.\n");
}