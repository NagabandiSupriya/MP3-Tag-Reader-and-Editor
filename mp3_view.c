#include "mp3_header.h"
#include<string.h>

void view(struct MP3 *mp3)  // Function to display MP3 tag contents
{
    mp3->org_mp3_fptr = fopen(mp3->mp3_filename,"r"); // Open MP3 file in read mode

    if(mp3->mp3_filename == NULL)  // Check if file opening failed
    {
        printf("Error");
        return;
    }
    else
    {
        fseek(mp3->org_mp3_fptr,10,SEEK_CUR);  // Skip ID3 header (first 10 bytes)
		char TAG[5];  // Read frame ID
		printf("===================SELECTED VIEW DETAILS====================================\n\n");
		printf("============================================================================\n");
		printf("\t\t MG3 TAG READER AND EDITOR FOR ID3v2\t\t\n");
		printf("============================================================================\n");
        for(int i=0;i<6;i++)  // Loop to read 6 ID3 frames
        {
			TAG[4]='\0';
            fread(TAG,4,1,mp3->org_mp3_fptr);
    
            int frame_size; // Read frame size
            fread(&frame_size,sizeof(int),1,mp3->org_mp3_fptr);

            toggle_endianess(mp3,&frame_size);   // Convert frame size endianess

            fseek(mp3->org_mp3_fptr,3,SEEK_CUR); // Skip frame flags

            tag_to_name(TAG); // Print tag name

            for(int j=0;j<(frame_size-1);j++)  // Read and print frame content
            {
                char ch;
                fread(&ch,1,1,mp3->org_mp3_fptr);
                printf("%c",ch);
            }

            printf("\n");
        }
		printf("====================================================================================\n");
		printf("====================DETAILS DISPLAYED SUCCESSFULLY===================================\n");
    }
}

// Function to map tag ID to readable name
void tag_to_name(char TAG[])
{
	
	if(!(strcmp(TAG,"TIT2")))
	{
		printf("%-20s%-10s","Title",":");
	}
	else if(!(strcmp(TAG,"TPE1")))
	{
		printf("%-20s%-10s","Artist",":");
	}
	else if(!(strcmp(TAG,"TALB")))
	{
		printf("%-20s%-10s","Album",":");
	}
	else if(!(strcmp(TAG,"TYER")))
	{
		printf("%-20s%-10s","Year",":");
	}
	else if(!(strcmp(TAG,"TCON")))
	{
		printf("%-20s%-10s","Music",":");
	}
	else if(!(strcmp(TAG,"COMM")))
	{
		printf("%-20s%-10s","Comment",":");
	}
	else
	{
		printf("TAG not found");
		return ;
	}
}