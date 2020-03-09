/****************************************************************************
*
*   Copyright (c) 2017 Windhover Labs, L.L.C. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*
* 1. Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in
*    the documentation and/or other materials provided with the
*    distribution.
* 3. Neither the name Windhover Labs nor the names of its 
*    contributors may be used to endorse or promote products derived 
*    from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
* OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
* AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
* ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
*****************************************************************************/
#include "FreeRTOS.h"
#include "ff.h"
#include "semphr.h"
#include "osapi.h"
#include <string.h>
#include <errno.h>


OS_FDTableEntry   OS_FDTable[OS_MAX_NUM_OPEN_FILES];
FIL               OS_OSFDTable[OS_MAX_NUM_OPEN_FILES];
SemaphoreHandle_t OS_FDTableMutex;
SemaphoreHandle_t OS_VolumeTableSem;


int32         OS_check_name_length(const char *path);
extern uint32 OS_FindCreator(void);



int32 OS_FS_Init(void)
{
    int i;

    /* Initialize the file system constructs */
    for (i = 0; i < OS_MAX_NUM_OPEN_FILES; i++)
    {
        OS_FDTable[i].OSfd =       -1;
        strcpy(OS_FDTable[i].Path, "\0");
        OS_FDTable[i].User =       0;
        OS_FDTable[i].IsValid =    FALSE;
    }

    OS_FDTableMutex = xSemaphoreCreateRecursiveMutex();
    if ( OS_FDTableMutex == NULL )
    {
        return OS_ERROR;
    }
    else
    {
    	OS_VolumeTableSem = xSemaphoreCreateRecursiveMutex();
        if(OS_VolumeTableSem == NULL)
        {
            return OS_ERROR;
        }
        else
        {
            return OS_SUCCESS;
        }
    }
}



int32 OS_creat(const char *path, int32 access)
{
    int    status;
    char   local_path[OS_MAX_LOCAL_PATH_LEN];
    BYTE   perm;
    uint32 PossibleFD;
    FIL    fil;

    /*
    ** Check to see if the path pointer is NULL
    */
    if (path == NULL)
    {
        return OS_FS_ERR_INVALID_POINTER;
    }

    /*
    ** Check to see if the path is too long
    */
    if (strlen(path) >= OS_MAX_PATH_LEN)
    {
        return OS_FS_ERR_PATH_TOO_LONG;
    }

    /*
    ** check if the name of the file is too long
    */
    if (OS_check_name_length(path) != OS_FS_SUCCESS)
    {
        return OS_FS_ERR_NAME_TOO_LONG;
    }

    /*
    ** Check for a valid access mode
    ** For creating a file, OS_READ_ONLY does not make sense
    */
    switch(access)
    {
        case OS_WRITE_ONLY:
            perm = FA_WRITE;
            break;
        case OS_READ_WRITE:
            perm = FA_READ | FA_WRITE;
            break;
        default:
            return OS_FS_ERROR;
    }

    /*
    ** Translate the path
    */
    if ( OS_TranslatePath(path, (char *)local_path) != OS_FS_SUCCESS )
    {
        return OS_FS_ERR_PATH_INVALID;
    }

    xSemaphoreTakeRecursive(OS_FDTableMutex, OS_INTERNAL_MUTEX_TIMEOUT);

    for ( PossibleFD = 0; PossibleFD < OS_MAX_NUM_OPEN_FILES; PossibleFD++)
    {
        if( OS_FDTable[PossibleFD].IsValid == FALSE)
        {
            break;
        }
    }

    if (PossibleFD >= OS_MAX_NUM_OPEN_FILES)
    {
        xSemaphoreGiveRecursive(OS_FDTableMutex);
        return OS_FS_ERR_NO_FREE_FDS;
    }

    /* Mark the table entry as valid so no other
     * task can take that ID */
    OS_FDTable[PossibleFD].IsValid = TRUE;

    status = f_open(&fil, local_path, FA_CREATE_ALWAYS | perm);
	if (status == FR_OK)
	{
        /* fill in the table before returning */
		OS_OSFDTable[PossibleFD] = fil;
        OS_FDTable[PossibleFD].OSfd = 0;
        strncpy(OS_FDTable[PossibleFD].Path, path, OS_MAX_PATH_LEN);
        OS_FDTable[PossibleFD].User = OS_FindCreator();
        xSemaphoreGiveRecursive(OS_FDTableMutex);
        return PossibleFD;
    }
    else
    {
        /* Operation failed, so reset to false */
        OS_FDTable[PossibleFD].IsValid = FALSE;
        xSemaphoreGiveRecursive(OS_FDTableMutex);
        return OS_FS_ERROR;
    }
}



