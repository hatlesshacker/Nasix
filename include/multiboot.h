#ifndef MULTIBOOT_H_
#define MULTIBOOT_H_

typedef struct multiboot_module {
    unsigned int mod_start;
    unsigned int mod_end;
    unsigned int string;
    unsigned int reserved;
} __attribute__((packed)) multiboot_module_t;
typedef struct multiboot_aout {
    unsigned int tabsize;
    unsigned int strsize;
    unsigned int addr;
    unsigned int reserved;
} __attribute__((packed)) multiboot_aout_t;


typedef struct multiboot_elf {
    unsigned int num;
    unsigned int size;
    unsigned int addr;
    unsigned int shndx;
} __attribute__((packed))  multiboot_elf_t;

typedef struct multiboot_mmap {
    unsigned int size;
    unsigned long long base_addr;
    unsigned long long length;
    unsigned int type;
} __attribute__((packed)) multiboot_mmap_t;

typedef struct multiboot_drive {
    unsigned int size;
    unsigned char drive_number;
    unsigned char drive_mode;
    unsigned char drive_cylinders;
    unsigned short drive_heads;
    unsigned char drive_sectors;
    unsigned short *drive_ports;
} __attribute__((packed)) multiboot_drive_t;

#define MULTIBOOT_DRIVE_CHS 0
#define MULTIBOOT_DRIVE_LBA 1

typedef struct multiboot_apm_table {
    unsigned short version;
    unsigned short cseg;
    unsigned short offset;
    unsigned short cseg_16;
    unsigned short dseg;
    unsigned short flags;
    unsigned short cseg_len;
    unsigned short cseg_16_len;
    unsigned short dseg_len;
} __attribute__((packed)) multiboot_apm_table_t;

typedef struct multiboot_info {
    unsigned int flags;
    unsigned int mem_lower;
    unsigned int mem_upper;
    unsigned int boot_device;
    unsigned int command_line;
    unsigned int mods_count;
    unsigned int mods_addr;
    union {
        multiboot_aout_t aout;
        multiboot_elf_t elf;
    } aout_elf;

    unsigned int mmap_length;
    unsigned int mmap_addr;

    unsigned int drives_length;
    unsigned int drives_addr;
    unsigned int config_table;
    unsigned int boot_loader_name;
    unsigned int apm_table;
    unsigned int vbe_control_info;
    unsigned int vbe_mode_info;
    unsigned short vbe_mode;
    unsigned short vbe_interface_segment;
    unsigned short vbe_interface_offset;
    unsigned short vbe_interface_length;
} __attribute__((packed)) multiboot_info_t;

extern multiboot_info_t * multiboot_info;

#endif