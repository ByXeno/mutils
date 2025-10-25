#!/bin/sh
# POSIX shell build script for musl-coreutils
# Works with clang/zig, fully GNU-free

# ------------------------------
# Configuration
# ------------------------------
CC="${CC:-musl-gcc}"                        # Compiler
CFLAGS="${CFLAGS:--O2 -Wall -std=c99 -Iinclude}"  # Compiler flags
STATIC="${STATIC:-0}"                    # STATIC=1 for static build
LIBNAME="mutils"
BUILDDIR="build"
SRCDIR="src"
LIBSRC="lib/common.c"

# ------------------------------
# Prepare build directory
# ------------------------------
mkdir -p "$BUILDDIR"

# ------------------------------
# Compile library objects
# ------------------------------
OBJFILES=""
for src in $LIBSRC; do
    obj="$BUILDDIR/$(basename "$src" .c).o"
    echo "Compiling $src -> $obj"
    $CC $CFLAGS -fPIC -c "$src" -o "$obj" || exit 1
    OBJFILES="$OBJFILES $obj"
done

# ------------------------------
# Build library
# ------------------------------
if [ "$STATIC" -eq 1 ]; then
    LIBFILE="$BUILDDIR/lib$LIBNAME.a"
    echo "Creating static library $LIBFILE"
    ar rcs "$LIBFILE" $OBJFILES || exit 1
else
    LIBFILE="$BUILDDIR/lib$LIBNAME.so"
    echo "Creating shared library $LIBFILE"
    $CC -shared -o "$LIBFILE" $OBJFILES || exit 1
fi

# ------------------------------
# Build tools
# ------------------------------
# List all .c files in src/ as tools
for srcfile in "$SRCDIR"/*.c; do
    tool="$(basename "$srcfile" .c)"
    outfile="$BUILDDIR/$tool"
    echo "Building tool $tool -> $outfile"
    if [ "$STATIC" -eq 1 ]; then
        $CC $CFLAGS -static "$srcfile" $LIBSRC -o "$outfile" || exit 1
    else
        $CC $CFLAGS "$srcfile" -L"$BUILDDIR" -l$LIBNAME -o "$outfile" || exit 1
    fi
done

echo "Build complete. Binaries are in $BUILDDIR/"