int32 OS_open(const char *path,  int32 access,  uint32 mode)
{
    int    status;
    char   local_path[OS_MAX_LOCAL_PATH_LEN];
    BYTE   perm;
    uint32 PossibleFD;
    FIL    fil;

    /*
    ** Check to see if the path pointer is NULL
    */
    if (path == NULL)
    {
        return OS_FS_ERR_INVALID_POINTER;
    }

    /*
    ** Check to see if the path is too long
    */
    if (strlen(path) >= OS_MAX_PATH_LEN)
    {
        return OS_FS_ERR_PATH_TOO_LONG;
    }

    /*
    ** check if the name of the file is too long
    */
    if (OS_check_name_length(path) != OS_FS_SUCCESS)
    {
        return OS_FS_ERR_NAME_TOO_LONG;
    }

    /*
    ** Check for a valid access mode
    ** For creating a file, OS_READ_ONLY does not make sense
    */
    switch(access)
    {
        case OS_READ_ONLY:
            perm = FA_READ;
            break;

        case OS_WRITE_ONLY:
            perm = FA_WRITE;
            break;

        case OS_READ_WRITE:
            perm = FA_READ | FA_WRITE;
            break;

        default:
            return OS_FS_ERROR;
    }

    /*
    ** Translate the path
    */
    if ( OS_TranslatePath(path, (char *)local_path) != OS_FS_SUCCESS )
    {
        return OS_FS_ERR_PATH_INVALID;
    }

    xSemaphoreTakeRecursive(OS_FDTableMutex, OS_INTERNAL_MUTEX_TIMEOUT);

    for ( PossibleFD = 0; PossibleFD < OS_MAX_NUM_OPEN_FILES; PossibleFD++)
    {
        if( OS_FDTable[PossibleFD].IsValid == FALSE)
        {
            break;
        }
    }

    if (PossibleFD >= OS_MAX_NUM_OPEN_FILES)
    {
        xSemaphoreGiveRecursive(OS_FDTableMutex);
        return OS_FS_ERR_NO_FREE_FDS;
    }

    /* Mark the table entry as valid so no other
     * task can take that ID */
    OS_FDTable[PossibleFD].IsValid = TRUE;

    status = f_open(&fil, local_path, FA_OPEN_EXISTING | perm);
	if (status == FR_OK)
	{
        /* fill in the table before returning */
		OS_OSFDTable[PossibleFD] = fil;
        OS_FDTable[PossibleFD].OSfd = 0;
        strncpy(OS_FDTable[PossibleFD].Path, path, OS_MAX_PATH_LEN);
        OS_FDTable[PossibleFD].User = OS_FindCreator();
        xSemaphoreGiveRecursive(OS_FDTableMutex);
        return PossibleFD;
    }
    else
    {
        /* Operation failed, so reset to false */
        OS_FDTable[PossibleFD].IsValid = FALSE;
        xSemaphoreGiveRecursive(OS_FDTableMutex);
        return OS_FS_ERROR;
    }
}



int32 OS_close(int32  filedes)
{
    FRESULT status;

    /* Make sure the file descriptor is legit before using it */
    if (filedes < 0 || filedes >= OS_MAX_NUM_OPEN_FILES || OS_FDTable[filedes].IsValid == FALSE)
    {
        return OS_FS_ERR_INVALID_FD;
    }
    else
    {
        xSemaphoreTakeRecursive(OS_FDTableMutex, OS_INTERNAL_MUTEX_TIMEOUT);

        status = f_close(&OS_OSFDTable[filedes]);

        if (status == FR_OK)
        {
            /* fill in the table before returning */
            OS_FDTable[filedes].OSfd =       -1;
            strcpy(OS_FDTable[filedes].Path, "\0");
            OS_FDTable[filedes].User =       0;
            OS_FDTable[filedes].IsValid =    FALSE;

            xSemaphoreGiveRecursive(OS_FDTableMutex);

            return OS_FS_SUCCESS;
        }
        else
        {
            xSemaphoreGiveRecursive(OS_FDTableMutex);

            return OS_FS_ERROR;
        }
    }
}



