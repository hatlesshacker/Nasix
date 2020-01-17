typedef struct {
  uint16_t ofs;
  uint16_t seg;
} FARPTR;

#ifndef COLOR_LIST
#define COLOR_LIST
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHT_GREY 7
#define DARK_GREY 8
#define LIGHT_BLUE 9
#define LIGHT_GREEN 10
#define LIGHT_CYAN 11
#define LIGHT_RED 12
#define LIGHT_MAGENTA 13
#define YELLOW 14
#define WHITE 15
#endif

typedef struct VbeInfoBlock {
    char VbeSignature[4];
    uint16_t VbeVersion;
    uint16_t OemStringPtr[2];
    uint8_t Capabilities[4];
    uint16_t *VideoModePtr;
    uint16_t TotalMemory;
    uint16_t oem_software_revision;
    uint32_t oem_vendor_name_string;
    uint32_t oem_product_name_string;
    uint32_t oem_product_revision_string;
    uint8_t reserved[222];
    uint8_t oem_data[256];
} VbeInfoBlock;

typedef struct ModeInfoBlock {
    uint16_t attributes;
    uint8_t winA, winB;
    uint16_t granularity;
    uint16_t winsize;
    uint16_t segmentA, segmentB;
    FARPTR realFctPtr;
    uint16_t pitch;

    uint16_t Xres, Yres;
    uint8_t Wchar, Ychar, planes, bpp, banks;
    uint8_t memory_model, bank_size, image_pages;
    uint8_t reserved0;

    uint8_t red_mask, red_position;
    uint8_t green_mask, green_position;
    uint8_t blue_mask, blue_position;
    uint8_t rsv_mask, rsv_position;
    uint8_t directcolor_attributes;

    uint32_t physbase;
    uint32_t reserved1;
    uint16_t reserved2;
} ModeInfoBlock;

typedef struct _color_t {
    uint8_t R;
    uint8_t G;
    uint8_t B;
} color_t;

ModeInfoBlock *get_miblock();