#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include <ctime>

#include "classes.h"

using namespace std;

int search_date(int day, int month, int year); 

Event::Event() {
    year = 0;
    day = 0;
    month = 0;
    numEvents = 0;
}


void Event::setAtts(int y, int d, int m)	{
	year = y;
	day = d;
	month = m;
}
void Event::setNumEvents(int nevs) {
	numEvents = nevs;
}
	void Event::addEvent(string newEvent)
		{
				events[numEvents] = newEvent;
				numEvents++;
		}
int Event::getYear() {
	return year;
}

int Event::getDay() {
	return day;
}

int Event::getMonth() {
	return month;
}

int Event::getNumEvents() {
	return numEvents;
}

string* Event::getEvents() {
	return events;
}


void Event :: writeEventsToFile(int day, int month, int year) {
		int line_number = search_date(day, month, year);
			if (line_number == -1) {
				ofstream myfile;
				myfile.open("events.txt", ios::app);
				if (myfile.is_open()) {
					myfile << day << " " << month << " " << year << "\n";
					myfile << getNumEvents() << "\n";
					for (int i = 0; i < getNumEvents(); i++) {
						myfile << events[i] << "\n";
					}
					myfile.close();
					cout << "Events added successfully.\n";
				} else {
					cout << "Unable to open file.\n";
				}
			} else {
				int nmevs;
				ifstream infile("events.txt");
				if (!infile) {
					cout << "Unable to open file." << endl;
					return;
				}

				string line;
				for (int i = 1; i <= line_number+1; i++) {
					getline(infile, line);
					if (i == line_number+1) {
						nmevs = stoi(line);
					}
				}
			
				infile.close();

				int newvalue = nmevs + getNumEvents();
				string filename = "events.txt";
				ofstream outfile("temp.txt");
				if (!outfile) {
					cout << "Unable to open file." << endl;
					return;
				}

				int currentLine = 1;
				infile.open("events.txt");
				while (getline(infile, line)) {
					if (currentLine == line_number+1) {
						line = to_string(newvalue);
					}
					if (currentLine == line_number+2+nmevs) {
						for (int i = 0; i < getNumEvents(); i++) {
							outfile << events[i] << endl;
						}
					}
					outfile << line << endl;
					currentLine++;
				}

				infile.close();
				outfile.close();

				remove(filename.c_str());
				rename("temp.txt", filename.c_str());
	}
}
 Event::~Event(){

}

int search_date(int day, int month, int year) {
	ifstream file("events.txt");
	string line;
	int line_number = 0;
	while (getline(file, line)) {
		line_number++;
		int d, m, y;
		if (sscanf(line.c_str(), "%d %d %d", &d, &m, &y) == 3 && d == day && m == month && y == year) {

			file.close();
			return line_number;
		}
	}
	file.close();
	return -1;
}
int getCurrentYear() {
    time_t now = time(nullptr);
    tm* localTime = localtime(&now);
    return localTime->tm_year + 1900; 
}
int getCurrentMonth() {
    time_t now = time(nullptr);
    tm* localTime = localtime(&now);
    return localTime->tm_mon + 1; 
}
void printLinesFromFile(int start_line, int num_lines) {
	string line;

	std::ifstream infile("events.txt");
	if (!infile) {
		cout << "Unable to open file." << endl;
		return;
	}

	int current_line_number = 1;
	while (current_line_number < start_line) {
		getline(infile, line);
		current_line_number++;
	}
	int i=1;
	
	while (getline(infile, line) && num_lines > 0) {
		cout <<i<<"/ "<< line << endl;
		i++;
		num_lines--;
	}

	infile.close();
}

