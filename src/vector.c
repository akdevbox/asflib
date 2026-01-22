// SPDX-License-Identifier: MIT

/**
 * Copyright (C) 2026 Amaan.
 * All rights reserved.
 */

#include "vector.h"
#include <stdlib.h>
#include <string.h>

AsfVec *asfvec_ccreate(size_t elem_size, size_t capacity)
{
    // Try to allocate the object
    AsfVec *vec = (AsfVec *)malloc(sizeof(AsfVec));
    if (vec == NULL)
        return NULL;

    vec->element_size = elem_size;
    vec->length = 0;
    vec->capacity = capacity;

    if (capacity)
    {
        vec->contents = (void **)malloc(capacity * elem_size);
        // If the allocation fails, free the currently allocated struct and return NULL
        if (vec->contents == NULL)
        {
            free(vec);
            return NULL;
        }
    }
    else
    {
        // If the size to allocate is given as 0, don't allocate
        vec->contents = NULL;
    }

    return vec;
}

AsfVec *asfvec_create(size_t elem_size)
{
    return asfvec_ccreate(elem_size, 0);
}

void asfvec_free(AsfVec *vec)
{
    free(vec->contents);
    free(vec);
}

int asfvec_cresize(AsfVec *vec, size_t new_cap)
{
    void *new_vec = realloc(vec->contents, vec->element_size * new_cap);
    if (new_vec == NULL)
        return ASFVECERR_MEMORY;

    vec->contents = new_vec;
    vec->capacity = new_cap;

    // Truncate the length if its higher than new capacity
    if (vec->length > new_cap)
        vec->length = new_cap;

    return 0;
}

int asfvec_lresize(AsfVec *vec, size_t new_len)
{
    if (vec->length < new_len)
        return ASFVECERR_CANT_GROW;

    vec->length = new_len;
    return 0;
}

/**
 * Grows the vector in an optimized manner.
 */
static int asfvec_optimized_grow(AsfVec *vec, size_t extra_size)
{
    size_t current_space = vec->capacity - vec->length;
    if (current_space >= extra_size)
        return 0; // Don't need to grow

    // The amount of extra slots that we need
    size_t growth_required = extra_size - current_space;
    if (growth_required < ASFVEC_OPT_GROWSIZE) // Ensure a minimum growth size
        growth_required = ASFVEC_OPT_GROWSIZE;

    size_t new_capacity = vec->capacity + growth_required;

    return asfvec_cresize(vec, new_capacity);
}

int asfvec_pushunsafe(AsfVec *vec)
{
    int err;

    err = asfvec_optimized_grow(vec, 1);
    if (err < 0)
        return err;

    vec->length++;
    return 0;
}

int asfvec_pushcpy(AsfVec *vec, void *element)
{
    int err;

    err = asfvec_pushunsafe(vec);
    if (err < 0)
        return err;

    void *new_item = asfvec_getitem(vec, vec->length - 1);
    memcpy(new_item, element, vec->element_size); // Copy the new element in
    return 0;
}

int asfvec_pushzro(AsfVec *vec)
{
    int err;

    err = asfvec_pushunsafe(vec);
    if (err < 0)
        return err;

    void *new_item = asfvec_getitem(vec, vec->length - 1);
    memset(new_item, 0, vec->element_size);
    return 0;
}
