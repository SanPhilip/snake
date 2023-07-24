#!/bin/sh

CFLAGS="-Wall -Wextra"
LIBS="-lraylib"

gcc $CFLAGS -o snake snake.c $LIBS
