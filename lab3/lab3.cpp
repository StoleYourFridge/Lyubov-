#include "lab3header.h"

using namespace std;

int main()
{
	PlayArea playArea;
	try 
	{
		playArea = PlayArea("examples/example1.txt");
	}
	catch (string errorText)
	{
		cout << errorText;
		return 0;
	}
	printPlayAreaCreationResult(playArea);
	return 0;
}