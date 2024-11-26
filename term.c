#include <stdio.h>
int main() {
  int n,t1=0,t2=1,nextTerm;
  printf("enter the number of term:");
  scanf("%d",&n);
  printf("Fibonacci Seriers:%d,%d",t1,t2);
  for(int i=3;i<=n;i++){
   nextTerm=t1+t2;
    printf(",%d",nextTerm);
    t1=t2;
    t2=nextTerm;
 }
  return 0;                                                                                    }
   