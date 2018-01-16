/*Author: JT Palmer

File: album.cpp

Description: Implmentations for album constructors, getters, and parsing functions related to the album.
*/


#include "album.hpp"

Album::Album(){

	_title = "";

	_genres = "";

	_year = "";

	_artistID = 0;

	_albumID = 0;

	_numTracks = 0;

	_numImages = 0;
}

Album::~Album(){

}

std::string Album::title(){

	return _title;
}
unsigned Album::albumID(){

	return _albumID;
}

unsigned Album::numImages(){

	return _numImages;
}
unsigned Album::numTracks(){

	return _numTracks;
}

std::string Album::genres(){

	return _genres;
}

std::string Album::year(){

	return _year;
}

void Album::print(){

	//print function to debug, modeled after google chrome parsed json output
	std::cout << "Number Of Tracks: " << _numTracks << std::endl;
	std::cout << "Title: " << _title << std::endl;
	std::cout << "Year: " << _year << std::endl;
	std::cout << "Genre: " << _genres << std::endl;
	std::cout << "Artist ID: " << _artistID << std::endl;
	std::cout << "Number Of Images: " << _numImages << std::endl;
	std::cout << "Album ID " << _albumID << std::endl;
}

void Album::readJSONDataObject(std::fstream &stream){

	char c;

	if( !(stream >> c) || c != '{' )
	{   
		// The first non-space character of a JSON object has to be '{'.
		// print some error message and exit the program.

		std::cout << "The file is not in JSON format. Expected an { " << std::endl;

		return;
	}
	do {
		readJSONDataItem(stream);   // we know that a JSON object has at least one JSON key/value pair.
		// readJSONDataItem reads exactly one such pair.
		stream >> c;  // the character after the JSON key/value pair is either a comma, indicating
		// there are more key/value pairs to be read, or a closed-brace ('}').
		// A closed-brace means that we have already read all JSON key/value pairs.
	} while( c != '}' );
}

void Album::readJSONDataItem(std::fstream &stream){

	char c;

	if( !(stream >> c) || c != '"' )  // The first non-space character of a JSON key/value pair has to be
	{                                  // a double-quote.
		// print some error message and exit the program.
		std::cout << "The file was not in JSON format. Missing an qoutation mark. " << std::endl;
		return;
	}	
	// using stream.get(c) read one character at a time until you find the matching end double-quote.
	// Notice that \" doesn't end the key string; it should be injected into the text of the key string.
	std::string keyAttribute = "";

	char prev = ' ';

	c = ' ';

	do{

		prev = c;

		stream.get(c);

		if(c != '"'){
			keyAttribute += c;
		}
		if(c == '"' && prev == '\\'){

			keyAttribute += c;

			c = ' ';
		}
	} while( c != '"');

	// After having read the key, including the closing double-quote, we should find a colon.
	if( !(stream >> c) || c != ':' )
		// print an error message and exit
		std::cout << "The file was not in JSON format. Missing an : " << std::endl;

	// Now, we are ready to read the value part. It is either a string or a number.
	stream >> c;
	if( isdigit(c) ) {
		stream.unget();  // put the digit back into the stream so we read the number.
		int number;
		stream >> number;
		if(keyAttribute == "album_id") _albumID = number;
		else if(keyAttribute == "num_images") _numImages = number;
		else if(keyAttribute == "num_tracks") _numTracks = number;
		else if(keyAttribute == "artist_id") _artistID = number;

	} else {
		// the value part is a string. Read it including the closing double-quotes.
		// Again, \" should be injected into the text of the value string.a
		std::string value = "";

		c = ' ';

		do{
			prev = c;

			stream.get(c);

			if(c != '\\'){

				if (c != '\\'){

					if (c != '"') value += c;
					if(c == '"' && prev == '\\')
					{
						value += c;

						c = ' ';
					}
				}
			}
		}while (c != '"');

		if(keyAttribute == "title") _title = value;

		else if(keyAttribute == "genres") _genres = value;

		else if (keyAttribute == "year") _year = value;

		else if(keyAttribute == "num_images")
		{

			unsigned imgAsInt = std::stoi(value);

			_numImages = imgAsInt;
		}
	}
}
std::string Album::albHTMLString(){


	std::string stringNumTracks = std::to_string( _numTracks );

	std::string stringAlbID = std::to_string( _albumID );

	std::string stringNumImg = std::to_string ( _numImages );


	std::string htmlAlb = "<li>" + _title + "<dl>title</dt><dd>" + _title + 
		"</dd><dt>album_id</dt><dd>" + stringAlbID +  "</dd><dt>genres</dt><dd>" + _genres + 
		"<dt>num_images</dt><dd>" + stringNumImg + "</dd><dt>num_tracks</dt><dd>" + 
		stringNumTracks + "</dd><dt>year</dt><dd>" + _year + "</dd></dl></li>";

	return htmlAlb;
}
