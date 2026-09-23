#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

struct logArray
{
	vector<string> lines;
};

struct Date
{
	int month;
	int day;
	int hour;
	int minute;
	int second;
};

int month2num(const string& month)
{
	if (month == "Jan") return 1;
	if (month == "Feb") return 2;
	if (month == "Mar") return 3;
	if (month == "Apr") return 4;
	if (month == "May") return 5;
	if (month == "Jun") return 6;
	if (month == "Jul") return 7;
	if (month == "Aug") return 8;
	if (month == "Sep") return 9;
	if (month == "Oct") return 10;
	if (month == "Nov") return 11;
	if (month == "Dec") return 12;
	return -1;
}

bool getDate(const string& line, Date& resultDate)
{
	istringstream input(line);

	string monthText;
	int day;
	string timeText;

	if (!(input >> monthText >> day >> timeText))
	{
		return false;
	}

	int month = month2num(monthText);
	if (month == -1)
	{
		return false;
	}

	istringstream timeInput(timeText);

	int hour;
	int minute;
	int second;
	char colon1;
	char colon2;

	if (!(timeInput >> hour >> colon1 >> minute >> colon2 >> second))
	{
		return false;
	}

	resultDate.month = month;
	resultDate.day = day;
	resultDate.hour = hour;
	resultDate.minute = minute;
	resultDate.second = second;

	return true;
}

void init(logArray& log)
{
	log.lines.clear();
}

bool readFile(const string& filename, vector<string>& lines)
{
	ifstream file(filename);
	if (!file.is_open())
	{
		cerr << "Error opening file: " << filename << endl;
		return false;
	}
	string line;
	while (getline(file, line))
	{
		lines.push_back(line);
	}
	file.close();
	return true;
}

void printLines(const vector<string>& lines)
{
	for (const auto& line : lines)
	{
		cout << line << endl;
	}
}

bool compareDate(const Date& first, const Date& second)
{
	if (first.month != second.month)
	{
		return first.month < second.month;
	}

	if (first.day != second.day)
	{
		return first.day < second.day;
	}

	if (first.hour != second.hour)
	{
		return first.hour < second.hour;
	}

	if (first.minute != second.minute)
	{
		return first.minute < second.minute;
	}

	return first.second < second.second;
}

bool compareLine(const string& firstLine, const string& secondLine)
{
	Date firstDate;
	Date secondDate;

	if (!getDate(firstLine, firstDate))
	{
		return false;
	}

	if (!getDate(secondLine, secondDate))
	{
		return false;
	}

	return compareDate(firstDate, secondDate);
}

void sortByDate(vector<string>& lines)
{
	sort(lines.begin(), lines.end(), compareLine);
}

int main()
{
	logArray log;
	init(log);
	readFile("bitacora.txt", log.lines);
	sortByDate(log.lines);
	printLines(log.lines);
}