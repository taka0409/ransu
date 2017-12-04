#include<stdio.h>
int main(){
  int i=0,x = 4444,a = 1541,c = 2957,M = 14000;
  int A_0=0,A_1=0,B_0=0,B_1=0;
  while(i<100000){
    if(x%2==0)//交互になる，証明できる？
      A_0++;
    else
      A_1++;
    if(x<M/2)
      B_0++;
    else
      B_1++;
    x = (a*x+c)%M;
    i++;
  }
  printf("A-0:%d A-1:%d\nB-0:%d B-1:%d",A_0,A_1,B_0,B_1);
}