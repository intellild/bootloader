#ifndef EXT3_H
#define EXT3_H

#include <inttypes.h>

#pragma pack(push)
#pragma pack(1)
typedef struct {
  uint32_t indBlock[12];
  uint32_t secindBlockLevel1;
  uint32_t secindBlockLevel2;
  uint32_t secindBlockLevel3;
  uint32_t unknown;
  uint32_t szLog;
} log_backup_info_t;

typedef struct {
  uint32_t cntiNode;
  uint32_t cntBlock;
  uint32_t cntReservedBlock;
  uint32_t cntFreeBlock;
  uint32_t cntFreeNode;
  uint32_t firstDataBlock;
  uint32_t szBlock;
  uint32_t szSegment;
  uint32_t cntBlockPerGroup;
  uint32_t cntSegmentPerBlock;
  uint32_t cntiNodePerGroup;
  uint32_t lastMountTime;
  uint32_t lastWriteTime;
  uint16_t cntMount;
  uint16_t maxCntMount;
  uint16_t signature;
  uint16_t err;
  uint16_t errMethod;
  uint16_t subVersion;
  uint32_t lastCheckTime;
  uint32_t maxCheckGap;
  uint32_t creator;
  uint32_t mainVersion;
  uint16_t uid;
  uint16_t gid;
  uint32_t firstiNode;
  uint16_t sziNode;
  uint16_t curGroup; // whitch group current superblock in
  uint32_t sigComp;
  uint32_t sigUncomp;
  uint32_t sigReadonly;
  uint8_t UUID[16];
  char name[16];
  char lastPath[64];
  uint32_t mapAlgo;
  uint8_t cntFilePreallocBlock;
  uint8_t cntPathPreallocBlock;
  uint16_t reserved;
  uint8_t logUUID[16];
  uint32_t logiNode;
  uint32_t logDevice;
  uint32_t lastAloneiNode;
  uint32_t hashSeed[4];
  uint32_t defaultHashVersion;
  uint32_t defaultMountOption;
  uint32_t firstOriginDataBlockGroup;
  uint32_t creatTime;
  log_backup_info_t logBackupInfo;
} ext3_super_block_t;
#pragma pack(pop) // pack(1)

bool ext3_verify_partition(dpt_t dpt);

#endif
