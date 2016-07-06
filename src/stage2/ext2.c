#include "ext2.h"
#include "disk.h"
#include "print.h"
#include <stddef.h>

static ext2_superblock_t superblock;
static uint8_t buf[4096];

static uint32_t find_dir(char* name);

int ext2_verify_disk(dpt_t* pdpt)
{
    read_disk(&superblock, pdpt->lbaBeg + 2, 2);
    if (superblock.magic == 0xef53)
    {
        return 1;
    }
    return 0;
}

void ext2_read(dpt_t* pdpt, char* path, void* dst)
{
    static ext2_group_descriptor_t group;
    static uint8_t lbaOffset[3] = {4, 4, 8};
    static uint8_t blk2sector[3] = {2, 4, 8};
    static ext2_inode_t root;

    read_disk(buf, pdpt->lbaBeg + lbaOffset[superblock.blockSize], 1);
    memcpy(&group, buf, sizeof(group));

    read_disk(buf, pdpt->lbaBeg + blk2sector[superblock.blockSize] * group.inodeTableAddr, 1);
    memcpy(&root, buf + sizeof(root), sizeof(root));

    for (int i = 0; i < 12; i++)
    {
        if (root.blockDirect[i] == 0)
        {
            monitor_write("error\n");
            while (1)
                ;
        }

        read_disk(buf, pdpt->lbaBeg + blk2sector[superblock.blockSize] * root.blockDirect[i], blk2sector[superblock.blockSize]);
        uint32_t inode = find_dir(path);
        if (inode)
        {
            //uint32_t groupind = inode / superblock.inodePerGroup;
            monitor_write("file found");

            //TODO
            while (1)
                ;
        }
    }
}

static uint32_t find_dir(char* name)
{
    static uint16_t blksize[3] = {1024, 2048, 4096};
    ext2_directory_entry_t* pdir;
    pdir = (ext2_directory_entry_t*)buf;
    while (pdir->inode)
    {
        if (strequ(name, pdir->name, pdir->nameLen))
        {
            return pdir->inode;
        }
        else
        {
            pdir = (ext2_directory_entry_t*)((uint8_t*)pdir + sizeof(pdir->size));

            if ((size_t)pdir - (size_t)buf > blksize[superblock.blockSize] - 8u)
            {
                return 0;
            }
        }
    }
    return 0;
}