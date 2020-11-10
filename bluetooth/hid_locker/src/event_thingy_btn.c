#include "event_thingy_btn.h"

static int log_event_thingy_btn(const struct event_header *eh, char *buf,
                            size_t buf_len)
{
        struct event_thingy_btn *event = cast_event_thingy_btn(eh);

        return snprintf(buf, buf_len, "val1=%d", event->btn_val);
}

EVENT_TYPE_DEFINE(event_thingy_btn,         /* Unique event name. */
                  false,                 /* Event logged by default. */
                  log_event_thingy_btn,     /* Function logging event data. */
                  NULL);                /* No event info provided. */