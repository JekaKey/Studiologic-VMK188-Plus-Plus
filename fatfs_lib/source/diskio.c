#include "sdio_high_level.h"
#include "diskio.h"

DSTATUS disk_initialize (
    BYTE pdrv                /* Physical drive nmuber (0..) */
)
{
    if (pdrv != 0)
    {
        return STA_NOINIT;
    }

    NVIC_InitTypeDef NVIC_InitStructure;

    /* Configure the NVIC Preemption Priority Bits */
    NVIC_PriorityGroupConfig (NVIC_PriorityGroup_1);
    NVIC_InitStructure.NVIC_IRQChannel = SDIO_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init (&NVIC_InitStructure);
    NVIC_InitStructure.NVIC_IRQChannel = SD_SDIO_DMA_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_Init (&NVIC_InitStructure);

    SD_Error Status = SD_Init ();
    if (Status != SD_OK)
    {
        return STA_NOINIT;
    }

    return 0;
}

DSTATUS disk_status (
    BYTE pdrv        /* Physical drive nmuber (0..) */
)
{
    if (pdrv != 0)
    {
        return STA_NOINIT;
    }

    return 0;
}

#if _USE_IOCTL
DRESULT disk_ioctl (
    BYTE pdrv,        /* Physical drive nmuber (0..) */
    BYTE cmd,        /* Control code */
    void *buff        /* Buffer to send/receive control data */
)
{
    if (pdrv != 0)
    {
        return RES_PARERR;
    }

    switch (cmd)
    {
    case CTRL_SYNC:
        //do nothing. By calling SD_WaitReadOperation and
        //SD_WaitWriteOperation we already ensure that operations
        //complete in the read and write functions.
        return RES_OK;
        break;
    default:
        return RES_PARERR;
    }
}
#endif

DRESULT disk_read (
    BYTE pdrv,        /* Physical drive nmuber (0..) */
    BYTE *buff,        /* Data buffer to store read data */
    DWORD sector,    /* Sector address (LBA) */
    UINT count        /* Number of sectors to read (1..128) */
)
{
    if (pdrv != 0)
    {
        return RES_PARERR;
    }

    uint64_t readAddr = sector * 512;
    SD_Error err = SD_ReadMultiBlocks(buff, readAddr, 512, count);
    if (err == SD_OK)
    {
        err = SD_WaitReadOperation();
        if (err == SD_OK)
        {
            while (SD_GetStatus() != SD_TRANSFER_OK){}
        }
        else
        {
            return RES_ERROR;
        }
    }
    else
    {
        return RES_ERROR;
    }
    return RES_OK;
}


#if _USE_WRITE
DRESULT disk_write (
    BYTE pdrv,            /* Physical drive nmuber (0..) */
    const BYTE *buff,    /* Data to be written */
    DWORD sector,        /* Sector address (LBA) */
    UINT count            /* Number of sectors to write (1..128) */
)
{
    if (pdrv != 0)
    {
        return RES_PARERR;
    }

    uint64_t writeAddr = sector * 512;
    SD_Error err = SD_WriteMultiBlocks(buff, writeAddr, 512, count);
    if (err == SD_OK)
    {
        err = SD_WaitWriteOperation();
        if (err == SD_OK)
        {
            while (SD_GetStatus() != SD_TRANSFER_OK){}
        }
        else
        {
            return RES_ERROR;
        }
    }
    else
    {
        return RES_ERROR;
    }
    return RES_OK;
}
#endif

DWORD get_fattime()
{
    return 0b00000000001000010000000000000000;
}
