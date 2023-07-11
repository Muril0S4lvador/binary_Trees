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
    char what[10], name[20], key[4];
    BinaryTree *bt = binary_tree_construct(Cmp_fn, KeyDestroy_fn, ValDestroy_fn);

    scanf("%d", &qtd);

    for(int i = 0; i < qtd; i++){
        scanf("%s", what);

        if( !strcmp(what, "SET") ){
            scanf("%s %d %f", name, &age, &height);
            void *v = key_create(name);
            Person *person = person_create(age, height);
            binary_tree_add_recursive(bt, v, person);

        } else if( !strcmp(what, "GET") ){
            scanf("%s", name);
            Person *p = binary_tree_get(bt, key);
            if(p)
                person_print(p);
            else
                printf("CHAVE INEXISTENTE\n");

        } else if( !strcmp(what, "POP") ){
            scanf("%s", key);
            binary_tree_remove(bt, key);

        } else if( !strcmp(what, "MIN") ){
            KeyValPair kvp = binary_tree_min(bt);
            printf("%s ", (char*)kvp.key);
            person_print(kvp.value);

        } else if( !strcmp(what, "MAX") ){
            KeyValPair kvp = binary_tree_max(bt);
            printf("%s ", (char*)kvp.key);
            person_print(kvp.value);

        } else if( !strcmp(what, "POP_MIN") ){
            KeyValPair *kvp = binary_tree_pop_min(bt);
            
            if(kvp){
                printf("%s ", (char*)kvp->key);
                person_print(kvp->value);
                key_val_pair_destroy(kvp, bt->key_destroy_fn, bt->val_destroy_fn);

            } else 
                printf("ARVORE VAZIA\n");

        } else if( !strcmp(what, "POP_MAX") ){
            KeyValPair *kvp = binary_tree_pop_max(bt);
            
            if(kvp){
                printf("%s ", (char*)kvp->key);
                person_print(kvp->value);
                key_val_pair_destroy(kvp, bt->key_destroy_fn, bt->val_destroy_fn);

            } else 
                printf("ARVORE VAZIA\n");

        }
    }

    binary_tree_destroy(bt);

    return 0;
}