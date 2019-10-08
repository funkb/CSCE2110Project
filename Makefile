#Since the Source and Build folders are seperate, you have to define
#which folder your cpp and h files are in the Makefile. It's a little
#bit of extra work, but it makes the project much cleaner overall.



#To add your file to the make, type the name with .o added after the other
#files.  Whitespace sensitive, so don't remove any tabs/spaces

output: main.o porter_stem.o readin.o tfidf.o cosinesimilarity.o
	g++ -std=c++11 -Wall ./build/main.o ./build/porter_stem.o ./build/readin.o ./build/tfidf.o ./build/cosinesimilarity.o -o ./build/output.out



#Main never changes
main.o: ./src/main.cpp ./src/datastructs.h
	g++ -std=c++11 -Wall -c ./src/main.cpp -o ./build/main.o


#Use the following format to add your cpp and h files to the build as
#you add them to the main.

porter_stem.o: ./src/porter_stem.cpp ./src/porter_stem.h
	g++ -std=c++11 -Wall -c ./src/porter_stem.cpp -o ./build/porter_stem.o

readin.o: ./src/readin.cpp ./src/readin.h
	g++ -std=c++11 -Wall -c ./src/readin.cpp -o ./build/readin.o

tfidf.o: ./src/tfidf.cpp ./src/tfidf.h
	g++ -std=c++11 -Wall -c ./src/tfidf.cpp -o ./build/tfidf.o

cosinesimilarity.o: ./src/cosinesimilarity.cpp ./src/cosinesimilarity.h
		g++ -std=c++11 -Wall -c ./src/cosinesimilarity.cpp -o ./build/cosinesimilarity.o


#Doesn't change
clean:
	rm ./build/*.o
	rm ./build/output.out
