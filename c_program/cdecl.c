#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


#define MAXTOKENS 100
#define MAXTOKENLEN 64

enum type_tag {IDENTIFIER, QUALIFIER, TYPE};

struct token{
    char type;
    char string[MAXTOKENLEN];
};

int top = -1;

struct token stack[MAXTOKENS];//在第一个标识符前保存所有的标记
struct token this;//保存刚读入的标记

#define pop stack[top--]
#define push(s) stack[++top] = s

enum type_tag
classify_string(void){//推断标识符的类型
    char *s = this.string;
    if(!strcmp(s, "const")){
        strcpy(s, "read-only");
        return QUALIFIER;
    }
    if(!strcmp(s, "volatile")) return QUALIFIER;
    if(!strcmp(s, "void")) return TYPE;
    if(!strcmp(s, "char")) return TYPE;
    if(!strcmp(s, "signed")) return TYPE;
    if(!strcmp(s, "unsigned")) return TYPE;
    if(!strcmp(s, "short")) return TYPE;
    if(!strcmp(s, "int")) return TYPE;
    if(!strcmp(s, "long")) return TYPE;
    if(!strcmp(s, "float")) return TYPE;
    if(!strcmp(s, "double")) return TYPE;
    if(!strcmp(s, "struct")) return TYPE;
    if(!strcmp(s, "union")) return TYPE;
    if(!strcmp(s, "enum")) return TYPE;

    return IDENTIFIER;
}


void
gettoken(void){//读取下一个标识到 this
    char *p = this.string;//存入位置

    while((*p = getchar()) == ' ');//略过所有空白

    if(isalnum(*p)){
        while(isalnum(*++p = getchar()));
        ungetc(*p, stdin);
        *p = '\0';
        this.type = classify_string();
        return;
    }

    if(*p == '*'){
        strcpy(this.string, "pointer to");
        this.type = '*';
        return ;
    }

    this.string[1] = '\0';
    this.type = *p;
    return;
}

void
read_to_first_identifer(){
    gettoken();
    while(this.type != IDENTIFIER){
        push(this);//仅在找到标识符前,需要入栈
        gettoken();
    }
    printf("%s is ", this.string);
    gettoken();
}

void
deal_with_arrays(){
    while(this.type == '['){//有可能存在多维数组,需要循环
        printf("array ");
        gettoken();
        if(isdigit(this.string[0])){//如果有长度声明
            printf("0..%d ", atoi(this.string) - 1);
            gettoken(); // 读取']'
        }
        gettoken();
        printf("of ");
    }
}

void
deal_with_function_args(){
    while(this.type != ')')
        gettoken();
    gettoken();//找到右括号 略过了对参数声明的处理
    printf("function returning ");
}

void
deal_with_pointers(){
    while(stack[top].type == '*'){//有可能存在多级指针,需要循环
        printf("%s ", pop.string);
    }
}

void
deal_with_declarator(){
    switch(this.type){//标识符右侧 的 数组 或 函数 声明 优先解释
        case '[': deal_with_arrays(); break;
        case '(': deal_with_function_args(); break;
    }

    deal_with_pointers();// 再解释前缀 *

    while(top >= 0){
        if(stack[top].type == '('){
            pop;//出栈左括号
            gettoken(); //多找一个token
            deal_with_declarator();// 再次进入右侧 解释
        }else{
            printf("%s ", pop.string);
        }
    }
}




int
main(){
    read_to_first_identifer();//第一步找到标识符
    deal_with_declarator();
    printf("\n");
    return 0;
}

// int*(*foo[10])()
