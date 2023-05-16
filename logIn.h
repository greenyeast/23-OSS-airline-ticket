typedef struct{
    char name[20];
    int age;
    char userId[50];
    char pw[50];
} User;

int checkAdminID(char ID[], char pw[]);     // 관리자 아이디,비밀번호 확인.
int checkUserID(char ID[], char pw[]);      // 유저
void new_member();                                  // 회원가입.
int showStartMenu();
int showLoginMenu();