#include<stdio.h>
int main(){
  int i=1,x = 4444,a = 1541,c = 2957,M = 14000;
  int A_0=0,A_1=0,B_0=0,B_1=0;
  for(;i<=20;i++){
    x = (a*x+c)%M;
    if(x%2==0)//交互になる，証明できる？
      A_0++;
    else
      A_1++;
    if(x<M/2)
      B_0++;
    else
      B_1++;
  }
  printf("%d %d\n%d %d",A_0,A_1,B_0,B_1);
}