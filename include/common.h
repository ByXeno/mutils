#ifndef COMMON_H_
#define COMMON_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>


#define RESET       "\033[0m"

#define BLACK       "\033[30m"
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define BLUE        "\033[34m"
#define MAGENTA     "\033[35m"
#define CYAN        "\033[36m"
#define WHITE       "\033[37m"

#define BBLACK      "\033[90m"
#define BRED        "\033[91m"
#define BGREEN      "\033[92m"
#define BYELLOW     "\033[93m"
#define BBLUE       "\033[94m"
#define BMAGENTA    "\033[95m"
#define BCYAN       "\033[96m"
#define BWHITE      "\033[97m"

#define BG_BLACK    "\033[40m"
#define BG_RED      "\033[41m"
#define BG_GREEN    "\033[42m"
#define BG_YELLOW   "\033[43m"
#define BG_BLUE     "\033[44m"
#define BG_MAGENTA  "\033[45m"
#define BG_CYAN     "\033[46m"
#define BG_WHITE    "\033[47m"

#define BG_BBLACK   "\033[100m"
#define BG_BRED     "\033[101m"
#define BG_BGREEN   "\033[102m"
#define BG_BYELLOW  "\033[103m"
#define BG_BBLUE    "\033[104m"
#define BG_BMAGENTA "\033[105m"
#define BG_BCYAN    "\033[106m"
#define BG_BWHITE   "\033[107m"

#define BOLD        "\033[1m"
#define DIM         "\033[2m"
#define ITALIC      "\033[3m"
#define UNDERLINE   "\033[4m"
#define BLINK       "\033[5m"
#define REVERSE     "\033[7m"
#define HIDDEN      "\033[8m"
#define STRIKE      "\033[9m"

#define FG256(n)    "\033[38;5;" #n "m"
#define BG256(n)    "\033[48;5;" #n "m"

#endif // COMMON_H_

