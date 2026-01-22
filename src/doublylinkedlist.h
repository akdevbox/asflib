// SPDX-License-Identifier: MIT

/**
 * Copyright (C) 2026 Amaan.
 * All rights reserved.
 *
 * This file provides an implementation for generic doubly linked lists. The
 * data of the linkedlist lives inside the linkedlist itself.
 */

#pragma once
#include <stddef.h>
#include <stdalign.h>

/**
 * A doubly linked list node. Do not create this struct without the appropriate library methods.
 */
typedef struct _AsfDllNode
{
    struct _AsfDllNode *next;
    struct _AsfDllNode *previous;
    _Alignas(max_align_t) char value[];
} AsfDllNode;

/**
 * Creates a Linked List Node with the given element size. It is recommended that the element
 * size for a given linked list stay consistent. This method does not initialize the memory
 * inside the node that is returned from malloc.
 */
AsfDllNode *asfdll_createunsafe(size_t elem_size);

/**
 * Creates a Linked List Node with given element size, see asfdll_createunsafe.
 * This method initializes the node's value to zero.
 */
AsfDllNode *asfdll_createzro(size_t elem_size);

/**
 * Creates a Linked List Node with given element size, see asfdll_createunsafe.
 * This method initializes the node's value by copying from void *elem.
 */
AsfDllNode *asfdll_createcpy(size_t elem_size, void *elem);

/**
 * Returns the pointer to the last node given a root or intermediate node.
 */
AsfDllNode *asfdll_last(AsfDllNode *root);

/**
 * Returns the pointer to the first node given a root or intermediate node.
 */
AsfDllNode *asfdll_first(AsfDllNode *root);

/**
 * Appends a linked list nextnode to existing root by setting the root's last node's next.
 * nextnode may be a single node or a linkedlist.
 *
 * The nextnode's previous points to the last element and the last element's next points to the nextnode.
 *
 * Returns a pointer to the appended node, ie returning nextnode
 */
AsfDllNode *asfdll_append(AsfDllNode *root, AsfDllNode *nextnode);

/**
 * Appends a linked list prevnode to existing root by setting the root's first node's previous.
 * prevnode may be a single node or a linkedlist.
 *
 * The prevnode's next points to the first element and the first element's previous points to prevnode
 *
 * Returns a pointer to the appended node, ie returning prevnode
 */
AsfDllNode *asfdll_prepend(AsfDllNode *root, AsfDllNode *prevnode);

/**
 * Free the entire list starting from the given root element and also freeing
 * up the elements towards the start.
 */
void asfdll_free(AsfDllNode *root);

/**
 * Free just the given element without touching the rest of the list.
 * Also sets the previous node's next to NULL and next node's previous to NULL
 */
void asfdll_freen(AsfDllNode *node);

/**
 * Pops an element out of the list given a pointer to the element.
 * Sets the previous node's next to the next node of the provided node
 * and similarly for the next node's previous to the previous node of the provided node
 *
 * A <-> B <-> C
 *
 * asfdll_popn(B);
 *
 * A <-> C
 *
 * Returns the pointer to the popped node. The node is not freed, and
 * node's next and previous are set to NULL
 */
AsfDllNode *asfdll_popn(AsfDllNode *node);

/**
 * Splits the list at next.
 *
 * A <-> B <-> C
 *
 * asfdll_splitn(B);
 *
 * A <-> B, C
 *
 * returns C in this case since it got isolated from input B.
 */
AsfDllNode *asfdll_splitn(AsfDllNode *node);

/**
 * Splits the list at previous.
 *
 * A <-> B <-> C
 *
 * asfdll_splitp(B);
 *
 * A, B <-> C
 *
 * returns A in this case, since it got isolated from input B.
 */
AsfDllNode *asfdll_splitp(AsfDllNode *node);

/**
 * Get linked list item as a pointer to the value.
 *
 * node is a AsfDllNode*
 * type is the T* pointer type (example: int*)
 */
#define asfdll_value(node, type) ((type)((node)->value))
