/*
9
SET 123 jose 32 1.56
GET 123
SET 345 maria 18 2.11
SET 001 paulo 55 1.65
SET 211 naldo 43 1.89
GET 001
GET 211
GET 345
GET 123
*/

#include <stdio.h>
#include <string.h>
// #include "binary_tree.h"
// #include "person.h"

int main(){
    int qtd, age;
    float height;
    char what[3], name[50], key[3];
    // BinaryTree *bt = binary_tree_construct();

    scanf("%d", &qtd);

    for(int i = 0; i < qtd; i++){
        scanf("%s", what);

        if( !strcmp(what, "SET") ){
            scanf("%s %s %d %f", key, name, &age, &height);
            printf("%s %s %d %f", key, name, age, height);
            // binary_tree_add(bt, key, value);

        } else if( !strcmp(what, "GET") ){


        }
    }

    return 0;
}