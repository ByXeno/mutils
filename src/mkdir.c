#include "common.h"

int main(int argc,char** argv)
{
    if(argc <= 1)
    {
        printf("Usage: mkdir [DIR]\n");
        return 0;
    }
    uint32_t i = 1;
    uint32_t mode = 0755;
    for(;i < argc;++i)
    {
        char* flag = argv[i];
        if(*flag != '-') continue;
        if(*flag == '-') flag++;
        if(*flag == '-') flag++;
        if((strcmp(flag,"m") == 0) || (strcmp(flag,"mode")))
        {
            char* eq = strchr(flag,'=');
            if(eq == 0)
            {
                if(i+1>=argc)
                {
                    printf("mkdir failed: Argument is not given\n");
                    return 1;
                }
                *argv[i] = 0;
                i++;
                mode = atol(argv[i]);
            }
            else
            {
                if(*(eq+1) == 0)
                {
                    printf("mkdir failed: Argument's parameter is not given\n");
                    return 1;
                }
                mode = atol(eq+1);
            }
        }
        *argv[i] = 0;
    }
    for(i = 1;i < argc;++i)
    {
        if(!(*argv[i])) continue;
        if(mkdirat(AT_FDCWD,argv[i],mode) != 0)
        {
            printf("mkdir failed: %s : %s\n",argv[i],strerror(errno));
        }
    }
    return 0;
}
