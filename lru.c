#include "types.h"
#include "user.h"

#define NUM_FRAMES 3

int find_lru(int *frames, int *last_used, int num_frames)
{
    int min_index = 0;
    int min_used = last_used[0];

    for (int i = 1; i < num_frames; i++)
    {
        if (last_used[i] < min_used)
        {
            min_used = last_used[i];
            min_index = i;
        }
    }

    return min_index;
}

void lru_page_replace(int *reference_string, int ref_length, int num_frames)
{
    int frames[num_frames], last_used[num_frames];
    for (int i = 0; i < num_frames; i++)
    {
        frames[i] = -1;
        last_used[i] = 0;
    }

    int page_faults = 0;

    for (int i = 0; i < ref_length; i++)
    {
        int page = reference_string[i], frame_index = -1;
        for (int j = 0; j < num_frames; j++)
        {
            if (frames[j] == page)
            {
                frame_index = j;
                break;
            }
        }

        if (frame_index == -1)
        {
            page_faults++;
            frame_index = find_lru(frames, last_used, num_frames);
            frames[frame_index] = page;
        }

        last_used[frame_index] = i + 1;
        printf(1, "Frames after accessing page %d: ", page);
        for (int j = 0; j < num_frames; j++)
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
    printf(1, "LRU Page Replacement Algorithm:\n");
    lru_page_replace(reference_string, ref_length, NUM_FRAMES);
    exit();
}
