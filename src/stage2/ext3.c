#include "ext3.h"
#include "disk.h"
#include "common.h"
#include <stddef.h>

#ifndef NODEBUG
#include "print.h"
#endif

static uint8_t buf[1024];

static inline uint32_t blocks_to_sectors(ext3_super_block_t* pSuperBlock, uint32_t cntBlock);
static inline uint32_t groups_to_sectors(ext3_super_block_t* pSuperBlock, uint32_t cntGroup);

static inline void read_super_block(dpt_t* dpt, ext3_super_block_t* pSuperBlock)
{
    read_disk(buf, dpt->lbaBeg + 2, 2);
    memcpy(pSuperBlock, buf, sizeof(ext3_super_block_t));
}

static inline void read_group_descriptor(
    dpt_t* dpt,
    ext3_super_block_t* pSuperBlock,
    ext3_block_group_descriptor_t* pGroupDescriptor,
    uint32_t ind,
    bool flush)
{
    static uint32_t desbuf[512];
    uint32_t bufind = 0xFFFFFFFF;
    if (bufind == ind / 16 && !flush)
    {
        memcpy(
            pGroupDescriptor,
            (ext3_block_group_descriptor_t*)desbuf + ind % 16,
            sizeof(ext3_block_group_descriptor_t));
    }
    else
    {
        read_disk(desbuf, dpt->lbaBeg + blocks_to_sectors(pSuperBlock, 1) + ind / 16, 1);
        bufind = ind / 16;
        memcpy(
            pGroupDescriptor,
            (ext3_block_group_descriptor_t*)desbuf + ind % 16,
            sizeof(ext3_block_group_descriptor_t));
    }
}

static inline uint32_t blocks_to_sectors(ext3_super_block_t* pSuperBlock, uint32_t cntBlock)
{
    return cntBlock * power(2, pSuperBlock->szBlock + 1);
}

static inline uint32_t groups_to_sectors(ext3_super_block_t* pSuperBlock, uint32_t cntGroup)
{
    return cntGroup * blocks_to_sectors(pSuperBlock, pSuperBlock->cntBlockPerGroup);
}

static uint32_t get_lba(ext3_super_block_t* pSuperBlock, uint32_t cntGroup, uint32_t cntBlock)
{
    uint32_t ret = 0;
    ret += groups_to_sectors(pSuperBlock, cntGroup);
    ret += blocks_to_sectors(pSuperBlock, cntBlock);
    return ret;
}

static uint32_t get_block_descriptor_lba(ext3_super_block_t* superBlock)
{
    if (superBlock->cntBlock <= 1)
    {
        return 4;
    }
    else
    {
        return power(2, superBlock->cntBlock + 1);
    }
}

bool ext3_verify_partition(dpt_t* dpt)
{
    ext3_super_block_t* psuperblock = (ext3_super_block_t*)buf;

    read_disk(buf, dpt->lbaBeg + 2, 2);

    if (psuperblock->signature == 0xEF53)
    {
        return true;
    }

    return false;
}

bool ext3_read_file(dpt_t* dpt, char* filename, uint8_t* buf, uint64_t offset, uint64_t cntBytes)
{
    static ext3_super_block_t superBlock;
    read_super_block(dpt, &superBlock);

#ifndef NODEBUG
    if (superBlock.signature == 0xEF53)
    {
        monitor_write("reading ext3 file system\n");
    }
#endif

    static ext3_block_group_descriptor_t groupDescriptor;
    read_group_descriptor(dpt, &superBlock, &groupDescriptor, 1, false);
    monitor_write("number of paths: ");
    monitor_print_hex(groupDescriptor.cntPath, 16);

    return false;
}