void printEventsForDate(int day, int month, int year) {
	string line;
	int num_events;


	ifstream infile("events.txt");
	if (!infile) {
		cout << "Unable to open file." << endl;
		return;
	}

	bool date_found = false;
	int current_line_number = 0;
	while (getline(infile, line)) {
		current_line_number++;
	
		stringstream ss(line);
		int d, m, y;
		ss >> d >> m >> y;
		if (d == day && m == month && y == year) {
			date_found = true;
			
			getline(infile, line);
			num_events = stoi(line);
			break;
		}
	}

	infile.close();


	if (!date_found) {
		cout << "No events found for the requested date." << endl;
		return;
	}

	
	int start_line = current_line_number +2;
	printLinesFromFile(start_line, num_events);
}
void deleteLineFromFile(int lineToDelete) {

	ifstream infile("events.txt");
	if (!infile) {
		cout << "Unable to open file." << endl;
		return;
	}


	ofstream outfile("temp.txt");
	if (!outfile) {
		cout << "Unable to create temporary file." << endl;
		infile.close();
		return;
	}


	string line;
	int lineNum = 0;
	while (getline(infile, line)) {
		lineNum++;
		if (lineNum != lineToDelete) {
			outfile << line << endl;
		}
	}
	cout<<"the event has been deleted successfully"<<endl;


	infile.close();
	outfile.close();


	remove("events.txt");
	rename("temp.txt", "events.txt");
}

void deletenumber_of_eventes(int line_number, int many) {
	int nmevs;
	ifstream infile("events.txt");
	if (!infile) {
		cout << "Unable to open file." << endl;
		return;
	}

	string line;
	for (int i = 1; i <= line_number+1; i++) {
		getline(infile, line);
		if (i == line_number+1) {
			nmevs = stoi(line);
		}
	}

	infile.close();

	int newvalue = nmevs - many;



	string filename = "events.txt";
	ifstream infile2(filename);
	ofstream outfile("temp.txt");

	
	int current_line_number = 1;
	while (getline(infile2, line)) {
		if (current_line_number == line_number+1) {
			outfile << newvalue << endl;
		} else {
			outfile << line << endl;
		}
		current_line_number++;
	}

	infile2.close();
	outfile.close();


	remove("events.txt");
	rename("temp.txt", "events.txt");


}





int DAYS_IN_MONTH[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};


const string MONTH_NAMES[] = {"January", "February", "March", "April", "May", "June",
                              "July", "August", "September", "October", "November", "December"
                             };
const string DAY_NAMES[] = {"Su", "Mo", "Tu", "We", "Th", "Fr", "Sa"};
enum DayOfWeek { SU, MO, TU, WE, TH, FR, SA };
DayOfWeek dayOfWeek(int year, int month, int day) {
	int q = day;
	int m = (month + 9) % 12 + 1;
	int Y = year - (month <= 2);
	int d = Y % 100;
	int c = Y / 100;

	int f = q + ((13*m - 1) / 5) + d + (d / 4) + (c / 4) - 2*c;
	int h = f % 7;

	if (h < 0) {
		h += 7;
	}

	return static_cast<DayOfWeek>(h);
}


bool isleapyear (int year) {

	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

void afficher(int year,int month ) {


	cout <<  MONTH_NAMES[month] << " " << year << "\n";


	for (int i = 0; i < 7; i++) {
		cout << DAY_NAMES[i] << "\t";
	}
	cout << "\n";


	DayOfWeek firstDay = dayOfWeek(year, month+1, 1);


	for (int i = 0; i < firstDay; i++) {
		cout << "\t";
	}


	for (int day = 1 ; day <= DAYS_IN_MONTH[month]; day++) {
		// Print the day
		cout << day << "\t";

		if ((day +firstDay) % 7 == 0)   {
			cout << "\n";

		}
	}

	cout << "\n";


}
int menu () {
	int choix;
	cout<<endl<<endl<<endl<<"enter 1 to add an event"<<endl;
	cout<<"enter 2 to delete an event"<<endl;
	cout<<"enter 3 to choose another day "<<endl;
	cout<<"enter 4 to close the app "<<endl;
	cin>>choix;
	return choix;
}