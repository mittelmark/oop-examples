// OOP with C
// https://www.perplexity.ai/search/how-can-i-simulate-a-animal-cl-wqtfh.F0S_OT9PL2Houzsw
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Typedef for function pointers - methods of our object
typedef void (*read_func)(void* self);
typedef void (*eat_func)(void* self,float amount);
typedef void (*run_func)(void* self,float distance);
// Animal struct definition
struct Animal {
    // properties
    char* species;
    int age;
    char* name;
    float weight;
    // methods
    read_func read;
    eat_func eat;    
    run_func run;
} ;

// Method implementations
void animal_read(void* self) {
    struct Animal* animal = (struct Animal*)self;
    printf("Species: %s\nAge: %d\nName: %s\n", 
           animal->species, animal->age, animal->name);
}
void animal_eat(void* self,float amount) {
    struct Animal* animal = (struct Animal*)self;
    animal->weight += amount;
    printf("Weight of %s after eat: %0.1f\n",animal->name,animal->weight);
}

void animal_run(void* self,float distance) {
    struct Animal* animal = (struct Animal*)self;
    animal->weight -= distance*0.1;
    printf("%s's weight after running %0.2fkm: %0.2f\n",animal->name,distance,animal->weight);
}

// Constructor
struct Animal* Animal_new(const char* species, int age, const char* name,float weight) {
    struct Animal* obj = malloc(sizeof(struct Animal));
    obj->species = strdup(species);
    obj->age = age;
    obj->name = strdup(name);
    obj->weight = weight;
    obj->read = animal_read;
    obj->eat = animal_eat;
    obj->run = animal_run;    
    printf("Animal %s created!\n",obj->name);
    return obj;
}

// Destructor
void Animal_delete(struct Animal** obj) {
    printf("Animal %s will be deleted!\n",(*obj)->name);
    free((*obj)->species);
    free((*obj)->name);
    free(*obj);
    *obj = NULL;
}

// using macros for simplfied object creation and destruction
#define ANIMAL(x,species,age,name,weight) struct Animal* x = Animal_new(species,age,name,weight);
#define DELETE(x)     Animal_delete(&x);
// Usage example
int main() {
    struct Animal* lion = Animal_new("Panthera leo", 5, "Simba",100.0);
    struct Animal* micky = Animal_new("Cat", 18, "Micky",4.5);
    ANIMAL(susi,"Cat",10,"Susi",5.2);
    lion->eat(lion,4.5); // Explicit context passing
    micky->eat(micky,0.1); 
    susi->eat(susi,0.1);
    susi->run(susi,1);
    lion->run(lion,3.0); 
    lion->read(lion);   
    micky->run(micky,0.01);     
    micky->read(micky);       
    susi->read(susi);
    Animal_delete(&lion);
    Animal_delete(&micky);  
    DELETE(susi);
    return 0;
}