int32 OS_read(int32 filedes, void *buffer, uint32 nbytes)
{
    FRESULT status;
    UINT    bytesRead;

    if (buffer == NULL)
        return OS_FS_ERR_INVALID_POINTER;

    /* Make sure the file descriptor is legit before using it */
    if (filedes < 0 || filedes >= OS_MAX_NUM_OPEN_FILES || OS_FDTable[filedes].IsValid == FALSE)
    {
        return OS_FS_ERR_INVALID_FD;
    }
    else
    {
        status = f_read(&OS_OSFDTable[filedes], buffer, nbytes, &bytesRead);

        if (status != FR_OK)
        {
            return OS_FS_ERROR;
        }
    }

    return bytesRead;
}



int32 OS_write(int32 filedes, const void *buffer, uint32 nbytes)
{
    FRESULT status;
    UINT    bytesWritten;

    if (buffer == NULL)
        return OS_FS_ERR_INVALID_POINTER;

    /* Make sure the file descriptor is legit before using it */
    if (filedes < 0 || filedes >= OS_MAX_NUM_OPEN_FILES || OS_FDTable[filedes].IsValid == FALSE)
    {
        return OS_FS_ERR_INVALID_FD;
    }
    else
    {
        status = f_write(&OS_OSFDTable[filedes], buffer, nbytes, &bytesWritten);

        if (status != FR_OK)
        {
            return OS_FS_ERROR;
        }
    }

    return bytesWritten;
}



int32 OS_chmod(const char *path, uint32 access)
{
    return OS_FS_UNIMPLEMENTED;
}



int32 OS_stat(const char *path, os_fstat_t *filestats)
{
    FRESULT status;
	FILINFO fno;
    char local_path[OS_MAX_LOCAL_PATH_LEN];

    /*
    ** Check to see if the file pointers are NULL
    */
    if (path == NULL || filestats == NULL)
    {
        return OS_FS_ERR_INVALID_POINTER;
    }

    /*
    ** Check to see if the path is too long
    */
    if (strlen(path) >= OS_MAX_PATH_LEN)
    {
        return OS_FS_ERR_PATH_TOO_LONG;
    }

    /*
    ** Translate the path
    */
    if ( OS_TranslatePath(path, (char *)local_path) != OS_FS_SUCCESS )
    {
        return OS_FS_ERR_PATH_INVALID;
    }

    status = f_stat( (char*) local_path, &fno);
    if (status == FR_OK)
    {
    	filestats->st_mtime = fno.ftime;
    	filestats->st_size = fno.fsize;
    	/* AM_RDO: Read only */
    	/* AM_HID: Hidden    */
    	/* AM_SYS: System    */
    	/* AM_ARC: Archive   */
    	/* AM_DIR: Directory */
    	if(fno.fattrib & AM_DIR)
    	{
    	    filestats->st_mode = S_IFDIR;
    	}
    	else
    	{
    	    filestats->st_mode = 0;
    	}

        return OS_FS_SUCCESS;
    }
    else
    {
        return OS_FS_ERROR;
    }
}



int32 OS_lseek(int32  filedes, int32 offset, uint32 whence)
{
	FRESULT status;

   /* Make sure the file descriptor is legit before using it */
   if (filedes < 0 || filedes >= OS_MAX_NUM_OPEN_FILES || OS_FDTable[filedes].IsValid == FALSE)
   {
       return OS_FS_ERR_INVALID_FD;
   }
   else
   {
	   if(whence != OS_SEEK_SET)
	   {
           return OS_FS_ERROR;
	   }


       status = f_lseek(&OS_OSFDTable[filedes], offset);

       if (status == FR_OK)
           return (int32) status;
       else
           return OS_FS_ERROR;
   }
}



