#ifndef OS_PFS_H
#define OS_PFS_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* File System error number */

#define PFS_ERR_NOPACK 1       /* no memory card is plugged or */
#define PFS_ERR_NEW_PACK 2     /* ram pack has been changed to a different one */
#define PFS_ERR_INCONSISTENT 3 /* need to run Pfschecker*/
#define PFS_ERR_CONTRFAIL CONT_OVERRUN_ERROR
#define PFS_ERR_INVALID 5     /* invalid parameter or file not exist*/
#define PFS_ERR_BAD_DATA 6    /* the data read from pack are bad*/
#define PFS_DATA_FULL 7       /* no free pages on ram pack*/
#define PFS_DIR_FULL 8        /* no free directories on ram pack*/
#define PFS_ERR_EXIST 9       /* file exists*/
#define PFS_ERR_ID_FATAL 10   /* dead ram pack */
#define PFS_ERR_DEVICE 11     /* wrong device type*/
#define PFS_ERR_NO_GBCART 12  /* no gb cartridge (64GB-PAK) */
#define PFS_ERR_NEW_GBCART 13 /* gb cartridge may be changed */

#ifdef __cplusplus
}
#endif

#endif
