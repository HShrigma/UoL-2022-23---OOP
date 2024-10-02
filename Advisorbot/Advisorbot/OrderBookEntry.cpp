#include "OrderBookEntry.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

OrderBookEntry::OrderBookEntry(
	double _price,
	double _amount,
	string _timestamp,
	string _product,
	OrderBookType _orderType)
	:price(_price), amount(_amount), timestamp(_timestamp), product(_product), orderType(_orderType)
{

}

double price;
double amount;
string timestamp;
string product;