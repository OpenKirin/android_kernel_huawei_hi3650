#ifdef DWC_NOTIFYLIB

#include "dwc_notifier.h"
#include "dwc_list.h"
/*lint -e717 -e826*/
typedef struct dwc_observer {
	void *observer;
	dwc_notifier_callback_t callback;
	void *data;
	char *notification;
	DWC_CIRCLEQ_ENTRY(dwc_observer) list_entry;
} observer_t;

DWC_CIRCLEQ_HEAD(observer_queue, dwc_observer);

typedef struct dwc_notifier {
	void *mem_ctx;
	void *object;
	struct observer_queue observers;
	DWC_CIRCLEQ_ENTRY(dwc_notifier) list_entry;
} notifier_t;

DWC_CIRCLEQ_HEAD(notifier_queue, dwc_notifier);
typedef struct manager {
	dwc_workq_t *wq;
/*	dwc_mutex_t *mutex; */
	struct notifier_queue notifiers;
} manager_t;
static manager_t *manager;

/*lint -e715*/
static int create_manager(const void *mem_ctx, const void *wkq_ctx)
{
	manager = dwc_alloc(mem_ctx, sizeof(manager_t));
	if (!manager) {
		return -DWC_E_NO_MEMORY;
	}

	DWC_CIRCLEQ_INIT(&manager->notifiers);

	manager->wq = dwc_workq_alloc(wkq_ctx, "DWC Notification WorkQ");
	if (!manager->wq) {
		return -DWC_E_NO_MEMORY;
	}

	return 0;
}
/*lint +e715*/
static void free_manager(void)
{
	dwc_workq_free(manager->wq);

	/* All notifiers must have unregistered themselves before this module
	 * can be removed.  Hitting this assertion indicates a programmer
	 * error. */
	DWC_ASSERT(DWC_CIRCLEQ_EMPTY(&manager->notifiers),
		   "Notification manager being freed before all notifiers have been removed");
	dwc_free(manager->mem_ctx, manager);
}

#ifdef DEBUG
static void dump_manager(void)
{
	notifier_t *n;
	observer_t *o;

	DWC_ASSERT(manager, "Notification manager not found");

	DWC_DEBUG("List of all notifiers and observers:\n");
	DWC_CIRCLEQ_FOREACH(n, &manager->notifiers, list_entry) {
		DWC_DEBUG("Notifier %pK has observers:\n", n->object);
		DWC_CIRCLEQ_FOREACH(o, &n->observers, list_entry) {
			DWC_DEBUG("    %pK watching %s\n", o->observer, o->notification);
		}
	}
}
#else
#define dump_manager(...)
#endif

/*lint -e715*/
static observer_t *alloc_observer(const void *mem_ctx, void *observer, char *notification,
				  dwc_notifier_callback_t callback, void *data)
{
	observer_t *new_observer = dwc_alloc(mem_ctx, sizeof(observer_t));

	if (!new_observer) {
		return NULL;
	}

	DWC_CIRCLEQ_INIT_ENTRY(new_observer, list_entry);
	new_observer->observer = observer;
	new_observer->notification = notification;
	new_observer->callback = callback;
	new_observer->data = data;
	return new_observer;
}
/*lint +e715*/

/*lint -e715*/
static void free_observer(const void *mem_ctx, observer_t *observer)
{
	dwc_free(mem_ctx, observer);
}
/*lint +e715*/

static notifier_t *alloc_notifier(void *mem_ctx, void *object)
{
	notifier_t *notifier;

	if (!object) {
		return NULL;
	}

	notifier = dwc_alloc(mem_ctx, sizeof(notifier_t));
	if (!notifier) {
		return NULL;
	}

	DWC_CIRCLEQ_INIT(&notifier->observers);
	DWC_CIRCLEQ_INIT_ENTRY(notifier, list_entry);

	notifier->mem_ctx = mem_ctx;
	notifier->object = object;
	return notifier;
}

static void free_notifier(notifier_t *notifier)
{
	observer_t *observer, *next_observer;

	DWC_CIRCLEQ_FOREACH_SAFE(observer, next_observer, &notifier->observers, list_entry) {
		free_observer(notifier->mem_ctx, observer);
	}

	dwc_free(notifier->mem_ctx, notifier);
}

static notifier_t *find_notifier(const void *object)
{
	notifier_t *notifier;

	DWC_ASSERT(manager, "Notification manager not found");

	if (!object) {
		return NULL;
	}

	DWC_CIRCLEQ_FOREACH(notifier, &manager->notifiers, list_entry) {
		if (notifier->object == object) {
			return notifier;
		}
	}

	return NULL;
}

int dwc_alloc_notification_manager(const void *mem_ctx, const void *wkq_ctx)
{
	return create_manager(mem_ctx, wkq_ctx);
}

void dwc_free_notification_manager(void)
{
	free_manager();
}

