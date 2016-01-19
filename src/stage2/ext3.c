#include "ext3.h"
#include "disk.h"
#include "common.h"
#include <stddef.h>

static uint8_t buf[1024];

bool ext3_verify_partition(dpt_t* dpt)
{
    ext3_super_block_t* psuperblock = (ext3_super_block_t*)buf;
    read_disk(buf, dpt->lbaBeg + 2, 2);

    if (psuperblock->signature != 0xEF53)
    {
        return false;
    }

    return true;
}

bool ext3_read_file(dpt_t* dpt, char* filename, uint8_t* buf, uint64_t offset, uint64_t cntBytes)
{
    static ext3_super_block_t superBlock;
    read_disk(buf, dpt->lbaBeg + 2, 2);
    memcpy(&superBlock, buf, sizeof(superBlock));

    read_disk(buf, dpt->lbaBeg + 4, 2);
    int i;
    for (i = 0; i < superBlock.cntBlock / superBlock.cntBlockPerGroup; i++)
    {
        static ext3_block_group_descriptor_t* pGroupDescriptor;
        pGroupDescriptor = (ext3_block_group_descriptor_t*)(buf + i * sizeof(ext3_block_group_descriptor_t));
    }
}
