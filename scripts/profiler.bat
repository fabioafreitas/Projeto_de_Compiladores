gcc -pg ../main.c -o main
main
gprof main.exe gmon.out > profiling.txt