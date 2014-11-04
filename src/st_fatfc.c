/*
 * High level SD_card IO operations library based on FATFS and low level  SD functions.
 *
 */

#include <string.h>
#include "log.h"
#include "sd_fatfs.h"

static FATFS FileSystemObject; //File system

SDFS_status_type SDFS_init(void) {
	if (SD_Init() == SD_OK) {
		return SDFS_OK;
	} else {
		return SDFS_SD_PROBLEM;
	}
}

SDFS_status_type SDFS_mount(void) {
	SDFS_status_type ret_wert = SDFS_MOUNT_ERR;
	FRESULT check = FR_INVALID_PARAMETER;
	DWORD fre_clust;
	FATFS *fs;

	check = f_mount(&FileSystemObject, "", 1);
	if (check == FR_OK) {
		check = f_getfree("0:", &fre_clust, &fs);
		if (check == FR_OK) {
			ret_wert = SDFS_OK;
		} else {
			ret_wert = SDFS_GETFREE_ERR;
		}
	} else {
		ret_wert = SDFS_MOUNT_ERR;
	}

	return (ret_wert);

}

SDFS_status_type SDFS_open(FIL* fp, const char* name, FMODE_t mode) {
	SDFS_status_type ret_wert = SDFS_OPEN_ERR;
	FRESULT check = FR_INVALID_PARAMETER;

	switch (mode) {
	case F_RD:
		check = f_open(fp, name, FA_OPEN_EXISTING | FA_READ);
		break;
	case F_WR:
		check = f_open(fp, name, FA_OPEN_EXISTING | FA_WRITE);
		break;
	case F_WR_NEW:
		check = f_open(fp, name, FA_OPEN_ALWAYS | FA_WRITE);
		break;
	case F_WR_CLEAR:
		check = f_open(fp, name, FA_CREATE_ALWAYS | FA_WRITE);
		break;
	}

	if (check == FR_OK) {

		ret_wert = SDFS_OK;
		if ((mode == F_WR) || (mode == F_WR_NEW)) {

			check = f_lseek(fp, f_size(fp));
			if (check != FR_OK) {
				ret_wert = SDFS_SEEK_ERR;
			}
		}
	} else {
		ret_wert = SDFS_OPEN_ERR;
	}

	return (ret_wert);
}

SDFS_status_type SDFS_close(FIL* fp) {
	SDFS_status_type ret_wert = SDFS_CLOSE_ERR;
	FRESULT check = FR_INVALID_PARAMETER;

	check = f_close(fp);

	if (check == FR_OK) {
		ret_wert = SDFS_OK;
	} else {
		ret_wert = SDFS_CLOSE_ERR;
	}

	return (ret_wert);
}

SDFS_status_type SDFS_writeString(FIL* fp, char* text) {
	SDFS_status_type ret_wert = SDFS_WRITE_ERR;
	int check = 0;

	check = f_puts(text, fp);

	if (check >= 0) {
		ret_wert = SDFS_OK;
		f_putc('\n', fp);
	} else {
		ret_wert = SDFS_WRITE_ERR;
	}

	return (ret_wert);
}

SDFS_status_type SDFS_readString(FIL* fp, char* text, uint32_t len) {
	SDFS_status_type ret_wert = SDFS_RD_STRING_ERR;
	int check;

	f_gets(text, len, fp);
	check = f_eof(fp);
	if (check != 0)
		return (SDFS_EOF);
	check = f_error(fp);
	if (check != 0)
		return (SDFS_RD_STRING_ERR);
	ret_wert = SDFS_OK;

	return (ret_wert);
}

static 	char lfn[_MAX_LFN+1];


SDFS_status_type SDFS_scandir(char* path, file_list_type* fl) {
	FRESULT res;
	FILINFO fno;
	DIR dir;
	WORD n = 0;

//	char lfn[_MAX_LFN];
	fno.lfname = lfn;
	fno.lfsize = _MAX_LFN - 1;

	res = f_opendir(&dir, path);
	if (res == FR_OK) {
		for (;;) {
			res = f_readdir(&dir, &fno); /* Read dir object */
			if (res != FR_OK || fno.fname[0] == 0)
				break;
			if (fno.fname[0] == '.')
				continue; /* Ignore element "." */
			if (!(fno.fattrib & AM_DIR)) { /* It is file not dir */
				strcpy(fl->names[n], *fno.lfname ? fno.lfname : fno.fname);
				n++;
			}
		}
		fl->num = n;
		f_closedir(&dir);
		return SDFS_OK;
	} else {
       return SDFS_DIR_OPEN_ERR;
	}
}

void SDIO_IRQHandler()
{
    SD_ProcessIRQSrc();
}

void DMA2_Stream3_IRQHandler()
{
    SD_ProcessDMAIRQ();
}
