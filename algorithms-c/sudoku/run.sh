#!/bin/bash
echo "indent:"
indent -kr -i8 sudoku.c
echo "gcc:"
gcc sudoku.c
echo "run a.out:"
./a.out
echo "over~~"


