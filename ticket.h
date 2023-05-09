#include <stdio.h>
#include <string.h>

typedef struct{
    User *user; // 아니면 user typedef struct 포인터
    Airplane *airplane; // airplane typedef struct 포인터 
    int passengers;    // 탑승인원 수
    char seatNum[5];    // a1, a2, ...
} Ticket;

typedef struct{
    char userId[20];
    char pw[20];
    char name[20];
    int age;
} User;

// 비행기 고유 데이터
typedef struct{
    char airPlaneName[100];  // HAN 122
    char gate;    // A,B...
    char department[100]; // 목적지
    char departureTime[10];  // 출발시간
    int seatNum;    // 좌석 수, 최대 좌석수는 180좌석, 입력받을때는 줄수로 입력받을 것.
    char seatName[26][5];  // isalpha() 사용
} Airplane;


//Create


//Read

//Update

//Delete