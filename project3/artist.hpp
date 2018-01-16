/*
Author: JT Palmer

File: artist.hpp

Description: function prototypes for artist class, artists have names, legal names, a profile, 
the number of images available to this artist, and an ID.
*/

#include<fstream>
#include<cstring>
#include<iostream>
#include <cstdlib>
#include <vector>
#include <string>

class Artist 
{
	public:
		Artist();
		~Artist();

		std::string profile()    { return _profile; }
		std::string name()       { return _name; }
		std::string realName()   { return _realName; }

		// numImages is a string in the JSON file, but you
		// should convert it to unsigned when you parse
		// from the JSON stream.
		unsigned    numImages() { return _numImages; }

		unsigned    artistID()   { return _artistID;  }
		void print();
		void parseFromJSONstream(std::fstream &stream);
		std::string artHTMLString();

		void readJSONArray(std::fstream &stream);
		void readJSONDataObject(std::fstream &stream);
		void readJSONDataItem(std::fstream &stream);
	private:
		std::string _name, _realName, _profile;
		unsigned _numImages, _artistID;
};
