#include "ext3.h"
#include "disk.h"
#include "common.h"
#include <stddef.h>

static uint8_t buf[1024];

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
    read_disk(buf, dpt->lbaBeg + 2, 2);
    memcpy(&superBlock, buf, sizeof(superBlock));
    uint32_t despciptorOffser = get_block_descriptor_lba(&superBlock);

    read_disk(buf, dpt->lbaBeg + despciptorOffser, 2);
    uint32_t i;
    for (i = 0; i < superBlock.cntBlock / superBlock.cntBlockPerGroup; i++)
    {
        ext3_block_group_descriptor_t* pGroupDescriptor;
        pGroupDescriptor = (ext3_block_group_descriptor_t*)(buf + (i % 64) * sizeof(ext3_block_group_descriptor_t));

        uint32_t j;
        for (j = 0; j < superBlock.cntiNodePerGroup; j++)
        {
            static ext3_inode_t inode;
        }

        if (i % 64 == 1)
        {
            read_disk(buf, dpt->lbaBeg + despciptorOffser + i / 64, 2);
        }
    }

    return false;
}