#include <iostream>
#include <ctime>
#include <string>
using namespace std;

struct Tiempo
{
    int seconds;
    int minutes;
    int hours;
    int day;
    int month;
    int year;
    string namemonth;
    string currentdate;
    time_t now = time(0);
    const char * dt = ctime(&now);
    tm * ltm = localtime(&now);
    Tiempo()
    {
        seconds = ltm->tm_sec;
        minutes = 1 + ltm->tm_min;
        day = ltm->tm_mday;
        hours = ltm->tm_hour;
        month = 1 + ltm->tm_mon;
        year = 1900 + ltm->tm_year;
        namemonth = "";
        currentdate = dt;
    }
    void print()
    {        
        cout<<currentdate<<endl;
    }
};
