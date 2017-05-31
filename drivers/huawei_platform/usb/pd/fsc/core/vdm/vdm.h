/****************************************************************************
 * Company:         Fairchild Semiconductor
 *
 * Author           Date          Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * G. Noblesmith
 *
 *
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * Software License Agreement:
 *
 * The software supplied herewith by Fairchild Semiconductor (the �Company�)
 * is supplied to you, the Company's customer, for exclusive use with its
 * USB Type C / USB PD products.  The software is owned by the Company and/or
 * its supplier, and is protected under applicable copyright laws.
 * All rights are reserved. Any use in violation of the foregoing restrictions
 * may subject the user to criminal sanctions under applicable laws, as well
 * as to civil liability for the breach of the terms and conditions of this
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN �AS IS� CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 *****************************************************************************/
#ifdef FSC_HAVE_VDM

#ifndef __VDM_MANAGER_H__
#define __VDM_MANAGER_H__

#include "../platform.h"
#include "fsc_vdm_defs.h"
#include "vdm_callbacks_defs.h"
#include "../PD_Types.h"
#include "../vendor_info.h"

#define SVID_DEFAULT SVID1_SOP
#define MODE_DEFAULT 0x0001
#define SVID_AUTO_ENTRY 0x05AC
#define MODE_AUTO_ENTRY 0x0001

#define NUM_VDM_MODES 6
#define MAX_NUM_SVIDS_PER_SOP 30
#define MAX_SVIDS_PER_MESSAGE 12
#define MIN_DISC_ID_RESP_SIZE 3

// Millisecond values ticked by 1ms timer.
#define tVDMSenderResponse 27 * 1
#define tVDMWaitModeEntry  45 * 1
#define tVDMWaitModeExit   45 * 1


/*
 * VDM Manager object, so I can have multiple instances intercommunicating using the same functions!
 */
	typedef struct {
		// callbacks!
		RequestIdentityInfo req_id_info;
		RequestSvidInfo		req_svid_info;
		RequestModesInfo	req_modes_info;
		ModeEntryRequest	req_mode_entry;
		ModeExitRequest		req_mode_exit;
		EnterModeResult		enter_mode_result;
		ExitModeResult		exit_mode_result;
		InformIdentity		inform_id;
		InformSvids			inform_svids;
		InformModes			inform_modes;
		InformAttention		inform_attention;
	} VdmManager;

/*
 * Initialization functions.
 */
	FSC_S32 initializeVdm(void);

/*
 * Functions to go through PD VDM flow.
 */
	// Initiations from DPM
	FSC_S32 requestDiscoverIdentity (SopType sop);								        // Discovers identities in the system!
	FSC_S32 requestDiscoverSvids	(SopType sop);										// Discovers SVIDs in the system!
	FSC_S32 requestDiscoverModes	(SopType sop, FSC_U16 svid);						// Discovers Modes available for each SVID
	FSC_S32 requestSendAttention	(SopType sop, FSC_U16 svid, FSC_U8 mode);			// send attention command to specified sop
	FSC_S32 requestEnterMode		(SopType sop, FSC_U16 svid, FSC_U32 mode_index);    // enter mode specified by SVID and mode index
	FSC_S32 requestExitMode			(SopType sop, FSC_U16 svid, FSC_U32 mode_index);    // exit mode specified by SVID and mode index
	FSC_S32 requestExitAllModes		(void);												// exits all modes

	// receiving end
	FSC_S32 processVdmMessage		(SopType sop, FSC_U32* arr, FSC_U32 length);        // function to call when we receive VDM messages
	FSC_S32 processDiscoverIdentity (SopType sop, FSC_U32* arr_in, FSC_U32 length_in);
    FSC_S32 processDiscoverSvids    (SopType sop, FSC_U32* arr_in, FSC_U32 length_in);
    FSC_S32 processDiscoverModes    (SopType sop, FSC_U32* arr_in, FSC_U32 length_in);
    FSC_S32 processEnterMode        (SopType sop, FSC_U32* arr_in, FSC_U32 length_in);
    FSC_S32 processExitMode         (SopType sop, FSC_U32* arr_in, FSC_U32 length_in);
    FSC_S32 processAttention        (SopType sop, FSC_U32* arr_in, FSC_U32 length_in);
    FSC_S32 processSvidSpecific     (SopType sop, FSC_U32* arr_in, FSC_U32 length_in);

	void sendVdmMessageWithTimeout  (SopType sop, FSC_U32* arr, FSC_U32 length, FSC_S32 n_pe);// for internal use
	void vdmMessageTimeout          (void);
	FSC_BOOL expectingVdmResponse   (void);
    void startVdmTimer              (FSC_S32 n_pe);
    void sendVdmMessageFailed       (void);
    void resetPolicyState           (void);

    void sendVdmMessage(SopType sop, FSC_U32 * arr, FSC_U32 length, PolicyState_t next_ps);

#endif // header guard
#endif // FSC_HAVE_VDM
