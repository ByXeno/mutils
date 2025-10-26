#include "common.h"
#define FLAGS_IMPLEMENTATION
#include "flags.h"

static uint64_t mode = 0755;
flag_t flags[] = {
    {.flag = "mode",.desc = "sets the direcotries mode",.addr = &mode,.type = as_oct},
    {.flag = "m",.desc = "sets the direcotries mode",.addr = &mode,.type = as_oct},
};

int main(int argc,char** argv)
{
    if(!flags_parse(flags,sizeof(flags)/sizeof(flags[0]),&argc,&argv))
    {
        flags_error();
        return 1;
    }
    if(argc < 1)
    {
        printf("Usage: mkdir [DIR]\n");
        return 0;
    }
    for(uint32_t i = 0;i < argc;++i)
    {
        if(mkdirat(AT_FDCWD,argv[i],mode) != 0)
        {
            printf("mkdir failed: %s : %s\n",argv[i],strerror(errno));
        }
    }
    return 0;
}
