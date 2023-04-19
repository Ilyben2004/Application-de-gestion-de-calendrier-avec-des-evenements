#include <string>

using namespace std;


class Event {
	private:
		int year, day, month;
		string events[10];
		int numEvents;

	public:
		Event();

		void setAtts(int y, int d, int m);
		void setNumEvents(int nevs);
		
			void addEvent(string newEvent);
			
		int getYear() ;

		int getDay() ;

		int getMonth() ;

		int getNumEvents() ;

		string* getEvents();
			void writeEventsToFile(int day, int month, int year) ;
	




		~Event() ;
};

