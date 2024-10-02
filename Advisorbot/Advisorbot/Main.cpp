#include "Main.h"
#include "CSVReader.h"
#include "LineArt.h"
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "CSVReader.h"

using namespace std;

const string invalidInputSize = "Invalid Input Size!";
const string invalidCommand = "Invalid Command!";
const string invalidOBT = "Invalid Order Book Type!";
const string invalidProduct = "Invalid Product!";

void Main::Init()
{
	PrintTitle();
	CurrentTime = Orders.GetEarliestTime();
	while (true) {
		LineArt::PrintLineTitle("Menu");
		string input = GetInput();
		ProcessInput(input);
	}

}
void Main::PrintTitle() {
	string title = "";
	string line = "";

	ifstream title_txt;
	title_txt.open("ascii_title.txt");
	if (title_txt.is_open())
	{
		while (getline(title_txt, line))
		{
			title += line + "\n";
		}
	}
	else
	{
		cout << "ERROR:NO FILE OPENED";
	}
	cout << title;
}
#pragma region Base Loop

string Main::GetInput()
{
	LineArt::PrintLineSegment("Please enter a command, or enter help for a list of commands:");
	string input;
	getline(cin, input);
	return input;
}

void Main::ProcessInput(string& input)
{
	//get tokens
	if (input.length() == 0)
	{
		LineArt::PrintLineSegment(invalidInputSize);
		return;
	}
	vector<string> tokens = CSVReader::tokenise(input, ' ');

	if (tokens[0] == "help")
	{
		if (tokens.size() == 1)
		{
			PrintHelp();
		}
		else if (tokens.size() == 2)
		{
			PrintHelp(tokens[1]);
		}
		else
		{
			LineArt::PrintLineSegment(invalidInputSize);
		}
	}
	else if (tokens[0] == "prod")
	{
		PrintProd();
	}
	else if (tokens[0] == "min")
	{
		if (tokens.size() != 3)
		{
			LineArt::PrintLineSegment(invalidInputSize);
			return;
		}
		PrintMin(tokens);
	}
	else if (tokens[0] == "max")
	{
		if (tokens.size() != 3)
		{
			LineArt::PrintLineSegment(invalidInputSize);
			return;
		}
		PrintMax(tokens);
	}
	else if (tokens[0] == "avg")
	{
		if (tokens.size() != 4)
		{
			LineArt::PrintLineSegment(invalidInputSize);
			return;
		}
		PrintAvg(tokens);
	}
	else if (tokens[0] == "predict")
	{
		if (tokens.size() != 4)
		{
			LineArt::PrintLineSegment(invalidInputSize);
		}
		PrintPredict(tokens);
	}
	else if (tokens[0] == "time")
	{
		if (tokens.size() != 1)
		{
			LineArt::PrintLineSegment(invalidInputSize);
		}
		PrintTime();
	}
	else if (tokens[0] == "step")
	{
		if (tokens.size() != 1)
		{
			LineArt::PrintLineSegment(invalidInputSize);
		}
		MoveStep();
	}
	else if (tokens[0] == "track")
	{
		if (tokens.size() != 1)
		{
			LineArt::PrintLineSegment(invalidInputSize);
		}
		Track();
	}
	else
	{
		LineArt::PrintLineSegment(invalidCommand);
	}

}
#pragma endregion

