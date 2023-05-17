#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "logIn.h"

int showLoginMenu(){
    int menu;
    printf("\n***************HanAir Ticket System ***************\n");
    printf("1. HanAir를 처음 사용하십니까? 회원가입\n");
    printf("2. HanAir를 사용한 적이 있나요? 로그인\n");
    printf("********************************************************\n");
    printf("\n");
    printf("=> 원하는 메뉴는? ");

    scanf(" %d", &menu);
    getchar();
    return menu;
}
int showStartMenu(){
    int menu;
    printf("\n***************HanAir Ticket System ***************\n");
    printf("1. 사용자\n");
    printf("2. 관리자\n");
    printf("********************************************************\n");
    printf("\n");
    printf("=> 원하는 메뉴는? ");

    scanf(" %d", &menu);
    getchar();
    return menu;
}

int checkUserID(char ID[], char pw[]){
    FILE * file = fopen("userList.txt", "r");
    char line[100];
    while(fgets(line,sizeof(line),file)){
        User *u= (User *)malloc(sizeof(User));
        sscanf(line, "%s %d %s %s\n", u->name, &u->age, u->userId, u->pw);
        if(!strcmp(ID,u->userId)){
            if(strcmp(pw,u->pw)){
                printf("비밀번호가 틀렸습니다.\n");
                return 0;
            }else{
                printf("로그인 성공\n");
                return 1;
            }
        }
    }

    fclose(file);
    printf("일치하는 ID가 없습니다.\n");
    return 0;
}

int checkAdminID(char ID[], char pw[]){
    FILE * file = fopen("adminList.txt", "r");
    char line[100];
    while(fgets(line,sizeof(line),file)){
        User *u= (User *)malloc(sizeof(User));
        sscanf(line, "%s %s\n", u->userId, u->pw);
        if(!strcmp(ID,u->userId)){
            if(strcmp(pw,u->pw)){
                printf("비밀번호가 틀렸습니다.\n");
                return 0;
            }else{
                printf("로그인 성공\n");
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

    printf("\n*************** HanAir Ticket System ***************\n");
    printf("이름은? ");
    fgets(u->name, 20, stdin);
    u->name[strlen(u->name) - 1] = '\0';
    
    printf("나이는? ");
    scanf("%d", &u->age);
    getchar();

    while(1){
        int plag = 0;
        printf("새로운 ID를 입력하세요 (3글자 이상): ");
        fgets(u->userId, 50, stdin);
        u->userId[strlen(u->userId) - 1] = '\0';
        if(strlen(u->userId) < 3){
            printf("3글자 이상 입력해주세요.\n");
            continue;
        }

        while(fgets(line,sizeof(line),file)){
            User *check= (User *)malloc(sizeof(User));
            sscanf(line, "%s %d %s %s\n", check->name, &check->age, check->userId, check->pw);
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
        fgets(u->pw, 50, stdin);
        u->pw[strlen(u->pw) - 1] = '\0';

        if(strlen(u->pw) < 3){
            printf("3글자 이상 입력해주세요.\n");
            continue;
        }else{
            break;
        }
    }

    fprintf(file,"%s %d %s %s\n", u->name, u->age, u->userId, u->pw);
    printf("********************************************************\n");
    printf("=> 사용자 계정이 생성되었습니다. 로그인해주세요.\n");
    fclose(file);
    return;
}