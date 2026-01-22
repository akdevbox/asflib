// SPDX-License-Identifier: MIT

/**
 * Copyright (C) 2026 Amaan.
 * All rights reserved.
 */
#include "debug.h"
#include <stdio.h>

// A function to print a vector of integers
void debug_intvec(AsfVec *vec)
{
    if (vec == NULL)
    {
        printf("\nVec: NULL\n");
        return;
    }

    printf("\nVec: %p\n", vec);
    printf("Contents: %p\n", vec->contents);
    printf("Length: %zu\n", vec->length);
    printf("Cap: %zu\n", vec->capacity);
    for (int x = 0; x < vec->length; x++)
    {
        int *item = (int *)asfvec_getitem(vec, x);

        if (item != NULL)
        {
            printf("%2d: %d\n", x, *item);
        }
        else
        {
            printf("%2d: %s\n", x, "NULL RETURNED");
        }
    }
}

// A function to print a linked list of integers
void debug_intll(AsfLlNode *root)
{
    if (root == NULL)
    {
        printf("\nLl: NULL\n");
        return;
    }

    int size = 0;
    printf("\nLl: %p\n", root);

    while (root != NULL)
    {
        printf("%2d: %d\n", size, *asfll_value(root, int *));
        size++;
        root = root->next;
    }

    printf("Ll Size: %d\n", size);
}
