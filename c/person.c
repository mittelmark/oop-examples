#include <stdio.h>

// In this example we demonstrate:
// - simple class declaration using a struct
// - function pointers in the struct as methods
// - constructor creation
// - inheritance in C by using a variable super
// - declaration of private variables by convention of using an underline
// - unique identifiers by using the static keyword

// struct as class
struct Person {
    // properties
    int age;
    // methods
    int (*get)(struct Person *);
    void (*set)(struct Person *, int age);
};

// method implementations
void Person_setAge(struct Person *self, int age) { self->age = age; }

int Person_getAge(struct Person *self) { return (self->age); }

// constructor implementation
struct Person Person_new (int age) {
    struct Person p;
    p.set=Person_setAge;
    p.get=Person_getAge;
    p.set(&p,age);
    return(p);
}

// inheritance
struct Student {
    // parent class
    struct Person super ;
    // properties
    int matrikel;
    int kn;
    // methods
    void (*learn)(struct Student* self);
    // private variable by convention
    int _hidden;
};
void Student_learn (struct Student* self) {
    self->kn = self->kn+1;
}
struct NAME {
    //public properties
    int x;
    //methods
    int (*getX)(struct NAME* self);
    // private vars
    int _h;
};
struct Student Student_new (int age, int kn) {
    // no student should have the same matrikel number
    static int matrikel = 799999;
    matrikel++;
    struct Student s;
    s.super = Person_new(age);
    s.learn = Student_learn;
    s.kn = kn;
    s.matrikel = matrikel;
    s._hidden = 1;
    return(s);
}

int main(int argc, char *argv[]) {
    struct Person p1 = Person_new(11);
    p1.set(&p1, 12);
    printf("Age is: %i\n", p1.get(&p1));
    struct Student s1 = Student_new(25,100);
    for (int i = 0; i < 10; i++) {
        s1.learn(&s1);
    }
    printf("Student s1's  Age is: %i\n", s1.super.get(&s1.super));
    printf("Student s1's knowledge is: %i\n",s1.kn);
    printf("Student s1's matrikel is: %i\n",s1.matrikel); 
    // bad style: access to private parts
    s1._hidden = 10;
    // another students with independent properties
    struct Student s2 = Student_new(27,88);
    printf("Student s2's matrikel is: %i\n",s2.matrikel); 
    printf("Student s2's age is: %i\n",s2.super.get(&s2.super));     
    printf("Student s1's matrikel is: %i\n",s2.matrikel);     
    printf("Student s1's age is: %i\n",s1.super.get(&s1.super));         
    return (0);
}
