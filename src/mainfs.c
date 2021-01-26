#include "common.h"
#include "heap_permanent.h"
#include "heap_temporary.h"

INCLUDE_ASM(s32, "mainfs", func_80009880);

INCLUDE_ASM(s32, "mainfs", func_800098FC);

// Likely file break for mainfs.c

// 16 byte portion of a directory or file table, which is initially read from ROM.
struct mainfs_table_header {
    s32 count;
    s32 offsets[3]; // Enough to pad to size 16
};

struct mainfs_entry_info {
    u8 *file_bytes;
    s32 size;
    s32 compression_type;
};

extern void *D_800ABFC0; // FS ROM location
extern u32 D_800ABFC4; // Directory count
extern s32 *D_800ABFC8; // Directory offset table pointer.

extern void *D_800ABFCC; // FS ROM location (copy)
extern u32 D_800ABFD0; // Directory count (copy)
extern s32 *D_800ABFD4; // Directory offset table pointer (copy)

extern struct mainfs_table_header D_800ABFE0;

// Initialize file system from ROM.
void func_80009AC0(void *fs_rom_loc) {
    s32 dir_table_size;
    struct mainfs_table_header *mainfs_table_header;

    D_800ABFC0 = fs_rom_loc;
    mainfs_table_header = &D_800ABFE0;
    func_8004DA40(fs_rom_loc, mainfs_table_header, 16); // ExecRomCopy
    D_800ABFC4 = mainfs_table_header->count;
    dir_table_size = mainfs_table_header->count * 4;
    D_800ABFC8 = (s32 *)MallocPerm(dir_table_size);
    func_8004DA40(fs_rom_loc + 4, D_800ABFC8, dir_table_size);
    D_800ABFCC = D_800ABFC0;
    D_800ABFD0 = D_800ABFC4;
    D_800ABFD4 = D_800ABFC8;
}

INCLUDE_ASM(s32, "mainfs", func_80009B64);

INCLUDE_ASM(s32, "mainfs", ReadMainFS);

INCLUDE_ASM(s32, "mainfs", func_80009C74);

INCLUDE_ASM(s32, "mainfs", func_80009CD8);

INCLUDE_ASM(s32, "mainfs", func_80009D4C);

INCLUDE_ASM(s32, "mainfs", func_80009DA8);

INCLUDE_ASM(s32, "mainfs", func_80009E04);

/**
 * Free file previously obtained through ReadMainFS.
 */
void FreeMainFS(void *file) {
    if (file != NULL) {
        FreePerm(file);
    }
}

void func_80009E8C(void *file) {
    if (file != NULL) {
        FreePerm(file); //! Should be FreeTemp, but not functionally problematic.
    }
}

INCLUDE_ASM(s32, "mainfs", func_80009EAC);

INCLUDE_ASM(s32, "mainfs", func_80009F64);

INCLUDE_ASM(s32, "mainfs", func_80009FF8);

INCLUDE_ASM(s32, "mainfs", func_8000A028);

INCLUDE_ASM(s32, "mainfs", func_8000A0D4);

INCLUDE_ASM(s32, "mainfs", func_8000A150);
