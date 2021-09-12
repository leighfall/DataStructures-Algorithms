//Project 1: Lib_Info
//Nicholas Parsly and Autumn Henderson
//A program that sorts and formats information about MP3 files

#include "solution.hpp"
#include <iostream>
#include <sstream>

using namespace std;

//Converts the ##:## time to an integer of seconds
int Convert(string time) {

	int itime;
	int seconds;
	int minutes;
	istringstream iss;

	itime = 0;
	seconds = 0;
	minutes = 0;

	iss.clear();

	//Breaks up seconds and minutes
	for (int i = 0; i < (int) time.size(); i++) {

		if (time.at(i) == ':') {
			time.replace(i, 1, " ");
		}
	}

	iss.str(time);

	//Takes minutes and converts to seconds
	iss >> minutes;
	minutes *= 60;

	//Inputs seconds
	iss >> seconds;

	//Adds both seconds and minutes
	itime = seconds + minutes;
	return itime;
}

//Converts integer of seconds to ##:## time
string Convert_Back(int time) {

	string stime;	
	string tmp1, tmp2;
	stringstream ss;
	int second;
	int minute;


	//Calculates seconds and minutes
	second = time % 60;
	minute = time / 60;

	//Converts integers to strings
	ss << minute;
	tmp1 = ss.str();
	ss.clear();
	ss.str("");
	ss << second;
	tmp2 = ss.str();

	//Formats stime to ##:##
	if ((int)tmp2.length() == 1) {
		stime = tmp1 + ":0" + tmp2;
	}

	else {
		stime = tmp1 + ':' + tmp2;
	}

	return stime;
}

//Takes a set of all of the artists and prints out their albums and songs in the requested format
void Print_All(const map <string, Artist> &artists) {

	map<string, Artist>::const_iterator artit;
	map<string, Album>::const_iterator albit;
	map<int, Song>::const_iterator songit;

	string artist_time;

	string album_name;
	int album_nsongs;
	string album_time;

	string song_name;
	string song_time;
	int song_track;

	for(artit = artists.begin(); artit != artists.end(); artit++) {

		//Prints out Artist information
		artist_time = Convert_Back(artit->second.time);
		cout << artit->first << ": " << artit->second.nsongs << ", " << artist_time << endl;

		//Prints out Album information
		for(albit = artit->second.albums.begin(); albit != artit->second.albums.end(); albit++) {
			album_name = albit->first; 
			album_nsongs = albit->second.nsongs; 
			album_time = Convert_Back(albit->second.time);

			cout << "        " << album_name << ": " << album_nsongs << ", " << album_time << endl;

			//Prints out Song information
			for(songit = albit->second.songs.begin(); songit != albit->second.songs.end(); songit++) {
				song_track = songit->second.track;
				song_name = songit->second.title;
				song_time = Convert_Back(songit->second.time);

				cout << "                " << song_track << ". " << song_name << ": " << song_time << endl;
			}
		}
	}
}

//Removes the underscores from a string and replaces them with spaces
void Despace(string &s) {

	size_t i;

	for (i = 0; i < s.size(); i++) {

		//If the character is an underscore, replace the character of length 1 at i with a space
		if (s.at(i) == '_') s.replace(i, 1, " ");
	}
}
