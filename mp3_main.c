#include "mp3_header.h"

int main(int argc, char *argv[])
{
    struct MP3 mp3;

    int ret = validate_cla(argc,argv,&mp3);
    if(ret == VIEW)
    {
        view(&mp3); // calling the view function
        printf("%s",argv[2]);

    }
    else if(ret == EDIT)
    {
        edit(argc,argv,&mp3); // calling the edit function
        printf("Completed Editing....\n");   
    }

    return 0;

}
