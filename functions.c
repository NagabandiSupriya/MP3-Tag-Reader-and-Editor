#include "mp3_header.h"
#include<string.h>

// Function to validate command line arguments
int validate_cla(int argc, char *argv[], struct MP3 *mp3)
{
    // If no arguments are passed
    if( argc == 1 )
    {
        // Print usage error message
        printf("------------------------------------------------------------------------------\n");
        printf("ERROR: ./a.out : INVALID ARGUMENTS\n");
        printf("USAGE : To view please pass like: ./a.out -v mp3filename\n");
        printf("To edit please pass like: ./a.out -e -t/-a/-A/-m/-y/-c changing_text mp3filename\n");
        printf("To get help pass like : ./a.out --help\n");
        printf("------------------------------------------------------------------------------\n");
        return 0;
    }

    // If help option is passed
    if( (strcmp(argv[1], "--help") == 0) )
    {
        // Print help menu
        printf("------------------------------->HELP<-----------------------------------------\n");
        printf("1. -v -> to view mp3 file contents\n");
        printf("2. -e -> to edit mp3 file contents\n");
        printf("\t\t2.1. -t -> to edit song title\n");
        printf("\t\t2.2. -a -> to edit artist name\n");
        printf("\t\t2.3. -A -> to edit album name\n");
        printf("\t\t2.4. -y -> to edit year\n");
        printf("\t\t2.5. -m -> to edit content\n");
        printf("\t\t2.6. -c -> to edit comment\n");
        printf("------------------------------------------------------------------------------\n");
        return 0; 
    }

    // If view option is selected
    if(!strcmp(argv[1], "-v"))
    {
        // Check for correct argument count
        if (argc!= 3)
        {
            printf("--------------------------------------------------------------------------\n");
            printf("Invalid arguments for edit option\n");
            printf("To get help pass : ./a,out --help\n");
            printf("--------------------------------------------------------------------------\n");
            return 0;
        }
        else if(argc == 3)
        {
            // Check if file has .mp3 extension
            char * ret = strstr(argv[2],".mp3");
            if(ret == NULL || strcmp(ret,".mp3")!= 0)
            {
                printf("--------------------------------------------------------------------------\n");
                printf("Invalid at 3rd argument please enter valid entry\n");
                printf("3rd argument should have .mp3 file extensions\n");
                printf("--------------------------------------------------------------------------\n");
                return 0;
            }
            // Store mp3 filename
            mp3->mp3_filename=argv[2];
            return VIEW;
        }
    }
    
    // If edit option is selected
    if(!strcmp(argv[1], "-e"))
    {
        // Check for correct argument count
        if (argc ==5)
        {
            // Title tag
            if(!(strcmp(argv[2],"-t")))
            {
                strcpy(mp3->given_tag,"TIT2");
                mp3->given_tag[4]='\0';
            }
            // Artist tag
            else if(!(strcmp(argv[2],"-a")))
            {
                strcpy(mp3->given_tag,"TPE1");
                mp3->given_tag[4]='\0';
            }
            // Album tag
            else if(!(strcmp(argv[2],"-A")))
            {
                strcpy(mp3->given_tag,"TALB");
                mp3->given_tag[4]='\0';
            }
            // Year tag
            else if(!(strcmp(argv[2],"-y")))
            {
                strcpy(mp3->given_tag,"TYER");
                mp3->given_tag[4]='\0';
            }
            // Comment tag
            else if(!(strcmp(argv[2],"-c")))
            {
                strcpy(mp3->given_tag,"COMM");
                mp3->given_tag[4]='\0';
            }
            // Content tag
            else if(!(strcmp(argv[2],"-m")))
            {
                strcpy(mp3->given_tag,"TCON");
                mp3->given_tag[4]='\0';
            }
            // Invalid edit option
            else
            {
                printf("--------------------------------------------------------------------------\n");
                printf("Invalid argument please enter valid entry\n");
                printf("To get help pass : ./a,out --help\n");
                printf("--------------------------------------------------------------------------\n");
                return 0;
            }

            // Check for valid .mp3 file
            char * ret = strstr(argv[4],".mp3");
            if(ret!= NULL && strcmp(ret,".mp3")== 0)
            {
                // Store mp3 filename
                mp3->mp3_filename=argv[4];
                return EDIT;	
            }
            else
            {
                printf("Invalid .mp3 file\n");
                return 0;
            }
        }
        else
        {
            // Invalid argument count
            printf("--------------------------------------------------------------------------\n");
            printf("Invalid argument please enter valid entry\n");
            printf("To get help pass : ./a,out --help\n");
            printf("--------------------------------------------------------------------------\n");
        }
    }
}

// Function to convert big endian to little endian or vice versa
void toggle_endianess(struct MP3 *mp3, int *size)
{
    char *ptr;
    
    // Typecast integer pointer to char pointer
    ptr = (char*) size;
    
    // Swap bytes to change endianess
    for(int i=0;i<2;i++)
    {
        char temp = ptr[i];
        ptr[i]=ptr[4-i-1];
        ptr[4-i-1]=temp;
    }
}
