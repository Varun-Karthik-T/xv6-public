#include "types.h"
#include "stat.h"
#include "user.h"
#include <stdarg.h>

// Simple vsnprintf implementation for xv6
int xv6_vsnprintf(char *buf, int size, const char *fmt, va_list args) {
    int written = 0;
    int total_written = 0;

    for (; *fmt != '\0'; ++fmt) {
        if (*fmt != '%') {
            buf[written++] = *fmt;
            ++total_written;
            if (written >= size - 1) {
                break;
            }
            continue;
        }

        ++fmt;

        if (*fmt == 'd') {
            int num = va_arg(args, int);
            int digits = 0;
            int num_tmp = num;

            // Count the number of digits in num
            do {
                ++digits;
                num_tmp /= 10;
            } while (num_tmp != 0);

            // Print the digits of num to buf
            num_tmp = num;
            for (int i = written + digits - 1; i >= written; --i) {
                buf[i] = '0' + (num_tmp % 10);
                num_tmp /= 10;
            }

            written += digits;
            total_written += digits;
        } else if (*fmt == 's') {
            char *str = va_arg(args, char *);
            while (*str != '\0') {
                buf[written++] = *str++;
                ++total_written;
                if (written >= size - 1) {
                    break;
                }
            }
        } else {
            // Unknown format specifier, just print as is
            buf[written++] = *fmt;
            ++total_written;
            if (written >= size - 1) {
                break;
            }
        }
    }

    // Null-terminate the buffer
    buf[written] = '\0';

    return total_written;
}

// Simple implementation of printf for xv6
void xv6_printf(const char *fmt, ...) {
    char buf[256];
    va_list args;
    va_start(args, fmt);
    xv6_vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);

    // Output the formatted string using write system call
    for (int i = 0; buf[i] != '\0'; i++) {
        write(1, &buf[i], 1); // File descriptor 1 is stdout
    }
}

#define NUM_FRAMES 3

// Function to simulate FIFO page replacement algorithm
void fifo_page_replace(int *reference_string, int ref_length, int num_frames) {
    int frames[NUM_FRAMES];
    int next_frame = 0; // Index of the next frame to be replaced

    // Initialize frames
    for (int i = 0; i < NUM_FRAMES; i++) {
        frames[i] = -1; // Empty frame
    }

    int page_faults = 0;

    for (int i = 0; i < ref_length; i++) {
        int page = reference_string[i];
        int frame_index = -1;

        // Check if page is already in memory
        for (int j = 0; j < num_frames; j++) {
            if (frames[j] == page) {
                frame_index = j;
                break;
            }
        }

        if (frame_index == -1) {
            // Page fault
            page_faults++;

            // Replace the oldest page in the frame
            frame_index = next_frame;
            frames[next_frame] = page;
            next_frame = (next_frame + 1) % num_frames;
        }

        // Print the current state of frames
        xv6_printf("Frames after accessing page %d: ", page);
        for (int j = 0; j < num_frames; j++) {
            if (frames[j] == -1) {
                xv6_printf("- ");
            } else {
                xv6_printf("%d ", frames[j]);
            }
        }
        xv6_printf("\n");
    }

    xv6_printf("Total page faults: %d\n", page_faults);
}

int main() {
    int reference_string[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int ref_length = sizeof(reference_string) / sizeof(reference_string[0]);

    xv6_printf("Reference String: ");
    for (int i = 0; i < ref_length; i++) {
        xv6_printf("%d ", reference_string[i]);
    }
    xv6_printf("\n\n");

    xv6_printf("FIFO Page Replacement Algorithm:\n");
    fifo_page_replace(reference_string, ref_length, NUM_FRAMES);

    exit();
}

