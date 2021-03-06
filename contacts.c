#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define MAX 256
#define fname "contacts.txt"

FILE *s;
struct Contacts{ char name[50], phone[20]; };
struct Contacts x;

void Add(){
    s = fopen(fname, "a+");
    printf("Enter the name: ");
    scanf("%s", x.name);
    printf("Enter the number: ");
    scanf("%s", x.phone);
    //Making first char in name Upper
    x.name[0] >= 97? x.name[0] -= 32 : x.name[0];
    fprintf(s, "Name: %s\t\t Phone: %s\n",x.name, x.phone);
}

void Show(){
    char sh;
    s = fopen(fname, "r");
    while( fscanf(s,"%c", &sh) != EOF )
        printf("%c", sh);
}

void Remove(){

    s = fopen(fname, "r");
    FILE *w = fopen("new.txt", "w");
    if(s == NULL){
        printf("There is no contacts");
    }
    char str[MAX], ch;
    int line, po = 0;
    printf("Enter the line you want to remove: ");
    scanf("%d", &line);
    --line;
    //copy original file to new file and remove the line
    while(!feof(s)){
        strcpy(str, "\0");
        fgets(str, MAX, s);
        if(po != line)
            fprintf(w, "%s", str);
        po++;
    }

    fclose(s);
    fclose(w);
    remove("contacts.txt");
    rename("new.txt", "contacts.txt");

}

int Search(){
    s = fopen(fname, "r");
    char name[MAX], cmp[MAX], line[MAX];
    printf("Enter the name: ");
    scanf("%s", name);
    //to make first char upper
    if(name[0] >= 97)
        name[0] -= 32;
    while( !feof(s) ){
        strcpy(line, "\0");
        fscanf(s, "%s", cmp);
        if( strcmp(name, cmp) == 0 ){
            fgets(line, MAX, s);
            printf("\n%s %s", cmp, line);
            return 0;
        }
        
    }
    printf("\nNot found\n");
}

int main(){
    while( 1 ){
        int req;
        printf("\nTo add a new name press 1\n"
               "To show contacts press 2\n"
               "To remove name press 3\n"
               "To search for a name press 4\n"
               "To Exit press 0 \n");
        scanf("%d", &req);

        req == 0? exit(0) : req == 1? Add() : req == 2? Show() : req == 3? Remove() : req == 4? Search(): printf("\n\nWorng input");
    }

}