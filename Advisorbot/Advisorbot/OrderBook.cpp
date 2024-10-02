#include "OrderBook.h"
#include "CSVReader.h"
#include "LineArt.h"
#include <map>
#include <iostream>
#include <algorithm>

using namespace std;


OrderBook::OrderBook(string filename)
{
	LineArt::PrintLineTitle("Loading market data, please wait");
	orders = CSVReader::readCSV(filename);
}

vector< string> OrderBook::GetKnownProducts()
{
	vector< string> products;
	map < string, bool> prodMap;
	for (OrderBookEntry& e : orders)
	{
		prodMap[e.product] = true;
	}
	for (auto const& e : prodMap)
	{
		products.push_back(e.first);
	}
	return products;
}

vector<OrderBookEntry> OrderBook::GetOrders(
	OrderBookType type,
	string product,
	string timestamp)
{
	vector<OrderBookEntry> orders_sub;

	for (OrderBookEntry const& e : orders)
	{
		if (e.orderType == type &&
			e.product == product &&
			e.timestamp == timestamp)
		{
			orders_sub.push_back(e);
		}
	}

	return orders_sub;
}

double OrderBook::GetHighPrice(vector<OrderBookEntry>& orders)
{
	double max{ orders[0].price };
	for (OrderBookEntry& e : orders) {
		if (e.price > max) max = e.price;
	}
	return max;
}

double OrderBook::GetLowPrice(vector<OrderBookEntry>& orders)
{
	double min{ orders[0].price };
	for (OrderBookEntry& e : orders) {
		if (e.price < min) min = e.price;
	}
	return min;
}
double OrderBook::GetAveragePrice(vector<OrderBookEntry>& orders)
{
	double allPrices = 0;
	for (OrderBookEntry& e : orders)allPrices += e.price;
	return (allPrices / orders.size());
}

string OrderBook::GetEarliestTime()
{
	return orders[0].timestamp;
}

string OrderBook::GetNextTime(string timestamp)
{
	string time = "";
	for (OrderBookEntry& e : orders) {
		if (e.timestamp > timestamp)
		{
			time = e.timestamp;
			break;
		}
	}
	if (time == "")
	{
		time = GetEarliestTime();
	}
	return time;
}
string OrderBook::GetPreviousTime(string timestamp)
{
	string time = "";
	for (int i = orders.size() - 1; i >= 0; i--) {
		if (orders[i].timestamp < timestamp)
		{
			time = orders[i].timestamp;
			break;
		}
	}
	if (time == "")
	{
		time = GetEarliestTime();
	}
	return time;
}

double OrderBook::GetPriceDiffAverage(vector<OrderBookEntry>& orders, vector<OrderBookEntry>& prevOrders)
{
	return GetAveragePrice(orders) - GetAveragePrice(prevOrders);
}
