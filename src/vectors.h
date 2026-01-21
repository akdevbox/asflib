// SPDX-License-Identifier: MIT

/*
 * Copyright (C) 2026 Amaan.
 * All rights reserved.
 *
 * This file provides an implementation for generic vectors that can store any type of elements.
 *
 * You can also change the amount of new allocations made for vectors when it needs to grow
 * by defining ASFVEC_OPT_GROWSIZE through `-DASFVEC_OPT_GROWSIZE=100`
 */

#pragma once
#include <stddef.h>

#define ASFVECERR -1
#define ASFVECERR_MEMORY -2    // Any errors regarding memory
#define ASFVECERR_CANT_GROW -3 // Thrown for cases where the vector isn't supposed to grow but the function paramters ask it to

#ifndef ASFVEC_OPT_GROWSIZE
#define ASFVEC_OPT_GROWSIZE 10
#endif

typedef struct
{
    void *contents;
    size_t capacity;
    size_t length;
    size_t element_size;
} AsfVector;

AsfVector *asfvec_ccreate(size_t elem_size, size_t capacity);
AsfVector *asfvec_create(size_t elem_size);
void asfvec_free(AsfVector *vec);
int asfvec_cresize(AsfVector *vec, size_t new_cap);
int asfvec_lresize(AsfVector *vec, size_t new_len);
int asfvec_pushunsafe(AsfVector *vec);
int asfvec_pushcpy(AsfVector *vec, void *element);
int asfvec_pushzro(AsfVector *vec);

// Code below this is for providing functions for inlining

/*
 * Returns the pointer to an item inside the vector, its the caller's responsibility
 * to provide a valid index or this returns a NULL pointer in Debug mode.
 */

#define asfvec_getitem(vec, idx) ((char *)((vec)->contents) + ((idx) * ((vec)->element_size)))

#ifdef ASF_IMPL
#include <stdlib.h>
#include <string.h>
/*
 * Allocates a AsfVector struct using malloc with appropriate capacity and returns it
 *
 * Returns NULL if allocation failed
 */
AsfVector *asfvec_ccreate(size_t elem_size, size_t capacity)
{
    // Try to allocate the object
    AsfVector *vec = (AsfVector *)malloc(sizeof(AsfVector));
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

/*
 * Allocate an AsfVector with zero capacity by default, see asfvec_ccreate for better knowledge
 * of how to create a pre-allocated capacity vector.
 *
 * Returns NULL if the allocation failed
 */
AsfVector *asfvec_create(size_t elem_size)
{
    return asfvec_ccreate(elem_size, 0);
}

/*
 * Frees up an AsfVec
 */
void asfvec_free(AsfVector *vec)
{
    free(vec->contents);
    free(vec);
}

/*
 * Resizes the capacity of a vector, truncating the length in the process if needed.
 * Might change the pointer of the contents.
 *
 * If an error is encountered, nothing changes and the error code ASFVECERR_MEMORY is returned
 */
int asfvec_cresize(AsfVector *vec, size_t new_cap)
{
    void **new_vec = realloc(vec->contents, vec->element_size * new_cap);
    if (new_vec == NULL)
        return ASFVECERR_MEMORY;

    vec->contents = new_vec;
    vec->capacity = new_cap;

    // Truncate the length if its higher than new capacity
    if (vec->length > new_cap)
        vec->length = new_cap;

    return 0;
}

/*
 * Resize the length of a vector, only lets reduction of the length and not growth.
 * Does not change the capacity of the contents.
 *
 * Returns ASFVECERR_CANT_GROW if the new_len is invalid in the vec's context
 */
int asfvec_lresize(AsfVector *vec, size_t new_len)
{
    if (vec->length < new_len)
        return ASFVECERR_CANT_GROW;

    vec->length = new_len;
    return 0;
}

/*
 * Grows the vector in an optimized manner.
 */
static int asfvec_optimized_grow(AsfVector *vec, size_t extra_size)
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

/*
 * Pushes a new element to the vector, appropriately allocating new space when needed.
 * Doesn't change the allocated region's data. essentially, the data in the new element
 * is undefined by default.
 *
 * Ideally, use asfvec_pushcpy and asfvec_pushzro
 */
int asfvec_pushunsafe(AsfVector *vec)
{
    int err;

    err = asfvec_optimized_grow(vec, 1);
    if (err < 0)
        return err;

    vec->length++;
    return 0;
}

/*
 * Pushes a new element to the vector, appropriately allocating new space when needed
 * copies the bytes pointed to by *element based on the internal element_size
 *
 * Returns any errors if encountered, in which case the vector is left unchanged
 */
int asfvec_pushcpy(AsfVector *vec, void *element)
{
    int err;

    err = asfvec_pushunsafe(vec);
    if (err < 0)
        return err;

    void *new_item = asfvec_getitem(vec, vec->length - 1);
    memcpy(new_item, element, vec->element_size); // Copy the new element in
    return 0;
}

/*
 * Increments the length by one pushing a zeroed out element to the list. Returns an int depicting
 * weather the operation was successful or not. Use asfvec_last to get the pointer to the element
 * pushed by this.
 */
int asfvec_pushzro(AsfVector *vec)
{
    int err;

    err = asfvec_pushunsafe(vec);
    if (err < 0)
        return err;

    void *new_item = asfvec_getitem(vec, vec->length - 1);
    memset(new_item, 0, vec->element_size);
    return 0;
}
#endif // ASF_IMPL
