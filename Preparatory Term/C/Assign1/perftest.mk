perftest : perftest.o myalgos.o myutils.o
	gcc -o perftest perftest.o myalgos.o myutils.o
myalgos.o : myalgos.c myalgos.h
	gcc -c myalgos.c
myutils.o : myutils.c myutils.h datadef.h
	gcc -c myutils.c
perftest.o : perftest.c datadef.h
	gcc -c perftest.c

