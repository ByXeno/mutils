#include "common.h"

char* get_pwd(uint32_t iter)
{
    char* tmp = calloc(iter*1024,sizeof(char));
    char* val = getcwd(tmp,iter*1024);
    if(getcwd(tmp,iter*1024) == 0)
    {
        if(errno == ERANGE)
        {
            free(tmp);
            return get_pwd(iter+1);
        }
        else
        {
            printf("pwd failed: %s \n",strerror(errno));
            return 0;
        }
    }
    else
    {
        return val;
    }
}

int main(int argc,char** argv)
{
    char* pwd = get_pwd(1);
    if(pwd == 0) return 1;
    printf("%s\n",pwd);
    free(pwd);
    return 0;
}
