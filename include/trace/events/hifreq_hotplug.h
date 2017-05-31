#undef TRACE_SYSTEM
#define TRACE_SYSTEM hifreq_hotplug

#if !defined(_TRACE_HIFREQ_HOTPLUG_H) || defined(TRACE_HEADER_MULTI_READ)
#define _TRACE_HIFREQ_HOTPLUG_H

#include <linux/tracepoint.h>

DECLARE_EVENT_CLASS(timer,
	TP_PROTO(unsigned int cpu_id, unsigned int cur_freq,
	         unsigned int target_freq, unsigned int nr_running,
		 int boost, bool offline),
	TP_ARGS(cpu_id, cur_freq, target_freq, nr_running, boost, offline),

	TP_STRUCT__entry(
		__field(unsigned int, cpu_id    )
		__field(unsigned int, cur_freq   )
		__field(unsigned int, target_freq )
		__field(unsigned int, nr_running )
		__field(int, boost )
		__field(bool, offline )
	),

	TP_fast_assign(
		__entry->cpu_id = cpu_id;
		__entry->cur_freq = cur_freq;
		__entry->target_freq = target_freq;
		__entry->nr_running = nr_running;
		__entry->boost = boost;
		__entry->offline = offline;
	),

	TP_printk("cpu=%u cur=%u target=%u nr=%u boost=%d offline=%d",
	          __entry->cpu_id, __entry->cur_freq, __entry->target_freq,
	          __entry->nr_running, __entry->boost, (int)__entry->offline)
);

DEFINE_EVENT(timer, hifreq_hotplug_already,
	TP_PROTO(unsigned int cpu_id, unsigned int cur_freq,
		 unsigned int target_freq, unsigned int nr_running,
		 int boost, bool offline),
	TP_ARGS(cpu_id, cur_freq, target_freq, nr_running, boost, offline)
);

DEFINE_EVENT(timer, hifreq_hotplug_cnt_notyet,
	TP_PROTO(unsigned int cpu_id, unsigned int cur_freq,
		 unsigned int target_freq, unsigned int nr_running,
		 int boost, bool offline),
	TP_ARGS(cpu_id, cur_freq, target_freq, nr_running, boost, offline)
);

DEFINE_EVENT(timer, hifreq_hotplug_time_notyet,
	TP_PROTO(unsigned int cpu_id, unsigned int cur_freq,
		 unsigned int target_freq, unsigned int nr_running,
		 int boost, bool offline),
	TP_ARGS(cpu_id, cur_freq, target_freq, nr_running, boost, offline)
);

DEFINE_EVENT(timer, hifreq_hotplug_wakeup,
	TP_PROTO(unsigned int cpu_id, unsigned int cur_freq,
		 unsigned int target_freq, unsigned int nr_running,
		 int boost, bool offline),
	TP_ARGS(cpu_id, cur_freq, target_freq, nr_running, boost, offline)
);

DECLARE_EVENT_CLASS(task,
	TP_PROTO(unsigned int cpu_id, unsigned int cur_freq,
		 unsigned int target_freq, bool offline),
	TP_ARGS(cpu_id, cur_freq, target_freq, offline),

	TP_STRUCT__entry(
		__field(unsigned int, cpu_id    )
		__field(unsigned int, cur_freq  )
		__field(unsigned int, target_freq )
		__field(bool, offline )
	),

	TP_fast_assign(
		__entry->cpu_id = cpu_id;
		__entry->cur_freq = cur_freq;
		__entry->target_freq = target_freq;
		__entry->offline = offline;
	),

	TP_printk("cpu=%u cur=%u target=%u offline=%d",
	          __entry->cpu_id, __entry->cur_freq, __entry->target_freq,
	          (int)__entry->offline)
);

DEFINE_EVENT(task, hifreq_hotplug_task,
	TP_PROTO(unsigned int cpu_id, unsigned int cur_freq,
		 unsigned int target_freq, bool offline),
	TP_ARGS(cpu_id, cur_freq, target_freq, offline)
);

#endif /* _TRACE_HIFREQ_HOTPLUG_H */

/* This part must be outside protection */
#include <trace/define_trace.h>
