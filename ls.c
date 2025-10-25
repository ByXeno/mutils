
#include "common.h"
#include <dirent.h>

char cast_to_lower(char c)
{
    if('A' <= c && c <= 'Z')
    {return c+32;}
    return c;
}

char** compare_strings(char** item, char** stack, uint32_t j) {
    char *str1 = *item;
    char *str2 = stack[j];
    uint32_t k = 0;
    while (1) {
        char c1 = cast_to_lower(str1[k]);
        char c2 = cast_to_lower(str2[k]);
        if (c1 == '\0' && c2 == '\0') return item;
        if (c1 == '\0') return item;
        if (c2 == '\0') return &stack[j];
        if (c1 > c2) return &stack[j];
        if (c1 < c2) return item;
        k++;
    }
}

bool ls(char* path)
{
    DIR* d = opendir(path);
    if(!d) return false;
    struct dirent* ent = 0;
    uint32_t count = 0;
    while((ent = readdir(d)) != NULL)
    {count++;}
    rewinddir(d);
    char* stack[count*sizeof(char*)];
    char** ptr = stack; 
    while((ent = readdir(d)) != NULL)
    {*ptr = ent->d_name;ptr++;}
    uint32_t i = 0;
    for(;i < count;++i)
    {
        uint32_t j = 0;
        char** item = 0;
        for(;j < count;++j)
        {
            if(!(stack[j])) continue;
            if(!item)
            {item = &stack[j];continue;}
            item = compare_strings(item,stack,j);
        }
        printf("%s\n",*item);
        *item = 0;
    }
    
    closedir(d);
    return (errno != 0);
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
