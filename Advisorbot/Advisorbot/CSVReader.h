#pragma once
#include<iostream>
#include"OrderBookEntry.h"
#include <vector>
#include <string>

using namespace std;

/*
* This is the CSVReader Class Template/Interface
*/
class CSVReader
{
public:
	/*Constructor Function: takes no arguments*/
	CSVReader();
	/*reads CSV File and returns a vector of OBE(OrderBookEntry) objects.*/
	static  vector<OrderBookEntry> readCSV(string CSVFile);

	/*Takes a string and returns string vector. Elements end when a separator is found.
	Example:
	String: "one,two,three"
	Separator: ','
	Returned Vector: ["one", "two", "three"]*/
	static  vector< string> tokenise(string line, char separator);

	/*turns string to OBT(OrderBookType) enum.*/
	static OrderBookType stringToOBT(string s);

private:
	/*turns string vector into OBE(OrderBookEntry) object.*/
	static OrderBookEntry stringsToOBE(vector< string> strings);
};