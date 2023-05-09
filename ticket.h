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
    char airPlaneName[100];  // HAN122
    char gate;    // A,B...
    char department[100]; // 목적지
    char departureTime[10];  // 출발시간
    int seatNum;    // 좌석 수, 최대 좌석수는 180좌석, 입력받을때는 줄수로 입력받을 것.
    char seatName[26][5];  // isalpha() 사용
} Airplane;


int selectMenu();
// Create
int createUser(User *u);
int createTicket(Ticket *t, char *userid);

// Read
void listAirplaneTime(Airplane *ap, int count);    // 예매가능한 비행기표 목록 (user)
void listReservedTicket(Ticket *t, int count, char *userid);      // 내가 예매한 항공권 목록 (user)

// Update
// int updateAirplaneTime(Airplane *ap, char *userid);       //예매 비행기표 시간 변경 (user)
int updateTicket(Ticket *t, char *userid);// 예매 정보 변경 (user/admin)

// Delete
int deleteTicket(Ticket *t);// 예매 비행기표 삭제 (user)

// 데이터 파일 저장
// 회원 데이터
// 항공편 데이터

// 검색
// 목적지에 따른 비행기 목록 검색
