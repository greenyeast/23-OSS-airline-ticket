#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    char userId[20];
    char pw[20];
    int session; //관리자인 경우 1, 이용자일 경우 0.
} User;

int checkID(char ID[], char pw[], int *session);    // 아이디,비밀번호 확인.
void new_member();                                  // 회원가입.

int main(){
    char ID[20];
    char pw[20];
    int session = 0;  
    // new_member();
    // strcpy(u->userId, "qkrwks01");
    // strcpy(u->pw, "12367");
    while(1){
        printf("ID : ");
        scanf("%s", ID);
        getchar();
        printf("PW : ");
        scanf("%s", pw);
        getchar();
        if(checkID(ID,pw,&session)) break;
    }

    if(session){
        printf("관리자 입니다.");
    }else{
        printf("이용자 입니다.");
    }
    return 0;
}

int checkID(char ID[], char pw[], int *admin){
    FILE * file = fopen("userList.txt", "r");
    char line[100];
    while(fgets(line,sizeof(line),file)){
        User *u= (User *)malloc(sizeof(User));
        sscanf(line, "%s %s %d\n", u->userId, u->pw, &u->session);
        if(!strcmp(ID,u->userId)){
            if(strcmp(pw,u->pw)){
                printf("비밀번호가 틀렸습니다.\n");
                return 0;
            }else{
                printf("로그인 성공\n");
                *admin = u->session;          //관리자인 경우 1, 유저의 경우 0
                return 1;
            }
        }
    }

    fclose(file);
    printf("일치하는 ID가 없습니다.\n");
    return 0;
}

void new_member(){
    User *u= (User *)malloc(sizeof(User));
    FILE * file = fopen("userList.txt", "a+");
    char line[100];
    while(1){
        int plag = 0;
        printf("새로운 ID를 입력하세요 (3글자 이상): ");
        fgets(u->userId, 20, stdin);
        u->userId[strlen(u->userId) - 1] = '\0';
        if(strlen(u->userId) < 3){
            printf("3글자 이상 입력해주세요.\n");
            continue;
        }

        while(fgets(line,sizeof(line),file)){
            User *check= (User *)malloc(sizeof(User));
            sscanf(line, "%s %s %d\n", check->userId, check->pw, &check->session);
            if(!strcmp(u->userId, check->userId)){
                plag = 1;
                break;
            }
        }
        if(plag){
            printf("동일한 ID가 존재합니다.\n");
            continue;
        }else{
            break;
        }
    }

    while(1){
        printf("pw를 입력하세요 (3글자 이상): ");
        fgets(u->pw, 20, stdin);
        u->pw[strlen(u->pw) - 1] = '\0';

        if(strlen(u->pw) < 3){
            printf("3글자 이상 입력해주세요.\n");
            continue;
        }else{
            break;
        }
    }

    u->session = 0;

    fprintf(file,"%s %s %d\n", u->userId, u->pw, u->session);
    printf("회원가입이 완료되었습니다.\n");
    fclose(file);
    return;
}