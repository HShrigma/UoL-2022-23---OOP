#include "CSVReader.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

CSVReader::CSVReader()
{

};
OrderBookType CSVReader::stringToOBT(string s)
{
	if (s == "bid") return OrderBookType::bid;
	else if (s == "ask") return OrderBookType::ask;
	else return OrderBookType::unkown;
}

vector<OrderBookEntry> CSVReader::readCSV(string CSVFile)
{
	vector<OrderBookEntry> entries;
	ifstream data;
	string line;
	vector< string> tokens;

	data.open(CSVFile);

	if (data.is_open())
	{
		while (getline(data, line))
		{
			//Optimisation - removed try/catch snippet for faster reading speed due to data being thoroughly tested on and no errors were found
			OrderBookEntry obe = stringsToOBE(tokenise(line, ','));
			entries.push_back(obe);
		}
	}
	data.close();

	return entries;
};
vector< string> CSVReader::tokenise(string line, char separator)
{
	vector< string> strings;
	unsigned int index = 0;

	while (index < line.length()) {
		string temp = "";
		for (auto i = index; i < line.length(); i++)
		{
			if (line[i] == separator) {
				break;
			}
			temp += line[i];
		}
		strings.push_back(temp);
		index += temp.size() + 1;
	}

	return strings;
};

OrderBookEntry CSVReader::stringsToOBE(vector< string> strings)
{
	double price = 0;
	double amount = 0;
	OrderBookType orderType;

	if (strings.size() != 5) {
		throw  exception{};
	}
	price = stod(strings[3]);
	amount = stod(strings[4]);
	OrderBookEntry entry{ price,
		amount,
		strings[0],
		strings[1],
		stringToOBT(strings[2]) };

	return entry;
};