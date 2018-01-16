CFLAGS= -ggdb -std=c++11 

artists.x: main.o artist.o album.o track.o
	g++ $(CFLAGS) -o artists.x artist.o album.o track.o main.o

main.o: main.cpp
	g++ $(CFLAGS) -c main.cpp -o main.o

artist.o: artist.cpp artist.hpp
	g++ $(CFLAGS) -c -ggdb artist.cpp -o artist.o

album.o: album.cpp album.hpp
	g++ $(CFLAGS) -c -ggdb album.cpp -o album.o

track.o: track.cpp track.hpp
	g++ $(CFLAGS) -c -ggdb track.cpp -o track.o

publish:
	cp artists.html  albums.html tracks.html ~/public_html/ 
	chmod o+r ~/public_html/artists.html
	chmod o+r ~/public_html/albums.html
	chmod o+r ~/public_html/tracks.html


clean:
	/bin/rm -f parse.x *.o *.x
