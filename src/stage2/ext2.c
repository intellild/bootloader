#include "ext2.h"
#include "disk.h"

int ext2_verify_disk(dpt_t* pdpt)
{
    static ext2_superblock_t superblock;
    read_disk(&superblock, pdpt->lbaBeg + 2, 2);
    if (superblock.magic == 0xef53)
    {
        return 1;
    }
    return 0;
}

void ext2_read(dpt_t* pdpt, char* path, void* dst)
{
    (void)pdpt;
    (void)path;
    (void)dst;
}