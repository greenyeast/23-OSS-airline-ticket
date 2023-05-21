#include "admin.h"
#ifndef ticket
#define ticket
typedef struct{
    char userId[50];        // 예매하는 userID
    int airplaneIndex;      // 예매할 항공편 인덱스
    char seatType;      // 좌석 타입
} Ticket;


int selectTicketMenu();
int selectTicketDataNo(Ticket *t[], Airplane *a[],int index);
int loadTicketData(Ticket *t[], char *id);

// Create
//int createTicket(Ticket *t, char *userid);
int createTicket(Ticket *t, char *id);

// Read
//void listPossibleAirplane(Airplane *ap[]);  // 예매가능한 비행기표 목록 (user)
void listReservedTicket(Ticket *t[], Airplane *a[], int index);      // 내가 예매한 항공권 목록 (user)
void readReservedTicket(Ticket t, Airplane a);

// Update
// int updateAirplaneTime(Airplane *ap, char *userid);       //예매 비행기표 시간 변경 (user)
int updateTicket(Ticket *t);// 예매 정보 변경 (user/admin)

// Delete
int deleteTicket(Ticket *t);// 예매 비행기표 삭제 (user)

// 데이터 파일 저장
// 모든 사용자의 예매 내역 데이터
void saveAllUserTicketData(Ticket *t[], int index);

// 현재 사용자의 예매 내역 데이터
void saveUserTicketData(Ticket *t[], Airplane *a[], int index, char *id);
// 항공편 데이터

// 검색
// 목적지에 따른 비행기 목록 검색
//

#endif