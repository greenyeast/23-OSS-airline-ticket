#ifndef logIn
#define logIn
typedef struct{
    char userId[50];
    char pw[50];
    char name[20];
    int age;
} User;

int checkAdminID(char ID[], char pw[]);     // 관리자 아이디,비밀번호 확인
int checkUserID(char ID[], char pw[]);      // 유저
void new_member();                          // 회원가입
int showStartMenu();                        // 사용자, 관리자 시작 화면 
int showLoginMenu();                        // 로그인 화면 
#endif
