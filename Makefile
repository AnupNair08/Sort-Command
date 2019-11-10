msort: mysort.o extsort.o sort.o
	gcc -o ./a.out mysort.o extsort.o sort.o
mysort.o: mysort.c extsort.o sort.o
	gcc -c mysort.c
sort.o:  sort.h sort.c
	gcc -c sort.c
extsort.o: extsort.h sort.h extsort.c sort.c
	gcc -c extsort.c

