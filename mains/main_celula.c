#include <stdio.h>
#include <string.h>
#include "binary_tree.h"

typedef struct
{
    int x, y;
} Celula;

Celula *celula_create(int x, int y)
{
    Celula *c = malloc(sizeof(Celula));
    c->x = x;
    c->y = y;
    return c;
}

void celula_destroy(Celula *c)
{
    free(c);
}

int Cmp_fn(void *c1, void *c2)
{
    Celula *a = (Celula *)c1;
    Celula *b = (Celula *)c2;

    int x = (a->x - b->x),
        y = (a->y - b->y);
    if(x)
        return x;
    return y;
}

void KeyDestroy_fn(void *key){
    celula_destroy(key);
}

void ValDestroy_fn(void *val){
    free(val);
}

int main(){
    int qtd, x, y, val;
    char what[4];
    BinaryTree *bt = binary_tree_construct(Cmp_fn, KeyDestroy_fn, ValDestroy_fn);

    scanf("%d", &qtd);

    for(int i = 0; i < qtd; i++){
        scanf("%s", what);

        if( !strcmp(what, "SET") ){
            scanf("%d %d %d", &x, &y, &val);
            Celula *c = celula_create(x, y);
            int *ptr = malloc(sizeof(int));
            *ptr = val;
            binary_tree_add(bt, c, ptr);

        } else if( !strcmp(what, "GET") ){
            scanf("%d %d", &x, &y);
            Celula *c = celula_create(x, y);
            int *v = binary_tree_get(bt, c);
            if(c)
                celula_destroy(c);
            if(v)
                printf("%d\n", *v);
        }
    }

    binary_tree_destroy(bt);

    return 0;
}