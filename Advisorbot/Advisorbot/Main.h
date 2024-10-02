#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include "OrderBook.h"
using namespace std;

class Main
{
public:
	Main() = default;
	void Init();
private:
#pragma region Baseline Loop
	// -------------
	// Baseline Loop
	// -------------

	/**
		prints application title
	**/
	void PrintTitle();
	/**
		asks user for input and returns it as a string
	**/
	string GetInput();
	/**
		sees if user has selected appropriate input option
	**/
	void ProcessInput(string& input);

#pragma endregion
#pragma region Menu Commands
	// -------------
	// Menu Commands
	// -------------
	/**
		Command: help
		Purpose: list all available commands
		Example:
		user> help
		advisorbot> The available commands are help, help <cmd>, avg, time, (etc. list all commands)
	**/
	void PrintHelp();
	/**
		Command: help cmd
		Purpose: output help for the specified command
		Example:
		user> help avg
		avg ETH/BTC bid 10 -> average ETH/BTC bid over last 10 time steps
	**/
	void PrintHelp(string cmd);
	/**
		Command: prod
		Purpose: list available products
		Example:
		user> prod
		advisorbot> ETH/BTC,DOGE/BTC

	**/
	void PrintProd();
	/**
	Command: min product bid/ask
	Purpose: find minimum bid or ask for product in current time step
	Example:
	user> min ETH/BTC ask
	advisorbot> The min ask for ETH/BTC is 1.0	**/
	void PrintMin(vector<string> tokens);
	/**
		Command: max product bid/ask
		Purpose: find maximum bid or ask for product in current time step
		Example:
		user> max ETH/BTC ask
		advisorbot> The max ask for ETH/BTC is 1.0
	**/
	void PrintMax(vector<string> tokens);

	/**
		Command: avg product ask/bid timesteps
		Purpose: compute average ask or bid for the sent product over the sent number
		of time steps.
		Example:
		user> avg ETH/BTC ask 10
		advisorbot> The average ETH/BTC ask price over the last 10 timesteps was 1.0
**/
	void PrintAvg(vector<string> tokens);

	/**
		Command: predict max/min product ask/bid
		Purpose: predict max or min ask or bid for the sent product for the next time
		step
		Example:
		user> predict max ETH/BTC bid
		advisorbot> The max ETH/BTC bid price may be 1.0
		Note that it is up to you to select an appropriate algorithm to carry out the
		prediction. Most people use a moving average but there are more interesting
		algorithms.
	**/
	void PrintPredict(vector<string> tokens);

	/**
		Command: time
		Purpose: state current time in dataset, i.e. which timeframe are we looking at
		Example:
		user> time
		advisorbot> 2020/03/17 17:01:24
	**/
	void PrintTime();

	/**
		Command: step
		Purpose: move to next time step
		Example:
		user> step
		advisorbot> now at 2020/03/17 17:01:30
	**/
	void MoveStep();
	/**
		Command: Track
		Purpose: Shows the user the best and worst growing product for asks and bids on on this current timeframe.
		Example:
		user> advise 
		advisorbot> Best ask: ETH/BTC
		advisorbot> Best bid: ETH/BTC
		advisorbot> Worst ask: ETH/BTC
		advisorbot> Worst bid: ETH/BTC

		Note: Logic works on using a previous timeframe to establish what percentage does the average difference 
		of the products has grown or shrunk in this timeframe
	**/
	void Track();
#pragma endregion
#pragma region fields
	string CurrentTime;
	OrderBook Orders{ "20200601.csv" };

#pragma endregion
#pragma region Helper Functions
	double GetMin(vector<string> tokens, string timestamp);
	double GetMax(vector<string> tokens, string timestamp);
#pragma endregion
};

