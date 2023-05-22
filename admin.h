#include <stdio.h>
#include <time.h>

#ifndef admin
#define admin
// 비행기 고유 데이터
typedef struct{
    int timetableIndex;         // 구분하기 위한 인덱스
    char airPlaneName[100];     // HAN122
    char gate;                  // A,B...
    char departure[100];        // 촐발지
    char arrival[100];          // 도착지
    char dateTime[20];          // 출발시간
    int seatNum;                // 좌석 수, 최대 좌석수는 180좌석, 입력받을때는 줄수로 입력받기
    int remain_seat;            //남은 좌석 수
} Airplane;


int showAdminMenu();                                                    // 관리자 첫화면 메뉴
void readAirplane(Airplane *ap);                                        // Read 항공편
void c_Airplane(Airplane *ap[], int index);                             // Create 항공편
void listAirplane(Airplane *ap[], int index);                           // 항공편 리스트 보여주는 함수
void d_Airplane(Airplane *ap[], int index, int M_index);                // Delete 항공편
void u_Airplane(Airplane *ap[], int index);                             // Update 항공편
void saveFile(Airplane *ap[], int index);                               // 항공편 파일 저장
int loadFile(Airplane *ap[]);                                           // 항공편 파일 로드
void searchDate(Airplane *ap[], int index, char str[20]);               // 일자로 검색
void searchD_to_A(Airplane *ap[], int index, char d[100], char a[100]); // 출발지, 도착지로 검색
#endif