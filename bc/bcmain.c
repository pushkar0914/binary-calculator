#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<limits.h>
#include"bc.h"

int main(){
char a;
//command line argument not used as its displaying synatx err for ( and )
 FILE*p = fopen ("input.txt","w");
if(!p)return 0 ;
scanf("%c",&a);
while(a!='\n'){
    fprintf(p,"%c",a);
    scanf("%c",&a);
}
fclose(p);


  queue inq;
  initq(&inq);
  intoq("input.txt",&inq);
  //display(inq);
  queue postq ;
  initq (&postq);
    intopost(inq,&postq);
 // printf("\n");
 // printf("postq :");
  //display (postq);
  //printf("\n");
  st st ; 
  init (&st);
  eval (&postq,&st);
  //displayst(&st);
  printans(st);
  printf("\n");
  
  return 0 ;

}
