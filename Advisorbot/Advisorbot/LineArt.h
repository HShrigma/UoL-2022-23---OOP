#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class LineArt
{
public:
	/**
	Prints a line of text with a newline separator at the end
	**/
	static void PrintLine(string input);
	/**
	Prints a line of centered line of text with newline separators before and after thick borders
	**/
	static void PrintLineTitle(string input);
	/**
	Prints text with a newline separator and thin borders
	**/
	static void PrintLineSegment(string input);
	/**
	prints a thin border and a newline separator
	**/
	static void PrintBorderThin();
	/**
	prints a thick border and a newline separator
	**/
	static void PrintBorderThick();
};

