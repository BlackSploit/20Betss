#include <stdio.h>
#include <ctype.h>
#include <string.h>

int isKeyword(char* buffer){
    const char* Keyword[]={"int","float","return","if","while"};
    int n= sizeof(Keyword)/sizeof(Keyword[0]);

    for(int i=0;i<n;i++){
        if(strcmp(buffer,Keyword[i])==0)
            return 1;
    }
    return 0;
}

int main(){
    char input[100],buffer[20];
    int j=0;

    printf("Enter a string");
    fgets(input,sizeof(input),stdin);

    for(int i=0;input[i]!='\0';i++){
        if(isalnum(input[i]))
            buffer[j++]=input[i];
        else if((input[i]==' ' || input[i]=='\n')&& j!=0){
            buffer[j]='\0';
            j=0;
            printf("%s : %s\n",isKeyword(buffer)?"Keyword" : (isdigit(buffer[0])? "Number" : "Identifier"),buffer);
        }
        else if(strchr("+*/=<>",input[i]))
            printf("Operator : %c \n",input[i]);
    }
}