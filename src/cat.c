#include "common.h"
#define FLAGS_IMPLEMENTATION
#include "flags.h"

typedef struct {
    bool line_numbers;
} config_t;

char* read_entrie_file
(FILE* file,uint32_t* count)
{
    int64_t size = 0,current_pos = 0;
    current_pos = ftell(file);
    if(current_pos == -1L) return 0;
    if(fseek(file, 0, SEEK_END) != 0) return 0;
    size = ftell(file);
    if(size == -1L) return 0;
    if(fseek(file, current_pos, SEEK_SET) != 0) return 0;
    char* buffer = calloc(size,sizeof(char));
    if(!buffer) return 0;
    *count = fread(buffer,sizeof(char),size,file);
    if(*count != size) {free(buffer);return 0;}
    return buffer;
}

bool cat(char* path,config_t* conf)
{
    printf("\n");
    uint32_t count = 0;
    char* buf = 0;
    FILE* fptr = 0;
    fptr = fopen(path,"r");
    if(!fptr) return false;
    buf = read_entrie_file(fptr,&count);
    if(!conf->line_numbers)
    {
        printf("%s",buf);
    }
    else
    {
        uint32_t line = 0;
        char* ptr1 = 0;
        char* ptr2 = buf;
        while(1){
            line++;
            ptr1 = 0;
            ptr1 = strchr(ptr2,'\n');
            if(!ptr1)
            {
                printf("  %d  %s",line,ptr2);
                break;
            }
            if(*(ptr1+1) == 10) {printf("  %d\n",++line);}
            *(ptr1+1) = 0;
            printf("  %d  %s",line,ptr2);
            ptr2 = ptr1+2;
        }
    }
    printf("\n");
    free(buf);
    return true;
}

config_t conf = {0};
flag_t flags[] = {
    {.flag = "number",.desc = "enables the line numbers",.addr = &conf.line_numbers,.type = as_bool},
    {.flag = "n",.desc = "enables the line numbers",.addr = &conf.line_numbers,.type = as_bool},
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
        printf("Usage: cat [FILES]\n");
    }
    for(uint32_t i = 0;i < argc;++i)
    {
        if(!cat(argv[i],&conf))
        {
            printf("cat failed: %s : %s\n",argv[i],strerror(errno));
        }
    }
    return 0;
}
