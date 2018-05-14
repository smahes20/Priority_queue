pq.o: pc1.c pc.h
    gcc -c pq1.c
test: test.c pq.o
    gcc test.c pq.o -o test