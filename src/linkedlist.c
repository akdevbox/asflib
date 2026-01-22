// SPDX-License-Identifier: MIT

/**
 * Copyright (C) 2026 Amaan.
 * All rights reserved.
 */
#include "linkedlist.h"
#include <stdlib.h>
#include <string.h>

AsfLlNode *asfll_createunsafe(size_t elem_size)
{
    AsfLlNode *node = (AsfLlNode *)malloc(offsetof(AsfLlNode, value) + elem_size);
    if (node == NULL)
        return NULL;

    node->next = NULL;
    return node;
}

AsfLlNode *asfll_createzro(size_t elem_size)
{
    AsfLlNode *node = asfll_createunsafe(elem_size);
    memset(node->value, 0, elem_size);
    return node;
}

AsfLlNode *asfll_createcpy(size_t elem_size, void *elem)
{
    AsfLlNode *node = asfll_createunsafe(elem_size);
    memcpy(node->value, elem, elem_size);
    return node;
}

AsfLlNode *asfll_last(AsfLlNode *root)
{
    if (root == NULL)
    {
        return NULL;
    }

    // Loops until the root variable points to the final node
    while (root->next != NULL)
        root = root->next;

    return root;
}

AsfLlNode *asfll_append(AsfLlNode *root, AsfLlNode *nextnode)
{
    if (root == NULL || nextnode == NULL)
        return;

    AsfLlNode *last = asfll_last(root);
    last->next = nextnode;

    return nextnode;
}

void asfll_free(AsfLlNode *root)
{
    if (root == NULL)
        return;

    AsfLlNode *next;
    while (root != NULL)
    {
        next = root->next;
        free(root);
        root = next;
    }
}

void asfll_freen(AsfLlNode *node)
{
    if (node == NULL)
        return;
    free(node);
}