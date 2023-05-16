#include <stdio.h>
#include <time.h>
// #include "ticket.h"

// 비행기 고유 데이터
typedef struct{
    char airPlaneName[100];  // HAN122,
    char gate;    // A,B...
    char departure[100]; // 촐발지
    char arrival[100]; // 도착지
    char dateTime[20];  // 출발시간
    int seatNum;    // 좌석 수, 최대 좌석수는 180좌석, 입력받을때는 줄수로 입력받을 것.
    int remain_seat; //남은 좌석 수.
} Airplane;

int showAdminMenu();
void readAirplane(Airplane *ap);
void c_Airplane(Airplane *ap[], int index);
void listAirplane(Airplane *ap[], int index);
void d_Airplane(Airplane *ap[], int index, int M_index);
void u_Airplane(Airplane *ap[], int index);
void saveFile(Airplane *ap[], int index);
int loadFile(Airplane *ap[]);
void searchDate(Airplane *ap[], int index, char str[20]);
void searchD_to_A(Airplane *ap[], int index, char d[100], char a[100]);