#include <iostream>
#include <cmath>
using namespace std;

enum DATE_ERROR {DAY_ERROR, MONTH_ERROR, YEAR_ERROR};
const int MIN_YEAR = 1970;

struct data{
	int day, month, year, days_from_MIN_YEARS;
};

bool is_leap_year(const int&);
int compute_days(const data&);
data get_date(const int&, const int&, const int&);

int main(){
	data prima_data, seconda_data;
	int d, m, y;
// throw exception if something goes wrong:
try{
	cout<<"insert first date: ";
	cin>>d>>m>>y;
	prima_data=get_date(d, m, y);
	cerr<<"insert second date: ";
	cin>>d>>m>>y;
	seconda_data = get_date(d, m, y);
}
// exceptions handler:
catch(DATE_ERROR n){
	cerr<<"Error occured in passing: ";
	switch(n){
		case DAY_ERROR:
			cerr<<"day";
			break;
		case MONTH_ERROR:
			cerr<<"month";
			break;
		case YEAR_ERROR:
			cerr<<"year";
			break;
		default:
			cerr<<"something I can't manage.";
			break;
	}
	cerr<<endl;
	return 1;
}
	cerr<<"days between dates: "<<abs(prima_data.days_from_MIN_YEARS-seconda_data.days_from_MIN_YEARS)<<endl;
	return 0;
}

bool is_leap_year(const int& year){
	return ((year%400==0 ||year%100 != 0)&&year%4 ==0);
}

int compute_days(const data& d){
	// init result:
	int result = -1;
	// add day number to result:
	result+=d.day;
	// add 365 or 366 day to final result depending on leap year:
	for(int i=MIN_YEAR; i<d.year; i++) result+= (is_leap_year(i)? 366 : 365);
	// add entire months:
	switch(d.month-1){
		case 11:
			result+=30;
		case 10:
			result+=31;
		case 9:
			result+=30;
		case 8:
			result+=31;
		case 7:
			result+=31;
		case 6:
			result+=30;
		case 5:
			result+=31;
		case 4:
			result+=30;
		case 3:
			result+=31;
		case 2:
			result+=(is_leap_year(d.year)	? 29 : 28);
		case 1:
			result+=31;
	}
	return result;
}

data get_date(const int& d, const int& m, const int& y){
	if(y<MIN_YEAR) throw YEAR_ERROR;
	switch(m){
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			if(d<0 || d>31) throw DAY_ERROR;
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			if(d<0 || d>30) throw DAY_ERROR;
			break;
		case 2:
			if(d<0 || (is_leap_year(y)? d>29 : d>28)) throw DAY_ERROR;
			break;
		default:
			throw MONTH_ERROR;
	}

	data new_data;
	new_data.day = d;
	new_data.month = m;
	new_data.year = y;
	new_data.days_from_MIN_YEARS = compute_days(new_data);
	return new_data;
}