int32 OS_remove(const char *path)
{
    int  i;
    FRESULT  status;
    char local_path[OS_MAX_LOCAL_PATH_LEN];

    /*
    ** Check to see if the path pointer is NULL
    */
    if (path == NULL)
    {
        return OS_FS_ERR_INVALID_POINTER;
    }

    /*
    ** Check to see if the path is too long
    */
    if (strlen(path) >= OS_MAX_PATH_LEN)
    {
        return OS_FS_ERR_PATH_TOO_LONG;
    }

    /*
    ** check if the name of the file is too long
    */
    if (OS_check_name_length(path) != OS_FS_SUCCESS)
    {
        return OS_FS_ERR_NAME_TOO_LONG;
    }

    /*
    ** Make sure the file is not open by the OSAL before deleting it
    */
    for ( i =0; i < OS_MAX_NUM_OPEN_FILES; i++)
    {
       if ((OS_FDTable[i].IsValid == TRUE) &&
          (strcmp(OS_FDTable[i].Path, path) == 0))
       {
          return OS_FS_ERROR;
       }
    }

    /*
    ** Translate the path
    */
    if ( OS_TranslatePath(path, (char *)local_path) != OS_FS_SUCCESS )
    {
        return OS_FS_ERR_PATH_INVALID;
    }

    /*
    ** Call the system to remove the file
    */
    status = f_unlink(local_path);
    if (status == 0)
    {
        return OS_FS_SUCCESS;
    }
    else
    {
        return OS_FS_ERROR;
    }

}



int32 OS_rename(const char *old_filename, const char *new_filename)
{
    FRESULT status;
    int     i;
    char    old_path[OS_MAX_LOCAL_PATH_LEN];
    char    new_path[OS_MAX_LOCAL_PATH_LEN];

    /*
    ** Check to see if the path pointers are NULL
    */
    if (old_filename == NULL || new_filename == NULL)
        return OS_FS_ERR_INVALID_POINTER;

    /*
    ** Check to see if the paths are too long
    */
    if (strlen(old_filename) >= OS_MAX_PATH_LEN)
        return OS_FS_ERR_PATH_TOO_LONG;

    if (strlen(new_filename) >= OS_MAX_PATH_LEN)
        return OS_FS_ERR_PATH_TOO_LONG;

    /*
    ** check if the names of the files are too long
    */
    if (OS_check_name_length(old_filename) != OS_FS_SUCCESS)
        return OS_FS_ERR_NAME_TOO_LONG;

    if (OS_check_name_length(new_filename) != OS_FS_SUCCESS)
        return OS_FS_ERR_NAME_TOO_LONG;


    /*
    ** Translate the path
    */
    if ( OS_TranslatePath(old_filename, (char *)old_path) != OS_FS_SUCCESS )
    {
        return OS_FS_ERR_PATH_INVALID;
    }

    /*
    ** Translate the path
    */
    if ( OS_TranslatePath(new_filename, (char *)new_path) != OS_FS_SUCCESS )
    {
        return OS_FS_ERR_PATH_INVALID;
    }

    status = f_rename(old_path, new_path);
    if (status == FR_OK)
    {
        for ( i =0; i < OS_MAX_NUM_OPEN_FILES; i++)
        {
            if (strcmp(OS_FDTable[i].Path, old_filename) == 0 &&
                OS_FDTable[i].IsValid == TRUE)
            {
                strncpy (OS_FDTable[i].Path, new_filename, OS_MAX_PATH_LEN);
            }
        }
        return OS_FS_SUCCESS;
    }
    else
    {
        return OS_FS_ERROR;
    }
}



