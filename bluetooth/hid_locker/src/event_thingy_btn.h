#include "event_manager.h"

struct event_thingy_btn {
        struct event_header header;

        u8_t btn_val;
};

EVENT_TYPE_DECLARE(event_thingy_btn);