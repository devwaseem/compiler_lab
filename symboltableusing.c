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
char set[100][100];
int setp;
int setlen=0;


void clearString(){
    for(int i=0;i<strin;i++) str[i] = '\0';
    strin=0;
}

void addToStr(char c){
    str[strin++] = c;
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
    int flag=0;
    if(in == NULL){
        printf("File not found");
        exit(0);
    }
    while((ch=fgetc(in))!=EOF){
            int type = idType(ch);
            if(type == 1)
                continue;
            else if(type == 2)
                continue;
            else if(type == 3){
                //add to set
                for(int i=0;i<setlen;i++){
                    if(strcmp(set[i],str)==0){
                        flag=1;
                    }
                }
                if(flag==0){
                    strcpy(set[setlen++],str);
                }else{
                    flag=0;
                }
                
            }
               
        
    }
    for(int i=0;i<setlen;i++){
        printf("%s\t\t0x%d\t\t%d\n",set[i],rand()%100,rand()%100);
    }
    return 0;
}
