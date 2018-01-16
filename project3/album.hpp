/*
Author: JT Palmer

File: album.hpp

Description: function prototypes of an album, albums have an id, number of images, tracks, genres, and a year of release.
*/

#include<fstream>
#include<cstring>
#include <iostream>
#include <string>

class Album
{
	public:
		Album();
		~Album();

		std::string title();
		unsigned albumID();
		unsigned numImages();
		unsigned numTracks();
		std::string genres();
		std::string year();
		void print();
		void readJSONDataObject(std::fstream &stream);
		void readJSONDataItem(std::fstream &stream);
		std::string albHTMLString();

	private:
		std::string _title, _genres, _year;
		unsigned _albumID, _numTracks, _numImages, _artistID;
};
