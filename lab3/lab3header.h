#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct PlayAreaNode
{
	int id;
	int type = 0;
	int adjacentQuantity = 0;
	PlayAreaNode** adjacent;
	int* weights;
};

class Carriage
{
private:
	bool isCargoCarriage;
	bool isLoaded;
public:
	Carriage();
	Carriage(bool isCargoCarriageInput, bool isLoadedInput);
	bool getIsCargo();
	bool getIsLoaded();
};

class Locomotive
{
private:
	int speed;
	int serviceTimeLeft;
public:
	Locomotive();
	Locomotive(int speedInput, int serviceTimeLeftInput);
	void reduceSpeed();
	int getSpeed();
	int getServiceTimeLeft();
};

class Train
{
private:
	Locomotive locomotive;
	Carriage* carriages;
	int carriagesQuantity;
	int* path;
	int pathLength;
public:
	Train();
	Train(int locomotiveSpeed, int locomotiveServiceTimeLeft, int carriagesQuantity, bool** carriagesInfo, int* pathInput, int pathLengthInput);
	void setPath(int* input);
	void setPathLength(int input);
	Locomotive getLocomotive();
	Carriage* getCarriages();
	int getCarriagesQuantity();
	int* getPath();
	int getPathLength();
};

class PlayArea
{
private:
	PlayAreaNode** stations;
	Train* trains;
	int stationsQuantity;
	int trainsQuantity;
	int scanForInt(string input, int* startingIndexAddress, char limiter);
	int scanForInt(string input, int* startingIndexAddress, char* limiters, int limitersQuantity);
	void fillPlayAreaFromFile(string filePath);
	void fillStationsInfo(ifstream& input);
	void fillStationInfo(string input);
	void readStationInfoUntilUnderscore(ifstream& input);
	void fillTrainsInfo(ifstream& input);
	void fillTrainInfo(string input);
	void readTrainInfoUntilEOF(ifstream& input);
	void allocMemoryForCarriagesInfo(bool*** carriagesInfo, int carriagesQuantity);
	void fillCarriagesInfo(bool** carriagesInfo, string input, int* startingIndexAddress);
	int calcPathLength(string input, int startingIndex);
	int* readPath(string input, int pathLength, int startingIndex);
	void allocMemoryForAdjacent(PlayAreaNode* station, int input);
	void setAdjacent(PlayAreaNode* station, string input, int startingIndex);
public:
	PlayArea(string inputFilePath);
	bool directedLinkBetween(PlayAreaNode* node1, PlayAreaNode* node2);
	bool isCyclicPath(int* stationIndeces, int pathLength);
	PlayAreaNode** getStations();
	Train* getTrains();
	int getStationsQuantity();
	int getTrainsQuantity();
};

void printPlayAreaCreationResult(PlayArea result);