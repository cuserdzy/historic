/*
 *	ultrastor.c	(C) 1991 David B. Gentzel
 *	Low-level scsi driver for UltraStor 14F
 *	by David B. Gentzel, Whitfield Software Services, Carnegie, PA
 *	    (gentzel@nova.enet.dec.com)
 *	Thanks to UltraStor for providing the necessary documentation
 */

#ifndef _ULTRASTOR_H
#define _ULTRASTOR_H

/* ??? Some of the stuff in this file is really private to ultrastor.c and
   should be moved elsewhere (as this file is included by higher-level driver
   files). */

/* ??? These don't really belong here */
#ifndef TRUE
# define TRUE 1
#endif
#ifndef FALSE
# define FALSE 0
#endif

int ultrastor_14f_detect(int);
const char *ultrastor_14f_info(void);
#if 0	/* ??? Future direction... */
int ultrastor_14f_queuecommand(unsigned char target, const void *cmnd,
			       void *buff, int bufflen,
			       void (*done)(int, int));
#else
int ultrastor_14f_command(unsigned char target, const void *cmnd,
			  void *buff, int bufflen);
#endif
int ultrastor_14f_abort(int);
int ultrastor_14f_reset(void);

#if 0	/* ??? Future direction... */
# define ULTRASTOR_14F \
    { "UltraStor 14F", ultrastor_14f_detect, ultrastor_14f_info, 0, \
      ultrastor_14f_queuecommand, ultrastor_14f_abort, ultrastor_14f_reset, \
      TRUE, 0, 0 }
#else
# define ULTRASTOR_14F \
    { "UltraStor 14F", ultrastor_14f_detect, ultrastor_14f_info, \
      ultrastor_14f_command, 0, ultrastor_14f_abort, ultrastor_14f_reset, \
      FALSE, 0, 0 }
#endif

#define PORT_OVERRIDE 0x330

/* Port addresses (relative to the base address) */
#define LCL_DOORBELL_MASK(port) ((port) + 0x0)
#define LCL_DOORBELL_INTR(port) ((port) + 0x1)
#define SYS_DOORBELL_MASK(port) ((port) + 0x2)
#define SYS_DOORBELL_INTR(port) ((port) + 0x3)
#define PRODUCT_ID(port) ((port) + 0x4)
#define CONFIG(port) ((port) + 0x6)
#define OGM_DATA_PTR(port) ((port) + 0x8)
#define ICM_DATA_PTR(port) ((port) + 0xC)

/* Values for the PRODUCT_ID ports for the 14F */
#define US14F_PRODUCT_ID_0 0x56
#define US14F_PRODUCT_ID_1 0x40		/* NOTE: Only upper nibble is used */

/* MSCP field values */

/* Opcode */
#define OP_HOST_ADAPTER 0x1
#define OP_SCSI 0x2
#define OP_RESET 0x4

/* Date Transfer Direction */
#define DTD_SCSI 0x0
#define DTD_IN 0x1
#define DTD_OUT 0x2
#define DTD_NONE 0x3

/* Host Adapter command subcodes */
#define HA_CMD_INQUIRY 0x1
#define HA_CMD_SELF_DIAG 0x2
#define HA_CMD_READ_BUFF 0x3
#define HA_CMD_WRITE_BUFF 0x4

#endif
