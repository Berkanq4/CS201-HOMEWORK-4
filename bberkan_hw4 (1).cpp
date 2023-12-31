#include <iostream>
#include <string>
#include <vector>
#include <random>
//#include "strutils.h"
using namespace std;

struct Movie {
	string name;
	int year;
	string genre;
};

string toLower(const string& str) {
	string lowerStr;

	
	for (char c : str) {
		
		if (c >= 'A' && c <= 'Z') {
			lowerStr += c + ('a' - 'A');
		}
		else {
			
			lowerStr += c;
		}
	}

	return lowerStr;
}


void sortMovies(vector<Movie>& movies) {
	int n = movies.size();
	bool swapped;
	for (int i = 0; i < n - 1; i++) {
		swapped = false;
		for (int j = 0; j < n - i - 1; j++) {
			if (movies[j].year < movies[j + 1].year) {
				
				swap(movies[j], movies[j + 1]);
				swapped = true;
			}
			else if (movies[j].year == movies[j + 1].year) {
				
				if (movies[j].name > movies[j + 1].name) {
					swap(movies[j], movies[j + 1]);
					swapped = true;
				}
			}
		}
		
		if (!swapped) {
			break;
		}
	}
}

int main() {
	cout << "Welcome to the movie recommender program!" << endl;
	cout << endl;
	cout << "Please enter the movie, year and genre list: " << endl;
	string movieList;
	getline(cin, movieList);
	cout << endl;
	
	vector<Movie> movies;
	size_t start = 0, end = movieList.find('|');
	while (end != string::npos) {
		string movieStr = movieList.substr(start, end - start);
		size_t nameEnd = movieStr.find(';');
		string name = movieStr.substr(0, nameEnd);
		size_t yearEnd = movieStr.find(';', nameEnd + 1);
		int year = stoi(movieStr.substr(nameEnd + 1, yearEnd - nameEnd - 1));
		string genre = movieStr.substr(yearEnd + 1);
		movies.push_back({ name, year, genre });
		start = end + 1;
		end = movieList.find('|', start);
	}
	string movieStr = movieList.substr(start);
	size_t nameEnd = movieStr.find(';');
	string name = movieStr.substr(0, nameEnd);
	size_t yearEnd = movieStr.find(';', nameEnd + 1);
	int year = stoi(movieStr.substr(nameEnd + 1, yearEnd - nameEnd - 1));
	string genre = movieStr.substr(yearEnd + 1);
	
	movies.push_back({ name, year, genre });

	
	sortMovies(movies);

	random_device rd;
	mt19937 rand(rd());
	rand.seed(1907);
	bool sacmalik = true;
	while (true) {
		if (sacmalik) {

			cout << "Please select your action:" << endl;
			cout << "1. Select the genre of the movie that you want to watch" << endl;
			cout << "2. Select the year of the movie that you want to watch" << endl;
			cout << "3. Choose a random movie" << endl;
			cout << "4. Exit program" << endl;
			cout << endl;
			sacmalik = false;
		}

		cout << "Enter your choice: ";
		int choice;
		cin >> choice;
		///cout << endl;
		if (choice == 1) {
			cout << "Please enter the genre of the movie you want to watch: ";
			string genre;
			cin >> genre;
			//toLower(genre);
			cout << endl;
			bool found = false;
			bool only_once = true;
			for (const Movie& movie : movies) {
				string aklinda_tut = movie.genre;
				if (toLower(movie.genre) == toLower(genre)) {
					if (only_once) {
						cout << genre << " movies from newest to oldest:" << endl;
						only_once = false;
					}

					cout << "Movie name: " << movie.name << " Release Year: " << movie.year << endl;
					found = true;
				}
			}
			cout << endl;
			if (!found) {
				cout << "There are no " << genre << " movies!" << endl;
				cout << endl;
			}
		}
		else if (choice == 2) {
			cout << "Please enter the year of the movie you want to watch: ";
			string yearStr;
			cin >> yearStr;
			int year = -1, year2 = -1;
			size_t dashPos = yearStr.find('-');
			if (dashPos != string::npos) {
				year = stoi(yearStr.substr(0, dashPos));
				year2 = stoi(yearStr.substr(dashPos + 1));
			}
			else {
				year = stoi(yearStr);
			}
			bool found = false;
			bool found2 = false;
			bool devam = true;
			bool yildiz = true;
			for (const Movie& movie : movies) {
				if (year2 == -1) {
					if (movie.year == year) {
						if (yildiz) {
							cout << "Movies released in " << year << " from A to Z:" << endl;
							yildiz = false;
						}

						cout << "Movie name: " << movie.name << " Genre: " << movie.genre << endl;
						found = true;
						found2 = true;
					}
				}
				else {
					if (movie.year >= year && movie.year <= year2) {

						if (devam) {
							cout << "Movies released between the years " << year << "-" << year2 << " from A to Z with decreasing year ordering:" << endl;
							devam = false;
						}
						cout << "Movie name: " << movie.name << " Release Year: " << movie.year << " Genre: " << movie.genre << endl;
						found2 = true;
						found = true;
					}

				}
			}
			
			if (yearStr.find('-') == -1) {
				

				found2 = true;
				found = false;
			}
			else if (yearStr.find('-') != -1 && year2 != -1) {
				found = true;
				found2 = false;
			}
			
			cout << endl;
			if (!found) {
				cout << "There are no movies released in " << year << '!' << endl;
			}
			else if (!found2) {
				cout << "There are no movies released between " << year << '-' << year2 << '!' << endl;
			}
		}
		else if (choice == 3) {
			uniform_int_distribution<int> dist(0, movies.size() - 1);
			int index = dist(rand);

			cout << "Movie name: " << movies[index].name << " Release Year: " << movies[index].year << " Genre: " << movies[index].genre << endl;
			cout << endl;
		}
		else if (choice == 4) {
			cout << "Thank you..." << endl;
			break;
		}
		else {
			cout << "Invalid action!" << endl;
			cout << endl;
		}
	}
	return 0;
}