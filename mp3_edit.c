#include "mp3_header.h"
#include <string.h>

void edit(int argc, char *argv[], struct MP3 *mp3)
{
    mp3->dup_mp3_fptr = fopen("temp.mp3", "w");       // create temp file to store modified data
    mp3->org_mp3_fptr = fopen(mp3->mp3_filename, "r"); // open original mp3 file

    char header[10];
    fread(header, 10, 1, mp3->org_mp3_fptr);          // read first 10 bytes (ID3 header)
    fwrite(header, 10, 1, mp3->dup_mp3_fptr);         // copy ID3 header to temp file
    printf("--------------------SELECTED EDIT DETAILS-------------------\n\n");
    printf("--------------------SELECTED EDIT OPTION---------------\n");

    for (int i = 0; i < 6; i++)                        // process first 6 ID3 frames
    {
        char TAG[5] = {0};
        fread(TAG, 4, 1, mp3->org_mp3_fptr);          // read frame ID (ex: TIT2)
        fwrite(TAG, 4, 1, mp3->dup_mp3_fptr);         // write same frame ID to temp file

        if (strcmp(mp3->given_tag, TAG) != 0)         // check if this is NOT the required tag
        {
            int frame_size;
            fread(&frame_size, 4, 1, mp3->org_mp3_fptr); // read size of current frame
            fwrite(&frame_size, 4, 1, mp3->dup_mp3_fptr);// copy frame size

            char flag[3];
            fread(flag, 3, 1, mp3->org_mp3_fptr);     // read frame flags
            fwrite(flag, 3, 1, mp3->dup_mp3_fptr);    // copy frame flags

            toggle_endianess(mp3, &frame_size);       // convert frame size for correct reading

            for (int j = 0; j < frame_size - 1; j++)  // copy entire frame data
            {
                char ch;
                fread(&ch, 1, 1, mp3->org_mp3_fptr);  // read one byte from original file
                fwrite(&ch, 1, 1, mp3->dup_mp3_fptr); // write it to temp file
            }
        }
        else                                          // required tag found
        {
            int frame_size;
            fread(&frame_size, 4, 1, mp3->org_mp3_fptr); // read old frame size
            toggle_endianess(mp3, &frame_size);       // convert old frame size

            int new_size = strlen(argv[3]) + 1;       // calculate new tag size
            toggle_endianess(mp3, &new_size);         // convert new size to big endian
            fwrite(&new_size, 4, 1, mp3->dup_mp3_fptr); // write new frame size

            char flag[3];
            fread(flag, 3, 1, mp3->org_mp3_fptr);     // read frame flags
            fwrite(flag, 3, 1, mp3->dup_mp3_fptr);    // copy flags

            toggle_endianess(mp3, &new_size);         // convert back for writing data
            fwrite(argv[3], new_size - 1, 1, mp3->dup_mp3_fptr); // write new tag value

            fseek(mp3->org_mp3_fptr, frame_size - 1, SEEK_CUR); // skip old tag data
            break;                                    // stop after editing one tag
        }
    }

    print_tag_data(mp3);                              // copy remaining mp3 audio data
    remove(mp3->mp3_filename);                        // delete original mp3 file
    rename("temp.mp3", mp3->mp3_filename);            // rename temp file as original

    fclose(mp3->org_mp3_fptr);                        // close original file
    fclose(mp3->dup_mp3_fptr);                        // close temp file
}

void print_tag_data(struct MP3 *mp3)
{
    char ch;
    while (fread(&ch, 1, 1, mp3->org_mp3_fptr) == 1)   // read till end of file
    {
        fwrite(&ch, 1, 1, mp3->dup_mp3_fptr);          // write remaining data
    }
}
