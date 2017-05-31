/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
WARNING: This header file is auto-generated, DO NOT modify it manually
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

#ifndef _IMONITOR_KEYS_H_
#define _IMONITOR_KEYS_H_

#ifdef __cplusplus
extern "C" {
#endif

/*** Reliability events' keys ***/

	/* Event 901000000
		Android Vmreboot */
	/* Process Name */
	#define E901000000_PNAME_VARCHAR 0
	/* 1st fuction in stack */
	#define E901000000_F1NAME_VARCHAR 1
	/* 2nd function in stack */
	#define E901000000_F2NAME_VARCHAR 2
	/* Interrupt Time Type */
	#define E901000000_INTTIMETYPE_VARCHAR 3

	/* Event 901000001
		Vm Watchdog */
	/* Process Name */
	#define E901000001_PNAME_VARCHAR 0
	/* Blocked Thread Name */
	#define E901000001_BTHREAD1NAME_VARCHAR 1
	/* Interrupt Time Type */
	#define E901000001_INTTIMETYPE_VARCHAR 2

	/* Event 901000002
		Panic */
	/* Sub Type for This Error */
	#define E901000002_NAME_VARCHAR 0
	/* Process Name */
	#define E901000002_PNAME_VARCHAR 1
	/* 1st fuction in stack */
	#define E901000002_F1NAME_VARCHAR 2
	/* CPU Frequency */
	#define E901000002_CPUFREQ_VARCHAR 3
	/* AVS Parameter */
	#define E901000002_AVSPARAM_VARCHAR 4
	/* Interrupt Time Type */
	#define E901000002_INTTIMETYPE_VARCHAR 5

	/* Event 901000003
		Hw Watchdog */
	/* Sub Type for This Error */
	#define E901000003_NAME_VARCHAR 0
	/* CPU Frequency */
	#define E901000003_CPUFREQ_VARCHAR 1
	/* AVS Parameter */
	#define E901000003_AVSPARAM_VARCHAR 2
	/* Interrupt Time Type */
	#define E901000003_INTTIMETYPE_VARCHAR 3

	/* Event 901000004
		Powerclaspse */
	/* Sub Type for This Error */
	#define E901000004_NAME_VARCHAR 0
	/* CPU Frequency */
	#define E901000004_CPUFREQ_VARCHAR 1
	/* AVS Parameter */
	#define E901000004_AVSPARAM_VARCHAR 2
	/* Interrupt Time Type */
	#define E901000004_INTTIMETYPE_VARCHAR 3

	/* Event 901000005
		Hardware Fault */
	/* Fault Device Name */
	#define E901000005_HNAME_VARCHAR 0
	/* CPU Frequency */
	#define E901000005_CPUFREQ_VARCHAR 1
	/* AVS Parameter */
	#define E901000005_AVSPARAM_VARCHAR 2
	/* Interrupt Time Type */
	#define E901000005_INTTIMETYPE_VARCHAR 3

	/* Event 901001000
		ANR */
	/* Process Name */
	#define E901001000_PNAME_VARCHAR 0
	/* 1st fuction in stack */
	#define E901001000_F1NAME_VARCHAR 1
	/* Process Name take top CPU */
	#define E901001000_PTOPCPU_VARCHAR 2
	/* System take total cpu */
	#define E901001000_TOTALCPU_INT 3
	/* System take iowait cpu */
	#define E901001000_IOWAITCPU_INT 4
	/* APP Version */
	#define E901001000_APPVERSION_VARCHAR 5
	/* APP Type */
	#define E901001000_APPTYPE_VARCHAR 6
	/* Interrupt Time Type */
	#define E901001000_INTTIMETYPE_VARCHAR 7

	/* Event 901001001
		Crash */
	/* Process Name */
	#define E901001001_PNAME_VARCHAR 0
	/* 1st fuction in stack */
	#define E901001001_F1NAME_VARCHAR 1
	/* 2nd function in stack */
	#define E901001001_F2NAME_VARCHAR 2
	/* APP Version */
	#define E901001001_APPVERSION_VARCHAR 3
	/* APP Type */
	#define E901001001_APPTYPE_VARCHAR 4
	/* Interrupt Time Type */
	#define E901001001_INTTIMETYPE_VARCHAR 5

	/* Event 901001002
		Tomestone */
	/* Process Name */
	#define E901001002_PNAME_VARCHAR 0
	/* 1st fuction in stack */
	#define E901001002_F1NAME_VARCHAR 1
	/* Signal Num */
	#define E901001002_SIGNALNUM_INT 2
	/* APP Version */
	#define E901001002_APPVERSION_VARCHAR 3
	/* APP Type */
	#define E901001002_APPTYPE_VARCHAR 4
	/* Interrupt Time Type */
	#define E901001002_INTTIMETYPE_VARCHAR 5

	/* Event 901002000
		Modem Crash */
	/* Process Name */
	#define E901002000_PNAME_VARCHAR 0
	/* 1st fuction in stack */
	#define E901002000_F1NAME_VARCHAR 1
	/* Interrupt Time Type */
	#define E901002000_INTTIMETYPE_VARCHAR 2

	/* Event 901002001
		Hifi Crash */
	/* Process Name */
	#define E901002001_PNAME_VARCHAR 0
	/* 1st fuction in stack */
	#define E901002001_F1NAME_VARCHAR 1
	/* Interrupt Time Type */
	#define E901002001_INTTIMETYPE_VARCHAR 2

	/* Event 901002002
		Sensorhub Crash */
	/* Process Name */
	#define E901002002_PNAME_VARCHAR 0
	/* 1st fuction in stack */
	#define E901002002_F1NAME_VARCHAR 1
	/* Interrupt Time Type */
	#define E901002002_INTTIMETYPE_VARCHAR 2

	/* Event 901002003
		Tee OS Crash */
	/* Process Name */
	#define E901002003_PNAME_VARCHAR 0
	/* 1st fuction in stack */
	#define E901002003_F1NAME_VARCHAR 1
	/* Interrupt Time Type */
	#define E901002003_INTTIMETYPE_VARCHAR 2

	/* Event 901002004
		Wcnss/Adsp/Venus Crash */
	/* Process Name */
	#define E901002004_PNAME_VARCHAR 0
	/* 1st fuction in stack */
	#define E901002004_F1NAME_VARCHAR 1
	/* Interrupt Time Type */
	#define E901002004_INTTIMETYPE_VARCHAR 2

	/* Event 901003000
		Thread Limit */
	/* Process Name */
	#define E901003000_PNAME_VARCHAR 0
	/* Thread Name */
	#define E901003000_TNAME_VARCHAR 1
	/* Thread Num */
	#define E901003000_TNUM_INT 2
	/* APP Version */
	#define E901003000_APPVERSION_VARCHAR 3
	/* APP Type */
	#define E901003000_APPTYPE_VARCHAR 4

	/* Event 901003001
		File Handler Limit */
	/* Process Name */
	#define E901003001_PNAME_VARCHAR 0
	/* File Name */
	#define E901003001_TNAME_VARCHAR 1
	/* File Num */
	#define E901003001_TNUM_INT 2
	/* APP Version */
	#define E901003001_APPVERSION_VARCHAR 3
	/* APP Type */
	#define E901003001_APPTYPE_VARCHAR 4

	/* Event 901003002
		Memory Limit */
	/* Process Name */
	#define E901003002_PNAME_VARCHAR 0
	/* APP Version */
	#define E901003002_APPVERSION_VARCHAR 1
	/* APP Type */
	#define E901003002_APPTYPE_VARCHAR 2

	/* Event 901004000
		UI Freeze */
	/* Process Name */
	#define E901004000_PNAME_VARCHAR 0
	/* Process Name take top CPU */
	#define E901004000_PTOPCPU_VARCHAR 1
	/* System take total cpu */
	#define E901004000_TOTALCPU_INT 2
	/* System take iowait cpu */
	#define E901004000_IOWAITCPU_INT 3
	/* CPU Frequency */
	#define E901004000_CPUFREQ_VARCHAR 4
	/* AVS Parameter */
	#define E901004000_AVSPARAM_VARCHAR 5
	/* Interrupt Time Type */
	#define E901004000_INTTIMETYPE_VARCHAR 6

	/* Event 901004001
		Black Screen */
	/* Process Name */
	#define E901004001_PNAME_VARCHAR 0
	/* Process Name take top CPU */
	#define E901004001_PTOPCPU_VARCHAR 1
	/* System take total cpu */
	#define E901004001_TOTALCPU_INT 2
	/* System take iowait cpu */
	#define E901004001_IOWAITCPU_INT 3
	/* CPU Frequency */
	#define E901004001_CPUFREQ_VARCHAR 4
	/* AVS Parameter */
	#define E901004001_AVSPARAM_VARCHAR 5
	/* Interrupt Time Type */
	#define E901004001_INTTIMETYPE_VARCHAR 6

	/* Event 901005000
		Boot Fail Error */
	/* Boot Error Number */
	#define E901005000_BOOTERRNO_INT 0
	/* Boot Error Stage */
	#define E901005000_BOOTSTAGE_VARCHAR 1
	/* Recovery Select */
	#define E901005000_RECSELECT_VARCHAR 2
	/* Recovery Result */
	#define E901005000_RECRESULT_VARCHAR 3
	/* Root or Not */
	#define E901005000_ROOTORNOT_VARCHAR 4
	/* Boot Error Number */
	#define E901005000_BOOTERRORNO_VARCHAR 5
	/* Is User Perceptible */
	#define E901005000_ISUSERPERCEPTIBLE_VARCHAR 6
	/* Interrupt Time Type */
	#define E901005000_INTTIMETYPE_VARCHAR 7

/*** Performance events' keys ***/

	/* Event 902000000
		Key Application launching slowly */
	/* Performance Scene Name */
	#define E902000000_CASENAME_VARCHAR 0
	/* Error Level */
	#define E902000000_RESULT_INT 1
	/*  */
	#define E902000000_TOTALTIMESPENT_INT 2
	/*  */
	#define E902000000_ARG1_VARCHAR 3
	/*  */
	#define E902000000_ARG2_INT 4
	/*  */
	#define E902000000_VERSION_VARCHAR 5
	/*  */
	#define E902000000_CPULOAD_INT 6
	/*  */
	#define E902000000_CLTOP_PROC1_VARCHAR 7
	/*  */
	#define E902000000_CLPROC1_VAL_INT 8
	/*  */
	#define E902000000_CLTOP_PROC2_VARCHAR 9
	/*  */
	#define E902000000_CLPROC2_VAL_INT 10
	/*  */
	#define E902000000_CLTOP_PROC3_VARCHAR 11
	/*  */
	#define E902000000_CLPROC3_VAL_INT 12
	/*  */
	#define E902000000_FREEMEM_INT 13
	/*  */
	#define E902000000_FREEDISK_INT 14
	/*  */
	#define E902000000_LIMIT_FREQ_INT 15
	/*  */
	#define E902000000_BROOTED_INT 16
	/*  */
	#define E902000000_BMODEMLOGON_INT 17
	/*  */
	#define E902000000_BUARTENABL_INT 18
	/*  */
	#define E902000000_NPERFBUGSETTINGS_INT 19
	/*  */
	#define E902000000_IAWARE_INT 20
	/*  */
	#define E902000000_NRESERVE1_INT 21
	/*  */
	#define E902000000_STRRESERVE2_VARCHAR 22

	/* Event 902000001
		Wechat launching slowly */
	/* Performance Scene Name */
	#define E902000001_CASENAME_VARCHAR 0
	/* Error Level */
	#define E902000001_RESULT_INT 1
	/*  */
	#define E902000001_TOTALTIMESPENT_INT 2
	/*  */
	#define E902000001_ARG1_VARCHAR 3
	/*  */
	#define E902000001_ARG2_INT 4
	/*  */
	#define E902000001_VERSION_VARCHAR 5
	/*  */
	#define E902000001_CPULOAD_INT 6
	/*  */
	#define E902000001_CLTOP_PROC1_VARCHAR 7
	/*  */
	#define E902000001_CLPROC1_VAL_INT 8
	/*  */
	#define E902000001_CLTOP_PROC2_VARCHAR 9
	/*  */
	#define E902000001_CLPROC2_VAL_INT 10
	/*  */
	#define E902000001_CLTOP_PROC3_VARCHAR 11
	/*  */
	#define E902000001_CLPROC3_VAL_INT 12
	/*  */
	#define E902000001_FREEMEM_INT 13
	/*  */
	#define E902000001_FREEDISK_INT 14
	/*  */
	#define E902000001_LIMIT_FREQ_INT 15
	/*  */
	#define E902000001_BROOTED_INT 16
	/*  */
	#define E902000001_BMODEMLOGON_INT 17
	/*  */
	#define E902000001_BUARTENABL_INT 18
	/*  */
	#define E902000001_NPERFBUGSETTINGS_INT 19
	/*  */
	#define E902000001_IAWARE_INT 20
	/*  */
	#define E902000001_NRESERVE1_INT 21
	/*  */
	#define E902000001_STRRESERVE2_VARCHAR 22

	/* Event 902000002
		Huawei Application launching slowly */
	/* Performance Scene Name */
	#define E902000002_CASENAME_VARCHAR 0
	/* Error Level */
	#define E902000002_RESULT_INT 1
	/*  */
	#define E902000002_TOTALTIMESPENT_INT 2
	/*  */
	#define E902000002_ARG1_VARCHAR 3
	/*  */
	#define E902000002_ARG2_INT 4
	/*  */
	#define E902000002_VERSION_VARCHAR 5
	/*  */
	#define E902000002_CPULOAD_INT 6
	/*  */
	#define E902000002_CLTOP_PROC1_VARCHAR 7
	/*  */
	#define E902000002_CLPROC1_VAL_INT 8
	/*  */
	#define E902000002_CLTOP_PROC2_VARCHAR 9
	/*  */
	#define E902000002_CLPROC2_VAL_INT 10
	/*  */
	#define E902000002_CLTOP_PROC3_VARCHAR 11
	/*  */
	#define E902000002_CLPROC3_VAL_INT 12
	/*  */
	#define E902000002_FREEMEM_INT 13
	/*  */
	#define E902000002_FREEDISK_INT 14
	/*  */
	#define E902000002_LIMIT_FREQ_INT 15
	/*  */
	#define E902000002_BROOTED_INT 16
	/*  */
	#define E902000002_BMODEMLOGON_INT 17
	/*  */
	#define E902000002_BUARTENABL_INT 18
	/*  */
	#define E902000002_NPERFBUGSETTINGS_INT 19
	/*  */
	#define E902000002_IAWARE_INT 20
	/*  */
	#define E902000002_NRESERVE1_INT 21
	/*  */
	#define E902000002_STRRESERVE2_VARCHAR 22

	/* Event 902000003
		Third-Party application launching slowly */
	/* Performance Scene Name */
	#define E902000003_CASENAME_VARCHAR 0
	/* Error Level */
	#define E902000003_RESULT_INT 1
	/*  */
	#define E902000003_TOTALTIMESPENT_INT 2
	/*  */
	#define E902000003_ARG1_VARCHAR 3
	/*  */
	#define E902000003_ARG2_INT 4
	/*  */
	#define E902000003_VERSION_VARCHAR 5
	/*  */
	#define E902000003_CPULOAD_INT 6
	/*  */
	#define E902000003_CLTOP_PROC1_VARCHAR 7
	/*  */
	#define E902000003_CLPROC1_VAL_INT 8
	/*  */
	#define E902000003_CLTOP_PROC2_VARCHAR 9
	/*  */
	#define E902000003_CLPROC2_VAL_INT 10
	/*  */
	#define E902000003_CLTOP_PROC3_VARCHAR 11
	/*  */
	#define E902000003_CLPROC3_VAL_INT 12
	/*  */
	#define E902000003_FREEMEM_INT 13
	/*  */
	#define E902000003_FREEDISK_INT 14
	/*  */
	#define E902000003_LIMIT_FREQ_INT 15
	/*  */
	#define E902000003_BROOTED_INT 16
	/*  */
	#define E902000003_BMODEMLOGON_INT 17
	/*  */
	#define E902000003_BUARTENABL_INT 18
	/*  */
	#define E902000003_NPERFBUGSETTINGS_INT 19
	/*  */
	#define E902000003_IAWARE_INT 20
	/*  */
	#define E902000003_NRESERVE1_INT 21
	/*  */
	#define E902000003_STRRESERVE2_VARCHAR 22

	/* Event 902010000
		Key Application skip frames */
	/* Performance Scene Name */
	#define E902010000_CASENAME_VARCHAR 0
	/* Error Level */
	#define E902010000_RESULT_INT 1
	/*  */
	#define E902010000_TOTALTIMESPENT_INT 2
	/*  */
	#define E902010000_ARG1_VARCHAR 3
	/*  */
	#define E902010000_ARG2_INT 4
	/*  */
	#define E902010000_VERSION_VARCHAR 5
	/*  */
	#define E902010000_CPULOAD_INT 6
	/*  */
	#define E902010000_CLTOP_PROC1_VARCHAR 7
	/*  */
	#define E902010000_CLPROC1_VAL_INT 8
	/*  */
	#define E902010000_CLTOP_PROC2_VARCHAR 9
	/*  */
	#define E902010000_CLPROC2_VAL_INT 10
	/*  */
	#define E902010000_CLTOP_PROC3_VARCHAR 11
	/*  */
	#define E902010000_CLPROC3_VAL_INT 12
	/*  */
	#define E902010000_FREEMEM_INT 13
	/*  */
	#define E902010000_FREEDISK_INT 14
	/*  */
	#define E902010000_LIMIT_FREQ_INT 15
	/*  */
	#define E902010000_BROOTED_INT 16
	/*  */
	#define E902010000_BMODEMLOGON_INT 17
	/*  */
	#define E902010000_BUARTENABL_INT 18
	/*  */
	#define E902010000_NPERFBUGSETTINGS_INT 19
	/*  */
	#define E902010000_IAWARE_INT 20
	/*  */
	#define E902010000_NRESERVE1_INT 21
	/*  */
	#define E902010000_STRRESERVE2_VARCHAR 22

	/* Event 902010001
		Wechat skip frames */
	/* Performance Scene Name */
	#define E902010001_CASENAME_VARCHAR 0
	/* Error Level */
	#define E902010001_RESULT_INT 1
	/*  */
	#define E902010001_TOTALTIMESPENT_INT 2
	/*  */
	#define E902010001_ARG1_VARCHAR 3
	/*  */
	#define E902010001_ARG2_INT 4
	/*  */
	#define E902010001_VERSION_VARCHAR 5
	/*  */
	#define E902010001_CPULOAD_INT 6
	/*  */
	#define E902010001_CLTOP_PROC1_VARCHAR 7
	/*  */
	#define E902010001_CLPROC1_VAL_INT 8
	/*  */
	#define E902010001_CLTOP_PROC2_VARCHAR 9
	/*  */
	#define E902010001_CLPROC2_VAL_INT 10
	/*  */
	#define E902010001_CLTOP_PROC3_VARCHAR 11
	/*  */
	#define E902010001_CLPROC3_VAL_INT 12
	/*  */
	#define E902010001_FREEMEM_INT 13
	/*  */
	#define E902010001_FREEDISK_INT 14
	/*  */
	#define E902010001_LIMIT_FREQ_INT 15
	/*  */
	#define E902010001_BROOTED_INT 16
	/*  */
	#define E902010001_BMODEMLOGON_INT 17
	/*  */
	#define E902010001_BUARTENABL_INT 18
	/*  */
	#define E902010001_NPERFBUGSETTINGS_INT 19
	/*  */
	#define E902010001_IAWARE_INT 20
	/*  */
	#define E902010001_NRESERVE1_INT 21
	/*  */
	#define E902010001_STRRESERVE2_VARCHAR 22

	/* Event 902010002
		Huawei Application skip frames */
	/* Performance Scene Name */
	#define E902010002_CASENAME_VARCHAR 0
	/* Error Level */
	#define E902010002_RESULT_INT 1
	/*  */
	#define E902010002_TOTALTIMESPENT_INT 2
	/*  */
	#define E902010002_ARG1_VARCHAR 3
	/*  */
	#define E902010002_ARG2_INT 4
	/*  */
	#define E902010002_VERSION_VARCHAR 5
	/*  */
	#define E902010002_CPULOAD_INT 6
	/*  */
	#define E902010002_CLTOP_PROC1_VARCHAR 7
	/*  */
	#define E902010002_CLPROC1_VAL_INT 8
	/*  */
	#define E902010002_CLTOP_PROC2_VARCHAR 9
	/*  */
	#define E902010002_CLPROC2_VAL_INT 10
	/*  */
	#define E902010002_CLTOP_PROC3_VARCHAR 11
	/*  */
	#define E902010002_CLPROC3_VAL_INT 12
	/*  */
	#define E902010002_FREEMEM_INT 13
	/*  */
	#define E902010002_FREEDISK_INT 14
	/*  */
	#define E902010002_LIMIT_FREQ_INT 15
	/*  */
	#define E902010002_BROOTED_INT 16
	/*  */
	#define E902010002_BMODEMLOGON_INT 17
	/*  */
	#define E902010002_BUARTENABL_INT 18
	/*  */
	#define E902010002_NPERFBUGSETTINGS_INT 19
	/*  */
	#define E902010002_IAWARE_INT 20
	/*  */
	#define E902010002_NRESERVE1_INT 21
	/*  */
	#define E902010002_STRRESERVE2_VARCHAR 22

	/* Event 902010003
		Third-Party Application skip frames */
	/* Performance Scene Name */
	#define E902010003_CASENAME_VARCHAR 0
	/* Error Level */
	#define E902010003_RESULT_INT 1
	/*  */
	#define E902010003_TOTALTIMESPENT_INT 2
	/*  */
	#define E902010003_ARG1_VARCHAR 3
	/*  */
	#define E902010003_ARG2_INT 4
	/*  */
	#define E902010003_VERSION_VARCHAR 5
	/*  */
	#define E902010003_CPULOAD_INT 6
	/*  */
	#define E902010003_CLTOP_PROC1_VARCHAR 7
	/*  */
	#define E902010003_CLPROC1_VAL_INT 8
	/*  */
	#define E902010003_CLTOP_PROC2_VARCHAR 9
	/*  */
	#define E902010003_CLPROC2_VAL_INT 10
	/*  */
	#define E902010003_CLTOP_PROC3_VARCHAR 11
	/*  */
	#define E902010003_CLPROC3_VAL_INT 12
	/*  */
	#define E902010003_FREEMEM_INT 13
	/*  */
	#define E902010003_FREEDISK_INT 14
	/*  */
	#define E902010003_LIMIT_FREQ_INT 15
	/*  */
	#define E902010003_BROOTED_INT 16
	/*  */
	#define E902010003_BMODEMLOGON_INT 17
	/*  */
	#define E902010003_BUARTENABL_INT 18
	/*  */
	#define E902010003_NPERFBUGSETTINGS_INT 19
	/*  */
	#define E902010003_IAWARE_INT 20
	/*  */
	#define E902010003_NRESERVE1_INT 21
	/*  */
	#define E902010003_STRRESERVE2_VARCHAR 22

	/* Event 902040000
		Power on slowly */
	/* Performance Scene Name */
	#define E902040000_CASENAME_VARCHAR 0
	/* Error Level */
	#define E902040000_RESULT_INT 1
	/*  */
	#define E902040000_TOTALTIMESPENT_INT 2
	/*  */
	#define E902040000_ARG1_VARCHAR 3
	/*  */
	#define E902040000_ARG2_INT 4
	/*  */
	#define E902040000_VERSION_VARCHAR 5
	/*  */
	#define E902040000_CPULOAD_INT 6
	/*  */
	#define E902040000_CLTOP_PROC1_VARCHAR 7
	/*  */
	#define E902040000_CLPROC1_VAL_INT 8
	/*  */
	#define E902040000_CLTOP_PROC2_VARCHAR 9
	/*  */
	#define E902040000_CLPROC2_VAL_INT 10
	/*  */
	#define E902040000_CLTOP_PROC3_VARCHAR 11
	/*  */
	#define E902040000_CLPROC3_VAL_INT 12
	/*  */
	#define E902040000_FREEMEM_INT 13
	/*  */
	#define E902040000_FREEDISK_INT 14
	/*  */
	#define E902040000_LIMIT_FREQ_INT 15
	/*  */
	#define E902040000_BROOTED_INT 16
	/*  */
	#define E902040000_BMODEMLOGON_INT 17
	/*  */
	#define E902040000_BUARTENABL_INT 18
	/*  */
	#define E902040000_NPERFBUGSETTINGS_INT 19
	/*  */
	#define E902040000_IAWARE_INT 20
	/*  */
	#define E902040000_NRESERVE1_INT 21
	/*  */
	#define E902040000_STRRESERVE2_VARCHAR 22

	/* Event 902040100
		other abnormal performance during booting or shutdown */
	/* Performance Scene Name */
	#define E902040100_CASENAME_VARCHAR 0
	/* Error Level */
	#define E902040100_RESULT_INT 1
	/*  */
	#define E902040100_TOTALTIMESPENT_INT 2
	/*  */
	#define E902040100_ARG1_VARCHAR 3
	/*  */
	#define E902040100_ARG2_INT 4
	/*  */
	#define E902040100_VERSION_VARCHAR 5
	/*  */
	#define E902040100_CPULOAD_INT 6
	/*  */
	#define E902040100_CLTOP_PROC1_VARCHAR 7
	/*  */
	#define E902040100_CLPROC1_VAL_INT 8
	/*  */
	#define E902040100_CLTOP_PROC2_VARCHAR 9
	/*  */
	#define E902040100_CLPROC2_VAL_INT 10
	/*  */
	#define E902040100_CLTOP_PROC3_VARCHAR 11
	/*  */
	#define E902040100_CLPROC3_VAL_INT 12
	/*  */
	#define E902040100_FREEMEM_INT 13
	/*  */
	#define E902040100_FREEDISK_INT 14
	/*  */
	#define E902040100_LIMIT_FREQ_INT 15
	/*  */
	#define E902040100_BROOTED_INT 16
	/*  */
	#define E902040100_BMODEMLOGON_INT 17
	/*  */
	#define E902040100_BUARTENABL_INT 18
	/*  */
	#define E902040100_NPERFBUGSETTINGS_INT 19
	/*  */
	#define E902040100_IAWARE_INT 20
	/*  */
	#define E902040100_NRESERVE1_INT 21
	/*  */
	#define E902040100_STRRESERVE2_VARCHAR 22

	/* Event 902050000
		Screen on by powerkey slowly */
	/* Performance Scene Name */
	#define E902050000_CASENAME_VARCHAR 0
	/* Error Level */
	#define E902050000_RESULT_INT 1
	/*  */
	#define E902050000_TOTALTIMESPENT_INT 2
	/*  */
	#define E902050000_ARG1_VARCHAR 3
	/*  */
	#define E902050000_ARG2_INT 4
	/*  */
	#define E902050000_VERSION_VARCHAR 5
	/*  */
	#define E902050000_CPULOAD_INT 6
	/*  */
	#define E902050000_CLTOP_PROC1_VARCHAR 7
	/*  */
	#define E902050000_CLPROC1_VAL_INT 8
	/*  */
	#define E902050000_CLTOP_PROC2_VARCHAR 9
	/*  */
	#define E902050000_CLPROC2_VAL_INT 10
	/*  */
	#define E902050000_CLTOP_PROC3_VARCHAR 11
	/*  */
	#define E902050000_CLPROC3_VAL_INT 12
	/*  */
	#define E902050000_FREEMEM_INT 13
	/*  */
	#define E902050000_FREEDISK_INT 14
	/*  */
	#define E902050000_LIMIT_FREQ_INT 15
	/*  */
	#define E902050000_BROOTED_INT 16
	/*  */
	#define E902050000_BMODEMLOGON_INT 17
	/*  */
	#define E902050000_BUARTENABL_INT 18
	/*  */
	#define E902050000_NPERFBUGSETTINGS_INT 19
	/*  */
	#define E902050000_IAWARE_INT 20
	/*  */
	#define E902050000_NRESERVE1_INT 21
	/*  */
	#define E902050000_STRRESERVE2_VARCHAR 22

	/* Event 902050001
		Screen on by powerkey slowly when deeply sleep */
	/* Performance Scene Name */
	#define E902050001_CASENAME_VARCHAR 0
	/* Error Level */
	#define E902050001_RESULT_INT 1
	/*  */
	#define E902050001_TOTALTIMESPENT_INT 2
	/*  */
	#define E902050001_ARG1_VARCHAR 3
	/*  */
	#define E902050001_ARG2_INT 4
	/*  */
	#define E902050001_VERSION_VARCHAR 5
	/*  */
	#define E902050001_CPULOAD_INT 6
	/*  */
	#define E902050001_CLTOP_PROC1_VARCHAR 7
	/*  */
	#define E902050001_CLPROC1_VAL_INT 8
	/*  */
	#define E902050001_CLTOP_PROC2_VARCHAR 9
	/*  */
	#define E902050001_CLPROC2_VAL_INT 10
	/*  */
	#define E902050001_CLTOP_PROC3_VARCHAR 11
	/*  */
	#define E902050001_CLPROC3_VAL_INT 12
	/*  */
	#define E902050001_FREEMEM_INT 13
	/*  */
	#define E902050001_FREEDISK_INT 14
	/*  */
	#define E902050001_LIMIT_FREQ_INT 15
	/*  */
	#define E902050001_BROOTED_INT 16
	/*  */
	#define E902050001_BMODEMLOGON_INT 17
	/*  */
	#define E902050001_BUARTENABL_INT 18
	/*  */
	#define E902050001_NPERFBUGSETTINGS_INT 19
	/*  */
	#define E902050001_IAWARE_INT 20
	/*  */
	#define E902050001_NRESERVE1_INT 21
	/*  */
	#define E902050001_STRRESERVE2_VARCHAR 22

	/* Event 902050002
		Screen off by powerkey slowly */
	/* Performance Scene Name */
	#define E902050002_CASENAME_VARCHAR 0
	/* Error Level */
	#define E902050002_RESULT_INT 1
	/*  */
	#define E902050002_TOTALTIMESPENT_INT 2
	/*  */
	#define E902050002_ARG1_VARCHAR 3
	/*  */
	#define E902050002_ARG2_INT 4
	/*  */
	#define E902050002_VERSION_VARCHAR 5
	/*  */
	#define E902050002_CPULOAD_INT 6
	/*  */
	#define E902050002_CLTOP_PROC1_VARCHAR 7
	/*  */
	#define E902050002_CLPROC1_VAL_INT 8
	/*  */
	#define E902050002_CLTOP_PROC2_VARCHAR 9
	/*  */
	#define E902050002_CLPROC2_VAL_INT 10
	/*  */
	#define E902050002_CLTOP_PROC3_VARCHAR 11
	/*  */
	#define E902050002_CLPROC3_VAL_INT 12
	/*  */
	#define E902050002_FREEMEM_INT 13
	/*  */
	#define E902050002_FREEDISK_INT 14
	/*  */
	#define E902050002_LIMIT_FREQ_INT 15
	/*  */
	#define E902050002_BROOTED_INT 16
	/*  */
	#define E902050002_BMODEMLOGON_INT 17
	/*  */
	#define E902050002_BUARTENABL_INT 18
	/*  */
	#define E902050002_NPERFBUGSETTINGS_INT 19
	/*  */
	#define E902050002_IAWARE_INT 20
	/*  */
	#define E902050002_NRESERVE1_INT 21
	/*  */
	#define E902050002_STRRESERVE2_VARCHAR 22

	/* Event 902050003
		Screen on by incoming call slowly */
	/* Performance Scene Name */
	#define E902050003_CASENAME_VARCHAR 0
	/* Error Level */
	#define E902050003_RESULT_INT 1
	/*  */
	#define E902050003_TOTALTIMESPENT_INT 2
	/*  */
	#define E902050003_ARG1_VARCHAR 3
	/*  */
	#define E902050003_ARG2_INT 4
	/*  */
	#define E902050003_VERSION_VARCHAR 5
	/*  */
	#define E902050003_CPULOAD_INT 6
	/*  */
	#define E902050003_CLTOP_PROC1_VARCHAR 7
	/*  */
	#define E902050003_CLPROC1_VAL_INT 8
	/*  */
	#define E902050003_CLTOP_PROC2_VARCHAR 9
	/*  */
	#define E902050003_CLPROC2_VAL_INT 10
	/*  */
	#define E902050003_CLTOP_PROC3_VARCHAR 11
	/*  */
	#define E902050003_CLPROC3_VAL_INT 12
	/*  */
	#define E902050003_FREEMEM_INT 13
	/*  */
	#define E902050003_FREEDISK_INT 14
	/*  */
	#define E902050003_LIMIT_FREQ_INT 15
	/*  */
	#define E902050003_BROOTED_INT 16
	/*  */
	#define E902050003_BMODEMLOGON_INT 17
	/*  */
	#define E902050003_BUARTENABL_INT 18
	/*  */
	#define E902050003_NPERFBUGSETTINGS_INT 19
	/*  */
	#define E902050003_IAWARE_INT 20
	/*  */
	#define E902050003_NRESERVE1_INT 21
	/*  */
	#define E902050003_STRRESERVE2_VARCHAR 22

	/* Event 902050004
		Screen on by incoming call slowly when deeply sleep */
	/* Performance Scene Name */
	#define E902050004_CASENAME_VARCHAR 0
	/* Error Level */
	#define E902050004_RESULT_INT 1
	/*  */
	#define E902050004_TOTALTIMESPENT_INT 2
	/*  */
	#define E902050004_ARG1_VARCHAR 3
	/*  */
	#define E902050004_ARG2_INT 4
	/*  */
	#define E902050004_VERSION_VARCHAR 5
	/*  */
	#define E902050004_CPULOAD_INT 6
	/*  */
	#define E902050004_CLTOP_PROC1_VARCHAR 7
	/*  */
	#define E902050004_CLPROC1_VAL_INT 8
	/*  */
	#define E902050004_CLTOP_PROC2_VARCHAR 9
	/*  */
	#define E902050004_CLPROC2_VAL_INT 10
	/*  */
	#define E902050004_CLTOP_PROC3_VARCHAR 11
	/*  */
	#define E902050004_CLPROC3_VAL_INT 12
	/*  */
	#define E902050004_FREEMEM_INT 13
	/*  */
	#define E902050004_FREEDISK_INT 14
	/*  */
	#define E902050004_LIMIT_FREQ_INT 15
	/*  */
	#define E902050004_BROOTED_INT 16
	/*  */
	#define E902050004_BMODEMLOGON_INT 17
	/*  */
	#define E902050004_BUARTENABL_INT 18
	/*  */
	#define E902050004_NPERFBUGSETTINGS_INT 19
	/*  */
	#define E902050004_IAWARE_INT 20
	/*  */
	#define E902050004_NRESERVE1_INT 21
	/*  */
	#define E902050004_STRRESERVE2_VARCHAR 22

	/* Event 902050005
		Screen on by charging slowly */
	/* Performance Scene Name */
	#define E902050005_CASENAME_VARCHAR 0
	/* Error Level */
	#define E902050005_RESULT_INT 1
	/*  */
	#define E902050005_TOTALTIMESPENT_INT 2
	/*  */
	#define E902050005_ARG1_VARCHAR 3
	/*  */
	#define E902050005_ARG2_INT 4
	/*  */
	#define E902050005_VERSION_VARCHAR 5
	/*  */
	#define E902050005_CPULOAD_INT 6
	/*  */
	#define E902050005_CLTOP_PROC1_VARCHAR 7
	/*  */
	#define E902050005_CLPROC1_VAL_INT 8
	/*  */
	#define E902050005_CLTOP_PROC2_VARCHAR 9
	/*  */
	#define E902050005_CLPROC2_VAL_INT 10
	/*  */
	#define E902050005_CLTOP_PROC3_VARCHAR 11
	/*  */
	#define E902050005_CLPROC3_VAL_INT 12
	/*  */
	#define E902050005_FREEMEM_INT 13
	/*  */
	#define E902050005_FREEDISK_INT 14
	/*  */
	#define E902050005_LIMIT_FREQ_INT 15
	/*  */
	#define E902050005_BROOTED_INT 16
	/*  */
	#define E902050005_BMODEMLOGON_INT 17
	/*  */
	#define E902050005_BUARTENABL_INT 18
	/*  */
	#define E902050005_NPERFBUGSETTINGS_INT 19
	/*  */
	#define E902050005_IAWARE_INT 20
	/*  */
	#define E902050005_NRESERVE1_INT 21
	/*  */
	#define E902050005_STRRESERVE2_VARCHAR 22

	/* Event 902050006
		Screen on by charging slowly when deeply sleep */
	/* Performance Scene Name */
	#define E902050006_CASENAME_VARCHAR 0
	/* Error Level */
	#define E902050006_RESULT_INT 1
	/*  */
	#define E902050006_TOTALTIMESPENT_INT 2
	/*  */
	#define E902050006_ARG1_VARCHAR 3
	/*  */
	#define E902050006_ARG2_INT 4
	/*  */
	#define E902050006_VERSION_VARCHAR 5
	/*  */
	#define E902050006_CPULOAD_INT 6
	/*  */
	#define E902050006_CLTOP_PROC1_VARCHAR 7
	/*  */
	#define E902050006_CLPROC1_VAL_INT 8
	/*  */
	#define E902050006_CLTOP_PROC2_VARCHAR 9
	/*  */
	#define E902050006_CLPROC2_VAL_INT 10
	/*  */
	#define E902050006_CLTOP_PROC3_VARCHAR 11
	/*  */
	#define E902050006_CLPROC3_VAL_INT 12
	/*  */
	#define E902050006_FREEMEM_INT 13
	/*  */
	#define E902050006_FREEDISK_INT 14
	/*  */
	#define E902050006_LIMIT_FREQ_INT 15
	/*  */
	#define E902050006_BROOTED_INT 16
	/*  */
	#define E902050006_BMODEMLOGON_INT 17
	/*  */
	#define E902050006_BUARTENABL_INT 18
	/*  */
	#define E902050006_NPERFBUGSETTINGS_INT 19
	/*  */
	#define E902050006_IAWARE_INT 20
	/*  */
	#define E902050006_NRESERVE1_INT 21
	/*  */
	#define E902050006_STRRESERVE2_VARCHAR 22

	/* Event 902050007
		Screen on by pullout USB cable */
	/* Performance Scene Name */
	#define E902050007_CASENAME_VARCHAR 0
	/* Error Level */
	#define E902050007_RESULT_INT 1
	/*  */
	#define E902050007_TOTALTIMESPENT_INT 2
	/*  */
	#define E902050007_ARG1_VARCHAR 3
	/*  */
	#define E902050007_ARG2_INT 4
	/*  */
	#define E902050007_VERSION_VARCHAR 5
	/*  */
	#define E902050007_CPULOAD_INT 6
	/*  */
	#define E902050007_CLTOP_PROC1_VARCHAR 7
	/*  */
	#define E902050007_CLPROC1_VAL_INT 8
	/*  */
	#define E902050007_CLTOP_PROC2_VARCHAR 9
	/*  */
	#define E902050007_CLPROC2_VAL_INT 10
	/*  */
	#define E902050007_CLTOP_PROC3_VARCHAR 11
	/*  */
	#define E902050007_CLPROC3_VAL_INT 12
	/*  */
	#define E902050007_FREEMEM_INT 13
	/*  */
	#define E902050007_FREEDISK_INT 14
	/*  */
	#define E902050007_LIMIT_FREQ_INT 15
	/*  */
	#define E902050007_BROOTED_INT 16
	/*  */
	#define E902050007_BMODEMLOGON_INT 17
	/*  */
	#define E902050007_BUARTENABL_INT 18
	/*  */
	#define E902050007_NPERFBUGSETTINGS_INT 19
	/*  */
	#define E902050007_IAWARE_INT 20
	/*  */
	#define E902050007_NRESERVE1_INT 21
	/*  */
	#define E902050007_STRRESERVE2_VARCHAR 22

	/* Event 902050008
		Screen off by proximity */
	/* Performance Scene Name */
	#define E902050008_CASENAME_VARCHAR 0
	/* Error Level */
	#define E902050008_RESULT_INT 1
	/*  */
	#define E902050008_TOTALTIMESPENT_INT 2
	/*  */
	#define E902050008_ARG1_VARCHAR 3
	/*  */
	#define E902050008_ARG2_INT 4
	/*  */
	#define E902050008_VERSION_VARCHAR 5
	/*  */
	#define E902050008_CPULOAD_INT 6
	/*  */
	#define E902050008_CLTOP_PROC1_VARCHAR 7
	/*  */
	#define E902050008_CLPROC1_VAL_INT 8
	/*  */
	#define E902050008_CLTOP_PROC2_VARCHAR 9
	/*  */
	#define E902050008_CLPROC2_VAL_INT 10
	/*  */
	#define E902050008_CLTOP_PROC3_VARCHAR 11
	/*  */
	#define E902050008_CLPROC3_VAL_INT 12
	/*  */
	#define E902050008_FREEMEM_INT 13
	/*  */
	#define E902050008_FREEDISK_INT 14
	/*  */
	#define E902050008_LIMIT_FREQ_INT 15
	/*  */
	#define E902050008_BROOTED_INT 16
	/*  */
	#define E902050008_BMODEMLOGON_INT 17
	/*  */
	#define E902050008_BUARTENABL_INT 18
	/*  */
	#define E902050008_NPERFBUGSETTINGS_INT 19
	/*  */
	#define E902050008_IAWARE_INT 20
	/*  */
	#define E902050008_NRESERVE1_INT 21
	/*  */
	#define E902050008_STRRESERVE2_VARCHAR 22

	/* Event 902050009
		Screen on by proximity */
	/* Performance Scene Name */
	#define E902050009_CASENAME_VARCHAR 0
	/* Error Level */
	#define E902050009_RESULT_INT 1
	/*  */
	#define E902050009_TOTALTIMESPENT_INT 2
	/*  */
	#define E902050009_ARG1_VARCHAR 3
	/*  */
	#define E902050009_ARG2_INT 4
	/*  */
	#define E902050009_VERSION_VARCHAR 5
	/*  */
	#define E902050009_CPULOAD_INT 6
	/*  */
	#define E902050009_CLTOP_PROC1_VARCHAR 7
	/*  */
	#define E902050009_CLPROC1_VAL_INT 8
	/*  */
	#define E902050009_CLTOP_PROC2_VARCHAR 9
	/*  */
	#define E902050009_CLPROC2_VAL_INT 10
	/*  */
	#define E902050009_CLTOP_PROC3_VARCHAR 11
	/*  */
	#define E902050009_CLPROC3_VAL_INT 12
	/*  */
	#define E902050009_FREEMEM_INT 13
	/*  */
	#define E902050009_FREEDISK_INT 14
	/*  */
	#define E902050009_LIMIT_FREQ_INT 15
	/*  */
	#define E902050009_BROOTED_INT 16
	/*  */
	#define E902050009_BMODEMLOGON_INT 17
	/*  */
	#define E902050009_BUARTENABL_INT 18
	/*  */
	#define E902050009_NPERFBUGSETTINGS_INT 19
	/*  */
	#define E902050009_IAWARE_INT 20
	/*  */
	#define E902050009_NRESERVE1_INT 21
	/*  */
	#define E902050009_STRRESERVE2_VARCHAR 22

	/* Event 902050010
		Screen on by fingerprint */
	/* Performance Scene Name */
	#define E902050010_CASENAME_VARCHAR 0
	/* Error Level */
	#define E902050010_RESULT_INT 1
	/*  */
	#define E902050010_TOTALTIMESPENT_INT 2
	/*  */
	#define E902050010_ARG1_VARCHAR 3
	/*  */
	#define E902050010_ARG2_INT 4
	/*  */
	#define E902050010_VERSION_VARCHAR 5
	/*  */
	#define E902050010_CPULOAD_INT 6
	/*  */
	#define E902050010_CLTOP_PROC1_VARCHAR 7
	/*  */
	#define E902050010_CLPROC1_VAL_INT 8
	/*  */
	#define E902050010_CLTOP_PROC2_VARCHAR 9
	/*  */
	#define E902050010_CLPROC2_VAL_INT 10
	/*  */
	#define E902050010_CLTOP_PROC3_VARCHAR 11
	/*  */
	#define E902050010_CLPROC3_VAL_INT 12
	/*  */
	#define E902050010_FREEMEM_INT 13
	/*  */
	#define E902050010_FREEDISK_INT 14
	/*  */
	#define E902050010_LIMIT_FREQ_INT 15
	/*  */
	#define E902050010_BROOTED_INT 16
	/*  */
	#define E902050010_BMODEMLOGON_INT 17
	/*  */
	#define E902050010_BUARTENABL_INT 18
	/*  */
	#define E902050010_NPERFBUGSETTINGS_INT 19
	/*  */
	#define E902050010_IAWARE_INT 20
	/*  */
	#define E902050010_NRESERVE1_INT 21
	/*  */
	#define E902050010_STRRESERVE2_VARCHAR 22

	/* Event 902050011
		Screen on by SMS */
	/* Performance Scene Name */
	#define E902050011_CASENAME_VARCHAR 0
	/* Error Level */
	#define E902050011_RESULT_INT 1
	/*  */
	#define E902050011_TOTALTIMESPENT_INT 2
	/*  */
	#define E902050011_ARG1_VARCHAR 3
	/*  */
	#define E902050011_ARG2_INT 4
	/*  */
	#define E902050011_VERSION_VARCHAR 5
	/*  */
	#define E902050011_CPULOAD_INT 6
	/*  */
	#define E902050011_CLTOP_PROC1_VARCHAR 7
	/*  */
	#define E902050011_CLPROC1_VAL_INT 8
	/*  */
	#define E902050011_CLTOP_PROC2_VARCHAR 9
	/*  */
	#define E902050011_CLPROC2_VAL_INT 10
	/*  */
	#define E902050011_CLTOP_PROC3_VARCHAR 11
	/*  */
	#define E902050011_CLPROC3_VAL_INT 12
	/*  */
	#define E902050011_FREEMEM_INT 13
	/*  */
	#define E902050011_FREEDISK_INT 14
	/*  */
	#define E902050011_LIMIT_FREQ_INT 15
	/*  */
	#define E902050011_BROOTED_INT 16
	/*  */
	#define E902050011_BMODEMLOGON_INT 17
	/*  */
	#define E902050011_BUARTENABL_INT 18
	/*  */
	#define E902050011_NPERFBUGSETTINGS_INT 19
	/*  */
	#define E902050011_IAWARE_INT 20
	/*  */
	#define E902050011_NRESERVE1_INT 21
	/*  */
	#define E902050011_STRRESERVE2_VARCHAR 22

	/* Event 902050012
		Screen on by cover */
	/* Performance Scene Name */
	#define E902050012_CASENAME_VARCHAR 0
	/* Error Level */
	#define E902050012_RESULT_INT 1
	/*  */
	#define E902050012_TOTALTIMESPENT_INT 2
	/*  */
	#define E902050012_ARG1_VARCHAR 3
	/*  */
	#define E902050012_ARG2_INT 4
	/*  */
	#define E902050012_VERSION_VARCHAR 5
	/*  */
	#define E902050012_CPULOAD_INT 6
	/*  */
	#define E902050012_CLTOP_PROC1_VARCHAR 7
	/*  */
	#define E902050012_CLPROC1_VAL_INT 8
	/*  */
	#define E902050012_CLTOP_PROC2_VARCHAR 9
	/*  */
	#define E902050012_CLPROC2_VAL_INT 10
	/*  */
	#define E902050012_CLTOP_PROC3_VARCHAR 11
	/*  */
	#define E902050012_CLPROC3_VAL_INT 12
	/*  */
	#define E902050012_FREEMEM_INT 13
	/*  */
	#define E902050012_FREEDISK_INT 14
	/*  */
	#define E902050012_LIMIT_FREQ_INT 15
	/*  */
	#define E902050012_BROOTED_INT 16
	/*  */
	#define E902050012_BMODEMLOGON_INT 17
	/*  */
	#define E902050012_BUARTENABL_INT 18
	/*  */
	#define E902050012_NPERFBUGSETTINGS_INT 19
	/*  */
	#define E902050012_IAWARE_INT 20
	/*  */
	#define E902050012_NRESERVE1_INT 21
	/*  */
	#define E902050012_STRRESERVE2_VARCHAR 22

	/* Event 902050100
		Screen on by others */
	/* Performance Scene Name */
	#define E902050100_CASENAME_VARCHAR 0
	/* Error Level */
	#define E902050100_RESULT_INT 1
	/*  */
	#define E902050100_TOTALTIMESPENT_INT 2
	/*  */
	#define E902050100_ARG1_VARCHAR 3
	/*  */
	#define E902050100_ARG2_INT 4
	/*  */
	#define E902050100_VERSION_VARCHAR 5
	/*  */
	#define E902050100_CPULOAD_INT 6
	/*  */
	#define E902050100_CLTOP_PROC1_VARCHAR 7
	/*  */
	#define E902050100_CLPROC1_VAL_INT 8
	/*  */
	#define E902050100_CLTOP_PROC2_VARCHAR 9
	/*  */
	#define E902050100_CLPROC2_VAL_INT 10
	/*  */
	#define E902050100_CLTOP_PROC3_VARCHAR 11
	/*  */
	#define E902050100_CLPROC3_VAL_INT 12
	/*  */
	#define E902050100_FREEMEM_INT 13
	/*  */
	#define E902050100_FREEDISK_INT 14
	/*  */
	#define E902050100_LIMIT_FREQ_INT 15
	/*  */
	#define E902050100_BROOTED_INT 16
	/*  */
	#define E902050100_BMODEMLOGON_INT 17
	/*  */
	#define E902050100_BUARTENABL_INT 18
	/*  */
	#define E902050100_NPERFBUGSETTINGS_INT 19
	/*  */
	#define E902050100_IAWARE_INT 20
	/*  */
	#define E902050100_NRESERVE1_INT 21
	/*  */
	#define E902050100_STRRESERVE2_VARCHAR 22

	/* Event 902060000
		Sqlite processes slowly */
	/* Performance Scene Name */
	#define E902060000_CASENAME_VARCHAR 0
	/* Error Level */
	#define E902060000_RESULT_INT 1
	/*  */
	#define E902060000_TOTALTIMESPENT_INT 2
	/*  */
	#define E902060000_ARG1_VARCHAR 3
	/*  */
	#define E902060000_ARG2_INT 4
	/*  */
	#define E902060000_VERSION_VARCHAR 5
	/*  */
	#define E902060000_CPULOAD_INT 6
	/*  */
	#define E902060000_CLTOP_PROC1_VARCHAR 7
	/*  */
	#define E902060000_CLPROC1_VAL_INT 8
	/*  */
	#define E902060000_CLTOP_PROC2_VARCHAR 9
	/*  */
	#define E902060000_CLPROC2_VAL_INT 10
	/*  */
	#define E902060000_CLTOP_PROC3_VARCHAR 11
	/*  */
	#define E902060000_CLPROC3_VAL_INT 12
	/*  */
	#define E902060000_FREEMEM_INT 13
	/*  */
	#define E902060000_FREEDISK_INT 14
	/*  */
	#define E902060000_LIMIT_FREQ_INT 15
	/*  */
	#define E902060000_BROOTED_INT 16
	/*  */
	#define E902060000_BMODEMLOGON_INT 17
	/*  */
	#define E902060000_BUARTENABL_INT 18
	/*  */
	#define E902060000_NPERFBUGSETTINGS_INT 19
	/*  */
	#define E902060000_IAWARE_INT 20
	/*  */
	#define E902060000_NRESERVE1_INT 21
	/*  */
	#define E902060000_STRRESERVE2_VARCHAR 22

	/* Event 902060001
		RMS exception */
	/* Performance Scene Name */
	#define E902060001_CASENAME_VARCHAR 0
	/* Error Level */
	#define E902060001_RESULT_INT 1
	/*  */
	#define E902060001_TOTALTIMESPENT_INT 2
	/*  */
	#define E902060001_ARG1_VARCHAR 3
	/*  */
	#define E902060001_ARG2_INT 4
	/*  */
	#define E902060001_VERSION_VARCHAR 5
	/*  */
	#define E902060001_CPULOAD_INT 6
	/*  */
	#define E902060001_CLTOP_PROC1_VARCHAR 7
	/*  */
	#define E902060001_CLPROC1_VAL_INT 8
	/*  */
	#define E902060001_CLTOP_PROC2_VARCHAR 9
	/*  */
	#define E902060001_CLPROC2_VAL_INT 10
	/*  */
	#define E902060001_CLTOP_PROC3_VARCHAR 11
	/*  */
	#define E902060001_CLPROC3_VAL_INT 12
	/*  */
	#define E902060001_FREEMEM_INT 13
	/*  */
	#define E902060001_FREEDISK_INT 14
	/*  */
	#define E902060001_LIMIT_FREQ_INT 15
	/*  */
	#define E902060001_BROOTED_INT 16
	/*  */
	#define E902060001_BMODEMLOGON_INT 17
	/*  */
	#define E902060001_BUARTENABL_INT 18
	/*  */
	#define E902060001_NPERFBUGSETTINGS_INT 19
	/*  */
	#define E902060001_IAWARE_INT 20
	/*  */
	#define E902060001_NRESERVE1_INT 21
	/*  */
	#define E902060001_STRRESERVE2_VARCHAR 22

	/* Event 902060002
		iAware exception */
	/* Performance Scene Name */
	#define E902060002_CASENAME_VARCHAR 0
	/* Error Level */
	#define E902060002_RESULT_INT 1
	/*  */
	#define E902060002_TOTALTIMESPENT_INT 2
	/*  */
	#define E902060002_ARG1_VARCHAR 3
	/*  */
	#define E902060002_ARG2_INT 4
	/*  */
	#define E902060002_VERSION_VARCHAR 5
	/*  */
	#define E902060002_CPULOAD_INT 6
	/*  */
	#define E902060002_CLTOP_PROC1_VARCHAR 7
	/*  */
	#define E902060002_CLPROC1_VAL_INT 8
	/*  */
	#define E902060002_CLTOP_PROC2_VARCHAR 9
	/*  */
	#define E902060002_CLPROC2_VAL_INT 10
	/*  */
	#define E902060002_CLTOP_PROC3_VARCHAR 11
	/*  */
	#define E902060002_CLPROC3_VAL_INT 12
	/*  */
	#define E902060002_FREEMEM_INT 13
	/*  */
	#define E902060002_FREEDISK_INT 14
	/*  */
	#define E902060002_LIMIT_FREQ_INT 15
	/*  */
	#define E902060002_BROOTED_INT 16
	/*  */
	#define E902060002_BMODEMLOGON_INT 17
	/*  */
	#define E902060002_BUARTENABL_INT 18
	/*  */
	#define E902060002_NPERFBUGSETTINGS_INT 19
	/*  */
	#define E902060002_IAWARE_INT 20
	/*  */
	#define E902060002_NRESERVE1_INT 21
	/*  */
	#define E902060002_STRRESERVE2_VARCHAR 22

	/* Event 902060003
		core process or app is killed */
	/* Performance Scene Name */
	#define E902060003_CASENAME_VARCHAR 0
	/* Error Level */
	#define E902060003_RESULT_INT 1
	/*  */
	#define E902060003_TOTALTIMESPENT_INT 2
	/*  */
	#define E902060003_ARG1_VARCHAR 3
	/*  */
	#define E902060003_ARG2_INT 4
	/*  */
	#define E902060003_VERSION_VARCHAR 5
	/*  */
	#define E902060003_CPULOAD_INT 6
	/*  */
	#define E902060003_CLTOP_PROC1_VARCHAR 7
	/*  */
	#define E902060003_CLPROC1_VAL_INT 8
	/*  */
	#define E902060003_CLTOP_PROC2_VARCHAR 9
	/*  */
	#define E902060003_CLPROC2_VAL_INT 10
	/*  */
	#define E902060003_CLTOP_PROC3_VARCHAR 11
	/*  */
	#define E902060003_CLPROC3_VAL_INT 12
	/*  */
	#define E902060003_FREEMEM_INT 13
	/*  */
	#define E902060003_FREEDISK_INT 14
	/*  */
	#define E902060003_LIMIT_FREQ_INT 15
	/*  */
	#define E902060003_BROOTED_INT 16
	/*  */
	#define E902060003_BMODEMLOGON_INT 17
	/*  */
	#define E902060003_BUARTENABL_INT 18
	/*  */
	#define E902060003_NPERFBUGSETTINGS_INT 19
	/*  */
	#define E902060003_IAWARE_INT 20
	/*  */
	#define E902060003_NRESERVE1_INT 21
	/*  */
	#define E902060003_STRRESERVE2_VARCHAR 22

	/* Event 902060100
		other system resource */
	/* Performance Scene Name */
	#define E902060100_CASENAME_VARCHAR 0
	/* Error Level */
	#define E902060100_RESULT_INT 1
	/*  */
	#define E902060100_TOTALTIMESPENT_INT 2
	/*  */
	#define E902060100_ARG1_VARCHAR 3
	/*  */
	#define E902060100_ARG2_INT 4
	/*  */
	#define E902060100_VERSION_VARCHAR 5
	/*  */
	#define E902060100_CPULOAD_INT 6
	/*  */
	#define E902060100_CLTOP_PROC1_VARCHAR 7
	/*  */
	#define E902060100_CLPROC1_VAL_INT 8
	/*  */
	#define E902060100_CLTOP_PROC2_VARCHAR 9
	/*  */
	#define E902060100_CLPROC2_VAL_INT 10
	/*  */
	#define E902060100_CLTOP_PROC3_VARCHAR 11
	/*  */
	#define E902060100_CLPROC3_VAL_INT 12
	/*  */
	#define E902060100_FREEMEM_INT 13
	/*  */
	#define E902060100_FREEDISK_INT 14
	/*  */
	#define E902060100_LIMIT_FREQ_INT 15
	/*  */
	#define E902060100_BROOTED_INT 16
	/*  */
	#define E902060100_BMODEMLOGON_INT 17
	/*  */
	#define E902060100_BUARTENABL_INT 18
	/*  */
	#define E902060100_NPERFBUGSETTINGS_INT 19
	/*  */
	#define E902060100_IAWARE_INT 20
	/*  */
	#define E902060100_NRESERVE1_INT 21
	/*  */
	#define E902060100_STRRESERVE2_VARCHAR 22

	/* Event 902070000
		Orientation change slowly */
	/* Performance Scene Name */
	#define E902070000_CASENAME_VARCHAR 0
	/* Error Level */
	#define E902070000_RESULT_INT 1
	/*  */
	#define E902070000_TOTALTIMESPENT_INT 2
	/*  */
	#define E902070000_ARG1_VARCHAR 3
	/*  */
	#define E902070000_ARG2_INT 4
	/*  */
	#define E902070000_VERSION_VARCHAR 5
	/*  */
	#define E902070000_CPULOAD_INT 6
	/*  */
	#define E902070000_CLTOP_PROC1_VARCHAR 7
	/*  */
	#define E902070000_CLPROC1_VAL_INT 8
	/*  */
	#define E902070000_CLTOP_PROC2_VARCHAR 9
	/*  */
	#define E902070000_CLPROC2_VAL_INT 10
	/*  */
	#define E902070000_CLTOP_PROC3_VARCHAR 11
	/*  */
	#define E902070000_CLPROC3_VAL_INT 12
	/*  */
	#define E902070000_FREEMEM_INT 13
	/*  */
	#define E902070000_FREEDISK_INT 14
	/*  */
	#define E902070000_LIMIT_FREQ_INT 15
	/*  */
	#define E902070000_BROOTED_INT 16
	/*  */
	#define E902070000_BMODEMLOGON_INT 17
	/*  */
	#define E902070000_BUARTENABL_INT 18
	/*  */
	#define E902070000_NPERFBUGSETTINGS_INT 19
	/*  */
	#define E902070000_IAWARE_INT 20
	/*  */
	#define E902070000_NRESERVE1_INT 21
	/*  */
	#define E902070000_STRRESERVE2_VARCHAR 22

	/* Event 902070001
		Slide to click */
	/* Performance Scene Name */
	#define E902070001_CASENAME_VARCHAR 0
	/* Error Level */
	#define E902070001_RESULT_INT 1
	/*  */
	#define E902070001_TOTALTIMESPENT_INT 2
	/*  */
	#define E902070001_ARG1_VARCHAR 3
	/*  */
	#define E902070001_ARG2_INT 4
	/*  */
	#define E902070001_VERSION_VARCHAR 5
	/*  */
	#define E902070001_CPULOAD_INT 6
	/*  */
	#define E902070001_CLTOP_PROC1_VARCHAR 7
	/*  */
	#define E902070001_CLPROC1_VAL_INT 8
	/*  */
	#define E902070001_CLTOP_PROC2_VARCHAR 9
	/*  */
	#define E902070001_CLPROC2_VAL_INT 10
	/*  */
	#define E902070001_CLTOP_PROC3_VARCHAR 11
	/*  */
	#define E902070001_CLPROC3_VAL_INT 12
	/*  */
	#define E902070001_FREEMEM_INT 13
	/*  */
	#define E902070001_FREEDISK_INT 14
	/*  */
	#define E902070001_LIMIT_FREQ_INT 15
	/*  */
	#define E902070001_BROOTED_INT 16
	/*  */
	#define E902070001_BMODEMLOGON_INT 17
	/*  */
	#define E902070001_BUARTENABL_INT 18
	/*  */
	#define E902070001_NPERFBUGSETTINGS_INT 19
	/*  */
	#define E902070001_IAWARE_INT 20
	/*  */
	#define E902070001_NRESERVE1_INT 21
	/*  */
	#define E902070001_STRRESERVE2_VARCHAR 22

	/* Event 902070002
		Automatical backlight exception */
	/* Performance Scene Name */
	#define E902070002_CASENAME_VARCHAR 0
	/* Error Level */
	#define E902070002_RESULT_INT 1
	/*  */
	#define E902070002_TOTALTIMESPENT_INT 2
	/*  */
	#define E902070002_ARG1_VARCHAR 3
	/*  */
	#define E902070002_ARG2_INT 4
	/*  */
	#define E902070002_VERSION_VARCHAR 5
	/*  */
	#define E902070002_CPULOAD_INT 6
	/*  */
	#define E902070002_CLTOP_PROC1_VARCHAR 7
	/*  */
	#define E902070002_CLPROC1_VAL_INT 8
	/*  */
	#define E902070002_CLTOP_PROC2_VARCHAR 9
	/*  */
	#define E902070002_CLPROC2_VAL_INT 10
	/*  */
	#define E902070002_CLTOP_PROC3_VARCHAR 11
	/*  */
	#define E902070002_CLPROC3_VAL_INT 12
	/*  */
	#define E902070002_FREEMEM_INT 13
	/*  */
	#define E902070002_FREEDISK_INT 14
	/*  */
	#define E902070002_LIMIT_FREQ_INT 15
	/*  */
	#define E902070002_BROOTED_INT 16
	/*  */
	#define E902070002_BMODEMLOGON_INT 17
	/*  */
	#define E902070002_BUARTENABL_INT 18
	/*  */
	#define E902070002_NPERFBUGSETTINGS_INT 19
	/*  */
	#define E902070002_IAWARE_INT 20
	/*  */
	#define E902070002_NRESERVE1_INT 21
	/*  */
	#define E902070002_STRRESERVE2_VARCHAR 22

	/* Event 902070003
		TP feedback slowly */
	/* Performance Scene Name */
	#define E902070003_CASENAME_VARCHAR 0
	/* Error Level */
	#define E902070003_RESULT_INT 1
	/*  */
	#define E902070003_TOTALTIMESPENT_INT 2
	/*  */
	#define E902070003_ARG1_VARCHAR 3
	/*  */
	#define E902070003_ARG2_INT 4
	/*  */
	#define E902070003_VERSION_VARCHAR 5
	/*  */
	#define E902070003_CPULOAD_INT 6
	/*  */
	#define E902070003_CLTOP_PROC1_VARCHAR 7
	/*  */
	#define E902070003_CLPROC1_VAL_INT 8
	/*  */
	#define E902070003_CLTOP_PROC2_VARCHAR 9
	/*  */
	#define E902070003_CLPROC2_VAL_INT 10
	/*  */
	#define E902070003_CLTOP_PROC3_VARCHAR 11
	/*  */
	#define E902070003_CLPROC3_VAL_INT 12
	/*  */
	#define E902070003_FREEMEM_INT 13
	/*  */
	#define E902070003_FREEDISK_INT 14
	/*  */
	#define E902070003_LIMIT_FREQ_INT 15
	/*  */
	#define E902070003_BROOTED_INT 16
	/*  */
	#define E902070003_BMODEMLOGON_INT 17
	/*  */
	#define E902070003_BUARTENABL_INT 18
	/*  */
	#define E902070003_NPERFBUGSETTINGS_INT 19
	/*  */
	#define E902070003_IAWARE_INT 20
	/*  */
	#define E902070003_NRESERVE1_INT 21
	/*  */
	#define E902070003_STRRESERVE2_VARCHAR 22

	/* Event 902070100
		other respond */
	/* Performance Scene Name */
	#define E902070100_CASENAME_VARCHAR 0
	/* Error Level */
	#define E902070100_RESULT_INT 1
	/*  */
	#define E902070100_TOTALTIMESPENT_INT 2
	/*  */
	#define E902070100_ARG1_VARCHAR 3
	/*  */
	#define E902070100_ARG2_INT 4
	/*  */
	#define E902070100_VERSION_VARCHAR 5
	/*  */
	#define E902070100_CPULOAD_INT 6
	/*  */
	#define E902070100_CLTOP_PROC1_VARCHAR 7
	/*  */
	#define E902070100_CLPROC1_VAL_INT 8
	/*  */
	#define E902070100_CLTOP_PROC2_VARCHAR 9
	/*  */
	#define E902070100_CLPROC2_VAL_INT 10
	/*  */
	#define E902070100_CLTOP_PROC3_VARCHAR 11
	/*  */
	#define E902070100_CLPROC3_VAL_INT 12
	/*  */
	#define E902070100_FREEMEM_INT 13
	/*  */
	#define E902070100_FREEDISK_INT 14
	/*  */
	#define E902070100_LIMIT_FREQ_INT 15
	/*  */
	#define E902070100_BROOTED_INT 16
	/*  */
	#define E902070100_BMODEMLOGON_INT 17
	/*  */
	#define E902070100_BUARTENABL_INT 18
	/*  */
	#define E902070100_NPERFBUGSETTINGS_INT 19
	/*  */
	#define E902070100_IAWARE_INT 20
	/*  */
	#define E902070100_NRESERVE1_INT 21
	/*  */
	#define E902070100_STRRESERVE2_VARCHAR 22

	/* Event 902080000
		EMUI application business process slowy */
	/* Performance Scene Name */
	#define E902080000_CASENAME_VARCHAR 0
	/* Error Level */
	#define E902080000_RESULT_INT 1
	/*  */
	#define E902080000_TOTALTIMESPENT_INT 2
	/*  */
	#define E902080000_ARG1_VARCHAR 3
	/*  */
	#define E902080000_ARG2_INT 4
	/*  */
	#define E902080000_VERSION_VARCHAR 5
	/*  */
	#define E902080000_CPULOAD_INT 6
	/*  */
	#define E902080000_CLTOP_PROC1_VARCHAR 7
	/*  */
	#define E902080000_CLPROC1_VAL_INT 8
	/*  */
	#define E902080000_CLTOP_PROC2_VARCHAR 9
	/*  */
	#define E902080000_CLPROC2_VAL_INT 10
	/*  */
	#define E902080000_CLTOP_PROC3_VARCHAR 11
	/*  */
	#define E902080000_CLPROC3_VAL_INT 12
	/*  */
	#define E902080000_FREEMEM_INT 13
	/*  */
	#define E902080000_FREEDISK_INT 14
	/*  */
	#define E902080000_LIMIT_FREQ_INT 15
	/*  */
	#define E902080000_BROOTED_INT 16
	/*  */
	#define E902080000_BMODEMLOGON_INT 17
	/*  */
	#define E902080000_BUARTENABL_INT 18
	/*  */
	#define E902080000_NPERFBUGSETTINGS_INT 19
	/*  */
	#define E902080000_IAWARE_INT 20
	/*  */
	#define E902080000_NRESERVE1_INT 21
	/*  */
	#define E902080000_STRRESERVE2_VARCHAR 22

	/* Event 902090000
		Camera business process slowly */
	/* Performance Scene Name */
	#define E902090000_CASENAME_VARCHAR 0
	/* Error Level */
	#define E902090000_RESULT_INT 1
	/*  */
	#define E902090000_TOTALTIMESPENT_INT 2
	/*  */
	#define E902090000_ARG1_VARCHAR 3
	/*  */
	#define E902090000_ARG2_INT 4
	/*  */
	#define E902090000_VERSION_VARCHAR 5
	/*  */
	#define E902090000_CPULOAD_INT 6
	/*  */
	#define E902090000_CLTOP_PROC1_VARCHAR 7
	/*  */
	#define E902090000_CLPROC1_VAL_INT 8
	/*  */
	#define E902090000_CLTOP_PROC2_VARCHAR 9
	/*  */
	#define E902090000_CLPROC2_VAL_INT 10
	/*  */
	#define E902090000_CLTOP_PROC3_VARCHAR 11
	/*  */
	#define E902090000_CLPROC3_VAL_INT 12
	/*  */
	#define E902090000_FREEMEM_INT 13
	/*  */
	#define E902090000_FREEDISK_INT 14
	/*  */
	#define E902090000_LIMIT_FREQ_INT 15
	/*  */
	#define E902090000_BROOTED_INT 16
	/*  */
	#define E902090000_BMODEMLOGON_INT 17
	/*  */
	#define E902090000_BUARTENABL_INT 18
	/*  */
	#define E902090000_NPERFBUGSETTINGS_INT 19
	/*  */
	#define E902090000_IAWARE_INT 20
	/*  */
	#define E902090000_NRESERVE1_INT 21
	/*  */
	#define E902090000_STRRESERVE2_VARCHAR 22

	/* Event 902500000
		Key Application launching time */
	/* Performance Scene Name */
	#define E902500000_CASENAME_VARCHAR 0
	/*  */
	#define E902500000_STATSDURATION_INT 1
	/*  */
	#define E902500000_FIELDNAME_VARCHAR 2
	/*  */
	#define E902500000_VERSION_VARCHAR 3
	/*  */
	#define E902500000_CNT1_INT 4
	/*  */
	#define E902500000_CNT2_INT 5
	/*  */
	#define E902500000_CNT3_INT 6
	/*  */
	#define E902500000_CNT4_INT 7
	/*  */
	#define E902500000_CNT5_INT 8
	/*  */
	#define E902500000_CNT6_INT 9
	/*  */
	#define E902500000_CNT7_INT 10
	/*  */
	#define E902500000_CNT8_INT 11
	/*  */
	#define E902500000_CNT9_INT 12
	/*  */
	#define E902500000_CNT10_INT 13
	/*  */
	#define E902500000_CNT11_INT 14
	/*  */
	#define E902500000_CNT12_INT 15
	/*  */
	#define E902500000_CNT13_INT 16
	/*  */
	#define E902500000_CNT14_INT 17
	/*  */
	#define E902500000_CNT15_INT 18
	/*  */
	#define E902500000_CNT16_INT 19
	/*  */
	#define E902500000_CNT17_INT 20
	/*  */
	#define E902500000_CNT18_INT 21
	/*  */
	#define E902500000_CNT19_INT 22
	/*  */
	#define E902500000_CNT20_INT 23

	/* Event 902500001
		Wechat launching time */
	/* Performance Scene Name */
	#define E902500001_CASENAME_VARCHAR 0
	/*  */
	#define E902500001_STATSDURATION_INT 1
	/*  */
	#define E902500001_FIELDNAME_VARCHAR 2
	/*  */
	#define E902500001_VERSION_VARCHAR 3
	/*  */
	#define E902500001_CNT1_INT 4
	/*  */
	#define E902500001_CNT2_INT 5
	/*  */
	#define E902500001_CNT3_INT 6
	/*  */
	#define E902500001_CNT4_INT 7
	/*  */
	#define E902500001_CNT5_INT 8
	/*  */
	#define E902500001_CNT6_INT 9
	/*  */
	#define E902500001_CNT7_INT 10
	/*  */
	#define E902500001_CNT8_INT 11
	/*  */
	#define E902500001_CNT9_INT 12
	/*  */
	#define E902500001_CNT10_INT 13
	/*  */
	#define E902500001_CNT11_INT 14
	/*  */
	#define E902500001_CNT12_INT 15
	/*  */
	#define E902500001_CNT13_INT 16
	/*  */
	#define E902500001_CNT14_INT 17
	/*  */
	#define E902500001_CNT15_INT 18
	/*  */
	#define E902500001_CNT16_INT 19
	/*  */
	#define E902500001_CNT17_INT 20
	/*  */
	#define E902500001_CNT18_INT 21
	/*  */
	#define E902500001_CNT19_INT 22
	/*  */
	#define E902500001_CNT20_INT 23

	/* Event 902500002
		Key Application skip frames */
	/* Performance Scene Name */
	#define E902500002_CASENAME_VARCHAR 0
	/*  */
	#define E902500002_STATSDURATION_INT 1
	/*  */
	#define E902500002_FIELDNAME_VARCHAR 2
	/*  */
	#define E902500002_VERSION_VARCHAR 3
	/*  */
	#define E902500002_CNT1_INT 4
	/*  */
	#define E902500002_CNT2_INT 5
	/*  */
	#define E902500002_CNT3_INT 6
	/*  */
	#define E902500002_CNT4_INT 7
	/*  */
	#define E902500002_CNT5_INT 8
	/*  */
	#define E902500002_CNT6_INT 9
	/*  */
	#define E902500002_CNT7_INT 10
	/*  */
	#define E902500002_CNT8_INT 11
	/*  */
	#define E902500002_CNT9_INT 12
	/*  */
	#define E902500002_CNT10_INT 13
	/*  */
	#define E902500002_CNT11_INT 14
	/*  */
	#define E902500002_CNT12_INT 15
	/*  */
	#define E902500002_CNT13_INT 16
	/*  */
	#define E902500002_CNT14_INT 17
	/*  */
	#define E902500002_CNT15_INT 18
	/*  */
	#define E902500002_CNT16_INT 19
	/*  */
	#define E902500002_CNT17_INT 20
	/*  */
	#define E902500002_CNT18_INT 21
	/*  */
	#define E902500002_CNT19_INT 22
	/*  */
	#define E902500002_CNT20_INT 23

	/* Event 902500003
		Wechat skip frames */
	/* Performance Scene Name */
	#define E902500003_CASENAME_VARCHAR 0
	/*  */
	#define E902500003_STATSDURATION_INT 1
	/*  */
	#define E902500003_FIELDNAME_VARCHAR 2
	/*  */
	#define E902500003_VERSION_VARCHAR 3
	/*  */
	#define E902500003_CNT1_INT 4
	/*  */
	#define E902500003_CNT2_INT 5
	/*  */
	#define E902500003_CNT3_INT 6
	/*  */
	#define E902500003_CNT4_INT 7
	/*  */
	#define E902500003_CNT5_INT 8
	/*  */
	#define E902500003_CNT6_INT 9
	/*  */
	#define E902500003_CNT7_INT 10
	/*  */
	#define E902500003_CNT8_INT 11
	/*  */
	#define E902500003_CNT9_INT 12
	/*  */
	#define E902500003_CNT10_INT 13
	/*  */
	#define E902500003_CNT11_INT 14
	/*  */
	#define E902500003_CNT12_INT 15
	/*  */
	#define E902500003_CNT13_INT 16
	/*  */
	#define E902500003_CNT14_INT 17
	/*  */
	#define E902500003_CNT15_INT 18
	/*  */
	#define E902500003_CNT16_INT 19
	/*  */
	#define E902500003_CNT17_INT 20
	/*  */
	#define E902500003_CNT18_INT 21
	/*  */
	#define E902500003_CNT19_INT 22
	/*  */
	#define E902500003_CNT20_INT 23

	/* Event 902500004
		Other performance scenes */
	/* Performance Scene Name */
	#define E902500004_CASENAME_VARCHAR 0
	/*  */
	#define E902500004_STATSDURATION_INT 1
	/*  */
	#define E902500004_FIELDNAME_VARCHAR 2
	/*  */
	#define E902500004_VERSION_VARCHAR 3
	/*  */
	#define E902500004_CNT1_INT 4
	/*  */
	#define E902500004_CNT2_INT 5
	/*  */
	#define E902500004_CNT3_INT 6
	/*  */
	#define E902500004_CNT4_INT 7
	/*  */
	#define E902500004_CNT5_INT 8
	/*  */
	#define E902500004_CNT6_INT 9
	/*  */
	#define E902500004_CNT7_INT 10
	/*  */
	#define E902500004_CNT8_INT 11
	/*  */
	#define E902500004_CNT9_INT 12
	/*  */
	#define E902500004_CNT10_INT 13
	/*  */
	#define E902500004_CNT11_INT 14
	/*  */
	#define E902500004_CNT12_INT 15
	/*  */
	#define E902500004_CNT13_INT 16
	/*  */
	#define E902500004_CNT14_INT 17
	/*  */
	#define E902500004_CNT15_INT 18
	/*  */
	#define E902500004_CNT16_INT 19
	/*  */
	#define E902500004_CNT17_INT 20
	/*  */
	#define E902500004_CNT18_INT 21
	/*  */
	#define E902500004_CNT19_INT 22
	/*  */
	#define E902500004_CNT20_INT 23

	/* Event 902500005
		UBM */
	/* Performance Scene Name */
	#define E902500005_CASENAME_VARCHAR 0

	/* Event 902500006
		iAWare bigdata */
	/* Performance Scene Name */
	#define E902500006_CASENAME_VARCHAR 0

/*** PowerThermal events' keys ***/

	/* Event 903001000
		Base power consumption of day/hour */
	/* The stats start time */
	#define E903001000_FROMTIME_DATETIME 0
	/* The stats end time */
	#define E903001000_TOTIME_DATETIME 1
	/* Sim card type */
	#define E903001000_SIMCARDTYPE_VARCHAR 2
	/* Total battery drop */
	#define E903001000_TOTALBATDROP_INT 3
	/* Screen On time(seconds) */
	#define E903001000_SCRNONTIME_INT 4
	/* Screen Off time(seconds) */
	#define E903001000_SCRNOFFTIME_INT 5
	/* Battery drop during Screen On */
	#define E903001000_SCRNONBATDROP_INT 6
	/* Battery drop during Screen Off */
	#define E903001000_SCRNOFFBATDROP_INT 7
	/* Unstandby time during screen off */
	#define E903001000_SCRNOFFUNSTANDBYTIME_INT 8
	/* Standby bat drop during night */
	#define E903001000_NIGHTSTANDBYBATDROP_INT 9
	/* Charging time during the stats time(seconds) */
	#define E903001000_CHARGINGTIME_INT 10
	/* Phone call time during the stats time(seconds) */
	#define E903001000_PHONECALLTIME_INT 11
	/* Battery capacity */
	#define E903001000_BATCAPACITY_INT 12
	/* The times of battery charge */
	#define E903001000_BATCHARGETIMES_INT 13
	/* Wifi opend time */
	#define E903001000_WIFIOPENTIME_INT 14
	/* Wifi ap opened time */
	#define E903001000_WIFIAPOPENTIME_INT 15
	/* Mobile data enabled time */
	#define E903001000_MOBILEDATAOPENTIME_INT 16
	/* Net switch times */
	#define E903001000_NETSWITCHTIMES_INT 17
	/* Ptm version */
	#define E903001000_PTMVERSION_VARCHAR 18

	/* Event 903001001
		Screen backlight info of day/hour */
	/* The stats start time */
	#define E903001001_FROMTIME_DATETIME 0
	/* The stats end time */
	#define E903001001_TOTIME_DATETIME 1
	/* Screen dark time(seconds) */
	#define E903001001_SCREENDARKTIME_INT 2
	/* Sceen dim time(seconds) */
	#define E903001001_SCREENDIMTIME_INT 3
	/* Screen medium time(seconds) */
	#define E903001001_SCREENMEDIUMTIME_INT 4
	/* Screen light time(seconds) */
	#define E903001001_SCREENLIGHTTIME_INT 5
	/* Screen bright time(seconds) */
	#define E903001001_SCREENBRIGHTTIME_INT 6

	/* Event 903001002
		Phone staying time on signal specific state for day/hour */
	/* The stats start time */
	#define E903001002_FROMTIME_DATETIME 0
	/* The stats end time */
	#define E903001002_TOTIME_DATETIME 1
	/* No singal time(seconds) */
	#define E903001002_SIGNALNONETIME_INT 2
	/* Signal poor time(seconds) */
	#define E903001002_SIGNALPOORTIME_INT 3
	/* Signal moderate time(seconds) */
	#define E903001002_SIGNALMODERATETIME_INT 4
	/* Signal good time(seconds) */
	#define E903001002_SIGNALGOODTIME_INT 5
	/* Signal greate time(seconds) */
	#define E903001002_SIGNALGREATTIME_INT 6

	/* Event 903001003
		Wake lock info */
	/* The stats start time */
	#define E903001003_FROMTIME_DATETIME 0
	/* The stats end time */
	#define E903001003_TOTIME_DATETIME 1
	/* Wakelock type */
	#define E903001003_WAKELOCKTYPE_VARCHAR 2
	/* Uid */
	#define E903001003_UID_VARCHAR 3
	/* Package name of uid */
	#define E903001003_PKG_VARCHAR 4
	/* Wakelock name */
	#define E903001003_WAKELOCKNAME_VARCHAR 5
	/* Wakelock duration time(seconds) */
	#define E903001003_WAKELOCKDURATION_INT 6
	/* Wakelock times */
	#define E903001003_WAKELOCKTIMES_INT 7

	/* Event 903001004
		Wakeup resource for day/hour */
	/* The stats start time */
	#define E903001004_FROMTIME_DATETIME 0
	/* The stats end time */
	#define E903001004_TOTIME_DATETIME 1
	/* Wakeup reason type */
	#define E903001004_WAKEUPREASONTYPE_VARCHAR 2
	/* Wakelock name */
	#define E903001004_WAKEUPREASONNAME_VARCHAR 3
	/* Wakelock duration time(seconds) */
	#define E903001004_WAKEUPREASONDURATION_INT 4
	/* Wakelock times */
	#define E903001004_WAKEUPREASONTIMES_INT 5

	/* Event 903001005
		Alarm info for day/hour */
	/* The stats start time */
	#define E903001005_FROMTIME_DATETIME 0
	/* The stats end time */
	#define E903001005_TOTIME_DATETIME 1
	/* Alarm name */
	#define E903001005_ALARMNAME_VARCHAR 2
	/* Alarm times */
	#define E903001005_ALARMTIMES_INT 3

	/* Event 903001006
		Day/Hour Data RxTx stats */
	/* The stats start time */
	#define E903001006_FROMTIME_DATETIME 0
	/* The stats end time */
	#define E903001006_TOTIME_DATETIME 1
	/* Mobile Rx Kbytes */
	#define E903001006_MOBILERXTOTALBYTES_FLOAT 2
	/* Mobile Tx Kbytes */
	#define E903001006_MOBILETXTOTALBYTES_FLOAT 3
	/* WIFI Rx Kbytes */
	#define E903001006_WIFIRXTOTALBYTES_FLOAT 4
	/* WIFI Tx Kbytes */
	#define E903001006_WIFITXTOTALBYTES_FLOAT 5

	/* Event 903001007
		CPU usage top proc */
	/* The stats start time */
	#define E903001007_FROMTIME_DATETIME 0
	/* The stats end time */
	#define E903001007_TOTIME_DATETIME 1
	/* Proc name */
	#define E903001007_PROCNAME_VARCHAR 2
	/* proc use time(User & kernel)(seconds) */
	#define E903001007_PROCUSETIME_INT 3

	/* Event 903001008
		Gps usage info for day/hour */
	/* Stats start time per hour */
	#define E903001008_FROMTIME_DATETIME 0
	/* Stats end time per hour */
	#define E903001008_TOTIME_DATETIME 1
	/* Resource hold gps */
	#define E903001008_HOLDPKG_VARCHAR 2
	/* Resource holding time duration(seconds) */
	#define E903001008_HOLDDURATION_INT 3
	/* Resource holding times */
	#define E903001008_HOLDTIMES_INT 4

	/* Event 903001009
		Power consume detail */
	/* The stats start time */
	#define E903001009_FROMTIME_DATETIME 0
	/* The stats end time */
	#define E903001009_TOTIME_DATETIME 1
	/* Application name */
	#define E903001009_APKNAME_VARCHAR 2
	/* Proc name */
	#define E903001009_PRONAME_VARCHAR 3
	/* MAh total consume */
	#define E903001009_MAHTOTAL_FLOAT 4
	/* Cpu background time(seconds) */
	#define E903001009_CPUBG_INT 5
	/* Cpu foreground time(seconds) */
	#define E903001009_CPUTOTAL_INT 6
	/* Wakelock time(seconds) */
	#define E903001009_WAKELOCK_INT 7
	/* Gps time(seconds) */
	#define E903001009_GPSTIME_INT 8
	/* Camera time(seconds) */
	#define E903001009_CAMERATIME_INT 9
	/* Flashlinght time(seconds) */
	#define E903001009_FLASHLIGHTTIME_INT 10
	/* Mobile power consume */
	#define E903001009_MAHMOBILE_FLOAT 11
	/* Wifi power consume */
	#define E903001009_MAHWIFI_FLOAT 12
	/* Sensor power consume */
	#define E903001009_MAHSENSOR_FLOAT 13

	/* Event 903001010
		Phone running-change states */
	/* Time */
	#define E903001010_TIME_DATETIME 0
	/* Operational events */
	#define E903001010_EVENT_VARCHAR 1
	/* Operational states */
	#define E903001010_STATE_VARCHAR 2

	/* Event 903001011
		Power consumption states Info */
	/* Time */
	#define E903001011_TIME_DATETIME 0
	/* Powergenie mode */
	#define E903001011_PGMODE_TINYINT 1
	/* Backlight value */
	#define E903001011_BACKLIGHT_INT 2
	/* Discharge current */
	#define E903001011_DISCHARGING_INT 3
	/* AP temperature */
	#define E903001011_APTEMP_TINYINT 4
	/* PA temperature */
	#define E903001011_PATEMP_TINYINT 5
	/* CUP temperature */
	#define E903001011_CPUTEMP_TINYINT 6
	/* Gpu temperature */
	#define E903001011_GPUTEMP_TINYINT 7
	/* The frequency of CPU big core */
	#define E903001011_CPUFREQBIG_INT 8
	/* The frequency of CPU little core */
	#define E903001011_CPUFREQLITTLE_INT 9
	/* The frequency of DDR */
	#define E903001011_DDRFREQ_INT 10
	/* The frequency of GPU */
	#define E903001011_GPUFREQ_INT 11

	/* Event 903001012
		Temperature Info */
	/* Sampling Time */
	#define E903001012_TIME_DATETIME 0
	/* Triggering event */
	#define E903001012_TAG_VARCHAR 1
	/* Computed case temperature */
	#define E903001012_CASETEMP_TINYINT 2
	/* AP temperature */
	#define E903001012_APTEMP_TINYINT 3
	/* PMIC temperature */
	#define E903001012_CHARGETEMP_TINYINT 4
	/* Flash temperature */
	#define E903001012_FLASHTEMP_TINYINT 5
	/* PA temperature */
	#define E903001012_PATEMP_TINYINT 6
	/* Battery temperature */
	#define E903001012_BATTERYTEMP_TINYINT 7
	/* CPU temperature */
	#define E903001012_CPUTEMP_TINYINT 8
	/* GPU temperature */
	#define E903001012_GPUTEMP_TINYINT 9

	/* Event 903001013
		Time statistics of foreground application */
	/* Sampling Time */
	#define E903001013_TIME_DATETIME 0
	/* Foreground application */
	#define E903001013_FOREAPK_VARCHAR 1
	/* The time last for the APK(seconds) */
	#define E903001013_TIMELAST_INT 2

	/* Event 903001014
		Audio status Info */
	/* Sampling Time */
	#define E903001014_TIME_DATETIME 0
	/* Audio model */
	#define E903001014_AUDIOMODEL_VARCHAR 1
	/* Music player APK */
	#define E903001014_MUSICAPK_VARCHAR 2
	/* volume */
	#define E903001014_VOLUME_INT 3
	/* software at zero volume */
	#define E903001014_SOFTFLOW_INT 4
	/* Audio parameter */
	#define E903001014_AUDIOPARM_VARCHAR 5

	/* Event 903001015
		Application power consumption information(every hour) */
	/* Start Time */
	#define E903001015_STARTTIME_DATETIME 0
	/* End Time */
	#define E903001015_ENDTIME_DATETIME 1
	/* Application name */
	#define E903001015_APPNAME_VARCHAR 2
	/* Wakeup information */
	#define E903001015_WAKEUPPOWER_VARCHAR 3
	/* Screen brightness power consumption */
	#define E903001015_BRIGHTNESSPOWER_VARCHAR 4
	/* CPU power consumption */
	#define E903001015_CPUPOWER_VARCHAR 5
	/* GPS power consumption */
	#define E903001015_GPSPOWER_VARCHAR 6
	/* Wakelock power consumption */
	#define E903001015_WAKELOCKPOWER_VARCHAR 7
	/* Sensors power consumption */
	#define E903001015_SENSORPOWER_VARCHAR 8
	/* GPU power consumption */
	#define E903001015_GPUPOWER_VARCHAR 9
	/* Camera power consumption */
	#define E903001015_CAMERAPOWER_VARCHAR 10
	/* Flashlight power consumption */
	#define E903001015_FLASHLIGHTPOWER_VARCHAR 11
	/* Audio power consumption */
	#define E903001015_AUDIOPOWER_VARCHAR 12
	/* Connectivity power consumption */
	#define E903001015_CONNECTIVITYPOWER_VARCHAR 13

	/* Event 903001016
		IP load monitor */
	/* Start Time */
	#define E903001016_STARTTIME_DATETIME 0
	/* End Time */
	#define E903001016_ENDTIME_DATETIME 1
	/* IP name */
	#define E903001016_NAME_VARCHAR 2
	/* IP off time */
	#define E903001016_OFFTIME_INT 3
	/* IP busy time */
	#define E903001016_BUSYTIME_INT 4
	/* IP low volt busy time */
	#define E903001016_LOWVOLTBUSYTIME_INT 5
	/* IP idle time */
	#define E903001016_IDLETIME_INT 6
	/* IP power consumption */
	#define E903001016_POWER_FLOAT 7

	/* Event 903001017
		Modem GSM information statistics */
	/* Start Time */
	#define E903001017_STARTTIME_DATETIME 0
	/* End Time */
	#define E903001017_ENDTIME_DATETIME 1
	/* Rat Type */
	#define E903001017_RATTYPE_SMALLINT 2
	/* Information space capacity */
	#define E903001017_INFOCAPACITY_SMALLINT 3
	/* Search network total time */
	#define E903001017_SEARCHTIME_INT 4
	/* Search network count */
	#define E903001017_SEARCHCOUNT_INT 5
	/* Idle total time */
	#define E903001017_IDLETIME_INT 6
	/* Idle DRX total count */
	#define E903001017_IDLEDRXCOUNT_INT 7
	/* cs voice total time */
	#define E903001017_CSTIME_INT 8
	/* cs voice low tx power time */
	#define E903001017_CSTXPWRLOW_INT 9
	/* cs voice middle tx power time */
	#define E903001017_CSTXPWRMID_INT 10
	/* cs voice high tx power time */
	#define E903001017_CSTXPWRHIGH_INT 11
	/* ps data total time */
	#define E903001017_PSTIME_INT 12
	/* ps data low tx power time */
	#define E903001017_PSTXPWRLOW_INT 13
	/* ps data middle tx power time */
	#define E903001017_PSTXPWRMID_INT 14
	/* ps data high tx power time */
	#define E903001017_PSTXPWRHIGH_INT 15
	/* DRX count of which during time less than 15ms */
	#define E903001017_DRXCOUNT15_INT 16
	/* DRX count of which during time less than Xms */
	#define E903001017_DRXCOUNTX_INT 17
	/* Received signal strength in weak signal */
	#define E903001017_RSSIWEAKTIME_INT 18
	/* Received signal strength in middle signal */
	#define E903001017_RSSIMIDTIME_INT 19
	/* Received signal strength in strong signal */
	#define E903001017_RSSISTRONGTIME_INT 20
	/* Neighbor cell measurement count less than X */
	#define E903001017_NCELLMEASCOUNTX_INT 21
	/* Neighbor cell measurement count span */
	#define E903001017_NCELLMEASSPAN_INT 22
	/* Inter Rat measurement total count */
	#define E903001017_INTERRATMEASCOUNT_INT 23
	/* Class10 total time */
	#define E903001017_CLASS10TIME_INT 24
	/* ClassX total time */
	#define E903001017_CLASSXTIME_INT 25
	/* Neighbor cell measurement count less */
	#define E903001017_NCELLMEASCOUNTLESS_INT 26
	/* Neighbor cell measurement count mid */
	#define E903001017_NCELLMEASCOUNTMID_INT 27
	/* Neighbor cell measurement count more */
	#define E903001017_NCELLMEASCOUNTMORE_INT 28

	/* Event 903001018
		Modem WCDMA information statistics */
	/* Start Time */
	#define E903001018_STARTTIME_DATETIME 0
	/* End Time */
	#define E903001018_ENDTIME_DATETIME 1
	/* Rat Type */
	#define E903001018_RATTYPE_SMALLINT 2
	/* Information space capacity */
	#define E903001018_INFOCAPACITY_SMALLINT 3
	/* Search network total time */
	#define E903001018_SEARCHTIME_INT 4
	/* Search network count */
	#define E903001018_SEARCHCOUNT_INT 5
	/* Idle total time */
	#define E903001018_IDLETIME_INT 6
	/* Idle DRX total count */
	#define E903001018_IDLEDRXCOUNT_INT 7
	/* cs voice total time */
	#define E903001018_CSTIME_INT 8
	/* cs voice low tx power time */
	#define E903001018_CSTXPWRLOW_INT 9
	/* cs voice middle tx power time */
	#define E903001018_CSTXPWRMID_INT 10
	/* cs voice high tx power time */
	#define E903001018_CSTXPWRHIGH_INT 11
	/* ps data total time */
	#define E903001018_PSTIME_INT 12
	/* ps data low tx power time */
	#define E903001018_PSTXPWRLOW_INT 13
	/* ps data middle tx power time */
	#define E903001018_PSTXPWRMID_INT 14
	/* ps data high tx power time */
	#define E903001018_PSTXPWRHIGH_INT 15
	/* DRX count of which during time less than 15ms */
	#define E903001018_DRXCOUNT15_INT 16
	/* DRX count of which during time less than Xms */
	#define E903001018_DRXCOUNTX_INT 17
	/* Received signal strength in weak signal */
	#define E903001018_RSCPWEAKTIME_INT 18
	/* Received signal strength in middle signal */
	#define E903001018_RSCPMIDTIME_INT 19
	/* Received signal strength in strong signal */
	#define E903001018_RSCPSTRONGTIME_INT 20
	/* Neighbor cell measurement count less than X */
	#define E903001018_NCELLMEASCOUNTX_INT 21
	/* Neighbor cell measurement count span */
	#define E903001018_NCELLMEASSPAN_INT 22
	/* Inter Rat measurement total count */
	#define E903001018_INTERRATMEASCOUNT_INT 23
	/* FET Count */
	#define E903001018_FETCOUNT_INT 24

	/* Event 903001019
		Modem 1X information statistics */
	/* Start Time */
	#define E903001019_STARTTIME_DATETIME 0
	/* End Time */
	#define E903001019_ENDTIME_DATETIME 1
	/* Rat Type */
	#define E903001019_RATTYPE_SMALLINT 2
	/* Information space capacity */
	#define E903001019_INFOCAPACITY_SMALLINT 3
	/* Search network total time */
	#define E903001019_SEARCHTIME_INT 4
	/* Search network count */
	#define E903001019_SEARCHCOUNT_INT 5
	/* Idle total time */
	#define E903001019_IDLETIME_INT 6
	/* cs voice total time */
	#define E903001019_CSTIME_INT 7
	/* cs voice low tx power time */
	#define E903001019_CSTXPWRLOW_INT 8
	/* cs voice middle tx power time */
	#define E903001019_CSTXPWRMID_INT 9
	/* cs voice high tx power time */
	#define E903001019_CSTXPWRHIGH_INT 10
	/* ps data total time */
	#define E903001019_PSTIME_INT 11
	/* ps data low tx power time */
	#define E903001019_PSTXPWRLOW_INT 12
	/* ps data middle tx power time */
	#define E903001019_PSTXPWRMID_INT 13
	/* ps data high tx power time */
	#define E903001019_PSTXPWRHIGH_INT 14
	/* Received signal strength in weak signal */
	#define E903001019_ECN0WEAKTIME_INT 15
	/* Received signal strength in middle signal */
	#define E903001019_ECN0MIDTIME_INT 16
	/* Received signal strength in strong signal */
	#define E903001019_ECN0STRONGTIME_INT 17
	/* Idle PCH DRX total count */
	#define E903001019_PCHDRXCOUNT_INT 18
	/* DRX count of which PCH time less than 80ms */
	#define E903001019_PCHDRXCOUNT80_INT 19
	/* DRX count of which PCH time more than 160ms */
	#define E903001019_PCHDRXCOUNT160_INT 20
	/* Idle QPCH DRX total count */
	#define E903001019_QPCHDRXCOUNT_INT 21
	/* DRX count of which PCH time more than 60ms */
	#define E903001019_QPCHDRXCOUNT60_INT 22
	/* Neighbor cell measurement count less than 30 */
	#define E903001019_NCELLMEASCOUNT30_INT 23
	/* Neighbor cell measurement count more than 60 */
	#define E903001019_NCELLMEASCOUNT60_INT 24

	/* Event 903001020
		Modem EVDO information statistics */
	/* Start Time */
	#define E903001020_STARTTIME_DATETIME 0
	/* End Time */
	#define E903001020_ENDTIME_DATETIME 1
	/* Rat Type */
	#define E903001020_RATTYPE_SMALLINT 2
	/* Information space capacity */
	#define E903001020_INFOCAPACITY_SMALLINT 3
	/* Search network total time */
	#define E903001020_SEARCHTIME_INT 4
	/* Search network count */
	#define E903001020_SEARCHCOUNT_INT 5
	/* Idle total time */
	#define E903001020_IDLETIME_INT 6
	/* Idle DRX total count */
	#define E903001020_IDLEDRXCOUNT_INT 7
	/* ps data total time */
	#define E903001020_PSTIME_INT 8
	/* ps data low tx power time */
	#define E903001020_PSTXPWRLOW_INT 9
	/* ps data middle tx power time */
	#define E903001020_PSTXPWRMID_INT 10
	/* ps data high tx power time */
	#define E903001020_PSTXPWRHIGH_INT 11
	/* Received signal strength in weak signal */
	#define E903001020_ECN0WEAKTIME_INT 12
	/* Received signal strength in middle signal */
	#define E903001020_ECN0MIDTIME_INT 13
	/* Received signal strength in strong signal */
	#define E903001020_ECN0STRONGTIME_INT 14
	/* Inter Rat measurement total count */
	#define E903001020_INTERRATMEASCOUNT_INT 15
	/* DRX count of which during time less than 80ms */
	#define E903001020_DRXCOUNT80_INT 16
	/* DRX count of which during time more than 160ms */
	#define E903001020_DRXCOUNT160_INT 17
	/* Neighbor cell measurement count less than 30 */
	#define E903001020_NCELLMEASCOUNT30_INT 18
	/* Neighbor cell measurement count more than 60 */
	#define E903001020_NCELLMEASCOUNT60_INT 19

	/* Event 903001021
		Modem TDS information statistics */
	/* Start Time */
	#define E903001021_STARTTIME_DATETIME 0
	/* End Time */
	#define E903001021_ENDTIME_DATETIME 1
	/* Rat Type */
	#define E903001021_RATTYPE_SMALLINT 2
	/* Information space capacity */
	#define E903001021_INFOCAPACITY_SMALLINT 3
	/* Search network total time */
	#define E903001021_SEARCHTIME_INT 4
	/* Search network count */
	#define E903001021_SEARCHCOUNT_INT 5
	/* Idle total time */
	#define E903001021_IDLETIME_INT 6
	/* Idle DRX total count */
	#define E903001021_IDLEDRXCOUNT_INT 7
	/* cs total time */
	#define E903001021_CSTIME_INT 8
	/* ps total time */
	#define E903001021_PSTIME_INT 9
	/* Idle total inter freq meas count */
	#define E903001021_INTERMEASCOUNT_INT 10
	/* Idle total inter freq meas time */
	#define E903001021_INTERMEASTIME_INT 11
	/* Idle total irat Gsm meas count */
	#define E903001021_IRATGMEASCOUNT_INT 12
	/* Idle total irat Gsm meas time */
	#define E903001021_IRATGMEASTIME_INT 13
	/* Idle total irat lte meas count */
	#define E903001021_IRATLMEASCOUNT_INT 14
	/* Idle total irat lte meas time */
	#define E903001021_IRATLMEASTIME_INT 15
	/* Received signal strength in weak signal */
	#define E903001021_RSCPWEAKCOUNT_INT 16
	/* Received signal strength in middle signal */
	#define E903001021_RSCPMIDCOUNT_INT 17
	/* Received signal strength in strong signal */
	#define E903001021_RSCPSTRONGCOUNT_INT 18
	/* Time length of high Tx power */
	#define E903001021_TXPWRHIGH_INT 19
	/* Time length of middle Tx power */
	#define E903001021_TXPWRMID_INT 20
	/* Time length of low Tx power */
	#define E903001021_TXPWRLOW_INT 21
	/* Time Slice of enter DCH */
	#define E903001021_DCHENTERTIME_INT 22
	/* Time Slice of exit DCH */
	#define E903001021_DCHEXISTTIME_INT 23

	/* Event 903001022
		Modem LTE information statistics */
	/* Start Time */
	#define E903001022_STARTTIME_DATETIME 0
	/* End Time */
	#define E903001022_ENDTIME_DATETIME 1
	/* Rat Type */
	#define E903001022_RATTYPE_SMALLINT 2
	/* Information space capacity */
	#define E903001022_INFOCAPACITY_SMALLINT 3
	/* Search network total time */
	#define E903001022_SEARCHTIME_INT 4
	/* Search network count */
	#define E903001022_SEARCHCOUNT_INT 5
	/* Idle total time */
	#define E903001022_IDLETIME_INT 6
	/* Idle DRX total count */
	#define E903001022_IDLEDRXCOUNT_INT 7
	/* ps low tx power time */
	#define E903001022_PSTXPWRLOW_INT 8
	/* ps middle tx power time */
	#define E903001022_PSTXPWRMID_INT 9
	/* ps high tx power time */
	#define E903001022_PSTXPWRHIGH_INT 10
	/* back ground search LTE count */
	#define E903001022_BGLCOUNT_INT 11
	/* Idle total inter freq meas count */
	#define E903001022_INTERMEASCOUNT_INT 12
	/* Idle total inter freq meas time */
	#define E903001022_INTERMEASTIME_INT 13
	/* Idle total irat Gsm meas count */
	#define E903001022_IRATGMEASCOUNT_INT 14
	/* Idle total irat Gsm meas time */
	#define E903001022_IRATGMEASTIME_INT 15
	/* Idle total irat Tds meas count */
	#define E903001022_IRATTMEASCOUNT_INT 16
	/* Idle total irat Tds meas time */
	#define E903001022_IRATTMEASTIME_INT 17
	/* Idle total irat Wcdma meas count */
	#define E903001022_IRATWMEASCOUNT_INT 18
	/* Idle total irat Wcdma meas time */
	#define E903001022_IRATWMEASTIME_INT 19
	/* Idle total irat 1x meas count */
	#define E903001022_IRATCMEASCOUNT_INT 20
	/* Idle total irat 1x meas time */
	#define E903001022_IRATCMEASTIME_INT 21
	/* Received signal strength in weak signal */
	#define E903001022_SRSRPWEAKCOUNT_INT 22
	/* Received signal strength in middle signal */
	#define E903001022_SRSRPMIDCOUNT_INT 23
	/* Received signal strength in strong signal */
	#define E903001022_SRSRPSTRONGCOUNT_INT 24
	/* Connect total time */
	#define E903001022_CONNECTTIME_INT 25
	/* Time length of CDRX */
	#define E903001022_CDRXTIME_INT 26
	/* Time length of no tx in cdrx station */
	#define E903001022_CDRXNOTXTIME_INT 27
	/* Time Slice of last collection */
	#define E903001022_LASTTIMESLICE_INT 28

	/* Event 903001023
		Modem Driver information statistics */
	/* Start Time */
	#define E903001023_STARTTIME_DATETIME 0
	/* End Time */
	#define E903001023_ENDTIME_DATETIME 1
	/* Information space capacity */
	#define E903001023_INFOCAPACITY_SMALLINT 2
	/* Total count of suspend flow */
	#define E903001023_INTERPMSUSPENDCOUNT_INT 3
	/* Total count of resume flow */
	#define E903001023_INTERPMRESUMECOUNT_INT 4
	/* Max time of suspend */
	#define E903001023_SUSPENDMAXTIME_INT 5
	/* Average time of suspend */
	#define E903001023_SUSPENDAVGTIME_INT 6
	/* Min time of suspend */
	#define E903001023_SUSPENDMINTIME_INT 7
	/* Max time of resume */
	#define E903001023_RESUMEMAXTIME_INT 8
	/* Average time of resume */
	#define E903001023_RESUMEAVGTIME_INT 9
	/* Min time of resume */
	#define E903001023_RESUMEMINTIME_INT 10
	/* Total sleep time of C core */
	#define E903001023_INTERSLEEPTIME_INT 11
	/* Total work time of C core */
	#define E903001023_INTERWOKTIME_INT 12
	/* Count of interrupt wake up */
	#define E903001023_INTERRUPTWAKEUPCOUNT_VARCHAR 13
	/* Time of interrupt wake up */
	#define E903001023_INTERRUPTWAKEUPTIME_VARCHAR 14
	/* Time of holding wake lock */
	#define E903001023_WAKELOCKTIME_VARCHAR 15

	/* Event 903001024
		Background application power control */
	/* Start Time */
	#define E903001024_STARTTIME_DATETIME 0
	/* End Time */
	#define E903001024_ENDTIME_DATETIME 1
	/* Apps which are cleaned when screen off */
	#define E903001024_SCREENOFFCLEAN_VARCHAR 2
	/* Important apps which are protected */
	#define E903001024_BEPROTECTED_VARCHAR 3
	/* High power apps which are cleaned */
	#define E903001024_HIGHPOWERCLEAN_VARCHAR 4
	/* Apps which are self start frequently */
	#define E903001024_REPEATSELFSTART_VARCHAR 5
	/* Reasons which app can not enter hibernation of power
		genie */
	#define E903001024_NOHIBERNATIONREASON_VARCHAR 6
	/* Reasons which app exits from hibernation of power genie */
	#define E903001024_EXITHIBERNATIONREASON_VARCHAR 7

	/* Event 903002000
		Abnormal kernel workque power consumption */
	/* Abnornal workque name */
	#define E903002000_WORKQUENAME_VARCHAR 0
	/* Abnornal workque running time */
	#define E903002000_WORKQUETIME_INT 1
	/* Abnornal workque running times */
	#define E903002000_WORKQUETIMES_INT 2
	/* Abnormal count start time */
	#define E903002000_ABSTARTIME_DATETIME 3

	/* Event 903002001
		Abnormal process power consumption */
	/* High power process name */
	#define E903002001_THNAME_VARCHAR 0
	/* The power consume value of abnormal process */
	#define E903002001_TPCONSUME_INT 1
	/* Background process running time */
	#define E903002001_TPBTIME_INT 2
	/* Total process running time */
	#define E903002001_TPRTIME_INT 3
	/* Abnormal process gps time */
	#define E903002001_THGTIME_INT 4
	/* Abnormal process gps times */
	#define E903002001_THGTIMES_INT 5
	/* Abnormal wifi power consume */
	#define E903002001_TWIFICONSUME_INT 6
	/* Abnormal wifi lock time */
	#define E903002001_TWIFILOCKTIME_INT 7
	/* Abnormal data service power consume */
	#define E903002001_THDSPC_INT 8
	/* Frequent self restart process name */
	#define E903002001_SRPNAME_VARCHAR 9
	/* Frequent self restart process times */
	#define E903002001_SRPTIMES_INT 10
	/* Abnormal count start time */
	#define E903002001_ABSTARTIME_DATETIME 11

	/* Event 903002002
		Abnormal device power consumption */
	/* Invalid Lcd slef refresh */
	#define E903002002_LSRTIMES_INT 0
	/* Invalid rog */
	#define E903002002_ROG_INT 1
	/* Frequent sd scan times */
	#define E903002002_SSTIMES_INT 2
	/* Abnormal ddr capacity times */
	#define E903002002_DWLTIMES_INT 3
	/* Bat capacity leak value */
	#define E903002002_BATLEAK_INT 4
	/* Bat level bounce value */
	#define E903002002_BATGAP_INT 5
	/* Not normally closed power name during sleep */
	#define E903002002_SPON_VARCHAR 6
	/* Not normally closed power name during work */
	#define E903002002_DPOWERON_VARCHAR 7
	/* Not normally closed camera exception */
	#define E903002002_ABCAMERAON_INT 8
	/* Abnornal camera type */
	#define E903002002_CAMERATYPE_VARCHAR 9
	/* Frequent ble device scan times */
	#define E903002002_BSCANTIMES_INT 10
	/* Wifi power setting status */
	#define E903002002_WIFISTATUS_INT 11
	/* Abnormal count start time */
	#define E903002002_ABSTARTIME_DATETIME 12

	/* Event 903002003
		High frequency power consumption */
	/* Max cpu frequency scene */
	#define E903002003_MCFSCENE_VARCHAR 0
	/* Max gpu frequency scene */
	#define E903002003_MGFSCENE_VARCHAR 1
	/* Abnormal count start time */
	#define E903002003_ABSTARTIME_DATETIME 2

	/* Event 903002004
		Abnormal power consumption when screen on */
	/* Reduced battery level value when screen on */
	#define E903002004_BATLEVEL_INT 0
	/* Reduced battery level time when screen on */
	#define E903002004_BATLEVELTIME_INT 1
	/* Unfreeze key application name */
	#define E903002004_UNFREEZENAME_VARCHAR 2
	/* Abnormal count start time */
	#define E903002004_ABSTARTIME_DATETIME 3

	/* Event 903002005
		Abnormal AP hot */
	/* Realtime Process Name take top CPU */
	#define E903002005_RNTOPCPU_VARCHAR 0
	/* Realtime top CPU load */
	#define E903002005_RDTOPCPU_INT 1
	/* Realtime AP temperature */
	#define E903002005_RAPTEMP_INT 2
	/* Process Name */
	#define E903002005_PNAME_VARCHAR 3
	/* Thread Name */
	#define E903002005_TNAME_VARCHAR 4
	/* Abnormal count start time */
	#define E903002005_ABSTARTIME_DATETIME 5

	/* Event 903002006
		AP wakeup power consumption */
	/* Frequent interrupt name */
	#define E903002006_INTNAME_VARCHAR 0
	/* Frequent interrupt times */
	#define E903002006_INTTIMES_INT 1
	/* Frequent gpio irq name */
	#define E903002006_GPIONAME_VARCHAR 2
	/* Frequent gpio irq times */
	#define E903002006_GPIOTIMES_INT 3
	/* Freeze fail process name */
	#define E903002006_FFNAME_VARCHAR 4
	/* Freeze fail process times */
	#define E903002006_FFTIMES_INT 5
	/* Frequent wake alarm name */
	#define E903002006_ALARMNAME_VARCHAR 6
	/* Frequent wake alarm times */
	#define E903002006_ALARMTIMES_INT 7
	/* Long range wakelock name */
	#define E903002006_LRWNAME_VARCHAR 8
	/* Long range wakelock process name */
	#define E903002006_LPROCNAME_VARCHAR 9
	/* Long wakelock time */
	#define E903002006_WAKELOCKTIME_INT 10
	/* Abnormal count start time */
	#define E903002006_ABSTARTIME_DATETIME 11

	/* Event 903002007
		Abnormal sensorhub power consumption */
	/* Sensorhub unsleep status */
	#define E903002007_SENSORHUBSTATUS_INT 0
	/* Sensorhub unsleep reason */
	#define E903002007_SENSORHUBREASON_VARCHAR 1
	/* Sensorhub wake up frequency */
	#define E903002007_SENSORHUBWAKE_INT 2
	/* Abnormal active sensor name */
	#define E903002007_SENSORNAME_VARCHAR 3
	/* Abnormal active sensor time */
	#define E903002007_SENSORTIME_INT 4
	/* Abnormal count start time */
	#define E903002007_ABSTARTIME_DATETIME 5

	/* Event 903002008
		Abnormal modem power consumption */
	/* Modem type */
	#define E903002008_MODEMTYPE_INT 0
	/* Modem wake up time */
	#define E903002008_MWAKETIME_INT 1
	/* Modem wake up votes */
	#define E903002008_MODEMVOTE_VARCHAR 2
	/* Modem vote times */
	#define E903002008_VOTE_TIMES_INT 3
	/* Network switch times */
	#define E903002008_SWITCHTIMES_INT 4
	/* The decrease of modem wake times is disabled */
	#define E903002008_LATCOMMAND_TINYINT 5
	/* Data service agent solution is disabled */
	#define E903002008_DSAGENT_TINYINT 6
	/* Apt solution is disabled */
	#define E903002008_APT_TINYINT 7
	/* Adrx solution is disabled */
	#define E903002008_ADRX_TINYINT 8
	/* Qpc solution is disabled */
	#define E903002008_QPC_TINYINT 9
	/* Ssc solution is disabled */
	#define E903002008_SSC_TINYINT 10
	/* Modem rubish filter solution is disabled */
	#define E903002008_MFILTER_TINYINT 11
	/* Abnormal count start time */
	#define E903002008_ABSTARTIME_DATETIME 12

	/* Event 903002009
		Abnormal power consumption when screen off */
	/* Power consume before 30 minutes screen off */
	#define E903002009_BATLEVEL_INT 0
	/* Power consume when screen off */
	#define E903002009_BATLEVELALL_INT 1
	/* Wifi ap status */
	#define E903002009_WIFIAPSTATUS_TINYINT 2
	/* Modem weak signal type */
	#define E903002009_SIGNAL_TYPE_VARCHAR 3
	/* Modem weak signal strength */
	#define E903002009_SIGNAL_STRENGTH_VARCHAR 4
	/* Abnormal count start time */
	#define E903002009_ABSTARTIME_DATETIME 5

	/* Event 903002010
		Temperature alarm info */
	/* Sampling Time */
	#define E903002010_TIME_VARCHAR 0
	/* Triggering event */
	#define E903002010_EVENT_VARCHAR 1
	/* Computed case temperature */
	#define E903002010_CASETEMP_TINYINT 2
	/* AP temperature */
	#define E903002010_APTEMP_TINYINT 3
	/* PMIC temperature */
	#define E903002010_CHARGETEMP_TINYINT 4
	/* Flash temperature */
	#define E903002010_FLASHTEMP_TINYINT 5
	/* PA temperature */
	#define E903002010_PATEMP_TINYINT 6
	/* Battery temperature */
	#define E903002010_BATTERYTEMP_TINYINT 7
	/* CPU temperature */
	#define E903002010_CPUTEMP_TINYINT 8
	/* GPU temperature */
	#define E903002010_GPUTEMP_TINYINT 9
	/* Battery Current */
	#define E903002010_BATTERYCURRENT_INT 10
	/* Big CPU frequency */
	#define E903002010_CPUFREQBIG_INT 11
	/* Little CPU frequency */
	#define E903002010_CPUFREQLITTLE_INT 12
	/* DDR frequency */
	#define E903002010_DDRFREQ_INT 13
	/* GPU frequency */
	#define E903002010_GPUFREQ_INT 14
	/* Charging status */
	#define E903002010_BATTERYSTATUS_TINYINT 15
	/* Battery Voltage */
	#define E903002010_BATTERYVOLTAGE_FLOAT 16
	/* Enviroment light level */
	#define E903002010_LIGHTLEVEL_INT 17
	/* Display backlight level */
	#define E903002010_BRIGHTNESS_INT 18
	/* Speeker/earphone volume */
	#define E903002010_MUSICVOLUME_INT 19
	/* Phone calling or idel */
	#define E903002010_CALLINGSTATUS_TINYINT 20
	/* Phone signal type */
	#define E903002010_SIGNALKIND_VARCHAR 21
	/* Phone signal strength */
	#define E903002010_SIGNALLEVEL_SMALLINT 22
	/* WIFI hotspot */
	#define E903002010_WIFIHOTSPOT_TINYINT 23
	/* GPS on/off */
	#define E903002010_GPSSTATUS_TINYINT 24
	/* Thermal feeling level */
	#define E903002010_THERMALFEELING_TINYINT 25
	/* Top application power consumption in temperature alarm */
	#define E903002010_TOPAPPINFO_VARCHAR 26

	/* Event 903003000
		Coulometer abnormal jump Info */
	/* capicaty stats begin time */
	#define E903003000_COULJUMPFROM_DATETIME 0
	/* capicaty stats end time */
	#define E903003000_COULJUMPTO_DATETIME 1
	/* The capicaty before coulometer jump */
	#define E903003000_BATDROPFROM_INT 2
	/* The capicaty after coulometer jump */
	#define E903003000_BATDROPTO_INT 3
	/* hardware leak stats from time */
	#define E903003000_HWLEAKSTATSFROM_DATETIME 4
	/* hardware leak stats end time */
	#define E903003000_HWLEAKSTATSTO_DATETIME 5
	/* hardware leak abnormal Info */
	#define E903003000_HWLEAKBATDROP_VARCHAR 6
	/* WIFI hotspot time */
	#define E903003000_WIFIHOTSPOT_INT 7

/*** CHR events' keys ***/

	/* Event 904000000
		NetWorkSearch */
	/* PlatForm 1 Hisi 2 Qcom 3 VIA 4 Sprd */
	#define E904000000_PLATFORM_INT 0
	/* Fault Classification 1 AP Fault 2 Modem Fault */
	#define E904000000_FAULTCLASSIFICATION_INT 1
	/* ChrEventId */
	#define E904000000_CHREVENTID_INT 2
	/* EventScenario */
	#define E904000000_EVENTSCENARIO_INT 3
	/* EventFailCause */
	#define E904000000_EVENTFAILCAUSE_INT 4

	/* Event 904001000
		Call */
	/* PlatForm 1 Hisi 2 Qcom 3 VIA 4 Sprd */
	#define E904001000_PLATFORM_INT 0
	/* Fault Classification 1 AP Fault 2 Modem Fault */
	#define E904001000_FAULTCLASSIFICATION_INT 1
	/* ChrEventId */
	#define E904001000_CHREVENTID_INT 2
	/* EventScenario */
	#define E904001000_EVENTSCENARIO_INT 3
	/* EventFailCause */
	#define E904001000_EVENTFAILCAUSE_INT 4

	/* Event 904002000
		Data Service */
	/* PlatForm 1 Hisi 2 Qcom 3 VIA 4 Sprd */
	#define E904002000_PLATFORM_INT 0
	/* Fault Classification 1 AP Fault 2 Modem Fault */
	#define E904002000_FAULTCLASSIFICATION_INT 1
	/* ChrEventId */
	#define E904002000_CHREVENTID_INT 2
	/* EventScenario */
	#define E904002000_EVENTSCENARIO_INT 3
	/* EventFailCause */
	#define E904002000_EVENTFAILCAUSE_INT 4

	/* Event 904003000
		SimCard */
	/* PlatForm 1 Hisi 2 Qcom 3 VIA 4 Sprd */
	#define E904003000_PLATFORM_INT 0
	/* Fault Classification 1 AP Fault 2 Modem Fault */
	#define E904003000_FAULTCLASSIFICATION_INT 1
	/* ChrEventId */
	#define E904003000_CHREVENTID_INT 2
	/* EventScenario */
	#define E904003000_EVENTSCENARIO_INT 3
	/* EventFailCause */
	#define E904003000_EVENTFAILCAUSE_INT 4

	/* Event 904004000
		Volte */
	/* PlatForm 1 Hisi 2 Qcom 3 VIA 4 Sprd */
	#define E904004000_PLATFORM_INT 0
	/* Fault Classification 0 Network or Other 1 AP Fault
		2 Modem Fault */
	#define E904004000_FAULTCLASSIFICATION_INT 1
	/* ChrEventId */
	#define E904004000_CHREVENTID_INT 2
	/* EventScenario */
	#define E904004000_EVENTSCENARIO_INT 3
	/* EventFailCause */
	#define E904004000_EVENTFAILCAUSE_INT 4

	/* Event 904004001
		VT */
	/* PlatForm 1 Hisi 2 Qcom 3 VIA 4 Sprd */
	#define E904004001_PLATFORM_INT 0
	/* Fault Classification 0 Network or Other 1 AP Fault
		2 Modem Fault */
	#define E904004001_FAULTCLASSIFICATION_INT 1
	/* ChrEventId */
	#define E904004001_CHREVENTID_INT 2
	/* EventScenario */
	#define E904004001_EVENTSCENARIO_INT 3
	/* EventFailCause */
	#define E904004001_EVENTFAILCAUSE_INT 4

	/* Event 904005000
		Message */
	/* PlatForm 1 Hisi 2 Qcom 3 VIA 4 Sprd */
	#define E904005000_PLATFORM_INT 0
	/* Fault Classification 0 Network or Other 1 AP Fault
		2 Modem Fault */
	#define E904005000_FAULTCLASSIFICATION_INT 1
	/* ChrEventId */
	#define E904005000_CHREVENTID_INT 2
	/* EventScenario */
	#define E904005000_EVENTSCENARIO_INT 3
	/* EventFailCause */
	#define E904005000_EVENTFAILCAUSE_INT 4

	/* Event 904006000
		BSD */
	/* PlatForm 1 Hisi 2 Qcom 3 VIA 4 Sprd */
	#define E904006000_PLATFORM_INT 0
	/* Fault Classification 1 AP Fault 2 Modem Fault */
	#define E904006000_FAULTCLASSIFICATION_INT 1
	/* ChrEventId */
	#define E904006000_CHREVENTID_INT 2
	/* EventScenario */
	#define E904006000_EVENTSCENARIO_INT 3
	/* EventFailCause */
	#define E904006000_EVENTFAILCAUSE_INT 4

	/* Event 904007000
		Information Collect */
	/* PlatForm 1 Hisi 2 Qcom 3 VIA 4 Sprd */
	#define E904007000_PLATFORM_INT 0
	/* Fault Classification 1 AP Fault 2 Modem Fault */
	#define E904007000_FAULTCLASSIFICATION_INT 1
	/* ChrEventId */
	#define E904007000_CHREVENTID_INT 2
	/* EventScenario */
	#define E904007000_EVENTSCENARIO_INT 3
	/* EventFailCause */
	#define E904007000_EVENTFAILCAUSE_INT 4

	/* Event 904008000
		Hardware Failure */
	/* PlatForm 1 Hisi 2 Qcom 3 VIA 4 Sprd */
	#define E904008000_PLATFORM_INT 0
	/* Fault Classification 1 AP Fault 2 Modem Fault */
	#define E904008000_FAULTCLASSIFICATION_INT 1
	/* ChrEventId */
	#define E904008000_CHREVENTID_INT 2
	/* EventScenario */
	#define E904008000_EVENTSCENARIO_INT 3
	/* EventFailCause */
	#define E904008000_EVENTFAILCAUSE_INT 4

	/* Event 904009000
		SkyTone */
	/* PlatForm 1 Hisi 2 Qcom 3 VIA 4 Sprd */
	#define E904009000_PLATFORM_INT 0
	/* Fault Classification 1 AP Fault 2 Modem Fault */
	#define E904009000_FAULTCLASSIFICATION_INT 1
	/* ChrEventId */
	#define E904009000_CHREVENTID_INT 2
	/* EventScenario */
	#define E904009000_EVENTSCENARIO_INT 3
	/* EventFailCause */
	#define E904009000_EVENTFAILCAUSE_INT 4

	/* Event 904010000
		X Mode */
	/* PlatForm 1 Hisi 2 Qcom 3 VIA 4 Sprd */
	#define E904010000_PLATFORM_INT 0
	/* Fault Classification 1 AP Fault 2 Modem Fault */
	#define E904010000_FAULTCLASSIFICATION_INT 1
	/* ChrEventId */
	#define E904010000_CHREVENTID_INT 2
	/* EventScenario */
	#define E904010000_EVENTSCENARIO_INT 3
	/* EventFailCause */
	#define E904010000_EVENTFAILCAUSE_INT 4

	/* Event 904100000
		CHR */

/*** DMD events' keys ***/

	/* Event 920001003
		battery absence */
	/* error level */
	#define E920001003_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920001003_IC_NAME_VARCHAR 1
	/* module name */
	#define E920001003_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920001003_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920001003_COUNT_INT 4

	/* Event 920001004
		battery under-temperature */
	/* error level */
	#define E920001004_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920001004_IC_NAME_VARCHAR 1
	/* module name */
	#define E920001004_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920001004_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920001004_COUNT_INT 4

	/* Event 920001005
		battery over-voltage */
	/* error level */
	#define E920001005_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920001005_IC_NAME_VARCHAR 1
	/* module name */
	#define E920001005_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920001005_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920001005_COUNT_INT 4

	/* Event 920001006
		battery under-voltage */
	/* error level */
	#define E920001006_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920001006_IC_NAME_VARCHAR 1
	/* module name */
	#define E920001006_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920001006_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920001006_COUNT_INT 4

	/* Event 920001007
		battery cutoff early */
	/* error level */
	#define E920001007_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920001007_IC_NAME_VARCHAR 1
	/* module name */
	#define E920001007_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920001007_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920001007_COUNT_INT 4

	/* Event 920001008
		battery cutoff never */
	/* error level */
	#define E920001008_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920001008_IC_NAME_VARCHAR 1
	/* module name */
	#define E920001008_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920001008_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920001008_COUNT_INT 4

	/* Event 920001009
		battery current detect error */
	/* error level */
	#define E920001009_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920001009_IC_NAME_VARCHAR 1
	/* module name */
	#define E920001009_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920001009_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920001009_COUNT_INT 4

	/* Event 920001010
		vbus over-voltage */
	/* error level */
	#define E920001010_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920001010_IC_NAME_VARCHAR 1
	/* module name */
	#define E920001010_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920001010_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920001010_COUNT_INT 4

	/* Event 920001011
		watchdog over-time */
	/* error level */
	#define E920001011_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920001011_IC_NAME_VARCHAR 1
	/* module name */
	#define E920001011_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920001011_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920001011_COUNT_INT 4

	/* Event 920001012
		charging current large */
	/* error level */
	#define E920001012_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920001012_IC_NAME_VARCHAR 1
	/* module name */
	#define E920001012_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920001012_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920001012_COUNT_INT 4

	/* Event 920001013
		discharging current large */
	/* error level */
	#define E920001013_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920001013_IC_NAME_VARCHAR 1
	/* module name */
	#define E920001013_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920001013_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920001013_COUNT_INT 4

	/* Event 920001014
		resister current 0 */
	/* error level */
	#define E920001014_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920001014_IC_NAME_VARCHAR 1
	/* module name */
	#define E920001014_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920001014_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920001014_COUNT_INT 4

	/* Event 920001015
		temp fault not charging */
	/* error level */
	#define E920001015_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920001015_IC_NAME_VARCHAR 1
	/* module name */
	#define E920001015_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920001015_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920001015_COUNT_INT 4

	/* Event 920001016
		batt shutdown temp */
	/* error level */
	#define E920001016_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920001016_IC_NAME_VARCHAR 1
	/* module name */
	#define E920001016_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920001016_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920001016_COUNT_INT 4

	/* Event 920001017
		batt capacity */
	/* error level */
	#define E920001017_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920001017_IC_NAME_VARCHAR 1
	/* module name */
	#define E920001017_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920001017_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920001017_COUNT_INT 4

	/* Event 920001018
		charger ts */
	/* error level */
	#define E920001018_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920001018_IC_NAME_VARCHAR 1
	/* module name */
	#define E920001018_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920001018_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920001018_COUNT_INT 4

	/* Event 920001019
		otg ture no otg device */
	/* error level */
	#define E920001019_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920001019_IC_NAME_VARCHAR 1
	/* module name */
	#define E920001019_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920001019_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920001019_COUNT_INT 4

	/* Event 920001021
		vbus voltage abnormal */
	/* error level */
	#define E920001021_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920001021_IC_NAME_VARCHAR 1
	/* module name */
	#define E920001021_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920001021_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920001021_COUNT_INT 4

	/* Event 920001022
		fcp detect failed */
	/* error level */
	#define E920001022_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920001022_IC_NAME_VARCHAR 1
	/* module name */
	#define E920001022_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920001022_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920001022_COUNT_INT 4

	/* Event 920001023
		fcp boost failed */
	/* error level */
	#define E920001023_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920001023_IC_NAME_VARCHAR 1
	/* module name */
	#define E920001023_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920001023_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920001023_COUNT_INT 4

	/* Event 920001024
		fcp deattach */
	/* error level */
	#define E920001024_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920001024_IC_NAME_VARCHAR 1
	/* module name */
	#define E920001024_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920001024_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920001024_COUNT_INT 4

	/* Event 920001025
		fcp over-voltage */
	/* error level */
	#define E920001025_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920001025_IC_NAME_VARCHAR 1
	/* module name */
	#define E920001025_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920001025_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920001025_COUNT_INT 4

	/* Event 920001026
		fcp over-current */
	/* error level */
	#define E920001026_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920001026_IC_NAME_VARCHAR 1
	/* module name */
	#define E920001026_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920001026_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920001026_COUNT_INT 4

	/* Event 920001027
		fcp over-temperature */
	/* error level */
	#define E920001027_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920001027_IC_NAME_VARCHAR 1
	/* module name */
	#define E920001027_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920001027_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920001027_COUNT_INT 4

	/* Event 920001030
		check fcc invalid */
	/* error level */
	#define E920001030_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920001030_IC_NAME_VARCHAR 1
	/* module name */
	#define E920001030_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920001030_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920001030_COUNT_INT 4

	/* Event 920001048
		Internal short current is below 10mA */
	/* error level */
	#define E920001048_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920001048_IC_NAME_VARCHAR 1
	/* module name */
	#define E920001048_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920001048_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920001048_COUNT_INT 4

	/* Event 920001049
		Internal short current is between 10 -15 mA */
	/* error level */
	#define E920001049_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920001049_IC_NAME_VARCHAR 1
	/* module name */
	#define E920001049_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920001049_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920001049_COUNT_INT 4

	/* Event 920001050
		Internal short current is between 15-20 mA */
	/* error level */
	#define E920001050_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920001050_IC_NAME_VARCHAR 1
	/* module name */
	#define E920001050_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920001050_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920001050_COUNT_INT 4

	/* Event 920001051
		Internal short current is between 20-25 mA */
	/* error level */
	#define E920001051_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920001051_IC_NAME_VARCHAR 1
	/* module name */
	#define E920001051_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920001051_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920001051_COUNT_INT 4

	/* Event 920001052
		Internal short current is between 25-30 mA */
	/* error level */
	#define E920001052_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920001052_IC_NAME_VARCHAR 1
	/* module name */
	#define E920001052_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920001052_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920001052_COUNT_INT 4

	/* Event 920001053
		Internal short current is between 30-50mA */
	/* error level */
	#define E920001053_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920001053_IC_NAME_VARCHAR 1
	/* module name */
	#define E920001053_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920001053_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920001053_COUNT_INT 4

	/* Event 920001054
		Internal short current is between 50-100mA */
	/* error level */
	#define E920001054_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920001054_IC_NAME_VARCHAR 1
	/* module name */
	#define E920001054_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920001054_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920001054_COUNT_INT 4

	/* Event 920001055
		Internal short current is between 100-200mA */
	/* error level */
	#define E920001055_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920001055_IC_NAME_VARCHAR 1
	/* module name */
	#define E920001055_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920001055_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920001055_COUNT_INT 4

	/* Event 920001056
		Internal short current is above 200 mA */
	/* error level */
	#define E920001056_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920001056_IC_NAME_VARCHAR 1
	/* module name */
	#define E920001056_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920001056_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920001056_COUNT_INT 4

	/* Event 920001060
		DIRECT_CHARGE_VOL_ACCURACY */
	/* error level */
	#define E920001060_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920001060_IC_NAME_VARCHAR 1
	/* module name */
	#define E920001060_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920001060_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920001060_COUNT_INT 4

	/* Event 920001061
		DIRECT_CHARGE_FULL_PATH_RESISTANCE */
	/* error level */
	#define E920001061_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920001061_IC_NAME_VARCHAR 1
	/* module name */
	#define E920001061_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920001061_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920001061_COUNT_INT 4

	/* Event 920001062
		DIRECT_CHARGE_LOADSWITCH_RESISTANCE */
	/* error level */
	#define E920001062_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920001062_IC_NAME_VARCHAR 1
	/* module name */
	#define E920001062_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920001062_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920001062_COUNT_INT 4

	/* Event 920001063
		DIRECT_CHARGE_USB_PORT_LEAKAGE_CURRENT */
	/* error level */
	#define E920001063_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920001063_IC_NAME_VARCHAR 1
	/* module name */
	#define E920001063_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920001063_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920001063_COUNT_INT 4

	/* Event 920002001
		battery ID detect abnormal */
	/* error level */
	#define E920002001_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920002001_IC_NAME_VARCHAR 1
	/* module name */
	#define E920002001_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920002001_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920002001_COUNT_INT 4

	/* Event 920003000
		smpl */
	/* error level */
	#define E920003000_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920003000_IC_NAME_VARCHAR 1
	/* module name */
	#define E920003000_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920003000_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920003000_COUNT_INT 4

	/* Event 920004000
		USB short circuit protect */
	/* error level */
	#define E920004000_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920004000_IC_NAME_VARCHAR 1
	/* module name */
	#define E920004000_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920004000_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920004000_COUNT_INT 4

	/* Event 920004001
		USB short circuit protect, check NTC */
	/* error level */
	#define E920004001_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920004001_IC_NAME_VARCHAR 1
	/* module name */
	#define E920004001_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920004001_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920004001_COUNT_INT 4

	/* Event 920005000
		PMU abort:chipset over-temperature */
	/* error level */
	#define E920005000_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920005000_IC_NAME_VARCHAR 1
	/* module name */
	#define E920005000_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920005000_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920005000_COUNT_INT 4

	/* Event 920005001
		PMU abort:reset by thermal protetion */
	/* error level */
	#define E920005001_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920005001_IC_NAME_VARCHAR 1
	/* module name */
	#define E920005001_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920005001_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920005001_COUNT_INT 4

	/* Event 920005002
		PMU abort:battery smpl */
	/* error level */
	#define E920005002_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920005002_IC_NAME_VARCHAR 1
	/* module name */
	#define E920005002_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920005002_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920005002_COUNT_INT 4

	/* Event 920005003
		PMU abort:vbus less than 4.3v */
	/* error level */
	#define E920005003_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920005003_IC_NAME_VARCHAR 1
	/* module name */
	#define E920005003_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920005003_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920005003_COUNT_INT 4

	/* Event 920005004
		exception Interrupts: PMU abort:vbus more than 5.5v */
	/* error level */
	#define E920005004_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920005004_IC_NAME_VARCHAR 1
	/* module name */
	#define E920005004_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920005004_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920005004_COUNT_INT 4

	/* Event 920005005
		exception Interrupts: PMU abort:vsys over-voltage */
	/* error level */
	#define E920005005_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920005005_IC_NAME_VARCHAR 1
	/* module name */
	#define E920005005_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920005005_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920005005_COUNT_INT 4

	/* Event 920005006
		exception Interrupts: PMU abort:vsys under-voltage */
	/* error level */
	#define E920005006_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920005006_IC_NAME_VARCHAR 1
	/* module name */
	#define E920005006_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920005006_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920005006_COUNT_INT 4

	/* Event 920005007
		exception Interrupts: PMU abort:boost under-voltage */
	/* error level */
	#define E920005007_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920005007_IC_NAME_VARCHAR 1
	/* module name */
	#define E920005007_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920005007_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920005007_COUNT_INT 4

	/* Event 920005008
		exception Interrupts: PMU abort:boost over-voltage */
	/* error level */
	#define E920005008_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920005008_IC_NAME_VARCHAR 1
	/* module name */
	#define E920005008_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920005008_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920005008_COUNT_INT 4

	/* Event 920005009
		exception Interrupts: PMU abort:flash_led short-circuit */
	/* error level */
	#define E920005009_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920005009_IC_NAME_VARCHAR 1
	/* module name */
	#define E920005009_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920005009_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920005009_COUNT_INT 4

	/* Event 920005010
		exception Interrupts: PMU abort:flash_led open-circuit */
	/* error level */
	#define E920005010_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920005010_IC_NAME_VARCHAR 1
	/* module name */
	#define E920005010_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920005010_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920005010_COUNT_INT 4

	/* Event 920005011
		exception Interrupts: PMU abort:voltage less than 2.3v */
	/* error level */
	#define E920005011_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920005011_IC_NAME_VARCHAR 1
	/* module name */
	#define E920005011_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920005011_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920005011_COUNT_INT 4

	/* Event 920005012
		exception Interrupts: PMU abort:voltage less than 2.8v */
	/* error level */
	#define E920005012_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920005012_IC_NAME_VARCHAR 1
	/* module name */
	#define E920005012_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920005012_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920005012_COUNT_INT 4

	/* Event 920005013
		exception Interrupts: PMU abort:over-temperature 150
		celsius */
	/* error level */
	#define E920005013_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920005013_IC_NAME_VARCHAR 1
	/* module name */
	#define E920005013_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920005013_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920005013_COUNT_INT 4

	/* Event 920006000
		fg charging abnormal */
	/* error level */
	#define E920006000_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920006000_IC_NAME_VARCHAR 1
	/* module name */
	#define E920006000_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920006000_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920006000_COUNT_INT 4

	/* Event 920006001
		fg closed abnormal */
	/* error level */
	#define E920006001_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920006001_IC_NAME_VARCHAR 1
	/* module name */
	#define E920006001_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920006001_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920006001_COUNT_INT 4

	/* Event 920006002
		Reserved */
	/* error level */
	#define E920006002_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920006002_IC_NAME_VARCHAR 1
	/* module name */
	#define E920006002_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920006002_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920006002_COUNT_INT 4

	/* Event 920007000
		source oc:LDO2 over-load */
	/* error level */
	#define E920007000_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920007000_IC_NAME_VARCHAR 1
	/* module name */
	#define E920007000_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920007000_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920007000_COUNT_INT 4

	/* Event 920007001
		source oc:LDO1over-load */
	/* error level */
	#define E920007001_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920007001_IC_NAME_VARCHAR 1
	/* module name */
	#define E920007001_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920007001_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920007001_COUNT_INT 4

	/* Event 920007002
		source oc:LDO0_2 over-load */
	/* error level */
	#define E920007002_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920007002_IC_NAME_VARCHAR 1
	/* module name */
	#define E920007002_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920007002_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920007002_COUNT_INT 4

	/* Event 920007003
		source oc:BUCK4 over-load */
	/* error level */
	#define E920007003_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920007003_IC_NAME_VARCHAR 1
	/* module name */
	#define E920007003_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920007003_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920007003_COUNT_INT 4

	/* Event 920007004
		source oc:BUCK3 over-load */
	/* error level */
	#define E920007004_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920007004_IC_NAME_VARCHAR 1
	/* module name */
	#define E920007004_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920007004_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920007004_COUNT_INT 4

	/* Event 920007005
		source oc:BUCK2 over-load */
	/* error level */
	#define E920007005_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920007005_IC_NAME_VARCHAR 1
	/* module name */
	#define E920007005_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920007005_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920007005_COUNT_INT 4

	/* Event 920007006
		source oc:BUCK1 over-load */
	/* error level */
	#define E920007006_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920007006_IC_NAME_VARCHAR 1
	/* module name */
	#define E920007006_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920007006_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920007006_COUNT_INT 4

	/* Event 920007007
		source oc:BUCK0 over-load */
	/* error level */
	#define E920007007_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920007007_IC_NAME_VARCHAR 1
	/* module name */
	#define E920007007_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920007007_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920007007_COUNT_INT 4

	/* Event 920007008
		source oc:LDO11 over-load */
	/* error level */
	#define E920007008_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920007008_IC_NAME_VARCHAR 1
	/* module name */
	#define E920007008_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920007008_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920007008_COUNT_INT 4

	/* Event 920007009
		source oc:LDO10 over-load */
	/* error level */
	#define E920007009_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920007009_IC_NAME_VARCHAR 1
	/* module name */
	#define E920007009_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920007009_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920007009_COUNT_INT 4

	/* Event 920007010
		source oc:LDO9 over-load */
	/* error level */
	#define E920007010_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920007010_IC_NAME_VARCHAR 1
	/* module name */
	#define E920007010_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920007010_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920007010_COUNT_INT 4

	/* Event 920007011
		source oc:LDO8 over-load */
	/* error level */
	#define E920007011_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920007011_IC_NAME_VARCHAR 1
	/* module name */
	#define E920007011_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920007011_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920007011_COUNT_INT 4

	/* Event 920007012
		source oc:LDO8 over-load */
	/* error level */
	#define E920007012_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920007012_IC_NAME_VARCHAR 1
	/* module name */
	#define E920007012_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920007012_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920007012_COUNT_INT 4

	/* Event 920007013
		source oc:LDO5 over-load */
	/* error level */
	#define E920007013_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920007013_IC_NAME_VARCHAR 1
	/* module name */
	#define E920007013_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920007013_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920007013_COUNT_INT 4

	/* Event 920007014
		source oc:LDO4 over-load */
	/* error level */
	#define E920007014_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920007014_IC_NAME_VARCHAR 1
	/* module name */
	#define E920007014_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920007014_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920007014_COUNT_INT 4

	/* Event 920007015
		source oc:LDO3 over-load */
	/* error level */
	#define E920007015_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920007015_IC_NAME_VARCHAR 1
	/* module name */
	#define E920007015_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920007015_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920007015_COUNT_INT 4

	/* Event 920007016
		source oc:LDO20 over-load */
	/* error level */
	#define E920007016_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920007016_IC_NAME_VARCHAR 1
	/* module name */
	#define E920007016_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920007016_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920007016_COUNT_INT 4

	/* Event 920007017
		source oc:LDO19 over-load */
	/* error level */
	#define E920007017_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920007017_IC_NAME_VARCHAR 1
	/* module name */
	#define E920007017_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920007017_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920007017_COUNT_INT 4

	/* Event 920007018
		source oc:LDO17 over-load */
	/* error level */
	#define E920007018_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920007018_IC_NAME_VARCHAR 1
	/* module name */
	#define E920007018_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920007018_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920007018_COUNT_INT 4

	/* Event 920007019
		source oc:LDO16 over-load */
	/* error level */
	#define E920007019_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920007019_IC_NAME_VARCHAR 1
	/* module name */
	#define E920007019_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920007019_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920007019_COUNT_INT 4

	/* Event 920007020
		source oc:LDO15 over-load */
	/* error level */
	#define E920007020_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920007020_IC_NAME_VARCHAR 1
	/* module name */
	#define E920007020_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920007020_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920007020_COUNT_INT 4

	/* Event 920007021
		source oc:LDO14 over-load */
	/* error level */
	#define E920007021_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920007021_IC_NAME_VARCHAR 1
	/* module name */
	#define E920007021_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920007021_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920007021_COUNT_INT 4

	/* Event 920007022
		source oc:LDO13 over-load */
	/* error level */
	#define E920007022_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920007022_IC_NAME_VARCHAR 1
	/* module name */
	#define E920007022_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920007022_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920007022_COUNT_INT 4

	/* Event 920007023
		source oc:LDO12 over-load */
	/* error level */
	#define E920007023_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920007023_IC_NAME_VARCHAR 1
	/* module name */
	#define E920007023_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920007023_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920007023_COUNT_INT 4

	/* Event 920007024
		source oc:LDO28 over-load */
	/* error level */
	#define E920007024_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920007024_IC_NAME_VARCHAR 1
	/* module name */
	#define E920007024_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920007024_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920007024_COUNT_INT 4

	/* Event 920007025
		source oc:LDO27 over-load */
	/* error level */
	#define E920007025_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920007025_IC_NAME_VARCHAR 1
	/* module name */
	#define E920007025_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920007025_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920007025_COUNT_INT 4

	/* Event 920007026
		source oc:LDO26 over-load */
	/* error level */
	#define E920007026_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920007026_IC_NAME_VARCHAR 1
	/* module name */
	#define E920007026_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920007026_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920007026_COUNT_INT 4

	/* Event 920007027
		source oc:LDO25 over-load */
	/* error level */
	#define E920007027_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920007027_IC_NAME_VARCHAR 1
	/* module name */
	#define E920007027_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920007027_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920007027_COUNT_INT 4

	/* Event 920007028
		source oc:LDO24 over-load */
	/* error level */
	#define E920007028_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920007028_IC_NAME_VARCHAR 1
	/* module name */
	#define E920007028_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920007028_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920007028_COUNT_INT 4

	/* Event 920007029
		source oc:LDO23 over-load */
	/* error level */
	#define E920007029_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920007029_IC_NAME_VARCHAR 1
	/* module name */
	#define E920007029_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920007029_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920007029_COUNT_INT 4

	/* Event 920007030
		source oc:LDO22 over-load */
	/* error level */
	#define E920007030_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920007030_IC_NAME_VARCHAR 1
	/* module name */
	#define E920007030_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920007030_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920007030_COUNT_INT 4

	/* Event 920007031
		source oc:LDO21 over-load */
	/* error level */
	#define E920007031_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920007031_IC_NAME_VARCHAR 1
	/* module name */
	#define E920007031_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920007031_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920007031_COUNT_INT 4

	/* Event 920007032
		source oc:classd over load */
	/* error level */
	#define E920007032_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920007032_IC_NAME_VARCHAR 1
	/* module name */
	#define E920007032_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920007032_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920007032_COUNT_INT 4

	/* Event 920007033
		source oc:DC mode DR2 over load */
	/* error level */
	#define E920007033_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920007033_IC_NAME_VARCHAR 1
	/* module name */
	#define E920007033_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920007033_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920007033_COUNT_INT 4

	/* Event 920007034
		source oc:LSW53 over-load */
	/* error level */
	#define E920007034_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920007034_IC_NAME_VARCHAR 1
	/* module name */
	#define E920007034_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920007034_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920007034_COUNT_INT 4

	/* Event 920007035
		source oc:LSW52 over-load */
	/* error level */
	#define E920007035_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920007035_IC_NAME_VARCHAR 1
	/* module name */
	#define E920007035_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920007035_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920007035_COUNT_INT 4

	/* Event 920007036
		source oc:LDO32 over-load */
	/* error level */
	#define E920007036_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920007036_IC_NAME_VARCHAR 1
	/* module name */
	#define E920007036_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920007036_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920007036_COUNT_INT 4

	/* Event 920007037
		source oc:LDO31 over-load */
	/* error level */
	#define E920007037_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920007037_IC_NAME_VARCHAR 1
	/* module name */
	#define E920007037_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920007037_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920007037_COUNT_INT 4

	/* Event 920007038
		source oc:LDO30 over-load */
	/* error level */
	#define E920007038_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920007038_IC_NAME_VARCHAR 1
	/* module name */
	#define E920007038_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920007038_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920007038_COUNT_INT 4

	/* Event 920007039
		source oc:LDO29 over-load */
	/* error level */
	#define E920007039_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920007039_IC_NAME_VARCHAR 1
	/* module name */
	#define E920007039_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920007039_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920007039_COUNT_INT 4

	/* Event 920007040
		source oc:BUCK4 short-circuit */
	/* error level */
	#define E920007040_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920007040_IC_NAME_VARCHAR 1
	/* module name */
	#define E920007040_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920007040_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920007040_COUNT_INT 4

	/* Event 920007041
		source oc:BUCK3 short-circuit */
	/* error level */
	#define E920007041_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920007041_IC_NAME_VARCHAR 1
	/* module name */
	#define E920007041_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920007041_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920007041_COUNT_INT 4

	/* Event 920007042
		source oc:BUCK2 short-circuit */
	/* error level */
	#define E920007042_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920007042_IC_NAME_VARCHAR 1
	/* module name */
	#define E920007042_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920007042_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920007042_COUNT_INT 4

	/* Event 920007043
		source oc:BUCK1 short-circuit */
	/* error level */
	#define E920007043_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920007043_IC_NAME_VARCHAR 1
	/* module name */
	#define E920007043_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920007043_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920007043_COUNT_INT 4

	/* Event 920007044
		source oc:BUCK0 short-circuit */
	/* error level */
	#define E920007044_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920007044_IC_NAME_VARCHAR 1
	/* module name */
	#define E920007044_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920007044_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920007044_COUNT_INT 4

	/* Event 920007045
		source oc:boost short-circuit */
	/* error level */
	#define E920007045_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920007045_IC_NAME_VARCHAR 1
	/* module name */
	#define E920007045_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920007045_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920007045_COUNT_INT 4

	/* Event 920007046
		source oc */
	/* error level */
	#define E920007046_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920007046_IC_NAME_VARCHAR 1
	/* module name */
	#define E920007046_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920007046_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920007046_COUNT_INT 4

	/* Event 920007047
		source oc:boost over-load */
	/* error level */
	#define E920007047_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920007047_IC_NAME_VARCHAR 1
	/* module name */
	#define E920007047_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920007047_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920007047_COUNT_INT 4

	/* Event 920007048
		source oc:BUCK6 short-circuit */
	/* error level */
	#define E920007048_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920007048_IC_NAME_VARCHAR 1
	/* module name */
	#define E920007048_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920007048_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920007048_COUNT_INT 4

	/* Event 920008000
		not charging */
	/* error level */
	#define E920008000_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920008000_IC_NAME_VARCHAR 1
	/* module name */
	#define E920008000_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920008000_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920008000_COUNT_INT 4

	/* Event 920008001
		not charging */
	/* error level */
	#define E920008001_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920008001_IC_NAME_VARCHAR 1
	/* module name */
	#define E920008001_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920008001_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920008001_COUNT_INT 4

	/* Event 920008002
		charging slow */
	/* error level */
	#define E920008002_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920008002_IC_NAME_VARCHAR 1
	/* module name */
	#define E920008002_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920008002_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920008002_COUNT_INT 4

	/* Event 920008003
		charging slow */
	/* error level */
	#define E920008003_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920008003_IC_NAME_VARCHAR 1
	/* module name */
	#define E920008003_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920008003_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920008003_COUNT_INT 4

	/* Event 920008004
		charging slow */
	/* error level */
	#define E920008004_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920008004_IC_NAME_VARCHAR 1
	/* module name */
	#define E920008004_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920008004_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920008004_COUNT_INT 4

	/* Event 920008005
		charging slow */
	/* error level */
	#define E920008005_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920008005_IC_NAME_VARCHAR 1
	/* module name */
	#define E920008005_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920008005_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920008005_COUNT_INT 4

	/* Event 920008006
		charging over release */
	/* error level */
	#define E920008006_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920008006_IC_NAME_VARCHAR 1
	/* module name */
	#define E920008006_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920008006_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920008006_COUNT_INT 4

	/* Event 920008007
		Limiting current */
	/* error level */
	#define E920008007_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920008007_IC_NAME_VARCHAR 1
	/* module name */
	#define E920008007_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920008007_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920008007_COUNT_INT 4

	/* Event 920008008
		Battery not present */
	/* error level */
	#define E920008008_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920008008_IC_NAME_VARCHAR 1
	/* module name */
	#define E920008008_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920008008_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920008008_COUNT_INT 4

	/* Event 920008010
		ibus almost zero */
	/* error level */
	#define E920008010_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920008010_IC_NAME_VARCHAR 1
	/* module name */
	#define E920008010_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920008010_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920008010_COUNT_INT 4

	/* Event 920008011
		temperature cross hot or cold threshold */
	/* error level */
	#define E920008011_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920008011_IC_NAME_VARCHAR 1
	/* module name */
	#define E920008011_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920008011_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920008011_COUNT_INT 4

	/* Event 920008012
		temperature arrive current limit threshold */
	/* error level */
	#define E920008012_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920008012_IC_NAME_VARCHAR 1
	/* module name */
	#define E920008012_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920008012_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920008012_COUNT_INT 4

	/* Event 920008013
		non-standard charger */
	/* error level */
	#define E920008013_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920008013_IC_NAME_VARCHAR 1
	/* module name */
	#define E920008013_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920008013_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920008013_COUNT_INT 4

	/* Event 920008014
		ibus is low */
	/* error level */
	#define E920008014_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920008014_IC_NAME_VARCHAR 1
	/* module name */
	#define E920008014_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920008014_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920008014_COUNT_INT 4

	/* Event 920008015
		system current consum large */
	/* error level */
	#define E920008015_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920008015_IC_NAME_VARCHAR 1
	/* module name */
	#define E920008015_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920008015_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920008015_COUNT_INT 4

	/* Event 920008016
		no ibus system current consum large */
	/* error level */
	#define E920008016_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920008016_IC_NAME_VARCHAR 1
	/* module name */
	#define E920008016_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920008016_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920008016_COUNT_INT 4

	/* Event 920008017
		charger or the USBcable problem */
	/* error level */
	#define E920008017_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920008017_IC_NAME_VARCHAR 1
	/* module name */
	#define E920008017_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920008017_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920008017_COUNT_INT 4

	/* Event 920008030
		Unknow charging slow */
	/* error level */
	#define E920008030_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920008030_IC_NAME_VARCHAR 1
	/* module name */
	#define E920008030_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920008030_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920008030_COUNT_INT 4

	/* Event 920009000
		power-on reason abnormal: smpl */
	/* error level */
	#define E920009000_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920009000_IC_NAME_VARCHAR 1
	/* module name */
	#define E920009000_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920009000_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920009000_COUNT_INT 4

	/* Event 920009001
		power-off reason abnormal: Thermal Fault Tolerance */
	/* error level */
	#define E920009001_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920009001_IC_NAME_VARCHAR 1
	/* module name */
	#define E920009001_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920009001_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920009001_COUNT_INT 4

	/* Event 920009002
		power-off reason abnormal: UVLO */
	/* error level */
	#define E920009002_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920009002_IC_NAME_VARCHAR 1
	/* module name */
	#define E920009002_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920009002_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920009002_COUNT_INT 4

	/* Event 920009003
		power-off reason abnormal: PMIC overtemp */
	/* error level */
	#define E920009003_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920009003_IC_NAME_VARCHAR 1
	/* module name */
	#define E920009003_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920009003_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920009003_COUNT_INT 4

	/* Event 920009004
		power-off reason abnormal: Stage3 reset */
	/* error level */
	#define E920009004_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920009004_IC_NAME_VARCHAR 1
	/* module name */
	#define E920009004_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920009004_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920009004_COUNT_INT 4

	/* Event 920009005
		external CPU temperature abnormal */
	/* error level */
	#define E920009005_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920009005_IC_NAME_VARCHAR 1
	/* module name */
	#define E920009005_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920009005_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920009005_COUNT_INT 4

	/* Event 920009006
		PA temperature abnormal */
	/* error level */
	#define E920009006_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920009006_IC_NAME_VARCHAR 1
	/* module name */
	#define E920009006_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920009006_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920009006_COUNT_INT 4

	/* Event 920009007
		thermal zone2 overtemp */
	/* error level */
	#define E920009007_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920009007_IC_NAME_VARCHAR 1
	/* module name */
	#define E920009007_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920009007_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920009007_COUNT_INT 4

	/* Event 920009008
		thermal zone4 overtemp */
	/* error level */
	#define E920009008_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920009008_IC_NAME_VARCHAR 1
	/* module name */
	#define E920009008_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920009008_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920009008_COUNT_INT 4

	/* Event 920009009
		LDO1 voltage is low */
	/* error level */
	#define E920009009_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920009009_IC_NAME_VARCHAR 1
	/* module name */
	#define E920009009_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920009009_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920009009_COUNT_INT 4

	/* Event 920009010
		LDO2 voltage is low */
	/* error level */
	#define E920009010_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920009010_IC_NAME_VARCHAR 1
	/* module name */
	#define E920009010_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920009010_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920009010_COUNT_INT 4

	/* Event 920009011
		LDO3 voltage is low */
	/* error level */
	#define E920009011_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920009011_IC_NAME_VARCHAR 1
	/* module name */
	#define E920009011_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920009011_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920009011_COUNT_INT 4

	/* Event 920009012
		LDO4 voltage is low */
	/* error level */
	#define E920009012_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920009012_IC_NAME_VARCHAR 1
	/* module name */
	#define E920009012_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920009012_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920009012_COUNT_INT 4

	/* Event 920009013
		LDO5 voltage is low */
	/* error level */
	#define E920009013_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920009013_IC_NAME_VARCHAR 1
	/* module name */
	#define E920009013_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920009013_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920009013_COUNT_INT 4

	/* Event 920009014
		LDO6 voltage is low */
	/* error level */
	#define E920009014_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920009014_IC_NAME_VARCHAR 1
	/* module name */
	#define E920009014_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920009014_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920009014_COUNT_INT 4

	/* Event 920009015
		LDO7 voltage is low */
	/* error level */
	#define E920009015_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920009015_IC_NAME_VARCHAR 1
	/* module name */
	#define E920009015_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920009015_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920009015_COUNT_INT 4

	/* Event 920009016
		LDO8 voltage is low */
	/* error level */
	#define E920009016_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920009016_IC_NAME_VARCHAR 1
	/* module name */
	#define E920009016_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920009016_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920009016_COUNT_INT 4

	/* Event 920009017
		LDO9 voltage is low */
	/* error level */
	#define E920009017_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920009017_IC_NAME_VARCHAR 1
	/* module name */
	#define E920009017_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920009017_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920009017_COUNT_INT 4

	/* Event 920009018
		LDO10 voltage is low */
	/* error level */
	#define E920009018_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920009018_IC_NAME_VARCHAR 1
	/* module name */
	#define E920009018_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920009018_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920009018_COUNT_INT 4

	/* Event 920009019
		LDO11 voltage is low */
	/* error level */
	#define E920009019_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920009019_IC_NAME_VARCHAR 1
	/* module name */
	#define E920009019_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920009019_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920009019_COUNT_INT 4

	/* Event 920009020
		LDO12 voltage is low */
	/* error level */
	#define E920009020_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920009020_IC_NAME_VARCHAR 1
	/* module name */
	#define E920009020_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920009020_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920009020_COUNT_INT 4

	/* Event 920009021
		LDO13 voltage is low */
	/* error level */
	#define E920009021_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920009021_IC_NAME_VARCHAR 1
	/* module name */
	#define E920009021_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920009021_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920009021_COUNT_INT 4

	/* Event 920009022
		LDO14 voltage is low */
	/* error level */
	#define E920009022_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920009022_IC_NAME_VARCHAR 1
	/* module name */
	#define E920009022_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920009022_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920009022_COUNT_INT 4

	/* Event 920009023
		LDO15 voltage is low */
	/* error level */
	#define E920009023_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920009023_IC_NAME_VARCHAR 1
	/* module name */
	#define E920009023_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920009023_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920009023_COUNT_INT 4

	/* Event 920009024
		LDO16 voltage is low */
	/* error level */
	#define E920009024_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920009024_IC_NAME_VARCHAR 1
	/* module name */
	#define E920009024_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920009024_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920009024_COUNT_INT 4

	/* Event 920009025
		LDO17 voltage is low */
	/* error level */
	#define E920009025_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920009025_IC_NAME_VARCHAR 1
	/* module name */
	#define E920009025_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920009025_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920009025_COUNT_INT 4

	/* Event 920009026
		LDO18 voltage is low */
	/* error level */
	#define E920009026_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920009026_IC_NAME_VARCHAR 1
	/* module name */
	#define E920009026_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920009026_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920009026_COUNT_INT 4

	/* Event 920010000
		battery capacity jumps during normal use */
	/* error level */
	#define E920010000_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920010000_IC_NAME_VARCHAR 1
	/* module name */
	#define E920010000_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920010000_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920010000_COUNT_INT 4

	/* Event 920010001
		battery voltage is over 3.6V, but soc = 0 */
	/* error level */
	#define E920010001_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920010001_IC_NAME_VARCHAR 1
	/* module name */
	#define E920010001_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920010001_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920010001_COUNT_INT 4

	/* Event 920010002
		battery voltage is over 3.7V, but soc < 2 */
	/* error level */
	#define E920010002_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920010002_IC_NAME_VARCHAR 1
	/* module name */
	#define E920010002_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920010002_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920010002_COUNT_INT 4

	/* Event 920010003
		battery voltage is over 4.35V, but soc < 90 */
	/* error level */
	#define E920010003_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920010003_IC_NAME_VARCHAR 1
	/* module name */
	#define E920010003_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920010003_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920010003_COUNT_INT 4

	/* Event 920010004
		battery voltage is too low when soc = 2 */
	/* error level */
	#define E920010004_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920010004_IC_NAME_VARCHAR 1
	/* module name */
	#define E920010004_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920010004_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920010004_COUNT_INT 4

	/* Event 920010005
		capacity jumps when plug in and out charger */
	/* error level */
	#define E920010005_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920010005_IC_NAME_VARCHAR 1
	/* module name */
	#define E920010005_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920010005_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920010005_COUNT_INT 4

	/* Event 920010006
		power on soc jumps more than 10 percent comparge to
		last shutdown soc */
	/* error level */
	#define E920010006_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920010006_IC_NAME_VARCHAR 1
	/* module name */
	#define E920010006_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920010006_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920010006_COUNT_INT 4

	/* Event 920010007
		battery profile load exception */
	/* error level */
	#define E920010007_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920010007_IC_NAME_VARCHAR 1
	/* module name */
	#define E920010007_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920010007_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920010007_COUNT_INT 4

	/* Event 920010008
		battery vol soc dismatch */
	/* error level */
	#define E920010008_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920010008_IC_NAME_VARCHAR 1
	/* module name */
	#define E920010008_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920010008_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920010008_COUNT_INT 4

	/* Event 920010009
		volt above 3.7V UVLO */
	/* error level */
	#define E920010009_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920010009_IC_NAME_VARCHAR 1
	/* module name */
	#define E920010009_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920010009_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920010009_COUNT_INT 4

	/* Event 920010010
		batt not std */
	/* error level */
	#define E920010010_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920010010_IC_NAME_VARCHAR 1
	/* module name */
	#define E920010010_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920010010_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920010010_COUNT_INT 4

	/* Event 920011000
		cannot charging when allowed */
	/* error level */
	#define E920011000_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920011000_IC_NAME_VARCHAR 1
	/* module name */
	#define E920011000_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920011000_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920011000_COUNT_INT 4

	/* Event 920011001
		CHARGE SPMI bus error */
	/* error level */
	#define E920011001_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920011001_IC_NAME_VARCHAR 1
	/* module name */
	#define E920011001_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920011001_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920011001_COUNT_INT 4

	/* Event 920011002
		CHARGE chargers OVP */
	/* error level */
	#define E920011002_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920011002_IC_NAME_VARCHAR 1
	/* module name */
	#define E920011002_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920011002_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920011002_COUNT_INT 4

	/* Event 920011003
		CHARGE no battery */
	/* error level */
	#define E920011003_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920011003_IC_NAME_VARCHAR 1
	/* module name */
	#define E920011003_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920011003_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920011003_COUNT_INT 4

	/* Event 920011004
		limit current fail when battery warm */
	/* error level */
	#define E920011004_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920011004_IC_NAME_VARCHAR 1
	/* module name */
	#define E920011004_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920011004_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920011004_COUNT_INT 4

	/* Event 920011005
		limit current fail when battery cool */
	/* error level */
	#define E920011005_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920011005_IC_NAME_VARCHAR 1
	/* module name */
	#define E920011005_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920011005_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920011005_COUNT_INT 4

	/* Event 920011006
		battery full when charger is absent */
	/* error level */
	#define E920011006_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920011006_IC_NAME_VARCHAR 1
	/* module name */
	#define E920011006_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920011006_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920011006_COUNT_INT 4

	/* Event 920011007
		charger online status abnormal when plug in and out */
	/* error level */
	#define E920011007_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920011007_IC_NAME_VARCHAR 1
	/* module name */
	#define E920011007_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920011007_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920011007_COUNT_INT 4

	/* Event 920011008
		battery voltage is over 4.4V */
	/* error level */
	#define E920011008_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920011008_IC_NAME_VARCHAR 1
	/* module name */
	#define E920011008_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920011008_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920011008_COUNT_INT 4

	/* Event 920011009
		battery voltage is below 2.5V */
	/* error level */
	#define E920011009_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920011009_IC_NAME_VARCHAR 1
	/* module name */
	#define E920011009_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920011009_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920011009_COUNT_INT 4

	/* Event 920011010
		battery full when soc is below 95 percent */
	/* error level */
	#define E920011010_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920011010_IC_NAME_VARCHAR 1
	/* module name */
	#define E920011010_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920011010_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920011010_COUNT_INT 4

	/* Event 920011011
		charging when charger is absent */
	/* error level */
	#define E920011011_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920011011_IC_NAME_VARCHAR 1
	/* module name */
	#define E920011011_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920011011_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920011011_COUNT_INT 4

	/* Event 920011012
		non-standard charger has been detected */
	/* error level */
	#define E920011012_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920011012_IC_NAME_VARCHAR 1
	/* module name */
	#define E920011012_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920011012_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920011012_COUNT_INT 4

	/* Event 920011013
		still charge when battery is hot */
	/* error level */
	#define E920011013_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920011013_IC_NAME_VARCHAR 1
	/* module name */
	#define E920011013_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920011013_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920011013_COUNT_INT 4

	/* Event 920011014
		still charge when battery is cold */
	/* error level */
	#define E920011014_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920011014_IC_NAME_VARCHAR 1
	/* module name */
	#define E920011014_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920011014_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920011014_COUNT_INT 4

	/* Event 920011015
		still charge when set discharge */
	/* error level */
	#define E920011015_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920011015_IC_NAME_VARCHAR 1
	/* module name */
	#define E920011015_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920011015_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920011015_COUNT_INT 4

	/* Event 920011016
		still charge when battery is over 4.35V */
	/* error level */
	#define E920011016_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920011016_IC_NAME_VARCHAR 1
	/* module name */
	#define E920011016_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920011016_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920011016_COUNT_INT 4

	/* Event 920011017
		battery health is overheat */
	/* error level */
	#define E920011017_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920011017_IC_NAME_VARCHAR 1
	/* module name */
	#define E920011017_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920011017_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920011017_COUNT_INT 4

	/* Event 920011018
		battery id is unknow */
	/* error level */
	#define E920011018_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920011018_IC_NAME_VARCHAR 1
	/* module name */
	#define E920011018_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920011018_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920011018_COUNT_INT 4

	/* Event 920011019
		battery temperature jumps */
	/* error level */
	#define E920011019_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920011019_IC_NAME_VARCHAR 1
	/* module name */
	#define E920011019_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920011019_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920011019_COUNT_INT 4

	/* Event 920011020
		battery temperature is too low */
	/* error level */
	#define E920011020_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920011020_IC_NAME_VARCHAR 1
	/* module name */
	#define E920011020_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920011020_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920011020_COUNT_INT 4

	/* Event 920011021
		battery temperature is too hot */
	/* error level */
	#define E920011021_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920011021_IC_NAME_VARCHAR 1
	/* module name */
	#define E920011021_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920011021_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920011021_COUNT_INT 4

	/* Event 920011022
		not charging when battery is hot */
	/* error level */
	#define E920011022_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920011022_IC_NAME_VARCHAR 1
	/* module name */
	#define E920011022_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920011022_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920011022_COUNT_INT 4

	/* Event 920011023
		not charging when battery is cold */
	/* error level */
	#define E920011023_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920011023_IC_NAME_VARCHAR 1
	/* module name */
	#define E920011023_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920011023_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920011023_COUNT_INT 4

	/* Event 920011024
		usbin irq invokes too frequency */
	/* error level */
	#define E920011024_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920011024_IC_NAME_VARCHAR 1
	/* module name */
	#define E920011024_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920011024_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920011024_COUNT_INT 4

	/* Event 920011025
		charging_enabled is set 0 in user verison */
	/* error level */
	#define E920011025_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920011025_IC_NAME_VARCHAR 1
	/* module name */
	#define E920011025_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920011025_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920011025_COUNT_INT 4

	/* Event 920011026
		factory_diag is set 0 in user version */
	/* error level */
	#define E920011026_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920011026_IC_NAME_VARCHAR 1
	/* module name */
	#define E920011026_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920011026_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920011026_COUNT_INT 4

	/* Event 920011027
		bq: enable OTG failed */
	/* error level */
	#define E920011027_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920011027_IC_NAME_VARCHAR 1
	/* module name */
	#define E920011027_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920011027_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920011027_COUNT_INT 4

	/* Event 920011028
		bq: i2c read failed */
	/* error level */
	#define E920011028_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920011028_IC_NAME_VARCHAR 1
	/* module name */
	#define E920011028_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920011028_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920011028_COUNT_INT 4

	/* Event 920011029
		bq: battery is charging when OTG mode is enabled */
	/* error level */
	#define E920011029_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920011029_IC_NAME_VARCHAR 1
	/* module name */
	#define E920011029_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920011029_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920011029_COUNT_INT 4

	/* Event 920011030
		bq reg error: WATCHDOG_FAULT */
	/* error level */
	#define E920011030_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920011030_IC_NAME_VARCHAR 1
	/* module name */
	#define E920011030_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920011030_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920011030_COUNT_INT 4

	/* Event 920011031
		bq reg error: OTG_FAULT */
	/* error level */
	#define E920011031_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920011031_IC_NAME_VARCHAR 1
	/* module name */
	#define E920011031_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920011031_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920011031_COUNT_INT 4

	/* Event 920011032
		bq reg error: POWER_SUPPLY_OVP */
	/* error level */
	#define E920011032_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920011032_IC_NAME_VARCHAR 1
	/* module name */
	#define E920011032_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920011032_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920011032_COUNT_INT 4

	/* Event 920011033
		bq reg error: THERMAL_SHUTDOWM */
	/* error level */
	#define E920011033_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920011033_IC_NAME_VARCHAR 1
	/* module name */
	#define E920011033_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920011033_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920011033_COUNT_INT 4

	/* Event 920011034
		bq reg error: BAT_FAULT_OVP */
	/* error level */
	#define E920011034_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920011034_IC_NAME_VARCHAR 1
	/* module name */
	#define E920011034_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920011034_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920011034_COUNT_INT 4

	/* Event 920011035
		bq reg error: CHRG_TIMER_EXPIRED */
	/* error level */
	#define E920011035_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920011035_IC_NAME_VARCHAR 1
	/* module name */
	#define E920011035_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920011035_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920011035_COUNT_INT 4

	/* Event 920011036
		linear charger: usb_overtemp */
	/* error level */
	#define E920011036_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920011036_IC_NAME_VARCHAR 1
	/* module name */
	#define E920011036_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920011036_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920011036_COUNT_INT 4

	/* Event 920011037
		linear charger: chg_failed */
	/* error level */
	#define E920011037_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920011037_IC_NAME_VARCHAR 1
	/* module name */
	#define E920011037_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920011037_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920011037_COUNT_INT 4

	/* Event 920011038
		linear charger: charge current is over 1.5A */
	/* error level */
	#define E920011038_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920011038_IC_NAME_VARCHAR 1
	/* module name */
	#define E920011038_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920011038_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920011038_COUNT_INT 4

	/* Event 920011039
		linear charger: discharge current is over 5A */
	/* error level */
	#define E920011039_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920011039_IC_NAME_VARCHAR 1
	/* module name */
	#define E920011039_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920011039_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920011039_COUNT_INT 4

	/* Event 920011040
		report discharging but actual soc is 100 percent */
	/* error level */
	#define E920011040_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920011040_IC_NAME_VARCHAR 1
	/* module name */
	#define E920011040_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920011040_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920011040_COUNT_INT 4

	/* Event 920011041
		battery voltage is over 4.45V */
	/* error level */
	#define E920011041_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920011041_IC_NAME_VARCHAR 1
	/* module name */
	#define E920011041_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920011041_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920011041_COUNT_INT 4

	/* Event 920011042
		still charge when batt voltage above 4.45V */
	/* error level */
	#define E920011042_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920011042_IC_NAME_VARCHAR 1
	/* module name */
	#define E920011042_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920011042_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920011042_COUNT_INT 4

	/* Event 920011043
		Charging timeout */
	/* error level */
	#define E920011043_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920011043_IC_NAME_VARCHAR 1
	/* module name */
	#define E920011043_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920011043_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920011043_COUNT_INT 4

	/* Event 920011044
		spmi interrupt error */
	/* error level */
	#define E920011044_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920011044_IC_NAME_VARCHAR 1
	/* module name */
	#define E920011044_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920011044_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920011044_COUNT_INT 4

	/* Event 920012000
		LP8758 INT ON BUCK3! */
	/* error level */
	#define E920012000_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920012000_IC_NAME_VARCHAR 1
	/* module name */
	#define E920012000_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920012000_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920012000_COUNT_INT 4

	/* Event 920012001
		LP8758 INT ON BUCK2! */
	/* error level */
	#define E920012001_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920012001_IC_NAME_VARCHAR 1
	/* module name */
	#define E920012001_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920012001_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920012001_COUNT_INT 4

	/* Event 920012002
		LP8758 INT ON BUCK1! */
	/* error level */
	#define E920012002_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920012002_IC_NAME_VARCHAR 1
	/* module name */
	#define E920012002_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920012002_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920012002_COUNT_INT 4

	/* Event 920012003
		LP8758 INT ON BUCK0! */
	/* error level */
	#define E920012003_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920012003_IC_NAME_VARCHAR 1
	/* module name */
	#define E920012003_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920012003_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920012003_COUNT_INT 4

	/* Event 920012004
		LP8758 TDIE REACH! */
	/* error level */
	#define E920012004_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920012004_IC_NAME_VARCHAR 1
	/* module name */
	#define E920012004_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920012004_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920012004_COUNT_INT 4

	/* Event 920012005
		LP8758 TDIE WARNNING! */
	/* error level */
	#define E920012005_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920012005_IC_NAME_VARCHAR 1
	/* module name */
	#define E920012005_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920012005_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920012005_COUNT_INT 4

	/* Event 920012006
		LP8758 ILIM INT ON BUCK1! */
	/* error level */
	#define E920012006_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920012006_IC_NAME_VARCHAR 1
	/* module name */
	#define E920012006_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920012006_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920012006_COUNT_INT 4

	/* Event 920012007
		LP8758 POWERGOOD INT ON BUCK0! */
	/* error level */
	#define E920012007_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920012007_IC_NAME_VARCHAR 1
	/* module name */
	#define E920012007_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920012007_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920012007_COUNT_INT 4

	/* Event 920012008
		LP8758 SC INT ON BUCK0! */
	/* error level */
	#define E920012008_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920012008_IC_NAME_VARCHAR 1
	/* module name */
	#define E920012008_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920012008_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920012008_COUNT_INT 4

	/* Event 920012009
		LP8758 ILIM INT ON BUCK0! */
	/* error level */
	#define E920012009_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920012009_IC_NAME_VARCHAR 1
	/* module name */
	#define E920012009_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920012009_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920012009_COUNT_INT 4

	/* Event 920012010
		HI6422V100 VSYS UNDER VOLTAGE! */
	/* error level */
	#define E920012010_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920012010_IC_NAME_VARCHAR 1
	/* module name */
	#define E920012010_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920012010_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920012010_COUNT_INT 4

	/* Event 920012011
		HI6422V100 VSYS OVER VOLTAGE! */
	/* error level */
	#define E920012011_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920012011_IC_NAME_VARCHAR 1
	/* module name */
	#define E920012011_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920012011_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920012011_COUNT_INT 4

	/* Event 920012012
		HI6422V100 OVER TMP LIMIT REACHED! */
	/* error level */
	#define E920012012_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920012012_IC_NAME_VARCHAR 1
	/* module name */
	#define E920012012_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920012012_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920012012_COUNT_INT 4

	/* Event 920012013
		HI6422V100 OVER TMP 150 RACHED! */
	/* error level */
	#define E920012013_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920012013_IC_NAME_VARCHAR 1
	/* module name */
	#define E920012013_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920012013_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920012013_COUNT_INT 4

	/* Event 920012014
		HI6422V100 VBAT UNDER 2.6V! */
	/* error level */
	#define E920012014_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920012014_IC_NAME_VARCHAR 1
	/* module name */
	#define E920012014_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920012014_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920012014_COUNT_INT 4

	/* Event 920012015
		HI6422V100 VBAT UNDER 2.3V! */
	/* error level */
	#define E920012015_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920012015_IC_NAME_VARCHAR 1
	/* module name */
	#define E920012015_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920012015_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920012015_COUNT_INT 4

	/* Event 920012016
		HI6422V100 BUCK34 SCP! */
	/* error level */
	#define E920012016_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920012016_IC_NAME_VARCHAR 1
	/* module name */
	#define E920012016_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920012016_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920012016_COUNT_INT 4

	/* Event 920012017
		HI6422V100 BUCK012 SCP! */
	/* error level */
	#define E920012017_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920012017_IC_NAME_VARCHAR 1
	/* module name */
	#define E920012017_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920012017_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920012017_COUNT_INT 4

	/* Event 920012018
		HI6422V100 BUCK4 OCP! */
	/* error level */
	#define E920012018_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920012018_IC_NAME_VARCHAR 1
	/* module name */
	#define E920012018_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920012018_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920012018_COUNT_INT 4

	/* Event 920012019
		HI6422V100 BUCK3 OCP! */
	/* error level */
	#define E920012019_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920012019_IC_NAME_VARCHAR 1
	/* module name */
	#define E920012019_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920012019_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920012019_COUNT_INT 4

	/* Event 920012020
		HI6422V100 BUCK2 OCP! */
	/* error level */
	#define E920012020_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920012020_IC_NAME_VARCHAR 1
	/* module name */
	#define E920012020_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920012020_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920012020_COUNT_INT 4

	/* Event 920012021
		HI6422V100 BUCK1 OCP! */
	/* error level */
	#define E920012021_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920012021_IC_NAME_VARCHAR 1
	/* module name */
	#define E920012021_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920012021_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920012021_COUNT_INT 4

	/* Event 920012022
		HI6422V100 BUCK0 OCP! */
	/* error level */
	#define E920012022_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920012022_IC_NAME_VARCHAR 1
	/* module name */
	#define E920012022_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920012022_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920012022_COUNT_INT 4

	/* Event 920012023
		VBAT BUCK4 OCP! */
	/* error level */
	#define E920012023_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920012023_IC_NAME_VARCHAR 1
	/* module name */
	#define E920012023_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920012023_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920012023_COUNT_INT 4

	/* Event 920012024
		VBAT BUCK3 OCP! */
	/* error level */
	#define E920012024_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920012024_IC_NAME_VARCHAR 1
	/* module name */
	#define E920012024_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920012024_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920012024_COUNT_INT 4

	/* Event 920012025
		VBAT BUCK2 OCP! */
	/* error level */
	#define E920012025_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920012025_IC_NAME_VARCHAR 1
	/* module name */
	#define E920012025_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920012025_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920012025_COUNT_INT 4

	/* Event 920012026
		VBAT BUCK1 OCP! */
	/* error level */
	#define E920012026_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920012026_IC_NAME_VARCHAR 1
	/* module name */
	#define E920012026_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920012026_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920012026_COUNT_INT 4

	/* Event 920012027
		VBAT BUCK0 OCP! */
	/* error level */
	#define E920012027_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920012027_IC_NAME_VARCHAR 1
	/* module name */
	#define E920012027_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920012027_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920012027_COUNT_INT 4

	/* Event 920012028
		HI6422V200 VSYS UNDER 2.6V! */
	/* error level */
	#define E920012028_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920012028_IC_NAME_VARCHAR 1
	/* module name */
	#define E920012028_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920012028_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920012028_COUNT_INT 4

	/* Event 920012029
		HI6422V200 VSYS OVER 6V! */
	/* error level */
	#define E920012029_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920012029_IC_NAME_VARCHAR 1
	/* module name */
	#define E920012029_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920012029_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920012029_COUNT_INT 4

	/* Event 920012030
		HI6422V200_VSYS UNDER 2.4V! */
	/* error level */
	#define E920012030_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920012030_IC_NAME_VARCHAR 1
	/* module name */
	#define E920012030_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920012030_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920012030_COUNT_INT 4

	/* Event 920012031
		HI6422V200 TEMP REACH 125! */
	/* error level */
	#define E920012031_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920012031_IC_NAME_VARCHAR 1
	/* module name */
	#define E920012031_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920012031_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920012031_COUNT_INT 4

	/* Event 920012032
		HI6422V200 TEMP REACH 140! */
	/* error level */
	#define E920012032_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920012032_IC_NAME_VARCHAR 1
	/* module name */
	#define E920012032_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920012032_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920012032_COUNT_INT 4

	/* Event 920012033
		HI6422V200 BUCK3 OCP! */
	/* error level */
	#define E920012033_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920012033_IC_NAME_VARCHAR 1
	/* module name */
	#define E920012033_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920012033_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920012033_COUNT_INT 4

	/* Event 920012034
		HI6422V200 BUCK2 OCP! */
	/* error level */
	#define E920012034_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920012034_IC_NAME_VARCHAR 1
	/* module name */
	#define E920012034_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920012034_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920012034_COUNT_INT 4

	/* Event 920012035
		HI6422V200 BUCK1 OCP! */
	/* error level */
	#define E920012035_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920012035_IC_NAME_VARCHAR 1
	/* module name */
	#define E920012035_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920012035_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920012035_COUNT_INT 4

	/* Event 920012036
		HI6422V200 BUCK0 OCP! */
	/* error level */
	#define E920012036_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920012036_IC_NAME_VARCHAR 1
	/* module name */
	#define E920012036_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920012036_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920012036_COUNT_INT 4

	/* Event 920012037
		HI6422V200 BUCK3 SCP! */
	/* error level */
	#define E920012037_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920012037_IC_NAME_VARCHAR 1
	/* module name */
	#define E920012037_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920012037_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920012037_COUNT_INT 4

	/* Event 920012038
		HI6422V200 BUCK2 SCP! */
	/* error level */
	#define E920012038_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920012038_IC_NAME_VARCHAR 1
	/* module name */
	#define E920012038_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920012038_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920012038_COUNT_INT 4

	/* Event 920012039
		HI6422V200 BUCK1 SCP! */
	/* error level */
	#define E920012039_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920012039_IC_NAME_VARCHAR 1
	/* module name */
	#define E920012039_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920012039_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920012039_COUNT_INT 4

	/* Event 920012040
		HI6422V200 BUCK0 SCP! */
	/* error level */
	#define E920012040_ERROR_LEVEL_INT 0
	/* IC name */
	#define E920012040_IC_NAME_VARCHAR 1
	/* module name */
	#define E920012040_MODULE_NAME_VARCHAR 2
	/* description */
	#define E920012040_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E920012040_COUNT_INT 4

	/* Event 921001000
		soc hifi reset */
	/* error level */
	#define E921001000_ERROR_LEVEL_INT 0
	/* IC name */
	#define E921001000_IC_NAME_VARCHAR 1
	/* module name */
	#define E921001000_MODULE_NAME_VARCHAR 2
	/* description */
	#define E921001000_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E921001000_COUNT_INT 4

	/* Event 921001001
		codec hifi reset */
	/* error level */
	#define E921001001_ERROR_LEVEL_INT 0
	/* IC name */
	#define E921001001_IC_NAME_VARCHAR 1
	/* module name */
	#define E921001001_MODULE_NAME_VARCHAR 2
	/* description */
	#define E921001001_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E921001001_COUNT_INT 4

	/* Event 921001002
		(hisi20204) */
	/* error level */
	#define E921001002_ERROR_LEVEL_INT 0
	/* IC name */
	#define E921001002_IC_NAME_VARCHAR 1
	/* module name */
	#define E921001002_MODULE_NAME_VARCHAR 2
	/* description */
	#define E921001002_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E921001002_COUNT_INT 4

	/* Event 921001003
		frequency modulation DDRto 360mhz lack of performance */
	/* error level */
	#define E921001003_ERROR_LEVEL_INT 0
	/* IC name */
	#define E921001003_IC_NAME_VARCHAR 1
	/* module name */
	#define E921001003_MODULE_NAME_VARCHAR 2
	/* description */
	#define E921001003_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E921001003_COUNT_INT 4

	/* Event 921001004
		Power on Codec PLL fail */
	/* error level */
	#define E921001004_ERROR_LEVEL_INT 0
	/* IC name */
	#define E921001004_IC_NAME_VARCHAR 1
	/* module name */
	#define E921001004_MODULE_NAME_VARCHAR 2
	/* description */
	#define E921001004_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E921001004_COUNT_INT 4

	/* Event 921001005
		Codec PLL unlock */
	/* error level */
	#define E921001005_ERROR_LEVEL_INT 0
	/* IC name */
	#define E921001005_IC_NAME_VARCHAR 1
	/* module name */
	#define E921001005_MODULE_NAME_VARCHAR 2
	/* description */
	#define E921001005_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E921001005_COUNT_INT 4

	/* Event 921001006
		can not lock Codec PLL */
	/* error level */
	#define E921001006_ERROR_LEVEL_INT 0
	/* IC name */
	#define E921001006_IC_NAME_VARCHAR 1
	/* module name */
	#define E921001006_MODULE_NAME_VARCHAR 2
	/* description */
	#define E921001006_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E921001006_COUNT_INT 4

	/* Event 921001007
		error happen when try to read slimbus */
	/* error level */
	#define E921001007_ERROR_LEVEL_INT 0
	/* IC name */
	#define E921001007_IC_NAME_VARCHAR 1
	/* module name */
	#define E921001007_MODULE_NAME_VARCHAR 2
	/* description */
	#define E921001007_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E921001007_COUNT_INT 4

	/* Event 921001008
		slimbus lost synchronization */
	/* error level */
	#define E921001008_ERROR_LEVEL_INT 0
	/* IC name */
	#define E921001008_IC_NAME_VARCHAR 1
	/* module name */
	#define E921001008_MODULE_NAME_VARCHAR 2
	/* description */
	#define E921001008_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E921001008_COUNT_INT 4

	/* Event 921001009
		6402_mbhc_abnormal_headset_type */
	/* error level */
	#define E921001009_ERROR_LEVEL_INT 0
	/* IC name */
	#define E921001009_IC_NAME_VARCHAR 1
	/* module name */
	#define E921001009_MODULE_NAME_VARCHAR 2
	/* description */
	#define E921001009_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E921001009_COUNT_INT 4

	/* Event 921001010
		pcm_write error */
	/* error level */
	#define E921001010_ERROR_LEVEL_INT 0
	/* IC name */
	#define E921001010_IC_NAME_VARCHAR 1
	/* module name */
	#define E921001010_MODULE_NAME_VARCHAR 2
	/* description */
	#define E921001010_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E921001010_COUNT_INT 4

	/* Event 921001011
		creat Track fail */
	/* error level */
	#define E921001011_ERROR_LEVEL_INT 0
	/* IC name */
	#define E921001011_IC_NAME_VARCHAR 1
	/* module name */
	#define E921001011_MODULE_NAME_VARCHAR 2
	/* description */
	#define E921001011_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E921001011_COUNT_INT 4

	/* Event 921001012
		Headphone type identification errors */
	/* error level */
	#define E921001012_ERROR_LEVEL_INT 0
	/* IC name */
	#define E921001012_IC_NAME_VARCHAR 1
	/* module name */
	#define E921001012_MODULE_NAME_VARCHAR 2
	/* description */
	#define E921001012_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E921001012_COUNT_INT 4

	/* Event 921001013
		DSP start error */
	/* error level */
	#define E921001013_ERROR_LEVEL_INT 0
	/* IC name */
	#define E921001013_IC_NAME_VARCHAR 1
	/* module name */
	#define E921001013_MODULE_NAME_VARCHAR 2
	/* description */
	#define E921001013_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E921001013_COUNT_INT 4

	/* Event 921001014
		audio load error */
	/* error level */
	#define E921001014_ERROR_LEVEL_INT 0
	/* IC name */
	#define E921001014_IC_NAME_VARCHAR 1
	/* module name */
	#define E921001014_MODULE_NAME_VARCHAR 2
	/* description */
	#define E921001014_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E921001014_COUNT_INT 4

	/* Event 921001015
		audio hal layer error */
	/* error level */
	#define E921001015_ERROR_LEVEL_INT 0
	/* IC name */
	#define E921001015_IC_NAME_VARCHAR 1
	/* module name */
	#define E921001015_MODULE_NAME_VARCHAR 2
	/* description */
	#define E921001015_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E921001015_COUNT_INT 4

	/* Event 921001016
		modem crash error */
	/* error level */
	#define E921001016_ERROR_LEVEL_INT 0
	/* IC name */
	#define E921001016_IC_NAME_VARCHAR 1
	/* module name */
	#define E921001016_MODULE_NAME_VARCHAR 2
	/* description */
	#define E921001016_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E921001016_COUNT_INT 4

	/* Event 921001017
		headset plug and press less than 500ms */
	/* error level */
	#define E921001017_ERROR_LEVEL_INT 0
	/* IC name */
	#define E921001017_IC_NAME_VARCHAR 1
	/* module name */
	#define E921001017_MODULE_NAME_VARCHAR 2
	/* description */
	#define E921001017_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E921001017_COUNT_INT 4

	/* Event 921001018
		headset press and release less than 500ms */
	/* error level */
	#define E921001018_ERROR_LEVEL_INT 0
	/* IC name */
	#define E921001018_IC_NAME_VARCHAR 1
	/* module name */
	#define E921001018_MODULE_NAME_VARCHAR 2
	/* description */
	#define E921001018_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E921001018_COUNT_INT 4

	/* Event 921001019
		headset plug and release less than 500ms */
	/* error level */
	#define E921001019_ERROR_LEVEL_INT 0
	/* IC name */
	#define E921001019_IC_NAME_VARCHAR 1
	/* module name */
	#define E921001019_MODULE_NAME_VARCHAR 2
	/* description */
	#define E921001019_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E921001019_COUNT_INT 4

	/* Event 921001020
		MMI test time too short less than 2s */
	/* error level */
	#define E921001020_ERROR_LEVEL_INT 0
	/* IC name */
	#define E921001020_IC_NAME_VARCHAR 1
	/* module name */
	#define E921001020_MODULE_NAME_VARCHAR 2
	/* description */
	#define E921001020_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E921001020_COUNT_INT 4

	/* Event 921001021
		afe codec digital clock config fail */
	/* error level */
	#define E921001021_ERROR_LEVEL_INT 0
	/* IC name */
	#define E921001021_IC_NAME_VARCHAR 1
	/* module name */
	#define E921001021_MODULE_NAME_VARCHAR 2
	/* description */
	#define E921001021_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E921001021_COUNT_INT 4

	/* Event 921001022
		modem crash codec callback */
	/* error level */
	#define E921001022_ERROR_LEVEL_INT 0
	/* IC name */
	#define E921001022_IC_NAME_VARCHAR 1
	/* module name */
	#define E921001022_MODULE_NAME_VARCHAR 2
	/* description */
	#define E921001022_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E921001022_COUNT_INT 4

	/* Event 921001023
		spmi lock sleep timeout */
	/* error level */
	#define E921001023_ERROR_LEVEL_INT 0
	/* IC name */
	#define E921001023_IC_NAME_VARCHAR 1
	/* module name */
	#define E921001023_MODULE_NAME_VARCHAR 2
	/* description */
	#define E921001023_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E921001023_COUNT_INT 4

	/* Event 921001024
		audio stream detect find a issue */
	/* error level */
	#define E921001024_ERROR_LEVEL_INT 0
	/* IC name */
	#define E921001024_IC_NAME_VARCHAR 1
	/* module name */
	#define E921001024_MODULE_NAME_VARCHAR 2
	/* description */
	#define E921001024_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E921001024_COUNT_INT 4

	/* Event 921002000
		PMU operation fail */
	/* error level */
	#define E921002000_ERROR_LEVEL_INT 0
	/* IC name */
	#define E921002000_IC_NAME_VARCHAR 1
	/* module name */
	#define E921002000_MODULE_NAME_VARCHAR 2
	/* description */
	#define E921002000_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E921002000_COUNT_INT 4

	/* Event 921002001
		operation work queue fail */
	/* error level */
	#define E921002001_ERROR_LEVEL_INT 0
	/* IC name */
	#define E921002001_IC_NAME_VARCHAR 1
	/* module name */
	#define E921002001_MODULE_NAME_VARCHAR 2
	/* description */
	#define E921002001_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E921002001_COUNT_INT 4

	/* Event 921002002
		PMU operation fail */
	/* error level */
	#define E921002002_ERROR_LEVEL_INT 0
	/* IC name */
	#define E921002002_IC_NAME_VARCHAR 1
	/* module name */
	#define E921002002_MODULE_NAME_VARCHAR 2
	/* description */
	#define E921002002_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E921002002_COUNT_INT 4

	/* Event 921002003
		read ADC fail */
	/* error level */
	#define E921002003_ERROR_LEVEL_INT 0
	/* IC name */
	#define E921002003_IC_NAME_VARCHAR 1
	/* module name */
	#define E921002003_MODULE_NAME_VARCHAR 2
	/* description */
	#define E921002003_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E921002003_COUNT_INT 4

	/* Event 921002004
		read ADC fail */
	/* error level */
	#define E921002004_ERROR_LEVEL_INT 0
	/* IC name */
	#define E921002004_IC_NAME_VARCHAR 1
	/* module name */
	#define E921002004_MODULE_NAME_VARCHAR 2
	/* description */
	#define E921002004_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E921002004_COUNT_INT 4

	/* Event 921002005
		Charging status chaos */
	/* error level */
	#define E921002005_ERROR_LEVEL_INT 0
	/* IC name */
	#define E921002005_IC_NAME_VARCHAR 1
	/* module name */
	#define E921002005_MODULE_NAME_VARCHAR 2
	/* description */
	#define E921002005_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E921002005_COUNT_INT 4

	/* Event 921002006
		work queue operation failed */
	/* error level */
	#define E921002006_ERROR_LEVEL_INT 0
	/* IC name */
	#define E921002006_IC_NAME_VARCHAR 1
	/* module name */
	#define E921002006_MODULE_NAME_VARCHAR 2
	/* description */
	#define E921002006_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E921002006_COUNT_INT 4

	/* Event 921002007
		wrong Noise-Cancelling Headphones button event */
	/* error level */
	#define E921002007_ERROR_LEVEL_INT 0
	/* IC name */
	#define E921002007_IC_NAME_VARCHAR 1
	/* module name */
	#define E921002007_MODULE_NAME_VARCHAR 2
	/* description */
	#define E921002007_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E921002007_COUNT_INT 4

	/* Event 921003000
		SMARTPA I2C abnormally */
	/* error level */
	#define E921003000_ERROR_LEVEL_INT 0
	/* IC name */
	#define E921003000_IC_NAME_VARCHAR 1
	/* module name */
	#define E921003000_MODULE_NAME_VARCHAR 2
	/* description */
	#define E921003000_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E921003000_COUNT_INT 4

	/* Event 922001000
		lcd underflow issue */
	/* error level */
	#define E922001000_ERROR_LEVEL_INT 0
	/* IC name */
	#define E922001000_IC_NAME_VARCHAR 1
	/* module name */
	#define E922001000_MODULE_NAME_VARCHAR 2
	/* description */
	#define E922001000_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E922001000_COUNT_INT 4

	/* Event 922001001
		TE timeout */
	/* error level */
	#define E922001001_ERROR_LEVEL_INT 0
	/* IC name */
	#define E922001001_IC_NAME_VARCHAR 1
	/* module name */
	#define E922001001_MODULE_NAME_VARCHAR 2
	/* description */
	#define E922001001_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E922001001_COUNT_INT 4

	/* Event 922001002
		lcd status error */
	/* error level */
	#define E922001002_ERROR_LEVEL_INT 0
	/* IC name */
	#define E922001002_IC_NAME_VARCHAR 1
	/* module name */
	#define E922001002_MODULE_NAME_VARCHAR 2
	/* description */
	#define E922001002_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E922001002_COUNT_INT 4

	/* Event 922001003
		VSP status error */
	/* error level */
	#define E922001003_ERROR_LEVEL_INT 0
	/* IC name */
	#define E922001003_IC_NAME_VARCHAR 1
	/* module name */
	#define E922001003_MODULE_NAME_VARCHAR 2
	/* description */
	#define E922001003_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E922001003_COUNT_INT 4

	/* Event 922001004
		lcd esd */
	/* error level */
	#define E922001004_ERROR_LEVEL_INT 0
	/* IC name */
	#define E922001004_IC_NAME_VARCHAR 1
	/* module name */
	#define E922001004_MODULE_NAME_VARCHAR 2
	/* description */
	#define E922001004_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E922001004_COUNT_INT 4

	/* Event 922001005
		LCD_BRIGHTNESS_ERROR */
	/* error level */
	#define E922001005_ERROR_LEVEL_INT 0
	/* IC name */
	#define E922001005_IC_NAME_VARCHAR 1
	/* module name */
	#define E922001005_MODULE_NAME_VARCHAR 2
	/* description */
	#define E922001005_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E922001005_COUNT_INT 4

	/* Event 922001006
		ESD ERROR:ret = (1,2,3...)or ESD ERROR:reg (0x0a,0x0d)
		= (0x98,0x07) */
	/* error level */
	#define E922001006_ERROR_LEVEL_INT 0
	/* IC name */
	#define E922001006_IC_NAME_VARCHAR 1
	/* module name */
	#define E922001006_MODULE_NAME_VARCHAR 2
	/* description */
	#define E922001006_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E922001006_COUNT_INT 4

	/* Event 922001007
		cd happen ocp */
	/* error level */
	#define E922001007_ERROR_LEVEL_INT 0
	/* IC name */
	#define E922001007_IC_NAME_VARCHAR 1
	/* module name */
	#define E922001007_MODULE_NAME_VARCHAR 2
	/* description */
	#define E922001007_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E922001007_COUNT_INT 4

	/* Event 922001008
		backlight ic ovp/ocp occur */
	/* error level */
	#define E922001008_ERROR_LEVEL_INT 0
	/* IC name */
	#define E922001008_IC_NAME_VARCHAR 1
	/* module name */
	#define E922001008_MODULE_NAME_VARCHAR 2
	/* description */
	#define E922001008_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E922001008_COUNT_INT 4

	/* Event 922001009
		lcd comfort mode */
	/* error level */
	#define E922001009_ERROR_LEVEL_INT 0
	/* IC name */
	#define E922001009_IC_NAME_VARCHAR 1
	/* module name */
	#define E922001009_MODULE_NAME_VARCHAR 2
	/* description */
	#define E922001009_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E922001009_COUNT_INT 4

	/* Event 922001010
		LCD mipi cmd tx error */
	/* error level */
	#define E922001010_ERROR_LEVEL_INT 0
	/* IC name */
	#define E922001010_IC_NAME_VARCHAR 1
	/* module name */
	#define E922001010_MODULE_NAME_VARCHAR 2
	/* description */
	#define E922001010_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E922001010_COUNT_INT 4

	/* Event 922001011
		LCD TE time out */
	/* error level */
	#define E922001011_ERROR_LEVEL_INT 0
	/* IC name */
	#define E922001011_IC_NAME_VARCHAR 1
	/* module name */
	#define E922001011_MODULE_NAME_VARCHAR 2
	/* description */
	#define E922001011_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E922001011_COUNT_INT 4

	/* Event 922001012
		LCD status register error */
	/* error level */
	#define E922001012_ERROR_LEVEL_INT 0
	/* IC name */
	#define E922001012_IC_NAME_VARCHAR 1
	/* module name */
	#define E922001012_MODULE_NAME_VARCHAR 2
	/* description */
	#define E922001012_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E922001012_COUNT_INT 4

	/* Event 922001013
		MDP/GPU error */
	/* error level */
	#define E922001013_ERROR_LEVEL_INT 0
	/* IC name */
	#define E922001013_IC_NAME_VARCHAR 1
	/* module name */
	#define E922001013_MODULE_NAME_VARCHAR 2
	/* description */
	#define E922001013_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E922001013_COUNT_INT 4

	/* Event 922001014
		LCD OTP error */
	/* error level */
	#define E922001014_ERROR_LEVEL_INT 0
	/* IC name */
	#define E922001014_IC_NAME_VARCHAR 1
	/* module name */
	#define E922001014_MODULE_NAME_VARCHAR 2
	/* description */
	#define E922001014_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E922001014_COUNT_INT 4

	/* Event 922001015
		LCD brightness error */
	/* error level */
	#define E922001015_ERROR_LEVEL_INT 0
	/* IC name */
	#define E922001015_IC_NAME_VARCHAR 1
	/* module name */
	#define E922001015_MODULE_NAME_VARCHAR 2
	/* description */
	#define E922001015_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E922001015_COUNT_INT 4

	/* Event 922001016
		LCD mipi dsi isr error */
	/* error level */
	#define E922001016_ERROR_LEVEL_INT 0
	/* IC name */
	#define E922001016_IC_NAME_VARCHAR 1
	/* module name */
	#define E922001016_MODULE_NAME_VARCHAR 2
	/* description */
	#define E922001016_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E922001016_COUNT_INT 4

	/* Event 922001017
		LCD mdp isr error */
	/* error level */
	#define E922001017_ERROR_LEVEL_INT 0
	/* IC name */
	#define E922001017_IC_NAME_VARCHAR 1
	/* module name */
	#define E922001017_MODULE_NAME_VARCHAR 2
	/* description */
	#define E922001017_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E922001017_COUNT_INT 4

	/* Event 922001018
		LCD ESD status error */
	/* error level */
	#define E922001018_ERROR_LEVEL_INT 0
	/* IC name */
	#define E922001018_IC_NAME_VARCHAR 1
	/* module name */
	#define E922001018_MODULE_NAME_VARCHAR 2
	/* description */
	#define E922001018_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E922001018_COUNT_INT 4

	/* Event 922001019
		LCD ESD reset error */
	/* error level */
	#define E922001019_ERROR_LEVEL_INT 0
	/* IC name */
	#define E922001019_IC_NAME_VARCHAR 1
	/* module name */
	#define E922001019_MODULE_NAME_VARCHAR 2
	/* description */
	#define E922001019_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E922001019_COUNT_INT 4

	/* Event 922001020
		LCD power status error */
	/* error level */
	#define E922001020_ERROR_LEVEL_INT 0
	/* IC name */
	#define E922001020_IC_NAME_VARCHAR 1
	/* module name */
	#define E922001020_MODULE_NAME_VARCHAR 2
	/* description */
	#define E922001020_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E922001020_COUNT_INT 4

	/* Event 922001021
		LCD underrun error */
	/* error level */
	#define E922001021_ERROR_LEVEL_INT 0
	/* IC name */
	#define E922001021_IC_NAME_VARCHAR 1
	/* module name */
	#define E922001021_MODULE_NAME_VARCHAR 2
	/* description */
	#define E922001021_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E922001021_COUNT_INT 4

	/* Event 922001022
		mdss IOMMU error */
	/* error level */
	#define E922001022_ERROR_LEVEL_INT 0
	/* IC name */
	#define E922001022_IC_NAME_VARCHAR 1
	/* module name */
	#define E922001022_MODULE_NAME_VARCHAR 2
	/* description */
	#define E922001022_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E922001022_COUNT_INT 4

	/* Event 922001023
		mdss pipe error */
	/* error level */
	#define E922001023_ERROR_LEVEL_INT 0
	/* IC name */
	#define E922001023_IC_NAME_VARCHAR 1
	/* module name */
	#define E922001023_MODULE_NAME_VARCHAR 2
	/* description */
	#define E922001023_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E922001023_COUNT_INT 4

	/* Event 922001024
		mdss pingpong error */
	/* error level */
	#define E922001024_ERROR_LEVEL_INT 0
	/* IC name */
	#define E922001024_IC_NAME_VARCHAR 1
	/* module name */
	#define E922001024_MODULE_NAME_VARCHAR 2
	/* description */
	#define E922001024_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E922001024_COUNT_INT 4

	/* Event 922001025
		mdss vsp/vsn error */
	/* error level */
	#define E922001025_ERROR_LEVEL_INT 0
	/* IC name */
	#define E922001025_IC_NAME_VARCHAR 1
	/* module name */
	#define E922001025_MODULE_NAME_VARCHAR 2
	/* description */
	#define E922001025_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E922001025_COUNT_INT 4

	/* Event 922001026
		mdss rotator error */
	/* error level */
	#define E922001026_ERROR_LEVEL_INT 0
	/* IC name */
	#define E922001026_IC_NAME_VARCHAR 1
	/* module name */
	#define E922001026_MODULE_NAME_VARCHAR 2
	/* description */
	#define E922001026_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E922001026_COUNT_INT 4

	/* Event 922001027
		mdss fence error */
	/* error level */
	#define E922001027_ERROR_LEVEL_INT 0
	/* IC name */
	#define E922001027_IC_NAME_VARCHAR 1
	/* module name */
	#define E922001027_MODULE_NAME_VARCHAR 2
	/* description */
	#define E922001027_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E922001027_COUNT_INT 4

	/* Event 922001028
		mdss cmd stop error */
	/* error level */
	#define E922001028_ERROR_LEVEL_INT 0
	/* IC name */
	#define E922001028_IC_NAME_VARCHAR 1
	/* module name */
	#define E922001028_MODULE_NAME_VARCHAR 2
	/* description */
	#define E922001028_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E922001028_COUNT_INT 4

	/* Event 922001029
		mdss video display error */
	/* error level */
	#define E922001029_ERROR_LEVEL_INT 0
	/* IC name */
	#define E922001029_IC_NAME_VARCHAR 1
	/* module name */
	#define E922001029_MODULE_NAME_VARCHAR 2
	/* description */
	#define E922001029_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E922001029_COUNT_INT 4

	/* Event 922001030
		mdss mdp clk error */
	/* error level */
	#define E922001030_ERROR_LEVEL_INT 0
	/* IC name */
	#define E922001030_IC_NAME_VARCHAR 1
	/* module name */
	#define E922001030_MODULE_NAME_VARCHAR 2
	/* description */
	#define E922001030_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E922001030_COUNT_INT 4

	/* Event 922001031
		mdss mdp busy error */
	/* error level */
	#define E922001031_ERROR_LEVEL_INT 0
	/* IC name */
	#define E922001031_IC_NAME_VARCHAR 1
	/* module name */
	#define E922001031_MODULE_NAME_VARCHAR 2
	/* description */
	#define E922001031_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E922001031_COUNT_INT 4

	/* Event 922002000
		gpu hang error */
	/* error level */
	#define E922002000_ERROR_LEVEL_INT 0
	/* IC name */
	#define E922002000_IC_NAME_VARCHAR 1
	/* module name */
	#define E922002000_MODULE_NAME_VARCHAR 2
	/* description */
	#define E922002000_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E922002000_COUNT_INT 4

	/* Event 922002001
		gpu page fault error */
	/* error level */
	#define E922002001_ERROR_LEVEL_INT 0
	/* IC name */
	#define E922002001_IC_NAME_VARCHAR 1
	/* module name */
	#define E922002001_MODULE_NAME_VARCHAR 2
	/* description */
	#define E922002001_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E922002001_COUNT_INT 4

	/* Event 922002002
		gpu snapshot log */
	/* error level */
	#define E922002002_ERROR_LEVEL_INT 0
	/* IC name */
	#define E922002002_IC_NAME_VARCHAR 1
	/* module name */
	#define E922002002_MODULE_NAME_VARCHAR 2
	/* description */
	#define E922002002_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E922002002_COUNT_INT 4

	/* Event 923001000
		Pastar no signal fault */
	/* error level */
	#define E923001000_ERROR_LEVEL_INT 0
	/* IC name */
	#define E923001000_IC_NAME_VARCHAR 1
	/* module name */
	#define E923001000_MODULE_NAME_VARCHAR 2
	/* description */
	#define E923001000_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E923001000_COUNT_INT 4

	/* Event 923002000
		I2C Write Error, Error Type: Others */
	/* error level */
	#define E923002000_ERROR_LEVEL_INT 0
	/* IC name */
	#define E923002000_IC_NAME_VARCHAR 1
	/* module name */
	#define E923002000_MODULE_NAME_VARCHAR 2
	/* description */
	#define E923002000_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E923002000_COUNT_INT 4

	/* Event 923002001
		I2C Read Error, Error Type: Others */
	/* error level */
	#define E923002001_ERROR_LEVEL_INT 0
	/* IC name */
	#define E923002001_IC_NAME_VARCHAR 1
	/* module name */
	#define E923002001_MODULE_NAME_VARCHAR 2
	/* description */
	#define E923002001_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E923002001_COUNT_INT 4

	/* Event 923002002
		Clock Enable Fail */
	/* error level */
	#define E923002002_ERROR_LEVEL_INT 0
	/* IC name */
	#define E923002002_IC_NAME_VARCHAR 1
	/* module name */
	#define E923002002_MODULE_NAME_VARCHAR 2
	/* description */
	#define E923002002_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E923002002_COUNT_INT 4

	/* Event 923002003
		I2C Write Error, Error Type: Operation not supported
		on transport endpoint */
	/* error level */
	#define E923002003_ERROR_LEVEL_INT 0
	/* IC name */
	#define E923002003_IC_NAME_VARCHAR 1
	/* module name */
	#define E923002003_MODULE_NAME_VARCHAR 2
	/* description */
	#define E923002003_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E923002003_COUNT_INT 4

	/* Event 923002004
		I2C Read Error, Error Type: Operation not supported
		on transport endpoint */
	/* error level */
	#define E923002004_ERROR_LEVEL_INT 0
	/* IC name */
	#define E923002004_IC_NAME_VARCHAR 1
	/* module name */
	#define E923002004_MODULE_NAME_VARCHAR 2
	/* description */
	#define E923002004_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E923002004_COUNT_INT 4

	/* Event 923002005
		I2C Write Error, Error Type: Remote I/O error */
	/* error level */
	#define E923002005_ERROR_LEVEL_INT 0
	/* IC name */
	#define E923002005_IC_NAME_VARCHAR 1
	/* module name */
	#define E923002005_MODULE_NAME_VARCHAR 2
	/* description */
	#define E923002005_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E923002005_COUNT_INT 4

	/* Event 923002006
		I2C Read Error, Error Type: Remote I/O error */
	/* error level */
	#define E923002006_ERROR_LEVEL_INT 0
	/* IC name */
	#define E923002006_IC_NAME_VARCHAR 1
	/* module name */
	#define E923002006_MODULE_NAME_VARCHAR 2
	/* description */
	#define E923002006_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E923002006_COUNT_INT 4

	/* Event 923002007
		RD Station I2C Write Error, Error Type: Others */
	/* error level */
	#define E923002007_ERROR_LEVEL_INT 0
	/* IC name */
	#define E923002007_IC_NAME_VARCHAR 1
	/* module name */
	#define E923002007_MODULE_NAME_VARCHAR 2
	/* description */
	#define E923002007_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E923002007_COUNT_INT 4

	/* Event 923002008
		RD Station I2C Read Error, Error Type: Others */
	/* error level */
	#define E923002008_ERROR_LEVEL_INT 0
	/* IC name */
	#define E923002008_IC_NAME_VARCHAR 1
	/* module name */
	#define E923002008_MODULE_NAME_VARCHAR 2
	/* description */
	#define E923002008_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E923002008_COUNT_INT 4

	/* Event 923002009
		RD Station I2C Write Error, Error Type: Operation not
		supported on transport endpoint */
	/* error level */
	#define E923002009_ERROR_LEVEL_INT 0
	/* IC name */
	#define E923002009_IC_NAME_VARCHAR 1
	/* module name */
	#define E923002009_MODULE_NAME_VARCHAR 2
	/* description */
	#define E923002009_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E923002009_COUNT_INT 4

	/* Event 923002010
		RD Station I2C Read Error, Error Type: Operation not
		supported on transport endpoint */
	/* error level */
	#define E923002010_ERROR_LEVEL_INT 0
	/* IC name */
	#define E923002010_IC_NAME_VARCHAR 1
	/* module name */
	#define E923002010_MODULE_NAME_VARCHAR 2
	/* description */
	#define E923002010_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E923002010_COUNT_INT 4

	/* Event 923002011
		RD Station I2C Write Error, Error Type: Remote I/O
		error */
	/* error level */
	#define E923002011_ERROR_LEVEL_INT 0
	/* IC name */
	#define E923002011_IC_NAME_VARCHAR 1
	/* module name */
	#define E923002011_MODULE_NAME_VARCHAR 2
	/* description */
	#define E923002011_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E923002011_COUNT_INT 4

	/* Event 923002012
		RD Station I2C Read Error, Error Type: Remote I/O error */
	/* error level */
	#define E923002012_ERROR_LEVEL_INT 0
	/* IC name */
	#define E923002012_IC_NAME_VARCHAR 1
	/* module name */
	#define E923002012_MODULE_NAME_VARCHAR 2
	/* description */
	#define E923002012_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E923002012_COUNT_INT 4

	/* Event 923002013
		Check NFC SIM Status error */
	/* error level */
	#define E923002013_ERROR_LEVEL_INT 0
	/* IC name */
	#define E923002013_IC_NAME_VARCHAR 1
	/* module name */
	#define E923002013_MODULE_NAME_VARCHAR 2
	/* description */
	#define E923002013_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E923002013_COUNT_INT 4

	/* Event 924001000
		hota update fail */
	/* error level */
	#define E924001000_ERROR_LEVEL_INT 0
	/* IC name */
	#define E924001000_IC_NAME_VARCHAR 1
	/* module name */
	#define E924001000_MODULE_NAME_VARCHAR 2
	/* description */
	#define E924001000_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E924001000_COUNT_INT 4

	/* Event 924002000
		selinux server accessed or execute authority was refused */
	/* error level */
	#define E924002000_ERROR_LEVEL_INT 0
	/* IC name */
	#define E924002000_IC_NAME_VARCHAR 1
	/* module name */
	#define E924002000_MODULE_NAME_VARCHAR 2
	/* description */
	#define E924002000_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E924002000_COUNT_INT 4

	/* Event 924003000
		MM_BUDDY_SLUB_BIG */
	/* error level */
	#define E924003000_ERROR_LEVEL_INT 0
	/* IC name */
	#define E924003000_IC_NAME_VARCHAR 1
	/* module name */
	#define E924003000_MODULE_NAME_VARCHAR 2
	/* description */
	#define E924003000_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E924003000_COUNT_INT 4

	/* Event 924003001
		MM_MLOCK_BIG */
	/* error level */
	#define E924003001_ERROR_LEVEL_INT 0
	/* IC name */
	#define E924003001_IC_NAME_VARCHAR 1
	/* module name */
	#define E924003001_MODULE_NAME_VARCHAR 2
	/* description */
	#define E924003001_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E924003001_COUNT_INT 4

	/* Event 925001000
		spi_sync timeout error */
	/* error level */
	#define E925001000_ERROR_LEVEL_INT 0
	/* IC name */
	#define E925001000_IC_NAME_VARCHAR 1
	/* module name */
	#define E925001000_MODULE_NAME_VARCHAR 2
	/* description */
	#define E925001000_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E925001000_COUNT_INT 4

	/* Event 925001001
		spi invalid argument error */
	/* error level */
	#define E925001001_ERROR_LEVEL_INT 0
	/* IC name */
	#define E925001001_IC_NAME_VARCHAR 1
	/* module name */
	#define E925001001_MODULE_NAME_VARCHAR 2
	/* description */
	#define E925001001_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E925001001_COUNT_INT 4

	/* Event 925001002
		spi shutdown error */
	/* error level */
	#define E925001002_ERROR_LEVEL_INT 0
	/* IC name */
	#define E925001002_IC_NAME_VARCHAR 1
	/* module name */
	#define E925001002_MODULE_NAME_VARCHAR 2
	/* description */
	#define E925001002_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E925001002_COUNT_INT 4

	/* Event 925001003
		spi unkown error */
	/* error level */
	#define E925001003_ERROR_LEVEL_INT 0
	/* IC name */
	#define E925001003_IC_NAME_VARCHAR 1
	/* module name */
	#define E925001003_MODULE_NAME_VARCHAR 2
	/* description */
	#define E925001003_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E925001003_COUNT_INT 4

	/* Event 925001004
		sg_alloc_table sgt_rx error */
	/* error level */
	#define E925001004_ERROR_LEVEL_INT 0
	/* IC name */
	#define E925001004_IC_NAME_VARCHAR 1
	/* module name */
	#define E925001004_MODULE_NAME_VARCHAR 2
	/* description */
	#define E925001004_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E925001004_COUNT_INT 4

	/* Event 925001005
		sg_alloc_table sgt_tx error */
	/* error level */
	#define E925001005_ERROR_LEVEL_INT 0
	/* IC name */
	#define E925001005_IC_NAME_VARCHAR 1
	/* module name */
	#define E925001005_MODULE_NAME_VARCHAR 2
	/* description */
	#define E925001005_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E925001005_COUNT_INT 4

	/* Event 925002000
		sdio read/write error */
	/* error level */
	#define E925002000_ERROR_LEVEL_INT 0
	/* IC name */
	#define E925002000_IC_NAME_VARCHAR 1
	/* module name */
	#define E925002000_MODULE_NAME_VARCHAR 2
	/* description */
	#define E925002000_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E925002000_COUNT_INT 4

	/* Event 925002001
		sdio controler init error */
	/* error level */
	#define E925002001_ERROR_LEVEL_INT 0
	/* IC name */
	#define E925002001_IC_NAME_VARCHAR 1
	/* module name */
	#define E925002001_MODULE_NAME_VARCHAR 2
	/* description */
	#define E925002001_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E925002001_COUNT_INT 4

	/* Event 925002002
		sdio hardware lock */
	/* error level */
	#define E925002002_ERROR_LEVEL_INT 0
	/* IC name */
	#define E925002002_IC_NAME_VARCHAR 1
	/* module name */
	#define E925002002_MODULE_NAME_VARCHAR 2
	/* description */
	#define E925002002_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E925002002_COUNT_INT 4

	/* Event 925002003
		read/write timeout */
	/* error level */
	#define E925002003_ERROR_LEVEL_INT 0
	/* IC name */
	#define E925002003_IC_NAME_VARCHAR 1
	/* module name */
	#define E925002003_MODULE_NAME_VARCHAR 2
	/* description */
	#define E925002003_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E925002003_COUNT_INT 4

	/* Event 925002004
		SDIO ATTCH fail */
	/* error level */
	#define E925002004_ERROR_LEVEL_INT 0
	/* IC name */
	#define E925002004_IC_NAME_VARCHAR 1
	/* module name */
	#define E925002004_MODULE_NAME_VARCHAR 2
	/* description */
	#define E925002004_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E925002004_COUNT_INT 4

	/* Event 925002005
		send cmd52 invald data */
	/* error level */
	#define E925002005_ERROR_LEVEL_INT 0
	/* IC name */
	#define E925002005_IC_NAME_VARCHAR 1
	/* module name */
	#define E925002005_MODULE_NAME_VARCHAR 2
	/* description */
	#define E925002005_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E925002005_COUNT_INT 4

	/* Event 925002006
		cmd52 r5 error */
	/* error level */
	#define E925002006_ERROR_LEVEL_INT 0
	/* IC name */
	#define E925002006_IC_NAME_VARCHAR 1
	/* module name */
	#define E925002006_MODULE_NAME_VARCHAR 2
	/* description */
	#define E925002006_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E925002006_COUNT_INT 4

	/* Event 925002007
		cmd52 r5 function data error */
	/* error level */
	#define E925002007_ERROR_LEVEL_INT 0
	/* IC name */
	#define E925002007_IC_NAME_VARCHAR 1
	/* module name */
	#define E925002007_MODULE_NAME_VARCHAR 2
	/* description */
	#define E925002007_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E925002007_COUNT_INT 4

	/* Event 925002008
		cmd52 out of range error */
	/* error level */
	#define E925002008_ERROR_LEVEL_INT 0
	/* IC name */
	#define E925002008_IC_NAME_VARCHAR 1
	/* module name */
	#define E925002008_MODULE_NAME_VARCHAR 2
	/* description */
	#define E925002008_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E925002008_COUNT_INT 4

	/* Event 925002009
		cmd52 read/wirte fail */
	/* error level */
	#define E925002009_ERROR_LEVEL_INT 0
	/* IC name */
	#define E925002009_IC_NAME_VARCHAR 1
	/* module name */
	#define E925002009_MODULE_NAME_VARCHAR 2
	/* description */
	#define E925002009_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E925002009_COUNT_INT 4

	/* Event 925002010
		cmd53 invald data */
	/* error level */
	#define E925002010_ERROR_LEVEL_INT 0
	/* IC name */
	#define E925002010_IC_NAME_VARCHAR 1
	/* module name */
	#define E925002010_MODULE_NAME_VARCHAR 2
	/* description */
	#define E925002010_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E925002010_COUNT_INT 4

	/* Event 925002011
		cmd53 malloc fail */
	/* error level */
	#define E925002011_ERROR_LEVEL_INT 0
	/* IC name */
	#define E925002011_IC_NAME_VARCHAR 1
	/* module name */
	#define E925002011_MODULE_NAME_VARCHAR 2
	/* description */
	#define E925002011_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E925002011_COUNT_INT 4

	/* Event 925002012
		cmd53 read/write fail */
	/* error level */
	#define E925002012_ERROR_LEVEL_INT 0
	/* IC name */
	#define E925002012_IC_NAME_VARCHAR 1
	/* module name */
	#define E925002012_MODULE_NAME_VARCHAR 2
	/* description */
	#define E925002012_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E925002012_COUNT_INT 4

	/* Event 925002013
		cmd53 read/write data fail */
	/* error level */
	#define E925002013_ERROR_LEVEL_INT 0
	/* IC name */
	#define E925002013_IC_NAME_VARCHAR 1
	/* module name */
	#define E925002013_MODULE_NAME_VARCHAR 2
	/* description */
	#define E925002013_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E925002013_COUNT_INT 4

	/* Event 925002014
		cmd52 r5 fail */
	/* error level */
	#define E925002014_ERROR_LEVEL_INT 0
	/* IC name */
	#define E925002014_IC_NAME_VARCHAR 1
	/* module name */
	#define E925002014_MODULE_NAME_VARCHAR 2
	/* description */
	#define E925002014_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E925002014_COUNT_INT 4

	/* Event 925002015
		cmd52 r5 function data error */
	/* error level */
	#define E925002015_ERROR_LEVEL_INT 0
	/* IC name */
	#define E925002015_IC_NAME_VARCHAR 1
	/* module name */
	#define E925002015_MODULE_NAME_VARCHAR 2
	/* description */
	#define E925002015_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E925002015_COUNT_INT 4

	/* Event 925002016
		cmd52 out of range error */
	/* error level */
	#define E925002016_ERROR_LEVEL_INT 0
	/* IC name */
	#define E925002016_IC_NAME_VARCHAR 1
	/* module name */
	#define E925002016_MODULE_NAME_VARCHAR 2
	/* description */
	#define E925002016_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E925002016_COUNT_INT 4

	/* Event 925002017
		sdio unkown error */
	/* error level */
	#define E925002017_ERROR_LEVEL_INT 0
	/* IC name */
	#define E925002017_IC_NAME_VARCHAR 1
	/* module name */
	#define E925002017_MODULE_NAME_VARCHAR 2
	/* description */
	#define E925002017_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E925002017_COUNT_INT 4

	/* Event 925002018
		sdio read/write error */
	/* error level */
	#define E925002018_ERROR_LEVEL_INT 0
	/* IC name */
	#define E925002018_IC_NAME_VARCHAR 1
	/* module name */
	#define E925002018_MODULE_NAME_VARCHAR 2
	/* description */
	#define E925002018_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E925002018_COUNT_INT 4

	/* Event 926001000
		FPGA load fail */
	/* error level */
	#define E926001000_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926001000_IC_NAME_VARCHAR 1
	/* module name */
	#define E926001000_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926001000_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926001000_COUNT_INT 4

	/* Event 926001001
		voltage abnormally */
	/* error level */
	#define E926001001_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926001001_IC_NAME_VARCHAR 1
	/* module name */
	#define E926001001_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926001001_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926001001_COUNT_INT 4

	/* Event 926001002
		clock abnormally */
	/* error level */
	#define E926001002_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926001002_IC_NAME_VARCHAR 1
	/* module name */
	#define E926001002_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926001002_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926001002_COUNT_INT 4

	/* Event 926001003
		check crc abnormally */
	/* error level */
	#define E926001003_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926001003_IC_NAME_VARCHAR 1
	/* module name */
	#define E926001003_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926001003_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926001003_COUNT_INT 4

	/* Event 926001004
		SPI read and write abnormally */
	/* error level */
	#define E926001004_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926001004_IC_NAME_VARCHAR 1
	/* module name */
	#define E926001004_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926001004_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926001004_COUNT_INT 4

	/* Event 926001005
		traverse truth table abnormally */
	/* error level */
	#define E926001005_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926001005_IC_NAME_VARCHAR 1
	/* module name */
	#define E926001005_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926001005_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926001005_COUNT_INT 4

	/* Event 926002000
		Hall error */
	/* error level */
	#define E926002000_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926002000_IC_NAME_VARCHAR 1
	/* module name */
	#define E926002000_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926002000_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926002000_COUNT_INT 4

	/* Event 926002001
		DSM_HS_IRQ_TIMES_ERR */
	/* error level */
	#define E926002001_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926002001_IC_NAME_VARCHAR 1
	/* module name */
	#define E926002001_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926002001_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926002001_COUNT_INT 4

	/* Event 926002002
		DSM_HS_IRQ_TIMES_ERR */
	/* error level */
	#define E926002002_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926002002_IC_NAME_VARCHAR 1
	/* module name */
	#define E926002002_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926002002_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926002002_COUNT_INT 4

	/* Event 926003000
		touch the power key by mistake */
	/* error level */
	#define E926003000_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926003000_IC_NAME_VARCHAR 1
	/* module name */
	#define E926003000_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926003000_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926003000_COUNT_INT 4

	/* Event 926003001
		touch the volume key by mistake */
	/* error level */
	#define E926003001_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926003001_IC_NAME_VARCHAR 1
	/* module name */
	#define E926003001_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926003001_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926003001_COUNT_INT 4

	/* Event 926003002
		long pres power key */
	/* error level */
	#define E926003002_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926003002_IC_NAME_VARCHAR 1
	/* module name */
	#define E926003002_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926003002_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926003002_COUNT_INT 4

	/* Event 926003003
		DSM_VOL_KEY_PRESS_TIMES_ERR */
	/* error level */
	#define E926003003_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926003003_IC_NAME_VARCHAR 1
	/* module name */
	#define E926003003_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926003003_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926003003_COUNT_INT 4

	/* Event 926003004
		DSM_VOL_KEY_PRESS_INTERVAL_ERR */
	/* error level */
	#define E926003004_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926003004_IC_NAME_VARCHAR 1
	/* module name */
	#define E926003004_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926003004_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926003004_COUNT_INT 4

	/* Event 926003005
		DSM_POWER_KEY_PRESS_TIMES_ERR */
	/* error level */
	#define E926003005_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926003005_IC_NAME_VARCHAR 1
	/* module name */
	#define E926003005_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926003005_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926003005_COUNT_INT 4

	/* Event 926003006
		DSM_POWER_KEY_PRESS_INTERVAL_ERR */
	/* error level */
	#define E926003006_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926003006_IC_NAME_VARCHAR 1
	/* module name */
	#define E926003006_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926003006_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926003006_COUNT_INT 4

	/* Event 926004000
		i2c error */
	/* error level */
	#define E926004000_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926004000_IC_NAME_VARCHAR 1
	/* module name */
	#define E926004000_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926004000_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926004000_COUNT_INT 4

	/* Event 926004001
		FW update error */
	/* error level */
	#define E926004001_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926004001_IC_NAME_VARCHAR 1
	/* module name */
	#define E926004001_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926004001_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926004001_COUNT_INT 4

	/* Event 926004002
		TP rawdata error */
	/* error level */
	#define E926004002_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926004002_IC_NAME_VARCHAR 1
	/* module name */
	#define E926004002_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926004002_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926004002_COUNT_INT 4

	/* Event 926004003
		TP CRC error */
	/* error level */
	#define E926004003_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926004003_IC_NAME_VARCHAR 1
	/* module name */
	#define E926004003_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926004003_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926004003_COUNT_INT 4

	/* Event 926004004
		TP device status error */
	/* error level */
	#define E926004004_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926004004_IC_NAME_VARCHAR 1
	/* module name */
	#define E926004004_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926004004_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926004004_COUNT_INT 4

	/* Event 926004005
		TP freeze */
	/* error level */
	#define E926004005_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926004005_IC_NAME_VARCHAR 1
	/* module name */
	#define E926004005_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926004005_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926004005_COUNT_INT 4

	/* Event 926004006
		TP change report error */
	/* error level */
	#define E926004006_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926004006_IC_NAME_VARCHAR 1
	/* module name */
	#define E926004006_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926004006_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926004006_COUNT_INT 4

	/* Event 926004007
		TP in glove mode */
	/* error level */
	#define E926004007_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926004007_IC_NAME_VARCHAR 1
	/* module name */
	#define E926004007_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926004007_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926004007_COUNT_INT 4

	/* Event 926004008
		TP moisture count info */
	/* error level */
	#define E926004008_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926004008_IC_NAME_VARCHAR 1
	/* module name */
	#define E926004008_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926004008_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926004008_COUNT_INT 4

	/* Event 926004009
		TP very noise count info */
	/* error level */
	#define E926004009_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926004009_IC_NAME_VARCHAR 1
	/* module name */
	#define E926004009_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926004009_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926004009_COUNT_INT 4

	/* Event 926004010
		TP calibration crc error */
	/* error level */
	#define E926004010_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926004010_IC_NAME_VARCHAR 1
	/* module name */
	#define E926004010_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926004010_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926004010_COUNT_INT 4

	/* Event 926004011
		TP fw crash error no */
	/* error level */
	#define E926004011_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926004011_IC_NAME_VARCHAR 1
	/* module name */
	#define E926004011_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926004011_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926004011_COUNT_INT 4

	/* Event 926004012
		TP bus error */
	/* error level */
	#define E926004012_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926004012_IC_NAME_VARCHAR 1
	/* module name */
	#define E926004012_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926004012_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926004012_COUNT_INT 4

	/* Event 926004013
		TP FW error */
	/* error level */
	#define E926004013_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926004013_IC_NAME_VARCHAR 1
	/* module name */
	#define E926004013_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926004013_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926004013_COUNT_INT 4

	/* Event 926004014
		TP cap error */
	/* error level */
	#define E926004014_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926004014_IC_NAME_VARCHAR 1
	/* module name */
	#define E926004014_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926004014_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926004014_COUNT_INT 4

	/* Event 926004015
		TP esd error */
	/* error level */
	#define E926004015_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926004015_IC_NAME_VARCHAR 1
	/* module name */
	#define E926004015_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926004015_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926004015_COUNT_INT 4

	/* Event 926004016
		TP F34 error */
	/* error level */
	#define E926004016_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926004016_IC_NAME_VARCHAR 1
	/* module name */
	#define E926004016_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926004016_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926004016_COUNT_INT 4

	/* Event 926004017
		TP F54 error */
	/* error level */
	#define E926004017_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926004017_IC_NAME_VARCHAR 1
	/* module name */
	#define E926004017_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926004017_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926004017_COUNT_INT 4

	/* Event 926004018
		TP PDT PROPS error */
	/* error level */
	#define E926004018_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926004018_IC_NAME_VARCHAR 1
	/* module name */
	#define E926004018_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926004018_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926004018_COUNT_INT 4

	/* Event 926004019
		TP F34 read queries error */
	/* error level */
	#define E926004019_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926004019_IC_NAME_VARCHAR 1
	/* module name */
	#define E926004019_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926004019_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926004019_COUNT_INT 4

	/* Event 926004020
		TP wakeup error */
	/* error level */
	#define E926004020_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926004020_IC_NAME_VARCHAR 1
	/* module name */
	#define E926004020_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926004020_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926004020_COUNT_INT 4

	/* Event 926004021
		TP hid timeout info */
	/* error level */
	#define E926004021_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926004021_IC_NAME_VARCHAR 1
	/* module name */
	#define E926004021_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926004021_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926004021_COUNT_INT 4

	/* Event 926004022
		TP startup failed info */
	/* error level */
	#define E926004022_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926004022_IC_NAME_VARCHAR 1
	/* module name */
	#define E926004022_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926004022_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926004022_COUNT_INT 4

	/* Event 926004023
		Get lcd panel name failed info */
	/* error level */
	#define E926004023_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926004023_IC_NAME_VARCHAR 1
	/* module name */
	#define E926004023_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926004023_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926004023_COUNT_INT 4

	/* Event 926004024
		TP noise record number info */
	/* error level */
	#define E926004024_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926004024_IC_NAME_VARCHAR 1
	/* module name */
	#define E926004024_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926004024_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926004024_COUNT_INT 4

	/* Event 926005000
		DTS config error */
	/* error level */
	#define E926005000_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926005000_IC_NAME_VARCHAR 1
	/* module name */
	#define E926005000_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926005000_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926005000_COUNT_INT 4

	/* Event 926005001
		Sensorhub invalid command */
	/* error level */
	#define E926005001_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926005001_IC_NAME_VARCHAR 1
	/* module name */
	#define E926005001_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926005001_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926005001_COUNT_INT 4

	/* Event 926005002
		Sensorhub invalid download */
	/* error level */
	#define E926005002_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926005002_IC_NAME_VARCHAR 1
	/* module name */
	#define E926005002_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926005002_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926005002_COUNT_INT 4

	/* Event 926005003
		Sensorhub Application processor I2C error */
	/* error level */
	#define E926005003_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926005003_IC_NAME_VARCHAR 1
	/* module name */
	#define E926005003_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926005003_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926005003_COUNT_INT 4

	/* Event 926005004
		Sensorhub IPC timeout */
	/* error level */
	#define E926005004_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926005004_IC_NAME_VARCHAR 1
	/* module name */
	#define E926005004_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926005004_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926005004_COUNT_INT 4

	/* Event 926005005
		Sensorhub Application error not defined */
	/* error level */
	#define E926005005_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926005005_IC_NAME_VARCHAR 1
	/* module name */
	#define E926005005_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926005005_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926005005_COUNT_INT 4

	/* Event 926005006
		Sensorhub write data to inputhub error */
	/* error level */
	#define E926005006_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926005006_IC_NAME_VARCHAR 1
	/* module name */
	#define E926005006_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926005006_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926005006_COUNT_INT 4

	/* Event 926005007
		inputhub step counter error */
	/* error level */
	#define E926005007_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926005007_IC_NAME_VARCHAR 1
	/* module name */
	#define E926005007_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926005007_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926005007_COUNT_INT 4

	/* Event 926005008
		Sensorhub watchdog timeout */
	/* error level */
	#define E926005008_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926005008_IC_NAME_VARCHAR 1
	/* module name */
	#define E926005008_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926005008_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926005008_COUNT_INT 4

	/* Event 926005009
		inputhub write data to sensorhub error */
	/* error level */
	#define E926005009_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926005009_IC_NAME_VARCHAR 1
	/* module name */
	#define E926005009_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926005009_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926005009_COUNT_INT 4

	/* Event 926006000
		Accelerometer sensor error */
	/* error level */
	#define E926006000_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926006000_IC_NAME_VARCHAR 1
	/* module name */
	#define E926006000_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926006000_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926006000_COUNT_INT 4

	/* Event 926006001
		airpress sensor error */
	/* error level */
	#define E926006001_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926006001_IC_NAME_VARCHAR 1
	/* module name */
	#define E926006001_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926006001_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926006001_COUNT_INT 4

	/* Event 926006002
		Light sensor error */
	/* error level */
	#define E926006002_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926006002_IC_NAME_VARCHAR 1
	/* module name */
	#define E926006002_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926006002_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926006002_COUNT_INT 4

	/* Event 926006003
		Fusion error */
	/* error level */
	#define E926006003_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926006003_IC_NAME_VARCHAR 1
	/* module name */
	#define E926006003_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926006003_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926006003_COUNT_INT 4

	/* Event 926006004
		Gyroscope sensor error */
	/* error level */
	#define E926006004_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926006004_IC_NAME_VARCHAR 1
	/* module name */
	#define E926006004_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926006004_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926006004_COUNT_INT 4

	/* Event 926006005
		Sensorhub I2C error */
	/* error level */
	#define E926006005_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926006005_IC_NAME_VARCHAR 1
	/* module name */
	#define E926006005_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926006005_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926006005_COUNT_INT 4

	/* Event 926006006
		LABC sensor error */
	/* error level */
	#define E926006006_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926006006_IC_NAME_VARCHAR 1
	/* module name */
	#define E926006006_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926006006_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926006006_COUNT_INT 4

	/* Event 926006007
		Light sensor software error */
	/* error level */
	#define E926006007_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926006007_IC_NAME_VARCHAR 1
	/* module name */
	#define E926006007_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926006007_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926006007_COUNT_INT 4

	/* Event 926006008
		Magnetic sensor error */
	/* error level */
	#define E926006008_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926006008_IC_NAME_VARCHAR 1
	/* module name */
	#define E926006008_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926006008_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926006008_COUNT_INT 4

	/* Event 926006009
		Motion sensor error */
	/* error level */
	#define E926006009_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926006009_IC_NAME_VARCHAR 1
	/* module name */
	#define E926006009_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926006009_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926006009_COUNT_INT 4

	/* Event 926006010
		Sensorhub MCU undefined error */
	/* error level */
	#define E926006010_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926006010_IC_NAME_VARCHAR 1
	/* module name */
	#define E926006010_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926006010_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926006010_COUNT_INT 4

	/* Event 926006011
		PDR error */
	/* error level */
	#define E926006011_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926006011_IC_NAME_VARCHAR 1
	/* module name */
	#define E926006011_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926006011_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926006011_COUNT_INT 4

	/* Event 926006012
		Pedometer sensor error */
	/* error level */
	#define E926006012_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926006012_IC_NAME_VARCHAR 1
	/* module name */
	#define E926006012_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926006012_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926006012_COUNT_INT 4

	/* Event 926006013
		Proximity sensor error */
	/* error level */
	#define E926006013_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926006013_IC_NAME_VARCHAR 1
	/* module name */
	#define E926006013_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926006013_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926006013_COUNT_INT 4

	/* Event 926006100
		Sensorhub init error */
	/* error level */
	#define E926006100_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926006100_IC_NAME_VARCHAR 1
	/* module name */
	#define E926006100_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926006100_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926006100_COUNT_INT 4

	/* Event 926006101
		Sensorhub server init error */
	/* error level */
	#define E926006101_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926006101_IC_NAME_VARCHAR 1
	/* module name */
	#define E926006101_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926006101_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926006101_COUNT_INT 4

	/* Event 926006102
		Sensorhub timer timeout */
	/* error level */
	#define E926006102_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926006102_IC_NAME_VARCHAR 1
	/* module name */
	#define E926006102_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926006102_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926006102_COUNT_INT 4

	/* Event 926006103
		Accelerometer peroid error */
	/* error level */
	#define E926006103_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926006103_IC_NAME_VARCHAR 1
	/* module name */
	#define E926006103_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926006103_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926006103_COUNT_INT 4

	/* Event 926006104
		CA sensor error */
	/* error level */
	#define E926006104_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926006104_IC_NAME_VARCHAR 1
	/* module name */
	#define E926006104_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926006104_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926006104_COUNT_INT 4

	/* Event 926007000
		Gsensor i2c error */
	/* error level */
	#define E926007000_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926007000_IC_NAME_VARCHAR 1
	/* module name */
	#define E926007000_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926007000_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926007000_COUNT_INT 4

	/* Event 926007001
		Gsensor data abnormal */
	/* error level */
	#define E926007001_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926007001_IC_NAME_VARCHAR 1
	/* module name */
	#define E926007001_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926007001_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926007001_COUNT_INT 4

	/* Event 926007002
		Gsensor data all zero */
	/* error level */
	#define E926007002_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926007002_IC_NAME_VARCHAR 1
	/* module name */
	#define E926007002_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926007002_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926007002_COUNT_INT 4

	/* Event 926007003
		Gsensor data not update */
	/* error level */
	#define E926007003_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926007003_IC_NAME_VARCHAR 1
	/* module name */
	#define E926007003_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926007003_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926007003_COUNT_INT 4

	/* Event 926007004
		Light sensor i2c error */
	/* error level */
	#define E926007004_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926007004_IC_NAME_VARCHAR 1
	/* module name */
	#define E926007004_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926007004_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926007004_COUNT_INT 4

	/* Event 926007005
		Light sensor irq error */
	/* error level */
	#define E926007005_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926007005_IC_NAME_VARCHAR 1
	/* module name */
	#define E926007005_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926007005_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926007005_COUNT_INT 4

	/* Event 926007006
		Light sensor threshold error */
	/* error level */
	#define E926007006_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926007006_IC_NAME_VARCHAR 1
	/* module name */
	#define E926007006_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926007006_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926007006_COUNT_INT 4

	/* Event 926007007
		Light sensor no irq */
	/* error level */
	#define E926007007_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926007007_IC_NAME_VARCHAR 1
	/* module name */
	#define E926007007_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926007007_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926007007_COUNT_INT 4

	/* Event 926007008
		Light sensor enable error */
	/* error level */
	#define E926007008_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926007008_IC_NAME_VARCHAR 1
	/* module name */
	#define E926007008_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926007008_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926007008_COUNT_INT 4

	/* Event 926007009
		Light sensor threshold out of range */
	/* error level */
	#define E926007009_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926007009_IC_NAME_VARCHAR 1
	/* module name */
	#define E926007009_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926007009_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926007009_COUNT_INT 4

	/* Event 926007010
		Light sensor power error */
	/* error level */
	#define E926007010_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926007010_IC_NAME_VARCHAR 1
	/* module name */
	#define E926007010_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926007010_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926007010_COUNT_INT 4

	/* Event 926007011
		Magnetic sensor I2C read write error */
	/* error level */
	#define E926007011_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926007011_IC_NAME_VARCHAR 1
	/* module name */
	#define E926007011_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926007011_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926007011_COUNT_INT 4

	/* Event 926007012
		Magnetic data abnormal */
	/* error level */
	#define E926007012_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926007012_IC_NAME_VARCHAR 1
	/* module name */
	#define E926007012_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926007012_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926007012_COUNT_INT 4

	/* Event 926007013
		Magnetic data not update */
	/* error level */
	#define E926007013_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926007013_IC_NAME_VARCHAR 1
	/* module name */
	#define E926007013_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926007013_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926007013_COUNT_INT 4

	/* Event 926007014
		Mangetic selftest error */
	/* error level */
	#define E926007014_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926007014_IC_NAME_VARCHAR 1
	/* module name */
	#define E926007014_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926007014_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926007014_COUNT_INT 4

	/* Event 926007015
		Sensorservice exit error */
	/* error level */
	#define E926007015_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926007015_IC_NAME_VARCHAR 1
	/* module name */
	#define E926007015_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926007015_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926007015_COUNT_INT 4

	/* Event 926007016
		Sensorservice data update error */
	/* error level */
	#define E926007016_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926007016_IC_NAME_VARCHAR 1
	/* module name */
	#define E926007016_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926007016_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926007016_COUNT_INT 4

	/* Event 926008000
		AP-CP communication abnormity */
	/* error level */
	#define E926008000_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926008000_IC_NAME_VARCHAR 1
	/* module name */
	#define E926008000_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926008000_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926008000_COUNT_INT 4

	/* Event 926008001
		read Modem state abnormity */
	/* error level */
	#define E926008001_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926008001_IC_NAME_VARCHAR 1
	/* module name */
	#define E926008001_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926008001_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926008001_COUNT_INT 4

	/* Event 926008002
		modem power up abnormity */
	/* error level */
	#define E926008002_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926008002_IC_NAME_VARCHAR 1
	/* module name */
	#define E926008002_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926008002_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926008002_COUNT_INT 4

	/* Event 926008003
		open AT file node fail */
	/* error level */
	#define E926008003_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926008003_IC_NAME_VARCHAR 1
	/* module name */
	#define E926008003_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926008003_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926008003_COUNT_INT 4

	/* Event 926008004
		read file node fail */
	/* error level */
	#define E926008004_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926008004_IC_NAME_VARCHAR 1
	/* module name */
	#define E926008004_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926008004_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926008004_COUNT_INT 4

	/* Event 926008005
		can not recive VPUP */
	/* error level */
	#define E926008005_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926008005_IC_NAME_VARCHAR 1
	/* module name */
	#define E926008005_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926008005_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926008005_COUNT_INT 4

	/* Event 926008006
		faild to gain systen time */
	/* error level */
	#define E926008006_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926008006_IC_NAME_VARCHAR 1
	/* module name */
	#define E926008006_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926008006_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926008006_COUNT_INT 4

	/* Event 926008007
		prepare asci device fail */
	/* error level */
	#define E926008007_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926008007_IC_NAME_VARCHAR 1
	/* module name */
	#define E926008007_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926008007_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926008007_COUNT_INT 4

	/* Event 926008008
		handshake with asci boot fail */
	/* error level */
	#define E926008008_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926008008_IC_NAME_VARCHAR 1
	/* module name */
	#define E926008008_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926008008_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926008008_COUNT_INT 4

	/* Event 926008009
		cbp bootloader abnormity */
	/* error level */
	#define E926008009_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926008009_IC_NAME_VARCHAR 1
	/* module name */
	#define E926008009_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926008009_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926008009_COUNT_INT 4

	/* Event 926008010
		File deletion abnormity */
	/* error level */
	#define E926008010_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926008010_IC_NAME_VARCHAR 1
	/* module name */
	#define E926008010_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926008010_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926008010_COUNT_INT 4

	/* Event 926008011
		faild to open fail */
	/* error level */
	#define E926008011_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926008011_IC_NAME_VARCHAR 1
	/* module name */
	#define E926008011_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926008011_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926008011_COUNT_INT 4

	/* Event 926008012
		faild to read fail */
	/* error level */
	#define E926008012_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926008012_IC_NAME_VARCHAR 1
	/* module name */
	#define E926008012_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926008012_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926008012_COUNT_INT 4

	/* Event 926008013
		faild to write fail */
	/* error level */
	#define E926008013_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926008013_IC_NAME_VARCHAR 1
	/* module name */
	#define E926008013_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926008013_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926008013_COUNT_INT 4

	/* Event 926008014
		open fsm table fail */
	/* error level */
	#define E926008014_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926008014_IC_NAME_VARCHAR 1
	/* module name */
	#define E926008014_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926008014_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926008014_COUNT_INT 4

	/* Event 926008015
		cbp image download err */
	/* error level */
	#define E926008015_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926008015_IC_NAME_VARCHAR 1
	/* module name */
	#define E926008015_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926008015_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926008015_COUNT_INT 4

	/* Event 926008016
		upload image err */
	/* error level */
	#define E926008016_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926008016_IC_NAME_VARCHAR 1
	/* module name */
	#define E926008016_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926008016_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926008016_COUNT_INT 4

	/* Event 926008017
		erase image err */
	/* error level */
	#define E926008017_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926008017_IC_NAME_VARCHAR 1
	/* module name */
	#define E926008017_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926008017_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926008017_COUNT_INT 4

	/* Event 926008018
		Fsm calibration error */
	/* error level */
	#define E926008018_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926008018_IC_NAME_VARCHAR 1
	/* module name */
	#define E926008018_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926008018_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926008018_COUNT_INT 4

	/* Event 926008019
		serial number can not match */
	/* error level */
	#define E926008019_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926008019_IC_NAME_VARCHAR 1
	/* module name */
	#define E926008019_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926008019_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926008019_COUNT_INT 4

	/* Event 926008020
		checksum fail */
	/* error level */
	#define E926008020_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926008020_IC_NAME_VARCHAR 1
	/* module name */
	#define E926008020_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926008020_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926008020_COUNT_INT 4

	/* Event 926009000
		ACK write timeout */
	/* error level */
	#define E926009000_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926009000_IC_NAME_VARCHAR 1
	/* module name */
	#define E926009000_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926009000_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926009000_COUNT_INT 4

	/* Event 926009001
		ACK read timeout */
	/* error level */
	#define E926009001_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926009001_IC_NAME_VARCHAR 1
	/* module name */
	#define E926009001_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926009001_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926009001_COUNT_INT 4

	/* Event 926009002
		80packet timeout */
	/* error level */
	#define E926009002_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926009002_IC_NAME_VARCHAR 1
	/* module name */
	#define E926009002_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926009002_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926009002_COUNT_INT 4

	/* Event 926009003
		sync abnormally */
	/* error level */
	#define E926009003_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926009003_IC_NAME_VARCHAR 1
	/* module name */
	#define E926009003_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926009003_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926009003_COUNT_INT 4

	/* Event 926009004
		SPI locked(down_timeout) */
	/* error level */
	#define E926009004_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926009004_IC_NAME_VARCHAR 1
	/* module name */
	#define E926009004_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926009004_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926009004_COUNT_INT 4

	/* Event 926009005
		port inception inception */
	/* error level */
	#define E926009005_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926009005_IC_NAME_VARCHAR 1
	/* module name */
	#define E926009005_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926009005_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926009005_COUNT_INT 4

	/* Event 926009006
		RNIC sent packet abnormally */
	/* error level */
	#define E926009006_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926009006_IC_NAME_VARCHAR 1
	/* module name */
	#define E926009006_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926009006_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926009006_COUNT_INT 4

	/* Event 926009007
		date packet block */
	/* error level */
	#define E926009007_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926009007_IC_NAME_VARCHAR 1
	/* module name */
	#define E926009007_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926009007_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926009007_COUNT_INT 4

	/* Event 926009008
		CBP ready fail */
	/* error level */
	#define E926009008_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926009008_IC_NAME_VARCHAR 1
	/* module name */
	#define E926009008_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926009008_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926009008_COUNT_INT 4

	/* Event 926009009
		kzalloc kernel space fail */
	/* error level */
	#define E926009009_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926009009_IC_NAME_VARCHAR 1
	/* module name */
	#define E926009009_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926009009_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926009009_COUNT_INT 4

	/* Event 926009010
		dev_alloc_skb allocated space fail */
	/* error level */
	#define E926009010_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926009010_IC_NAME_VARCHAR 1
	/* module name */
	#define E926009010_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926009010_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926009010_COUNT_INT 4

	/* Event 926009011
		donload image fail */
	/* error level */
	#define E926009011_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926009011_IC_NAME_VARCHAR 1
	/* module name */
	#define E926009011_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926009011_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926009011_COUNT_INT 4

	/* Event 926009012
		call spi_sync interfa fail */
	/* error level */
	#define E926009012_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926009012_IC_NAME_VARCHAR 1
	/* module name */
	#define E926009012_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926009012_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926009012_COUNT_INT 4

	/* Event 926009013
		call Modem SDIO ACK timeout */
	/* error level */
	#define E926009013_ERROR_LEVEL_INT 0
	/* IC name */
	#define E926009013_IC_NAME_VARCHAR 1
	/* module name */
	#define E926009013_MODULE_NAME_VARCHAR 2
	/* description */
	#define E926009013_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E926009013_COUNT_INT 4

	/* Event 927001000
		csi mipi0 error */
	/* error level */
	#define E927001000_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927001000_IC_NAME_VARCHAR 1
	/* module name */
	#define E927001000_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927001000_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927001000_COUNT_INT 4

	/* Event 927001001
		csi mipi1 error */
	/* error level */
	#define E927001001_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927001001_IC_NAME_VARCHAR 1
	/* module name */
	#define E927001001_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927001001_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927001001_COUNT_INT 4

	/* Event 927002000
		Flash i2c transfer fail */
	/* error level */
	#define E927002000_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927002000_IC_NAME_VARCHAR 1
	/* module name */
	#define E927002000_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927002000_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927002000_COUNT_INT 4

	/* Event 927002001
		LED short circuit or open circuit */
	/* error level */
	#define E927002001_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927002001_IC_NAME_VARCHAR 1
	/* module name */
	#define E927002001_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927002001_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927002001_COUNT_INT 4

	/* Event 927002002
		LED over-Temperature */
	/* error level */
	#define E927002002_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927002002_IC_NAME_VARCHAR 1
	/* module name */
	#define E927002002_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927002002_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927002002_COUNT_INT 4

	/* Event 927003000
		Camera server crash */
	/* error level */
	#define E927003000_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927003000_IC_NAME_VARCHAR 1
	/* module name */
	#define E927003000_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927003000_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927003000_COUNT_INT 4

	/* Event 927003001
		Camera buffer stuck */
	/* error level */
	#define E927003001_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927003001_IC_NAME_VARCHAR 1
	/* module name */
	#define E927003001_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927003001_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927003001_COUNT_INT 4

	/* Event 927003002
		Camera meta stuck */
	/* error level */
	#define E927003002_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927003002_IC_NAME_VARCHAR 1
	/* module name */
	#define E927003002_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927003002_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927003002_COUNT_INT 4

	/* Event 927003003
		Camera buffer stream off fail */
	/* error level */
	#define E927003003_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927003003_IC_NAME_VARCHAR 1
	/* module name */
	#define E927003003_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927003003_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927003003_COUNT_INT 4

	/* Event 927003004
		Camera meta stream off fail */
	/* error level */
	#define E927003004_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927003004_IC_NAME_VARCHAR 1
	/* module name */
	#define E927003004_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927003004_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927003004_COUNT_INT 4

	/* Event 927003005
		Camera encoder open fail */
	/* error level */
	#define E927003005_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927003005_IC_NAME_VARCHAR 1
	/* module name */
	#define E927003005_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927003005_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927003005_COUNT_INT 4

	/* Event 927003006
		Camera encoder process fail */
	/* error level */
	#define E927003006_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927003006_IC_NAME_VARCHAR 1
	/* module name */
	#define E927003006_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927003006_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927003006_COUNT_INT 4

	/* Event 927003007
		Camera encoder close fail */
	/* error level */
	#define E927003007_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927003007_IC_NAME_VARCHAR 1
	/* module name */
	#define E927003007_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927003007_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927003007_COUNT_INT 4

	/* Event 927003008
		Send rpmsg to HISP error */
	/* error level */
	#define E927003008_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927003008_IC_NAME_VARCHAR 1
	/* module name */
	#define E927003008_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927003008_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927003008_COUNT_INT 4

	/* Event 927003009
		Camera MatchId Error */
	/* error level */
	#define E927003009_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927003009_IC_NAME_VARCHAR 1
	/* module name */
	#define E927003009_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927003009_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927003009_COUNT_INT 4

	/* Event 927003010
		Check Point Timeout */
	/* error level */
	#define E927003010_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927003010_IC_NAME_VARCHAR 1
	/* module name */
	#define E927003010_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927003010_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927003010_COUNT_INT 4

	/* Event 927003011
		process request timeout */
	/* error level */
	#define E927003011_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927003011_IC_NAME_VARCHAR 1
	/* module name */
	#define E927003011_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927003011_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927003011_COUNT_INT 4

	/* Event 927003012
		wait room timeout */
	/* error level */
	#define E927003012_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927003012_IC_NAME_VARCHAR 1
	/* module name */
	#define E927003012_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927003012_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927003012_COUNT_INT 4

	/* Event 927003013
		cp4msg timeout */
	/* error level */
	#define E927003013_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927003013_IC_NAME_VARCHAR 1
	/* module name */
	#define E927003013_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927003013_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927003013_COUNT_INT 4

	/* Event 927003014
		flush timeout */
	/* error level */
	#define E927003014_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927003014_IC_NAME_VARCHAR 1
	/* module name */
	#define E927003014_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927003014_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927003014_COUNT_INT 4

	/* Event 927003015
		start streaming timeout */
	/* error level */
	#define E927003015_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927003015_IC_NAME_VARCHAR 1
	/* module name */
	#define E927003015_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927003015_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927003015_COUNT_INT 4

	/* Event 927003016
		stop streaming timeout */
	/* error level */
	#define E927003016_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927003016_IC_NAME_VARCHAR 1
	/* module name */
	#define E927003016_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927003016_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927003016_COUNT_INT 4

	/* Event 927003017
		cp4merge buf timeout */
	/* error level */
	#define E927003017_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927003017_IC_NAME_VARCHAR 1
	/* module name */
	#define E927003017_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927003017_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927003017_COUNT_INT 4

	/* Event 927003019
		OTP checksum fail */
	/* error level */
	#define E927003019_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927003019_IC_NAME_VARCHAR 1
	/* module name */
	#define E927003019_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927003019_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927003019_COUNT_INT 4

	/* Event 927003020
		load camera so fail */
	/* error level */
	#define E927003020_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927003020_IC_NAME_VARCHAR 1
	/* module name */
	#define E927003020_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927003020_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927003020_COUNT_INT 4

	/* Event 927004000
		Camera meta stream off fail */
	/* error level */
	#define E927004000_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927004000_IC_NAME_VARCHAR 1
	/* module name */
	#define E927004000_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927004000_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927004000_COUNT_INT 4

	/* Event 927004001
		Camera encoder open fail */
	/* error level */
	#define E927004001_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927004001_IC_NAME_VARCHAR 1
	/* module name */
	#define E927004001_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927004001_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927004001_COUNT_INT 4

	/* Event 927004002
		Camera encoder process fail */
	/* error level */
	#define E927004002_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927004002_IC_NAME_VARCHAR 1
	/* module name */
	#define E927004002_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927004002_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927004002_COUNT_INT 4

	/* Event 927004003
		Camera encoder close fail */
	/* error level */
	#define E927004003_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927004003_IC_NAME_VARCHAR 1
	/* module name */
	#define E927004003_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927004003_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927004003_COUNT_INT 4

	/* Event 927004004
		VC data exception when capture */
	/* error level */
	#define E927004004_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927004004_IC_NAME_VARCHAR 1
	/* module name */
	#define E927004004_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927004004_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927004004_COUNT_INT 4

	/* Event 927004005
		OVISP sent command to CMD no respond */
	/* error level */
	#define E927004005_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927004005_IC_NAME_VARCHAR 1
	/* module name */
	#define E927004005_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927004005_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927004005_COUNT_INT 4

	/* Event 927004006
		OVISP failed to sent command to CMD */
	/* error level */
	#define E927004006_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927004006_IC_NAME_VARCHAR 1
	/* module name */
	#define E927004006_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927004006_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927004006_COUNT_INT 4

	/* Event 927004007
		OVISP receive wrong message from CMD */
	/* error level */
	#define E927004007_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927004007_IC_NAME_VARCHAR 1
	/* module name */
	#define E927004007_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927004007_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927004007_COUNT_INT 4

	/* Event 927005000
		IVP smmu abnormally */
	/* error level */
	#define E927005000_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927005000_IC_NAME_VARCHAR 1
	/* module name */
	#define E927005000_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927005000_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927005000_COUNT_INT 4

	/* Event 927005001
		IVP watchdog abnormally */
	/* error level */
	#define E927005001_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927005001_IC_NAME_VARCHAR 1
	/* module name */
	#define E927005001_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927005001_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927005001_COUNT_INT 4

	/* Event 927005002
		IVP dwaxi abnormally */
	/* error level */
	#define E927005002_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927005002_IC_NAME_VARCHAR 1
	/* module name */
	#define E927005002_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927005002_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927005002_COUNT_INT 4

	/* Event 927005003
		IVP Open fail */
	/* error level */
	#define E927005003_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927005003_IC_NAME_VARCHAR 1
	/* module name */
	#define E927005003_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927005003_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927005003_COUNT_INT 4

	/* Event 927005004
		IVP Message out of time */
	/* error level */
	#define E927005004_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927005004_IC_NAME_VARCHAR 1
	/* module name */
	#define E927005004_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927005004_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927005004_COUNT_INT 4

	/* Event 927005005
		IVP Core Panic */
	/* error level */
	#define E927005005_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927005005_IC_NAME_VARCHAR 1
	/* module name */
	#define E927005005_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927005005_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927005005_COUNT_INT 4

	/* Event 927006000
		HISP FW ALL ERROR */
	/* error level */
	#define E927006000_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927006000_IC_NAME_VARCHAR 1
	/* module name */
	#define E927006000_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927006000_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927006000_COUNT_INT 4

	/* Event 927006001
		HISP SENSOR ERROR */
	/* error level */
	#define E927006001_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927006001_IC_NAME_VARCHAR 1
	/* module name */
	#define E927006001_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927006001_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927006001_COUNT_INT 4

	/* Event 927006002
		HISP VCM ERROR */
	/* error level */
	#define E927006002_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927006002_IC_NAME_VARCHAR 1
	/* module name */
	#define E927006002_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927006002_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927006002_COUNT_INT 4

	/* Event 927006003
		HISP OIS ERROR */
	/* error level */
	#define E927006003_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927006003_IC_NAME_VARCHAR 1
	/* module name */
	#define E927006003_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927006003_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927006003_COUNT_INT 4

	/* Event 927006004
		HISP LASER ERROR */
	/* error level */
	#define E927006004_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927006004_IC_NAME_VARCHAR 1
	/* module name */
	#define E927006004_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927006004_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927006004_COUNT_INT 4

	/* Event 927007000
		MINIISP internal error */
	/* error level */
	#define E927007000_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927007000_IC_NAME_VARCHAR 1
	/* module name */
	#define E927007000_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927007000_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927007000_COUNT_INT 4

	/* Event 927007001
		extisp PQ error */
	/* error level */
	#define E927007001_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927007001_IC_NAME_VARCHAR 1
	/* module name */
	#define E927007001_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927007001_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927007001_COUNT_INT 4

	/* Event 927007002
		extisp I2C error */
	/* error level */
	#define E927007002_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927007002_IC_NAME_VARCHAR 1
	/* module name */
	#define E927007002_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927007002_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927007002_COUNT_INT 4

	/* Event 927007003
		extisp USPI error */
	/* error level */
	#define E927007003_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927007003_IC_NAME_VARCHAR 1
	/* module name */
	#define E927007003_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927007003_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927007003_COUNT_INT 4

	/* Event 927007004
		extisp VCM error */
	/* error level */
	#define E927007004_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927007004_IC_NAME_VARCHAR 1
	/* module name */
	#define E927007004_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927007004_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927007004_COUNT_INT 4

	/* Event 927007005
		extisp Interrupt error */
	/* error level */
	#define E927007005_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927007005_IC_NAME_VARCHAR 1
	/* module name */
	#define E927007005_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927007005_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927007005_COUNT_INT 4

	/* Event 927007006
		extisp CommonFunc error */
	/* error level */
	#define E927007006_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927007006_IC_NAME_VARCHAR 1
	/* module name */
	#define E927007006_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927007006_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927007006_COUNT_INT 4

	/* Event 927007007
		extisp A3 error */
	/* error level */
	#define E927007007_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927007007_IC_NAME_VARCHAR 1
	/* module name */
	#define E927007007_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927007007_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927007007_COUNT_INT 4

	/* Event 927007008
		extisp PIPE error */
	/* error level */
	#define E927007008_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927007008_IC_NAME_VARCHAR 1
	/* module name */
	#define E927007008_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927007008_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927007008_COUNT_INT 4

	/* Event 927007009
		extisp RDN error */
	/* error level */
	#define E927007009_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927007009_IC_NAME_VARCHAR 1
	/* module name */
	#define E927007009_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927007009_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927007009_COUNT_INT 4

	/* Event 927007010
		extisp TXLM error */
	/* error level */
	#define E927007010_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927007010_IC_NAME_VARCHAR 1
	/* module name */
	#define E927007010_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927007010_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927007010_COUNT_INT 4

	/* Event 927007011
		extisp MTX error */
	/* error level */
	#define E927007011_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927007011_IC_NAME_VARCHAR 1
	/* module name */
	#define E927007011_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927007011_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927007011_COUNT_INT 4

	/* Event 927007012
		extisp MRX error */
	/* error level */
	#define E927007012_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927007012_IC_NAME_VARCHAR 1
	/* module name */
	#define E927007012_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927007012_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927007012_COUNT_INT 4

	/* Event 927007013
		extisp FEC0 error */
	/* error level */
	#define E927007013_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927007013_IC_NAME_VARCHAR 1
	/* module name */
	#define E927007013_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927007013_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927007013_COUNT_INT 4

	/* Event 927007014
		extisp SENSOR error */
	/* error level */
	#define E927007014_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927007014_IC_NAME_VARCHAR 1
	/* module name */
	#define E927007014_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927007014_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927007014_COUNT_INT 4

	/* Event 927007015
		extisp FEC1 error */
	/* error level */
	#define E927007015_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927007015_IC_NAME_VARCHAR 1
	/* module name */
	#define E927007015_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927007015_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927007015_COUNT_INT 4

	/* Event 927007016
		extisp CAP error */
	/* error level */
	#define E927007016_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927007016_IC_NAME_VARCHAR 1
	/* module name */
	#define E927007016_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927007016_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927007016_COUNT_INT 4

	/* Event 927007017
		extisp internal other error */
	/* error level */
	#define E927007017_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927007017_IC_NAME_VARCHAR 1
	/* module name */
	#define E927007017_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927007017_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927007017_COUNT_INT 4

	/* Event 927008000
		HW TRACE ERROR */
	/* error level */
	#define E927008000_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927008000_IC_NAME_VARCHAR 1
	/* module name */
	#define E927008000_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927008000_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927008000_COUNT_INT 4

	/* Event 927009000
		DSM_CAMERA_SOF_ERR */
	/* error level */
	#define E927009000_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927009000_IC_NAME_VARCHAR 1
	/* module name */
	#define E927009000_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927009000_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927009000_COUNT_INT 4

	/* Event 927009001
		DSM_CAMERA_I2C_ERR */
	/* error level */
	#define E927009001_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927009001_IC_NAME_VARCHAR 1
	/* module name */
	#define E927009001_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927009001_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927009001_COUNT_INT 4

	/* Event 927009002
		DSM_CAMERA_CHIP_ID_NOT_MATCH */
	/* error level */
	#define E927009002_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927009002_IC_NAME_VARCHAR 1
	/* module name */
	#define E927009002_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927009002_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927009002_COUNT_INT 4

	/* Event 927009003
		DSM_CAMERA_OTP_ERR */
	/* error level */
	#define E927009003_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927009003_IC_NAME_VARCHAR 1
	/* module name */
	#define E927009003_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927009003_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927009003_COUNT_INT 4

	/* Event 927009004
		DSM_CAMERA_CPP_BUFF_ERR */
	/* error level */
	#define E927009004_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927009004_IC_NAME_VARCHAR 1
	/* module name */
	#define E927009004_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927009004_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927009004_COUNT_INT 4

	/* Event 927009005
		DSM_CAMERA_SENSOR_NO_FRAME */
	/* error level */
	#define E927009005_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927009005_IC_NAME_VARCHAR 1
	/* module name */
	#define E927009005_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927009005_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927009005_COUNT_INT 4

	/* Event 927009006
		DSM_CAMERA_LED_FLASH_CIRCUIT_ERR */
	/* error level */
	#define E927009006_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927009006_IC_NAME_VARCHAR 1
	/* module name */
	#define E927009006_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927009006_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927009006_COUNT_INT 4

	/* Event 927009007
		DSM_CAMERA_LED_FLASH_OVER_TEMPERATURE */
	/* error level */
	#define E927009007_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927009007_IC_NAME_VARCHAR 1
	/* module name */
	#define E927009007_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927009007_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927009007_COUNT_INT 4

	/* Event 927009008
		DSM_CAMERA_LED_FLASH_VOUT_ERROR */
	/* error level */
	#define E927009008_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927009008_IC_NAME_VARCHAR 1
	/* module name */
	#define E927009008_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927009008_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927009008_COUNT_INT 4

	/* Event 927009009
		CAMERA ISP AXI stream fail */
	/* error level */
	#define E927009009_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927009009_IC_NAME_VARCHAR 1
	/* module name */
	#define E927009009_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927009009_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927009009_COUNT_INT 4

	/* Event 927009010
		CAMERA post event timeout */
	/* error level */
	#define E927009010_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927009010_IC_NAME_VARCHAR 1
	/* module name */
	#define E927009010_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927009010_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927009010_COUNT_INT 4

	/* Event 927009011
		CAMERA actuator init fail */
	/* error level */
	#define E927009011_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927009011_IC_NAME_VARCHAR 1
	/* module name */
	#define E927009011_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927009011_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927009011_COUNT_INT 4

	/* Event 927009012
		CAMERA actuator set info err */
	/* error level */
	#define E927009012_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927009012_IC_NAME_VARCHAR 1
	/* module name */
	#define E927009012_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927009012_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927009012_COUNT_INT 4

	/* Event 927009013
		CAMERA actuator move fail */
	/* error level */
	#define E927009013_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927009013_IC_NAME_VARCHAR 1
	/* module name */
	#define E927009013_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927009013_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927009013_COUNT_INT 4

	/* Event 927009014
		CAMERA fd leak */
	/* error level */
	#define E927009014_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927009014_IC_NAME_VARCHAR 1
	/* module name */
	#define E927009014_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927009014_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927009014_COUNT_INT 4

	/* Event 927009015
		CAMERA sensor init session fail */
	/* error level */
	#define E927009015_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927009015_IC_NAME_VARCHAR 1
	/* module name */
	#define E927009015_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927009015_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927009015_COUNT_INT 4

	/* Event 927009016
		CAMERA session ID match fail */
	/* error level */
	#define E927009016_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927009016_IC_NAME_VARCHAR 1
	/* module name */
	#define E927009016_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927009016_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927009016_COUNT_INT 4

	/* Event 927009017
		CAMERA reprocess param error */
	/* error level */
	#define E927009017_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927009017_IC_NAME_VARCHAR 1
	/* module name */
	#define E927009017_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927009017_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927009017_COUNT_INT 4

	/* Event 927009018
		CAMERA mct_pipeline set fail */
	/* error level */
	#define E927009018_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927009018_IC_NAME_VARCHAR 1
	/* module name */
	#define E927009018_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927009018_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927009018_COUNT_INT 4

	/* Event 927009019
		CAMERA invalid poll fd */
	/* error level */
	#define E927009019_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927009019_IC_NAME_VARCHAR 1
	/* module name */
	#define E927009019_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927009019_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927009019_COUNT_INT 4

	/* Event 927009020
		CAMERA start channel no buf */
	/* error level */
	#define E927009020_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927009020_IC_NAME_VARCHAR 1
	/* module name */
	#define E927009020_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927009020_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927009020_COUNT_INT 4

	/* Event 927009021
		CAMERA buf manager no buf */
	/* error level */
	#define E927009021_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927009021_IC_NAME_VARCHAR 1
	/* module name */
	#define E927009021_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927009021_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927009021_COUNT_INT 4

	/* Event 927009022
		CAMERA ISP request hal buf fail */
	/* error level */
	#define E927009022_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927009022_IC_NAME_VARCHAR 1
	/* module name */
	#define E927009022_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927009022_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927009022_COUNT_INT 4

	/* Event 927009023
		CAMERA ISP request buf update fail */
	/* error level */
	#define E927009023_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927009023_IC_NAME_VARCHAR 1
	/* module name */
	#define E927009023_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927009023_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927009023_COUNT_INT 4

	/* Event 927009024
		CAMERA CPP input params error */
	/* error level */
	#define E927009024_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927009024_IC_NAME_VARCHAR 1
	/* module name */
	#define E927009024_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927009024_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927009024_COUNT_INT 4

	/* Event 927009025
		CAMERA CPP output params error */
	/* error level */
	#define E927009025_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927009025_IC_NAME_VARCHAR 1
	/* module name */
	#define E927009025_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927009025_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927009025_COUNT_INT 4

	/* Event 927009026
		CAMERA ISPIF port error */
	/* error level */
	#define E927009026_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927009026_IC_NAME_VARCHAR 1
	/* module name */
	#define E927009026_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927009026_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927009026_COUNT_INT 4

	/* Event 927009027
		CAMERA ISPIF module not found */
	/* error level */
	#define E927009027_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927009027_IC_NAME_VARCHAR 1
	/* module name */
	#define E927009027_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927009027_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927009027_COUNT_INT 4

	/* Event 927009028
		CAMERA ISPIF cfg error */
	/* error level */
	#define E927009028_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927009028_IC_NAME_VARCHAR 1
	/* module name */
	#define E927009028_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927009028_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927009028_COUNT_INT 4

	/* Event 927009029
		CAMERA focus not done */
	/* error level */
	#define E927009029_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927009029_IC_NAME_VARCHAR 1
	/* module name */
	#define E927009029_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927009029_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927009029_COUNT_INT 4

	/* Event 927009030
		CAMERA ois acc fail */
	/* error level */
	#define E927009030_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927009030_IC_NAME_VARCHAR 1
	/* module name */
	#define E927009030_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927009030_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927009030_COUNT_INT 4

	/* Event 927009031
		CAMERA ois check fail */
	/* error level */
	#define E927009031_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927009031_IC_NAME_VARCHAR 1
	/* module name */
	#define E927009031_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927009031_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927009031_COUNT_INT 4

	/* Event 927009032
		CAMERA ois init fail */
	/* error level */
	#define E927009032_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927009032_IC_NAME_VARCHAR 1
	/* module name */
	#define E927009032_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927009032_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927009032_COUNT_INT 4

	/* Event 927010000
		camera pmic i2c error */
	/* error level */
	#define E927010000_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927010000_IC_NAME_VARCHAR 1
	/* module name */
	#define E927010000_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927010000_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927010000_COUNT_INT 4

	/* Event 927010001
		camera pmic enable error */
	/* error level */
	#define E927010001_ERROR_LEVEL_INT 0
	/* IC name */
	#define E927010001_IC_NAME_VARCHAR 1
	/* module name */
	#define E927010001_MODULE_NAME_VARCHAR 2
	/* description */
	#define E927010001_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E927010001_COUNT_INT 4

	/* Event 928001000
		block **** is corrupted (**** is block number) */
	/* error level */
	#define E928001000_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928001000_IC_NAME_VARCHAR 1
	/* module name */
	#define E928001000_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928001000_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928001000_COUNT_INT 4

	/* Event 928001001
		block **** is corrupted (**** is block number) */
	/* error level */
	#define E928001001_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928001001_IC_NAME_VARCHAR 1
	/* module name */
	#define E928001001_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928001001_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928001001_COUNT_INT 4

	/* Event 928002001
		EMMC_TUNING_ERROR(tuning abnormally) */
	/* error level */
	#define E928002001_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928002001_IC_NAME_VARCHAR 1
	/* module name */
	#define E928002001_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928002001_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928002001_COUNT_INT 4

	/* Event 928002002
		EMMC_READ_ERROR(read abnormally) */
	/* error level */
	#define E928002002_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928002002_IC_NAME_VARCHAR 1
	/* module name */
	#define E928002002_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928002002_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928002002_COUNT_INT 4

	/* Event 928002003
		EMMC_WRITE_ERROR(write abnormally) */
	/* error level */
	#define E928002003_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928002003_IC_NAME_VARCHAR 1
	/* module name */
	#define E928002003_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928002003_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928002003_COUNT_INT 4

	/* Event 928002004
		EMMC_PRE_EOL_INFO_ERROR(check nand Bad Bloc abnormally) */
	/* error level */
	#define E928002004_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928002004_IC_NAME_VARCHAR 1
	/* module name */
	#define E928002004_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928002004_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928002004_COUNT_INT 4

	/* Event 928002005
		EMMC_DEVICE_LIFE_TIME_EST_ERROR(check Equipment life
		abnormally) */
	/* error level */
	#define E928002005_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928002005_IC_NAME_VARCHAR 1
	/* module name */
	#define E928002005_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928002005_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928002005_COUNT_INT 4

	/* Event 928002006
		DSM_SYSTEM_W_ERR(write SYSTEM readonly partitioned
		abnormally) */
	/* error level */
	#define E928002006_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928002006_IC_NAME_VARCHAR 1
	/* module name */
	#define E928002006_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928002006_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928002006_COUNT_INT 4

	/* Event 928002007
		DSM_EMMC_ERASE_ERR(erase command abnormally) */
	/* error level */
	#define E928002007_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928002007_IC_NAME_VARCHAR 1
	/* module name */
	#define E928002007_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928002007_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928002007_COUNT_INT 4

	/* Event 928002008
		DSM_EMMC_VDET_ERR(check low voltage error) */
	/* error level */
	#define E928002008_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928002008_IC_NAME_VARCHAR 1
	/* module name */
	#define E928002008_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928002008_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928002008_COUNT_INT 4

	/* Event 928002009
		DSM_EMMC_SEND_CXD_ERR(get CSD or CID error) */
	/* error level */
	#define E928002009_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928002009_IC_NAME_VARCHAR 1
	/* module name */
	#define E928002009_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928002009_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928002009_COUNT_INT 4

	/* Event 928002010
		DSM_EMMC_SET_BUS_WIDTH_ERR(set SD bus widths error) */
	/* error level */
	#define E928002010_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928002010_IC_NAME_VARCHAR 1
	/* module name */
	#define E928002010_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928002010_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928002010_COUNT_INT 4

	/* Event 928002011
		DSM_EMMC_RSP_ERR(R1 RESPONSE respond error state) */
	/* error level */
	#define E928002011_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928002011_IC_NAME_VARCHAR 1
	/* module name */
	#define E928002011_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928002011_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928002011_COUNT_INT 4

	/* Event 928002012
		DSM_EMMC_HOST_ERR(HOST interupt in wrong state) */
	/* error level */
	#define E928002012_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928002012_IC_NAME_VARCHAR 1
	/* module name */
	#define E928002012_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928002012_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928002012_COUNT_INT 4

	/* Event 928002013
		DSM_EMMC_URGENT_BKOPS(BKOPS start) */
	/* error level */
	#define E928002013_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928002013_IC_NAME_VARCHAR 1
	/* module name */
	#define E928002013_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928002013_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928002013_COUNT_INT 4

	/* Event 928002014
		DSM_EMMC_DYNCAP_NEEDED(dynamic capacity) */
	/* error level */
	#define E928002014_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928002014_IC_NAME_VARCHAR 1
	/* module name */
	#define E928002014_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928002014_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928002014_COUNT_INT 4

	/* Event 928002015
		DSM_EMMC_PACKED_FAILURE(tar command execute error) */
	/* error level */
	#define E928002015_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928002015_IC_NAME_VARCHAR 1
	/* module name */
	#define E928002015_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928002015_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928002015_COUNT_INT 4

	/* Event 928002016
		emmc HOST rw timeout error */
	/* error level */
	#define E928002016_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928002016_IC_NAME_VARCHAR 1
	/* module name */
	#define E928002016_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928002016_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928002016_COUNT_INT 4

	/* Event 928002017
		emmc system resources pool exhausted */
	/* error level */
	#define E928002017_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928002017_IC_NAME_VARCHAR 1
	/* module name */
	#define E928002017_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928002017_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928002017_COUNT_INT 4

	/* Event 928002018
		emmc cache flush timeout */
	/* error level */
	#define E928002018_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928002018_IC_NAME_VARCHAR 1
	/* module name */
	#define E928002018_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928002018_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928002018_COUNT_INT 4

	/* Event 928002019
		emmc cache flush error */
	/* error level */
	#define E928002019_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928002019_IC_NAME_VARCHAR 1
	/* module name */
	#define E928002019_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928002019_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928002019_COUNT_INT 4

	/* Event 928002020
		EMMC_INIT_ERROR(init abnormally) */
	/* error level */
	#define E928002020_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928002020_IC_NAME_VARCHAR 1
	/* module name */
	#define E928002020_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928002020_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928002020_COUNT_INT 4

	/* Event 928002021
		EMMC_DATA0_BUSY_ERROR(DATA0 not release abnormally) */
	/* error level */
	#define E928002021_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928002021_IC_NAME_VARCHAR 1
	/* module name */
	#define E928002021_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928002021_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928002021_COUNT_INT 4

	/* Event 928002022
		EMMC_THROUGHPUT_MONITOR_ERROR(data of throughput abnormally) */
	/* error level */
	#define E928002022_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928002022_IC_NAME_VARCHAR 1
	/* module name */
	#define E928002022_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928002022_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928002022_COUNT_INT 4

	/* Event 928002023
		DSM_STORAGE_EXT4_ERROR_NO(ext4 abnormally) */
	/* error level */
	#define E928002023_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928002023_IC_NAME_VARCHAR 1
	/* module name */
	#define E928002023_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928002023_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928002023_COUNT_INT 4

	/* Event 928002024
		DSM_EMMC_RW_TIMEOUT_ERR(read write command timeout) */
	/* error level */
	#define E928002024_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928002024_IC_NAME_VARCHAR 1
	/* module name */
	#define E928002024_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928002024_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928002024_COUNT_INT 4

	/* Event 928002025
		DSM_EMMC_SYSPOOL_EXHAUSTED(data tag exhaust system
		resource) */
	/* error level */
	#define E928002025_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928002025_IC_NAME_VARCHAR 1
	/* module name */
	#define E928002025_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928002025_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928002025_COUNT_INT 4

	/* Event 928003000
		general error */
	/* error level */
	#define E928003000_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928003000_IC_NAME_VARCHAR 1
	/* module name */
	#define E928003000_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928003000_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928003000_COUNT_INT 4

	/* Event 928003001
		inode error */
	/* error level */
	#define E928003001_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928003001_IC_NAME_VARCHAR 1
	/* module name */
	#define E928003001_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928003001_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928003001_COUNT_INT 4

	/* Event 928003002
		fail error */
	/* error level */
	#define E928003002_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928003002_IC_NAME_VARCHAR 1
	/* module name */
	#define E928003002_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928003002_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928003002_COUNT_INT 4

	/* Event 928003003
		read superblock error */
	/* error level */
	#define E928003003_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928003003_IC_NAME_VARCHAR 1
	/* module name */
	#define E928003003_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928003003_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928003003_COUNT_INT 4

	/* Event 928003004
		read and backup superblock error */
	/* error level */
	#define E928003004_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928003004_IC_NAME_VARCHAR 1
	/* module name */
	#define E928003004_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928003004_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928003004_COUNT_INT 4

	/* Event 928003005
		write superblock error */
	/* error level */
	#define E928003005_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928003005_IC_NAME_VARCHAR 1
	/* module name */
	#define E928003005_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928003005_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928003005_COUNT_INT 4

	/* Event 928003006
		repair message */
	/* error level */
	#define E928003006_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928003006_IC_NAME_VARCHAR 1
	/* module name */
	#define E928003006_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928003006_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928003006_COUNT_INT 4

	/* Event 928004000
		EXT4 file system arranged and report */
	/* error level */
	#define E928004000_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928004000_IC_NAME_VARCHAR 1
	/* module name */
	#define E928004000_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928004000_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928004000_COUNT_INT 4

	/* Event 928005000
		F2FS general error */
	/* error level */
	#define E928005000_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928005000_IC_NAME_VARCHAR 1
	/* module name */
	#define E928005000_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928005000_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928005000_COUNT_INT 4

	/* Event 928005001
		F2FS superblock error */
	/* error level */
	#define E928005001_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928005001_IC_NAME_VARCHAR 1
	/* module name */
	#define E928005001_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928005001_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928005001_COUNT_INT 4

	/* Event 928005002
		F2FS BUGCHK error */
	/* error level */
	#define E928005002_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928005002_IC_NAME_VARCHAR 1
	/* module name */
	#define E928005002_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928005002_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928005002_COUNT_INT 4

	/* Event 928006000
		report Sd card CMD2 gain CID fail,wrong respons status */
	/* error level */
	#define E928006000_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928006000_IC_NAME_VARCHAR 1
	/* module name */
	#define E928006000_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928006000_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928006000_COUNT_INT 4

	/* Event 928006001
		report Sd card CMD3 gain card adress fail,wrong respons
		status */
	/* error level */
	#define E928006001_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928006001_IC_NAME_VARCHAR 1
	/* module name */
	#define E928006001_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928006001_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928006001_COUNT_INT 4

	/* Event 928006002
		report Sd card CMD6 SWITCH command fail,command error
		or data error */
	/* error level */
	#define E928006002_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928006002_IC_NAME_VARCHAR 1
	/* module name */
	#define E928006002_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928006002_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928006002_COUNT_INT 4

	/* Event 928006003
		report SD card CMD7 gain wrong respons status */
	/* error level */
	#define E928006003_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928006003_IC_NAME_VARCHAR 1
	/* module name */
	#define E928006003_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928006003_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928006003_COUNT_INT 4

	/* Event 928006004
		report SD card CMD8 gain wrong respons status */
	/* error level */
	#define E928006004_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928006004_IC_NAME_VARCHAR 1
	/* module name */
	#define E928006004_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928006004_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928006004_COUNT_INT 4

	/* Event 928006005
		report SD card CMD9gain wrong value from CSD */
	/* error level */
	#define E928006005_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928006005_IC_NAME_VARCHAR 1
	/* module name */
	#define E928006005_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928006005_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928006005_COUNT_INT 4

	/* Event 928006006
		report SD card CMD55 APP initialization command fail,wrong
		response state */
	/* error level */
	#define E928006006_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928006006_IC_NAME_VARCHAR 1
	/* module name */
	#define E928006006_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928006006_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928006006_COUNT_INT 4

	/* Event 928006007
		report SD card CMD41 initialization command fail,wrong
		response state */
	/* error level */
	#define E928006007_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928006007_IC_NAME_VARCHAR 1
	/* module name */
	#define E928006007_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928006007_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928006007_COUNT_INT 4

	/* Event 928006008
		report SD card block device initialization fail */
	/* error level */
	#define E928006008_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928006008_IC_NAME_VARCHAR 1
	/* module name */
	#define E928006008_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928006008_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928006008_COUNT_INT 4

	/* Event 928006009
		DSM_SDCARD_BLK_WR_SPEED_ERR(sdcard write read speed
		unnormal) */
	/* error level */
	#define E928006009_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928006009_IC_NAME_VARCHAR 1
	/* module name */
	#define E928006009_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928006009_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928006009_COUNT_INT 4

	/* Event 928006010
		DSM_SDCARD_BLK_RW_CHECK_ERR(sdcard write read check
		error) */
	/* error level */
	#define E928006010_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928006010_IC_NAME_VARCHAR 1
	/* module name */
	#define E928006010_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928006010_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928006010_COUNT_INT 4

	/* Event 928006011
		DSM_SDCARD_RO_ERR(sdcard CSD readonly register error) */
	/* error level */
	#define E928006011_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928006011_IC_NAME_VARCHAR 1
	/* module name */
	#define E928006011_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928006011_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928006011_COUNT_INT 4

	/* Event 928006012
		report [FAT/EXFAT] Filesystem has been set read-only */
	/* error level */
	#define E928006012_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928006012_IC_NAME_VARCHAR 1
	/* module name */
	#define E928006012_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928006012_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928006012_COUNT_INT 4

	/* Event 928006013
		DSM_SDCARD_LOWSPEED_SPEC_ERR(sdcard low speed spec
		error) */
	/* error level */
	#define E928006013_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928006013_IC_NAME_VARCHAR 1
	/* module name */
	#define E928006013_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928006013_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928006013_COUNT_INT 4

	/* Event 928006014
		DSM_SDCARD_NO_UEVENT_REPORT(sdcard no event error) */
	/* error level */
	#define E928006014_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928006014_IC_NAME_VARCHAR 1
	/* module name */
	#define E928006014_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928006014_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928006014_COUNT_INT 4

	/* Event 928006015
		SDCARD get CID register error */
	/* error level */
	#define E928006015_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928006015_IC_NAME_VARCHAR 1
	/* module name */
	#define E928006015_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928006015_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928006015_COUNT_INT 4

	/* Event 928006016
		SDCARD get RCA address error */
	/* error level */
	#define E928006016_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928006016_IC_NAME_VARCHAR 1
	/* module name */
	#define E928006016_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928006016_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928006016_COUNT_INT 4

	/* Event 928006017
		Select the card error, not for data transmission */
	/* error level */
	#define E928006017_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928006017_IC_NAME_VARCHAR 1
	/* module name */
	#define E928006017_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928006017_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928006017_COUNT_INT 4

	/* Event 928006018
		CMD8 response error */
	/* error level */
	#define E928006018_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928006018_IC_NAME_VARCHAR 1
	/* module name */
	#define E928006018_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928006018_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928006018_COUNT_INT 4

	/* Event 928006019
		command error */
	/* error level */
	#define E928006019_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928006019_IC_NAME_VARCHAR 1
	/* module name */
	#define E928006019_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928006019_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928006019_COUNT_INT 4

	/* Event 928006020
		command error */
	/* error level */
	#define E928006020_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928006020_IC_NAME_VARCHAR 1
	/* module name */
	#define E928006020_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928006020_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928006020_COUNT_INT 4

	/* Event 928006021
		get CID reg error */
	/* error level */
	#define E928006021_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928006021_IC_NAME_VARCHAR 1
	/* module name */
	#define E928006021_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928006021_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928006021_COUNT_INT 4

	/* Event 928006022
		add disk error */
	/* error level */
	#define E928006022_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928006022_IC_NAME_VARCHAR 1
	/* module name */
	#define E928006022_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928006022_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928006022_COUNT_INT 4

	/* Event 928006023
		interrupt time out error */
	/* error level */
	#define E928006023_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928006023_IC_NAME_VARCHAR 1
	/* module name */
	#define E928006023_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928006023_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928006023_COUNT_INT 4

	/* Event 928006024
		block abort err */
	/* error level */
	#define E928006024_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928006024_IC_NAME_VARCHAR 1
	/* module name */
	#define E928006024_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928006024_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928006024_COUNT_INT 4

	/* Event 928007000
		Volume is idle but appears to be mounted - fixing */
	/* error level */
	#define E928007000_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928007000_IC_NAME_VARCHAR 1
	/* module name */
	#define E928007000_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928007000_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928007000_COUNT_INT 4

	/* Event 928007001
		Failed to get device nodes */
	/* error level */
	#define E928007001_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928007001_IC_NAME_VARCHAR 1
	/* module name */
	#define E928007001_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928007001_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928007001_COUNT_INT 4

	/* Event 928007002
		Error making device node */
	/* error level */
	#define E928007002_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928007002_IC_NAME_VARCHAR 1
	/* module name */
	#define E928007002_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928007002_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928007002_COUNT_INT 4

	/* Event 928007003
		NULL(reserved for sdcard vold hisi) */
	/* error level */
	#define E928007003_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928007003_IC_NAME_VARCHAR 1
	/* module name */
	#define E928007003_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928007003_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928007003_COUNT_INT 4

	/* Event 928007004
		Filesystem check failed (unknown exit code) fat.cpp */
	/* error level */
	#define E928007004_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928007004_IC_NAME_VARCHAR 1
	/* module name */
	#define E928007004_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928007004_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928007004_COUNT_INT 4

	/* Event 928007005
		NULL(reserved for sdcard vold hisi) */
	/* error level */
	#define E928007005_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928007005_IC_NAME_VARCHAR 1
	/* module name */
	#define E928007005_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928007005_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928007005_COUNT_INT 4

	/* Event 928007006
		fs_prepare_dir failed */
	/* error level */
	#define E928007006_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928007006_IC_NAME_VARCHAR 1
	/* module name */
	#define E928007006_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928007006_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928007006_COUNT_INT 4

	/* Event 928007007
		Failed to bind mount points */
	/* error level */
	#define E928007007_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928007007_IC_NAME_VARCHAR 1
	/* module name */
	#define E928007007_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928007007_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928007007_COUNT_INT 4

	/* Event 928007008
		failed to mount via VFAT */
	/* error level */
	#define E928007008_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928007008_IC_NAME_VARCHAR 1
	/* module name */
	#define E928007008_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928007008_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928007008_COUNT_INT 4

	/* Event 928007009
		appears to be a read only filesystem - retrying mount
		RO fat.cpp */
	/* error level */
	#define E928007009_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928007009_IC_NAME_VARCHAR 1
	/* module name */
	#define E928007009_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928007009_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928007009_COUNT_INT 4

	/* Event 928007010
		Failed to unmount */
	/* error level */
	#define E928007010_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928007010_IC_NAME_VARCHAR 1
	/* module name */
	#define E928007010_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928007010_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928007010_COUNT_INT 4

	/* Event 928007011
		Failed to unmount secure area */
	/* error level */
	#define E928007011_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928007011_IC_NAME_VARCHAR 1
	/* module name */
	#define E928007011_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928007011_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928007011_COUNT_INT 4

	/* Event 928007012
		Giving up on unmount */
	/* error level */
	#define E928007012_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928007012_IC_NAME_VARCHAR 1
	/* module name */
	#define E928007012_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928007012_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928007012_COUNT_INT 4

	/* Event 928007013
		Failed to apply disk configuration */
	/* error level */
	#define E928007013_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928007013_IC_NAME_VARCHAR 1
	/* module name */
	#define E928007013_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928007013_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928007013_COUNT_INT 4

	/* Event 928007014
		NULL(reserved for sdcard vold hisi) */
	/* error level */
	#define E928007014_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928007014_IC_NAME_VARCHAR 1
	/* module name */
	#define E928007014_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928007014_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928007014_COUNT_INT 4

	/* Event 928007015
		Failed to format */
	/* error level */
	#define E928007015_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928007015_IC_NAME_VARCHAR 1
	/* module name */
	#define E928007015_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928007015_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928007015_COUNT_INT 4

	/* Event 928007016
		EMMC FSTRIM */
	/* error level */
	#define E928007016_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928007016_IC_NAME_VARCHAR 1
	/* module name */
	#define E928007016_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928007016_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928007016_COUNT_INT 4

	/* Event 928008000
		UFS_FASTBOOT_PWMODE_CHANGE_ERROR */
	/* error level */
	#define E928008000_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928008000_IC_NAME_VARCHAR 1
	/* module name */
	#define E928008000_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928008000_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928008000_COUNT_INT 4

	/* Event 928008001
		UFS_FASTBOOT_RW_ERR */
	/* error level */
	#define E928008001_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928008001_IC_NAME_VARCHAR 1
	/* module name */
	#define E928008001_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928008001_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928008001_COUNT_INT 4

	/* Event 928008002
		UFS_SYSBUS_ERROR */
	/* error level */
	#define E928008002_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928008002_IC_NAME_VARCHAR 1
	/* module name */
	#define E928008002_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928008002_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928008002_COUNT_INT 4

	/* Event 928008003
		UFS_UIC_TRANSFER_ERROR */
	/* error level */
	#define E928008003_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928008003_IC_NAME_VARCHAR 1
	/* module name */
	#define E928008003_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928008003_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928008003_COUNT_INT 4

	/* Event 928008004
		UFS_UIC_CMD_ERROR */
	/* error level */
	#define E928008004_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928008004_IC_NAME_VARCHAR 1
	/* module name */
	#define E928008004_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928008004_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928008004_COUNT_INT 4

	/* Event 928008005
		UFS_CONTROLLER_ERROR */
	/* error level */
	#define E928008005_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928008005_IC_NAME_VARCHAR 1
	/* module name */
	#define E928008005_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928008005_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928008005_COUNT_INT 4

	/* Event 928008006
		UFS_DEVICE_ERROR */
	/* error level */
	#define E928008006_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928008006_IC_NAME_VARCHAR 1
	/* module name */
	#define E928008006_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928008006_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928008006_COUNT_INT 4

	/* Event 928008007
		UFS_TIMEOUT_ERR */
	/* error level */
	#define E928008007_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928008007_IC_NAME_VARCHAR 1
	/* module name */
	#define E928008007_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928008007_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928008007_COUNT_INT 4

	/* Event 928008008
		UFS_UTP_TRANS_ERR */
	/* error level */
	#define E928008008_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928008008_IC_NAME_VARCHAR 1
	/* module name */
	#define E928008008_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928008008_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928008008_COUNT_INT 4

	/* Event 928008009
		UFS_SCSI_CMD_ERR */
	/* error level */
	#define E928008009_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928008009_IC_NAME_VARCHAR 1
	/* module name */
	#define E928008009_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928008009_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928008009_COUNT_INT 4

	/* Event 928009000
		fsck.f2fs check disk's error */
	/* error level */
	#define E928009000_ERROR_LEVEL_INT 0
	/* IC name */
	#define E928009000_IC_NAME_VARCHAR 1
	/* module name */
	#define E928009000_MODULE_NAME_VARCHAR 2
	/* description */
	#define E928009000_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E928009000_COUNT_INT 4

/*** Application events' keys ***/

	/* Event 907000002
		sms service block */
	/* error type */
	#define E907000002_ERRORTYPE_INT 0
	/* reason of block */
	#define E907000002_REASON_VARCHAR 1
	/* supplements info */
	#define E907000002_SUPPLEMENTINFO_VARCHAR 2

	/* Event 907000003
		sms send failed */
	/* error type */
	#define E907000003_ERRORTYPE_INT 0
	/* ID of SIM */
	#define E907000003_SUBID_INT 1
	/* Reason of Failed */
	#define E907000003_REASON_VARCHAR 2
	/* supplements info */
	#define E907000003_SUPPLEMENTINFO_VARCHAR 3

	/* Event 907000004
		sms receive failed */
	/* error type */
	#define E907000004_ERRORTYPE_INT 0
	/* ID of SIM */
	#define E907000004_SUBID_INT 1
	/* Reason of Failed */
	#define E907000004_REASON_VARCHAR 2
	/* supplements info */
	#define E907000004_SUPPLEMENTINFO_VARCHAR 3

	/* Event 907000011
		mms send error */
	/* error type */
	#define E907000011_ERRORTYPE_INT 0
	/* ID of SIM */
	#define E907000011_SUBID_INT 1
	/* reason of error */
	#define E907000011_REASON_VARCHAR 2
	/* supplements info */
	#define E907000011_SUPPLEMENTINFO_VARCHAR 3

	/* Event 907000012
		mms receive error */
	/* error type */
	#define E907000012_ERRORTYPE_INT 0
	/* ID of SIM */
	#define E907000012_SUBID_INT 1
	/* reason of error */
	#define E907000012_REASON_VARCHAR 2
	/* supplements info */
	#define E907000012_SUPPLEMENTINFO_VARCHAR 3

	/* Event 907000014
		mms display error */
	/* error type */
	#define E907000014_ERRORTYPE_INT 0
	/* ID of SIM */
	#define E907000014_SUBID_INT 1
	/* Reason of Failed */
	#define E907000014_REASON_VARCHAR 2
	/* info of interface */
	#define E907000014_INTERFACE_VARCHAR 3
	/* supplements info */
	#define E907000014_SUPPLEMENTINFO_VARCHAR 4

	/* Event 907000015
		sms db error */
	/* error type */
	#define E907000015_ERRORTYPE_INT 0
	/* ID of SIM */
	#define E907000015_SUBID_INT 1
	/* reason of error */
	#define E907000015_REASON_VARCHAR 2
	/* operation type */
	#define E907000015_OPERATION_TYPE_VARCHAR 3
	/* supplements info */
	#define E907000015_SUPPLEMENTINFO_VARCHAR 4

	/* Event 907000016
		mms settings error */
	/* error type */
	#define E907000016_ERRORTYPE_INT 0
	/* ID of SIM */
	#define E907000016_SUBID_INT 1
	/* Reason of Failed */
	#define E907000016_REASON_VARCHAR 2
	/* supplements info */
	#define E907000016_SUPPLEMENTINFO_VARCHAR 3

	/* Event 907000018
		encrypt message error */
	/* error type */
	#define E907000018_ERRORTYPE_INT 0
	/* ID of SIM */
	#define E907000018_SUBID_INT 1
	/* reason of error */
	#define E907000018_REASON_VARCHAR 2
	/* supplements info */
	#define E907000018_SUPPLEMENTINFO_VARCHAR 3

	/* Event 907000019
		mms smart message error */
	/* error type */
	#define E907000019_ERRORTYPE_INT 0
	/* ID of SIM */
	#define E907000019_SUBID_INT 1
	/* reason of error */
	#define E907000019_REASON_VARCHAR 2
	/* supplements info */
	#define E907000019_SUPPLEMENTINFO_VARCHAR 3

	/* Event 907000020
		RCS message error */
	/* error type */
	#define E907000020_ERRORTYPE_INT 0
	/* ID of SIM */
	#define E907000020_SUBID_INT 1
	/* reason of error */
	#define E907000020_REASON_VARCHAR 2
	/* supplements info */
	#define E907000020_SUPPLEMENTINFO_VARCHAR 3

	/* Event 907000021
		APN activity failed */
	/* error type */
	#define E907000021_ERRORTYPE_INT 0
	/* ID of SIM */
	#define E907000021_SUBID_INT 1
	/* Reason of Failed */
	#define E907000021_REASON_VARCHAR 2
	/* supplements info */
	#define E907000021_SUPPLEMENTINFO_VARCHAR 3

	/* Event 907000022
		mms establishes the link failed */
	/* error type */
	#define E907000022_ERRORTYPE_INT 0
	/* ID of SIM */
	#define E907000022_SUBID_INT 1
	/* reason of error */
	#define E907000022_REASON_VARCHAR 2
	/* supplements info */
	#define E907000022_SUPPLEMENTINFO_VARCHAR 3

	/* Event 907000023
		mms display error */
	/* error type */
	#define E907000023_ERRORTYPE_INT 0
	/* ID of SIM */
	#define E907000023_SUBID_INT 1
	/* reason of error */
	#define E907000023_REASON_VARCHAR 2
	/* info of interface */
	#define E907000023_INTERFACE_VARCHAR 3
	/* supplements info */
	#define E907000023_SUPPLEMENTINFO_VARCHAR 4

	/* Event 907000024
		message loss error */
	/* error type */
	#define E907000024_ERRORTYPE_INT 0
	/* ID of SIM */
	#define E907000024_SUBID_INT 1
	/* reason of error */
	#define E907000024_REASON_VARCHAR 2
	/* supplements info */
	#define E907000024_SUPPLEMENTINFO_VARCHAR 3

	/* Event 907003001
		Answer call timeout */
	/* Bug description */
	#define E907003001_DESCRIPTION_VARCHAR 0
	/* answer used time */
	#define E907003001_USED_TIME_VARCHAR 1

	/* Event 907003002
		No ring for incoming call */
	/* Bug description */
	#define E907003002_DESCRIPTION_VARCHAR 0
	/* ring URI */
	#define E907003002_PATH_VARCHAR 1
	/* reason */
	#define E907003002_REASON_VARCHAR 2

	/* Event 907003003
		No incoming call ui */
	/* Bug description */
	#define E907003003_DESCRIPTION_VARCHAR 0
	/* top Activity */
	#define E907003003_TOP_ACTIVITY_VARCHAR 1

	/* Event 907003004
		Screen no on for a incoming call */
	/* Bug description */
	#define E907003004_DESCRIPTION_VARCHAR 0

	/* Event 907003005
		Hang up fail */
	/* Bug description */
	#define E907003005_DESCRIPTION_VARCHAR 0

	/* Event 907003006
		Get iccid fail */
	/* Bug description */
	#define E907003006_DESCRIPTION_VARCHAR 0
	/* error type */
	#define E907003006_ERROR_TYPE_VARCHAR 1

	/* Event 907003007
		Call-ui no remove after disconnected */
	/* Bug description */
	#define E907003007_DESCRIPTION_VARCHAR 0
	/* hangup type */
	#define E907003007_HANGUP_TYPE_VARCHAR 1
	/* activity state */
	#define E907003007_ACTIVITY_STATE_VARCHAR 2

	/* Event 907003008
		Cover-ui no remove */
	/* Bug description */
	#define E907003008_DESCRIPTION_VARCHAR 0

	/* Event 907003009
		Vibrate no stop */
	/* Bug description */
	#define E907003009_DESCRIPTION_VARCHAR 0

	/* Event 907003010
		Motion start fail */
	/* Bug description */
	#define E907003010_DESCRIPTION_VARCHAR 0

	/* Event 907003011
		Motion recognition fail */
	/* Bug description */
	#define E907003011_DESCRIPTION_VARCHAR 0

	/* Event 907003012
		Call recorder fail */
	/* Bug description */
	#define E907003012_DESCRIPTION_VARCHAR 0
	/* reason */
	#define E907003012_REASON_VARCHAR 1

	/* Event 907003013
		Call recorder no stop */
	/* Bug description */
	#define E907003013_DESCRIPTION_VARCHAR 0

	/* Event 907003014
		dial automaticly */
	/* Bug description */
	#define E907003014_DESCRIPTION_VARCHAR 0
	/* call app */
	#define E907003014_CALL_APP_VARCHAR 1

	/* Event 907003015
		Dial phones into multi-party calls */
	/* Bug description */
	#define E907003015_DESCRIPTION_VARCHAR 0
	/* call number */
	#define E907003015_CALL_NUMBER_VARCHAR 1
	/* call state */
	#define E907003015_CALL_STATE_VARCHAR 2

	/* Event 907006001
		Save contacts failed */
	/* Exception description */
	#define E907006001_EXCEPTIONDESCRIPTION_VARCHAR 0
	/* Lastest 10 times operation in cotntacts */
	#define E907006001_REPROCEDURE_VARCHAR 1

	/* Event 907006002
		Delete contacts failed */
	/* Exception description */
	#define E907006002_EXCEPTIONDESCRIPTION_VARCHAR 0
	/* Lastest 10 times operation in cotntacts */
	#define E907006002_REPROCEDURE_VARCHAR 1

	/* Event 907006003
		Save SIM contacts failed */
	/* Exception description */
	#define E907006003_EXCEPTIONDESCRIPTION_VARCHAR 0
	/* Lastest 10 times operation in cotntacts */
	#define E907006003_REPROCEDURE_VARCHAR 1

	/* Event 907006004
		Delete SIM contacts failed */
	/* Exception description */
	#define E907006004_EXCEPTIONDESCRIPTION_VARCHAR 0
	/* Lastest 10 times operation in cotntacts */
	#define E907006004_REPROCEDURE_VARCHAR 1

	/* Event 907006005
		SIM card contacts' quantity not correct, not displayed
		or can not saved */
	/* ExceptionScenes description */
	#define E907006005_EXCEPTIONSCENES_VARCHAR 0
	/* Lastest 10 times operation in cotntacts */
	#define E907006005_REPROCEDURE_VARCHAR 1

	/* Event 907006006
		SIM card contacts loaded time */
	/* Real used time */
	#define E907006006_SPENTTIME_VARCHAR 0
	/* Lastest 10 times operation in cotntacts */
	#define E907006006_REPROCEDURE_VARCHAR 1

	/* Event 907006007
		Search contacts failed */
	/* Error DataListFilter Type */
	#define E907006007_FILTETYPE_VARCHAR 0
	/* Lastest 10 times operation in cotntacts */
	#define E907006007_REPROCEDURE_VARCHAR 1

	/* Event 907006008
		monitor who set the cursor null */
	/* The called method name */
	#define E907006008_METHODNAME_VARCHAR 0
	/* Lastest 10 times operation in cotntacts */
	#define E907006008_REPROCEDURE_VARCHAR 1

	/* Event 907006009
		Contacts account isn't display */
	/* The 3rd APPS packages name */
	#define E907006009_RESPACKAGENAME_VARCHAR 0
	/* Lastest 10 times operation in cotntacts */
	#define E907006009_REPROCEDURE_VARCHAR 1

	/* Event 907006010
		Name card recognized failed */
	/* Exception description */
	#define E907006010_EXCEPTIONDESCRIPTION_VARCHAR 0
	/* Lastest 10 times operation in cotntacts */
	#define E907006010_REPROCEDURE_VARCHAR 1

	/* Event 907006011
		name card recognized failed */
	/* Exception description */
	#define E907006011_EXCEPTIONDESCRIPTION_VARCHAR 0
	/* Lastest 10 times operation in cotntacts */
	#define E907006011_REPROCEDURE_VARCHAR 1

	/* Event 907006012
		QRCODE doesn't display */
	/* Exception description */
	#define E907006012_EXCEPTIONDESCRIPTION_VARCHAR 0
	/* Lastest 10 times operation in cotntacts */
	#define E907006012_REPROCEDURE_VARCHAR 1

	/* Event 907006013
		load sim card contacts failed */
	/* Exception description */
	#define E907006013_EXCEPTIONDESCRIPTION_VARCHAR 0
	/* Lastest 10 times operation in cotntacts */
	#define E907006013_REPROCEDURE_VARCHAR 1

	/* Event 907006014
		SimFactory init exception */
	/* Exception description */
	#define E907006014_EXCEPTIONDESCRIPTION_VARCHAR 0
	/* The sim card init failed */
	#define E907006014_SIM_CARD_INT 1
	/* Lastest 10 times operation in cotntacts */
	#define E907006014_REPROCEDURE_VARCHAR 2

	/* Event 907006015
		Photo decode failed */
	/* Exception description */
	#define E907006015_EXCEPTIONDESCRIPTION_VARCHAR 0
	/* Lastest 10 times operation in cotntacts */
	#define E907006015_REPROCEDURE_VARCHAR 1

	/* Event 907006016
		Export vcard failed */
	/* Exception description */
	#define E907006016_EXCEPTIONDESCRIPTION_VARCHAR 0
	/* Lastest 10 times operation in cotntacts */
	#define E907006016_REPROCEDURE_VARCHAR 1

	/* Event 907006017
		Import vcard failed */
	/* Exception description */
	#define E907006017_EXCEPTIONDESCRIPTION_VARCHAR 0
	/* Lastest 10 times operation in cotntacts */
	#define E907006017_REPROCEDURE_VARCHAR 1

	/* Event 907006018
		NFC handler exception */
	/* Exception description */
	#define E907006018_EXCEPTIONDESCRIPTION_VARCHAR 0
	/* Lastest 10 times operation in cotntacts */
	#define E907006018_REPROCEDURE_VARCHAR 1

	/* Event 907006019
		NFC Import contacts exception */
	/* Exception description */
	#define E907006019_EXCEPTIONDESCRIPTION_VARCHAR 0
	/* Lastest 10 times operation in cotntacts */
	#define E907006019_REPROCEDURE_VARCHAR 1

	/* Event 907006020
		YellowPage databases read error */
	/* Exception description */
	#define E907006020_EXCEPTIONDESCRIPTION_VARCHAR 0
	/* Lastest 10 times operation in cotntacts */
	#define E907006020_REPROCEDURE_VARCHAR 1

	/* Event 907006021
		Add/remove blacklist failed */
	/* Exception description */
	#define E907006021_EXCEPTIONDESCRIPTION_VARCHAR 0
	/* Lastest 10 times operation in cotntacts */
	#define E907006021_REPROCEDURE_VARCHAR 1

	/* Event 907006022
		Dialpad tone issue */
	/* Exception description */
	#define E907006022_EXCEPTIONDESCRIPTION_VARCHAR 0
	/* Lastest 10 times operation in cotntacts */
	#define E907006022_REPROCEDURE_VARCHAR 1

	/* Event 907006023
		MEID can not get */
	/* Exception description */
	#define E907006023_EXCEPTIONDESCRIPTION_VARCHAR 0
	/* Lastest 10 times operation in cotntacts */
	#define E907006023_REPROCEDURE_VARCHAR 1

	/* Event 907006024
		Get sim card email counts failed */
	/* Exception description */
	#define E907006024_EXCEPTIONDESCRIPTION_VARCHAR 0
	/* Lastest 10 times operation in cotntacts */
	#define E907006024_REPROCEDURE_VARCHAR 1

	/* Event 907006025
		SIM states not correct */
	/* Exception description */
	#define E907006025_EXCEPTIONDESCRIPTION_VARCHAR 0
	/* Lastest 10 times operation in cotntacts */
	#define E907006025_REPROCEDURE_VARCHAR 1

	/* Event 907006026
		SIM state exception */
	/* Exception description */
	#define E907006026_EXCEPTIONDESCRIPTION_VARCHAR 0
	/* Lastest 10 times operation in cotntacts */
	#define E907006026_REPROCEDURE_VARCHAR 1

	/* Event 907006027
		Number location can not used */
	/* Exception description */
	#define E907006027_EXCEPTIONDESCRIPTION_VARCHAR 0
	/* Lastest 10 times operation in cotntacts */
	#define E907006027_REPROCEDURE_VARCHAR 1

	/* Event 907006028
		Dialpad display exception */
	/* Exception description */
	#define E907006028_EXCEPTIONDESCRIPTION_VARCHAR 0
	/* Lastest 10 times operation in cotntacts */
	#define E907006028_REPROCEDURE_VARCHAR 1

	/* Event 907006029
		sim card contacts display error */
	/* Exception description */
	#define E907006029_EXCEPTIONDESCRIPTION_VARCHAR 0
	/* Lastest 10 times operation in cotntacts */
	#define E907006029_REPROCEDURE_VARCHAR 1

	/* Event 907006030
		HightLight chars exception */
	/* Exception description */
	#define E907006030_EXCEPTIONDESCRIPTION_VARCHAR 0
	/* Lastest 10 times operation in cotntacts */
	#define E907006030_REPROCEDURE_VARCHAR 1

	/* Event 907006031
		The number location database exception */
	/* Exception description */
	#define E907006031_EXCEPTIONDESCRIPTION_VARCHAR 0
	/* Lastest 10 times operation in cotntacts */
	#define E907006031_REPROCEDURE_VARCHAR 1

	/* Event 907006032
		Contacts photo decode failed */
	/* Exception description */
	#define E907006032_EXCEPTIONDESCRIPTION_VARCHAR 0
	/* Lastest 10 times operation in cotntacts */
	#define E907006032_REPROCEDURE_VARCHAR 1

	/* Event 907006033
		SIM Contacts display exception */
	/* Exception description */
	#define E907006033_EXCEPTIONDESCRIPTION_VARCHAR 0
	/* Lastest 10 times operation in cotntacts */
	#define E907006033_REPROCEDURE_VARCHAR 1

	/* Event 907006034
		SIM card plug out,SIM contacts display exception */
	/* Real used time */
	#define E907006034_SPENTTIME_VARCHAR 0
	/* Exception description */
	#define E907006034_EXCEPTIONDESCRIPTION_VARCHAR 1

	/* Event 907006035
		ContactsProvider crash */
	/* Exception description */
	#define E907006035_EXCEPTIONDESCRIPTION_VARCHAR 0

	/* Event 907006036
		repeated contacts monitor */
	/* Exception description */
	#define E907006036_EXCEPTIONDESCRIPTION_VARCHAR 0

	/* Event 907006037
		Search result mismatch infact contacts */
	/* contacts id */
	#define E907006037_CONTACT_ID_INT 0
	/* Account Type */
	#define E907006037_ACCOUT_TYPE_VARCHAR 1
	/* Fail Reason */
	#define E907006037_FAIL_REASON_VARCHAR 2

	/* Event 907006038
		Cannot edit Contacts groups */
	/* Group Type */
	#define E907006038_GROUP_TYPE_VARCHAR 0
	/* Operate Type */
	#define E907006038_OPERATE_TYPE_VARCHAR 1
	/* Fail Reason */
	#define E907006038_FAIL_REASON_VARCHAR 2

	/* Event 907009001
		add attachment failed in SecureConversationViewFragment */
	/* APK Version */
	#define E907009001_APK_VERSION_VARCHAR 0
	/* Bug description */
	#define E907009001_DETAIL_VARCHAR 1

	/* Event 907009002
		Bad sync key,reset and delete data,resync email */
	/* APK Version */
	#define E907009002_APK_VERSION_VARCHAR 0
	/* Bug description */
	#define E907009002_DETAIL_VARCHAR 1

	/* Event 907009003
		When user reply/forward/etc a message, the orginal
		message is wrong */
	/* APK Version */
	#define E907009003_APK_VERSION_VARCHAR 0
	/* Bug description */
	#define E907009003_DETAIL_VARCHAR 1

	/* Event 907009004
		Client does not recognize the server's command */
	/* APK Version */
	#define E907009004_APK_VERSION_VARCHAR 0
	/* Bug description */
	#define E907009004_DETAIL_VARCHAR 1

	/* Event 907009005
		Sync mail happens error */
	/* APK Version */
	#define E907009005_APK_VERSION_VARCHAR 0
	/* Bug description */
	#define E907009005_DETAIL_VARCHAR 1

	/* Event 907009006
		download attachments failed */
	/* APK Version */
	#define E907009006_APK_VERSION_VARCHAR 0
	/* Bug description */
	#define E907009006_DETAIL_VARCHAR 1

	/* Event 907009007
		sync contacts failed */
	/* APK Version */
	#define E907009007_APK_VERSION_VARCHAR 0
	/* Bug description */
	#define E907009007_DETAIL_VARCHAR 1

	/* Event 907009008
		sync calender failed */
	/* APK Version */
	#define E907009008_APK_VERSION_VARCHAR 0
	/* Bug description */
	#define E907009008_DETAIL_VARCHAR 1

	/* Event 907009009
		Device id changes, need to rebind */
	/* APK Version */
	#define E907009009_APK_VERSION_VARCHAR 0
	/* Device id changes, need to rebind */
	#define E907009009_REASON_VARCHAR 1

	/* Event 907009010
		cannot get all the unread emails */
	/* APK Version */
	#define E907009010_APK_VERSION_VARCHAR 0
	/* Bug description */
	#define E907009010_DETAIL_VARCHAR 1

	/* Event 907009011
		cannot get the email automaticly */
	/* APK Version */
	#define E907009011_APK_VERSION_VARCHAR 0
	/* Bug description */
	#define E907009011_DETAIL_VARCHAR 1

	/* Event 907009012
		Mail consume too much traffic */
	/* APK Version */
	#define E907009012_APK_VERSION_VARCHAR 0
	/* Bug description */
	#define E907009012_DETAIL_VARCHAR 1

	/* Event 907009013
		send mail failed */
	/* APK Version */
	#define E907009013_APK_VERSION_VARCHAR 0
	/* Bug description */
	#define E907009013_DETAIL_VARCHAR 1

	/* Event 907012001
		open camera fail */
	/* APK version number */
	#define E907012001_APK_VERSION_VARCHAR 0
	/* Bug description */
	#define E907012001_DETAIL_VARCHAR 1
	/* camera id */
	#define E907012001_CAMERAID_INT 2

	/* Event 907012002
		save picture fail */
	/* APK version number */
	#define E907012002_APK_VERSION_VARCHAR 0
	/* Bug description */
	#define E907012002_DETAIL_VARCHAR 1
	/* picture Name */
	#define E907012002_PICTURENAME_VARCHAR 2
	/* prefer storage path */
	#define E907012002_PREFERSTORAGEPOS_INT 3
	/* picture storage path */
	#define E907012002_STORAGEPATH_VARCHAR 4
	/* picture type */
	#define E907012002_TYPE_INT 5

	/* Event 907012003
		camera error */
	/* APK version number */
	#define E907012003_APK_VERSION_VARCHAR 0
	/* Bug description */
	#define E907012003_DETAIL_VARCHAR 1
	/* camera id */
	#define E907012003_CAMERAID_INT 2
	/* error code */
	#define E907012003_ERRORCODE_INT 3

	/* Event 907012004
		no picture back */
	/* APK version number */
	#define E907012004_APK_VERSION_VARCHAR 0
	/* Bug description */
	#define E907012004_DETAIL_VARCHAR 1

	/* Event 907012105
		capture no response */
	/* Fail Reason */
	#define E907012105_FAIL_REASON_VARCHAR 0
	/* Extra Info */
	#define E907012105_EXTRA_INFO_VARCHAR 1

	/* Event 907012106
		save video fail */
	/* Fail Reason */
	#define E907012106_FAIL_REASON_VARCHAR 0
	/* Extra Info */
	#define E907012106_EXTRA_INFO_VARCHAR 1

	/* Event 907012107
		abnormal performance */
	/* Abnormal scene */
	#define E907012107_ABNORMAL_SCENE_VARCHAR 0
	/* Extra Info */
	#define E907012107_EXTRA_INFO_VARCHAR 1

	/* Event 907012008
		Switch camera timeout */
	/* Current camera id,0 for facing-back, 1 for facing-front */
	#define E907012008_CURRENT_CAMERAID_INT 0
	/* Bug description */
	#define E907012008_DETAIL_VARCHAR 1

	/* Event 907012009
		Stop recording timeout */
	/* Bug description */
	#define E907012009_DETAIL_VARCHAR 0

	/* Event 907012010
		Downloaded camera mode install fail */
	/* Plugin fileName */
	#define E907012010_PLUGIN_FILENAME_VARCHAR 0
	/* Plugin install path */
	#define E907012010_PLUGIN_INSTALL_PATH_VARCHAR 1
	/* Bug description */
	#define E907012010_DETAIL_VARCHAR 2

	/* Event 907015001
		Job running overtime(3s) in thread pool. */
	/* APK version number */
	#define E907015001_APK_VERSION_VARCHAR 0
	/* Scene def */
	#define E907015001_SCENE_DEF_INT 1
	/* Bug description */
	#define E907015001_DETAIL_VARCHAR 2

	/* Event 907015600
		Decode picture failed. */
	/* APK version number */
	#define E907015600_APK_VERSION_VARCHAR 0
	/* Scene def */
	#define E907015600_SCENE_DEF_INT 1
	/* filepath */
	#define E907015600_FILEPATH_VARCHAR 2
	/* Bug description */
	#define E907015600_DETAIL_VARCHAR 3

	/* Event 907015601
		Decode video failed. */
	/* APK version number */
	#define E907015601_APK_VERSION_VARCHAR 0
	/* Scene def */
	#define E907015601_SCENE_DEF_INT 1
	/* filepath */
	#define E907015601_FILEPATH_VARCHAR 2
	/* Bug description */
	#define E907015601_DETAIL_VARCHAR 3

	/* Event 907015700
		Gallery start-up failed in 3s. */
	/* APK version number */
	#define E907015700_APK_VERSION_VARCHAR 0
	/* Scene def */
	#define E907015700_SCENE_DEF_INT 1
	/* Bug description */
	#define E907015700_DETAIL_VARCHAR 2

	/* Event 907015701
		Main thread execution time consuming data loading */
	/* APK version number */
	#define E907015701_APK_VERSION_VARCHAR 0
	/* Scene def */
	#define E907015701_SCENE_DEF_INT 1
	/* Bug description */
	#define E907015701_DETAIL_VARCHAR 2

	/* Event 907015702
		Create region decode engine failed. */
	/* APK version number */
	#define E907015702_APK_VERSION_VARCHAR 0
	/* Bug type */
	#define E907015702_BUG_TYPE_INT 1
	/* filepath */
	#define E907015702_FILEPATH_VARCHAR 2
	/* Bug description */
	#define E907015702_DETAIL_VARCHAR 3

	/* Event 907015703
		Region decoding failed. */
	/* APK version number */
	#define E907015703_APK_VERSION_VARCHAR 0
	/* Scene def */
	#define E907015703_SCENE_DEF_INT 1
	/* filepath */
	#define E907015703_FILEPATH_VARCHAR 2
	/* Bug description */
	#define E907015703_DETAIL_VARCHAR 3

	/* Event 907018001
		Can not show fragment */
	/* invalid fragment name */
	#define E907018001_FRAGMENTNAME_VARCHAR 0

	/* Event 907018002
		WIFI enable time out */
	/* WIFI state when time out */
	#define E907018002_CURRENTSTATE_INT 0

	/* Event 907018003
		Bluetooth enable time out */
	/* Bt state when time out */
	#define E907018003_CURRENTSTATE_INT 0

	/* Event 907018004
		WIFI hotspot enable time out */
	/* WIFI hotspot state when time out */
	#define E907018004_CURRENTSTATE_INT 0

	/* Event 907018005
		Can not set ringtone */
	/* state code from HwThemeMananger */
	#define E907018005_RESULTCODE_INT 0
	/* uri return from HwThemeManager */
	#define E907018005_URI_VARCHAR 1

	/* Event 907018006
		Can not add new user */
	/* User type */
	#define E907018006_USERTYPE_INT 0
	/* User name */
	#define E907018006_USERNAME_VARCHAR 1

	/* Event 907018007
		Can not add new FingerPrint */
	/* Bug ID */
	#define E907018007_ERRMSGID_INT 0
	/* Bug information */
	#define E907018007_ERRSTRING_VARCHAR 1

	/* Event 907018008
		Can not set lockscreen password */
	/* Lock screen type */
	#define E907018008_LOCKTYPE_INT 0

	/* Event 907018009
		Can not set sd card password */
	/* Response code for setting operation */
	#define E907018009_RESPONSECODE_INT 0
	/* SD card lock state before settings */
	#define E907018009_STATE_INT 1

	/* Event 907018010
		Can not clear sd card password */
	/* Response code for setting operation */
	#define E907018010_RESPONSECODE_INT 0

	/* Event 907018011
		Can not unlock sd card password */
	/* Response code for setting operation */
	#define E907018011_RESPONSECODE_INT 0

	/* Event 907021001
		Failed to get operator name */
	/* DeviceId */
	#define E907021001_DEVICEID_VARCHAR 0
	/* tencent sdk version */
	#define E907021001_CURRENTVERSION_VARCHAR 1

	/* Event 907021002
		Failed to traffic calibration */
	/* DeviceId */
	#define E907021002_DEVICEID_VARCHAR 0
	/* tencent sdk version */
	#define E907021002_CURRENTVERSION_VARCHAR 1

	/* Event 907021003
		Failed to stop app from secondary-starting */
	/* Reason */
	#define E907021003_RESAON_VARCHAR 0
	/* Caller imformation */
	#define E907021003_CALLER_INFO_VARCHAR 1
	/* Target imformation */
	#define E907021003_TARGE_INFO_VARCHAR 2

	/* Event 907021004
		Mainscreen scan timeout */
	/* ScanItem */
	#define E907021004_SCANITEM_INT 0

	/* Event 907021005
		failed updated */
	/* ResultCode */
	#define E907021005_RESULTCODE_VARCHAR 0
	/* tencent sdk version */
	#define E907021005_CURRENTVERSION_VARCHAR 1

	/* Event 907024001
		Clear desktop data, reload, desktop hot area icon lost */
	/* APK version number */
	#define E907024001_APK_VERSION_VARCHAR 0
	/* Bug description */
	#define E907024001_DETAIL_VARCHAR 1

	/* Event 907024002
		Switch desktop grid exception, desktop hot area icon
		is missing */
	/* APK version number */
	#define E907024002_APK_VERSION_VARCHAR 0
	/* Bug description */
	#define E907024002_DETAIL_VARCHAR 1

	/* Event 907024003
		Folder open turn off exception, icon disappears */
	/* APK version number */
	#define E907024003_APK_VERSION_VARCHAR 0
	/* Bug description */
	#define E907024003_DETAIL_VARCHAR 1

	/* Event 907024004
		Icon Lost */
	/* Lost Type */
	#define E907024004_LOST_TYPE_INT 0
	/* Lost Time */
	#define E907024004_LOST_TIME_VARCHAR 1
	/* Fail Reason */
	#define E907024004_FAIL_REASON_VARCHAR 2

	/* Event 907024005
		Repeat Icon */
	/* Repeat Icon Type */
	#define E907024005_REPEAT_ICON_TYPE_INT 0
	/* Title */
	#define E907024005_TITLE_VARCHAR 1
	/* Intent */
	#define E907024005_INTENT_VARCHAR 2
	/* Content */
	#define E907024005_CONTENT_VARCHAR 3

	/* Event 907024006
		Icon Marker Not Changed */
	/* App Name */
	#define E907024006_APPNAME_VARCHAR 0
	/* Marker Counts */
	#define E907024006_MARKERCOUNTS_INT 1
	/* Accept Time */
	#define E907024006_ACCEPT_TIME_VARCHAR 2
	/* Real Marker Counts */
	#define E907024006_REAL_MARKERCOUNTS_INT 3
	/* Content */
	#define E907024006_CONTENT_VARCHAR 4

	/* Event 907030001
		Enter the correct pin code to the lock was removed,
		slower than 1s */
	/* reason */
	#define E907030001_FAILCAUSE_VARCHAR 0
	/* password type */
	#define E907030001_PWDTYPE_VARCHAR 1

	/* Event 907030003
		Enter the correct pin SIM code to lock is removed,
		slower than 4s */
	/* reason */
	#define E907030003_FAILCAUSE_VARCHAR 0

	/* Event 907030004
		Music player interface, click on the button is invalid
		or delay */
	/* reason */
	#define E907030004_FAILCAUSE_VARCHAR 0
	/* which key pressed */
	#define E907030004_KEY_VARCHAR 1

	/* Event 907030005
		Flashlight, click on the button is invalid or delay */
	/* reason */
	#define E907030005_FAILCAUSE_VARCHAR 0
	/* on/off */
	#define E907030005_ISLIGHTSWITCHON_VARCHAR 1

	/* Event 907030007
		Magazine lock screen download failed */
	/* fail reason */
	#define E907030007_FAILCAUSE_VARCHAR 0
	/* download url */
	#define E907030007_DOWNLOADURL_VARCHAR 1
	/* downloadChannel */
	#define E907030007_CHANNEL_VARCHAR 2

	/* Event 907030008
		Inner SD not mount */
	/* Error msg for accessing Inner SD */
	#define E907030008_ERROR_MSG_VARCHAR 0
	/* Error Time */
	#define E907030008_ERROR_TIME_VARCHAR 1
	/* Fail Reason */
	#define E907030008_FAIL_REASON_VARCHAR 2

	/* Event 907030009
		MagazineUnlock not copy the whole pictures */
	/* Error Msg for Copying pictrues */
	#define E907030009_ERROR_MSG_VARCHAR 0
	/* Pictures Counts */
	#define E907030009_PICTRUES_COUNTS_INT 1
	/* Error Time */
	#define E907030009_ERROR_TIME_VARCHAR 2
	/* Fail Reason */
	#define E907030009_FAIL_REASON_VARCHAR 3

	/* Event 907031002
		order product error */
	/* APK version number */
	#define E907031002_APK_VERSION_VARCHAR 0
	/* productId */
	#define E907031002_PRODUCTID_VARCHAR 1
	/* account status */
	#define E907031002_ACCOUNTSTATUS_VARCHAR 2
	/* fail reason */
	#define E907031002_REASON_VARCHAR 3

	/* Event 907031003
		download error */
	/* APK version number */
	#define E907031003_APK_VERSION_VARCHAR 0
	/* resource Id */
	#define E907031003_ID_VARCHAR 1
	/* is charged or free */
	#define E907031003_ISPAYED_BIT 2
	/* download url */
	#define E907031003_DOWNLOADURL_VARCHAR 3
	/* fail reason */
	#define E907031003_REASON_VARCHAR 4
	/* right */
	#define E907031003_RIGHT_VARCHAR 5

	/* Event 907031004
		json parse error */
	/* APK version number */
	#define E907031004_APK_VERSION_VARCHAR 0
	/* interface name */
	#define E907031004_INTERFACENAME_VARCHAR 1
	/* error detail */
	#define E907031004_ERROR_VARCHAR 2

	/* Event 907031005
		no theme */
	/* APK version number */
	#define E907031005_APK_VERSION_VARCHAR 0
	/* is local version apk */
	#define E907031005_ISLOCAL_BIT 1
	/* is conifg no online */
	#define E907031005_ISCONFIGNOONLINE_BIT 2
	/* sim isocode */
	#define E907031005_ISOCODE_VARCHAR 3
	/* region */
	#define E907031005_REGION_VARCHAR 4
	/* online switch on server */
	#define E907031005_ISSUPPORTONLINETHEME_BIT 5

	/* Event 907031006
		red point has no updated theme */
	/* APK version number */
	#define E907031006_APK_VERSION_VARCHAR 0
	/* red point count in db */
	#define E907031006_DBCOUNT_VARCHAR 1
	/* update theme json */
	#define E907031006_JSON_VARCHAR 2
	/* installed themes */
	#define E907031006_INSTALLEDTHEMES_VARCHAR 3

	/* Event 907031007
		notificationjump to preview fail */
	/* APK version number */
	#define E907031007_APK_VERSION_VARCHAR 0
	/* id,title,version */
	#define E907031007_THEMEINFO_VARCHAR 1
	/* error detail */
	#define E907031007_ERROR_VARCHAR 2

	/* Event 907032001
		The Bluetooth signal is not in the normal range. */
	/* smartLock switch state */
	#define E907032001_ISSMARTLOCKSWITCHON_BIT 0
	/* bluetooth switch state */
	#define E907032001_ISBLUETOOTHSWITCHON_BIT 1
	/* Current rssi */
	#define E907032001_RSSI_INT 2

	/* Event 907033001
		Single handle mode read exception */
	/* Exception reason */
	#define E907033001_REASON_VARCHAR 0

	/* Event 907033002
		Failed to load recent tasks */
	/* Exception reason */
	#define E907033002_REASON_VARCHAR 0
	/* recent tasks count */
	#define E907033002_NUMBER_INT 1
	/* current user id */
	#define E907033002_USER_INT 2

	/* Event 907033003
		Low memory without using BlurWallpaper */
	/* Exception reason */
	#define E907033003_REASON_VARCHAR 0
	/* Current memory */
	#define E907033003_MEMORY_VARCHAR 1
	/* Current bitmap name user setted */
	#define E907033003_BITMAP_NAME_VARCHAR 2

	/* Event 907033004
		Init BlurWallpaper failed */
	/* Exception reason */
	#define E907033004_REASON_VARCHAR 0
	/* Current bitmap name user setted */
	#define E907033004_BITMAP_NAME_VARCHAR 1

	/* Event 907033005
		Failed to take screenshot */
	/* Exception reason */
	#define E907033005_REASON_VARCHAR 0
	/* Screenshot type */
	#define E907033005_TYPE_VARCHAR 1

	/* Event 907033006
		Error loading sound for notification */
	/* Exception reason */
	#define E907033006_REASON_VARCHAR 0
	/* Current ring name the user setted */
	#define E907033006_RING_NAME_VARCHAR 1

	/* Event 907033007
		Draw wallpaper exception */
	/* Exception reason */
	#define E907033007_REASON_VARCHAR 0
	/* Current bitmap name user setted */
	#define E907033007_BITMAP_NAME_VARCHAR 1

	/* Event 907033008
		Battery image color set exception */
	/* Exception reason */
	#define E907033008_REASON_VARCHAR 0
	/* Current color type get from system */
	#define E907033008_COLOR_TYPE_INT 1

	/* Event 907040001
		Generation signature data */
	/* error type */
	#define E907040001_ERRORTYPE_INT 0
	/* reason of error */
	#define E907040001_REASON_VARCHAR 1
	/* supplements info */
	#define E907040001_SUPPLEMENTINFO_VARCHAR 2

	/* Event 907040002
		db downgrade error */
	/* error type */
	#define E907040002_ERRORTYPE_INT 0
	/* reason of error */
	#define E907040002_REASON_VARCHAR 1
	/* error code */
	#define E907040002_SERVERERRORCODE_VARCHAR 2
	/* supplements info */
	#define E907040002_SUPPLEMENTINFO_VARCHAR 3

	/* Event 907040003
		Cipher sent failed */
	/* error type */
	#define E907040003_ERRORTYPE_INT 0
	/* reason of error */
	#define E907040003_REASON_VARCHAR 1
	/* supplements info */
	#define E907040003_SUPPLEMENTINFO_VARCHAR 2

	/* Event 907051001
		faile to get calendar from Exchange */
	/* APK version number */
	#define E907051001_APK_VERSION_VARCHAR 0
	/* Bug description */
	#define E907051001_BODY_VARCHAR 1
	/* default theme version and theme pkg version */
	#define E907051001_CURRENTVERSION_VARCHAR 2

	/* Event 907051002
		download error */
	/* APK version number */
	#define E907051002_APK_VERSION_VARCHAR 0
	/* Bug description */
	#define E907051002_BODY_VARCHAR 1
	/* productId */
	#define E907051002_PRODUCTID_VARCHAR 2
	/* account status */
	#define E907051002_ACCOUNTSTATUS_VARCHAR 3
	/* fail reason */
	#define E907051002_REASON_VARCHAR 4

	/* Event 907051003
		sync error */
	/* APK version number */
	#define E907051003_APK_VERSION_VARCHAR 0
	/* Bug description */
	#define E907051003_BODY_VARCHAR 1
	/* resource Id */
	#define E907051003_ID_VARCHAR 2
	/* is charged or free */
	#define E907051003_ISPAYED_BIT 3
	/* download url */
	#define E907051003_DOWNLOADURL_VARCHAR 4
	/* fail reason */
	#define E907051003_REASON_VARCHAR 5
	/* right */
	#define E907051003_RIGHT_VARCHAR 6

	/* Event 907051004
		share events error */
	/* APK version number */
	#define E907051004_APK_VERSION_VARCHAR 0
	/* Bug description */
	#define E907051004_BODY_VARCHAR 1
	/* interface name */
	#define E907051004_INTERFACENAME_VARCHAR 2
	/* error detail */
	#define E907051004_ERROR_VARCHAR 3

	/* Event 907051005
		category error */
	/* APK version number */
	#define E907051005_APK_VERSION_VARCHAR 0
	/* Bug description */
	#define E907051005_BODY_VARCHAR 1
	/* interface name */
	#define E907051005_INTERFACENAME_VARCHAR 2
	/* error detail */
	#define E907051005_ERROR_VARCHAR 3

	/* Event 907052001
		add_picture_fail */
	/* Bug type */
	#define E907052001_BUG_TYPE_INT 0
	/* picture width */
	#define E907052001_WIDTH_INT 1
	/* picture height */
	#define E907052001_HEIGHT_INT 2
	/* error detail */
	#define E907052001_REASON_VARCHAR 3

	/* Event 907052002
		data_backup_fail */
	/* Bug type */
	#define E907052002_BUG_TYPE_INT 0
	/* local db version */
	#define E907052002_LOCALDBVERSION_INT 1
	/* backup db version */
	#define E907052002_BACKUPDBVERSION_INT 2
	/* error detail */
	#define E907052002_REASON_VARCHAR 3

	/* Event 907052003
		data_synchronize_upload_fail */
	/* Bug type */
	#define E907052003_BUG_TYPE_INT 0
	/* interface name */
	#define E907052003_INTERFACENAME_VARCHAR 1
	/* database version */
	#define E907052003_DBVERSION_INT 2
	/* error detail */
	#define E907052003_REASON_VARCHAR 3

	/* Event 907052004
		data_synchronize_download_fail */
	/* Bug type */
	#define E907052004_BUG_TYPE_INT 0
	/* interface name */
	#define E907052004_INTERFACENAME_VARCHAR 1
	/* database version */
	#define E907052004_DBVERSION_INT 2
	/* error detail */
	#define E907052004_REASON_VARCHAR 3

	/* Event 907061001
		normal alarm alerted fail */
	/* Alert in silence mode status */
	#define E907061001_ALERT_IN_SILENCE_MODE_VARCHAR 0
	/* Alert time */
	#define E907061001_ALERT_TIME_VARCHAR 1

	/* Event 907061002
		power off alarm alerted fail */
	/* Alert in silence mode status */
	#define E907061002_ALERT_IN_SILENCE_MODE_VARCHAR 0
	/* Alert time */
	#define E907061002_ALERT_TIME_VARCHAR 1
	/* Power on reason */
	#define E907061002_POWER_ON_REASON_VARCHAR 2

	/* Event 907069001
		location city is error */
	/* APK version number */
	#define E907069001_APK_VERSION_VARCHAR 0
	/* sim isocode */
	#define E907069001_ISOCODE_VARCHAR 1

	/* Event 907069002
		weather push time 's abnormal */
	/* APK version number */
	#define E907069002_APK_VERSION_VARCHAR 0
	/* Data soure type */
	#define E907069002_DATASOURCE_INT 1
	/* error detail */
	#define E907069002_REASON_VARCHAR 2

	/* Event 907069003
		http failed */
	/* APK version number */
	#define E907069003_APK_VERSION_VARCHAR 0
	/* Data soure type */
	#define E907069003_DATASOURCE_INT 1

	/* Event 907069004
		location failed */
	/* APK version number */
	#define E907069004_APK_VERSION_VARCHAR 0
	/* location service */
	#define E907069004_PROVIDER_VARCHAR 1

	/* Event 907069005
		city has no pollution */
	/* APK version number */
	#define E907069005_APK_VERSION_VARCHAR 0
	/* City Info */
	#define E907069005_CITYCODE_VARCHAR 1

	/* Event 907069006
		json parse error */
	/* APK version number */
	#define E907069006_APK_VERSION_VARCHAR 0
	/* interface name */
	#define E907069006_INTERFACENAME_VARCHAR 1
	/* error detail */
	#define E907069006_REASON_VARCHAR 2
	/* Data soure type */
	#define E907069006_DATASOURCE_INT 3

	/* Event 907090001
		Card lost */
	/* Card Type */
	#define E907090001_CARD_TYPE_VARCHAR 0

	/* Event 907090002
		WeatherServer status wrong */
	/* cur state */
	#define E907090002_CUR_STATE_VARCHAR 0
	/* cur op */
	#define E907090002_CUR_OP_VARCHAR 1

	/* Event 907090003
		assert error */
	/* fun name */
	#define E907090003_FUN_NAME_VARCHAR 0
	/* var name */
	#define E907090003_VAR_NAME_VARCHAR 1
	/* class name */
	#define E907090003_CLASS_NAME_VARCHAR 2
	/* assert */
	#define E907090003_ASSERT_VARCHAR 3

	/* Event 907090004
		flight code error */
	/* flightCode */
	#define E907090004_FLIGHT_CODE_VARCHAR 0
	/* date */
	#define E907090004_DATE_VARCHAR 1

	/* Event 907090005
		train code error */
	/* trainNum */
	#define E907090005_TRAIN_NUM_VARCHAR 0
	/* date */
	#define E907090005_DATE_VARCHAR 1

	/* Event 907090006
		flow error */
	/* fun name */
	#define E907090006_FUN_NAME_VARCHAR 0
	/* class name */
	#define E907090006_CLASS_NAME_VARCHAR 1
	/* flow name */
	#define E907090006_FLOW_NAME_VARCHAR 2
	/* detail */
	#define E907090006_DETAIL_VARCHAR 3

	/* Event 907091001
		fail release wakeLock */
	/* APK version number */
	#define E907091001_APK_VERSION_VARCHAR 0
	/*  */
	#define E907091001_REASON_VARCHAR 1

	/* Event 907091002
		fail to load gammar */
	/* APK version number */
	#define E907091002_APK_VERSION_VARCHAR 0
	/* fail reason */
	#define E907091002_REASON_VARCHAR 1

	/* Event 907091003
		fail to open navi */
	/* APK version number */
	#define E907091003_APK_VERSION_VARCHAR 0
	/* fail reason */
	#define E907091003_REASON_VARCHAR 1

	/* Event 907091004
		xml parse error */
	/* APK version number */
	#define E907091004_APK_VERSION_VARCHAR 0
	/* fail reason */
	#define E907091004_REASON_VARCHAR 1

	/* Event 907092001
		vdriver can not connect Mirrorlink */
	/* mirrorlink Major version */
	#define E907092001_ML_MAJOR_VERSION_INT 0
	/* ML Minor Version */
	#define E907092001_ML_MINOR_VERSION_INT 1
	/* function name */
	#define E907092001_FUNCTION_NAME_VARCHAR 2
	/* is in ncm mode */
	#define E907092001_NCM_STATUS_BIT 3
	/* error description */
	#define E907092001_REASON_VARCHAR 4

	/* Event 907100001
		NFC no response */
	/* Fail Reason */
	#define E907100001_FAIL_REASON_VARCHAR 0

	/* Event 907102001
		BLE_START_TIMEOUT */
	/* Fail Reason */
	#define E907102001_FAIL_REASON_VARCHAR 0

	/* Event 907102002
		BREDR_START_TIMEOUT */
	/* Fail Reason */
	#define E907102002_FAIL_REASON_VARCHAR 0

	/* Event 907102003
		ENABLE_TIMEOUT */
	/* Fail Reason */
	#define E907102003_FAIL_REASON_VARCHAR 0

	/* Event 907102004
		BOND_FAULT */
	/* Fail Reason */
	#define E907102004_FAIL_REASON_VARCHAR 0

	/* Event 907102005
		SCAN_FAULT */
	/* Fail Reason */
	#define E907102005_FAIL_REASON_VARCHAR 0

	/* Event 907102006
		BINDER_TIMEOUT */
	/* Fail Reason */
	#define E907102006_FAIL_REASON_VARCHAR 0

	/* Event 907102007
		BREDR_STOP_TIMEOUT */
	/* Fail Reason */
	#define E907102007_FAIL_REASON_VARCHAR 0

	/* Event 907137000
		WeChat cfg file read failed */
	/* fail reason */
	#define E907137000_ERROR_REASON_INT 0
	/* WeChat version number */
	#define E907137000_WECHAT_VERSION_INT 1
	/* WeChatStrategy version number */
	#define E907137000_WECHATSTRATEGY_VERSION_INT 2

	/* Event 907137001
		WeChat StepCount restart */

	/* Event 907137003
		WeChat StepCount exception */
	/* WeChat cfg file read failed count */
	#define E907137003_CFG_FILE_EXCEPTION_INT 0
	/* WeChat StepCountService restart count */
	#define E907137003_RESTART_COUNT_INT 1

	/* Event 907119001
		failed to backup or restore data */
	/* APK version number */
	#define E907119001_APK_VERSION_VARCHAR 0
	/* Bug type */
	#define E907119001_BUG_TYPE_INT 1
	/* Operate Time */
	#define E907119001_OPERATE_TIME_DATETIME 2
	/* File Path */
	#define E907119001_FILE_PATH_VARCHAR 3
	/* fail reason */
	#define E907119001_REASON_VARCHAR 4

	/* Event 907119002
		failed to login dbank */
	/* APK version number */
	#define E907119002_APK_VERSION_VARCHAR 0
	/* Bug type */
	#define E907119002_BUG_TYPE_INT 1
	/* Login Time */
	#define E907119002_LOGIN_TIME_DATETIME 2
	/* User ID */
	#define E907119002_USER_ID_VARCHAR 3
	/* Server Return Info */
	#define E907119002_SERVER_RETURN_INFO_VARCHAR 4
	/* fail reason */
	#define E907119002_REASON_VARCHAR 5

	/* Event 907124001
		PushService onDestroy */
	/* APK version number */
	#define E907124001_APK_VERSION_VARCHAR 0
	/* Build.MODEL */
	#define E907124001_MODE_VARCHAR 1

	/* Event 907124002
		PushService catch uncaughtException */
	/* APK version number */
	#define E907124002_APK_VERSION_VARCHAR 0
	/* Bug description */
	#define E907124002_ERRORINFO_VARCHAR 1

	/* Event 907126001
		delete file failure */
	/* APK version number */
	#define E907126001_APK_VERSION_VARCHAR 0
	/* delete timestamp */
	#define E907126001_DELETE_TIME_DATETIME 1
	/* API return code */
	#define E907126001_API_RETURN_CODE_VARCHAR 2
	/* AbsolutePath */
	#define E907126001_ABSOLUTEPATH_VARCHAR 3
	/* fail reason */
	#define E907126001_REASON_VARCHAR 4

	/* Event 907126002
		login to dbank failure */
	/* APK version number */
	#define E907126002_APK_VERSION_VARCHAR 0
	/* login timestamp */
	#define E907126002_LOGIN_TIME_DATETIME 1
	/* login user id */
	#define E907126002_LOGIN_USER_ID_VARCHAR 2
	/* Server return info */
	#define E907126002_SERVER_RETURN_INFO_VARCHAR 3
	/* fail reason */
	#define E907126002_REASON_VARCHAR 4

	/* Event 907126003
		download dbank file frequent failure */
	/* APK version number */
	#define E907126003_APK_VERSION_VARCHAR 0
	/* download failure time */
	#define E907126003_DOWNLOAD_FAILURE_TIME_DATETIME 1
	/* login user id */
	#define E907126003_LOGIN_USER_ID_VARCHAR 2
	/* download url host */
	#define E907126003_DOWNLOAD_URL_HOST_VARCHAR 3
	/* file total size */
	#define E907126003_FILE_TOTAL_SIZE_VARCHAR 4
	/* current downloaded size */
	#define E907126003_CURRENT_DOWNLOADED_SIZE_VARCHAR 5
	/* WIFI: 1 MOBILE: 2 */
	#define E907126003_NETWORK_TYPE_INT 6
	/* fail reason */
	#define E907126003_REASON_VARCHAR 7

	/* Event 907132001
		PhoneClone disConnect */
	/* APK version number */
	#define E907132001_APK_VERSION_VARCHAR 0
	/* phone disconnect info */
	#define E907132001_PHONE_DISCONNECT_VARCHAR 1
	/* disconnect_time */
	#define E907132001_DISCONNECT_TIME_DATETIME 2
	/* fail reason */
	#define E907132001_REASON_VARCHAR 3

	/* Event 907132002
		PhoneClone transmission application or data failed */
	/* APK version number */
	#define E907132002_APK_VERSION_VARCHAR 0
	/* send success: true,send fail: false */
	#define E907132002_SENDER_STATUS_BIT 1
	/* receive success:true, receive fail:false */
	#define E907132002_RECEIVE_STATUS_BIT 2
	/* app instal lresult in the new phone */
	#define E907132002_INSTALL_RESULT_VARCHAR 3
	/* fail reason */
	#define E907132002_REASON_VARCHAR 4

	/* Event 907142002
		Location search failed */
	/* Failed phase */
	#define E907142002_FAILED_PHASE_INT 0
	/* Reason description */
	#define E907142002_REASON_INT 1

	/* Event 907144001
		Wildkids mode exist failure after reboot */
	/* Bug description */
	#define E907144001_BUG_DESCRIPTION_VARCHAR 0
	/* Restore launcher */
	#define E907144001_RESTORELAUNCHER_INT 1

	/* Event 907144002
		Setting wildkids as default launcher failure */
	/* Bug description */
	#define E907144002_BUG_DESCRIPTION_VARCHAR 0
	/* Restore launcher */
	#define E907144002_RESTORELAUNCHER_INT 1
	/* Current default Launcher */
	#define E907144002_CURRENT_LAUNCHER_VARCHAR 2

	/* Event 907144003
		Suspending timing failure during incomming call */
	/* Bug description */
	#define E907144003_BUG_DESCRIPTION_VARCHAR 0
	/* Timing status */
	#define E907144003_TIMING_STATUS_INT 1
	/* Calling status */
	#define E907144003_CALL_STATUS_INT 2
	/* Current screen */
	#define E907144003_FRONT_ACTIVITY_VARCHAR 3
	/* Screen status */
	#define E907144003_SCREEN_STATUS_INT 4

	/* Event 907145001
		Location search failed */
	/* APK version number */
	#define E907145001_APK_VERSION_VARCHAR 0
	/* Failed phase */
	#define E907145001_FAILED_PHASE_INT 1
	/* Reason description */
	#define E907145001_REASON_INT 2

	/* Event 907350000
		Enter static state */
	/* Glass connect state */
	#define E907350000_GLASS_CONNECT_STATE_VARCHAR 0
	/* In static state */
	#define E907350000_IN_STATIC_STATE_VARCHAR 1
	/* Heartbeat state */
	#define E907350000_HEARTBEAT_STATE_VARCHAR 2
	/* Glass Dfu upgrade state */
	#define E907350000_DFU_UPGRADE_STATE_VARCHAR 3
	/* Glass Dfu connect state */
	#define E907350000_DFU_CONNECT_STATE_VARCHAR 4
	/* VRLauncher startup state */
	#define E907350000_START_VRLAUNCHER_STATE_VARCHAR 5
	/* VRParentActivity startup state */
	#define E907350000_VRPARENTACTIVITY_START_STATE_VARCHAR 6
	/* Navigator hide state */
	#define E907350000_NAVIGATOR_HIDE_STATE_VARCHAR 7
	/* Extra Info */
	#define E907350000_EXTRA_INFO_VARCHAR 8

	/* Event 907350001
		Not resume from static state */
	/* Glass connect state */
	#define E907350001_GLASS_CONNECT_STATE_VARCHAR 0
	/* In static state */
	#define E907350001_IN_STATIC_STATE_VARCHAR 1
	/* Heartbeat state */
	#define E907350001_HEARTBEAT_STATE_VARCHAR 2
	/* Glass Dfu upgrade state */
	#define E907350001_DFU_UPGRADE_STATE_VARCHAR 3
	/* Glass Dfu connect state */
	#define E907350001_DFU_CONNECT_STATE_VARCHAR 4
	/* VRLauncher startup state */
	#define E907350001_START_VRLAUNCHER_STATE_VARCHAR 5
	/* VRParentActivity startup state */
	#define E907350001_VRPARENTACTIVITY_START_STATE_VARCHAR 6
	/* Navigator hide state */
	#define E907350001_NAVIGATOR_HIDE_STATE_VARCHAR 7
	/* Extra Info */
	#define E907350001_EXTRA_INFO_VARCHAR 8

	/* Event 907350002
		Exit vr mode overtime */
	/* Glass connect state */
	#define E907350002_GLASS_CONNECT_STATE_VARCHAR 0
	/* In static state */
	#define E907350002_IN_STATIC_STATE_VARCHAR 1
	/* Heartbeat state */
	#define E907350002_HEARTBEAT_STATE_VARCHAR 2
	/* Glass Dfu upgrade state */
	#define E907350002_DFU_UPGRADE_STATE_VARCHAR 3
	/* Glass Dfu connect state */
	#define E907350002_DFU_CONNECT_STATE_VARCHAR 4
	/* VRLauncher startup state */
	#define E907350002_START_VRLAUNCHER_STATE_VARCHAR 5
	/* VRParentActivity startup state */
	#define E907350002_VRPARENTACTIVITY_START_STATE_VARCHAR 6
	/* Navigator hide state */
	#define E907350002_NAVIGATOR_HIDE_STATE_VARCHAR 7
	/* Extra Info */
	#define E907350002_EXTRA_INFO_VARCHAR 8

	/* Event 907350003
		Lock screen invalid */
	/* Glass connect state */
	#define E907350003_GLASS_CONNECT_STATE_VARCHAR 0
	/* In static state */
	#define E907350003_IN_STATIC_STATE_VARCHAR 1
	/* Heartbeat state */
	#define E907350003_HEARTBEAT_STATE_VARCHAR 2
	/* Glass Dfu upgrade state */
	#define E907350003_DFU_UPGRADE_STATE_VARCHAR 3
	/* Glass Dfu connect state */
	#define E907350003_DFU_CONNECT_STATE_VARCHAR 4
	/* VRLauncher startup state */
	#define E907350003_START_VRLAUNCHER_STATE_VARCHAR 5
	/* VRParentActivity startup state */
	#define E907350003_VRPARENTACTIVITY_START_STATE_VARCHAR 6
	/* Navigator hide state */
	#define E907350003_NAVIGATOR_HIDE_STATE_VARCHAR 7
	/* Extra Info */
	#define E907350003_EXTRA_INFO_VARCHAR 8

	/* Event 907350004
		Start PrepareActivity overtime */
	/* Glass connect state */
	#define E907350004_GLASS_CONNECT_STATE_VARCHAR 0
	/* In static state */
	#define E907350004_IN_STATIC_STATE_VARCHAR 1
	/* Heartbeat state */
	#define E907350004_HEARTBEAT_STATE_VARCHAR 2
	/* Glass Dfu upgrade state */
	#define E907350004_DFU_UPGRADE_STATE_VARCHAR 3
	/* Glass Dfu connect state */
	#define E907350004_DFU_CONNECT_STATE_VARCHAR 4
	/* VRLauncher startup state */
	#define E907350004_START_VRLAUNCHER_STATE_VARCHAR 5
	/* VRParentActivity startup state */
	#define E907350004_VRPARENTACTIVITY_START_STATE_VARCHAR 6
	/* Navigator hide state */
	#define E907350004_NAVIGATOR_HIDE_STATE_VARCHAR 7
	/* Extra Info */
	#define E907350004_EXTRA_INFO_VARCHAR 8

	/* Event 907350005
		Fail to start VRLauncher */
	/* Glass connect state */
	#define E907350005_GLASS_CONNECT_STATE_VARCHAR 0
	/* In static state */
	#define E907350005_IN_STATIC_STATE_VARCHAR 1
	/* Heartbeat state */
	#define E907350005_HEARTBEAT_STATE_VARCHAR 2
	/* Glass Dfu upgrade state */
	#define E907350005_DFU_UPGRADE_STATE_VARCHAR 3
	/* Glass Dfu connect state */
	#define E907350005_DFU_CONNECT_STATE_VARCHAR 4
	/* VRLauncher startup state */
	#define E907350005_START_VRLAUNCHER_STATE_VARCHAR 5
	/* VRParentActivity startup state */
	#define E907350005_VRPARENTACTIVITY_START_STATE_VARCHAR 6
	/* Navigator hide state */
	#define E907350005_NAVIGATOR_HIDE_STATE_VARCHAR 7
	/* Extra Info */
	#define E907350005_EXTRA_INFO_VARCHAR 8

	/* Event 907350006
		Hearbeat exception */
	/* Glass connect state */
	#define E907350006_GLASS_CONNECT_STATE_VARCHAR 0
	/* In static state */
	#define E907350006_IN_STATIC_STATE_VARCHAR 1
	/* Heartbeat state */
	#define E907350006_HEARTBEAT_STATE_VARCHAR 2
	/* Glass Dfu upgrade state */
	#define E907350006_DFU_UPGRADE_STATE_VARCHAR 3
	/* Glass Dfu connect state */
	#define E907350006_DFU_CONNECT_STATE_VARCHAR 4
	/* VRLauncher startup state */
	#define E907350006_START_VRLAUNCHER_STATE_VARCHAR 5
	/* VRParentActivity startup state */
	#define E907350006_VRPARENTACTIVITY_START_STATE_VARCHAR 6
	/* Navigator hide state */
	#define E907350006_NAVIGATOR_HIDE_STATE_VARCHAR 7
	/* Extra Info */
	#define E907350006_EXTRA_INFO_VARCHAR 8

	/* Event 907350007
		Hearbeat resume */
	/* Glass connect state */
	#define E907350007_GLASS_CONNECT_STATE_VARCHAR 0
	/* In static state */
	#define E907350007_IN_STATIC_STATE_VARCHAR 1
	/* Heartbeat state */
	#define E907350007_HEARTBEAT_STATE_VARCHAR 2
	/* Glass Dfu upgrade state */
	#define E907350007_DFU_UPGRADE_STATE_VARCHAR 3
	/* Glass Dfu connect state */
	#define E907350007_DFU_CONNECT_STATE_VARCHAR 4
	/* VRLauncher startup state */
	#define E907350007_START_VRLAUNCHER_STATE_VARCHAR 5
	/* VRParentActivity startup state */
	#define E907350007_VRPARENTACTIVITY_START_STATE_VARCHAR 6
	/* Navigator hide state */
	#define E907350007_NAVIGATOR_HIDE_STATE_VARCHAR 7
	/* Extra Info */
	#define E907350007_EXTRA_INFO_VARCHAR 8

	/* Event 907350008
		Dfu upgrade overtime */
	/* Glass connect state */
	#define E907350008_GLASS_CONNECT_STATE_VARCHAR 0
	/* In static state */
	#define E907350008_IN_STATIC_STATE_VARCHAR 1
	/* Heartbeat state */
	#define E907350008_HEARTBEAT_STATE_VARCHAR 2
	/* Glass Dfu upgrade state */
	#define E907350008_DFU_UPGRADE_STATE_VARCHAR 3
	/* Glass Dfu connect state */
	#define E907350008_DFU_CONNECT_STATE_VARCHAR 4
	/* VRLauncher startup state */
	#define E907350008_START_VRLAUNCHER_STATE_VARCHAR 5
	/* VRParentActivity startup state */
	#define E907350008_VRPARENTACTIVITY_START_STATE_VARCHAR 6
	/* Navigator hide state */
	#define E907350008_NAVIGATOR_HIDE_STATE_VARCHAR 7
	/* Crc check result */
	#define E907350008_CRC_CHECK_RESULT_VARCHAR 8
	/* Extra Info */
	#define E907350008_EXTRA_INFO_VARCHAR 9

	/* Event 907350009
		Dfu upgrade over the limit times */
	/* Glass connect state */
	#define E907350009_GLASS_CONNECT_STATE_VARCHAR 0
	/* In static state */
	#define E907350009_IN_STATIC_STATE_VARCHAR 1
	/* Heartbeat state */
	#define E907350009_HEARTBEAT_STATE_VARCHAR 2
	/* Glass Dfu upgrade state */
	#define E907350009_DFU_UPGRADE_STATE_VARCHAR 3
	/* Glass Dfu connect state */
	#define E907350009_DFU_CONNECT_STATE_VARCHAR 4
	/* VRLauncher startup state */
	#define E907350009_START_VRLAUNCHER_STATE_VARCHAR 5
	/* VRParentActivity startup state */
	#define E907350009_VRPARENTACTIVITY_START_STATE_VARCHAR 6
	/* Navigator hide state */
	#define E907350009_NAVIGATOR_HIDE_STATE_VARCHAR 7
	/* Extra Info */
	#define E907350009_EXTRA_INFO_VARCHAR 8

	/* Event 907400000
		Application Install Failed for installing application
		on SD card */
	/* Package Name */
	#define E907400000_PACKAGENAME_VARCHAR 0
	/* Version */
	#define E907400000_VERSION_VARCHAR 1
	/* Bug Type */
	#define E907400000_BUG_TYPE_VARCHAR 2
	/* extra info */
	#define E907400000_EXTRA_INFO_VARCHAR 3

	/* Event 907400001
		Application Install Failed for assigning different
		uid */
	/* Package Name */
	#define E907400001_PACKAGENAME_VARCHAR 0
	/* Version */
	#define E907400001_VERSION_VARCHAR 1
	/* Bug Type */
	#define E907400001_BUG_TYPE_VARCHAR 2
	/* uid that exists in phone */
	#define E907400001_CURRENT_UID_VARCHAR 3
	/* package uid that assigned by packagemanager for this
		installation. */
	#define E907400001_PKG_UID_VARCHAR 4
	/* Error message of repair failed */
	#define E907400001_UID_FIX_ERROR_VARCHAR 5
	/* extra info */
	#define E907400001_EXTRA_INFO_VARCHAR 6

	/* Event 907400002
		Ordered Broadcast Queue has overlength */
	/* Package Name */
	#define E907400002_PACKAGENAME_VARCHAR 0
	/* Version */
	#define E907400002_VERSION_VARCHAR 1
	/* Bug Type */
	#define E907400002_BUG_TYPE_VARCHAR 2
	/* the most frequent broadcast intent action */
	#define E907400002_MOST_FREQUENT_ACTION_VARCHAR 3
	/* the most frequent broadcast intent action number */
	#define E907400002_MOST_FREQUENT_ACTION_NUM_INT 4
	/* whether the ordered broadcast queue has contain mms
		action */
	#define E907400002_CONTAIN_MMS_ACTION_BIT 5
	/* the current receiver */
	#define E907400002_CURRENT_RECEIVER_VARCHAR 6
	/* the current package name */
	#define E907400002_CURRENT_RECEIVER_PACKAGE_VARCHAR 7
	/* extra info */
	#define E907400002_EXTRA_INFO_VARCHAR 8

	/* Event 907400003
		Ordered Broadcast Queue receiver timeout */
	/* Package Name */
	#define E907400003_PACKAGENAME_VARCHAR 0
	/* Version */
	#define E907400003_VERSION_VARCHAR 1
	/* Bug Type */
	#define E907400003_BUG_TYPE_VARCHAR 2
	/* the maybe timeout broadcast intent action */
	#define E907400003_ACTION_VARCHAR 3
	/* the maybe timeout receiver passed time */
	#define E907400003_REPORT_RECEIVER_TIME_FLOAT 4
	/* the current receiver */
	#define E907400003_CURRENT_RECEIVER_VARCHAR 5
	/* extra info */
	#define E907400003_EXTRA_INFO_VARCHAR 6

	/* Event 907400005
		Consuming long time in main thread message processing */
	/* Package Name */
	#define E907400005_PACKAGENAME_VARCHAR 0
	/* Version */
	#define E907400005_VERSION_VARCHAR 1
	/* Message Name */
	#define E907400005_MESSAGE_NAME_VARCHAR 2
	/* Message Took Time */
	#define E907400005_MESSAGE_TOOK_TIME_VARCHAR 3
	/* Extra Info */
	#define E907400005_EXTRA_INFO_VARCHAR 4

	/* Event 907400006
		Too many messages in main thread message queue */
	/* Package Name */
	#define E907400006_PACKAGENAME_VARCHAR 0
	/* Version */
	#define E907400006_VERSION_VARCHAR 1
	/* Message Queue Name */
	#define E907400006_MESSAGE_QUEUE_COUNT_INT 2
	/* message name of ranked first in the number of messages */
	#define E907400006_RANK_FIRST_MESSAGE_NAME_VARCHAR 3
	/* message count of ranked first in the number of messages */
	#define E907400006_RANK_FIRST_MESSAGE_COUNT_INT 4
	/* message name of ranked second in the number of messages */
	#define E907400006_RANK_SECOND_MESSAGE_NAME_VARCHAR 5
	/* message count of ranked second in the number of messages */
	#define E907400006_RANK_SECOND_MESSAGE_COUNT_INT 6
	/* message name of ranked third in the number of messages */
	#define E907400006_RANK_THIRD_MESSAGE_NAME_VARCHAR 7
	/* message count of ranked third in the number of messages */
	#define E907400006_RANK_THIRD_MESSAGE_COUNT_INT 8
	/* Extra Info */
	#define E907400006_EXTRA_INFO_VARCHAR 9

	/* Event 907400007
		Consuming long time in main thread binder communication */
	/* Package Name */
	#define E907400007_PACKAGENAME_VARCHAR 0
	/* Version */
	#define E907400007_VERSION_VARCHAR 1
	/* Binder Stack */
	#define E907400007_BINDER_STACK_VARCHAR 2
	/* Binder Took Time */
	#define E907400007_BINDER_TOOK_TIME_VARCHAR 3
	/* Extra Info */
	#define E907400007_EXTRA_INFO_VARCHAR 4

	/* Event 907400008
		Consuming long time in input processing */
	/* Package Name */
	#define E907400008_PACKAGENAME_VARCHAR 0
	/* Version */
	#define E907400008_VERSION_VARCHAR 1
	/* Input Took Time */
	#define E907400008_INPUT_TOOK_TIME_VARCHAR 2
	/* Extra Info */
	#define E907400008_EXTRA_INFO_VARCHAR 3

	/* Event 907400009
		Transparent Activity Scene Detection */
	/* Package Name */
	#define E907400009_PACKAGENAME_VARCHAR 0
	/* Version */
	#define E907400009_VERSION_VARCHAR 1
	/* Transparent activity name */
	#define E907400009_TRANSPARENT_ACTIVITY_NAME_VARCHAR 2
	/* Extra Info */
	#define E907400009_EXTRA_INFO_VARCHAR 3

	/* Event 907400010
		IME Blocking Activity Scene Detection */
	/* Package Name */
	#define E907400010_PACKAGENAME_VARCHAR 0
	/* Version */
	#define E907400010_VERSION_VARCHAR 1
	/* Block IME Name */
	#define E907400010_BLOCK_IME_NAME_VARCHAR 2
	/* Extra Info */
	#define E907400010_EXTRA_INFO_VARCHAR 3

	/* Event 907400011
		Window Of High Layer Scene Detection */
	/* Package Name */
	#define E907400011_PACKAGENAME_VARCHAR 0
	/* Version */
	#define E907400011_VERSION_VARCHAR 1
	/* High level window name */
	#define E907400011_HIGH_LEVEL_WINDOW_NAME_VARCHAR 2
	/* Extra Info */
	#define E907400011_EXTRA_INFO_VARCHAR 3

	/* Event 907400012
		Display Event Lost Scene Detection */
	/* Package Name */
	#define E907400012_PACKAGENAME_VARCHAR 0
	/* Version */
	#define E907400012_VERSION_VARCHAR 1
	/* Pid of process which lost display event */
	#define E907400012_PID_INT 2
	/* Name of process which lost display event */
	#define E907400012_PROCESS_NAME_VARCHAR 3
	/* Extra Info */
	#define E907400012_EXTRA_INFO_VARCHAR 4

	/* Event 907400013
		Focus Window Be NULL Scene Detection */
	/* Package Name */
	#define E907400013_PACKAGENAME_VARCHAR 0
	/* Version */
	#define E907400013_VERSION_VARCHAR 1
	/* Focus Activity Name */
	#define E907400013_FOCUS_ACTIVITY_NAME_VARCHAR 2
	/* Extra Info */
	#define E907400013_EXTRA_INFO_VARCHAR 3

	/* Event 907400014
		Time consuming detection of MountService call VOLD
		interface */
	/* Package Name */
	#define E907400014_PACKAGENAME_VARCHAR 0
	/* Version */
	#define E907400014_VERSION_VARCHAR 1
	/* error stack info */
	#define E907400014_ERROR_STACK_INFO_VARCHAR 2
	/* Extra Info */
	#define E907400014_EXTRA_INFO_VARCHAR 3

	/* Event 907400015
		Radar for server call exception stack */
	/* Package Name */
	#define E907400015_PACKAGENAME_VARCHAR 0
	/* Version */
	#define E907400015_VERSION_VARCHAR 1
	/* error stack info */
	#define E907400015_ERROR_STACK_INFO_VARCHAR 2
	/* Extra Info */
	#define E907400015_EXTRA_INFO_VARCHAR 3

	/* Event 907400016
		KernelCpuSpeed too large */
	/* cpu state */
	#define E907400016_CPU_STATE_VARCHAR 0
	/* Time that cpu already runs at this state */
	#define E907400016_CPU_TIME_VARCHAR 1
	/* extra info */
	#define E907400016_EXTRA_INFO_VARCHAR 2

	/* Event 907400017
		Application traffic spent unexpected */
	/* Package Name */
	#define E907400017_PROCESS_NAME_VARCHAR 0
	/* Version */
	#define E907400017_VERSION_VARCHAR 1
	/* uid */
	#define E907400017_UID_INT 2
	/* total traffic spent this month(MB) */
	#define E907400017_MONTH_TOTAL_TRAFFIC_INT 3
	/* transfer traffic spent this month(MB) */
	#define E907400017_MONTH_TX_TRAFFIC_INT 4
	/* receive traffic spent this month(MB) */
	#define E907400017_MONTH_RX_TRAFFIC_INT 5
	/* extra info */
	#define E907400017_EXTRA_INFO_VARCHAR 6

	/* Event 907400283
		Framework handle connection failed */
	/* mirrorlink Major version */
	#define E907400283_ML_MAJOR_VERSION_INT 0
	/* ML Minor Version */
	#define E907400283_ML_MINOR_VERSION_INT 1
	/* function name */
	#define E907400283_FUNCTION_NAME_VARCHAR 2
	/* is in ncm mode */
	#define E907400283_NCM_STATUS_BIT 3
	/* error description */
	#define E907400283_REASON_VARCHAR 4

	/* Event 907400281
		Undocking window failed */
	/* Activity Stack ID */
	#define E907400281_STACKID_INT 0
	/* Task Record ID */
	#define E907400281_TASKID_INT 1
	/* Fullscreen flag */
	#define E907400281_FULLSCREEN_INT 2
	/* Error description */
	#define E907400281_ERRORMSG_VARCHAR 3

	/* Event 907400282
		Fail to invoke framework interface to access data of
		another user */
	/* pid for invoker */
	#define E907400282_CALLINGPID_INT 0
	/* uid for invoker */
	#define E907400282_CALLINGUID_INT 1
	/* packagename for invoker */
	#define E907400282_CALLERPACKAGE_VARCHAR 2
	/* user id where invoker in */
	#define E907400282_USERID_INT 3
	/* simple bug description */
	#define E907400282_MSG_VARCHAR 4

	/* Event 907403000
		audio fault */
	/* Fail Reason */
	#define E907403000_FAIL_REASON_VARCHAR 0

	/* Event 907046001
		db upgrade error */
	/* error type */
	#define E907046001_ERRORTYPE_INT 0
	/* reason of error */
	#define E907046001_REASON_VARCHAR 1
	/* supplements info */
	#define E907046001_SUPPLEMENTINFO_VARCHAR 2

	/* Event 907046002
		db downgrade error */
	/* error type */
	#define E907046002_ERRORTYPE_INT 0
	/* reason of error */
	#define E907046002_REASON_VARCHAR 1
	/* supplements info */
	#define E907046002_SUPPLEMENTINFO_VARCHAR 2

	/* Event 907046003
		db damage error */
	/* error type */
	#define E907046003_ERRORTYPE_INT 0
	/* reason of error */
	#define E907046003_REASON_VARCHAR 1
	/* supplements info */
	#define E907046003_SUPPLEMENTINFO_VARCHAR 2

	/* Event 907046004
		Audio Exception */
	/* exception type */
	#define E907046004_TYPE_INT 0
	/* package name */
	#define E907046004_PACKAGENAME1_VARCHAR 1
	/* package name */
	#define E907046004_PACKAGENAME2_VARCHAR 2

/*** LogEngine events' keys ***/

	/* Event 908000000
		out of saving quota */
	/* File name */
	#define E908000000_FILENAME_VARCHAR 0
	/* File size */
	#define E908000000_FILESIZE_INT 1
	/* Full reason */
	#define E908000000_REASON_INT 2

	/* Event 908000001
		out of free space */
	/* File name */
	#define E908000001_FILENAME_VARCHAR 0
	/* File size */
	#define E908000001_FILESIZE_INT 1
	/* Total LogService file size */
	#define E908000001_TOTALLOGSIZE_INT 2
	/* Left space size */
	#define E908000001_LEFTSIZE_INT 3

	/* Event 908000002
		upload failed */
	/* File name */
	#define E908000002_FILENAME_VARCHAR 0
	/* Upload errno */
	#define E908000002_ERRNO_INT 1

	/* Event 908000003
		socket disconnect */
	/* Connect exception msg */
	#define E908000003_EXCEPTION_VARCHAR 0

	/* Event 908000004
		receive illegal packing command */
	/* EventId of illegal command */
	#define E908000004_RECVEVENTID_INT 0
	/* Error Command */
	#define E908000004_ERRORCOMMAND_VARCHAR 1

	/* Event 908000005
		log track */

	/* Event 908001001
		modem log status */
	/* Switch status */
	#define E908001001_STATUS_TINYINT 0

	/* Event 908001002
		tcpdump log status */
	/* Switch status */
	#define E908001002_STATUS_TINYINT 0

	/* Event 908001003
		gps log status */
	/* Switch status */
	#define E908001003_STATUS_TINYINT 0

	/* Event 908001004
		root status */
	/* Root status */
	#define E908001004_ROOTSTATUS_TINYINT 0

	/* Event 908001005
		system boot event */

	/* Event 908002001
		device information */
	/* Board id */
	#define E908002001_BOARDID_VARCHAR 0
	/* DDR info */
	#define E908002001_DDRINFO_VARCHAR 1
	/* EMMC info */
	#define E908002001_EMMCINFO_VARCHAR 2
	/* SOC name */
	#define E908002001_SOCNAME_VARCHAR 3

/*** Wifi events' keys ***/

	/* Event 909001001
		statistics of WiFi turn on/off, and wifi settings */
	/* sum of trying to turn wifi on */
	#define E909001001_OPENCOUNT_INT 0
	/* sum of wifi turned on */
	#define E909001001_OPENSUCCCOUNT_INT 1
	/* average time of turn wifi on */
	#define E909001001_OPENDURATION_INT 2
	/* sum of trying to turn wifi off */
	#define E909001001_CLOSECOUNT_INT 3
	/* sum of wifi turned off */
	#define E909001001_CLOSESUCCCOUNT_INT 4
	/* average time of turn wifi off */
	#define E909001001_CLOSEDURATION_INT 5
	/* settings of wifi pro */
	#define E909001001_ISWIFIPROON_BIT 6
	/* sum of switch the settings of wifi pro */
	#define E909001001_WIFIPROSWCNT_INT 7
	/* settings of scan always available */
	#define E909001001_ISSCANALWAYSAVAILBLE_BIT 8
	/* sum of switch the settings of scan always available */
	#define E909001001_SCANALWAYSSWCNT_INT 9
	/* settings of network notification */
	#define E909001001_ISWIFINOTIFATIONON_BIT 10
	/* sum of switch the settings of network notification */
	#define E909001001_WIFINOTIFATIONSWCNT_INT 11
	/* settings of keep wifi on during sleep */
	#define E909001001_WIFISLEEPPOLICY_TINYINT 12
	/* sum of switch the settings of sleep policy */
	#define E909001001_WIFISLEEPSWCNT_INT 13
	/* settings of WLAN&Mobile */
	#define E909001001_WIFITOPDP_TINYINT 14
	/* sum of switch the settings of WLAN&Mobile */
	#define E909001001_WIFITOPDPSWCNT_INT 15

	/* Event 909001002
		statistics of WiFi connection */
	/* SSID of an AP */
	#define E909001002_APSSID_VARCHAR 0
	/* sum of MAC with same SSID */
	#define E909001002_PUBLICESSCOUNT_TINYINT 1
	/* sum of association */
	#define E909001002_ASSOCCOUNT_SMALLINT 2
	/* sum of associated */
	#define E909001002_ASSOCSUCCCOUNT_SMALLINT 3
	/* sum of authentication */
	#define E909001002_AUTHCOUNT_SMALLINT 4
	/* sum of authenticated */
	#define E909001002_AUTHSUCCCOUNT_SMALLINT 5
	/* sum of dhcp */
	#define E909001002_IPDHCPCOUNT_SMALLINT 6
	/* sum of dhcp successfully */
	#define E909001002_DHCPSUCCCOUNT_SMALLINT 7
	/* sum of static IP */
	#define E909001002_IPSTATICCOUNT_SMALLINT 8
	/* sum of huawei auto IP */
	#define E909001002_IPAUTOCOUNT_SMALLINT 9
	/* sum of connection successful */
	#define E909001002_CONNECTEDCOUNT_SMALLINT 10
	/* sum of disconnection */
	#define E909001002_ABNORMALDISCONNCOUNT_SMALLINT 11
	/* duration of association */
	#define E909001002_ASSOCDURATION_INT 12
	/* duration of authentication */
	#define E909001002_AUTHDURATION_INT 13
	/* duration of dhcp */
	#define E909001002_DHCPDURATION_INT 14
	/* duration of connecting period */
	#define E909001002_CONNECTINGDURATION_INT 15
	/* duration of keep wifi connection */
	#define E909001002_CONNECTIONDURATION_INT 16
	/* sum of dns request */
	#define E909001002_DNSREQCNT_INT 17
	/* sum of dns fail */
	#define E909001002_DNSREQFAIL_INT 18
	/* average time of dns */
	#define E909001002_DNSAVGTIME_INT 19
	/* sum of dhcp renew */
	#define E909001002_DHCPRENEWCOUNT_INT 20
	/* sum of dhcp renew successfully */
	#define E909001002_DHCPRENEWSUCCCOUNT_INT 21
	/* duration of dhcp renew */
	#define E909001002_DHCPRENEWDURATION_INT 22
	/* sum of roaming */
	#define E909001002_ROAMINGCOUNT_INT 23
	/* sum of roaming successfully */
	#define E909001002_ROAMINGSUCCCOUNT_INT 24
	/* duration of roaming */
	#define E909001002_ROAMINGDURATION_INT 25
	/* sum of rekey */
	#define E909001002_REKEYCOUNT_INT 26
	/* sum of rekey successfully */
	#define E909001002_REKEYSUCCCOUNT_INT 27
	/* duration of rekey */
	#define E909001002_REKEYDURATION_INT 28
	/* sum of access internet fail */
	#define E909001002_ACCESSWEBFAILCNT_SMALLINT 29
	/* sum of access internet slowly */
	#define E909001002_ACCESSWEBSLOWLYCNT_SMALLINT 30
	/* sum of gateway IP in the LAN */
	#define E909001002_GWIPCOUNT_TINYINT 31
	/* sum of gateway MAC with same IP in the LAN */
	#define E909001002_GWMACCOUNT_TINYINT 32
	/* average rssi during connection */
	#define E909001002_RSSIAVG_INT 33

	/* Event 909002001
		exception of WiFi turn on/off */
	/* errorCode */
	#define E909002001_ERRORCODE_TINYINT 0
	/* subStatusCode */
	#define E909002001_SUBSTATUSCODE_TINYINT 1
	/* state of bt on or off */
	#define E909002001_ISBTSTATEON_BIT 2

	/* Event 909002002
		exception of WiFi scan */
	/* errorCode */
	#define E909002002_ERRORCODE_TINYINT 0
	/* subStatusCode */
	#define E909002002_SUBSTATUSCODE_TINYINT 1
	/* state of bt on or off */
	#define E909002002_ISBTSTATEON_BIT 2
	/* state of station connection */
	#define E909002002_ISWIFISTACONNECTED_BIT 3
	/* state of p2p connection */
	#define E909002002_ISWIFIP2PCONNECTED_BIT 4
	/* as p2p Go or Gc */
	#define E909002002_ISWIFIP2PGO_BIT 5

	/* Event 909002003
		user connection */
	/* errorCode */
	#define E909002003_ERRORCODE_TINYINT 0
	/* subStatusCode */
	#define E909002003_SUBSTATUSCODE_TINYINT 1
	/* failure info */
	#define E909002003_FAILUREINFO_VARCHAR 2
	/* WiFi MAC of the AP */
	#define E909002003_APMAC_VARCHAR 3
	/* SSID of an AP */
	#define E909002003_APSSID_VARCHAR 4
	/* vendor info of an AP */
	#define E909002003_APVENDORINFO_VARCHAR 5
	/* work channel of an AP */
	#define E909002003_APCHANNEL_SMALLINT 6
	/* the access security of an AP */
	#define E909002003_APSECURITY_SMALLINT 7
	/* the security protocol of an AP */
	#define E909002003_APPROTO_SMALLINT 8
	/* the key management scheme of an AP */
	#define E909002003_APKEYMGMT_SMALLINT 9
	/* the authentication algorithm of an AP */
	#define E909002003_APAUTHALG_SMALLINT 10
	/* the pairwise cipher for WPA */
	#define E909002003_APPAIRWISE_SMALLINT 11
	/* the group cipher of an AP */
	#define E909002003_APGROUP_SMALLINT 12
	/* the EAP method of an AP */
	#define E909002003_APEAP_SMALLINT 13
	/* signal strength of an AP */
	#define E909002003_APRSSI_SMALLINT 14
	/* signal strength of an AP after connected */
	#define E909002003_APRSSICONNECTED_SMALLINT 15
	/* sum of MAC with same SSID */
	#define E909002003_PUBLICESSCOUNT_TINYINT 16
	/* rssi of available roaming AP */
	#define E909002003_APROAMINGRSSI_SMALLINT 17
	/* channel of available roaming AP */
	#define E909002003_APROAMINGCHANNEL_SMALLINT 18
	/* num of Aps with 1 signal bar in the same channel */
	#define E909002003_APNEARBYS1_TINYINT 19
	/* num of Aps with 2 signal bar in the same channel */
	#define E909002003_APNEARBYS2_TINYINT 20
	/* num of Aps with 3 signal bar in the same channel */
	#define E909002003_APNEARBYS3_TINYINT 21
	/* num of Aps with 4 signal bar in the same channel */
	#define E909002003_APNEARBYS4_TINYINT 22
	/* num of Aps with 1 signal bar in the next channel */
	#define E909002003_APNEARBYN1_TINYINT 23
	/* num of Aps with 2 signal bar in the next channel */
	#define E909002003_APNEARBYN2_TINYINT 24
	/* num of Aps with 3 signal bar in the next channel */
	#define E909002003_APNEARBYN3_TINYINT 25
	/* num of Aps with 4 signal bar in the next channel */
	#define E909002003_APNEARBYN4_TINYINT 26
	/* state of bt on or off */
	#define E909002003_ISBTSTATEON_BIT 27
	/* state of p2p connection */
	#define E909002003_ISWIFIP2PCONNECTED_BIT 28
	/* as p2p Go or Gc */
	#define E909002003_ISWIFIP2PGO_BIT 29
	/* method of get IP */
	#define E909002003_IPINFOTYPE_TINYINT 30
	/* sum of association retry */
	#define E909002003_ASSOCRETRYCNT_TINYINT 31
	/* sum of authentication retry */
	#define E909002003_AUTHRETRYCNT_TINYINT 32
	/* sum of dhcp retry */
	#define E909002003_DHCPRETRYCNT_TINYINT 33
	/* sum of switch to disconnection state */
	#define E909002003_DISCSTATESWTICHCNT_TINYINT 34
	/* duration of connecting period */
	#define E909002003_CONNECTINGDURATION_INT 35

	/* Event 909002004
		exception during WiFi association */
	/* errorCode */
	#define E909002004_ERRORCODE_TINYINT 0
	/* subStatusCode */
	#define E909002004_SUBSTATUSCODE_TINYINT 1
	/* WiFi MAC of the AP */
	#define E909002004_APMAC_VARCHAR 2
	/* SSID of an AP */
	#define E909002004_APSSID_VARCHAR 3
	/* vendor info of an AP */
	#define E909002004_APVENDORINFO_VARCHAR 4
	/* work channel of an AP */
	#define E909002004_APCHANNEL_SMALLINT 5
	/* the access security of an AP */
	#define E909002004_APSECURITY_SMALLINT 6
	/* the security protocol of an AP */
	#define E909002004_APPROTO_SMALLINT 7
	/* the key management scheme of an AP */
	#define E909002004_APKEYMGMT_SMALLINT 8
	/* the authentication algorithm of an AP */
	#define E909002004_APAUTHALG_SMALLINT 9
	/* the pairwise cipher for WPA */
	#define E909002004_APPAIRWISE_SMALLINT 10
	/* the group cipher of an AP */
	#define E909002004_APGROUP_SMALLINT 11
	/* the EAP method of an AP */
	#define E909002004_APEAP_SMALLINT 12
	/* signal strength of an AP */
	#define E909002004_APRSSI_SMALLINT 13
	/* sum of MAC with same SSID */
	#define E909002004_PUBLICESSCOUNT_TINYINT 14
	/* rssi of available roaming AP */
	#define E909002004_APROAMINGRSSI_SMALLINT 15
	/* channel of available roaming AP */
	#define E909002004_APROAMINGCHANNEL_SMALLINT 16
	/* num of Aps with 1 signal bar in the same channel */
	#define E909002004_APNEARBYS1_TINYINT 17
	/* num of Aps with 2 signal bar in the same channel */
	#define E909002004_APNEARBYS2_TINYINT 18
	/* num of Aps with 3 signal bar in the same channel */
	#define E909002004_APNEARBYS3_TINYINT 19
	/* num of Aps with 4 signal bar in the same channel */
	#define E909002004_APNEARBYS4_TINYINT 20
	/* num of Aps with 1 signal bar in the next channel */
	#define E909002004_APNEARBYN1_TINYINT 21
	/* num of Aps with 2 signal bar in the next channel */
	#define E909002004_APNEARBYN2_TINYINT 22
	/* num of Aps with 3 signal bar in the next channel */
	#define E909002004_APNEARBYN3_TINYINT 23
	/* num of Aps with 4 signal bar in the next channel */
	#define E909002004_APNEARBYN4_TINYINT 24
	/* state of bt on or off */
	#define E909002004_ISBTSTATEON_BIT 25
	/* state of p2p connection */
	#define E909002004_ISWIFIP2PCONNECTED_BIT 26
	/* as p2p Go or Gc */
	#define E909002004_ISWIFIP2PGO_BIT 27
	/* isScreenOn */
	#define E909002004_ISSCREENON_BIT 28

	/* Event 909002005
		exception during WiFi authentication */
	/* errorCode */
	#define E909002005_ERRORCODE_TINYINT 0
	/* subStatusCode */
	#define E909002005_SUBSTATUSCODE_TINYINT 1
	/* WiFi MAC of the AP */
	#define E909002005_APMAC_VARCHAR 2
	/* SSID of an AP */
	#define E909002005_APSSID_VARCHAR 3
	/* vendor info of an AP */
	#define E909002005_APVENDORINFO_VARCHAR 4
	/* work channel of an AP */
	#define E909002005_APCHANNEL_SMALLINT 5
	/* the access security of an AP */
	#define E909002005_APSECURITY_SMALLINT 6
	/* the security protocol of an AP */
	#define E909002005_APPROTO_SMALLINT 7
	/* the key management scheme of an AP */
	#define E909002005_APKEYMGMT_SMALLINT 8
	/* the authentication algorithm of an AP */
	#define E909002005_APAUTHALG_SMALLINT 9
	/* the pairwise cipher for WPA */
	#define E909002005_APPAIRWISE_SMALLINT 10
	/* the group cipher of an AP */
	#define E909002005_APGROUP_SMALLINT 11
	/* the EAP method of an AP */
	#define E909002005_APEAP_SMALLINT 12
	/* signal strength of an AP */
	#define E909002005_APRSSI_SMALLINT 13
	/* sum of MAC with same SSID */
	#define E909002005_PUBLICESSCOUNT_TINYINT 14
	/* rssi of available roaming AP */
	#define E909002005_APROAMINGRSSI_SMALLINT 15
	/* channel of available roaming AP */
	#define E909002005_APROAMINGCHANNEL_SMALLINT 16
	/* num of Aps with 1 signal bar in the same channel */
	#define E909002005_APNEARBYS1_TINYINT 17
	/* num of Aps with 2 signal bar in the same channel */
	#define E909002005_APNEARBYS2_TINYINT 18
	/* num of Aps with 3 signal bar in the same channel */
	#define E909002005_APNEARBYS3_TINYINT 19
	/* num of Aps with 4 signal bar in the same channel */
	#define E909002005_APNEARBYS4_TINYINT 20
	/* num of Aps with 1 signal bar in the next channel */
	#define E909002005_APNEARBYN1_TINYINT 21
	/* num of Aps with 2 signal bar in the next channel */
	#define E909002005_APNEARBYN2_TINYINT 22
	/* num of Aps with 3 signal bar in the next channel */
	#define E909002005_APNEARBYN3_TINYINT 23
	/* num of Aps with 4 signal bar in the next channel */
	#define E909002005_APNEARBYN4_TINYINT 24
	/* state of bt on or off */
	#define E909002005_ISBTSTATEON_BIT 25
	/* state of p2p connection */
	#define E909002005_ISWIFIP2PCONNECTED_BIT 26
	/* as p2p Go or Gc */
	#define E909002005_ISWIFIP2PGO_BIT 27
	/* isScreenOn */
	#define E909002005_ISSCREENON_BIT 28

	/* Event 909002006
		exception during WiFi DHCP */
	/* errorCode */
	#define E909002006_ERRORCODE_TINYINT 0
	/* subStatusCode */
	#define E909002006_SUBSTATUSCODE_TINYINT 1
	/* WiFi MAC of the AP */
	#define E909002006_APMAC_VARCHAR 2
	/* SSID of an AP */
	#define E909002006_APSSID_VARCHAR 3
	/* vendor info of an AP */
	#define E909002006_APVENDORINFO_VARCHAR 4
	/* work channel of an AP */
	#define E909002006_APCHANNEL_SMALLINT 5
	/* the access security of an AP */
	#define E909002006_APSECURITY_SMALLINT 6
	/* the security protocol of an AP */
	#define E909002006_APPROTO_SMALLINT 7
	/* the key management scheme of an AP */
	#define E909002006_APKEYMGMT_SMALLINT 8
	/* the authentication algorithm of an AP */
	#define E909002006_APAUTHALG_SMALLINT 9
	/* the pairwise cipher for WPA */
	#define E909002006_APPAIRWISE_SMALLINT 10
	/* the group cipher of an AP */
	#define E909002006_APGROUP_SMALLINT 11
	/* the EAP method of an AP */
	#define E909002006_APEAP_SMALLINT 12
	/* signal strength of an AP */
	#define E909002006_APRSSI_SMALLINT 13
	/* sum of MAC with same SSID */
	#define E909002006_PUBLICESSCOUNT_TINYINT 14
	/* rssi of available roaming AP */
	#define E909002006_APROAMINGRSSI_SMALLINT 15
	/* channel of available roaming AP */
	#define E909002006_APROAMINGCHANNEL_SMALLINT 16
	/* num of Aps with 1 signal bar in the same channel */
	#define E909002006_APNEARBYS1_TINYINT 17
	/* num of Aps with 2 signal bar in the same channel */
	#define E909002006_APNEARBYS2_TINYINT 18
	/* num of Aps with 3 signal bar in the same channel */
	#define E909002006_APNEARBYS3_TINYINT 19
	/* num of Aps with 4 signal bar in the same channel */
	#define E909002006_APNEARBYS4_TINYINT 20
	/* num of Aps with 1 signal bar in the next channel */
	#define E909002006_APNEARBYN1_TINYINT 21
	/* num of Aps with 2 signal bar in the next channel */
	#define E909002006_APNEARBYN2_TINYINT 22
	/* num of Aps with 3 signal bar in the next channel */
	#define E909002006_APNEARBYN3_TINYINT 23
	/* num of Aps with 4 signal bar in the next channel */
	#define E909002006_APNEARBYN4_TINYINT 24
	/* sum of gateway IP in the LAN */
	#define E909002006_GWIPCOUNT_TINYINT 25
	/* sum of gateway MAC with same IP in the LAN */
	#define E909002006_GWMACCOUNT_TINYINT 26
	/* state of bt on or off */
	#define E909002006_ISBTSTATEON_BIT 27
	/* state of p2p connection */
	#define E909002006_ISWIFIP2PCONNECTED_BIT 28
	/* as p2p Go or Gc */
	#define E909002006_ISWIFIP2PGO_BIT 29
	/* isScreenOn */
	#define E909002006_ISSCREENON_BIT 30

	/* Event 909002007
		exception of the device can not access the internet
		after WiFi connection, without public IP info */
	/* errorCode */
	#define E909002007_ERRORCODE_TINYINT 0
	/* subStatusCode */
	#define E909002007_SUBSTATUSCODE_TINYINT 1
	/* WiFi MAC of the AP */
	#define E909002007_APMAC_VARCHAR 2
	/* SSID of an AP */
	#define E909002007_APSSID_VARCHAR 3
	/* vendor info of an AP */
	#define E909002007_APVENDORINFO_VARCHAR 4
	/* sum of gateway IP in the LAN */
	#define E909002007_GWIPCOUNT_TINYINT 5
	/* sum of gateway MAC with same IP in the LAN */
	#define E909002007_GWMACCOUNT_TINYINT 6
	/* sum of MAC with same SSID */
	#define E909002007_PUBLICESSCOUNT_TINYINT 7
	/* the access security of an AP */
	#define E909002007_APSECURITY_SMALLINT 8
	/* the security protocol of an AP */
	#define E909002007_APPROTO_SMALLINT 9
	/* the key management scheme of an AP */
	#define E909002007_APKEYMGMT_SMALLINT 10
	/* the authentication algorithm of an AP */
	#define E909002007_APAUTHALG_SMALLINT 11
	/* the pairwise cipher for WPA */
	#define E909002007_APPAIRWISE_SMALLINT 12
	/* the group cipher of an AP */
	#define E909002007_APGROUP_SMALLINT 13
	/* the EAP method of an AP */
	#define E909002007_APEAP_SMALLINT 14
	/* work channel of an AP */
	#define E909002007_APCHANNEL_SMALLINT 15
	/* num of Aps with 1 signal bar in the same channel */
	#define E909002007_APNEARBYS1_TINYINT 16
	/* num of Aps with 2 signal bar in the same channel */
	#define E909002007_APNEARBYS2_TINYINT 17
	/* num of Aps with 3 signal bar in the same channel */
	#define E909002007_APNEARBYS3_TINYINT 18
	/* num of Aps with 4 signal bar in the same channel */
	#define E909002007_APNEARBYS4_TINYINT 19
	/* num of Aps with 1 signal bar in the next channel */
	#define E909002007_APNEARBYN1_TINYINT 20
	/* num of Aps with 2 signal bar in the next channel */
	#define E909002007_APNEARBYN2_TINYINT 21
	/* num of Aps with 3 signal bar in the next channel */
	#define E909002007_APNEARBYN3_TINYINT 22
	/* num of Aps with 4 signal bar in the next channel */
	#define E909002007_APNEARBYN4_TINYINT 23
	/* signal strength of an AP */
	#define E909002007_APRSSI_SMALLINT 24
	/* link speed of an AP */
	#define E909002007_APLINKSPEED_SMALLINT 25
	/* state of bt on or off */
	#define E909002007_ISBTSTATEON_BIT 26
	/* sum of connected bt devices */
	#define E909002007_BTSTATEDEVICES_TINYINT 27
	/* state of bt a2dp */
	#define E909002007_ISBTSTATEA2DP_BIT 28
	/* state of bt voice */
	#define E909002007_ISBTSTATEVOICE_BIT 29
	/* state of bt file transfer */
	#define E909002007_ISBTSTATEOPP_BIT 30
	/* method of get IP */
	#define E909002007_IPINFOTYPE_TINYINT 31
	/* IP address of the device */
	#define E909002007_IPINFOADDR_VARCHAR 32
	/* IP mask */
	#define E909002007_IPINFOMASK_TINYINT 33
	/* the address of gateway */
	#define E909002007_IPINFOGATEWAY_VARCHAR 34
	/* DNS server */
	#define E909002007_IPINFODNS_VARCHAR 35
	/* IP leasetime */
	#define E909002007_IPINFOLEASETIME_INT 36
	/* the status of proxy */
	#define E909002007_IPINFOPROXY_TINYINT 37
	/* the status of vpn */
	#define E909002007_IPINFOVPN_TINYINT 38
	/* country code for WiFi chipset */
	#define E909002007_COUNTRYCODE_VARCHAR 39
	/* mcc of cell */
	#define E909002007_CELLIDMCC_INT 40
	/* mnc of cell */
	#define E909002007_CELLIDMNC_INT 41
	/* lac of cell */
	#define E909002007_CELLIDLAC_INT 42
	/* cid of cell */
	#define E909002007_CELLIDCID_INT 43
	/* the time period from connectied time to exception */
	#define E909002007_DURATIONEXCEPTION_INT 44
	/* sum of all packages tx successfully */
	#define E909002007_PACKETCOUNTTXGOOD_INT 45
	/* sum of all packages tx fail */
	#define E909002007_PACKETCOUNTTXBAD_INT 46
	/* sum of all packages rx */
	#define E909002007_PACKETCOUNTRXGOOD_INT 47
	/* sum of tcp rx */
	#define E909002007_TCPINFORX_INT 48
	/* sum of tcp tx */
	#define E909002007_TCPINFOTX_INT 49
	/* sum of tcp tx retrans */
	#define E909002007_TCPINFORETRANS_INT 50
	/* sum of tcp rtt of all packages */
	#define E909002007_TCPINFORTTTOTAL_INT 51
	/* sum of tcp rtt during detect period */
	#define E909002007_TCPINFORTTSAMPLE_INT 52
	/* rtt during period with 1 bar signal strength */
	#define E909002007_RTTSIGNAL1BAR_INT 53
	/* rtt during period with 2 bar signal strength */
	#define E909002007_RTTSIGNAL2BAR_INT 54
	/* rtt during period with 3 bar signal strength */
	#define E909002007_RTTSIGNAL3BAR_INT 55
	/* rtt during period with 4 bar signal strength */
	#define E909002007_RTTSIGNAL4BAR_INT 56
	/* sum of dns request */
	#define E909002007_DNSREQCNT_INT 57
	/* sum of dns fail */
	#define E909002007_DNSREQFAIL_INT 58
	/* average time of dns */
	#define E909002007_DNSAVGTIME_INT 59
	/* sum of cmd52 read request */
	#define E909002007_SDIOINFOCMD52RDREQ_INT 60
	/* sum of cmd52 read total */
	#define E909002007_SDIOINFOCMD52RDTOTAL_INT 61
	/* sum of cmd52 write request */
	#define E909002007_SDIOINFOCMD52WTREQ_INT 62
	/* sum of cmd52 write total */
	#define E909002007_SDIOINFOCMD52WTTOTAL_INT 63
	/* sum of cmd53 read request */
	#define E909002007_SDIOINFOCMD53RDREQ_INT 64
	/* sum of cmd53 read total */
	#define E909002007_SDIOINFOCMD53RDTOTAL_INT 65
	/* sum of cmd53 write request */
	#define E909002007_SDIOINFOCMD53WTREQ_INT 66
	/* sum of cmd53 write total */
	#define E909002007_SDIOINFOCMD53WTTOTAL_INT 67
	/* sum of kso set request */
	#define E909002007_SDIOINFOKSOSETREQ_INT 68
	/* sum of kso set total */
	#define E909002007_SDIOINFOKSOSETRETRY_INT 69
	/* sum of kso clear request */
	#define E909002007_SDIOINFOKSOCLRREQ_INT 70
	/* sum of kso clear total */
	#define E909002007_SDIOINFOKSOCLRRETRY_INT 71
	/* period of calculate the wl counters */
	#define E909002007_WLCNTERSMONITORDURATION_INT 72
	/* txallfrm */
	#define E909002007_WLCNTERSTXALLFRM_INT 73
	/* txframe */
	#define E909002007_WLCNTERSTXFRAME_INT 74
	/* txbytes */
	#define E909002007_WLCNTERSTXBYTES_INT 75
	/* txretrans */
	#define E909002007_WLCNTERSTXRETRANS_INT 76
	/* txerror */
	#define E909002007_WLCNTERSTXERROR_INT 77
	/* txfail */
	#define E909002007_WLCNTERSTXFAIL_INT 78
	/* txfrag */
	#define E909002007_WLCNTERSTXFRAG_INT 79
	/* txfrmsnt */
	#define E909002007_WLCNTERSTXFRMSNT_INT 80
	/* txnoack */
	#define E909002007_WLCNTERSTXNOACK_INT 81
	/* rxframe */
	#define E909002007_WLCNTERSRXFRAME_INT 82
	/* rxbytes */
	#define E909002007_WLCNTERSRXBYTES_INT 83
	/* rxfrag */
	#define E909002007_WLCNTERSRXFRAG_INT 84
	/* rxbadfcs */
	#define E909002007_WLCNTERSRXBADFCS_INT 85
	/* rxbadplcp */
	#define E909002007_WLCNTERSRXBADPLCP_INT 86
	/* rxnobuf */
	#define E909002007_WLCNTERSRXNOBUF_INT 87
	/* rxcrsglitch */
	#define E909002007_WLCNTERSRXCRSGLITCH_INT 88
	/* rxbadproto */
	#define E909002007_WLCNTERSRXBADPROTO_INT 89
	/* rxbadcm */
	#define E909002007_WLCNTERSRXBADCM_INT 90
	/* rxctl */
	#define E909002007_WLCNTERSRXCTL_INT 91
	/* rxmulti */
	#define E909002007_WLCNTERSRXMULTI_INT 92
	/* rxnondata */
	#define E909002007_WLCNTERSRXNONDATA_INT 93
	/* rxbadds */
	#define E909002007_WLCNTERSRXBADDS_INT 94
	/* reset */
	#define E909002007_WLCNTERSRESET_INT 95
	/* rxstrt */
	#define E909002007_WLCNTERSRXSTRT_INT 96
	/* rxdfrmocast */
	#define E909002007_WLCNTERSRXDFRMOCAST_INT 97
	/* rxmfrmocast */
	#define E909002007_WLCNTERSRXMFRMOCAST_INT 98
	/* rxcfrmocast */
	#define E909002007_WLCNTERSRXCFRMOCAST_INT 99
	/* rxdfrmucastmbss */
	#define E909002007_WLCNTERSRXDFRMUCASTMBSS_INT 100
	/* rxmfrmucastmbss */
	#define E909002007_WLCNTERSRXMFRMUCASTMBSS_INT 101
	/* rxcfrmucast */
	#define E909002007_WLCNTERSRXCFRMUCAST_INT 102
	/* rxdfrmmcast */
	#define E909002007_WLCNTERSRXDFRMMCAST_INT 103
	/* rxmfrmmcast */
	#define E909002007_WLCNTERSRXMFRMMCAST_INT 104
	/* rxcfrmmcast */
	#define E909002007_WLCNTERSRXCFRMMCAST_INT 105
	/* rtt of arp detection */
	#define E909002007_DETECTRTTARP_INT 106
	/* rtt of visit www.baidu.com */
	#define E909002007_DETECTRTTBAIDU_INT 107
	/* whether or not receive tcp packages after resume */
	#define E909002007_HASTRAFFICAFTERSUSPEND_BIT 108
	/* the front 5 records of route table all */
	#define E909002007_IPROUTE_VARCHAR 109
	/* the recent 5 apps suspend in backgroud and forbidden
		use wifi network */
	#define E909002007_IPFIREWALL_VARCHAR 110
	/* whether or not portal registered */
	#define E909002007_ISPORTALREGED_BIT 111
	/* isScreenOn */
	#define E909002007_ISSCREENON_BIT 112

	/* Event 909202007
		exception of the device can not access the internet
		after WiFi connection */
	/* errorCode */
	#define E909202007_ERRORCODE_TINYINT 0
	/* subStatusCode */
	#define E909202007_SUBSTATUSCODE_TINYINT 1
	/* WiFi MAC of the AP */
	#define E909202007_APMAC_VARCHAR 2
	/* SSID of an AP */
	#define E909202007_APSSID_VARCHAR 3
	/* vendor info of an AP */
	#define E909202007_APVENDORINFO_VARCHAR 4
	/* sum of gateway IP in the LAN */
	#define E909202007_GWIPCOUNT_TINYINT 5
	/* sum of gateway MAC with same IP in the LAN */
	#define E909202007_GWMACCOUNT_TINYINT 6
	/* sum of MAC with same SSID */
	#define E909202007_PUBLICESSCOUNT_TINYINT 7
	/* the access security of an AP */
	#define E909202007_APSECURITY_SMALLINT 8
	/* the security protocol of an AP */
	#define E909202007_APPROTO_SMALLINT 9
	/* the key management scheme of an AP */
	#define E909202007_APKEYMGMT_SMALLINT 10
	/* the authentication algorithm of an AP */
	#define E909202007_APAUTHALG_SMALLINT 11
	/* the pairwise cipher for WPA */
	#define E909202007_APPAIRWISE_SMALLINT 12
	/* the group cipher of an AP */
	#define E909202007_APGROUP_SMALLINT 13
	/* the EAP method of an AP */
	#define E909202007_APEAP_SMALLINT 14
	/* work channel of an AP */
	#define E909202007_APCHANNEL_SMALLINT 15
	/* num of Aps with 1 signal bar in the same channel */
	#define E909202007_APNEARBYS1_TINYINT 16
	/* num of Aps with 2 signal bar in the same channel */
	#define E909202007_APNEARBYS2_TINYINT 17
	/* num of Aps with 3 signal bar in the same channel */
	#define E909202007_APNEARBYS3_TINYINT 18
	/* num of Aps with 4 signal bar in the same channel */
	#define E909202007_APNEARBYS4_TINYINT 19
	/* num of Aps with 1 signal bar in the next channel */
	#define E909202007_APNEARBYN1_TINYINT 20
	/* num of Aps with 2 signal bar in the next channel */
	#define E909202007_APNEARBYN2_TINYINT 21
	/* num of Aps with 3 signal bar in the next channel */
	#define E909202007_APNEARBYN3_TINYINT 22
	/* num of Aps with 4 signal bar in the next channel */
	#define E909202007_APNEARBYN4_TINYINT 23
	/* signal strength of an AP */
	#define E909202007_APRSSI_SMALLINT 24
	/* link speed of an AP */
	#define E909202007_APLINKSPEED_SMALLINT 25
	/* state of bt on or off */
	#define E909202007_ISBTSTATEON_BIT 26
	/* sum of connected bt devices */
	#define E909202007_BTSTATEDEVICES_TINYINT 27
	/* state of bt a2dp */
	#define E909202007_ISBTSTATEA2DP_BIT 28
	/* state of bt voice */
	#define E909202007_ISBTSTATEVOICE_BIT 29
	/* state of bt file transfer */
	#define E909202007_ISBTSTATEOPP_BIT 30
	/* method of get IP */
	#define E909202007_IPINFOTYPE_TINYINT 31
	/* IP address of the device */
	#define E909202007_IPINFOADDR_VARCHAR 32
	/* IP mask */
	#define E909202007_IPINFOMASK_TINYINT 33
	/* the address of gateway */
	#define E909202007_IPINFOGATEWAY_VARCHAR 34
	/* DNS server */
	#define E909202007_IPINFODNS_VARCHAR 35
	/* IP leasetime */
	#define E909202007_IPINFOLEASETIME_INT 36
	/* the status of proxy */
	#define E909202007_IPINFOPROXY_TINYINT 37
	/* the status of vpn */
	#define E909202007_IPINFOVPN_TINYINT 38
	/* the public IP and address of wifi network for access
		the internet */
	#define E909202007_IPPUBLICINFO_VARCHAR 39
	/* country code for WiFi chipset */
	#define E909202007_COUNTRYCODE_VARCHAR 40
	/* mcc of cell */
	#define E909202007_CELLIDMCC_INT 41
	/* mnc of cell */
	#define E909202007_CELLIDMNC_INT 42
	/* lac of cell */
	#define E909202007_CELLIDLAC_INT 43
	/* cid of cell */
	#define E909202007_CELLIDCID_INT 44
	/* the time period from connectied time to exception */
	#define E909202007_DURATIONEXCEPTION_INT 45
	/* sum of all packages tx successfully */
	#define E909202007_PACKETCOUNTTXGOOD_INT 46
	/* sum of all packages tx fail */
	#define E909202007_PACKETCOUNTTXBAD_INT 47
	/* sum of all packages rx */
	#define E909202007_PACKETCOUNTRXGOOD_INT 48
	/* sum of tcp rx */
	#define E909202007_TCPINFORX_INT 49
	/* sum of tcp tx */
	#define E909202007_TCPINFOTX_INT 50
	/* sum of tcp tx retrans */
	#define E909202007_TCPINFORETRANS_INT 51
	/* sum of tcp rtt of all packages */
	#define E909202007_TCPINFORTTTOTAL_INT 52
	/* sum of tcp rtt during detect period */
	#define E909202007_TCPINFORTTSAMPLE_INT 53
	/* rtt during period with 1 bar signal strength */
	#define E909202007_RTTSIGNAL1BAR_INT 54
	/* rtt during period with 2 bar signal strength */
	#define E909202007_RTTSIGNAL2BAR_INT 55
	/* rtt during period with 3 bar signal strength */
	#define E909202007_RTTSIGNAL3BAR_INT 56
	/* rtt during period with 4 bar signal strength */
	#define E909202007_RTTSIGNAL4BAR_INT 57
	/* sum of dns request */
	#define E909202007_DNSREQCNT_INT 58
	/* sum of dns fail */
	#define E909202007_DNSREQFAIL_INT 59
	/* average time of dns */
	#define E909202007_DNSAVGTIME_INT 60
	/* sum of cmd52 read request */
	#define E909202007_SDIOINFOCMD52RDREQ_INT 61
	/* sum of cmd52 read total */
	#define E909202007_SDIOINFOCMD52RDTOTAL_INT 62
	/* sum of cmd52 write request */
	#define E909202007_SDIOINFOCMD52WTREQ_INT 63
	/* sum of cmd52 write total */
	#define E909202007_SDIOINFOCMD52WTTOTAL_INT 64
	/* sum of cmd53 read request */
	#define E909202007_SDIOINFOCMD53RDREQ_INT 65
	/* sum of cmd53 read total */
	#define E909202007_SDIOINFOCMD53RDTOTAL_INT 66
	/* sum of cmd53 write request */
	#define E909202007_SDIOINFOCMD53WTREQ_INT 67
	/* sum of cmd53 write total */
	#define E909202007_SDIOINFOCMD53WTTOTAL_INT 68
	/* sum of kso set request */
	#define E909202007_SDIOINFOKSOSETREQ_INT 69
	/* sum of kso set total */
	#define E909202007_SDIOINFOKSOSETRETRY_INT 70
	/* sum of kso clear request */
	#define E909202007_SDIOINFOKSOCLRREQ_INT 71
	/* sum of kso clear total */
	#define E909202007_SDIOINFOKSOCLRRETRY_INT 72
	/* period of calculate the wl counters */
	#define E909202007_WLCNTERSMONITORDURATION_INT 73
	/* txallfrm */
	#define E909202007_WLCNTERSTXALLFRM_INT 74
	/* txframe */
	#define E909202007_WLCNTERSTXFRAME_INT 75
	/* txbytes */
	#define E909202007_WLCNTERSTXBYTES_INT 76
	/* txretrans */
	#define E909202007_WLCNTERSTXRETRANS_INT 77
	/* txerror */
	#define E909202007_WLCNTERSTXERROR_INT 78
	/* txfail */
	#define E909202007_WLCNTERSTXFAIL_INT 79
	/* txfrag */
	#define E909202007_WLCNTERSTXFRAG_INT 80
	/* txfrmsnt */
	#define E909202007_WLCNTERSTXFRMSNT_INT 81
	/* txnoack */
	#define E909202007_WLCNTERSTXNOACK_INT 82
	/* rxframe */
	#define E909202007_WLCNTERSRXFRAME_INT 83
	/* rxbytes */
	#define E909202007_WLCNTERSRXBYTES_INT 84
	/* rxfrag */
	#define E909202007_WLCNTERSRXFRAG_INT 85
	/* rxbadfcs */
	#define E909202007_WLCNTERSRXBADFCS_INT 86
	/* rxbadplcp */
	#define E909202007_WLCNTERSRXBADPLCP_INT 87
	/* rxnobuf */
	#define E909202007_WLCNTERSRXNOBUF_INT 88
	/* rxcrsglitch */
	#define E909202007_WLCNTERSRXCRSGLITCH_INT 89
	/* rxbadproto */
	#define E909202007_WLCNTERSRXBADPROTO_INT 90
	/* rxbadcm */
	#define E909202007_WLCNTERSRXBADCM_INT 91
	/* rxctl */
	#define E909202007_WLCNTERSRXCTL_INT 92
	/* rxmulti */
	#define E909202007_WLCNTERSRXMULTI_INT 93
	/* rxnondata */
	#define E909202007_WLCNTERSRXNONDATA_INT 94
	/* rxbadds */
	#define E909202007_WLCNTERSRXBADDS_INT 95
	/* reset */
	#define E909202007_WLCNTERSRESET_INT 96
	/* rxstrt */
	#define E909202007_WLCNTERSRXSTRT_INT 97
	/* rxdfrmocast */
	#define E909202007_WLCNTERSRXDFRMOCAST_INT 98
	/* rxmfrmocast */
	#define E909202007_WLCNTERSRXMFRMOCAST_INT 99
	/* rxcfrmocast */
	#define E909202007_WLCNTERSRXCFRMOCAST_INT 100
	/* rxdfrmucastmbss */
	#define E909202007_WLCNTERSRXDFRMUCASTMBSS_INT 101
	/* rxmfrmucastmbss */
	#define E909202007_WLCNTERSRXMFRMUCASTMBSS_INT 102
	/* rxcfrmucast */
	#define E909202007_WLCNTERSRXCFRMUCAST_INT 103
	/* rxdfrmmcast */
	#define E909202007_WLCNTERSRXDFRMMCAST_INT 104
	/* rxmfrmmcast */
	#define E909202007_WLCNTERSRXMFRMMCAST_INT 105
	/* rxcfrmmcast */
	#define E909202007_WLCNTERSRXCFRMMCAST_INT 106
	/* rtt of arp detection */
	#define E909202007_DETECTRTTARP_INT 107
	/* rtt of visit www.baidu.com */
	#define E909202007_DETECTRTTBAIDU_INT 108
	/* whether or not receive tcp packages after resume */
	#define E909202007_HASTRAFFICAFTERSUSPEND_BIT 109
	/* the front 5 records of route table all */
	#define E909202007_IPROUTE_VARCHAR 110
	/* the recent 5 apps suspend in backgroud and forbidden
		use wifi network */
	#define E909202007_IPFIREWALL_VARCHAR 111
	/* whether or not portal registered */
	#define E909202007_ISPORTALREGED_BIT 112
	/* isScreenOn */
	#define E909202007_ISSCREENON_BIT 113

	/* Event 909002008
		exception of the device access the internet slowly
		via WiFi network, without public IP info */
	/* errorCode */
	#define E909002008_ERRORCODE_TINYINT 0
	/* subStatusCode */
	#define E909002008_SUBSTATUSCODE_TINYINT 1
	/* WiFi MAC of the AP */
	#define E909002008_APMAC_VARCHAR 2
	/* SSID of an AP */
	#define E909002008_APSSID_VARCHAR 3
	/* vendor info of an AP */
	#define E909002008_APVENDORINFO_VARCHAR 4
	/* sum of gateway IP in the LAN */
	#define E909002008_GWIPCOUNT_TINYINT 5
	/* sum of gateway MAC with same IP in the LAN */
	#define E909002008_GWMACCOUNT_TINYINT 6
	/* sum of MAC with same SSID */
	#define E909002008_PUBLICESSCOUNT_TINYINT 7
	/* the access security of an AP */
	#define E909002008_APSECURITY_SMALLINT 8
	/* the security protocol of an AP */
	#define E909002008_APPROTO_SMALLINT 9
	/* the key management scheme of an AP */
	#define E909002008_APKEYMGMT_SMALLINT 10
	/* the authentication algorithm of an AP */
	#define E909002008_APAUTHALG_SMALLINT 11
	/* the pairwise cipher for WPA */
	#define E909002008_APPAIRWISE_SMALLINT 12
	/* the group cipher of an AP */
	#define E909002008_APGROUP_SMALLINT 13
	/* the EAP method of an AP */
	#define E909002008_APEAP_SMALLINT 14
	/* work channel of an AP */
	#define E909002008_APCHANNEL_SMALLINT 15
	/* num of Aps with 1 signal bar in the same channel */
	#define E909002008_APNEARBYS1_TINYINT 16
	/* num of Aps with 2 signal bar in the same channel */
	#define E909002008_APNEARBYS2_TINYINT 17
	/* num of Aps with 3 signal bar in the same channel */
	#define E909002008_APNEARBYS3_TINYINT 18
	/* num of Aps with 4 signal bar in the same channel */
	#define E909002008_APNEARBYS4_TINYINT 19
	/* num of Aps with 1 signal bar in the next channel */
	#define E909002008_APNEARBYN1_TINYINT 20
	/* num of Aps with 2 signal bar in the next channel */
	#define E909002008_APNEARBYN2_TINYINT 21
	/* num of Aps with 3 signal bar in the next channel */
	#define E909002008_APNEARBYN3_TINYINT 22
	/* num of Aps with 4 signal bar in the next channel */
	#define E909002008_APNEARBYN4_TINYINT 23
	/* signal strength of an AP */
	#define E909002008_APRSSI_SMALLINT 24
	/* link speed of an AP */
	#define E909002008_APLINKSPEED_SMALLINT 25
	/* state of bt on or off */
	#define E909002008_ISBTSTATEON_BIT 26
	/* sum of connected bt devices */
	#define E909002008_BTSTATEDEVICES_TINYINT 27
	/* state of bt a2dp */
	#define E909002008_ISBTSTATEA2DP_BIT 28
	/* state of bt voice */
	#define E909002008_ISBTSTATEVOICE_BIT 29
	/* state of bt file transfer */
	#define E909002008_ISBTSTATEOPP_BIT 30
	/* method of get IP */
	#define E909002008_IPINFOTYPE_TINYINT 31
	/* IP address of the device */
	#define E909002008_IPINFOADDR_VARCHAR 32
	/* IP mask */
	#define E909002008_IPINFOMASK_TINYINT 33
	/* the address of gateway */
	#define E909002008_IPINFOGATEWAY_VARCHAR 34
	/* DNS server */
	#define E909002008_IPINFODNS_VARCHAR 35
	/* IP leasetime */
	#define E909002008_IPINFOLEASETIME_INT 36
	/* the status of proxy */
	#define E909002008_IPINFOPROXY_TINYINT 37
	/* the status of vpn */
	#define E909002008_IPINFOVPN_TINYINT 38
	/* country code for WiFi chipset */
	#define E909002008_COUNTRYCODE_VARCHAR 39
	/* mcc of cell */
	#define E909002008_CELLIDMCC_INT 40
	/* mnc of cell */
	#define E909002008_CELLIDMNC_INT 41
	/* lac of cell */
	#define E909002008_CELLIDLAC_INT 42
	/* cid of cell */
	#define E909002008_CELLIDCID_INT 43
	/* the time period from connectied time to exception */
	#define E909002008_DURATIONEXCEPTION_INT 44
	/* sum of all packages tx successfully */
	#define E909002008_PACKETCOUNTTXGOOD_INT 45
	/* sum of all packages tx fail */
	#define E909002008_PACKETCOUNTTXBAD_INT 46
	/* sum of all packages rx */
	#define E909002008_PACKETCOUNTRXGOOD_INT 47
	/* sum of tcp rx */
	#define E909002008_TCPINFORX_INT 48
	/* sum of tcp tx */
	#define E909002008_TCPINFOTX_INT 49
	/* sum of tcp tx retrans */
	#define E909002008_TCPINFORETRANS_INT 50
	/* sum of tcp rtt of all packages */
	#define E909002008_TCPINFORTTTOTAL_INT 51
	/* sum of tcp rtt during detect period */
	#define E909002008_TCPINFORTTSAMPLE_INT 52
	/* rtt during period with 1 bar signal strength */
	#define E909002008_RTTSIGNAL1BAR_INT 53
	/* rtt during period with 2 bar signal strength */
	#define E909002008_RTTSIGNAL2BAR_INT 54
	/* rtt during period with 3 bar signal strength */
	#define E909002008_RTTSIGNAL3BAR_INT 55
	/* rtt during period with 4 bar signal strength */
	#define E909002008_RTTSIGNAL4BAR_INT 56
	/* sum of dns request */
	#define E909002008_DNSREQCNT_INT 57
	/* sum of dns fail */
	#define E909002008_DNSREQFAIL_INT 58
	/* average time of dns */
	#define E909002008_DNSAVGTIME_INT 59
	/* sum of cmd52 read request */
	#define E909002008_SDIOINFOCMD52RDREQ_INT 60
	/* sum of cmd52 read total */
	#define E909002008_SDIOINFOCMD52RDTOTAL_INT 61
	/* sum of cmd52 write request */
	#define E909002008_SDIOINFOCMD52WTREQ_INT 62
	/* sum of cmd52 write total */
	#define E909002008_SDIOINFOCMD52WTTOTAL_INT 63
	/* sum of cmd53 read request */
	#define E909002008_SDIOINFOCMD53RDREQ_INT 64
	/* sum of cmd53 read total */
	#define E909002008_SDIOINFOCMD53RDTOTAL_INT 65
	/* sum of cmd53 write request */
	#define E909002008_SDIOINFOCMD53WTREQ_INT 66
	/* sum of cmd53 write total */
	#define E909002008_SDIOINFOCMD53WTTOTAL_INT 67
	/* sum of kso set request */
	#define E909002008_SDIOINFOKSOSETREQ_INT 68
	/* sum of kso set total */
	#define E909002008_SDIOINFOKSOSETRETRY_INT 69
	/* sum of kso clear request */
	#define E909002008_SDIOINFOKSOCLRREQ_INT 70
	/* sum of kso clear total */
	#define E909002008_SDIOINFOKSOCLRRETRY_INT 71
	/* period of calculate the wl counters */
	#define E909002008_WLCNTERSMONITORDURATION_INT 72
	/* txallfrm */
	#define E909002008_WLCNTERSTXALLFRM_INT 73
	/* txframe */
	#define E909002008_WLCNTERSTXFRAME_INT 74
	/* txbytes */
	#define E909002008_WLCNTERSTXBYTES_INT 75
	/* txretrans */
	#define E909002008_WLCNTERSTXRETRANS_INT 76
	/* txerror */
	#define E909002008_WLCNTERSTXERROR_INT 77
	/* txfail */
	#define E909002008_WLCNTERSTXFAIL_INT 78
	/* txfrag */
	#define E909002008_WLCNTERSTXFRAG_INT 79
	/* txfrmsnt */
	#define E909002008_WLCNTERSTXFRMSNT_INT 80
	/* txnoack */
	#define E909002008_WLCNTERSTXNOACK_INT 81
	/* rxframe */
	#define E909002008_WLCNTERSRXFRAME_INT 82
	/* rxbytes */
	#define E909002008_WLCNTERSRXBYTES_INT 83
	/* rxfrag */
	#define E909002008_WLCNTERSRXFRAG_INT 84
	/* rxbadfcs */
	#define E909002008_WLCNTERSRXBADFCS_INT 85
	/* rxbadplcp */
	#define E909002008_WLCNTERSRXBADPLCP_INT 86
	/* rxnobuf */
	#define E909002008_WLCNTERSRXNOBUF_INT 87
	/* rxcrsglitch */
	#define E909002008_WLCNTERSRXCRSGLITCH_INT 88
	/* rxbadproto */
	#define E909002008_WLCNTERSRXBADPROTO_INT 89
	/* rxbadcm */
	#define E909002008_WLCNTERSRXBADCM_INT 90
	/* rxctl */
	#define E909002008_WLCNTERSRXCTL_INT 91
	/* rxmulti */
	#define E909002008_WLCNTERSRXMULTI_INT 92
	/* rxnondata */
	#define E909002008_WLCNTERSRXNONDATA_INT 93
	/* rxbadds */
	#define E909002008_WLCNTERSRXBADDS_INT 94
	/* reset */
	#define E909002008_WLCNTERSRESET_INT 95
	/* rxstrt */
	#define E909002008_WLCNTERSRXSTRT_INT 96
	/* rxdfrmocast */
	#define E909002008_WLCNTERSRXDFRMOCAST_INT 97
	/* rxmfrmocast */
	#define E909002008_WLCNTERSRXMFRMOCAST_INT 98
	/* rxcfrmocast */
	#define E909002008_WLCNTERSRXCFRMOCAST_INT 99
	/* rxdfrmucastmbss */
	#define E909002008_WLCNTERSRXDFRMUCASTMBSS_INT 100
	/* rxmfrmucastmbss */
	#define E909002008_WLCNTERSRXMFRMUCASTMBSS_INT 101
	/* rxcfrmucast */
	#define E909002008_WLCNTERSRXCFRMUCAST_INT 102
	/* rxdfrmmcast */
	#define E909002008_WLCNTERSRXDFRMMCAST_INT 103
	/* rxmfrmmcast */
	#define E909002008_WLCNTERSRXMFRMMCAST_INT 104
	/* rxcfrmmcast */
	#define E909002008_WLCNTERSRXCFRMMCAST_INT 105
	/* rtt of arp detection */
	#define E909002008_DETECTRTTARP_INT 106
	/* rtt of visit www.baidu.com */
	#define E909002008_DETECTRTTBAIDU_INT 107
	/* whether or not receive tcp packages after resume */
	#define E909002008_HASTRAFFICAFTERSUSPEND_BIT 108
	/* sum of tx bytes in foreground */
	#define E909002008_TRAFFICSLOWTXFG_INT 109
	/* sum of rx bytes in foreground */
	#define E909002008_TRAFFICSLOWRXFG_INT 110
	/* sum of tx bytes in background */
	#define E909002008_TRAFFICSLOWTXBG_INT 111
	/* sum of rx bytes in background */
	#define E909002008_TRAFFICSLOWRXBG_INT 112
	/* cpufreq */
	#define E909002008_CPUFREQ_INT 113
	/* cpuload */
	#define E909002008_CPULOAD_INT 114
	/* memload */
	#define E909002008_MEMLOAD_INT 115
	/* whether or not portal registered */
	#define E909002008_ISPORTALREGED_BIT 116
	/* signal strength of an candicate AP with best signal */
	#define E909002008_APROAMINGRSSI_INT 117
	/* work channel of an candicate AP with best signal */
	#define E909002008_APROAMINGCHANNEL_INT 118
	/* signal strength of an candicate AP with better signal */
	#define E909002008_APROAMINGRSSI2_INT 119
	/* work channel of an candicate AP with better signal */
	#define E909002008_APROAMINGCHANNEL2_INT 120
	/* isScreenOn */
	#define E909002008_ISSCREENON_BIT 121

	/* Event 909202008
		exception of the device access the internet slowly
		via WiFi network */
	/* errorCode */
	#define E909202008_ERRORCODE_TINYINT 0
	/* subStatusCode */
	#define E909202008_SUBSTATUSCODE_TINYINT 1
	/* WiFi MAC of the AP */
	#define E909202008_APMAC_VARCHAR 2
	/* SSID of an AP */
	#define E909202008_APSSID_VARCHAR 3
	/* vendor info of an AP */
	#define E909202008_APVENDORINFO_VARCHAR 4
	/* sum of gateway IP in the LAN */
	#define E909202008_GWIPCOUNT_TINYINT 5
	/* sum of gateway MAC with same IP in the LAN */
	#define E909202008_GWMACCOUNT_TINYINT 6
	/* sum of MAC with same SSID */
	#define E909202008_PUBLICESSCOUNT_TINYINT 7
	/* the access security of an AP */
	#define E909202008_APSECURITY_SMALLINT 8
	/* the security protocol of an AP */
	#define E909202008_APPROTO_SMALLINT 9
	/* the key management scheme of an AP */
	#define E909202008_APKEYMGMT_SMALLINT 10
	/* the authentication algorithm of an AP */
	#define E909202008_APAUTHALG_SMALLINT 11
	/* the pairwise cipher for WPA */
	#define E909202008_APPAIRWISE_SMALLINT 12
	/* the group cipher of an AP */
	#define E909202008_APGROUP_SMALLINT 13
	/* the EAP method of an AP */
	#define E909202008_APEAP_SMALLINT 14
	/* work channel of an AP */
	#define E909202008_APCHANNEL_SMALLINT 15
	/* num of Aps with 1 signal bar in the same channel */
	#define E909202008_APNEARBYS1_TINYINT 16
	/* num of Aps with 2 signal bar in the same channel */
	#define E909202008_APNEARBYS2_TINYINT 17
	/* num of Aps with 3 signal bar in the same channel */
	#define E909202008_APNEARBYS3_TINYINT 18
	/* num of Aps with 4 signal bar in the same channel */
	#define E909202008_APNEARBYS4_TINYINT 19
	/* num of Aps with 1 signal bar in the next channel */
	#define E909202008_APNEARBYN1_TINYINT 20
	/* num of Aps with 2 signal bar in the next channel */
	#define E909202008_APNEARBYN2_TINYINT 21
	/* num of Aps with 3 signal bar in the next channel */
	#define E909202008_APNEARBYN3_TINYINT 22
	/* num of Aps with 4 signal bar in the next channel */
	#define E909202008_APNEARBYN4_TINYINT 23
	/* signal strength of an AP */
	#define E909202008_APRSSI_SMALLINT 24
	/* link speed of an AP */
	#define E909202008_APLINKSPEED_SMALLINT 25
	/* state of bt on or off */
	#define E909202008_ISBTSTATEON_BIT 26
	/* sum of connected bt devices */
	#define E909202008_BTSTATEDEVICES_TINYINT 27
	/* state of bt a2dp */
	#define E909202008_ISBTSTATEA2DP_BIT 28
	/* state of bt voice */
	#define E909202008_ISBTSTATEVOICE_BIT 29
	/* state of bt file transfer */
	#define E909202008_ISBTSTATEOPP_BIT 30
	/* method of get IP */
	#define E909202008_IPINFOTYPE_TINYINT 31
	/* IP address of the device */
	#define E909202008_IPINFOADDR_VARCHAR 32
	/* IP mask */
	#define E909202008_IPINFOMASK_TINYINT 33
	/* the address of gateway */
	#define E909202008_IPINFOGATEWAY_VARCHAR 34
	/* DNS server */
	#define E909202008_IPINFODNS_VARCHAR 35
	/* IP leasetime */
	#define E909202008_IPINFOLEASETIME_INT 36
	/* the status of proxy */
	#define E909202008_IPINFOPROXY_TINYINT 37
	/* the status of vpn */
	#define E909202008_IPINFOVPN_TINYINT 38
	/* the public IP and address of wifi network for access
		the internet */
	#define E909202008_IPPUBLICINFO_VARCHAR 39
	/* country code for WiFi chipset */
	#define E909202008_COUNTRYCODE_VARCHAR 40
	/* mcc of cell */
	#define E909202008_CELLIDMCC_INT 41
	/* mnc of cell */
	#define E909202008_CELLIDMNC_INT 42
	/* lac of cell */
	#define E909202008_CELLIDLAC_INT 43
	/* cid of cell */
	#define E909202008_CELLIDCID_INT 44
	/* the time period from connectied time to exception */
	#define E909202008_DURATIONEXCEPTION_INT 45
	/* sum of all packages tx successfully */
	#define E909202008_PACKETCOUNTTXGOOD_INT 46
	/* sum of all packages tx fail */
	#define E909202008_PACKETCOUNTTXBAD_INT 47
	/* sum of all packages rx */
	#define E909202008_PACKETCOUNTRXGOOD_INT 48
	/* sum of tcp rx */
	#define E909202008_TCPINFORX_INT 49
	/* sum of tcp tx */
	#define E909202008_TCPINFOTX_INT 50
	/* sum of tcp tx retrans */
	#define E909202008_TCPINFORETRANS_INT 51
	/* sum of tcp rtt of all packages */
	#define E909202008_TCPINFORTTTOTAL_INT 52
	/* sum of tcp rtt during detect period */
	#define E909202008_TCPINFORTTSAMPLE_INT 53
	/* rtt during period with 1 bar signal strength */
	#define E909202008_RTTSIGNAL1BAR_INT 54
	/* rtt during period with 2 bar signal strength */
	#define E909202008_RTTSIGNAL2BAR_INT 55
	/* rtt during period with 3 bar signal strength */
	#define E909202008_RTTSIGNAL3BAR_INT 56
	/* rtt during period with 4 bar signal strength */
	#define E909202008_RTTSIGNAL4BAR_INT 57
	/* sum of dns request */
	#define E909202008_DNSREQCNT_INT 58
	/* sum of dns fail */
	#define E909202008_DNSREQFAIL_INT 59
	/* average time of dns */
	#define E909202008_DNSAVGTIME_INT 60
	/* sum of cmd52 read request */
	#define E909202008_SDIOINFOCMD52RDREQ_INT 61
	/* sum of cmd52 read total */
	#define E909202008_SDIOINFOCMD52RDTOTAL_INT 62
	/* sum of cmd52 write request */
	#define E909202008_SDIOINFOCMD52WTREQ_INT 63
	/* sum of cmd52 write total */
	#define E909202008_SDIOINFOCMD52WTTOTAL_INT 64
	/* sum of cmd53 read request */
	#define E909202008_SDIOINFOCMD53RDREQ_INT 65
	/* sum of cmd53 read total */
	#define E909202008_SDIOINFOCMD53RDTOTAL_INT 66
	/* sum of cmd53 write request */
	#define E909202008_SDIOINFOCMD53WTREQ_INT 67
	/* sum of cmd53 write total */
	#define E909202008_SDIOINFOCMD53WTTOTAL_INT 68
	/* sum of kso set request */
	#define E909202008_SDIOINFOKSOSETREQ_INT 69
	/* sum of kso set total */
	#define E909202008_SDIOINFOKSOSETRETRY_INT 70
	/* sum of kso clear request */
	#define E909202008_SDIOINFOKSOCLRREQ_INT 71
	/* sum of kso clear total */
	#define E909202008_SDIOINFOKSOCLRRETRY_INT 72
	/* period of calculate the wl counters */
	#define E909202008_WLCNTERSMONITORDURATION_INT 73
	/* txallfrm */
	#define E909202008_WLCNTERSTXALLFRM_INT 74
	/* txframe */
	#define E909202008_WLCNTERSTXFRAME_INT 75
	/* txbytes */
	#define E909202008_WLCNTERSTXBYTES_INT 76
	/* txretrans */
	#define E909202008_WLCNTERSTXRETRANS_INT 77
	/* txerror */
	#define E909202008_WLCNTERSTXERROR_INT 78
	/* txfail */
	#define E909202008_WLCNTERSTXFAIL_INT 79
	/* txfrag */
	#define E909202008_WLCNTERSTXFRAG_INT 80
	/* txfrmsnt */
	#define E909202008_WLCNTERSTXFRMSNT_INT 81
	/* txnoack */
	#define E909202008_WLCNTERSTXNOACK_INT 82
	/* rxframe */
	#define E909202008_WLCNTERSRXFRAME_INT 83
	/* rxbytes */
	#define E909202008_WLCNTERSRXBYTES_INT 84
	/* rxfrag */
	#define E909202008_WLCNTERSRXFRAG_INT 85
	/* rxbadfcs */
	#define E909202008_WLCNTERSRXBADFCS_INT 86
	/* rxbadplcp */
	#define E909202008_WLCNTERSRXBADPLCP_INT 87
	/* rxnobuf */
	#define E909202008_WLCNTERSRXNOBUF_INT 88
	/* rxcrsglitch */
	#define E909202008_WLCNTERSRXCRSGLITCH_INT 89
	/* rxbadproto */
	#define E909202008_WLCNTERSRXBADPROTO_INT 90
	/* rxbadcm */
	#define E909202008_WLCNTERSRXBADCM_INT 91
	/* rxctl */
	#define E909202008_WLCNTERSRXCTL_INT 92
	/* rxmulti */
	#define E909202008_WLCNTERSRXMULTI_INT 93
	/* rxnondata */
	#define E909202008_WLCNTERSRXNONDATA_INT 94
	/* rxbadds */
	#define E909202008_WLCNTERSRXBADDS_INT 95
	/* reset */
	#define E909202008_WLCNTERSRESET_INT 96
	/* rxstrt */
	#define E909202008_WLCNTERSRXSTRT_INT 97
	/* rxdfrmocast */
	#define E909202008_WLCNTERSRXDFRMOCAST_INT 98
	/* rxmfrmocast */
	#define E909202008_WLCNTERSRXMFRMOCAST_INT 99
	/* rxcfrmocast */
	#define E909202008_WLCNTERSRXCFRMOCAST_INT 100
	/* rxdfrmucastmbss */
	#define E909202008_WLCNTERSRXDFRMUCASTMBSS_INT 101
	/* rxmfrmucastmbss */
	#define E909202008_WLCNTERSRXMFRMUCASTMBSS_INT 102
	/* rxcfrmucast */
	#define E909202008_WLCNTERSRXCFRMUCAST_INT 103
	/* rxdfrmmcast */
	#define E909202008_WLCNTERSRXDFRMMCAST_INT 104
	/* rxmfrmmcast */
	#define E909202008_WLCNTERSRXMFRMMCAST_INT 105
	/* rxcfrmmcast */
	#define E909202008_WLCNTERSRXCFRMMCAST_INT 106
	/* rtt of arp detection */
	#define E909202008_DETECTRTTARP_INT 107
	/* rtt of visit www.baidu.com */
	#define E909202008_DETECTRTTBAIDU_INT 108
	/* whether or not receive tcp packages after resume */
	#define E909202008_HASTRAFFICAFTERSUSPEND_BIT 109
	/* sum of tx bytes in foreground */
	#define E909202008_TRAFFICSLOWTXFG_INT 110
	/* sum of rx bytes in foreground */
	#define E909202008_TRAFFICSLOWRXFG_INT 111
	/* sum of tx bytes in background */
	#define E909202008_TRAFFICSLOWTXBG_INT 112
	/* sum of rx bytes in background */
	#define E909202008_TRAFFICSLOWRXBG_INT 113
	/* cpufreq */
	#define E909202008_CPUFREQ_INT 114
	/* cpuload */
	#define E909202008_CPULOAD_INT 115
	/* memload */
	#define E909202008_MEMLOAD_INT 116
	/* whether or not portal registered */
	#define E909202008_ISPORTALREGED_BIT 117
	/* signal strength of an candicate AP with best signal */
	#define E909202008_APROAMINGRSSI_INT 118
	/* work channel of an candicate AP with best signal */
	#define E909202008_APROAMINGCHANNEL_INT 119
	/* signal strength of an candicate AP with better signal */
	#define E909202008_APROAMINGRSSI2_INT 120
	/* work channel of an candicate AP with better signal */
	#define E909202008_APROAMINGCHANNEL2_INT 121
	/* isScreenOn */
	#define E909202008_ISSCREENON_BIT 122

	/* Event 909002009
		exception of disconnection from WiFi network */
	/* errorCode */
	#define E909002009_ERRORCODE_TINYINT 0
	/* subStatusCode */
	#define E909002009_SUBSTATUSCODE_TINYINT 1
	/* WiFi MAC of the AP */
	#define E909002009_APMAC_VARCHAR 2
	/* SSID of an AP */
	#define E909002009_APSSID_VARCHAR 3
	/* vendor info of an AP */
	#define E909002009_APVENDORINFO_VARCHAR 4
	/* work channel of an AP */
	#define E909002009_APCHANNEL_SMALLINT 5
	/* signal strength of an AP */
	#define E909002009_APRSSI_SMALLINT 6
	/* sum of MAC with same SSID */
	#define E909002009_PUBLICESSCOUNT_TINYINT 7
	/* rssi of available roaming AP */
	#define E909002009_APROAMINGRSSI_SMALLINT 8
	/* channel of available roaming AP */
	#define E909002009_APROAMINGCHANNEL_SMALLINT 9
	/* state of bt on or off */
	#define E909002009_ISBTSTATEON_BIT 10
	/* state of p2p connection */
	#define E909002009_ISWIFIP2PCONNECTED_BIT 11
	/* as p2p Go or Gc */
	#define E909002009_ISWIFIP2PGO_BIT 12
	/* isScreenOn */
	#define E909002009_ISSCREENON_BIT 13
	/* method of get IP */
	#define E909002009_IPINFOTYPE_TINYINT 14
	/* duration of connected to disconnect */
	#define E909002009_DURATIONEXCEPTION_INT 15
	/* sum of cmd52 read request */
	#define E909002009_SDIOINFOCMD52RDREQ_INT 16
	/* sum of cmd52 read total */
	#define E909002009_SDIOINFOCMD52RDTOTAL_INT 17
	/* sum of cmd52 write request */
	#define E909002009_SDIOINFOCMD52WTREQ_INT 18
	/* sum of cmd52 write total */
	#define E909002009_SDIOINFOCMD52WTTOTAL_INT 19
	/* sum of cmd53 read request */
	#define E909002009_SDIOINFOCMD53RDREQ_INT 20
	/* sum of cmd53 read total */
	#define E909002009_SDIOINFOCMD53RDTOTAL_INT 21
	/* sum of cmd53 write request */
	#define E909002009_SDIOINFOCMD53WTREQ_INT 22
	/* sum of cmd53 write total */
	#define E909002009_SDIOINFOCMD53WTTOTAL_INT 23
	/* sum of kso set request */
	#define E909002009_SDIOINFOKSOSETREQ_INT 24
	/* sum of kso set total */
	#define E909002009_SDIOINFOKSOSETRETRY_INT 25
	/* sum of kso clear request */
	#define E909002009_SDIOINFOKSOCLRREQ_INT 26
	/* sum of kso clear total */
	#define E909002009_SDIOINFOKSOCLRRETRY_INT 27

	/* Event 909002010
		exception of connect&disconnec from WiFi network in
		a short time */
	/* errorCode */
	#define E909002010_ERRORCODE_TINYINT 0
	/* subStatusCode */
	#define E909002010_SUBSTATUSCODE_TINYINT 1
	/* WiFi MAC of the AP */
	#define E909002010_APMAC_VARCHAR 2
	/* SSID of an AP */
	#define E909002010_APSSID_VARCHAR 3
	/* vendor info of an AP */
	#define E909002010_APVENDORINFO_VARCHAR 4
	/* work channel of an AP */
	#define E909002010_APCHANNEL_SMALLINT 5
	/* signal strength of an AP */
	#define E909002010_APRSSI_SMALLINT 6
	/* sum of MAC with same SSID */
	#define E909002010_PUBLICESSCOUNT_TINYINT 7
	/* rssi of available roaming AP */
	#define E909002010_APROAMINGRSSI_SMALLINT 8
	/* channel of available roaming AP */
	#define E909002010_APROAMINGCHANNEL_SMALLINT 9
	/* state of bt on or off */
	#define E909002010_ISBTSTATEON_BIT 10
	/* state of p2p connection */
	#define E909002010_ISWIFIP2PCONNECTED_BIT 11
	/* as p2p Go or Gc */
	#define E909002010_ISWIFIP2PGO_BIT 12
	/* isScreenOn */
	#define E909002010_ISSCREENON_BIT 13
	/* method of get IP */
	#define E909002010_IPINFOTYPE_TINYINT 14
	/* duration of connected to disconnect */
	#define E909002010_DURATIONEXCEPTION_INT 15
	/* sum of cmd52 read request */
	#define E909002010_SDIOINFOCMD52RDREQ_INT 16
	/* sum of cmd52 read total */
	#define E909002010_SDIOINFOCMD52RDTOTAL_INT 17
	/* sum of cmd52 write request */
	#define E909002010_SDIOINFOCMD52WTREQ_INT 18
	/* sum of cmd52 write total */
	#define E909002010_SDIOINFOCMD52WTTOTAL_INT 19
	/* sum of cmd53 read request */
	#define E909002010_SDIOINFOCMD53RDREQ_INT 20
	/* sum of cmd53 read total */
	#define E909002010_SDIOINFOCMD53RDTOTAL_INT 21
	/* sum of cmd53 write request */
	#define E909002010_SDIOINFOCMD53WTREQ_INT 22
	/* sum of cmd53 write total */
	#define E909002010_SDIOINFOCMD53WTTOTAL_INT 23
	/* sum of kso set request */
	#define E909002010_SDIOINFOKSOSETREQ_INT 24
	/* sum of kso set total */
	#define E909002010_SDIOINFOKSOSETRETRY_INT 25
	/* sum of kso clear request */
	#define E909002010_SDIOINFOKSOCLRREQ_INT 26
	/* sum of kso clear total */
	#define E909002010_SDIOINFOKSOCLRRETRY_INT 27

	/* Event 909002011
		WiFi open and close failed event */
	/* OpenCloseResonCode */
	#define E909002011_OPENFAILEDRESONCODE_SMALLINT 0
	/* subErrorCode */
	#define E909002011_SUBERRORCODE_INT 1

	/* Event 909002012
		WiFi abnormal disconnect event */
	/* abnormalDisconnectResonCode */
	#define E909002012_ABNORMALDISCONNECTRESONCODE_SMALLINT 0
	/* subErrorCode */
	#define E909002012_SUBERRORCODE_INT 1

	/* Event 909002013
		WiFi scan failed event */
	/* scanFailedResonCode */
	#define E909002013_SCANFAILEDRESONCODE_SMALLINT 0
	/* subErrorCode */
	#define E909002013_SUBERRORCODE_INT 1

	/* Event 909002014
		WiFi connect failed event */
	/* ErrorCode */
	#define E909002014_ERRORCODE_SMALLINT 0
	/* SubErrorCode */
	#define E909002014_SUBERRORCODE_SMALLINT 1

	/* Event 909002015
		WiFi access internet failed event */
	/* accessInternetFailedResonCode */
	#define E909002015_ACCESSINTERNETFAILEDRESONCODE_SMALLINT 0
	/* subErrorCode */
	#define E909002015_SUBERRORCODE_INT 1

	/* Event 909002016
		WiFi access internet slowly event */
	/* wifiAccessWebSlowlyReasonCode */
	#define E909002016_WIFIACCESSWEBSLOWLYREASONCODE_SMALLINT 0
	/* subErrorCode */
	#define E909002016_SUBERRORCODE_INT 1

	/* Event 909002017
		WiFi 110x device and firmware exception event */
	/* ErrorCode */
	#define E909002017_ERRORCODE_SMALLINT 0
	/* SubErrorCode */
	#define E909002017_SUBERRORCODE_SMALLINT 1

	/* Event 909002018
		WiFi+ exception event */
	/* wifiProSubEvent */
	#define E909002018_WIFIPROSUBEVENT_SMALLINT 0

	/* Event 909002019
		WiFi+ dualband exception event */
	/* dualbandExSubEvent */
	#define E909002019_DUALBANDEXSUBEVENT_SMALLINT 0

	/* Event 909002020
		WiFi AP Model collect exception event */
	/* WiFi MAC of the AP */
	#define E909002020_APMAC_VARCHAR 0
	/* SSID of an AP */
	#define E909002020_APSSID_VARCHAR 1

	/* Event 909030001
		DSM_WIFI_MODULE_INIT_ERROR */
	/* error level */
	#define E909030001_ERROR_LEVEL_INT 0
	/* IC name */
	#define E909030001_IC_NAME_VARCHAR 1
	/* module name */
	#define E909030001_MODULE_NAME_VARCHAR 2
	/* description */
	#define E909030001_DESCRIPTION_VARCHAR 3

	/* Event 909030002
		DSM_WIFI_KSO_ERROR */
	/* error level */
	#define E909030002_ERROR_LEVEL_INT 0
	/* IC name */
	#define E909030002_IC_NAME_VARCHAR 1
	/* module name */
	#define E909030002_MODULE_NAME_VARCHAR 2
	/* description */
	#define E909030002_DESCRIPTION_VARCHAR 3

	/* Event 909030003
		DSM_WIFI_CMD52_ERROR */
	/* error level */
	#define E909030003_ERROR_LEVEL_INT 0
	/* IC name */
	#define E909030003_IC_NAME_VARCHAR 1
	/* module name */
	#define E909030003_MODULE_NAME_VARCHAR 2
	/* description */
	#define E909030003_DESCRIPTION_VARCHAR 3

	/* Event 909030004
		DSM_WIFI_CMD53_ERROR */
	/* error level */
	#define E909030004_ERROR_LEVEL_INT 0
	/* IC name */
	#define E909030004_IC_NAME_VARCHAR 1
	/* module name */
	#define E909030004_MODULE_NAME_VARCHAR 2
	/* description */
	#define E909030004_DESCRIPTION_VARCHAR 3

	/* Event 909030005
		DSM_WIFI_SDIO_RESET_COMM_ERROR */
	/* error level */
	#define E909030005_ERROR_LEVEL_INT 0
	/* IC name */
	#define E909030005_IC_NAME_VARCHAR 1
	/* module name */
	#define E909030005_MODULE_NAME_VARCHAR 2
	/* description */
	#define E909030005_DESCRIPTION_VARCHAR 3

	/* Event 909030006
		DSM_WIFI_SDIO_PROBE_ATTACH_ERROR */
	/* error level */
	#define E909030006_ERROR_LEVEL_INT 0
	/* IC name */
	#define E909030006_IC_NAME_VARCHAR 1
	/* module name */
	#define E909030006_MODULE_NAME_VARCHAR 2
	/* description */
	#define E909030006_DESCRIPTION_VARCHAR 3

	/* Event 909030007
		DSM_WIFI_SDIO_FIRMWARE_DL_ERROR */
	/* error level */
	#define E909030007_ERROR_LEVEL_INT 0
	/* IC name */
	#define E909030007_IC_NAME_VARCHAR 1
	/* module name */
	#define E909030007_MODULE_NAME_VARCHAR 2
	/* description */
	#define E909030007_DESCRIPTION_VARCHAR 3

	/* Event 909030008
		DSM_WIFI_DHD_DEV_INIT_IOCTL_ERROR */
	/* error level */
	#define E909030008_ERROR_LEVEL_INT 0
	/* IC name */
	#define E909030008_IC_NAME_VARCHAR 1
	/* module name */
	#define E909030008_MODULE_NAME_VARCHAR 2
	/* description */
	#define E909030008_DESCRIPTION_VARCHAR 3

	/* Event 909030009
		DSM_WIFI_WLC_SET_PASSIVE_SCAN_ERROR */
	/* error level */
	#define E909030009_ERROR_LEVEL_INT 0
	/* IC name */
	#define E909030009_IC_NAME_VARCHAR 1
	/* module name */
	#define E909030009_MODULE_NAME_VARCHAR 2
	/* description */
	#define E909030009_DESCRIPTION_VARCHAR 3

	/* Event 909030010
		DSM_WIFI_WLC_SCAN_ERROR */
	/* error level */
	#define E909030010_ERROR_LEVEL_INT 0
	/* IC name */
	#define E909030010_IC_NAME_VARCHAR 1
	/* module name */
	#define E909030010_MODULE_NAME_VARCHAR 2
	/* description */
	#define E909030010_DESCRIPTION_VARCHAR 3

	/* Event 909030011
		DSM_WIFI_WLC_SET_SCANSUPPRESS_ERROR */
	/* error level */
	#define E909030011_ERROR_LEVEL_INT 0
	/* IC name */
	#define E909030011_IC_NAME_VARCHAR 1
	/* module name */
	#define E909030011_MODULE_NAME_VARCHAR 2
	/* description */
	#define E909030011_DESCRIPTION_VARCHAR 3

	/* Event 909030012
		DSM_WIFI_WLC_GET_CHANNEL_ERROR */
	/* error level */
	#define E909030012_ERROR_LEVEL_INT 0
	/* IC name */
	#define E909030012_IC_NAME_VARCHAR 1
	/* module name */
	#define E909030012_MODULE_NAME_VARCHAR 2
	/* description */
	#define E909030012_DESCRIPTION_VARCHAR 3

	/* Event 909030013
		DSM_WIFI_WLC_SCAN_RESULTS_ERROR */
	/* error level */
	#define E909030013_ERROR_LEVEL_INT 0
	/* IC name */
	#define E909030013_IC_NAME_VARCHAR 1
	/* module name */
	#define E909030013_MODULE_NAME_VARCHAR 2
	/* description */
	#define E909030013_DESCRIPTION_VARCHAR 3

	/* Event 909030014
		DSM_WIFI_WLC_DISASSOC_ERROR */
	/* error level */
	#define E909030014_ERROR_LEVEL_INT 0
	/* IC name */
	#define E909030014_IC_NAME_VARCHAR 1
	/* module name */
	#define E909030014_MODULE_NAME_VARCHAR 2
	/* description */
	#define E909030014_DESCRIPTION_VARCHAR 3

	/* Event 909030015
		DSM_WIFI_WLC_SET_SSID_ERROR */
	/* error level */
	#define E909030015_ERROR_LEVEL_INT 0
	/* IC name */
	#define E909030015_IC_NAME_VARCHAR 1
	/* module name */
	#define E909030015_MODULE_NAME_VARCHAR 2
	/* description */
	#define E909030015_DESCRIPTION_VARCHAR 3

	/* Event 909030016
		DSM_WIFI_SET_CIPHER_ERROR */
	/* error level */
	#define E909030016_ERROR_LEVEL_INT 0
	/* IC name */
	#define E909030016_IC_NAME_VARCHAR 1
	/* module name */
	#define E909030016_MODULE_NAME_VARCHAR 2
	/* description */
	#define E909030016_DESCRIPTION_VARCHAR 3

	/* Event 909030017
		DSM_WIFI_SET_KEY_MGMT_ERROR */
	/* error level */
	#define E909030017_ERROR_LEVEL_INT 0
	/* IC name */
	#define E909030017_IC_NAME_VARCHAR 1
	/* module name */
	#define E909030017_MODULE_NAME_VARCHAR 2
	/* description */
	#define E909030017_DESCRIPTION_VARCHAR 3

	/* Event 909030018
		DSM_WIFI_SET_SHAREDKEY_ERROR */
	/* error level */
	#define E909030018_ERROR_LEVEL_INT 0
	/* IC name */
	#define E909030018_IC_NAME_VARCHAR 1
	/* module name */
	#define E909030018_MODULE_NAME_VARCHAR 2
	/* description */
	#define E909030018_DESCRIPTION_VARCHAR 3

	/* Event 909030019
		DSM_WIFI_OPEN_ERROR */
	/* error level */
	#define E909030019_ERROR_LEVEL_INT 0
	/* IC name */
	#define E909030019_IC_NAME_VARCHAR 1
	/* module name */
	#define E909030019_MODULE_NAME_VARCHAR 2
	/* description */
	#define E909030019_DESCRIPTION_VARCHAR 3

	/* Event 909031001
		DSM_WIFI_DRIVER_LOAD_ERR */
	/* error level */
	#define E909031001_ERROR_LEVEL_INT 0
	/* IC name */
	#define E909031001_IC_NAME_VARCHAR 1
	/* module name */
	#define E909031001_MODULE_NAME_VARCHAR 2
	/* description */
	#define E909031001_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E909031001_COUNT_INT 4

	/* Event 909031002
		DSM_WIFI_SUPPLICANT_START_ERR */
	/* error level */
	#define E909031002_ERROR_LEVEL_INT 0
	/* IC name */
	#define E909031002_IC_NAME_VARCHAR 1
	/* module name */
	#define E909031002_MODULE_NAME_VARCHAR 2
	/* description */
	#define E909031002_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E909031002_COUNT_INT 4

	/* Event 909031003
		DSM_WIFI_CONNECT_SUPPLICANT_ERR */
	/* error level */
	#define E909031003_ERROR_LEVEL_INT 0
	/* IC name */
	#define E909031003_IC_NAME_VARCHAR 1
	/* module name */
	#define E909031003_MODULE_NAME_VARCHAR 2
	/* description */
	#define E909031003_DESCRIPTION_VARCHAR 3

	/* Event 909031004
		DSM_WIFI_MAC_ERR */
	/* error level */
	#define E909031004_ERROR_LEVEL_INT 0
	/* IC name */
	#define E909031004_IC_NAME_VARCHAR 1
	/* module name */
	#define E909031004_MODULE_NAME_VARCHAR 2
	/* description */
	#define E909031004_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E909031004_COUNT_INT 4

	/* Event 909031005
		DSM_WIFI_SCAN_FAIL_ERR */
	/* error level */
	#define E909031005_ERROR_LEVEL_INT 0
	/* IC name */
	#define E909031005_IC_NAME_VARCHAR 1
	/* module name */
	#define E909031005_MODULE_NAME_VARCHAR 2
	/* description */
	#define E909031005_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E909031005_COUNT_INT 4

	/* Event 909031006
		DSM_WIFI_FAIL_LOADFIRMWARE_ERR */
	/* error level */
	#define E909031006_ERROR_LEVEL_INT 0
	/* IC name */
	#define E909031006_IC_NAME_VARCHAR 1
	/* module name */
	#define E909031006_MODULE_NAME_VARCHAR 2
	/* description */
	#define E909031006_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E909031006_COUNT_INT 4

	/* Event 909031007
		DSM_WIFI_ABNORMAL_DISCONNECT_ERR */
	/* error level */
	#define E909031007_ERROR_LEVEL_INT 0
	/* IC name */
	#define E909031007_IC_NAME_VARCHAR 1
	/* module name */
	#define E909031007_MODULE_NAME_VARCHAR 2
	/* description */
	#define E909031007_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E909031007_COUNT_INT 4

	/* Event 909031008
		DSM_WIFI_CANNOT_CONNECT_AP_ERR */
	/* error level */
	#define E909031008_ERROR_LEVEL_INT 0
	/* IC name */
	#define E909031008_IC_NAME_VARCHAR 1
	/* module name */
	#define E909031008_MODULE_NAME_VARCHAR 2
	/* description */
	#define E909031008_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E909031008_COUNT_INT 4

	/* Event 909031009
		DSM_WIFI_ROOT_NOT_RIGHT_ERR */
	/* error level */
	#define E909031009_ERROR_LEVEL_INT 0
	/* IC name */
	#define E909031009_IC_NAME_VARCHAR 1
	/* module name */
	#define E909031009_MODULE_NAME_VARCHAR 2
	/* description */
	#define E909031009_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E909031009_COUNT_INT 4

	/* Event 909800001
		WIFI_STATISTICS_EVENT */
	/* description */
	#define E909800001_DESCRIPTION_VARCHAR 0
	/* ChrEventId */
	#define E909800001_CHREVENTID_INT 1

	/* Event 909800002
		WIFI_FAULT_EVENT */
	/* description */
	#define E909800002_DESCRIPTION_VARCHAR 0
	/* ChrEventId */
	#define E909800002_CHREVENTID_INT 1

	/* Event 909800003
		WIFI_FAULT_EVENT_WITH_WIFI_LOG */
	/* description */
	#define E909800003_DESCRIPTION_VARCHAR 0
	/* ChrEventId */
	#define E909800003_CHREVENTID_INT 1

	/* Event 909800004
		WIFI_FAULT_EVENT_WITH_HI110X_LOG */
	/* description */
	#define E909800004_DESCRIPTION_VARCHAR 0
	/* ChrEventId */
	#define E909800004_CHREVENTID_INT 1

/*** GPS events' keys ***/

	/* Event 910000000
		GPS_SESSION_EVENT */
	/* Name of location apk */
	#define E910000000_APK_NAME_VARCHAR 0
	/* the location provider used in this session */
	#define E910000000_PROVIDERMODE_VARCHAR 1
	/* Timestamp of gps_start */
	#define E910000000_STARTTIME_INT 2
	/* location methods */
	#define E910000000_POSMODE_TINYINT 3
	/* The current GNSS switch status */
	#define E910000000_LOCSETSTATUS_TINYINT 4
	/* Current network type */
	#define E910000000_NETWORKSTATUS_TINYINT 5
	/* Timestamp of get 4 SVs whose CN0 bigger than 28 */
	#define E910000000_CATCHSVTIME_INT 6
	/* Time to First Fix */
	#define E910000000_TTFF_INT 7
	/* Speed when fix */
	#define E910000000_FIX_SPEED_INT 8
	/* Accuracy when fix */
	#define E910000000_POSITIONACC_INT 9
	/* average accuracy of the first 10 fix */
	#define E910000000_AVGPOSITIONACC_INT 10
	/* the average CN0 of top 4 CVs when the speed exceed
		40 km/h at the first time */
	#define E910000000_AVGCN0WHEN40KMPH_TINYINT 11
	/* Position Fix Source */
	#define E910000000_POSITION_SOURCE_TINYINT 12
	/* Time Source */
	#define E910000000_TIME_SOURCE_TINYINT 13
	/* The aiding mothods used in current fix */
	#define E910000000_POSFIXAIDINGDATA_INT 14
	/* the offset of TCXO */
	#define E910000000_TCXO_INT 15
	/* TBD */
	#define E910000000_APPUSEDPARM_INT 16
	/* Whether GPSD crash and restart */
	#define E910000000_ISGPSDRESART_BIT 17
	/* whether to have issue in this session */
	#define E910000000_ISISSUESESSION_BIT 18
	/* Ref clock offset */
	#define E910000000_REF_CLK_INT 19
	/* Timestamp of gps_stop */
	#define E910000000_STOPTIME_INT 20
	/* counts of losing fix in one session */
	#define E910000000_LOSTPOSCNT_TINYINT 21
	/* LTO file status */
	#define E910000000_LTOFILESTATUS_INT 22

	/* Event 910000001
		GPS_SESSION_ERROR_EVENT */
	/* Timestamp of gps_start */
	#define E910000001_STARTTIME_INT 0
	/* Error Index in one session */
	#define E910000001_ERRINDEXINONESESSION_SMALLINT 1
	/* Error Code */
	#define E910000001_ERRORCODE_TINYINT 2
	/* True: Wifi On False: Wifi Off */
	#define E910000001_WIFI_SWITCH_BIT 3
	/* True: Screen On False: Screen Off */
	#define E910000001_SCREENSTATE_BIT 4
	/* MCC of Cell */
	#define E910000001_CELL_MCC_VARCHAR 5
	/* MNC of Cell */
	#define E910000001_CELL_MNC_VARCHAR 6
	/* LAC of Cell */
	#define E910000001_CELL_LAC_INT 7
	/* Cid of Cell */
	#define E910000001_CELL_CID_INT 8
	/* CDMA Cell BaseID */
	#define E910000001_CELL_ID_INT 9
	/* wifi mac address */
	#define E910000001_WIFI_BSSID_VARCHAR 10
	/* access point name */
	#define E910000001_WIFI_SSID_VARCHAR 11
	/* Current network status */
	#define E910000001_NETWORKSTATUS_TINYINT 12
	/* Current status of DataCall */
	#define E910000001_DATACALL_SWITCH_VARCHAR 13
	/* the aiding used in current fix */
	#define E910000001_POSFIXAIDINGDATA_INT 14
	/* Timestamp when VDR enable */
	#define E910000001_VDR_ENABLETIME_INT 15
	/* Timestamp when VDR disable */
	#define E910000001_VDR_DISABLETIME_INT 16
	/* GPS Time and local system time in UTC format */
	#define E910000001_REALTIME_INT 17
	/* NTP Time from NTP server */
	#define E910000001_NTPTIME_INT 18
	/* Current SV number and Snr */
	#define E910000001_CUR_SVINFO_VARCHAR 19
	/* Current GPS EphMask */
	#define E910000001_CUR_GPSSVEPHMASK_INT 20
	/* Current GLO EphMask */
	#define E910000001_CUR_GLOSVEPHMASK_INT 21
	/* Current BD EphMask */
	#define E910000001_CUR_BDSVEPHMASK_INT 22
	/* Current GPS AlmMask */
	#define E910000001_CUR_GPSSVALMMASK_INT 23
	/* Current GLO AlmMask */
	#define E910000001_CUR_GLOSVALMMASK_INT 24
	/* Current BD AlmMask */
	#define E910000001_CUR_BDSVALMMASK_INT 25
	/* Current GPS UsedMask */
	#define E910000001_CUR_GPSSVUSEMASK_INT 26
	/* Current GLO UsedMask */
	#define E910000001_CUR_GLOSVUSEMASK_INT 27
	/* Current BD UsedMask */
	#define E910000001_CUR_BDSVUSEMASK_INT 28
	/* Current Speed */
	#define E910000001_CUR_SPEED_INT 29
	/* RF Agc values // 0 Analog I Analog GPS */
	#define E910000001_CUR_AGC0_FLOAT 30
	/* RF Agc values // 1 Analog Q Digital GPS */
	#define E910000001_CUR_AGC1_FLOAT 31
	/* RF Agc values // 2 Digital I Analog GLNS */
	#define E910000001_CUR_AGC2_FLOAT 32
	/* RF Agc values // 3 Digital Q Digital GLNS */
	#define E910000001_CUR_AGC3_FLOAT 33
	/* RF Agc values // 4 N/A RESERVED */
	#define E910000001_CUR_AGC4_FLOAT 34
	/* RF Agc values // 5 N/A RESERVED */
	#define E910000001_CUR_AGC5_FLOAT 35
	/* WER test result in % */
	#define E910000001_CUR_WER_FLOAT 36
	/* Data transfer delay */
	#define E910000001_DELAYTIME_INT 37
	/* Network Fix Timeout Error Code */
	#define E910000001_NETWORKFIXTIMEOUTERRCODE_TINYINT 38
	/* Whether we can ping baidu to verify data access */
	#define E910000001_ISDATAAVAILABLE_BIT 39
	/* AGPS_SI_MSA = 1; AGPS_SI_MSB = 2; AGPS_NI_MSA = 3;
		AGPS_NI_MSB = 4; AGPS_CP = 5; */
	#define E910000001_AGPSTYPE_TINYINT 40
	/* AGPS error code */
	#define E910000001_AGPSERRORCODE_TINYINT 41
	/* Assert log messages */
	#define E910000001_ASSERTMSG_VARCHAR 42

	/* Event 910000002
		GPS_DAILY_CNT_REPORT */
	/* Network timeout count */
	#define E910000002_NETWORKTIMEOUTCNT_SMALLINT 0
	/* Network position count */
	#define E910000002_NETWORKREQCNT_SMALLINT 1
	/* GPS error count */
	#define E910000002_GPSERRORUPLOADCNT_SMALLINT 2
	/* GPS request count */
	#define E910000002_GPSREQCNT_SMALLINT 3
	/* xtra download success count */
	#define E910000002_XTRADLOADCNT_SMALLINT 4
	/* xtra download count */
	#define E910000002_XTRAREQCNT_SMALLINT 5
	/* ntp success count */
	#define E910000002_NTPFLASHSUCCCNT_SMALLINT 6
	/* ntp request count */
	#define E910000002_NTPREQCNT_SMALLINT 7
	/* Whether there is a 35db per day True: have 35db signal
		False: No 35db signal */
	#define E910000002_ISCN0NORMAL_BIT 8
	/* Whether there is a 25db per day True: have 25db signal
		False: No 25db signal */
	#define E910000002_ISCN0NORMAL2_BIT 9
	/* the biggest average CN0 of top 4 CVs in one day */
	#define E910000002_BIGGESTAVGCN0OFTOP4_SMALLINT 10

	/* Event 910001000
		GPS 110x device and firmware exception event */
	/* ErrorCode */
	#define E910001000_ERRORCODE_SMALLINT 0
	/* ChrEventId */
	#define E910001000_CHREVENTID_SMALLINT 1

	/* Event 910800001
		GPS_STATISTICS_EVENT */
	/* description */
	#define E910800001_DESCRIPTION_VARCHAR 0
	/* ChrEventId */
	#define E910800001_CHREVENTID_INT 1

	/* Event 910800002
		GPS_FAULT_EVENT */
	/* description */
	#define E910800002_DESCRIPTION_VARCHAR 0
	/* ChrEventId */
	#define E910800002_CHREVENTID_INT 1

/*** Fingerprint events' keys ***/

	/* Event 912000000
		FP unlock failure event */
	/* HistWidth score */
	#define E912000000_H_WTH_SC_INT 0
	/* oritationScore */
	#define E912000000_CRIT_SC_INT 1
	/* Contrast */
	#define E912000000_CONTRAST_INT 2
	/* front mean */
	#define E912000000_FRONT_AVG_INT 3
	/* dry score */
	#define E912000000_DRY_SC_INT 4
	/* wet score */
	#define E912000000_WET_SC_INT 5
	/* enable fallback or not */
	#define E912000000_FIRST_IMG_INT 6
	/* result */
	#define E912000000_RS_INT 7
	/* score */
	#define E912000000_ALG_SC_INT 8
	/* template index */
	#define E912000000_IDX_INT 9
	/* updated template size */
	#define E912000000_UPD_FLG_INT 10
	/* coverage */
	#define E912000000_COV_INT 11
	/* image quality */
	#define E912000000_QTY_INT 12
	/* spurious triggering */
	#define E912000000_SPR_TR_INT 13
	/* too fast count */
	#define E912000000_FST_CNT_INT 14
	/* liveness on or not */
	#define E912000000_LIVE_ON_INT 15
	/* identify as liveness fake finger */
	#define E912000000_ID_AS_LIVE_INT 16
	/* vendor information */
	#define E912000000_SEN_INF_VARCHAR 17
	/* alg version */
	#define E912000000_ALG_VER_VARCHAR 18
	/* the time between cpu wakeup and interrupt handled */
	#define E912000000_RESUM_T_INT 19
	/* fingerprintDownTime */
	#define E912000000_FPDOW_T_VARCHAR 20
	/* CaptureCompletedTime */
	#define E912000000_CAPCMP_T_INT 21
	/* AuthenticatedTime */
	#define E912000000_AUTH_T_INT 22
	/* screenOnTime */
	#define E912000000_SCRON_T_INT 23

	/* Event 912000001
		FP unlock failure event */
	/* HistWidth score */
	#define E912000001_H_WTH_SC_INT 0
	/* oritationScore */
	#define E912000001_CRIT_SC_INT 1
	/* Contrast */
	#define E912000001_CONTRAST_INT 2
	/* front mean */
	#define E912000001_FRONT_AVG_INT 3
	/* dry score */
	#define E912000001_DRY_SC_INT 4
	/* wet score */
	#define E912000001_WET_SC_INT 5
	/* enable fallback or not */
	#define E912000001_FIRST_IMG_INT 6
	/* result */
	#define E912000001_RS_INT 7
	/* score */
	#define E912000001_ALG_SC_INT 8
	/* template index */
	#define E912000001_IDX_INT 9
	/* updated template size */
	#define E912000001_UPD_FLG_INT 10
	/* coverage */
	#define E912000001_COV_INT 11
	/* image quality */
	#define E912000001_QTY_INT 12
	/* spurious triggering */
	#define E912000001_SPR_TR_INT 13
	/* too fast count */
	#define E912000001_FST_CNT_INT 14
	/* liveness on or not */
	#define E912000001_LIVE_ON_INT 15
	/* identify as liveness fake finger */
	#define E912000001_ID_AS_LIVE_INT 16
	/* vendor information */
	#define E912000001_SEN_INF_VARCHAR 17
	/* alg version */
	#define E912000001_ALG_VER_VARCHAR 18
	/* the time between cpu wakeup and interrupt handled */
	#define E912000001_RESUM_T_INT 19
	/* fingerprintDownTime */
	#define E912000001_FPDOW_T_VARCHAR 20
	/* CaptureCompletedTime */
	#define E912000001_CAPCMP_T_INT 21
	/* AuthenticatedTime */
	#define E912000001_AUTH_T_INT 22
	/* screenOnTime */
	#define E912000001_SCRON_T_INT 23

	/* Event 912000002
		FingerPrint enroll recoard */
	/* HistWidth score */
	#define E912000002_H_WTH_SC_INT 0
	/* oritationScore */
	#define E912000002_CRIT_SC_INT 1
	/* Contrast */
	#define E912000002_CONTRAST_INT 2
	/* front mean */
	#define E912000002_FRONT_AVG_INT 3
	/* dry score */
	#define E912000002_DRY_SC_INT 4
	/* wet score */
	#define E912000002_WET_SC_INT 5
	/* enable fallback or not */
	#define E912000002_FIRST_IMG_INT 6
	/* enrolling template size */
	#define E912000002_TPLT_SZ_INT 7
	/* enrolling template quality */
	#define E912000002_QTY_INT 8
	/* enroll progress */
	#define E912000002_PROG_INT 9
	/* finger down count */
	#define E912000002_DW_CNT_INT 10
	/* vendor information */
	#define E912000002_SEN_INF_VARCHAR 11
	/* alg version */
	#define E912000002_ALG_VER_VARCHAR 12

	/* Event 912000003
		FingerPrint unlcok statistics */
	/* All times */
	#define E912000003_A_T_INT 0
	/* All Fail times for fake finger */
	#define E912000003_LIVE_F_INT 1
	/* All failed times */
	#define E912000003_A_F_T_INT 2
	/* All succ times */
	#define E912000003_A_S_T_INT 3
	/* liveness on or not times */
	#define E912000003_L_ON_CNT_INT 4
	/* identify as liveness fake finger failed times */
	#define E912000003_L_ON_F_CNT_INT 5
	/* 1st succ times */
	#define E912000003_S_T_1_INT 6
	/* 2nd succ times */
	#define E912000003_S_T_2_INT 7
	/* 3rd succ times */
	#define E912000003_S_T_3_INT 8
	/* 4th succ times */
	#define E912000003_S_T_4_INT 9
	/* 5th succ times */
	#define E912000003_S_T_5_INT 10
	/* 6th succ times */
	#define E912000003_S_T_6_INT 11
	/* Others succ times */
	#define E912000003_S_T_OT_INT 12
	/* succ pisc coverage average */
	#define E912000003_SUC_C_AVG_INT 13
	/* succ pisc score average */
	#define E912000003_SUC_SC_AVG_INT 14
	/* succ pisc quality average */
	#define E912000003_SUC_Q_AVG_INT 15
	/* Identify average time */
	#define E912000003_C_ID_T_INT 16
	/* vendor information */
	#define E912000003_SEN_INF_VARCHAR 17
	/* alg version */
	#define E912000003_ALG_VER_VARCHAR 18

	/* Event 912001000
		wait irq error */
	/* error level */
	#define E912001000_ERROR_LEVEL_INT 0
	/* IC name */
	#define E912001000_IC_NAME_VARCHAR 1
	/* module name */
	#define E912001000_MODULE_NAME_VARCHAR 2
	/* description */
	#define E912001000_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E912001000_COUNT_INT 4

	/* Event 912001001
		capture image error */
	/* error level */
	#define E912001001_ERROR_LEVEL_INT 0
	/* IC name */
	#define E912001001_IC_NAME_VARCHAR 1
	/* module name */
	#define E912001001_MODULE_NAME_VARCHAR 2
	/* description */
	#define E912001001_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E912001001_COUNT_INT 4

	/* Event 912001002
		identify error */
	/* error level */
	#define E912001002_ERROR_LEVEL_INT 0
	/* IC name */
	#define E912001002_IC_NAME_VARCHAR 1
	/* module name */
	#define E912001002_MODULE_NAME_VARCHAR 2
	/* description */
	#define E912001002_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E912001002_COUNT_INT 4

	/* Event 912001003
		deadpixel error */
	/* error level */
	#define E912001003_ERROR_LEVEL_INT 0
	/* IC name */
	#define E912001003_IC_NAME_VARCHAR 1
	/* module name */
	#define E912001003_MODULE_NAME_VARCHAR 2
	/* description */
	#define E912001003_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E912001003_COUNT_INT 4

	/* Event 912001004
		enroll error */
	/* error level */
	#define E912001004_ERROR_LEVEL_INT 0
	/* IC name */
	#define E912001004_IC_NAME_VARCHAR 1
	/* module name */
	#define E912001004_MODULE_NAME_VARCHAR 2
	/* description */
	#define E912001004_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E912001004_COUNT_INT 4

	/* Event 912001005
		remove template error */
	/* error level */
	#define E912001005_ERROR_LEVEL_INT 0
	/* IC name */
	#define E912001005_IC_NAME_VARCHAR 1
	/* module name */
	#define E912001005_MODULE_NAME_VARCHAR 2
	/* description */
	#define E912001005_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E912001005_COUNT_INT 4

	/* Event 912001006
		enumerate error */
	/* error level */
	#define E912001006_ERROR_LEVEL_INT 0
	/* IC name */
	#define E912001006_IC_NAME_VARCHAR 1
	/* module name */
	#define E912001006_MODULE_NAME_VARCHAR 2
	/* description */
	#define E912001006_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E912001006_COUNT_INT 4

	/* Event 912001007
		module open error */
	/* error level */
	#define E912001007_ERROR_LEVEL_INT 0
	/* IC name */
	#define E912001007_IC_NAME_VARCHAR 1
	/* module name */
	#define E912001007_MODULE_NAME_VARCHAR 2
	/* description */
	#define E912001007_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E912001007_COUNT_INT 4

	/* Event 912001008
		probe error */
	/* error level */
	#define E912001008_ERROR_LEVEL_INT 0
	/* IC name */
	#define E912001008_IC_NAME_VARCHAR 1
	/* module name */
	#define E912001008_MODULE_NAME_VARCHAR 2
	/* description */
	#define E912001008_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E912001008_COUNT_INT 4

	/* Event 912001009
		diff deadpixel error */
	/* error level */
	#define E912001009_ERROR_LEVEL_INT 0
	/* IC name */
	#define E912001009_IC_NAME_VARCHAR 1
	/* module name */
	#define E912001009_MODULE_NAME_VARCHAR 2
	/* description */
	#define E912001009_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E912001009_COUNT_INT 4

	/* Event 912001010
		many deadpixel error */
	/* error level */
	#define E912001010_ERROR_LEVEL_INT 0
	/* IC name */
	#define E912001010_IC_NAME_VARCHAR 1
	/* module name */
	#define E912001010_MODULE_NAME_VARCHAR 2
	/* description */
	#define E912001010_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E912001010_COUNT_INT 4

	/* Event 912001011
		DB file lost error */
	/* error level */
	#define E912001011_ERROR_LEVEL_INT 0
	/* IC name */
	#define E912001011_IC_NAME_VARCHAR 1
	/* module name */
	#define E912001011_MODULE_NAME_VARCHAR 2
	/* description */
	#define E912001011_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E912001011_COUNT_INT 4

/*** BT events' keys ***/

	/* Event 913000000
		Bluetooth service exception event */
	/* bluetooth error code */
	#define E913000000_BTERRORCODE_INT 0
	/* bluetooth sub error code */
	#define E913000000_BTSUBERRORCODE_INT 1
	/* device name */
	#define E913000000_BTDEVICENAME_VARCHAR 2
	/* vendor ID */
	#define E913000000_BTVENDORID_VARCHAR 3
	/* bluetooth major class type */
	#define E913000000_BTMAJORCLASS_INT 4
	/* sub class type */
	#define E913000000_BTSUBCLASS_INT 5
	/* current profile state */
	#define E913000000_CURRENTPROFILESTATE_INT 6
	/* phone country code */
	#define E913000000_PHONECOUNTRYCODE_VARCHAR 7
	/* flight mode */
	#define E913000000_FLIGHTMODE_INT 8
	/* native is available */
	#define E913000000_NATIVEISAVAILABLE_INT 9
	/* Profiles started */
	#define E913000000_PROFILESSTARTED_INT 10
	/* Is bluetooth cleaning up? */
	#define E913000000_ISCLEANINGUP_INT 11
	/* bluetooth error code */
	#define E913000000_BTERRORCODE_VARCHAR 12
	/* bluetooth sub error code */
	#define E913000000_BTSUBERRORCODE_VARCHAR 13
	/* bluetooth major class type */
	#define E913000000_BTMAJORCLASS_VARCHAR 14
	/* sub class type */
	#define E913000000_BTSUBCLASS_VARCHAR 15
	/* current profile state */
	#define E913000000_CURRENTPROFILESTATE_VARCHAR 16
	/* flight mode */
	#define E913000000_FLIGHTMODE_VARCHAR 17
	/* native is available */
	#define E913000000_NATIVEISAVAILABLE_VARCHAR 18
	/* Profiles started */
	#define E913000000_PROFILESSTARTED_VARCHAR 19
	/* Is bluetooth cleaning up? */
	#define E913000000_ISCLEANINGUP_VARCHAR 20

	/* Event 913000001
		Bluetooth A2DP profile exception event */
	/* bluetooth error code */
	#define E913000001_BTERRORCODE_INT 0
	/* bluetooth sub error code */
	#define E913000001_BTSUBERRORCODE_INT 1
	/* device name */
	#define E913000001_BTDEVICENAME_VARCHAR 2
	/* vendor ID */
	#define E913000001_BTVENDORID_VARCHAR 3
	/* bluetooth major class type */
	#define E913000001_BTMAJORCLASS_INT 4
	/* sub class type */
	#define E913000001_BTSUBCLASS_INT 5
	/* current profile state */
	#define E913000001_CURRENTPROFILESTATE_INT 6
	/* phone country code */
	#define E913000001_PHONECOUNTRYCODE_VARCHAR 7
	/* bluetooth priority */
	#define E913000001_BTPRIORITY_INT 8
	/* flags for transport cnotrol */
	#define E913000001_TRANSPORTCONTROLFLAGS_INT 9
	/* current play state */
	#define E913000001_CURRENTPLAYSTATE_INT 10
	/* play status changed notify */
	#define E913000001_PLAYSTATUSCHANGEDNT_INT 11
	/* track changed notify */
	#define E913000001_TRACKCHANGEDNT_INT 12
	/* track number */
	#define E913000001_TRACKNUMBER_INT 13
	/* ms of current position */
	#define E913000001_CURRENTPOSMS_FLOAT 14
	/* ms of play start time */
	#define E913000001_PLAYSTARTTIMEMS_FLOAT 15
	/* ms of song length */
	#define E913000001_SONGLENGTHMS_FLOAT 16
	/* ms of play back interval */
	#define E913000001_PLAYBACKINTERVALMS_FLOAT 17
	/* notify for play postion changed */
	#define E913000001_PLAYPOSCHANGEDNT_INT 18
	/* ms of next postion */
	#define E913000001_NEXTPOSMS_FLOAT 19
	/* ms of prev postion */
	#define E913000001_PREVPOSMS_FLOAT 20
	/* skip start time */
	#define E913000001_SKIPSTARTTIME_FLOAT 21
	/* features of remote control */
	#define E913000001_BTRCFEATURES_INT 22
	/* volume of absolute */
	#define E913000001_ABSOLUTEVOLUME_INT 23
	/* volume of last set */
	#define E913000001_LASTSETVOLUME_INT 24
	/* last direction */
	#define E913000001_LASTDIRECTION_INT 25
	/* step of volume */
	#define E913000001_VOLUMESTEP_INT 26
	/* max of audio stream */
	#define E913000001_AUDIOSTREAMMAX_INT 27
	/* volume command in progress */
	#define E913000001_VOLCMDINPROGRESS_INT 28
	/* adsolute volume retry times */
	#define E913000001_ABSVOLRETRYTIMES_INT 29
	/* skip amount */
	#define E913000001_SKIPAMOUNT_INT 30
	/* state of song */
	#define E913000001_SONGSTATE_INT 31
	/* state of a2dp */
	#define E913000001_A2DPSTATE_INT 32
	/* state of FFRW */
	#define E913000001_FFRWSTATE_INT 33
	/* state of FFRW */
	#define E913000001_FFRWCNT_INT 34
	/* bluetooth error code */
	#define E913000001_BTERRORCODE_VARCHAR 35
	/* bluetooth sub error code */
	#define E913000001_BTSUBERRORCODE_VARCHAR 36
	/* bluetooth major class type */
	#define E913000001_BTMAJORCLASS_VARCHAR 37
	/* sub class type */
	#define E913000001_BTSUBCLASS_VARCHAR 38
	/* current profile state */
	#define E913000001_CURRENTPROFILESTATE_VARCHAR 39
	/* bluetooth priority */
	#define E913000001_BTPRIORITY_VARCHAR 40
	/* current play state */
	#define E913000001_CURRENTPLAYSTATE_VARCHAR 41
	/* play status changed notify */
	#define E913000001_PLAYSTATUSCHANGEDNT_VARCHAR 42
	/* track changed notify */
	#define E913000001_TRACKCHANGEDNT_VARCHAR 43
	/* notify for play postion changed */
	#define E913000001_PLAYPOSCHANGEDNT_VARCHAR 44
	/* features of remote control */
	#define E913000001_BTRCFEATURES_VARCHAR 45
	/* last direction */
	#define E913000001_LASTDIRECTION_VARCHAR 46
	/* volume command in progress */
	#define E913000001_VOLCMDINPROGRESS_VARCHAR 47
	/* state of song */
	#define E913000001_SONGSTATE_VARCHAR 48
	/* state of a2dp */
	#define E913000001_A2DPSTATE_VARCHAR 49
	/* state of FFRW */
	#define E913000001_FFRWSTATE_VARCHAR 50

	/* Event 913000002
		Bluetooth HFP profile exception event */
	/* bluetooth error code */
	#define E913000002_BTERRORCODE_INT 0
	/* bluetooth sub error code */
	#define E913000002_BTSUBERRORCODE_INT 1
	/* device name */
	#define E913000002_BTDEVICENAME_VARCHAR 2
	/* vendor ID */
	#define E913000002_BTVENDORID_VARCHAR 3
	/* bluetooth major class type */
	#define E913000002_BTMAJORCLASS_INT 4
	/* sub class type */
	#define E913000002_BTSUBCLASS_INT 5
	/* current profile state */
	#define E913000002_CURRENTPROFILESTATE_INT 6
	/* phone country code */
	#define E913000002_PHONECOUNTRYCODE_VARCHAR 7
	/* WBS Informaion */
	#define E913000002_BTWBSINFO_INT 8
	/* is hardware camera opened? */
	#define E913000002_ISHWCAMERAOPEN_INT 9
	/* max connections of HF profile */
	#define E913000002_MAXHFCONNECTIONS_INT 10
	/* is vittual call started? */
	#define E913000002_VIRTUALCALLSTARTED_INT 11
	/* is dialing out? */
	#define E913000002_DIALINGOUT_INT 12
	/* is native available */
	#define E913000002_NATIVEAVAILABLE_INT 13
	/* sco virtual call begin */
	#define E913000002_SCOVIRTUALCALLBEGIN_INT 14
	/* is audio on pending */
	#define E913000002_ISAUDIOONPENDING_INT 15
	/* state of audio */
	#define E913000002_AUDIOSTATE_INT 16
	/* is sco state on? */
	#define E913000002_ISSCOSTATEON_INT 17
	/* is wairting for voice recognition? */
	#define E913000002_WAITINGFORVOICERECOGNITION_INT 18
	/* is voice recognition started */
	#define E913000002_VOICERECOGNITIONSTARTED_INT 19
	/* num active of call */
	#define E913000002_NUMACTIVE_INT 20
	/* main card operator name */
	#define E913000002_SUB0OPERATORNAME_VARCHAR 21
	/* sub card operator name */
	#define E913000002_SUB1OPERATORNAME_VARCHAR 22
	/* phone call state */
	#define E913000002_BTPHONECALLSTATE_INT 23
	/* signal of network */
	#define E913000002_BTSIGNAL_INT 24
	/* roam of phone state */
	#define E913000002_BTPHONEROAM_INT 25
	/* charge level of battery */
	#define E913000002_BATTERYCHARGE_INT 26
	/* volume of speaker */
	#define E913000002_SPEAKERVOLUME_INT 27
	/* volume of mic */
	#define E913000002_MICVOLUME_INT 28
	/* is listening */
	#define E913000002_ISLISTENING_INT 29
	/* is SLC ready? */
	#define E913000002_SLCREADY_INT 30
	/* valid subscription */
	#define E913000002_VALIDSUBSCRIPTION_INT 31
	/* bluetooth error code */
	#define E913000002_BTERRORCODE_VARCHAR 32
	/* bluetooth sub error code */
	#define E913000002_BTSUBERRORCODE_VARCHAR 33
	/* bluetooth major class type */
	#define E913000002_BTMAJORCLASS_VARCHAR 34
	/* sub class type */
	#define E913000002_BTSUBCLASS_VARCHAR 35
	/* current profile state */
	#define E913000002_CURRENTPROFILESTATE_VARCHAR 36
	/* is hardware camera opened? */
	#define E913000002_ISHWCAMERAOPEN_VARCHAR 37
	/* is vittual call started? */
	#define E913000002_VIRTUALCALLSTARTED_VARCHAR 38
	/* is dialing out? */
	#define E913000002_DIALINGOUT_VARCHAR 39
	/* is native available */
	#define E913000002_NATIVEAVAILABLE_VARCHAR 40
	/* sco virtual call begin */
	#define E913000002_SCOVIRTUALCALLBEGIN_VARCHAR 41
	/* is audio on pending */
	#define E913000002_ISAUDIOONPENDING_VARCHAR 42
	/* state of audio */
	#define E913000002_AUDIOSTATE_VARCHAR 43
	/* is sco state on? */
	#define E913000002_ISSCOSTATEON_VARCHAR 44
	/* is wairting for voice recognition? */
	#define E913000002_WAITINGFORVOICERECOGNITION_VARCHAR 45
	/* is voice recognition started */
	#define E913000002_VOICERECOGNITIONSTARTED_VARCHAR 46
	/* phone call state */
	#define E913000002_BTPHONECALLSTATE_VARCHAR 47
	/* roam of phone state */
	#define E913000002_BTPHONEROAM_VARCHAR 48
	/* is listening */
	#define E913000002_ISLISTENING_VARCHAR 49
	/* is SLC ready? */
	#define E913000002_SLCREADY_VARCHAR 50

	/* Event 913000003
		BT exception event */
	/* Bt Error Code */
	#define E913000003_BTERRORCODE_SMALLINT 0
	/* Bt SubErrorCode */
	#define E913000003_BTSUBERRORCODE_SMALLINT 1
	/* Bt Device Name */
	#define E913000003_BTDEVICENAME_VARCHAR 2
	/* Bt Major Class */
	#define E913000003_BTMAJORCLASS_SMALLINT 3
	/* Bt SubClass */
	#define E913000003_BTSUBCLASS_SMALLINT 4

	/* Event 913001000
		Bluetooth connection success rate event */
	/* times of a2dp connect success */
	#define E913001000_A2DPSUCCESS_INT 0
	/* total times of a2dp connection */
	#define E913001000_A2DPALL_INT 1
	/* times of HFP connect success */
	#define E913001000_HFPSUCCESS_INT 2
	/* total times of HFP connection */
	#define E913001000_HFPALL_INT 3
	/* times of bond success */
	#define E913001000_BTSERVICESUCCESS_INT 4
	/* total times of bond success */
	#define E913001000_BTSERVICEALL_INT 5
	/* total time of used interval */
	#define E913001000_STATISTICINTERVALTIME_INT 6
	/* total time of BT open */
	#define E913001000_BTOPENTOTALTIME_INT 7
	/* total count of success connection */
	#define E913001000_TOTALSUCCCONNECTIONCOUNT_INT 8
	/* total count of connection */
	#define E913001000_TOTALCONNECTIONCOUNT_INT 9
	/* a2dp connection error times */
	#define E913001000_A2DPEXCPCOUNT_INT 10
	/* hfp connection error times */
	#define E913001000_HFPEXCPCOUNT_INT 11
	/* bond error times */
	#define E913001000_BTSERVICEEXCPCOUNT_INT 12

	/* Event 913001001
		Bluetooth device information event */
	/* bluetooth error code */
	#define E913001001_BTMAJORCLASS_INT 0
	/* bluetooth sub error code */
	#define E913001001_BTSUBCLASS_INT 1
	/* vendor ID */
	#define E913001001_BTVENDORID_VARCHAR 2
	/* device name */
	#define E913001001_BTNAME_VARCHAR 3
	/* is supported HFP? */
	#define E913001001_ISSUPPORTEDHFP_INT 4
	/* is supported A2DP? */
	#define E913001001_ISSUPPORTEDA2DP_INT 5
	/* is supported A2DP SINK? */
	#define E913001001_ISSUPPORTEDA2DPSINK_INT 6
	/* is supported HID? */
	#define E913001001_ISSUPPORTEDHID_INT 7
	/* is supported HDP? */
	#define E913001001_ISSUPPORTEDHDP_INT 8
	/* is supported PAN? */
	#define E913001001_ISSUPPORTEDPAN_INT 9
	/* is supported GATT? */
	#define E913001001_ISSUPPORTEDGATT_INT 10
	/* is supported MAP? */
	#define E913001001_ISSUPPORTEDMAP_INT 11
	/* is supported HFP Client? */
	#define E913001001_ISSUPPORTEDHFPCLIENT_INT 12
	/* is supported AVRCP Controller? */
	#define E913001001_ISSUPPORTEDAVRCPCONTROLLER_INT 13
	/* is supported SAP? */
	#define E913001001_ISSUPPORTEDSAP_INT 14
	/* version of bluetooth */
	#define E913001001_BTVERSIONS_INT 15
	/* Manufacturer info */
	#define E913001001_BTMANUFACTURER_VARCHAR 16
	/* total count of success connection */
	#define E913001001_SUCCCONNCOUNT_INT 17
	/* total count of connection */
	#define E913001001_TOTALCONNCOUNT_INT 18
	/* is supported AudioSink ? */
	#define E913001001_HAVEAUDIOSINK_INT 19
	/* is supported AudioSource ? */
	#define E913001001_HAVEAUDIOSOURCE_INT 20
	/* is supported AdvAudioDist ? */
	#define E913001001_HAVEADVAUDIODIST_INT 21
	/* is supported HSP ? */
	#define E913001001_HAVEHSP_INT 22
	/* is supported HSP_AG ? */
	#define E913001001_HAVEHSP_AG_INT 23
	/* is supported Handsfree ? */
	#define E913001001_HAVEHANDSFREE_INT 24
	/* is supported Handsfree_AG ? */
	#define E913001001_HAVEHANDSFREE_AG_INT 25
	/* is supported AvrcpController ? */
	#define E913001001_HAVEAVRCPCONTROLLER_INT 26
	/* is supported AvrcpTarget ? */
	#define E913001001_HAVEAVRCPTARGET_INT 27
	/* is supported ObexObjectPush ? */
	#define E913001001_HAVEOBEXOBJECTPUSH_INT 28
	/* is supported Hid ? */
	#define E913001001_HAVEHID_INT 29
	/* is supported Hogp ? */
	#define E913001001_HAVEHOGP_INT 30
	/* is supported PANU ? */
	#define E913001001_HAVEPANU_INT 31
	/* is supported NAP ? */
	#define E913001001_HAVENAP_INT 32
	/* is supported BNEP ? */
	#define E913001001_HAVEBNEP_INT 33
	/* is supported PBAP_PCE ? */
	#define E913001001_HAVEPBAP_PCE_INT 34
	/* is supported PBAP_PSE ? */
	#define E913001001_HAVEPBAP_PSE_INT 35
	/* is supported MAP ? */
	#define E913001001_HAVEMAP_INT 36
	/* is supported MNS ? */
	#define E913001001_HAVEMNS_INT 37
	/* is supported MAS ? */
	#define E913001001_HAVEMAS_INT 38
	/* is supported SAP ? */
	#define E913001001_HAVESAP_INT 39
	/* Chip Company ID */
	#define E913001001_BTCHIPCOMPANYID_VARCHAR 40
	/* Chip Sub Version Number */
	#define E913001001_BTCHIPSUBVERNUM_INT 41
	/* Phone Country Code */
	#define E913001001_PHONECOUNTRYCODE_INT 42
	/* Device Type */
	#define E913001001_BTDEVICETYPE_VARCHAR 43
	/* bluetooth major class type */
	#define E913001001_BTMAJORCLASS_VARCHAR 44
	/* sub class type */
	#define E913001001_BTSUBCLASS_VARCHAR 45
	/* Phone Country Code */
	#define E913001001_PHONECOUNTRYCODE_VARCHAR 46

	/* Event 913002001
		device probe failed */
	/* error level */
	#define E913002001_ERROR_LEVEL_INT 0
	/* IC name */
	#define E913002001_IC_NAME_VARCHAR 1
	/* module name */
	#define E913002001_MODULE_NAME_VARCHAR 2
	/* description */
	#define E913002001_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E913002001_COUNT_INT 4

	/* Event 913002002
		device open failed */
	/* error level */
	#define E913002002_ERROR_LEVEL_INT 0
	/* IC name */
	#define E913002002_IC_NAME_VARCHAR 1
	/* module name */
	#define E913002002_MODULE_NAME_VARCHAR 2
	/* description */
	#define E913002002_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E913002002_COUNT_INT 4

	/* Event 913002003
		firmware download failed */
	/* error level */
	#define E913002003_ERROR_LEVEL_INT 0
	/* IC name */
	#define E913002003_IC_NAME_VARCHAR 1
	/* module name */
	#define E913002003_MODULE_NAME_VARCHAR 2
	/* description */
	#define E913002003_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E913002003_COUNT_INT 4

	/* Event 913002004
		device config fail */
	/* error level */
	#define E913002004_ERROR_LEVEL_INT 0
	/* IC name */
	#define E913002004_IC_NAME_VARCHAR 1
	/* module name */
	#define E913002004_MODULE_NAME_VARCHAR 2
	/* description */
	#define E913002004_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E913002004_COUNT_INT 4

	/* Event 913002005
		device power on failed */
	/* error level */
	#define E913002005_ERROR_LEVEL_INT 0
	/* IC name */
	#define E913002005_IC_NAME_VARCHAR 1
	/* module name */
	#define E913002005_MODULE_NAME_VARCHAR 2
	/* description */
	#define E913002005_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E913002005_COUNT_INT 4

	/* Event 913002006
		Unknown HCI event */
	/* error level */
	#define E913002006_ERROR_LEVEL_INT 0
	/* IC name */
	#define E913002006_IC_NAME_VARCHAR 1
	/* module name */
	#define E913002006_MODULE_NAME_VARCHAR 2
	/* description */
	#define E913002006_DESCRIPTION_VARCHAR 3
	/* report counts */
	#define E913002006_COUNT_INT 4

	/* Event 913800001
		BT_STATISTICS_EVENT */
	/* description */
	#define E913800001_DESCRIPTION_VARCHAR 0
	/* ChrEventId */
	#define E913800001_CHREVENTID_INT 1

	/* Event 913800002
		BT_FAULT_EVENT */
	/* description */
	#define E913800002_DESCRIPTION_VARCHAR 0
	/* ChrEventId */
	#define E913800002_CHREVENTID_INT 1

/*** FileSystem events' keys ***/

	/* Event 914000000
		f2fs file system defrag and general report */
	/* file system space */
	#define E914000000_FS_BLKS_INT 0
	/* lifetime writekbytes */
	#define E914000000_LIFETIME_WB_INT 1
	/* free space */
	#define E914000000_FREE_BLKS_INT 2
	/* fragment of the free space */
	#define E914000000_FRAG_FREE_BLKS_INT 3
	/* fragment score of the free space */
	#define E914000000_FREE_SCORE_FLOAT 4
	/* number of GC */
	#define E914000000_GC_COUNT_INT 5
	/* block number of GC */
	#define E914000000_GC_BLKS_INT 6
	/* total score of all the directory */
	#define E914000000_TOTAL_SCORE_FLOAT 7

	/* Event 914001000
		f2fs file system top app defrag and report */
	/* the name of the app */
	#define E914001000_APP_NAME_VARCHAR 0
	/* total blocks of all the files */
	#define E914001000_TARGET_BLKS_INT 1
	/* files number */
	#define E914001000_FILES_COUNT_INT 2
	/* directory number */
	#define E914001000_DIR_COUNT_INT 3
	/* fragment number */
	#define E914001000_FRAG_EXTENTS_INT 4
	/* fragment blocks */
	#define E914001000_FRAG_BLKS_INT 5

	/* Event 914002000
		top 20 fragment file info */
	/* the name of the file */
	#define E914002000_FILE_NAME_VARCHAR 0
	/* index */
	#define E914002000_INDEX_INT 1
	/* fragment number */
	#define E914002000_FRAG_EXTENTS_INT 2
	/* fragment blocks */
	#define E914002000_FRAG_BLKS_INT 3
	/* total blocks of the file */
	#define E914002000_FILE_BLKS_INT 4

	/* Event 914003000
		top 20 fragment file info */
	/* the name of the file */
	#define E914003000_FILE_NAME_VARCHAR 0
	/* index */
	#define E914003000_INDEX_INT 1
	/* fragment number */
	#define E914003000_FRAG_EXTENTS_INT 2
	/* fragment blocks */
	#define E914003000_FRAG_BLKS_INT 3
	/* total blocks of the file */
	#define E914003000_FILE_BLKS_INT 4

	/* Event 914004000
		the info for fs trimming action */
	/* the space of the userdata partition */
	#define E914004000_TOTAL_SPACE_INT 0
	/* the free space of the userdata partition */
	#define E914004000_FREE_SPACE_INT 1
	/* all the trimmed space */
	#define E914004000_TRIMMED_SPACE_INT 2
	/* the delta time of the trimming */
	#define E914004000_TRIM_DELTA_INT 3
	/* the fs virtual space after trimming */
	#define E914004000_FS_VIRTUALSPACE_AFTERTRIM_INT 4
	/* the fs virtual space trimmed */
	#define E914004000_FS_VIRTUALSPACE_TRIMMED_INT 5
	/* the failed number of trimming */
	#define E914004000_FAILED_NUM_SMALLINT 6
	/* the success number of trimming */
	#define E914004000_SUCC_NUM_SMALLINT 7
	/* the information of the flash vendor */
	#define E914004000_CID_VARCHAR 8

/*** NFC events' keys ***/

	/* Event 915800001
		NFC_STATISTICS_EVENT */
	/* description */
	#define E915800001_DESCRIPTION_VARCHAR 0
	/* ChrEventId */
	#define E915800001_CHREVENTID_INT 1

	/* Event 915800002
		NFC_FAULT_EVENT */
	/* description */
	#define E915800002_DESCRIPTION_VARCHAR 0
	/* ChrEventId */
	#define E915800002_CHREVENTID_INT 1

/*** Audio events' keys ***/

	/* Event 916000001
		Howling Error */
	/* Event Level */
	#define E916000001_EVENTLEVEL_INT 0
	/* Event Module */
	#define E916000001_EVENTMODULE_VARCHAR 1

	/* Event 916000002
		Wind-Noise Error */
	/* Event Level */
	#define E916000002_EVENTLEVEL_INT 0
	/* Event Module */
	#define E916000002_EVENTMODULE_VARCHAR 1

	/* Event 916000003
		Coefficient Divergence */
	/* Event Level */
	#define E916000003_EVENTLEVEL_INT 0
	/* Event Module */
	#define E916000003_EVENTMODULE_VARCHAR 1

	/* Event 916000004
		Active-Time Ratio(%) */
	/* Event Level */
	#define E916000004_EVENTLEVEL_INT 0
	/* Event Module */
	#define E916000004_EVENTMODULE_VARCHAR 1
	/* Probability */
	#define E916000004_PROBABILITY_TINYINT 2

	/* Event 916000005
		ANC Processing/Path Error */
	/* Event Level */
	#define E916000005_EVENTLEVEL_INT 0
	/* Event Module */
	#define E916000005_EVENTMODULE_VARCHAR 1
	/* Cause Case */
	#define E916000005_CAUSECASE_VARCHAR 2

	/* Event 916000006
		OTD (outlier detection) */
	/* Event Level */
	#define E916000006_EVENTLEVEL_INT 0
	/* Event Module */
	#define E916000006_EVENTMODULE_VARCHAR 1

	/* Event 916000101
		Proc Error */
	/* Event Level */
	#define E916000101_EVENTLEVEL_INT 0
	/* Event Module */
	#define E916000101_EVENTMODULE_VARCHAR 1
	/* Description */
	#define E916000101_MAXRDC_INT 2
	/* MAX temperature */
	#define E916000101_MINRDC_INT 3
	/* MAX temperature */
	#define E916000101_MAXTEMP_INT 4
	/* MIN temperature */
	#define E916000101_MINTEMP_INT 5
	/* AVG temperature */
	#define E916000101_AVGTEMP_INT 6
	/* MAX amplitude */
	#define E916000101_MAXAMP_INT 7
	/* MIN amplitude */
	#define E916000101_MINAMP_INT 8
	/* Err code */
	#define E916000101_ERRCODE_INT 9

	/* Event 916000102
		ParaSet Error */
	/* Event Level */
	#define E916000102_EVENTLEVEL_INT 0
	/* Event Module */
	#define E916000102_EVENTMODULE_VARCHAR 1
	/* Description */
	#define E916000102_MAXRDC_INT 2
	/* MAX temperature */
	#define E916000102_MINRDC_INT 3
	/* MAX temperature */
	#define E916000102_MAXTEMP_INT 4
	/* MIN temperature */
	#define E916000102_MINTEMP_INT 5
	/* AVG temperature */
	#define E916000102_AVGTEMP_INT 6
	/* MAX amplitude */
	#define E916000102_MAXAMP_INT 7
	/* MIN amplitude */
	#define E916000102_MINAMP_INT 8
	/* Err position Tag */
	#define E916000102_ERRPOSTAG_VARCHAR 9

	/* Event 916000103
		Malloc Error */
	/* Event Level */
	#define E916000103_EVENTLEVEL_INT 0
	/* Event Module */
	#define E916000103_EVENTMODULE_VARCHAR 1
	/* Description */
	#define E916000103_MAXRDC_INT 2
	/* MAX temperature */
	#define E916000103_MINRDC_INT 3
	/* MAX temperature */
	#define E916000103_MAXTEMP_INT 4
	/* MIN temperature */
	#define E916000103_MINTEMP_INT 5
	/* AVG temperature */
	#define E916000103_AVGTEMP_INT 6
	/* MAX amplitude */
	#define E916000103_MAXAMP_INT 7
	/* MIN amplitude */
	#define E916000103_MINAMP_INT 8
	/* Err position Tag */
	#define E916000103_ERRPOSTAG_VARCHAR 9

	/* Event 916000104
		State Error */
	/* Event Level */
	#define E916000104_EVENTLEVEL_INT 0
	/* Event Module */
	#define E916000104_EVENTMODULE_VARCHAR 1
	/* Description */
	#define E916000104_MAXRDC_INT 2
	/* MAX temperature */
	#define E916000104_MINRDC_INT 3
	/* MAX temperature */
	#define E916000104_MAXTEMP_INT 4
	/* MIN temperature */
	#define E916000104_MINTEMP_INT 5
	/* AVG temperature */
	#define E916000104_AVGTEMP_INT 6
	/* MAX amplitude */
	#define E916000104_MAXAMP_INT 7
	/* MIN amplitude */
	#define E916000104_MINAMP_INT 8
	/* Err position Tag */
	#define E916000104_ERRPOSTAG_VARCHAR 9

/*** SpikeDog events' keys ***/

	/* Event 917001001
		SPIKEDOG_WATCH_EVENT */
	/* rawdata */
	#define E917001001_RAWDATA_VARCHAR 0

/*** Camera events' keys ***/

	/* Event 918000000
		Camera Memory Pool Leak */
	/* algo name */
	#define E918000000_ALGO_NAME_VARCHAR 0
	/* algo type (cap/pre/others) */
	#define E918000000_ALGO_TYPE_VARCHAR 1
	/* memory chunk leaked size total(KB) */
	#define E918000000_LEAK_SIZE_INT 2
	/* memory chunk used size total(KB) */
	#define E918000000_USED_SIZE_INT 3
	/* memory chunk leaked num total(KB) */
	#define E918000000_LEAK_NUM_INT 4

	/* Event 918000001
		Camera Memory Pool Shortage */
	/* memory pool used size total(KB) */
	#define E918000001_ALL_SIZE_INT 0
	/* memory pool max size threshold(KB) */
	#define E918000001_MAX_SIZE_INT 1
	/* alloc size(KB) */
	#define E918000001_ALLOC_SIZE_INT 2
	/* alloc algo name */
	#define E918000001_ALGO_NAME_VARCHAR 3
	/* alloc algo type (cap/pre/others) */
	#define E918000001_ALGO_TYPE_VARCHAR 4

	/* Event 918000002
		Camera Memory Pool Alloc Fail */
	/* memory pool used size total(KB) */
	#define E918000002_ALL_SIZE_INT 0
	/* memory pool max size threshold(KB) */
	#define E918000002_MAX_SIZE_INT 1
	/* system memory total size (KB) */
	#define E918000002_SYS_TOTAL_SIZE_INT 2
	/* system memory free size (KB) */
	#define E918000002_SYS_FREE_SIZE_INT 3
	/* camera graphic memory size (KB) */
	#define E918000002_CAMERA_GRAPHIC_SIZE_INT 4
	/* alloc size(KB) */
	#define E918000002_ALLOC_SIZE_INT 5
	/* mem malloc directly, not reused */
	#define E918000002_INSTANT_FLAG_BIT 6
	/* mem used device (CPU/GPU/IVP) */
	#define E918000002_USED_DEVICE_VARCHAR 7
	/* alloc algo name */
	#define E918000002_ALGO_NAME_VARCHAR 8
	/* alloc algo type (cap/pre/others) */
	#define E918000002_ALGO_TYPE_VARCHAR 9

	/* Event 918000020
		Camera Preview Algo Buffer Ref Leak */
	/* algo name */
	#define E918000020_ALGO_NAME_VARCHAR 0
	/* sensor position (-1unknow/0back/1front) */
	#define E918000020_SENSOR_POSITION_INT 1
	/* buffer ref */
	#define E918000020_BUFFER_REF_INT 2
	/* timeout frame count num */
	#define E918000020_FRAME_COUNT_INT 3
	/* leaked buffer num total */
	#define E918000020_LEAKED_NUM_TOTAL_INT 4

	/* Event 918000021
		Camera Capture Algo Buffer Ref Leak */
	/* snapshot name */
	#define E918000021_SNAPSHOT_NAME_VARCHAR 0
	/* sensor position (-1unknow/0back/1front) */
	#define E918000021_SENSOR_POSITION_INT 1
	/* buffer ref */
	#define E918000021_BUFFER_REF_INT 2
	/* allocate by algo */
	#define E918000021_ALLOCATE_FLAG_BIT 3
	/* snapshot frame index */
	#define E918000021_FRAME_INDEX_INT 4
	/* leaked buffer num total */
	#define E918000021_LEAKED_NUM_TOTAL_INT 5

	/* Event 918000040
		Camera Algo Process Time Out Error */
	/* algo name */
	#define E918000040_ALGO_NAME_VARCHAR 0
	/* sensor position (-1unknow/0back/1front) */
	#define E918000040_SENSOR_POSITION_INT 1
	/* algo type (cap/pre/tiny) */
	#define E918000040_ALGO_TYPE_VARCHAR 2
	/* time cost(ms) */
	#define E918000040_TIME_COST_INT 3
	/* time cost threshold(ms) */
	#define E918000040_TIME_THRESHOLD_INT 4

	/* Event 918000041
		Camera Algo Process Error */
	/* algo name */
	#define E918000041_ALGO_NAME_VARCHAR 0
	/* error type */
	#define E918000041_ERROR_TYPE_VARCHAR 1
	/* error id */
	#define E918000041_ERROR_ID_INT 2
	/* sensor position (-1unknow/0back/1front) */
	#define E918000041_SENSOR_POSITION_INT 3
	/* algo type (cap/pre/tiny) */
	#define E918000041_ALGO_TYPE_VARCHAR 4

	/* Event 918000060
		Camera Snapshot Time Out Error */
	/* snapshot name */
	#define E918000060_SNAPSHOT_NAME_VARCHAR 0
	/* sensor position (-1unknow/0back/1front) */
	#define E918000060_SENSOR_POSITION_INT 1
	/* snapshot frame num needed */
	#define E918000060_FRAME_NUM_NEEDED_INT 2
	/* snapshot frame num received */
	#define E918000060_FRAME_NUM_RECEIVED_INT 3
	/* time cost(ms) */
	#define E918000060_TIME_COST_INT 4
	/* time cost threshold(ms) */
	#define E918000060_TIME_THRESHOLD_INT 5

	/* Event 918000061
		Camera Other Time Out Error */
	/* algo name */
	#define E918000061_ALGO_NAME_VARCHAR 0
	/* monitor item */
	#define E918000061_MONITOR_ITEM_VARCHAR 1
	/* sensor position (-1unknow/0back/1front) */
	#define E918000061_SENSOR_POSITION_INT 2
	/* algo type (cap/pre/tiny) */
	#define E918000061_ALGO_TYPE_VARCHAR 3
	/* time cost(ms) */
	#define E918000061_TIME_COST_INT 4
	/* time cost threshold(ms) */
	#define E918000061_TIME_THRESHOLD_INT 5

	/* Event 918001000
		Camera Memory Pool Alloc Limit */
	/* algo name */
	#define E918001000_ALGO_NAME_VARCHAR 0
	/* algo type (cap/pre/others) */
	#define E918001000_ALGO_TYPE_VARCHAR 1
	/* algo used size(KB) */
	#define E918001000_USED_SIZE_INT 2
	/* algo alloc limit size(KB) */
	#define E918001000_LIMIT_SIZE_INT 3

	/* Event 918001001
		Camera Memory Pool Efficiency Warning */
	/* memory pool used size total(KB) */
	#define E918001001_ALL_SIZE_INT 0
	/* efficiency ratio */
	#define E918001001_RATIO_FLOAT 1
	/* efficiency threshold size(KB) */
	#define E918001001_THRESHOLD_ALL_SIZE_INT 2
	/* efficiency threshold ratio */
	#define E918001001_THRESHOLD_RATIO_FLOAT 3

	/* Event 918001020
		Camera Algo Process Time Out Warning */
	/* algo name */
	#define E918001020_ALGO_NAME_VARCHAR 0
	/* sensor position (-1unknow/0back/1front) */
	#define E918001020_SENSOR_POSITION_INT 1
	/* algo type (cap/pre/tiny) */
	#define E918001020_ALGO_TYPE_VARCHAR 2
	/* time cost(ms) */
	#define E918001020_TIME_COST_INT 3
	/* time cost threshold(ms) */
	#define E918001020_TIME_THRESHOLD_INT 4

	/* Event 918001040
		Camera Snapshot Time Out Warning */
	/* snapshot name */
	#define E918001040_SNAPSHOT_NAME_VARCHAR 0
	/* sensor position (-1unknow/0back/1front) */
	#define E918001040_SENSOR_POSITION_INT 1
	/* snapshot frame num needed */
	#define E918001040_FRAME_NUM_NEEDED_INT 2
	/* snapshot frame num received */
	#define E918001040_FRAME_NUM_RECEIVED_INT 3
	/* time cost(ms) */
	#define E918001040_TIME_COST_INT 4
	/* time cost threshold(ms) */
	#define E918001040_TIME_THRESHOLD_INT 5

	/* Event 918001041
		Camera Other Time Out Warning */
	/* algo name */
	#define E918001041_ALGO_NAME_VARCHAR 0
	/* monitor item */
	#define E918001041_MONITOR_ITEM_VARCHAR 1
	/* sensor position (-1unknow/0back/1front) */
	#define E918001041_SENSOR_POSITION_INT 2
	/* algo type (cap/pre/tiny) */
	#define E918001041_ALGO_TYPE_VARCHAR 3
	/* time cost(ms) */
	#define E918001041_TIME_COST_INT 4
	/* time cost threshold(ms) */
	#define E918001041_TIME_THRESHOLD_INT 5

#ifdef __cplusplus
}
#endif
#endif /* _IMONITOR_KEYS_H_ */
