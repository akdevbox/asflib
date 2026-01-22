// SPDX-License-Identifier: MIT

/**
 * Copyright (C) 2026 Amaan.
 * All rights reserved.
 */
#include "doublylinkedlist.h"
#include <stdlib.h>
#include <string.h>

AsfDllNode *asfdll_createunsafe(size_t elem_size)
{
    AsfDllNode *node = (AsfDllNode *)malloc(offsetof(AsfDllNode, value) + elem_size);
    if (node == NULL)
        return NULL;

    node->previous = NULL;
    node->next = NULL;
    return node;
}

AsfDllNode *asfdll_createzro(size_t elem_size)
{
    AsfDllNode *node = asfdll_createunsafe(elem_size);
    memset(node->value, 0, elem_size);
    return node;
}

AsfDllNode *asfdll_createcpy(size_t elem_size, void *elem)
{
    AsfDllNode *node = asfdll_createunsafe(elem_size);
    memcpy(node->value, elem, elem_size);
    return node;
}

AsfDllNode *asfdll_last(AsfDllNode *root)
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

AsfDllNode *asfdll_first(AsfDllNode *root)
{
    if (root == NULL)
    {
        return NULL;
    }

    // Loops until the root variable points to the final node
    while (root->previous != NULL)
        root = root->previous;

    return root;
}

AsfDllNode *asfdll_append(AsfDllNode *root, AsfDllNode *nextnode)
{
    if (root == NULL || nextnode == NULL)
        return;

    AsfDllNode *last = asfdll_last(root);
    last->next = nextnode;
    nextnode->previous = last;

    return nextnode;
}

AsfDllNode *asfdll_prepend(AsfDllNode *root, AsfDllNode *prevnode)
{
    if (root == NULL || prevnode == NULL)
        return;

    AsfDllNode *first = asfdll_first(root);
    first->previous = prevnode;
    prevnode->next = first;

    return prevnode;
}

void asfdll_free(AsfDllNode *root)
{
    if (root == NULL)
        return;

    AsfDllNode *originalroot = root;

    // Free root and also the elements towards the end
    AsfDllNode *next;
    while (root != NULL)
    {
        next = root->next;
        free(root);
        root = next;
    }

    // Free the elements before root (we are not freeing root itself because it was freed in the previous pass)
    root = originalroot->previous;
    while (root != NULL)
    {
        next = root->previous;
        free(root);
        root = next;
    }
}

void asfdll_freen(AsfDllNode *node)
{
    if (node == NULL)
        return;

    if (node->next != NULL)
        node->next->previous = NULL;
    if (node->previous != NULL)
        node->previous->next = NULL;

    free(node);
}

AsfDllNode *asfdll_popn(AsfDllNode *node)
{
    if (node == NULL)
        return NULL;

    if (node->next != NULL)
        node->next->previous = node->previous;
    if (node->previous != NULL)
        node->previous->next = node->next;

    node->previous = NULL;
    node->next = NULL;

    return node;
}

// TODO
AsfDllNode *asfdll_splitn(AsfDllNode *node)
{
    if (node == NULL || node->next == NULL)
        return NULL;
}

AsfDllNode *asfdll_splitp(AsfDllNode *node)
{
}