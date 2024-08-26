#include "types.h"
#include "user.h"
#include "date.h"

int main(void) {
    struct rtcdate r;

    if (getdate(&r) < 0) {
        printf(2, "date: error getting date\n");
        exit();
    }

    printf(1, "Current date and time: %d-%d-%d %d:%d:%d\n",
           r.year, r.month, r.day,
           r.hour, r.minute, r.second);
    exit();
}
