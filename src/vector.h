// SPDX-License-Identifier: MIT

/**
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

#ifndef ASFVEC_OPT_GROWSIZE
#define ASFVEC_OPT_GROWSIZE 10
#endif

typedef enum
{
    ASFVECERR_OK = 0,
    ASFVECERR_UNKNOWN = -1,
    ASFVECERR_MEMORY = -2,    // Any errors regarding memory
    ASFVECERR_CANT_GROW = -3, // Thrown for cases where the vector isn't supposed to grow but the function paramters ask it to
} AsfVecErr;

/**
 * A generic vector container which grows efficiently by keeping track
 * of capacity and length separately.
 */
typedef struct
{
    void *contents;
    size_t capacity;
    size_t length;
    size_t element_size;
} AsfVec;

/**
 * Allocates a AsfVec struct using malloc with appropriate capacity and returns it
 *
 * Returns NULL if allocation failed
 */
AsfVec *asfvec_ccreate(size_t elem_size, size_t capacity);

/**
 * Allocate an AsfVec with zero capacity by default, see asfvec_ccreate for better knowledge
 * of how to create a pre-allocated capacity vector.
 *
 * Returns NULL if the allocation failed
 */
AsfVec *asfvec_create(size_t elem_size);

/**
 * Frees up an AsfVec
 */
void asfvec_free(AsfVec *vec);

/**
 * Resizes the capacity of a vector, truncating the length in the process if needed.
 * Might change the pointer of the contents.
 *
 * If an error is encountered, nothing changes and the error code ASFVECERR_MEMORY is returned
 */
AsfVecErr asfvec_cresize(AsfVec *vec, size_t new_cap);

/**
 * Resize the length of a vector, only lets reduction of the length and not growth.
 * Does not change the capacity of the contents.
 *
 * Returns ASFVECERR_CANT_GROW if the new_len is invalid in the vec's context
 */
AsfVecErr asfvec_lresize(AsfVec *vec, size_t new_len);

/**
 * Pushes a new element to the vector, appropriately allocating new space when needed.
 * Doesn't change the allocated region's data. essentially, the data in the new element
 * is undefined by default.
 *
 * Ideally, use asfvec_pushcpy and asfvec_pushzro
 */
AsfVecErr asfvec_pushunsafe(AsfVec *vec);

/**
 * Pushes a new element to the vector, appropriately allocating new space when needed
 * copies the bytes pointed to by *element based on the internal element_size
 *
 * Returns any errors if encountered, in which case the vector is left unchanged
 */
AsfVecErr asfvec_pushcpy(AsfVec *vec, void *element);

/**
 * Increments the length by one pushing a zeroed out element to the list. Returns an int depicting
 * weather the operation was successful or not. Use asfvec_last to get the pointer to the element
 * pushed by this.
 */
AsfVecErr asfvec_pushzro(AsfVec *vec);

// Code below this is for providing functions for inlining

/**
 * Returns the pointer to an item inside the vector, its the caller's responsibility
 * to provide a valid index or this returns a NULL pointer in Debug mode.
 */
#define asfvec_getitem(vec, idx) ((char *)((vec)->contents) + ((idx) * ((vec)->element_size)))
