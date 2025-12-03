#include "RMNode.h"
#include <stdio.h>

struct RMNode{
    RMNode *parent;
    RMNode **children;
    void *ref;

    size_t child_count;
};


RMNode *rmnode_create(){
    RMNode *node = (RMNode *)malloc(sizeof(RMNode));
    node->parent = NULL;
    node->ref = NULL;
    node->child_count = 0;
}
void rmnode_destroy(RMNode *node){
    free(node);
}