// SPDX-License-Identifier: MIT

/**
 * Copyright (C) 2026 Amaan.
 * All rights reserved.
 *
 * This file provides an implementation for generic linked lists. The
 * data of the linkedlist lives inside the linkedlist itself.
 */

#pragma once
#include <stddef.h>
#include <stdalign.h>

/**
 * A singly linked list node. Do not create this struct without the appropriate library methods.
 */
typedef struct _AsfLlNode
{
    struct _AsfLlNode *next;
    _Alignas(max_align_t) char value[];
} AsfLlNode;

/**
 * Creates a Linked List Node with the given element size. It is recommended that the element
 * size for a given linked list stay consistent. This method does not initialize the memory
 * inside the node that is returned from malloc.
 */
AsfLlNode *asfll_createunsafe(size_t elem_size);

/**
 * Creates a Linked List Node with given element size, see asfll_createunsafe.
 * This method initializes the node's value to zero.
 */
AsfLlNode *asfll_createzro(size_t elem_size);

/**
 * Creates a Linked List Node with given element size, see asfll_createunsafe.
 * This method initializes the node's value by copying from void *elem.
 */
AsfLlNode *asfll_createcpy(size_t elem_size, void *elem);

/**
 * Returns the pointer to the last node given a root or intermediate node.
 */
AsfLlNode *asfll_last(AsfLlNode *root);

/**
 * Appends a linked list nextnode to existing root by setting the root's last node's next.
 * nextnode may be a single node or a linkedlist.
 *
 * Returns a pointer to the appended node, ie nextnode.
 */
AsfLlNode *asfll_append(AsfLlNode *root, AsfLlNode *nextnode);

/**
 * Free the entire list starting from the given root element
 */
void asfll_free(AsfLlNode *root);

/**
 * Free just the given element without touching the rest of the list
 */
void asfll_freen(AsfLlNode *node);

/**
 * Get linked list item as a pointer to the value.
 *
 * node is a AsfLlNode*
 * type is the T* pointer type (example: int*)
 */
#define asfll_value(node, type) ((type)((node)->value))
