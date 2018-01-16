/*
Author: JT Palmer

File: artist.cpp

Description: This file contains all of the getters, constructors, and parsing functions for artist objects.
*/

#include "artist.hpp"

Artist::Artist(){

	_name = "";

	_realName = "";

	_profile = "";

	_numImages = 0;

	_artistID = 0;
}

Artist::~Artist(){

}

void Artist::print(){

	//print function to debug, modeled after google chrome parsed json output
	std::cout << "Real Name: " << _realName << std::endl;
	std::cout << "Number of Images: " << _numImages << std::endl;
	std::cout << "Profile: " << _profile << std::endl;
	std::cout << "Artist ID: " << _artistID << std::endl;
	std::cout << "Name: " << _name << std::endl;



}

void Artist::readJSONDataObject(std::fstream &stream){

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

void Artist::readJSONDataItem(std::fstream &stream){

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
		if(keyAttribute == "artist_id") _artistID = number;

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

		if(keyAttribute == "real_name") _realName = value;

		else if(keyAttribute == "profile") _profile = value;

		else if (keyAttribute == "artist_name") _name = value;

		else if(keyAttribute == "num_images")
		{

			unsigned imgAsInt = std::stoi(value);

			_numImages = imgAsInt;
		}
	}
}

std::string Artist::artHTMLString(){

	std::string stringNumImg = std::to_string( _numImages );

	std::string stringArtID = std::to_string( _artistID );

	std::string htmlArt = "<li>" + _name + "<dl>artist_name</dt><dd>" + _name + 
		" </dd><dt>real_name</dt><dd>" + _realName + "</dd><dt>artist_id</dt><dd>" + stringArtID + 
		"<dt>num_images</dt><dd>" + stringNumImg + "</dd><dt>profile</dt><dd>" + 
		_profile +  "</dd></dl></li>";

	return htmlArt;

}
