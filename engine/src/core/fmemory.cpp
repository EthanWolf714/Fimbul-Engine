#include "fmemory.h"

fmemory memory;

void fmemory::initialize_memory(){

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

    platform_zero_memory(block, FALSE);

    return block;
};

void fmemory::ffree(void* block, u64 size, memory_tag tag){
    if(tag == MEMORY_TAG_UNKNOWN){
        FWARN("ffree called using MEMORY_TAG_UNKONW, Re-class allocations");

    }

    stats.total_allocated -= size;
    stats.tagged_allocations[tag] -= size;
    //TODO: alignment
    platform_free(block, FALSE);

    
}

void* fmemory::fzero_memory(void* block, u64 size){
    
    return platform_zero_memory(block, size);
}

void* fmemory::fcopy_memory(void* dest, const void* source, u64 size){
    return platform_copy_memory(dest, source, size);
    
}
void* fmemory::fset_memory(void* dest , i32 value, u64 size){
    return platform_set_memory(dest, value, size);
}

char* fmemory::get_memory_usage_str(){

    i32 gib = 1024 * 1024 * 1024;
    i32 mib = 1024 * 1024;
    i32 kib = 1024;
    //create buffer
    char buffer[8000] = "Sytem memory use: \n";
    u64 offset = strlen(buffer);
    for(int i = 0; i < MEMORY_TAG_MAX_TAGS; ++i){
        char unit[4] = "XiB";
        f32 amount;
        if(stats.tagged_allocations[i] >= gib ){
            unit[0] = 'G';
            amount = stats.tagged_allocations[i] / (float)gib;

        }else if(stats.tagged_allocations[i] >= mib){
            unit[0] = 'M';
            amount = stats.tagged_allocations[i] / (float)mib;

        }else if(stats.tagged_allocations[i] >= kib){
            unit[0] = 'K';
            amount = stats.tagged_allocations[i] / (float)kib;
        }else {
            unit[0] = 'B';
            unit[1] = 0;
            amount = (float)stats.tagged_allocations[i];
        }

        i32 length = snprintf(buffer + offset, 8000, "%s: %.2f%s\n", memory_tag_strings[i], amount, unit);
        offset +=length;
        
    }
    char* out_string = strdup(buffer);
        return out_string;
}