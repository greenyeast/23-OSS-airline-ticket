#include <stdlib.h>     // malloc
#include <stdio.h>
#include <string.h>
#include "ticket.h"
#include "logIn.h"
#include "admin.h"

int selectTicketMenu(){
    int menu;
    printf("\n—------------ HanAir Ticket System —------------\n");
    printf("  1. 항공권 예매 내역 조회\n");
    printf("  2. 항공권 예매\n");
    printf("  3. 항공권 변경\n");
    printf("  4. 항공권 예매 삭제\n");
    printf("  5. 항공권 예매 내역 저장\n");
    printf("  6. 예매 내역 도착지로 찾기\n");
    printf("  0. 종료\n");
    printf("—---------------------------------------------------\n");
    printf("=> 원하는 메뉴는? ");
    scanf("%d", &menu);

    return menu;
}

int selectTicketDataNo(Ticket *t[], Airplane *a[],int index){
    int no;
    listReservedTicket(t, a, index);
    printf("변경할 번호는 (취소: 0)? ");
    scanf("%d", &no);
    return no;
}


// Create
int createTicket(Airplane *a[], Ticket *t, char *id){

    strcpy(t->userId, id);          // 비행기표 예매할 아이디 저장
    printf("\n예매할 항공권 번호는? ");
    scanf("%d", &t->airplaneIndex);

    printf("좌석 타입은 (F:FirstClass / B:Business / E:Economy)? ");
    scanf(" %c", &t->seatType );

    a[t->airplaneIndex]->remain_seat--;
    printf("=> 예매내역이 추가되었습니다. \n");
    return 1;
}

void readReservedTicket(Ticket t, Airplane a){
    printf("%s\t%s\t%s\t%c\n", a.dateTime, a.departure, a.arrival, t.seatType);
}

// Read
void listReservedTicket(Ticket *t[], Airplane *a[], int index){      // 내가 예매한 항공권 목록 (user)
    printf("\nNo   출발일시\t\t출발지\t도착지\t좌석유형\n");
    for(int i=0; i<index; i++){
        int airplaneIndex = t[i]->airplaneIndex;

        if(t[i] == NULL) continue;
        printf("%2d ", i+1);
        readReservedTicket(*t[i], *a[airplaneIndex-1]);
    }
    printf("\n");
}
// Update
// int updateAirplaneTime(Airplane *ap, char *userid);       //예매 비행기표 시간 변경 (user)
int updateTicket(Ticket *t){          // 예매 정보 변경 (user/admin)
    printf("변경할 비행편 번호는? ");
    scanf("%d", &t->airplaneIndex);

    printf("변경할 좌석 타입은 (F:FirstClass / B:Business / E:Economy)? ");
    scanf(" %c", &t->seatType);
    
    return 1;
}
// Delete
int deleteTicket(Ticket *t[]){      // 예매 비행기표 삭제 (user)
    int deleteok;
    int deleteNo;
    printf("삭제할 번호는 (취소 :0)? ");
    scanf("%d", &deleteNo);
    if(deleteNo == 0) return 0;

    printf("정말로 삭제하시겠습니까 (삭제 :1)? ");
    scanf("%d", &deleteok);
    if(deleteok == 1){
        if(t[deleteNo-1]) free(t[deleteNo-1]);
        t[deleteNo-1] = NULL;
        printf("=> 삭제되었습니다.\n");
    }else{
        printf("=> 삭제처리가 완료되지 않았습니다.\n");
    }
    return 1;

}
// 데이터 파일 저장
// 모든 사용자의 예매 내역 데이터
// TODO 이후에 내용 추가하는 방향으로 
void saveAllUserTicketData(Ticket *t[], int index)
{
    FILE *fp;
    fp = fopen("ticketList.txt", "w");
    
    for(int i=0; i<index; i++){
        if(t[i] == NULL) continue;
        fprintf(fp, "%s %d %c\n", t[i]->userId, t[i]->airplaneIndex, t[i]->seatType);
    }
    fclose(fp);
    printf("전체 예매 내역에 저장되었습니다. (ticketList.txt)\n");
}

// 현재 사용자의 예매 내역 데이터
// TODO 상세 비행기편 데이터 index와 비교해서 저장
void saveUserTicketData(Ticket *t[], int index, char *id)
{
    FILE *fp;
    char fileName[50];
    sprintf(fileName, "ticket_%s.txt", id);     // 문자열 형식을 지정하여 저장
    fp = fopen(fileName, "w");

    for (int i=0; i<index; i++){
        if(t[i] == NULL) continue;
        fprintf(fp, "%d %c\n", t[i]->airplaneIndex, t[i]->seatType);
    }
    fclose(fp);
    printf("사용자 예매 내역에 저장되었습니다. (ticket_userID.txt)\n");
}

int loadTicketData(Ticket *t[], char *id){
    int count = 0;   
    int i = 0;

    FILE *fp;
    char fileName[50];
    sprintf(fileName, "ticket_%s.txt", id);

    fp = fopen(fileName, "rt");
    if (fp == NULL) {
        printf("=> 파일 없음\n");
        return 0;
    }

    for (i=0; i<100; i++){
        t[i] = (Ticket *)malloc(sizeof(Ticket));
        
        fscanf(fp, "%d", &t[i]->airplaneIndex);
        //printf("%d> airplaneIndex: %d\n", i, t[i]->airplaneIndex);
        if(feof(fp)) break;
        fscanf(fp, " %c", &t[i]->seatType);
        //printf("type: %c\n", t[i]->seatType);
        count++;
    }
    fclose(fp);
    printf("=> 로딩 성공!\n");
    return count;
}

// 검색
// 목적지에 따른 비행기 목록 검색
//