#include "RMTNode.h"
#include <stdio.h>
#include <stdlib.h>
#include "RMLinkedList.h">

struct RMTNode{
    RMTNode *parent;
    RMLinkedList *children;
    void *ref;
    size_t child_count;
};


RMTNode *RMTNode_create(){
    RMTNode *node = (RMTNode *)malloc(sizeof(RMTNode));
    node->parent = NULL;
    node->child_count = RMLinkedList_create();
    node->ref = NULL;
    node->child_count = 0;
    return node;
}

void RMTNode_destroy(RMTNode *node){
    RMLinkedList_destroy(node->children);
    free(node);
}

void RMTNode_set_parent(RMTNode *node, RMTNode *parent){
    node->parent = parent;
}

void RMTNode_set_ref(RMTNode *node, void *ref){
    node->ref = ref;
}

void *RMTNode_get_ref(RMTNode *node){
    return node->ref;
}
RMTNode *RMTNode_add_child(RMTNode *node, void *child){
    RMLinkedList_push(node->children, RMTNode_create());
}
void RMTNode_remove_child(RMTNode *node, void *child){
    RMLinkedList_popItem(node->children, child);
}