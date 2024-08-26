#include "types.h"
#include "stat.h"
#include "user.h"

int main(void) {
    int time = uptime();
    printf(1, "Uptime: %d ticks\n", time);
    exit();
}
