#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "readfile.h"

int main()
{
    Node* tree  = (Node*) calloc (1, sizeof(Node));
    Node* tree2 = (Node*) calloc (1, sizeof(Node));
    tree->value = 10;
    elem_t x = 5;
    TreeAdd (tree, &x);
    x = 3;
    TreeAdd (tree, &x);
    x = 2;
    TreeAdd (tree, &x);
    x = 8;
    TreeAdd (tree, &x);
    x = 7;
    TreeAdd (tree, &x);
    x = 6;
    TreeAdd (tree, &x);
    x = 12;
    TreeAdd (tree, &x);

    TreePrint (tree);
    TreeDtor  (tree);
    readfile  (&tree2, "data.txt");
    TreePrint (tree2);
    // TreeDtor  (tree2);
    puts ("bark");
    // free (tree2);
}
