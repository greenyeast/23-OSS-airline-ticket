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
    char departure[100]; // 촐발지
    char arrival[100]; // 도착지
    char dateTime[20];  // 출발시간
    int seatNum;    // 좌석 수, 최대 좌석수는 180좌석, 입력받을때는 줄수로 입력받을 것.
    int remain_seat; //남은 좌석 수.
    // char seatName[26][5];  // isalpha() 사용
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
    printf("번호\t출발일시\t출발지\t도착지\t편명\t게이트\t남은좌석/총 좌석\n");
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

    printf("출발일시 (ex.2023-05-13 17:30) : ");
    fgets(ap[index]->dateTime, 100, stdin);
    ap[index]->dateTime[strlen(ap[index]->dateTime) - 1] = '\0';

    printf("출발지 : ");
    fgets(ap[index]->departure, 100, stdin);
    ap[index]->departure[strlen(ap[index]->departure) - 1] = '\0';

    printf("도착지 : ");
    fgets(ap[index]->arrival, 100, stdin);
    ap[index]->arrival[strlen(ap[index]->arrival) - 1] = '\0';

    printf("항공기 명 : ");
    fgets(ap[index]->airPlaneName, 100, stdin);
    ap[index]->airPlaneName[strlen(ap[index]->airPlaneName) - 1] = '\0';

    printf("탑승 게이트 (ex. A,B,C ...) : ");
    scanf(" %c", &ap[index]->gate);
    getchar();

    printf("최대 수용 좌석수 : ");
    scanf(" %d", &sit);
    getchar();
    ap[index]->seatNum = ap[index]->remain_seat = sit;


    //출발시간을 기준으로 오름차순 정렬
    while(index && strcmp(ap[index] -> dateTime, ap[index-1] -> dateTime) < 0){      //index가 0이거나 이전 배열의 출발시간이 더 작으면 반복문 탈출
        Airplane *temp;
        temp = ap[index];
        ap[index] = ap[index-1];
        ap[index-1] = temp;
        index--;
    }

    printf("항공편이 추가되었습니다.\n");
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
        //항공편 정보 저장 - Date, Time, 출발지, 도착지, 항공편, 게이트, 잔여좌석/총좌석 
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
                ap[i]->arrival,
                ap[i]->dateTime,
                &ap[i]->seatNum,
                &ap[i]->gate,
                seat
        );

        //출발시간을 기준으로 오름차순 정렬
        while(i && strcmp(ap[i] -> dateTime, ap[i-1] -> dateTime) < 0){      //index가 0이거나 이전 배열의 출발시간이 더 작으면 반복문 탈출
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
