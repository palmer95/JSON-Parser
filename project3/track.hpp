/*
Author: JT Palmer

File: track.hpp

Description: This file contains function prototypes for the track class, tracks have an title, name of the main artist, 
a name from which album the track derives from, an id for the corresponding album, the length of the track, and 
the position of the track in the album.
*/

#include<fstream>
#include<cstring>
#include <iostream>
#include <string>

class Track
{
	public:
		Track();
		~Track();

		std::string artistName();
		std::string title();
		std::string albumName();
		unsigned albumID();
		std::string duration();
		std::string position();
		void print();
		void readJSONDataObject(std::fstream &stream);
		void readJSONDataItem(std::fstream &stream);
		std::string trackHTMLString();

	private:
		std::string _artistName, _title, _albumName, _duration, _position;
		unsigned _albumID;
};
