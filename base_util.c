#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "structures/structures.h"
#include "base_util.h"
#include "core_functions.h"

void copy_array(struct Value * a, struct Value_array * b){
    struct Value_array * array = malloc(sizeof(struct Value_array));
    array->size = b->size;
    for(int i = 0; i < b->size; i++){
        array->values[i] = value_copy_heap(b->values[i]);
    }
    a->data.array = array;
}

struct Tree * duplicate_tree(struct Tree * a){
    struct Tree * root = malloc(sizeof(struct Tree));
    root->type = a->type;
    root->size = 0;
    root->content = value_copy_stack(&a->content);
    for(int i = 0; i < a->size; i++){
        root->children[i] = duplicate_tree(a->children[i]);
        root->size++;
    }
    return root;
}

void printTree(struct Tree *tree){
    if(!tree->size){
      if(tree->type == 'k'){
          printf("{ type: \'%c\', size: %d, keyword: %s }", tree->type, tree->size, tree->content.data.str.body);
      }
      else if(tree->type == 'n'){
          printf("{ type: \'%c\', size: %d, value: %ld }", tree->type, tree->size, tree->content.data.ln);
      }
      else {
          printf("{ type: \'%c\', size: %d }", tree->type, tree->size);
      }
    } else {
      if(tree->type == 'k'){
          printf("{ type: \'%c\', size: %d, keyword: %s ", tree->type, tree->size, tree->content.data.str.body);
      }
      else if(tree->type == 'n'){
          printf("{ type: \'%c\', size: %d, value: %ld ", tree->type, tree->size, tree->content.data.ln);
      } else {
          printf("{ type: \'%c\', size: %d, ", tree->type, tree->size);
      }
      if(tree->size && tree->size < 100){
        printf("children: [");
        int counter = 0;
        while(counter < tree->size){
          printTree(tree->children[counter]);
          counter++;
        }
      }
      printf("]}");
    }
}
