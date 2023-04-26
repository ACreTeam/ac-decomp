#ifndef M_NAME_TABLE_H
#define M_NAME_TABLE_H

#include "types.h"
#include "m_actor_type.h"

/* TODO: these defintions are likely included from an auto-gen source */

#ifdef __cplusplus
extern "C" {
#endif

#define EMPTY_NO 0x0000

#define FTR_REDALOHASHIRT 0x1814
#define FTR_BLUEALOHASHIRT 0x1818

#define FTR_TAPEDECK 0x1E58

#define ITM_COLLEGERULE 0x2B00

#define FTR_ORANGEBOX 0x30F8

#define DOOR_START 0x4000
#define DOOR0 DOOR_START  /* 0x4000 */
#define DOOR1 (DOOR0 + 1) /* 0x4001 */

#define EXIT_DOOR 0x4080

#define RSV_DOOR 0xFE1B
#define RSV_WALL_NO 0xFFFE /* interior wall item, no collision */
#define RSV_NO 0xFFFF /* reserved space, can't interact but no collision */

#ifdef __cplusplus
}
#endif

#endif
