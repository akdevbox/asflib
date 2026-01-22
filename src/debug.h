// SPDX-License-Identifier: MIT

/**
 * Copyright (C) 2026 Amaan.
 * All rights reserved.
 *
 * Provides simple debug print functions for containers with concrete type of integer
 */
#pragma once
#include "vector.h"
#include "linkedlist.h"

// A function to print a vector of integers
void debug_intvec(AsfVec *vec);

// A function to print a linked list of integers
void debug_intll(AsfLlNode *root);
