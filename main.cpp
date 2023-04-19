#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include <vector>
#include "functions.cpp"
using namespace std;


int main() {

	int end_prog=0;


	int year,month,day;
	Event evs ;
	int choix;





	if(isleapyear (year)==true)  {
		DAYS_IN_MONTH[1]=29;
	}
	while (end_prog!=1 ) {


		evs.setNumEvents(0);
		cout << "Enter a year: ";
		cin >> year;
		system("cls");

		do {

			cout<<"choose a month (the number of the month) :  "<<endl;

			cin>>month;
		} while ((month>12) || (month<1)) ;

		system("cls");
		afficher(year,month-1);
		cout<<endl<<"choose the day  : ";
		cin>>day;
		DayOfWeek firstDay = dayOfWeek(year, month, day);
		system("cls");
		evs.setAtts(year,day,month);
		cout<<DAY_NAMES[firstDay-1]<<" "<<day<<"/"<<month<<"/"<<year<<endl;

		if (search_date(day,month, year)!=-1){
	        cout<<"the eventes for this date are :"<<endl;
			printEventsForDate(day,  month,  year);
				}
			else 
			cout<<"there is no eventes for this date"<<endl;
		choix = menu();
		switch(choix) {
			case 1 : {
				int times;
				string eventes;
				cout<<"how many eventes you want to add : ";
				cin>>times;
				cin.ignore();

				for (int i = 0; i<times; i++) {
					cout<<endl<<"add the event "<<i+1<<" : "<<endl;
					getline(cin, eventes);
					evs.addEvent(eventes);

				}
				evs.setNumEvents(times);
				evs.writeEventsToFile(day,month,year);
				break;
			}
			case 2: {
				int index,many ;
				cout<<endl<<"how many eventes you want do delete : ";
				cin>>many;
				for (int i=0 ; i<many ; i++) {
					cout<<endl<<"the number of the evente "<<i+1 << " that you wanna delete : ";
					cin>>index;
					deleteLineFromFile(search_date(day,month, year)+index+1);

				}
				deletenumber_of_eventes(search_date(day,month, year),many);

				break;
			}
			case 4 : {
				end_prog=1;
				break;
			}
		}
		if (choix!=3){
		
		cout<<" \n \n enter 0 to continue \n enter 1 to close the app"<<endl;
		cin>>end_prog;
	
		}
			system("cls");
	}

	return 0;
}

