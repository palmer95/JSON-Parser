/*
Author: JT Palmer

File: main.cpp

Description: Main file to run all of the functions written in the three classes, the functions for reading an json array are defined and ran here.

*/

#include <fstream>
#include <vector>
#include "track.hpp"
#include "artist.hpp"
#include "album.hpp"
#include <iostream>
#include <string>
#include "utils.hpp"

//function prototypes
void readJSONArrayArtists(std::fstream &stream, std::vector<Artist *> &artistsVector);
void readJSONArrayAlbums(std::fstream &stream, std::vector<Album *> &albumsVector);
void readJSONArrayTracks(std::fstream &stream, std::vector<Track *> &tracksVector);
std::string parseArtistsToHTML(std::fstream &stream, std::vector<Artist *> &artistsVector);
std::string parseAlbumsToHTML(std::fstream &stream, std::vector<Album *> &albumsVector);
std::string parseTracksToHTML(std::fstream &stream, std::vector<Track *> &tracksVector);

//function implementations
void readJSONArrayArtists(std::fstream &stream, std::vector<Artist *> &artistsVector)
{
	char c;

	//check the arguments to see if given files are truly JSON
	if(! (stream >> c) || c != '[')
	{
		std::cout << "The file is not in valid JSON format. " << std::endl;

		return;
	}
	//if they are, make an vector of artist objects and read the objects
	do
	{
		Artist *arts = new Artist();

		arts -> readJSONDataObject(stream);

		artistsVector.push_back(arts);

		stream >> c;
	
	} while (c != ']');
}

void readJSONArrayAlbums(std::fstream &stream, std::vector<Album *> &albumsVector)
{

	char c;

	//check if the second argument is truly JSON
	if(! (stream >> c) || c != '[')
	{
		std::cout << "The file is not in valid JSON format. " << std::endl;

		return;
	}
	//If so, make a vector of album objects and read the objects
	do
	{
		Album *albs = new Album();

		albs -> readJSONDataObject(stream);

		albumsVector.push_back(albs);

		stream >> c;

	} while (c != ']');
}

void readJSONArrayTracks(std::fstream &stream, std::vector<Track *> &tracksVector)
{

	char c;
	
	//is the third argument truly JSON
	if(! (stream >> c) || c != '[')
	{
		std::cout << "The file is not in valid JSON format. " << std::endl;

		return;
	}
	//IF so, make a vector of track objects, and read the objects
	do
	{
		Track *tracks = new Track();

		tracks -> readJSONDataObject(stream);

		tracksVector.push_back(tracks);

		stream >> c;

	} while (c != ']');

}

std::string parseArtistsToHTML(std::fstream &stream, std::vector<Artist *> &artistsVector){

	char c;

	std::string artsAsHTML = "";

	//check for html and being able to read in from the provided file
	if(! (stream >> c) || c != '<')
	{
		std::cout << "The file is not in valid HTML format. " << std::endl;

		return artsAsHTML;
	}
	//add the text until we reach the pre defined body
	do
	{
		artsAsHTML += c;

		stream.get(c);

	} while (c != '{');

	for(std::vector<Artist *>::iterator iter = artistsVector.begin(); iter < artistsVector.end(); iter++)
	{
		artsAsHTML += (*iter) -> artHTMLString();
	}
	while ( c != '}')
	{
		stream >> c;

	}

	stream.get(c);

	while( stream.get(c))
	{
		artsAsHTML += c;

	}

	return artsAsHTML;
}

std::string parseAlbumsToHTML(std::fstream &stream, std::vector<Album *> &albumsVector){

	char c;

	std::string albsAsHTML = "";

	if(! (stream >> c) || c != '<')
	{
		std::cout << "The file is not in valid HTML format. " << std::endl;

		return albsAsHTML;
	}
	do
	{	
		albsAsHTML += c;

		stream.get(c);
	}while (c != '{');

	for(std::vector<Album *>::iterator iter = albumsVector.begin(); iter < albumsVector.end(); iter++)
	{
		albsAsHTML += (*iter) -> albHTMLString();
	}

	while (c != '}')
	{
		stream >> c;
	}

	stream.get(c);

	while(stream.get(c))
	{
		albsAsHTML += c;
	}
	return albsAsHTML;
}

std::string parseTracksToHTML(std::fstream &stream, std::vector<Track *> &tracksVector){

	char c;

	std::string trackAsHTML = "";

	if(! (stream >> c) || c != '<')
	{
		std::cout << "The file is not in valid HTML format. " << std::endl;
	}
	do
	{
		trackAsHTML += c;

		stream.get(c);

	} while (c != '{');

	for(std::vector<Track *>::iterator iter = tracksVector.begin(); iter < tracksVector.end(); iter++)
	{
		trackAsHTML += (*iter) -> trackHTMLString();
	}

	while (c != '}')
	{
		stream >> c;
	}

	stream.get(c);

	while (stream.get(c))
	{
		trackAsHTML += c;
	}

	return trackAsHTML;
}

int main(int argc, char* argv[]){

	//check if correct number of files were provided
	if (argc != numArgs)
	{
		std::cout <<"Executable was called with  the incorrect number of files.\n" <<
			"Expected ./main.x file1 file2 file3.\n" << "The order being artist, album, and then track." << std::endl;

		return 0;
	}
	//grab all files
	std::fstream artistsInput (argv[1]);

	std::fstream albumsInput (argv[2]);

	std::fstream tracksInput (argv[3]);

	//make all vectors
	std::vector<Artist *> artistsVector;

	std::vector<Album *> albumsVector;

	std::vector<Track *> tracksVector;

	//parse the objects from json files
	readJSONArrayArtists(artistsInput, artistsVector);

	readJSONArrayAlbums(albumsInput, albumsVector);

	readJSONArrayTracks(tracksInput, tracksVector);

	//Create html streams

	//artists
	std::fstream artHTML;

	artHTML.open("artists_template.html");

	std::ofstream artOutput("artists.html");

	artOutput << parseArtistsToHTML(artHTML, artistsVector);

	artOutput.close();

	//Albums
	std::fstream albHTML;

	albHTML.open("albums_template.html");

	std::ofstream albOutput("albums.html");

	albOutput << parseAlbumsToHTML(albHTML, albumsVector);

	albOutput.close();

	//Tracks
	std::fstream trackHTML;

	trackHTML.open("tracks_template.html");

	std::ofstream trackOutput("tracks.html");

	trackOutput << parseTracksToHTML(trackHTML, tracksVector);

	trackOutput.close();

	//debug is initialized to true in utils.hpp
	if(!debug)
	{
		std::cout << std::endl;

		//print out the objects for testing
		for(std::vector<Artist *>::iterator iter = artistsVector.begin(); iter < artistsVector.end(); iter++)
		{
			(*iter) -> print();
			std::cout << std::endl;
		}

		std::cout << std::endl;

		for(std::vector<Album *>::iterator iterAlb = albumsVector.begin(); iterAlb < albumsVector.end(); iterAlb++)
		{
			(*iterAlb) -> print();
			std::cout << std::endl;
		}
		std::cout << std::endl;

		for(std::vector<Track *>::iterator iterT = tracksVector.begin(); iterT < tracksVector.end(); iterT ++)
		{
			(*iterT) -> print();
			std::cout << std::endl;
		}

		std::cout << std::endl;
	}
	return 0;	
}
