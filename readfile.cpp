#include "readfile.h"
#include "Onegin/header/readtext.h"
#include "Onegin/header/txtdtor.h"
#include "def.h"
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#define LEAF '*'
#define IN_BRANCH '{'
#define OUT_BRANCH '}'

TREE_ERROR TreeRead (Node* pNode, text* txt, size_t* nline);


TREE_ERROR readfile (Node** Tree, char* file)
{
    if (Tree == nullptr) return TREE_NULLPTR;

    text txt;
    readtext (&txt, file);
    PRINT_DEBUG ("readfile >>> txt.numlines = %lu\n", txt.numlines);
    size_t nline = 0;
    // Node* array = (Node*) calloc (txt.numlines, sizeof (Node));
    // *Tree = array;
    TREE_ERROR ERROR = TreeRead (*Tree, &txt, &nline);
    PRINT_DEBUG ("readfile >>> finish\n");

    txtDtor (&txt);

    return ERROR;
}

TREE_ERROR TreeRead (Node* pNode, text* txt, size_t* nline)
{

    if (pNode == nullptr || txt == nullptr || nline == nullptr)
        return TREE_NULLPTR;


    char c = '\0';
    PRINT_DEBUG ("TreeRead >>> I start sscanf\n");
    PRINT_DEBUG ("TreeRead >>> pNode = %p, *nline = %lu\n", pNode, *nline);
    PRINT_DEBUG ("TreeRead >>> txt->line[*nline].str = \"%s\"\n", txt->line[*nline].str);
    sscanf (txt->line[*nline].str, "%c", &c);
    PRINT_DEBUG ("TreeRead >>> first sscanf: c = %c\n", c);
    (*nline)++;

    if (c == '{')
    {
        PRINT_DEBUG ("TreeRead >>> func start do it smth\n");
        sscanf (txt->line[*nline].str, "%d", &(pNode->value));
        (*nline)++;
        PRINT_DEBUG ("TreeRead >>> value = %d\n", pNode->value);
        PRINT_DEBUG ("TreeRead >>> find memmory for left\n");
        PRINT_DEBUG ("TreeRead >>> &(pNode->left) = %p\n", &(pNode->left));
        if ((pNode->left = (Node*) calloc (1, sizeof (Node))) == nullptr)
            return TREE_NULLPTR;
        PRINT_DEBUG ("TreeRead >>> start see left\n");
        PRINT_DEBUG ("TreeRead >>> pNode->left = %p\n", pNode->left);
        if (TreeRead (pNode->left, txt, nline) == TREE_VOID)
        {
            free (pNode->left);
            pNode->left = nullptr;
        }
        PRINT_DEBUG ("TreeRead >>> finish see left\n");
        PRINT_DEBUG ("TreeRead >>> pNode->left = %p\n", pNode->left);
        PRINT_DEBUG ("TreeRead >>> find memmory for right\n");
        PRINT_DEBUG ("TreeRead >>> &(pNode->right) = %p\n", &(pNode->right));
        if ((pNode->right = (Node*) calloc (1, sizeof (Node))) == nullptr)
            return TREE_NULLPTR;
        PRINT_DEBUG ("TreeRead >>> pNode->right = %p\n", pNode->right);
        PRINT_DEBUG ("TreeRead >>> start see right\n");
        if (TreeRead (pNode->right, txt, nline) == TREE_VOID)
        {
            free (pNode->right);
            pNode->right = nullptr;
        }
        PRINT_DEBUG ("TreeRead >>> finish see right\n");
        PRINT_DEBUG ("TreeRead >>> pNode->right = %p\n", pNode->right);
        sscanf (txt->line[*nline].str, "%c", &c);
        PRINT_DEBUG ("TreeRead >>> third sscanf: c = %c[%d]\n", c, c);
        if (c != '}')
            return TREE_HZ_ERROR;
        (*nline)++;
        PRINT_DEBUG ("TreeRead >>> finish: pNode = %p, pNode->value = %d, pNode->left = %p, pNode->right = %p\n", pNode, pNode->value, pNode->left, pNode->right);
    }
    else if (c == '*')
    {
        PRINT_DEBUG ("TreeRead >>> free memory\n");
        return TREE_VOID;
    }
    else
    {
        PRINT_DEBUG ("TreeRead >>> Strange ERROR\n");
        return TREE_HZ_ERROR;
    }

    return TREE_NO_ERROR;
}
