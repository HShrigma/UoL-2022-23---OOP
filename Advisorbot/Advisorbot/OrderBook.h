#pragma once
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <string>
#include <vector>

using namespace std;

class OrderBook
{
public:
	/*Constructor: Read in .CSV data file*/
	OrderBook(string filename);
	/*Get vector of all known products in a data set.*/
	vector< string> GetKnownProducts();
	/*Gets the previous timestamp of by comparing all orders' timestamps to the one given as a parameter*/
	string GetPreviousTime(string timestamp);
	/**
	Return vector of products according to set filter
	**/
	vector<OrderBookEntry> GetOrders(
		OrderBookType type,
		string product,
		string timestamp);
	/*Returns the earliest timestamp*/
	string GetEarliestTime();
	/*Returns the next timestamp
	  If no next timestamp is found, the function will return the earliest timestamp.*/
	string GetNextTime(string timestamp);

	/**
	Returns the highest price of an order set*/
	static double GetHighPrice(vector<OrderBookEntry>& orders);
	/**
	Returns the lowest price of an order set
	**/
	static double GetLowPrice(vector<OrderBookEntry>& orders);
	/**
	Returns the average price of an order set*
	*/
	static double GetAveragePrice(vector<OrderBookEntry>& orders);
	/**
	Returns the difference between the average  prices of the current and previous timeframes
	**/
	static double GetPriceDiffAverage(vector<OrderBookEntry>& orders, vector<OrderBookEntry>& prevOrders);

private:
	vector<OrderBookEntry> orders;

};

