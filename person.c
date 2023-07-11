#include "person.h"

struct Person{
    char *name;
    int age;
    float height;
};


Person *person_create(char *name, int age, float height){
    Person *p = malloc(sizeof(Person));
    p->name = malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(p->name, name);
    // free(name);
    p->age = age;
    p->height = height;
    
    return p;
}

void person_destroy(Person *p){
    free(p->name);
    free(p);
}

void person_print(Person *p){
    printf("%s %d %.2f\n", p->name, p->age, p->height);
}