#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *skipspace(char *p);
double getnum(char **pp, int priority);

typedef struct{
        char strings[200];
        char name[16];
}function;

function functionarray[20];

int main(int argc, char *argv[])
{
    int fp=0;
    char input[200];
    char* reader=input;
    for(;;reader=input){
            scanf("%230s",input);
            if(strcmp(input,"addfunc")==0){
                                           reader+=7;
                                           reader=skipspace(reader);
                                           if(fp<19){
                                                    strncpy(functionarray[fp].name,reader,15);
                                                    reader+=strlen(reader);
                                                    strncpy(functionarray[fp].strings,reader,199);
                                                    fp++;
                                                    reader=input;
                                           }else {
                                                 printf("함수가 너무 많음\n");
                                                 reader=input;
                                           }
            }else if (strcmp(input,"calc")==0){
                  reader+=4;
                  reader=skipspace(reader);
                  double x= strtod(reader,0);
                  for(int i=0;i<20;i++){
                          if(strcmp(functionarray[i].name,reader)==0){
                                                           printf("%s(%lf)= %lf\n",functionarray[i].name,x,getnum((char**)&(functionarray[i].strings),9));
                                                           goto cont;
                          }
                  }
                  printf("함수 없음\n");
                  cont:
                       reader=input;
                       continue;
            }
    }
                                           
                                           
                                           
    system("PAUSE");
    return EXIT_SUCCESS;
}
