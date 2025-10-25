
#define _DEFAULT_SOURCE
#include "common.h"
#include <dirent.h>

bool ls(char* path)
{
    struct dirent **namelist;
    int n = scandir(path, &namelist, NULL, alphasort);
    if (n < 0) return false;
    for (int i = 0; i < n; i++) {
        printf("%s\n", namelist[i]->d_name);
        free(namelist[i]);
    }
    free(namelist);
    return true;
}

int main(int argc,char** argv)
{
    uint32_t i = 1;
    if(argc == 1)
    {
        ls(".");
    }
    for(;i < argc;++i)
    {
        if(!ls(argv[i]))
        {
            fprintf(stderr,"ls failed: %s : %s\n",argv[i],strerror(errno));
        }
    }
    return 0;
}
