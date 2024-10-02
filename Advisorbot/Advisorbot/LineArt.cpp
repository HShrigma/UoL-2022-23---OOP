#include "LineArt.h"
void LineArt::PrintLine(string input) {
	cout << input << endl;
}
void LineArt::PrintLineTitle(string input) {
	unsigned int borderLen = input.length() * 3;
	string spacing(input.length(), ' ');
	string border(borderLen, '=');

	cout << endl << border << endl << spacing << input << endl << border << endl << endl;
}
void LineArt::PrintLineSegment(string input) {
	string border(input.length(), '-');
	cout << border << endl << input << endl << border << endl;
}
void LineArt::PrintBorderThin() {
	cout << "---------------------" << endl;
}
void LineArt::PrintBorderThick() {
	cout << "=====================" << endl;
}