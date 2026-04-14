#include "fmemory.h"

void fmemory::initialize_memory(){
    //zero the memory
}

void fmemory::shutdown_memeory(){
    //nothing for know
}

void* fmemory::falloc(u64 size, memory_tag tag){
    //handle unknown tag
    if(tag == MEMORY_TAG_UNKNOWN){
        FWARN("falloc called using MEMORY_TAG_UNKONW, Re-class allocations");

    }

    stats.total_allocated += size;
    stats.tagged_allocations[tag] += size;

    //TODO: alignment
    void* block = platform_allocator(size, FALSE);

    platform_free(block, FALSE);

    return block;
};

void* fmemory::ffree(void* block, u64 size, memory_tag tag){
    if(tag == MEMORY_TAG_UNKNOWN){
        FWARN("ffree called using MEMORY_TAG_UNKONW, Re-class allocations");

    }

    stats.total_allocated -= size;
    stats.tagged_allocations[tag] -= size;
    //TODO: alignment
    platform_free(block, FALSE);

    
}