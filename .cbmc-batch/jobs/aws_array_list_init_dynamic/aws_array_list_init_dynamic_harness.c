/*
 * Copyright 2019 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://aws.amazon.com/apache2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#include <aws/common/array_list.h>
#include <proof_helpers/make_common_data_structures.h>

/**
 * Runtime: 6s
 */
void aws_array_list_init_dynamic_harness() {
    /* data structure */
    struct aws_array_list list;

    /* parameters */
    struct aws_allocator *allocator;
    size_t item_size;
    size_t initial_item_allocation;

    /* assumptions */
    ASSUME_CAN_FAIL_ALLOCATOR(allocator);
    __CPROVER_assume(initial_item_allocation <= MAX_INITIAL_ITEM_ALLOCATION);
    __CPROVER_assume(item_size <= MAX_ITEM_SIZE);

    /* perform operation under verification */
    if (aws_array_list_init_dynamic(nondet_bool() ? &list : NULL, allocator, initial_item_allocation, item_size) ==
        AWS_OP_SUCCESS) {
        /* assertions */
        assert(aws_array_list_is_valid(&list));
        assert(list.alloc == allocator);
        assert(list.item_size == item_size);
        assert(list.length == 0);
        assert(list.current_size == item_size * initial_item_allocation);
    }
}
