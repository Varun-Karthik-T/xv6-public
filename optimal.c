#include "types.h"
#include "user.h"

#define NUM_FRAMES 3

// Function to find the index of the page with the furthest access in the future
int find_optimal(int *frames, int *reference_string, int current_index, int ref_length)
{
    int max_index = -1;
    int max_future_access = -1;

    for (int i = 0; i < NUM_FRAMES; i++)
    {
        int page = frames[i];
        int future_access = ref_length;

        for (int j = current_index + 1; j < ref_length; j++)
        {
            if (reference_string[j] == page)
            {
                future_access = j;
                break;
            }
        }

        if (future_access > max_future_access)
        {
            max_future_access = future_access;
            max_index = i;
        }
    }

    return max_index;
}

// Function to simulate Optimal page replacement algorithm
void optimal_page_replace(int *reference_string, int ref_length)
{
    int frames[NUM_FRAMES];

    // Initialize frames array
    for (int i = 0; i < NUM_FRAMES; i++)
    {
        frames[i] = -1; // Empty frame
    }

    int page_faults = 0;

    for (int i = 0; i < ref_length; i++)
    {
        int page = reference_string[i];
        int frame_index = -1;

        // Check if page is already in memory
        for (int j = 0; j < NUM_FRAMES; j++)
        {
            if (frames[j] == page)
            {
                frame_index = j;
                break;
            }
        }

        if (frame_index == -1)
        {
            // Page fault
            page_faults++;

            // Find the page with the furthest access in the future
            frame_index = find_optimal(frames, reference_string, i, ref_length);

            // Replace the page with the furthest access in the future with the new page
            frames[frame_index] = page;
        }

        // Print the current state of frames after each page access
        printf(1, "Frames after accessing page %d: ", page);
        for (int j = 0; j < NUM_FRAMES; j++)
        {
            if (frames[j] == -1)
            {
                printf(1, "- ");
            }
            else
            {
                printf(1, "%d ", frames[j]);
            }
        }
        printf(1, "\n");
    }

    printf(1, "Total page faults: %d\n", page_faults);
}

int main()
{
    int reference_string[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int ref_length = sizeof(reference_string) / sizeof(reference_string[0]);

    printf(1, "Reference String: ");
    for (int i = 0; i < ref_length; i++)
    {
        printf(1, "%d ", reference_string[i]);
    }
    printf(1, "\n\n");

    printf(1, "Optimal Page Replacement Algorithm:\n");
    optimal_page_replace(reference_string, ref_length);

    exit();
}
