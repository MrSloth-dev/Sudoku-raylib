#!/bin/zsh


set -xe

cc main.c solve.c -g -lraylib -o sudoku
