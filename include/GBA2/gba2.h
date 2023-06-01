#ifndef GBA2_H
#define GBA2_H

#include "types.h"
#include "GBA/gba.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EAPPLI_LOAD_PROG_MAGIC 'PSAE'
#define EAPPLI_PROGRAM_CHECK_MAGIC_GC 'GAFJ'
#define EAPPLI_PROGRAM_CHECK_MAGIC_GBA 'AAFJ'

#define GBA2_GBA_STATE_ERROR -1
#define GBA2_GBA_STATE_ALREADY_EXIST 0
#define GBA2_GBA_STATE_SUCCESS 1
#define GBA2_GBA_STATE_TRANSMITTING 9

#define GBA2_EAPPLI_TRANSMITTING -1
#define GBA2_EAPPLI_SUCCESS 0
#define GBA2_EAPPLI_FAILURE_XFER_ERROR 1
#define GBA2_EAPPLI_FAILURE_NO_GBA 2

#define GBA2_SEND_RECV_TRIES 7
#define GBA2_CONNECTED_TRIES 45
#define GBA2_DEFAULT_TRIES 120
#define GBA2_READ_TRIES 1200

enum eappli_type {
  GBA2_EAPPLI_TYPE_NEEDLEWORK,  /* Able Sisters' design program */
  GBA2_EAPPLI_TYPE_MUSICSCORE,  /* Town tune editor program */
  GBA2_EAPPLI_TYPE_PTERMINAL,   /* e-Card scanning program */

  GBA2_EAPPLI_TYPE_NUM
};

enum send_eappli_state {
  SEND_EAPPLI_STATE_WAIT_FOR_GBA,                           /* GC awaits load magic (PSAE) from GBA */
  SEND_EAPPLI_STATE_GC_ACKNOWLEDGE_TO_GBA,                  /* GC sends load magic (PSAE) back to GBA to acknowledge it is there */
  SEND_EAPPLI_STATE_2,                                      /* skipped/unused state */
  SEND_EAPPLI_STATE_GC_SEND_EAPPLI_SIZE_TO_GBA,             /* GC sends eAppli program data size to GBA */
  SEND_EAPPLI_STATE_WAIT_FOR_GBA_ACKNOWLEDGED_EAPPLI_SIZE,  /* GC awaits GBA is ready for eAppli data */
  SEND_EAPPLI_STATE_GC_SEND_EAPPLI_DATA_TO_GBA,             /* GC sends eAppli data to GBA */
  SEND_EAPPLI_STATE_GC_OPEN_JOY_SIO_CONNECTION,             /* GC attempts to open connection with GBA eAppli program */
  SEND_EAPPLI_STATE_JOY_SIO_CONNECTION_OPEN                 /* GC <-> GBA connection is open */
};

enum send_eappli_status {
  SEND_EAPPLI_STATUS_SUCCESS,                   /* Program successfully sent & loaded */
  SEND_EAPPLI_STATUS_FAILED_GBA_NOT_DETECTED,   /* GBA was not detected during first stage */
  SEND_EAPPLI_STATUS_FAILED_TRANSMISSION_ERROR, /* Transmission error occurred */
  SEND_EAPPLI_STATUS_SENDING                    /* Transmission is in progress */
};

#define GBA2_MAKE_ACKNOWLEDGE_CODE(dev, state) (0xFFFE0000 | ((dev) << 8) | (state))

enum gba_gc_device {
  GBA2_DEVICE_NONE,
  GBA2_DEVICE_GC,
  GBA2_DEVICE_GBA
};

enum gba_gc_command {
  GBA2_CMD_CHECK_STATE = 1,
  GBA2_CMD_WRITE = 2,
  GBA2_CMD_START_RECV = 4,
  GBA2_CMD_VALID_CHKSUM = 6,
  GBA2_CMD_INVALID_CHKSUM = 7,
  GBA2_CMD_READY_FOR_XFER = 8,
  GBA2_CMD_XFER_START = 9,
  GBA2_CMD_XFER_FINISHED = 10,
};

typedef struct gba2_joywork_s {
  int unused0;
  
  u32 packet_block_checksum;
  u32 total_xfer_checksum;
  int packets_processed;
  int readwrite_ofs;
  
  int unused14;

  int cmd_attempts;
  
  u8 unused1C;

  u8 checksum_valid;
  u8 checksum_invalid;

  u8 unused1F;

  u8 status;
  u8 cmd_stage;
  u8 recv_state;
  u8 send_state;

  u8 port_connection_states[GBA_MAX_CHAN];

  u8 scan_state;
  u8 gba_awaiting_ack;

  int recv_wait;
} Joy_wrk_c;

extern int Port;

extern void mGcgba_Init();
extern void mGcgba_InitVar();
extern void mGcgba_EndComm();
extern int mGcgba_ConnectEnabled();
extern int mGcgba_Boot(u8* data_buf, size_t buf_size);
extern int mGcgba_IsEditor();
extern int mGcgba_IsIsland();
extern int mGcgba_Recv(u8* recv_bufp, size_t recv_buf_size);
extern int mGcgba_Read(u8* read_buf, size_t read_buf_size, u8 prog_type);
extern int mGcgba_CheckRecv(u8* recv_bufp, size_t recv_buf_size);
extern int mGcgba_Send(u8* send_bufp, size_t send_buf_size);
extern int mGcgba_send_eAppri(u8* eappli_p, size_t eappli_size);

#ifdef __cplusplus
}
#endif

#endif
