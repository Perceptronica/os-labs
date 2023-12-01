files: main1 main2

main1: libd1.so prog1.cpp
	g++ prog1.cpp -L. -ld1 -o main1 -Wl,-rpath -Wl,.

main2: libd1.so libd2.so prog2.cpp
	g++ prog2.cpp -L. -ldl -o main2 -Wl,-rpath -Wl,.

libd1.so: d1.o 
	g++ -shared d1.o -o libd1.so 

libd2.so: d2.o 
	g++ -shared d2.o -o libd2.so 

d1.o: lib1.cpp
	g++ -fPIC -c lib1.cpp -o d1.o

d2.o: lib2.cpp
	g++ -fPIC -c lib2.cpp -o d2.o

clean:
	rm -r *.so *.o main1 main2