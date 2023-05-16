#include <stdio.h>
#include <string.h>
#include "login.h"
#include "admin.h"

int main(){
    char ID[50];                                                // main에서 입력받을 ID
    char pw[50];                                                // main에서 입력받을 PW
    int session = 0;                                            // 사용자 == 1, 관리자 == 2
    Airplane *airplane[100];                                    // 항공기 정보를 저장할 포인터 배열
    int air_index = loadFile(airplane);                         // 저장된 항공기 정보 load & 현재 저장된 총 항공기 수 저장
    /********************로그인 과정**************************/
    while(1){
        session = showStartMenu();
        if(session == 1){
            printf("사용자 모드로 시작합니다.\n");
            break;
        }else if(session == 2){
            printf("관리자 모드로 시작합니다.\n");
            break;
        }else{
            printf("잘못 입력하셨습니다.\n");
        }
    }

    while(1){
        int loginMode = 0;
        if(session == 1){
            loginMode = showLoginMenu();
        }
        if(loginMode == 1){
            new_member();
        }else if(loginMode == 2 || session == 2){
            while(1){
                printf("ID : ");
                scanf("%s", ID);
                getchar();
                printf("PW : ");
                scanf("%s", pw);
                getchar();
                if(session == 2){
                    if(checkAdminID(ID,pw)) break;
                }else{
                    if(checkUserID(ID,pw)) break;
                }
                
            }
            break;
        }else{
            printf("잘못 입력하셨습니다.\n");
        }
    }
    
    /********************************관리자인 경우 (session == 2)********************************/
    if(session == 2){
        if(air_index){
            printf("=> 로딩성공\n");
        }else{
            printf("=> 정보가 없습니다.\n");
        }

        while(1){
            int num;
            int check;
            char str1[100], str2[100];
            
            switch (showAdminMenu())
            {
            case 0:
                printf("HanAir 관리자 서비스를 종료합니다.");
                return 0;

            case 1:
                if(!air_index){
                    printf("생성된 항공편이 존재하지 않습니다.\n");
                    break;
                }
                listAirplane(airplane, air_index);
                break;

            case 2:
                c_Airplane(airplane, air_index);
                air_index++;
                break;

            case 3:
                listAirplane(airplane, air_index);
                printf("\n");
                printf("변경할 번호는? ");
                scanf(" %d", &num);
                getchar();
                num--;
                u_Airplane(airplane,num);
                break;

            case 4:
                listAirplane(airplane, air_index);
                printf("\n");
                printf("삭제할 번호는 (취소 :0)? ");
                scanf(" %d", &num);
                getchar();
                if(!num){                           // num이 0이면 break
                    printf("취소되었습니다.\n");
                    break; 
                }                    
                num--;

                printf("정말로 삭제하시겠습니까 (삭제 :1)? ");
                scanf(" %d", &check);
                getchar();
                if(check != 1){                     //check가 1이 아니면 break
                    printf("취소되었습니다.\n");
                    break; 
                }              
                d_Airplane(airplane, num, air_index--);
                break;

            case 5:
                saveFile(airplane, air_index);
                break;

            case 6:
                printf("일자별 검색 1번, 출발도착지 검색 2번 ? ");
                scanf(" %d", &num);
                getchar();

                if(num == 1){
                    printf("검색할 날짜는? ");
                    fgets(str1, 100, stdin);
                    str1[strlen(str1) - 1] = '\0';

                    searchDate(airplane, air_index, str1);
                }else if(num == 2){
                    printf("검색할 출발지는? ");
                    fgets(str1, 100, stdin);
                    str1[strlen(str1) - 1] = '\0';

                    printf("검색할 도착지는? ");
                    fgets(str2, 100, stdin);
                    str2[strlen(str2) - 1] = '\0';

                    searchD_to_A(airplane, air_index, str1, str2);   
                }else{
                    printf("잘못된 입력입니다.\n");
                }

                break;
            
            default:
                break;
            }
        }
    }
    
    return 0;
}