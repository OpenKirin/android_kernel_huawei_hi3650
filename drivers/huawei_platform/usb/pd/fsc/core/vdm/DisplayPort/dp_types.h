#ifdef FSC_HAVE_DP

#ifndef __DISPLAYPORT_TYPES_H__
#define __DISPLAYPORT_TYPES_H__

#include "../../platform.h"

/* DisplayPort-specific commands */
typedef enum {
	DP_COMMAND_STATUS	=	0x10,	/* Status Update */
	DP_COMMAND_CONFIG	=	0x11	/* Configure */
} DpCommand;

typedef union {
	FSC_U32 word;
	FSC_U8 byte[4] __PACKED;
	struct {
		FSC_U32     UfpDCapable:1;          /* UFP_D-capable */
        FSC_U32     DfpDCapable:1;          /* DFP_D-capable */
		FSC_U32	    SupportsDPv1p3:1;	    /* Supports DP v1.3 signaling rates and electrical spec */
		FSC_U32		SupportsUSBGen2:1;	    /* Supportd USB Gen 2 signaling rate and electrical spec */
		FSC_U32	    Rsvd0:2;
		FSC_U32	    ReceptacleIndication:1;	/* 1 = Receptacle, 0 = Plug */
		FSC_U32	    USB2p0NotUsed:1;		/* 1 = USB r2.0 signaling not required, 0 = _may_ be required */
		FSC_U32		DFP_DPinAssignA:1;		/* DFP_D Pin Assignments */
		FSC_U32		DFP_DPinAssignB:1;
		FSC_U32		DFP_DPinAssignC:1;
		FSC_U32		DFP_DPinAssignD:1;
		FSC_U32		DFP_DPinAssignE:1;
		FSC_U32		DFP_DPinAssignF:1;
		FSC_U32		DFP_DPinAssignRsvd:2;
		FSC_U32		UFP_DPinAssignA:1;		/* UFP_D Pin Assigments */
		FSC_U32		UFP_DPinAssignB:1;
		FSC_U32		UFP_DPinAssignC:1;
		FSC_U32		UFP_DPinAssignD:1;
		FSC_U32		UFP_DPinAssignE:1;
		FSC_U32		UFP_DPinAssignRsvd:3;
		FSC_U32	    Rsvd1:8;
	};
    struct {
        FSC_U32    field0:2;
        FSC_U32    field1:2;
        FSC_U32    fieldrsvd0:2;
        FSC_U32    field2:1;
        FSC_U32    field3:1;
        FSC_U32    field4:6;
        FSC_U32    fieldrsvd1:2;
        FSC_U32    field5:5;
        FSC_U32    fieldrsvd2:11;
    };
} DisplayPortCaps_t;

/* DisplayPort DFP_D/UFP_D Connected */
typedef enum {
	DP_CONN_NEITHER	= 0,	/* Neither DFP_D nor UFP_D is connected, or adaptor is disabled */
	DP_CONN_DFP_D	= 1,	/* DFP_D is connected */
	DP_CONN_UFP_D	= 2,	/* UFP_D is connected */
	DP_CONN_BOTH	= 3	/* Both DFP_D and UFP_D are connected */
} DpConn_t;

typedef union {
	FSC_U32 word;
	FSC_U8 byte[4] __PACKED;
	struct {
		DpConn_t	Connection:2;				/* Connected-to information */
		FSC_U32	    PowerLow:1;					/* Adaptor has detected low power and disabled DisplayPort support */
		FSC_U32	    Enabled:1;					/* Adaptor DisplayPort functionality is enabled and operational */
		FSC_U32	    MultiFunctionPreferred:1;	/* Multi-function preference */
		FSC_U32		UsbConfigRequest:1;			/* 0 = Maintain current configuration, 1 = request switch to USB Configuration (if in DP Config) */
		FSC_U32		ExitDpModeRequest:1;		/* 0 = Maintain current mode, 1 = Request exit from DisplayPort Mode (if in DP Mode) */
		FSC_U32		HpdState:1;					/* 0 = HPD_Low, 1 = HPD_High */
		FSC_U32	    IrqHpd:1;					/* 0 = No IRQ_HPD since last status message, 1 = IRQ_HPD */
		FSC_U32	    Rsvd:23;
	};
} DisplayPortStatus_t;

/* Select configuration */
typedef enum {
	DP_CONF_USB		= 0,	/* Set configuration for USB */
	DP_CONF_DFP_D	= 1,	/* Set configuration for UFP_U as DFP_D */
	DP_CONF_UFP_D	= 2,	/* Set configuration for UFP_U as UFP_D */
	DP_CONF_RSVD	= 3
} DpConf_t;

/* Signaling for Transport of DisplayPort Protocol */
typedef enum {
	DP_CONF_SIG_UNSPECIFIED	= 0,	/* Signaling unspecified (only for USB Configuration) */
	DP_CONF_SIG_DP_V1P3		= 1,	/* Select DP v1.3 signaling rates and electrical settings */
	DP_CONF_SIG_GEN2		= 2		/* Select Gen 2 signaling rates and electrical specifications */
} DpConfSig_t;

/* Configure UFP_U with DFP_D Pin Assignment */
typedef enum {
	DP_DFPPA_DESELECT	= 0,		/* De-select DFP_D pin assignment */
	DP_DFPPA_A			= 1,		/* Pin assignments... */
	DP_DFPPA_B			= 2,
	DP_DFPPA_C			= 4,
	DP_DFPPA_D			= 8,
	DP_DFPPA_E			= 16,
	DP_DFPPA_F			= 32
} DpDfpPa_t;

/* Configure UFP_U with UFP_D Pin Assignment */
typedef enum {
	DP_UFPPA_DESELECT	= 0,		/* De-select UFP_D pin assignment */
	DP_UFPPA_A			= 1,		/* Pin assignments... */
	DP_UFPPA_B			= 2,
	DP_UFPPA_C			= 4,
	DP_UFPPA_D			= 8,
	DP_UFPPA_E			= 16
} DpUfpPa_t;

typedef union {
	FSC_U32 word;
	FSC_U8 byte[4] __PACKED;
	struct {
		DpConf_t		Conf:2;		/* Configuration */
		DpConfSig_t		SigConf:4;	/* Signaling configuration */
		FSC_U32	        Rsvd:2;
		DpDfpPa_t		DfpPa:8;	/* Configure UFP_U with DFP_D Pin Assigment */
		DpUfpPa_t		UfpPa:8;	/* Configure UFP_U with UFP_D Pin Assignment */
	};
} DisplayPortConfig_t;

#endif  // __DISPLAYPORT_TYPES_H__

#endif // FSC_HAVE_DP
