#ifndef RMNODE_H_
#define RMNODE_H_

typedef struct RMNode RMNode;


RMNode *rmnode_create();
void rmnode_destroy(RMNode *node);

void rmnode_set_parent(RMNode *node, RMNode *parent);
void rmnode_set_ref(RMNode *node, void *obj);
void *rmnode_get_ref(RMNode *node);
RMNode *rmnode_add_child(RMNode *node, void *child);
void rmnode_remove_child(RMNode *node, void *child);

#endif