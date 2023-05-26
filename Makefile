project: knn.o main.o
	g++ knn.o main.o -o project
	
knn.o: knn.cpp
	g++ -c knn.cpp
	
main.o: main.cpp
	g++ -c main.cpp
	
clean:
	rm *.0