#pragma region MenuCommands
void Main::PrintHelp()
{
	LineArt::PrintBorderThick();
	LineArt::PrintLine("help");
	LineArt::PrintLine("help <cmd>");
	LineArt::PrintLine("prod");
	LineArt::PrintLine("min");
	LineArt::PrintLine("max");
	LineArt::PrintLine("avg");
	LineArt::PrintLine("predict");
	LineArt::PrintLine("time");
	LineArt::PrintLine("step");
	LineArt::PrintLine("track");
	LineArt::PrintBorderThick();
}
void Main::PrintHelp(string cmd)
{
	string line;
	if (cmd == "help")
	{
		line = " help - List all available commands.";
	}
	else if (cmd == "prod")
	{
		line = " prod - List all available products.";
	}
	else if (cmd == "min")
	{
		line = " min <prod> <ask/bid> - Find minimum bid or ask for product in current time step.";
	}
	else if (cmd == "max")
	{
		line = " max <prod> <ask/bid> - Find maximum bid or ask for product in current time step.";
	}
	else if (cmd == "avg")
	{
		line = " avg <prod> <ask/bid> <steps> -  Compute average ask or bid for the sent product over the sent number of time steps.";
	}
	else if (cmd == "predict")
	{
		line = " predict <max/min> <product> <ask/bid> - Predict max or min ask or bid for the sent product for the next time step.";
	}
	else if (cmd == "time")
	{
		line = " time - State current time in dataset, i.e. which timeframe are we looking at.";
	}
	else if (cmd == "step")
	{
		line = " step - Move to next time step.";
	}
	else if (cmd == "track")
	{
		line = " track - Shows the best and worst growing products for asks and bids.";
	}
	else
	{
		line = invalidCommand;
	}
	LineArt::PrintLineSegment(line);
}
void Main::PrintProd()
{
	LineArt::PrintLineTitle("Products");
	LineArt::PrintBorderThick();
	for (string& prod : Orders.GetKnownProducts()) {
		LineArt::PrintLineSegment(prod);
	}
	LineArt::PrintBorderThick();
}
void Main::PrintMin(vector<string> tokens)
{
	double lowest = GetMin(tokens, CurrentTime);
	if (lowest != -1)
	{
		LineArt::PrintLineSegment("The min " + tokens[2] + " for " + tokens[1] + " is " + to_string(lowest));
	}

}
void Main::PrintMax(vector<string> tokens)
{
	double highest = GetMax(tokens, CurrentTime);
	if (highest != -1)
	{
		LineArt::PrintLineSegment("The max " + tokens[2] + " for " + tokens[1] + " is " + to_string(highest));
	}
}
void Main::PrintAvg(vector<string> tokens)
{
	//check if product is valid
	bool validProd = false;
	for (string& prod : Orders.GetKnownProducts()) {
		if (tokens[1] == prod)
		{
			validProd = true;
			break;
		}
	}
	if (!validProd)
	{
		LineArt::PrintLineSegment(invalidProduct);
		return;
	}
	//check if OBT is valid
	OrderBookType type = CSVReader::stringToOBT(tokens[2]);
	if (type == OrderBookType::unkown)
	{
		LineArt::PrintLineSegment(invalidOBT);
		return;
	}
	//check if timestamp can be parsed
	int stampCount;
	try
	{
		stampCount = stoi(tokens[3]);
	}
	catch (const std::exception&)
	{
		LineArt::PrintLineSegment("Invalid Argument! Please enter an integer value after avg <product> <ask/bid> ");
		return;
	}
	string stamp = CurrentTime;
	double avg = 0;
	//loop through desired timestamps
	for (size_t i = 0; i < stampCount; i++)
	{
		//get entries for desired product, type, timestamp
		vector<OrderBookEntry> entries = Orders.GetOrders(type, tokens[1], stamp);
		//update average and stamp
		avg += OrderBook::GetAveragePrice(entries);
		stamp = Orders.GetPreviousTime(stamp);
		if (stamp == Orders.GetEarliestTime())
		{
			break;
		}
	}
	//divide average sum by the count of timeframes to get true average
	avg /= stampCount;
	string output = "The average " + tokens[1] + " " + tokens[2] + " price over the last " + tokens[3] + " timesteps was " + to_string(avg);
	LineArt::PrintLineSegment(output);
}
void Main::PrintPredict(vector<string> tokens)
{
	// predict <max / min> <product> <ask / bid>
	bool min = false;
	if (tokens[1] == "max") {}
	else if (tokens[1] == "min")
	{
		min = true;
	}
	else
	{
		LineArt::PrintLineSegment(invalidCommand);
		return;
	}
	vector<string> inputs;
	inputs.push_back(tokens[0]);
	inputs.push_back(tokens[2]);
	inputs.push_back(tokens[3]);
	unsigned int loops = 0;
	double sum = 0;
	string timestamp = CurrentTime;

	do
	{
		try
		{
			if (min)
			{
				sum += GetMin(inputs, timestamp);
			}
			else
			{
				sum += GetMax(inputs, timestamp);
			}
		}
		catch (const std::exception&)
		{
			return;
		}
		loops++;
		timestamp = Orders.GetPreviousTime(timestamp);
	} while (timestamp != Orders.GetEarliestTime());

	double prediction = sum / loops;
	LineArt::PrintLineSegment("The " + tokens[1] + " " + tokens[2] + " " + tokens[3] + " price may be " + to_string(prediction));
}
void Main::PrintTime()
{
	string output = "Current time is: " + CurrentTime;
	LineArt::PrintLineSegment(output);
}
void Main::MoveStep()
{
	LineArt::PrintLineTitle("Going to next timeframe");
	CurrentTime = Orders.GetNextTime(CurrentTime);
}
void Main::Track()
{
	vector<string> prods = Orders.GetKnownProducts();
	double growthBestAsk = DBL_MIN_EXP;
	double growthBestBid = DBL_MIN_EXP;

	double growthWorstAsk = DBL_MAX_EXP;
	double growthWorstBid = DBL_MAX_EXP;

	string bestAsk = "";
	string worstAsk = "";
	string bestBid = "";
	string worstBid = "";

	//loop through products
	for (size_t i = 0; i < prods.size(); i++)
	{
		//get current asks&bids
		vector<OrderBookEntry> asks = Orders.GetOrders(OrderBookType::ask, prods[i], CurrentTime);
		vector<OrderBookEntry> bids = Orders.GetOrders(OrderBookType::bid, prods[i], CurrentTime);
		//get previous asks&bids
		vector<OrderBookEntry> prevAsks = Orders.GetOrders(OrderBookType::ask, prods[i], Orders.GetPreviousTime(CurrentTime));
		vector<OrderBookEntry> prevBids = Orders.GetOrders(OrderBookType::bid, prods[i], Orders.GetPreviousTime(CurrentTime));
		//get what percentage of the previous average price is the difference between the current and previous price
		double askPercent = (OrderBook::GetPriceDiffAverage(asks, prevAsks) / OrderBook::GetAveragePrice(prevAsks)) * 100;
		double bidPercent = (OrderBook::GetPriceDiffAverage(bids, prevBids) / OrderBook::GetAveragePrice(prevBids)) * 100;

		//logic for min/max vars
		if (askPercent > growthBestAsk)
		{
			growthBestAsk = askPercent;
			bestAsk = prods[i];
		}
		if (askPercent < growthWorstAsk)
		{
			growthWorstAsk = askPercent;
			worstAsk = prods[i];
		}
		if (bidPercent > growthBestBid)
		{
			growthBestBid = bidPercent;
			bestBid = prods[i];
		}
		if (bidPercent < growthWorstBid)
		{
			growthWorstBid = bidPercent;
			worstBid = prods[i];
		}
	}

	LineArt::PrintBorderThick();
	LineArt::PrintLineSegment("Best ask is " + bestAsk + " with a growth of " + to_string(growthBestAsk) + "%");
	LineArt::PrintLineSegment("Worst ask: " + worstAsk + " with a growth of " + to_string(growthWorstAsk) + "%");
	LineArt::PrintLineSegment("Best bid: " + bestBid + " with a growth of " + to_string(growthBestBid) + "%");
	LineArt::PrintLineSegment("Worst bid: " + worstBid + " with a growth of " + to_string(growthWorstBid) + "%");
	LineArt::PrintBorderThick();
}
#pragma endregion
#pragma region Helper Functions
double Main::GetMin(vector<string> tokens, string timestamp)
{
	double output = -1;
	//check if product is valid
	bool validProd = false;
	for (string& prod : Orders.GetKnownProducts()) {
		if (tokens[1] == prod)
		{
			validProd = true;
			break;
		}
	}
	if (!validProd)
	{
		LineArt::PrintLineSegment(invalidProduct);
		return output;
	}
	//check if OBT is valid
	OrderBookType type = CSVReader::stringToOBT(tokens[2]);
	if (type == OrderBookType::unkown)
	{
		LineArt::PrintLineSegment(invalidOBT);
		return output;
	}
	//get orders of this timestamp with product and OBT specified by userinput
	vector<OrderBookEntry> entries = Orders.GetOrders(type, tokens[1], timestamp);
	return  OrderBook::GetLowPrice(entries);
}
double Main::GetMax(vector<string> tokens, string timestamp)
{
	double output = -1;
	//check if product is valid
	bool validProd = false;
	for (string& prod : Orders.GetKnownProducts()) {
		if (tokens[1] == prod)
		{
			validProd = true;
			break;
		}
	}
	if (!validProd)
	{
		LineArt::PrintLineSegment(invalidProduct);
		return output;
	}
	//check if OBT is valid
	OrderBookType type = CSVReader::stringToOBT(tokens[2]);
	if (type == OrderBookType::unkown)
	{
		LineArt::PrintLineSegment(invalidOBT);
		return output;
	}
	//get orders of this timestamp with product and OBT specified by userinput
	vector<OrderBookEntry> entries = Orders.GetOrders(type, tokens[1], CurrentTime);
	return  OrderBook::GetHighPrice(entries);
}
#pragma endregion