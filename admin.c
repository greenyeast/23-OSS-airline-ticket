#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "admin.h"

int showAdminMenu(){
    int menu;
    printf("\n—------------ HanAir Ticket System —------------\n");
    printf("1. 항공편 조회\n");
    printf("2. 항공편 생성\n");
    printf("3. 항공권 정보 변경\n");
    printf("4. 항공편 삭제\n");
    printf("5. 항공편 파일 저장\n");
    printf("6. 항공편 일자별 목록으로 조회\n");
    printf("0. 종료\n");
    printf("—----------------------------------------------------------\n");
    printf("\n");
    printf("=> 원하는 메뉴는? ");
    scanf("%d", &menu);
    getchar();

    return menu;
}
void listAirplane(Airplane *ap[], int index){

    printf("번호\t출발일시\t\t출발지\t도착지\t편명\t게이트\t남은좌석/총 좌석\n");

    for(int i = 0; i < index; i++){
        printf("%d\t", i+1);
        readAirplane(ap[i]);
    }
    
}

void readAirplane(Airplane *ap){
    printf("%s\t%s\t%s\t%s\t%c\t%d/%d\n", ap->dateTime, ap->departure, ap->arrival, ap->airPlaneName, ap->gate, ap->remain_seat, ap->seatNum);
}

void c_Airplane(Airplane *ap[], int index){
    int seat;
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
    scanf(" %d", &seat);

    getchar();
    ap[index]->seatNum = ap[index]->remain_seat = seat;


    //출발시간을 기준으로 오름차순 정렬
    while(index && strcmp(ap[index] -> dateTime, ap[index-1] -> dateTime) < 0){      //index가 0이거나 이전 배열의 출발시간이 더 작으면 반복문 탈출
        Airplane *temp;
        temp = ap[index];
        ap[index] = ap[index-1];
        ap[index-1] = temp;
        index--;
    }

    printf("=> 항공편이 추가되었습니다.\n");
}

void u_Airplane(Airplane *ap[], int index){

    printf("변경할 항공기 명은? ");
    fgets(ap[index]->airPlaneName, 100, stdin);
    ap[index]->airPlaneName[strlen(ap[index]->airPlaneName) - 1] = '\0';

    printf("변경할 게이트는? : ");
    scanf(" %c", &ap[index]->gate);
    getchar();

    printf("=> 변경 내역이 업데이트 되었습니다.\n");
}

void d_Airplane(Airplane *ap[], int index, int M_index){

    // 데이터를 한칸씩 앞당김
    for(int i = index; i < M_index; i++){
        Airplane *temp;
        temp = ap[i];
        ap[i] = ap[i+1];
        ap[i+1] = temp;
    }

    //초기화 후 메모리 해제
    memset(ap[M_index],0,sizeof(Airplane));
    free(ap[M_index]);
    printf("=> 삭제되었습니다.\n");
}

void saveFile(Airplane *ap[], int index){
    FILE * file = fopen("airplane.txt", "w");
    if(file == NULL){
        printf("에러발생\n");
        return;
    }
    for(int i = 0; i < index; i++){
        //항공편 정보 저장 - 출발일시, 출발지, 도착지, 항공편, 게이트, 잔여좌석/총좌석 
        fprintf(file, "%s,%s,%s,%s,%c,%d,%d",
            ap[i]->dateTime,
            ap[i]->departure,
            ap[i]->arrival,
            ap[i]->airPlaneName,
            ap[i]->gate,
            ap[i]->remain_seat,
            ap[i]->seatNum
        );
        fprintf(file,"\n");
    }
    fclose(file);
    printf("저장되었습니다.\n");
}

int loadFile(Airplane *ap[]){
    FILE * file = fopen("airplane.txt", "r");
    char line[350];
    int index = 0;
    if(file == NULL){
        printf("\n=> 파일 없음\n");
        return 0;
    }
    while(fgets(line,sizeof(line),file)){
        int i = index;
        ap[i] = (Airplane *)malloc(sizeof(Airplane));
        sscanf(line," %[^,],%[^,],%[^,],%[^,],%c,%d,%d\n",
            ap[i]->dateTime,
            ap[i]->departure,
            ap[i]->arrival,
            ap[i]->airPlaneName,
            &ap[i]->gate,
            &ap[i]->remain_seat,
            &ap[i]->seatNum
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
    return index;
}

void searchDate(Airplane *ap[], int index, char str[20]){
    int no = 1;
    printf("번호\t출발일시\t\t출발지\t도착지\t편명\t게이트\t남은좌석/총 좌석\n");
    for(int i = 0; i < index; i++){
        if(strstr(ap[i]->dateTime, str)){   //같은 날인 경우만 출력
            printf("%d\t", no++);
            readAirplane(ap[i]);
        }
    }
}
void searchD_to_A(Airplane *ap[], int index, char d[100], char a[100]){
    int no = 1;
    printf("번호\t출발일시\t\t출발지\t도착지\t편명\t게이트\t남은좌석/총 좌석\n");
    for(int i = 0; i < index; i++){
        if(strstr(ap[i]->departure, d) && strstr(ap[i]->arrival, a)){   //출발지와 도착지가 같은 경우만 출력
            printf("%d\t", no++);
            readAirplane(ap[i]);
        }
    }
}