int32 OS_cp(const char *src, const char *dest)
{
    int  i;
    FRESULT status;
    char src_path[OS_MAX_LOCAL_PATH_LEN];
    char dest_path[OS_MAX_LOCAL_PATH_LEN];
    FIL  srcFil;
    FIL  dstFil;

    /*
    ** Check to see if the path pointers are NULL
    */
    if (src == NULL || dest == NULL)
    {
        return OS_FS_ERR_INVALID_POINTER;
    }

    /*
    ** Check to see if the paths are too long
    */
    if (strlen(src) >= OS_MAX_PATH_LEN)
    {
        return OS_FS_ERR_PATH_TOO_LONG;
    }

    if (strlen(dest) >= OS_MAX_PATH_LEN)
    {
        return OS_FS_ERR_PATH_TOO_LONG;
    }

    /*
    ** check if the names of the files are too long
    */
    if (OS_check_name_length(src) != OS_FS_SUCCESS)
    {
        return OS_FS_ERR_NAME_TOO_LONG;
    }

    if (OS_check_name_length(dest) != OS_FS_SUCCESS)
    {
        return OS_FS_ERR_NAME_TOO_LONG;
    }

    /*
    ** Make sure the destintation file is not open by the OSAL before doing the copy
    ** This may be caught by the host OS call but it does not hurt to
    ** be consistent
    */
    for ( i =0; i < OS_MAX_NUM_OPEN_FILES; i++)
    {
        if ((OS_FDTable[i].IsValid == TRUE) &&
           (strcmp(OS_FDTable[i].Path, dest) == 0))
        {
           return OS_FS_ERROR;
        }
    }

    /*
    ** Translate the path
    */
    if ( OS_TranslatePath(src, (char *)src_path) != OS_FS_SUCCESS )
    {
        return OS_FS_ERR_PATH_INVALID;
    }

    /*
    ** Translate the path
    */
    if ( OS_TranslatePath(dest, (char *)dest_path) != OS_FS_SUCCESS )
    {
        return OS_FS_ERR_PATH_INVALID;
    }

    /* BUFSIZE defaults to 8192
    ** BUFSIZE of 1 means one chareter at time
    ** good values should fit to blocksize, like 1024 or 4096
    ** higher values reduce number of system calls
    */
    char buf[BUFSIZ];
    size_t size = 0;
    UINT   bytesRead = 0;
    UINT   bytesWritten = 0;

    status = f_open(&srcFil, src_path, FA_READ);
    if(status == FR_OK)
    {
        return OS_FS_ERROR;
    }
    status = f_open(&dstFil, dest_path, FA_WRITE | FA_CREATE_ALWAYS);
    if(status == FR_OK)
    {
        f_close(&srcFil);
        return OS_FS_ERROR;
    }

    f_read(&srcFil, buf, BUFSIZ, &bytesRead);
    while (bytesRead > 0)
    {
    	status = f_write(&dstFil, buf, size, &bytesWritten);
        if (status == FR_OK)
	    {
	        f_close(&srcFil);
	        f_close(&dstFil);
            return OS_FS_ERROR;
	    }

        f_read(&srcFil, buf, BUFSIZ, &bytesRead);
    }

    f_close(&srcFil);
    f_close(&dstFil);

    return OS_FS_SUCCESS;

}



int32 OS_mv(const char *src, const char *dest)
{
    int i;
    int32 status;

    /*
    ** Validate the source and destination
    ** These checks may seem redundant because OS_cp and OS_remove also do
    ** the same checks, but this call needs to abort before doing a copy
    ** in some cases.
    */

    /*
    ** Check to see if the path pointers are NULL
    */
    if (src == NULL || dest == NULL)
    {
        return OS_FS_ERR_INVALID_POINTER;
    }

    /*
    ** Check to see if the paths are too long
    */
    if (strlen(src) >= OS_MAX_PATH_LEN)
    {
        return OS_FS_ERR_PATH_TOO_LONG;
    }

    if (strlen(dest) >= OS_MAX_PATH_LEN)
    {
        return OS_FS_ERR_PATH_TOO_LONG;
    }

    /*
    ** check if the names of the files are too long
    */
    if (OS_check_name_length(src) != OS_FS_SUCCESS)
    {
        return OS_FS_ERR_NAME_TOO_LONG;
    }

    if (OS_check_name_length(dest) != OS_FS_SUCCESS)
    {
        return OS_FS_ERR_NAME_TOO_LONG;
    }

    /*
    ** Make sure the source file is not open by the OSAL before doing the move
    */
    for ( i =0; i < OS_MAX_NUM_OPEN_FILES; i++)
    {
        if ((OS_FDTable[i].IsValid == TRUE) &&
            (strcmp(OS_FDTable[i].Path, src) == 0))
        {
            return OS_FS_ERROR;
        }
    }

    status = OS_cp (src, dest);
    if ( status == OS_FS_SUCCESS )
    {
        status = OS_remove(src);
    }

    return ( status);
}



int32 OS_FDGetInfo(int32 filedes, OS_FDTableEntry *fd_prop)
{
    if (fd_prop == NULL)
    {
        return(OS_FS_ERR_INVALID_POINTER);
    }

    /* Make sure the file descriptor is legit before using it */
    if (filedes < 0 || filedes >= OS_MAX_NUM_OPEN_FILES || OS_FDTable[filedes].IsValid == FALSE)
    {
       (*(fd_prop)).IsValid = FALSE;
        return OS_FS_ERR_INVALID_FD;
    }
    else
    {
        *fd_prop = OS_FDTable[filedes];
        return OS_FS_SUCCESS;
    }
}



