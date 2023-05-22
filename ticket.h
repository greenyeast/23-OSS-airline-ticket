#include "admin.h"

#ifndef ticket
#define ticket
typedef struct{
    char userId[50];        // 예매하는 userID
    int airplaneIndex;      // 예매할 항공편 인덱스
    char seatType;          // 좌석 타입
} Ticket;

int selectTicketMenu();                                             // 사용자 예매 메뉴 보여주는 함수
int selectTicketDataNo(Ticket *t[], Airplane *a[],int index);       // 예매 내역 데이터 인덱스 선택하는 함수
int loadTicketData(Ticket *t[], char *id);                          // 예매 내역 로드하는 함수

int createTicket( Airplane *a[], Ticket *t, char *id);                              // 항공편 예매 생성
void readReservedTicket(Ticket t, Airplane a);                      // 예매한 티켓 데이터 읽기
int updateTicket(Ticket *t);                                        // 예매 정보 변경 
int deleteTicket(Ticket *t[]);                                      // 예매 비행기표 삭제 

void listReservedTicket(Ticket *t[], Airplane *a[], int index);     // 사용자가 예매한 항공권 목록 
void saveAllUserTicketData(Ticket *t[], int index);                 // 모든 사용자의 예매 내역 데이터 저장
void saveUserTicketData(Ticket *t[], int index, char *id);          // 현재 사용자의 예매 내역 데이터 저장
#endif
