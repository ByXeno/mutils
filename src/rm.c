#include "common.h"

typedef struct {
    bool recursive;
    bool force;
} config_t;

static int rm_recursive_at(int dirfd, const char *name, const config_t *conf);

static int remove_entry_at(int dirfd, const char *name, const config_t *conf) {
    struct stat st;
    if (fstatat(dirfd, name, &st, AT_SYMLINK_NOFOLLOW) < 0) {
        if (conf->force && errno == ENOENT)
            return 0;
        perror(name);
        return -1;
    }
    if (S_ISDIR(st.st_mode)) {
        if (!conf->recursive) {
            if (!conf->force)
                fprintf(stderr, "rm: cannot remove '%s': Is a directory\n", name);
            return -1;
        }
        return rm_recursive_at(dirfd, name, conf);
    }
    if (unlinkat(dirfd, name, 0) < 0) {
        if (conf->force && errno == ENOENT)
            return 0;
        perror(name);
        return -1;
    }
    return 0;
}

static int rm_recursive_at(int dirfd, const char *dirname, const config_t *conf) {
    int dfd = openat(dirfd, dirname, O_DIRECTORY | O_RDONLY);
    if (dfd < 0) {
        if (errno == ENOTDIR)
            return unlinkat(dirfd, dirname, 0);
        if (conf->force && errno == ENOENT)
            return 0;
        perror(dirname);
        return -1;
    }
    DIR *dir = fdopendir(dfd);
    if (!dir) {
        perror(dirname);
        close(dfd);
        return -1;
    }
    struct dirent *ent;
    while ((ent = readdir(dir))) {
        if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
            continue;
        remove_entry_at(dfd, ent->d_name, conf);
    }
    closedir(dir);
    if (unlinkat(dirfd, dirname, AT_REMOVEDIR) < 0) {
        if (conf->force && errno == ENOENT)
            return 0;
        perror(dirname);
        return -1;
    }
    return 0;
}

int main(int argc, char **argv) {
    config_t conf = {0};
    if (argc == 1) {
        printf("Usage: rm [-rf] [FILES...]\n");
        return 0;
    }
    for (int i = 1; i < argc; ++i) {
        char *arg = argv[i];
        if (arg[0] != '-') continue;
        for (char *f = arg + 1; *f; f++) {
            switch (*f) {
                case 'r': conf.recursive = true; break;
                case 'f': conf.force = true; break;
                default:
                    fprintf(stderr, "Unknown flag: -%c\n", *f);
            }
        }
        *argv[i] = 0;
    }
    for (int i = 1; i < argc; ++i) {
        if (!*argv[i]) continue;
        remove_entry_at(AT_FDCWD, argv[i], &conf);
    }
    return 0;
}
