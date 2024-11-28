
#include<stdlib.h>
#include<stdio.h>
int main(){
  int n, *arr;
  printf("Enter the number of elements:");
  scanf("%d",&n);
  arr=(int*)malloc(n*sizeof(int));
  if(arr==NULL){
    printf("Memory allocation failed\n");
    return 1;
  }
  printf("Enter %d elements: \n",n);
for(int i=0;i<n;i++){
  scanf("%D",&arr[i]);
}  
  printf("The elements are:\n",n);
  for(int i=0;i<n;i++){
    printf("%d",arr[i]);
  }
  free(arr);
  printf("after free %d",*arr);
  return 0;
}