int32 OS_FileOpenCheck(char *Filename)
{
    uint32 i;

    if (Filename == NULL)
    {
        return(OS_FS_ERR_INVALID_POINTER);
    }

    xSemaphoreTakeRecursive(OS_FDTableMutex, OS_INTERNAL_MUTEX_TIMEOUT);

    for ( i = 0; i < OS_MAX_NUM_OPEN_FILES; i++)
    {
        if ((OS_FDTable[i].IsValid == TRUE) &&  (strcmp(OS_FDTable[i].Path, Filename) == 0))
        {
            xSemaphoreGiveRecursive(OS_FDTableMutex);
            return(OS_FS_SUCCESS);
        }
    }/* end for */

    xSemaphoreGiveRecursive(OS_FDTableMutex);

    return OS_FS_ERROR;
}



int32 OS_CloseAllFiles(void)
{
    uint32   i;
    int32    return_status = OS_FS_SUCCESS;
    FRESULT  status;

    xSemaphoreTakeRecursive(OS_FDTableMutex, OS_INTERNAL_MUTEX_TIMEOUT);

    for ( i = 0; i < OS_MAX_NUM_OPEN_FILES; i++)
    {
        if ( OS_FDTable[i].IsValid == TRUE )
        {
            /*
            ** Close the file
            */
            status = f_close(&OS_OSFDTable[i]);

            /*
            ** Next, remove the file from the OSAL list
            ** to free up that slot
            */
            OS_FDTable[i].OSfd =       -1;
            strcpy(OS_FDTable[i].Path, "\0");
            OS_FDTable[i].User =       0;
            OS_FDTable[i].IsValid =    FALSE;

            if (status != FR_OK)
            {
                return_status = OS_FS_ERROR;
            }
        }
    }/* end for */

    xSemaphoreGiveRecursive(OS_FDTableMutex);

    return (return_status);
}



int32 OS_CloseFileByName(char *Filename)
{
    uint32    i;
    FRESULT  status;

    if (Filename == NULL)
    {
        return(OS_FS_ERR_INVALID_POINTER);
    }

    xSemaphoreTakeRecursive(OS_FDTableMutex, OS_INTERNAL_MUTEX_TIMEOUT);

    for ( i = 0; i < OS_MAX_NUM_OPEN_FILES; i++)
    {
        if ((OS_FDTable[i].IsValid == TRUE) &&  (strcmp(OS_FDTable[i].Path, Filename) == 0))
        {
           /*
           ** Close the file
           */
           status = f_close(&OS_OSFDTable[i]);

           /*
           ** Next, remove the file from the OSAL list
           ** to free up that slot
           */
           OS_FDTable[i].OSfd =       -1;
           strcpy(OS_FDTable[i].Path, "\0");
           OS_FDTable[i].User =       0;
           OS_FDTable[i].IsValid =    FALSE;
           xSemaphoreGiveRecursive(OS_FDTableMutex);

           if (status == FR_OK)
           {
              return(OS_FS_SUCCESS);
           }
           else
           {
              return(OS_FS_ERROR);
           }
        }

    }/* end for */

    xSemaphoreGiveRecursive(OS_FDTableMutex);

    return (OS_FS_ERR_PATH_INVALID);
}


/******************************************************************************
** Directory API
******************************************************************************/

int32 OS_mkdir(const char *path, uint32 access)
{
    FRESULT status;
    char    local_path[OS_MAX_LOCAL_PATH_LEN];

    /*
    ** Check to see if the path pointer is NULL
    */
    if (path == NULL)
    {
        return OS_FS_ERR_INVALID_POINTER;
    }

    /*
    ** Check to see if the path is too long
    */
    if (strlen(path) >= OS_MAX_PATH_LEN)
    {
        return OS_FS_ERR_PATH_TOO_LONG;
    }

    /*
    ** Translate the path
    */
    if ( OS_TranslatePath(path, (char *)local_path) != OS_FS_SUCCESS )
    {
        return OS_FS_ERR_PATH_INVALID;
    }

    status = f_mkdir(local_path);

    if (status == 0)
    {
        return OS_FS_SUCCESS;
    }
    else
    {
        return OS_FS_ERROR;
    }
}



