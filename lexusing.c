#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

char keys[32][10]={"auto","break","case","char","const","continue","default",
"do","double","else","enum","extern","float","for","goto",
"if","int","long","register","return","short","signed",
"sizeof","static","struct","switch","typedef","union",
"unsigned","void","volatile","while"};

char functions[7][10]={"main","printf","scanf","getch","clrscr","gets","puts"};

char ch,str[25];
int strin=0;
FILE *in;

void clearString(){
    for(int i=0;i<strin;i++) str[i] = '\0';
    strin=0;
}

void addToStr(char c){
    str[strin++] = c;
}

int isAssignmentOperator(char op){
    char oper='=';
    if(oper == op){
        return 1;
    }
    return 0;
}

int isOperator(char op){
    char oper[]="+-*/";
    for(int i=0;i<strlen(oper);i++){
        if(oper[i] == op){
            return 1;
        }
    }
    return 0;
}

int isSpecialOperator(char op){
    char splchar[]="!@$%^&?";
    for(int i=0;i<strlen(splchar);i++){
        if(splchar[i] == op){
            return 1;
        }
    }
    return 0;
}

int isHeader(char ch){
    int limit = 50;
    clearString();
    if(ch == '#'){
        addToStr(ch);
        while(limit-->0){
            ch = fgetc(in);
            addToStr(ch);
            if(ch == '>'){
                return 1;   
            }
        }
        return 0;
    }
    return 0;
}

int isDelimiter(char c){
    char delim[15]=" \t\n,;(){}[]#\"<>";
    for(int i=0;i<strlen(delim);i++){
        if(delim[i] == c){
            return 1;
        }
    }
    return 0;
}

int isConstant(char c){
    clearString();
    if(isnumber(c)){
        while(isnumber(c)){
            addToStr(c);
            c = fgetc(in);
        }
        return 1;
    }
    return 0;
}

int isToken(char ch){
    int limit = 100;
    clearString();
    if(ch == '"'){
        addToStr(ch);
        while(limit-->0){
            ch = fgetc(in);
            addToStr(ch);
            if(ch == '"'){
                return 1;   
            }
        }
        return 0;
    }
    return 0;
}


int idType(char c){
    clearString();
    if(isalpha(c)){
        while(isalpha(c) && !isDelimiter(ch)){
            addToStr(c);
            c = fgetc(in);
        }
        for(int i=0;i<32;i++)
            if(strcmp(keys[i],str)==0) return 1;    
        for(int i=0;i<7;i++)
            if(strcmp(functions[i],str)==0) return 2;    
        return 3;
    }
    return 0;
}

int main(){
    in = fopen("prg.txt","r");
    if(in == NULL){
        printf("File not found");
        exit(0);
    }
    while((ch=fgetc(in))!=EOF){
        if(isOperator(ch)){
            printf("%c is operator\n",ch);
        }else if(isAssignmentOperator(ch)){
            printf("%c is Assignment Operator\n",ch);
        }else if(isSpecialOperator(ch)){
            printf("%c is Special Operator\n",ch);
        }else if(isHeader(ch)){
            printf("%s is a Header\n",str);
        }else if(isConstant(ch)){
            printf("%s is a Constant\n",str);
        }else if(isToken(ch)){
            printf("%s is a Token\n",str);
        }else if(isDelimiter(ch)){
            clearString();
        }else{
            int type = idType(ch);
            if(type == 1)
                printf("%s is a Keyword\n",str);
            else if(type == 2)
                printf("%s is a Function\n",str);
            else if(type == 3)
                printf("%s is a Identifier\n",str);
        
        }
    }
    return 0;
}
