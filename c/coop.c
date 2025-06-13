#include <stdio.h>
#include <string.h>
// class declaration
struct Person {
    int age, id;  char name[50];    // properties
    // methods - first argument pointer to the struct
    int (*getAge)(struct Person *);
    void (*setAge)(struct Person *, int age);
};
// method definitions, first argument should be *self
int Person_getAge (struct Person * self) {
    return(self->age);
}
void Person_setAge (struct Person * self, int age) {
    self->age = age;
}
// constructor assign properties and methods
struct Person Person_new (int age, const char * name) {
    static int id = 999;  id += 1;
    struct Person p;
    p.age  = age;  p.id = id;
    strncpy(p.name,name,strlen(name)+1);
    p.getAge = Person_getAge;
    p.setAge = Person_setAge;
    return(p); }
int main () {
    // object creation
    struct Person lisa = Person_new(23, "Lisa");
    struct Person emil = Person_new(18, "Emil");
    printf("Hello %s! Your id is: %d! You are %d years old! \n",
           lisa.name, lisa.id, // public property
           lisa.getAge(&lisa)); // method call with reference
    printf("Hello %s! Your id is: %d! You are %d years old!\n",
           emil.name, emil.id, // public property
       emil.getAge(&emil)); // method call with reference
    emil.setAge(&emil,emil.getAge(&emil)+1);
    printf("Hello %s! Your id is: %d! You are %d years old!\n",
           emil.name, emil.id, // public property
       emil.getAge(&emil)); // method call with reference
    return(0);
}