os_dirp_t OS_opendir(const char *path)
{
    FRESULT    status;
    static DIR osDirDesc;
    char       local_path[OS_MAX_LOCAL_PATH_LEN];

    /*
    ** Check to see if the path pointer is NULL
    */
    if (path == NULL)
    {
        return NULL;
    }

    /*
    ** Check to see if the path is too long
    */
    if (strlen(path) > OS_MAX_PATH_LEN)
    {
        return NULL;
    }

    /*
    ** Translate the path
    */
    if ( OS_TranslatePath(path, (char *)local_path) != OS_FS_SUCCESS )
    {
        return NULL;
    }

    status = f_opendir(&osDirDesc, (char*) local_path);

    if (status != FR_OK)
    {
        return NULL;
    }
    else
    {
        return (os_dirp_t)&osDirDesc;
    }
}



int32 OS_closedir(os_dirp_t dirHandle)
{
    FRESULT status;

    if (dirHandle == NULL)
    {
        return OS_FS_ERR_INVALID_POINTER;
    }

    status = f_closedir((DIR*)dirHandle);
    if (status == FR_OK)
    {
    	dirHandle = NULL;
        return OS_FS_SUCCESS;
    }
    else
    {
        return OS_FS_ERROR;
    }
}



void OS_rewinddir(os_dirp_t directory)
{
    if (directory != NULL)
    {
       /* TODO:  Log this as not implemented. */
    }
}



os_dirent_t* OS_readdir(os_dirp_t dirHandle)
{
    FRESULT status;
    FILINFO fno;
    static os_dirent_t dirent;

    if (dirHandle == NULL)
    {
        return NULL;
    }

    status = f_readdir((DIR*)dirHandle, &fno);
    if (status == FR_OK)
    {
    	if(fno.fname[0] == 0)
    	{
    		return NULL;
    	}

        strcpy(dirent.d_name, fno.fname);
        if(fno.fattrib & AM_DIR)
        {
        	dirent.d_type = DT_DIR;
        }
        else
        {
        	dirent.d_type = DT_FILE;
        }

        return &dirent;
    }
    else
    {
        return NULL;
    }
}



int32 OS_rmdir(const char *path)
{
    FRESULT status;
    char    local_path [OS_MAX_LOCAL_PATH_LEN];

    /*
    ** Check to see if the path pointer is NULL
    */
    if (path == NULL)
    {
        return OS_FS_ERR_INVALID_POINTER;
    }

    /*
    ** Check to see if the path is too long
    */
    if (strlen(path) >= OS_MAX_PATH_LEN)
    {
        return OS_FS_ERR_PATH_TOO_LONG;
    }

    /*
    ** Translate the path
    */
    if ( OS_TranslatePath(path, (char *)local_path) != OS_FS_SUCCESS )
    {
        return OS_FS_ERR_PATH_INVALID;
    }

    status = f_rmdir(local_path);

    if (status == FR_OK)
    {
        return OS_FS_SUCCESS;
    }
    else
    {
        return OS_FS_ERROR;
    }
}




/******************************************************************************
** Shell API
******************************************************************************/

int32 OS_ShellOutputToFile(const char* Cmd, int32 OS_fd)
{
    return OS_FS_UNIMPLEMENTED;
}



int32 OS_check_name_length(const char *path)
{
    char* name_ptr;
    char* end_of_path;
    int name_len;

    if (path == NULL)
        return OS_FS_ERR_INVALID_POINTER;


    if (strlen(path) > OS_MAX_PATH_LEN)
        return OS_FS_ERROR;
    /* checks to see if there is a '/' somewhere in the path */
    name_ptr = strrchr(path, '/');
    if (name_ptr == NULL)
        return OS_FS_ERROR;

    /* strrchr returns a pointer to the last '/' char, so we advance one char */
    name_ptr = name_ptr + sizeof(char);

    /* end_of_path points to the null terminator at the end of the path */
    end_of_path = strrchr(path,'\0');

    /* pointer subraction to see how many characters there are in the name */
    name_len = ((int) end_of_path - (int)name_ptr) / sizeof(char);

    if( name_len > OS_MAX_FILE_NAME)
    {
        return OS_FS_ERROR;
    }

    return OS_FS_SUCCESS;

}/* end OS_check_name_length */
