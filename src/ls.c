#define _DEFAULT_SOURCE
#include "common.h"

typedef struct {
    bool no_color;
    uint32_t off_count;
} config_t;

bool ls(char* path,config_t* conf)
{
    struct dirent **list;
    int n = scandir(path, &list, NULL, alphasort);
    if (n < 0) return false;
    char off[conf->off_count+1];
    memset(off,' ',conf->off_count);
    off[conf->off_count] = 0;
    for (int i = 0; i < n; i++) {
        if(*list[i]->d_name == '.') continue;
        if(conf->no_color) {
            printf("%s %s\n",off,list[i]->d_name);
        }
        else
        {
            switch(list[i]->d_type)
            {
                case DT_DIR:  { printf("%s"CYAN"%s\n"RESET, off, list[i]->d_name); } break;
                case DT_LNK:  { printf("%s"BLUE"%s\n"RESET, off, list[i]->d_name); } break;
                case DT_SOCK: { printf("%s"GREEN"%s\n"RESET, off, list[i]->d_name); } break;
                case DT_BLK:  { printf("%s"MAGENTA"%s\n"RESET, off, list[i]->d_name); } break;
                case DT_CHR:  { printf("%s"YELLOW"%s\n"RESET, off,list[i]->d_name); } break;
                case DT_FIFO: { printf("%s"YELLOW"%s\n"RESET, off,list[i]->d_name); } break;
                case DT_REG:  { printf("%s %s\n", off, list[i]->d_name); } break;
                case DT_UNKNOWN: { printf("%s"BG_BWHITE BLACK"%s\n"RESET, off ,list[i]->d_name); } break;
            }
        }
        free(list[i]);
    }
    free(list);
    return true;
}

int main(int argc,char** argv)
{
    config_t conf = {.off_count=4};
    uint32_t i = 1;
    if(argc == 1)
    {
        if(!ls(".",&conf))
        {
            fprintf(stderr,"ls failed: . : %s\n",strerror(errno));
        }
    }
    for(i = 1;i < argc;++i)
    {
        char* flag = argv[i];
        if(*flag != '-') continue;
        if(*flag == '-') flag++;
        if(*flag == '-') flag++;
        if(strcmp(flag,"nocolor") == 0)
        {
            conf.no_color = true;
        }
        else
        {
            printf("Unknown flag %s \n",flag);
        }
        *argv[i] = 0;
    }
    for(i = 1;i < argc;++i)
    {
        if(!(*argv[i])) continue;
        printf("%s:\n",argv[i]);
        if(!ls(argv[i],&conf))
        {
            fprintf(stderr,"ls failed: %s : %s\n",argv[i],strerror(errno));
        }
    }
    return 0;
}
