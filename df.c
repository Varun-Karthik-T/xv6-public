#include "types.h"
#include "stat.h"
#include "user.h"

int main(void) {
    if (df() < 0) {
        printf(2, "df: error retrieving disk usage\n");
        exit();
    }
    exit();
}
