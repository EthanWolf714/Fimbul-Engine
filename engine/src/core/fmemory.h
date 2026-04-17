#pragma once

#include <defines.h>
#include <string.h>
#include <stdio.h>
#include "platform/platform.h"
#include "logger.h"




typedef enum memory_tag{
    MEMORY_TAG_UNKNOWN,
    MEMORY_TAG_ARRAY,
    MEMORY_TAG_DARRAY,
    MEMORY_TAG_DICT,
    MEMORY_TAG_RING_QUEUE,
    MEMORY_TAG_BST,
    MEMORY_TAG_STRING,
    MEMORY_TAG_APPLICATION,
    MEMORY_TAG_JOB,
    MEMORY_TAG_TEXTURE,
    MEMORY_TAG_MATERIAL_INSTANCE,
    MEMORY_TAG_RENDERER,
    MEMORY_TAG_GAME,
    MEMORY_TAG_TRANSFORM,
    MEMORY_TAG_ENTITY,
    MEMORY_TAG_ENTITY_NODE,
    MEMORY_TAG_SCENE,

    MEMORY_TAG_MAX_TAGS
} memory_tag;


struct memory_stats {
    u64 total_allocated;
    u64 tagged_allocations[MEMORY_TAG_MAX_TAGS];

};

static const char* memory_tag_strings[MEMORY_TAG_MAX_TAGS] = {
    "UNKNOWN    ",
    "ARRAY      ",
    "DARRAY     ",
    "DICT       ",
    "RING_QUEUE ",
    "BST        ",
    "STRING     ",
    "APPLICATION",
    "JOB        ",
    "TEXTURE    ",
    "MAT_INST   ",
    "RENDERER   ",
    "GAME       ",
    "TRANSFORM  ",
    "ENTITY     ",
    "ENTITY_NODE",
    "SCENE      "};

static struct memory_stats stats;
class fmemory {

    public: 
        FAPI void initialize_memory();
        FAPI void shutdown_memeory();   

        FAPI void* falloc(u64 size, memory_tag tag);
        FAPI void ffree(void* block, u64 size, memory_tag tag);
        FAPI void* fzero_memory(void* block, u64 size);
        FAPI void* fcopy_memory(void* block, const void* source, u64 size);
        FAPI void* fset_memory(void* dest, i32 value, u64 size);

        FAPI char* get_memory_usage_str();
};

extern FAPI fmemory memory;