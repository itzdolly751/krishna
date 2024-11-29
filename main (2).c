#include<stdio.h>
struct Empolyee{
 char name[50];
int id;
float salary;
};
int main(){
  struct Employee employees[2];
  for(int i=0;i<2;i++){
    printf("enter detailes of employee %d:\n",i+1);
    printf("Name:");
    scanf("%s",employees[i].name);
    printf("ID:");
    scanf("%d",& employees[i].id);
    printf("salary:");
    scanf("%f",& employees[i].salary); 
    }
  }
  printf("\nEmployee Detiles:\n");
  for(int i=0;i<2;i++){
    printf("Name:"%s,ID:%d,salary:%.2f\n",employees[i].name, employees[i].ib, employees[i].salary);
  }