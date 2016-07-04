#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "base_util.h"
#include "core_functions.h"
#include "process_defs.h"
#include "execute.h"
#include "execution_functions/let_binding.h"
#include "structures/hash_table.h"
#include "config.h"

void make_args_map(struct Tree * ast, hash_table *defined, struct Scopes * scopes, struct Tree *function, int max_depth) {
    // we want to evaluate the values passed into the function
    // but store the result in the next scope, not the current one
    if (function->size - 2 != ast->size) {
        ERROR("Wrong number of arguments!: %i != %i", function->size - 2, ast->size);
    }
    struct Value vals[ast->size];
    for(int i = 0; i < ast->size; i++){
        vals[i] = execute(ast->children[i], defined, scopes, max_depth - 1);
    }
    make_scope(scopes);
    for(int l = 0; l < ast->size; l++){
        char t = function->children[l+1]->content.type;
        if (t != KEYWORD) {
            ERROR("Invalid type for argument: '%c' != KEYWORD", t);
        }
        store_let_value(&function->children[l+1]->content, &vals[l], scopes);
    }
}

struct Tree * get_defined_body(struct Tree * function){
    // just pulls the function body out of a (def...)
    if (function->size <= 1) {
        ERROR("No function body!");
    }
    int index = function->size - 1;
    if (function->children[index]->size == 0) {
        ERROR("No function body!");
    }
    return function->children[index];
}

struct Tree *get_defined_func(hash_table *defined, struct String key) {
    assert(string_is_sane(&key));
    return (struct Tree *) hash_table_get(defined, &key);
}
