#ifndef _PERSON_H_
#define _PERSON_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Person Person;

Person *person_create(char *name, int age, float height);

void person_print(Person *p);