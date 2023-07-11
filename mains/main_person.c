#include <stdio.h>
#include <string.h>
#include "binary_tree.h"
#include "person.h"

int Cmp_fn(void *v1, void *v2){
    return strcmp((char*)v1, (char*)v2);
}

void KeyDestroy_fn(void *key){
    free(key);
}

void ValDestroy_fn(void *val){
    person_destroy(val);
}

void *key_create(char key[]){
    char *v = malloc(sizeof(char) * (strlen(key) + 1));
    strcpy(v, key);
    return v;
}

int main(){
    int qtd, age;
    float height;
    char what[4], name[20], key[4];
    BinaryTree *bt = binary_tree_construct(Cmp_fn, KeyDestroy_fn, ValDestroy_fn);

    scanf("%d", &qtd);

    for(int i = 0; i < qtd; i++){
        scanf("%s", what);

        if( !strcmp(what, "SET") ){
            scanf("%s %s %d %f", key, name, &age, &height);
            void *v = key_create(key);
            Person *person = person_create(name, age, height);
            binary_tree_add_recursive(bt, v, person);

        } else if( !strcmp(what, "GET") ){
            scanf("%3s", key);
            Person *p = binary_tree_get(bt, key);
            person_print(p);
        }
    }

    binary_tree_destroy(bt);

    return 0;
}