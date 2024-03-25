#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "readfile.h"

int main()
{
    // Node* tree  = (Node*) calloc (1, sizeof(Node));
    Node* tree2 = (Node*) calloc (1, sizeof(Node));
    // tree->value = 10;
    // elem_t x = 5;


    // TreePrint (tree);
    // TreeDtor  (tree);
    readfile  (&tree2, "data.txt");
    // printf ("tree2->value = %d\n", tree2->value);
    TreePrint (tree2);
    TreeDtor  (tree2);
    // free (tree2);
}
