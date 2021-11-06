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
	bool cargoCarriage;
	bool loaded;
public:
	Carriage();
	Carriage(bool isCargoCarriageInput, bool isLoadedInput);
	void load();
	void unload();
	bool isCargo();
	bool isLoaded();
};

class Locomotive
{
private:
	int speed;
	int serviceTimeLeft;
public:
	Locomotive();
	Locomotive(int speedInput, int serviceTimeLeftInput);
	void increaseSpeedByOne();
	void decreaseSpeedByOne();
	void reduceServiceTimeLeftBy(int input);
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
	int currStationInPathIndex = 0;
	bool enRoute = false;
	int currStation;
	int currStationType;
	int currDestination;
	int currDistanceToDestination;
	bool broken = false;
public:
	Train();
	Train(int locomotiveSpeed, int locomotiveServiceTimeLeft, int carriagesQuantity, bool** carriagesInfo, int* pathInput, int pathLengthInput);
	void setPath(int* input);
	void setPathLength(int input);
	void setEnRoute(bool input);
	void setCurrStation(int input);
	void setCurrStationType(int input);
	void setCurrDestination(int input);
	void setCurrDistanceToDestination(int input);
	void send();
	void stop();
	void load();
	void unload();
	void disintegrate();
	void reduceServiceTimeLeftBy(int input);
	Locomotive getLocomotive();
	Carriage* getCarriages();
	int getCarriagesQuantity();
	int* getPath();
	int getPathLength();
	bool isEnRoute();
	bool isBroken();
	int getCurrStation();
	int getCurrStationType();
	int getCurrDestination();
	int getCurrDistanceToDestination();
	int turnsLeftToDestination();
	int getServiceTimeLeft();

	void printInfo();
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
	int getLinkWeight(int from, int to);
public:
	PlayArea();
	PlayArea(string inputFilePath);
	bool directedLinkBetween(PlayAreaNode* node1, PlayAreaNode* node2);
	bool isCyclicPath(int* stationIndeces, int pathLength);
	PlayAreaNode** getStations();
	Train* getTrains();
	int getStationsQuantity();
	int getTrainsQuantity();
	void sendTrain(int trainIndex);
	void stopTrain(int trainIndex);
	void nextTurn();

	void printPlayAreaState();
};

void printPlayAreaCreationResult(PlayArea result);