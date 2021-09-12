#include "solution.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

//Project 1: Lib_Info
//Nicholas Parsly and Autumn Henderson
//A program that sores and formats information about MP3 files
//Compiles using makefile

int main(int argc, char *argv[]) {

	Song temp1;									//Temps 1-3 store songs, albums, and artists until they are inserted
	Album temp2;
	Artist temp3;
	string line;								//Stores each line from the file
	string filename;							//The file name taken from the command line
	string title;								//These strings and ints are the data taken from each line of the file
	string timest;								//timest = time string. It's the time in ##:## format
	string artistname;
	string albumname;
	string genre;
	int timei;									//timei = time int. It's the time as an integer of seconds
	int tracknum;
	map <string, Artist> artists;				//The map that holds all of the artists. Used for printing out everything
	map <string, Album>::iterator albit;		//Iterators for the albums and artists maps
	map <string, Artist>::iterator artit;
	ifstream fin;
	stringstream ss;


	//Check for the proper format of command line
	if (argc != 2) {
		return -1;
	}

	//File opening and checking
	filename = argv[1];	
	fin.open(filename.c_str());

	if (fin.fail()) {
		return -1;
	}

	//This loop runs until the end of the file is reached. It contains most of this program
	while (getline(fin, line)) {

		//Stringstream inputs into each of the 6 words from the line. These are converted and despaced as necessary
		ss.clear();
		ss.str(line);
		ss >> title >> timest >> artistname >> albumname >> genre >> tracknum;

		Despace(title);
		Despace(artistname);
		Despace(albumname);
		timei = Convert(timest);

		//Data is stored in a Song
		temp1.title = title;
		temp1.time = timei;
		temp1.track = tracknum;

		/*I looked at Dr. Plank's notes http://web.eecs.utk.edu/~jplank/plank/classes/cs140/Notes/SetMap/index.html to refresh
		 * myself on formatting maps */

		//This block handles the updating of the artists map
		artit = artists.find(artistname);

		//This if statement puts the artist in the map if they are not within it
		if (artit == artists.end()) {
			temp3.name = artistname;
			temp3.time = timei;
			temp3.nsongs = 1;
			artists.insert(make_pair(artistname, temp3));
		}

		//This else statement updates the artist's info if they are already in the map
		else {
			artit->second.time = artit->second.time + timei;
			artit->second.nsongs = artit->second.nsongs + 1;
		}

		//This block handles the updating of the albums map
		artit = artists.find(artistname);
		albit = artit->second.albums.find(albumname);

		//This if statement puts the album in the map if it is not within it 
		if (albit == artit->second.albums.end()) {
			temp2.title = albumname;
			temp2.time = timei;
			temp2.nsongs = 1;
			artit->second.albums.insert(make_pair(albumname, temp2));
		}

		//This else statement updates the album info if it is already in the map
		else {
			albit->second.time = albit->second.time + timei;
			albit->second.nsongs = albit->second.nsongs + 1;
		}

		//Insertion of the song into the album
		albit = artit->second.albums.find(albumname);
		albit->second.songs.insert(make_pair(tracknum, temp1));

	}

	//Closing of the file and printing of the artists, albums, and songs
	fin.close();
	Print_All(artists);

	return 0;

}
