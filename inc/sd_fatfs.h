#ifndef  SD_FATFS
#define SD_FATFS
#include "sdio_high_level.h"
#include "ff.h"

#define FILE_LIST_SIZE 64 //Max number of characters in Long File name.

typedef enum {
	SDFS_OK,
	SDFS_SD_PROBLEM,
	SDFS_FILE_NOT_FOUND,
	SDFS_FILE_CREATE_ERROR,
	SDFS_GETFREE_ERR,
	SDFS_MOUNT_ERR,
	SDFS_OPEN_ERR,
	SDFS_SEEK_ERR,
	SDFS_CLOSE_ERR,
	SDFS_WRITE_ERR,
	SDFS_READ_ERR,
	SDFS_RD_STRING_ERR,
	SDFS_EOF,
	SDFS_DIR_OPEN_ERR
} SDFS_status_type;

typedef enum {
  F_RD =0,    // read an existent file
  F_WR,       // write to an existent file
  F_WR_NEW,   // write to a new file
  F_WR_CLEAR  // rewrite to an existent file
}FMODE_t;

typedef struct {
	WORD active; //Position of an active item
	WORD num; //Number of items in a file list
	WORD pos;  //Current position in a list
	char names[FILE_LIST_SIZE][_MAX_LFN];
}file_list_type;

SDFS_status_type SDFS_init(void);
SDFS_status_type SDFS_mount(void);
SDFS_status_type SDFS_open(FIL* fp, const char* name, FMODE_t mode);
SDFS_status_type SDFS_close(FIL* fp);
SDFS_status_type SDFS_writeString(FIL* fp, char* text);
SDFS_status_type SDFS_readString(FIL* fp, char* text, uint32_t len);
SDFS_status_type SDFS_scandir(char* path, file_list_type* fl);

#endif //SD_FATFS
