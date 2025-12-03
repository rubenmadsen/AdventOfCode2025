#ifndef RMTNODE_H_
#define RMTNODE_H_

typedef struct RMTNode RMTNode;


RMTNode *RMTNode_create();
void RMTNode_destroy(RMTNode *node);

void RMTNode_set_parent(RMTNode *node, RMTNode *parent);
void RMTNode_set_ref(RMTNode *node, void *ref);
void *RMTNode_get_ref(RMTNode *node);
RMTNode *RMTNode_add_child(RMTNode *node, void *child);
void RMTNode_remove_child(RMTNode *node, void *child);

#endif