/*
Author: JT Palmer

File: track.cpp

Description: This file contains implementations for the getters, constructors, and json parsing functions for tracks.
*/

#include "track.hpp"

Track::Track(){

	_artistName = "";

	_title = "";

	_albumName = "";

	_duration = "";

	_position = "";

	_albumID = 0;
}

Track::~Track(){

}

std::string Track::artistName(){

	return _artistName;
}

std::string Track::title(){

	return _title;
}

std::string Track::albumName(){

	return _albumName;
}

unsigned Track::albumID(){

	return _albumID;
}

std::string Track::duration(){

	return _duration;
}

std::string Track::position(){

	return _position;
}

void Track::print(){

	//print function to debug, modeled after google chrome parsed json output
	std::cout << "Artist Name: " << _artistName << std::endl;
	std::cout << "Title: " << _title << std::endl;
	std::cout << "Album Name: " << _albumName << std::endl;
	std::cout << "Duration: " << _duration << std::endl;
	std::cout << "Position: " << _position << std::endl;
	std::cout << "Album ID: " << _albumID << std::endl;
}
void Track::readJSONDataObject(std::fstream &stream)
{

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
void Track::readJSONDataItem(std::fstream &stream)
{

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

	} 
	else {
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

		else if(keyAttribute == "artist_name") _artistName = value;

		else if (keyAttribute == "album_name") _albumName = value;

		else if(keyAttribute == "duration") _duration = value;

		else if(keyAttribute == "position") _position = value;
	}
}

std::string Track::trackHTMLString(){

	std::string stringAlbID = std::to_string( _albumID );


	std::string htmlTrack = "<li>" + _title + "<dl>title</dt><dd>" + _title + 
		"</dd><dt>artist_name</dt><dd>" + _artistName +  "</dd><dt>album_name</dt><dd>" 
		+ _albumName+ "<dt>album_id</dt><dd>" + stringAlbID + "</dd><dt>duration</dt><dd>" + 
		_duration + "</dd><dt>position</dt><dd>" + _position + "</dd></dl></li>";
	/*
	   std::string htmlTrack = "<li><p>" + _title + "</p><ul><li><p>Artist Name: " 
	   + _artistName + "</p></li><li><p>Album Name: " + _albumName + "</p></li><li><p>Album ID: " 
	   + stringAlbID + "</p><li><li><p>Duration: " + _duration + "</p></li><li><p>Position: " 
	   + _position+ "</p></li></ul></li>";
	   */

	return htmlTrack;
}
