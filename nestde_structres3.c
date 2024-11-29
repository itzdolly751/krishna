#include <stdio.h>
struct Address{
char city[50];
int pin;
};
struct person{
char name[50];
struct Address addr;
};
int main() {
  struct person p;
  printf("Enter person name:") ;
  scanf("%s", p.name);
  printf("Enter city:");
  scanf("%s",p.addr.city);
  printf("Enter pin:");
  scanf("%d", &p.addr.pin);
  printf("\nPerson Details:\n");
  printf("Name:%s\nCity:%s\nPin:%d\n", p.name,p.addr.city,p.addr.pin);
  return 0;


}