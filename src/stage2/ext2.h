#pragma once
#ifndef EXT2_H
#define EXT2_h

#include <stdint.h>

#define EXT2_DIRE_UNKNONW 0
#define EXT2_DIRE_FILE 1
#define EXT2_DIRE_DIR 2
#define EXT2_DIRE_CHR 3
#define EXT2_DIRE_BLK 4
#define EXT2_DIRE_FIFO 5
#define EXT2_DIRE_SOCK 6
#define EXT2_DIRE_SYM 7

#pragma pack(push,1)
typedef struct ext2_super_block_struct
{
	uint32_t inodeTotal;
	uint32_t blockTotal;
	uint32_t blockReserved;
	uint32_t blockFree;
	uint32_t inodeFree;
	uint32_t blkInd; // Block number of the block containing the superblock  
	uint32_t blockSize;
	uint32_t segmentSize;
	uint32_t blockPerGroup;
	uint32_t segmentPerBlock;
	uint32_t inodePerGroup;
	int32_t timeMount;
	int32_t timeWrite;
	uint16_t mountCount;
	uint16_t fsckInterval;
	uint16_t magic;
	uint16_t stat;
	uint16_t errMethod;
	uint16_t versionMinor;
	uint32_t fsckLast;
	uint32_t fsckIntervalForce;
	uint32_t creator;
	uint32_t versionMajor;
	uint16_t uid;
	uint16_t gid;
	struct ExtArea
	{
		uint32_t inodeFirstNonReserve;
		uint16_t inodeStuctSize;
		uint16_t groupBelong; // whitch group current superblock in
		uint32_t flagOptional;
		uint32_t flagRequired;
		uint32_t flagReadonly;
		uint8_t UUID[16];
		char vname[16];
		char lastPath[64];
		uint32_t compressionAlgorithm;
		uint8_t blockPreallocFile;
		uint8_t blockPreallocDir;
		uint16_t __unused;
		uint8_t journalID[16];
		uint32_t journalInode;
		uint32_t journalDevice;
		uint32_t ophanInode;
		uint8_t unused[788];
	} ext;
} ext2_superblock_t;

typedef struct ext2_group_descriptor_struct
{
	uint32_t blockBitmapAddr;
	uint32_t inodeBitmapAddr;
	uint32_t inodeTableAddr;
	uint16_t blockFree;
	uint16_t inodeFree;
	uint16_t cntDir;
	uint8_t unused[14];
} ext2_group_descriptor_t;

typedef struct ext2_inode_struct
{
	uint16_t mode;
	uint16_t uid;
	uint32_t sizeLow;
	int32_t timeAccess;
	int32_t timeCreate;
	int32_t timeModify;
	int32_t timeDelete;
	uint16_t gid;
	uint16_t hardLink;
	uint32_t sector;
	uint32_t flag;
	uint32_t osspec;
	uint32_t blockDirect[12];
	uint32_t blockIndirectSingly;
	uint32_t blockIndirectDoubly;
	uint32_t blockIndirectTriply;
	uint32_t gengeration;
	uint32_t ex1; // In Ext2 version 0, this field is reserved. In version >= 1, Extended attribute block (File ACL). 
	uint32_t ex2; // In Ext2 version 0, this field is reserved. In version >= 1, Upper 32 bits of file size (if feature bit set) if it's a file, Directory ACL if it's a directory
	uint32_t fragment;
	uint8_t osspec2[12];
} ext2_inode_t;

typedef struct ext2_directory_entry_struct
{
	uint32_t inode;
	uint16_t size;
	uint8_t nameLen;
	uint8_t type;
	char name[256];
};
#pragma pack(pop)

#endif