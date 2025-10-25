#define _GNU_SOURCE
#include "common.h"

void write_stats(struct statx stx,char* file)
{
    printf("File:            %s\n",file);
    printf("Mask:            0x%x\n", stx.stx_mask);
    printf("Blksize:         %u\n", stx.stx_blksize);
    printf("Attributes:      0x%llx\n", (unsigned long long)stx.stx_attributes);
    printf("Nlink:           %u\n", stx.stx_nlink);
    printf("Uid:             %u\n", stx.stx_uid);
    printf("Gid:             %u\n", stx.stx_gid);
    printf("Mode:            0%o\n", stx.stx_mode);
    printf("Ino:             %llu\n", (unsigned long long)stx.stx_ino);
    printf("Size:            %llu\n", (unsigned long long)stx.stx_size);
    printf("Blocks:          %llu\n", (unsigned long long)stx.stx_blocks);
    printf("Attributes_mask: 0x%llx\n", (unsigned long long)stx.stx_attributes_mask);

    printf("Access  : %lld.%09u\n", (long long)stx.stx_atime.tv_sec, stx.stx_atime.tv_nsec);
    printf("Created : %lld.%09u\n", (long long)stx.stx_btime.tv_sec, stx.stx_btime.tv_nsec);
    printf("Changed : %lld.%09u\n", (long long)stx.stx_ctime.tv_sec, stx.stx_ctime.tv_nsec);
    printf("Modified: %lld.%09u\n", (long long)stx.stx_mtime.tv_sec, stx.stx_mtime.tv_nsec);

    printf("Rdev Major:Minor %04u:%04u\n", stx.stx_rdev_major,stx.stx_rdev_minor);
    printf("Dev  Major:Minor %04u:%04u\n",stx.stx_dev_major,stx.stx_dev_minor);
}

bool stat_(char* path)
{
    struct statx stx;
    int ret = statx(AT_FDCWD, path, AT_STATX_SYNC_AS_STAT, 
                    STATX_BASIC_STATS, &stx);
    if (ret == -1) return false;

    write_stats(stx,path);
    return true;
}

int main(int argc,char** argv)
{
    if(argc == 1)
    {
        if(!stat_("."))
        {
            printf("stat failed: . : %s\n",strerror(errno));
            return 1;
        }
        return 0;
    }
    uint32_t i = 1;
    for(;i < argc;++i)
    {
        if(!stat_(argv[i]))
        {
            printf("stat failed: %s : %s\n",argv[i],strerror(errno));
        }
        printf("\n");
    }
    return 0;
}
