all: parent.out child.out

parent.out:
	g++ -o parent.out parent.cpp -lpthread -lrt

child.out:
	g++ -o child.out child.cpp -lpthread -lrt

clean:
	rm -r *.out *.txt