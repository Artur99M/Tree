#ifndef TREE_H
#define TREE_H
typedef int elem_t;

typedef struct Node
{
    elem_t value;
    Node* left;
    Node* right;
} Node;

enum TREE_ERROR
{
    TREE_NO_ERROR = 0,
    TREE_NULLPTR = 1,
    TREE_ELEM_NULLPTR = 2,
    TREE_CALLOC_ERROR = 4,
    TREE_NO_ELEM = 8,
    TREE_ADD_ERROR = 16,
    ELEM_IS_VALUE_OF_NODE_OF_TREE = 32,
    TREE_FILE_NULLPTR = 64,
    TREE_HZ_ERROR = 128,
    TREE_VOID = 256
};

TREE_ERROR TreeAdd (Node*, const elem_t*);
TREE_ERROR TreePrint (const Node*);
TREE_ERROR TreeCtor (Node*, const elem_t*);
TREE_ERROR TreeCtor (Node*);
TREE_ERROR TreeAddNode (Node*, Node*);
TREE_ERROR TreeDelete (Node*, const elem_t*);
void TreeDtor (Node*);
#endif
