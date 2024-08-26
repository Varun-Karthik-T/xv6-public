#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

void copy(const char *src, const char *dest) {
    int src_fd, dest_fd, n;
    char buf[512];

    if ((src_fd = open(src, O_RDONLY)) < 0) {
        printf(2, "cp: cannot open %s\n", src);
        return;
    }

    if ((dest_fd = open(dest, O_CREATE | O_WRONLY)) < 0) {
        printf(2, "cp: cannot open %s\n", dest);
        close(src_fd);
        return;
    }

    while ((n = read(src_fd, buf, sizeof(buf))) > 0) {
        if (write(dest_fd, buf, n) != n) {
            printf(2, "cp: write error to %s\n", dest);
            close(src_fd);
            close(dest_fd);
            return;
        }
    }

    if (n < 0) {
        printf(2, "cp: read error from %s\n", src);
    }

    close(src_fd);
    close(dest_fd);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf(2, "Usage: cp source destination\n");
        exit();
    }

    copy(argv[1], argv[2]);
    exit();
}