dwc_notifier_t *dwc_register_notifier(void *mem_ctx, void *object)
{
	notifier_t *notifier;

	DWC_ASSERT(manager, "Notification manager not found");

	notifier = find_notifier(object);
	if (notifier) {
		DWC_ERROR("Notifier %pK is already registered\n", object);
		return NULL;
	}

	notifier = alloc_notifier(mem_ctx, object);
	if (!notifier) {
		return NULL;
	}

	DWC_CIRCLEQ_INSERT_TAIL(&manager->notifiers, notifier, list_entry);

	DWC_INFO("Notifier %pK registered", object);
	dump_manager();

	return notifier;
}

void dwc_unregister_notifier(dwc_notifier_t *notifier)
{
	DWC_ASSERT(manager, "Notification manager not found");

	if (!DWC_CIRCLEQ_EMPTY(&notifier->observers)) {
		observer_t *o;

		DWC_ERROR("Notifier %pK has active observers when removing\n", notifier->object);
		DWC_CIRCLEQ_FOREACH(o, &notifier->observers, list_entry) {
			DWC_DEBUG("    %pK watching %s\n", o->observer, o->notification);
		}

		DWC_ASSERT(DWC_CIRCLEQ_EMPTY(&notifier->observers),
			   "Notifier %pK has active observers when removing", notifier);
	}

	DWC_CIRCLEQ_REMOVE_INIT(&manager->notifiers, notifier, list_entry);
	free_notifier(notifier);

	DWC_INFO("Notifier unregistered");
	dump_manager();
}

/* Add an observer to observe the notifier for a particular state, event, or notification. */
int dwc_add_observer(void *observer, void *object, char *notification,
			dwc_notifier_callback_t callback, void *data)
{
	notifier_t *notifier = find_notifier(object);
	observer_t *new_observer;

	if (!notifier) {
		DWC_ERROR("Notifier %pK is not found when adding observer\n", object);
		return -DWC_E_INVALID;
	}

	new_observer = alloc_observer(notifier->mem_ctx, observer, notification, callback, data);
	if (!new_observer) {
		return -DWC_E_NO_MEMORY;
	}

	DWC_CIRCLEQ_INSERT_TAIL(&notifier->observers, new_observer, list_entry);

	DWC_INFO("Added observer %pK to notifier %pK observing notification %s, callback=%pK, data=%pK",
		observer, object, notification, callback, data);

	dump_manager();
	return 0;
}

int dwc_remove_observer(const void *observer)
{
	notifier_t *n;

	DWC_ASSERT(manager, "Notification manager not found");

	DWC_CIRCLEQ_FOREACH(n, &manager->notifiers, list_entry) {
		observer_t *o;
		observer_t *o2;

		DWC_CIRCLEQ_FOREACH_SAFE(o, o2, &n->observers, list_entry) {
			if (o->observer == observer) {
				DWC_CIRCLEQ_REMOVE_INIT(&n->observers, o, list_entry);
				DWC_INFO("Removing observer %pK from notifier %pK watching notification %s:",
					 o->observer, n->object, o->notification);
				free_observer(n->mem_ctx, o);
			}
		}
	}

	dump_manager();
	return 0;
}

typedef struct callback_data {
	void *mem_ctx;
	dwc_notifier_callback_t cb;
	void *observer;
	void *data;
	void *object;
	char *notification;
	void *notification_data;
} cb_data_t;

static void cb_task(void *data)
{
	cb_data_t *cb = (cb_data_t *)data;

	cb->cb(cb->object, cb->notification, cb->observer, cb->notification_data, cb->data);
	dwc_free(cb->mem_ctx, cb);
}

void dwc_notify(const dwc_notifier_t *notifier, char *notification, void *notification_data)
{
	observer_t *o;

	DWC_ASSERT(manager, "Notification manager not found");

	DWC_CIRCLEQ_FOREACH(o, &notifier->observers, list_entry) {
		int len = DWC_STRLEN(notification);

		if (DWC_STRLEN(o->notification) != len) {
			continue;
		}

		if (DWC_STRNCMP(o->notification, notification, (uint32_t)len) == 0) {
			cb_data_t *cb_data = dwc_alloc(notifier->mem_ctx, sizeof(cb_data_t));

			if (!cb_data) {
				DWC_ERROR("Failed to allocate callback data\n");
				return;
			}

			cb_data->mem_ctx = notifier->mem_ctx;
			cb_data->cb = o->callback;
			cb_data->observer = o->observer;
			cb_data->data = o->data;
			cb_data->object = notifier->object;
			cb_data->notification = notification;
			cb_data->notification_data = notification_data;
			DWC_DEBUG("Observer found %pK for notification %s\n", o->observer, notification);
			DWC_WORKQ_SCHEDULE(manager->wq, cb_task, cb_data,
					   "Notify callback from %pK for Notification %s, to observer %pK",
					   cb_data->object, notification, cb_data->observer);
		}
	}
}
/*lint +e717 +e826*/

#endif	/* DWC_NOTIFYLIB */
