#include "lab3header.h"

using namespace std;

PlayArea::PlayArea(string inputFilePath)
{
	fillPlayAreaFromFile(inputFilePath);
}

void PlayArea::fillPlayAreaFromFile(string filePath)
{
	ifstream input;
	input.open(filePath);
	fillStationsInfo(input);
	fillTrainsInfo(input);
}

void PlayArea::fillStationsInfo(ifstream& input)
{
	string currLine;
	getline(input, currLine);
	stationsQuantity = stoi(currLine);
	stations = new PlayAreaNode * [stationsQuantity];
	for (int i = 0; i < stationsQuantity; i++) stations[i] = new PlayAreaNode;
	readStationInfoUntilUnderscore(input);
	for (int i = 0; i < stationsQuantity; i++) stations[i]->id = i;
}

void PlayArea::fillStationInfo(string input)
{
	int currIndex = 0;
	int stationIndex = scanForInt(input, &currIndex, '(');
	currIndex++;
	allocMemoryForAdjacent(stations[stationIndex], scanForInt(input, &currIndex, ')'));
	currIndex += 2;
	setAdjacent(stations[stationIndex], input, currIndex);
}

void PlayArea::readStationInfoUntilUnderscore(ifstream& input)
{
	string currLine;
	getline(input, currLine);
	while (currLine[0] != '_')
	{
		fillStationInfo(currLine);
		getline(input, currLine);
	}
}

void PlayArea::fillTrainsInfo(ifstream& input)
{
	string currLine;
	getline(input, currLine);
	trainsQuantity = stoi(currLine);
	trains = new Train[trainsQuantity];
	readTrainInfoUntilEOF(input);
}

void PlayArea::fillTrainInfo(string input)
{
	Train currTrain;
	int currLocomotiveSpeed;
	int currLocomotiveServiceTimeLeft;
	int currCarriagesQuantity;
	bool** currCarriagesInfo;
	int currIndex = 0;
	int trainIndex = scanForInt(input, &currIndex, ':');
	currIndex += 2;
	currLocomotiveSpeed = scanForInt(input, &currIndex, ',');
	currIndex += 2;
	currLocomotiveServiceTimeLeft = scanForInt(input, &currIndex, ',');
	currIndex += 2;
	currCarriagesQuantity = scanForInt(input, &currIndex, ',');
	currLocomotiveSpeed -= currCarriagesQuantity;
	currIndex += 3;
	allocMemoryForCarriagesInfo(&currCarriagesInfo, currCarriagesQuantity);
	fillCarriagesInfo(currCarriagesInfo, input, &currIndex);
	currIndex += 2;
	int pathLength = calcPathLength(input, currIndex);
	int* stationIndeces = readPath(input, pathLength, currIndex);
	currTrain = Train(currLocomotiveSpeed, currLocomotiveServiceTimeLeft, currCarriagesQuantity, currCarriagesInfo, stationIndeces, pathLength);
	trains[trainIndex] = currTrain;
}

void PlayArea::readTrainInfoUntilEOF(ifstream& input)
{
	string currLine;
	while (getline(input, currLine) && currLine != "")
	{
		fillTrainInfo(currLine);
	}
}

void PlayArea::allocMemoryForCarriagesInfo(bool*** carriagesInfo, int carriagesQuantity)
{
	*carriagesInfo = new bool* [carriagesQuantity];
	for (int i = 0; i < carriagesQuantity; i++)
	{
		(*carriagesInfo)[i] = new bool[2];
	}
}

void PlayArea::fillCarriagesInfo(bool** carriagesInfo, string input, int* startingIndexAddress)
{
	int currIndex = *startingIndexAddress;
	int currCarriageIndex = 0;
	while (input[currIndex] != ' ')
	{
		if (input[currIndex] == 'Y') carriagesInfo[currCarriageIndex][0] = true;
		else carriagesInfo[currCarriageIndex][0] = false;
		currIndex += 2;
		if (input[currIndex] == 'Y') carriagesInfo[currCarriageIndex][1] = true;
		else carriagesInfo[currCarriageIndex][1] = false;
		currIndex += 3;
		currCarriageIndex++;
	}
	*startingIndexAddress = currIndex;
}

int PlayArea::calcPathLength(string input, int startingIndex)
{
	int pathLength = 0;
	for (int i = startingIndex; input[i] != ')'; i++)
	{
		if (input[i] == ',') pathLength++;
	}
	return pathLength + 1;
}

int* PlayArea::readPath(string input, int pathLength, int startingIndex)
{
	int currIndex = startingIndex;
	int* stationIndeces = new int[pathLength];
	int currPathIndex = 0;
	char* limiters = new char[2];
	limiters[0] = ',';
	limiters[1] = ')';
	for (currIndex; currIndex < size(input) && input[currIndex] != ')'; currIndex++)
	{
		stationIndeces[currPathIndex++] = scanForInt(input, &currIndex, limiters, 2);
		currIndex++;
	}
	return stationIndeces;
}

bool PlayArea::directedLinkBetween(PlayAreaNode* node1, PlayAreaNode *node2)
{
	for (int currAdjacentNodeIndex = 0; currAdjacentNodeIndex < node1->adjacentQuantity; currAdjacentNodeIndex++)
	{
		if(node1->adjacent[currAdjacentNodeIndex]->id == node2->id) return true;
	}
	return false;
}

bool PlayArea::isCyclicPath(int* stationIndeces, int pathLength)
{
	for (int currStation = 0; currStation < pathLength - 1; currStation++)
	{
		if (!directedLinkBetween(stations[stationIndeces[currStation]], stations[stationIndeces[currStation + 1]])) return false;
	}
	if (!directedLinkBetween(stations[stationIndeces[pathLength - 1]], stations[stationIndeces[0]])) return false;
	return true;
}

int PlayArea::scanForInt(string input, int* startingIndexAddress, char limiter)
{
	string outputStr;
	while (*startingIndexAddress < size(input) && input[*startingIndexAddress] != limiter)
	{
		outputStr += input[(*startingIndexAddress)++];
	}
	return stoi(outputStr);
}

int PlayArea::scanForInt(string input, int* startingIndexAddress, char* limiters, int limitersQuantity)
{
	string outputStr;
	bool breakUpperCycle = false;
	while (*startingIndexAddress < size(input))
	{
		for (int i = 0; i < limitersQuantity; i++)
		{
			if (input[*startingIndexAddress] == limiters[i])
			{
				breakUpperCycle = true;
				break;
			}
		}
		if (breakUpperCycle) break;
		outputStr += input[(*startingIndexAddress)++];
	}
	return stoi(outputStr);
}

void PlayArea::allocMemoryForAdjacent(PlayAreaNode* station, int input)
{
	station->adjacent = new PlayAreaNode * [input];
	station->adjacentQuantity = input;
	station->weights = new int[input];
}

void PlayArea::setAdjacent(PlayAreaNode* station, string input, int startingIndex)
{
	int currAdjacentIndex = 0;
	for (int i = startingIndex; i < size(input); i++)
	{
		if (input[i] == ' ')
		{
			i++;
			station->adjacent[currAdjacentIndex] = stations[scanForInt(input, &i, '(')];
			i++;
			station->weights[currAdjacentIndex++] = scanForInt(input, &i, ')');
		}
	}
}

Locomotive::Locomotive()
{
	speed = 5;
	serviceTimeLeft = 100;
}

Locomotive::Locomotive(int speedInput, int serviceTimeLeftInput)
{
	speed = speedInput;
	serviceTimeLeft = serviceTimeLeftInput;
}

Carriage::Carriage()
{
	isCargoCarriage = false;
	isLoaded = false;
}

Carriage::Carriage(bool isCargoCarriageInput, bool isLoadedInput)
{
	isCargoCarriage = isCargoCarriageInput;
	isLoaded = isLoadedInput;
}

Train::Train()
{
	locomotive = Locomotive();
	carriages = new Carriage[1];
	carriages[0] = Carriage();
	carriagesQuantity = 1;
}

Train::Train(int locomotiveSpeed, int locomotiveServiceTimeLeft, int carriagesQuantity, bool** carriagesInfo, int* pathInput, int pathLengthInput)
{
	locomotive = Locomotive(locomotiveSpeed, locomotiveServiceTimeLeft);
	carriages = new Carriage[carriagesQuantity];
	(*this).carriagesQuantity = carriagesQuantity;
	for (int currCarriage = 0; currCarriage < carriagesQuantity; currCarriage++)
	{
		carriages[currCarriage] = Carriage(carriagesInfo[currCarriage][0], carriagesInfo[currCarriage][1]);
	}
	path = pathInput;
	pathLength = pathLengthInput;
}

void Train::setPath(int* input)
{
	path = input;
}

void Train::setPathLength(int input)
{
	pathLength = input;
}

PlayAreaNode** PlayArea::getStations() { return stations; }
Train* PlayArea::getTrains() { return trains; }
int PlayArea::getStationsQuantity() { return stationsQuantity; }
int PlayArea::getTrainsQuantity() { return trainsQuantity; }

Locomotive Train::getLocomotive() { return locomotive; }
Carriage* Train::getCarriages() { return carriages; }
int Train::getCarriagesQuantity() { return carriagesQuantity; }
int* Train::getPath() { return path; }
int Train::getPathLength() { return pathLength; }

int Locomotive::getSpeed() { return speed; }
int Locomotive::getServiceTimeLeft() { return serviceTimeLeft; }

bool Carriage::getIsCargo() { return isCargoCarriage; }
bool Carriage::getIsLoaded() { return isLoaded; }

void printPlayAreaCreationResult(PlayArea result)
{
	int stationsQuantity = result.getStationsQuantity();
	printf("=========================================================\n");
	printf("Created a play area graph with %d stations\n", stationsQuantity);
	printf("Defined by the following matrix:\n\n");
	PlayAreaNode** stations = result.getStations();
	printf("   ");
	for (int j = 0; j < 2; j++)
	{
		if (j == 1) printf("   ");
		for (int i = 0; i < stationsQuantity; i++)
		{
			if (j == 0) printf("%d ", i);
			if (j == 1)
			{
				if (i < stationsQuantity - 1) printf("__");
				else printf("_");
			}
		}
		printf("\n");
	}
	for (int i = 0; i < stationsQuantity; i++)
	{
		printf("%d |", i);
		for (int j = 0; j < stationsQuantity; j++)
		{
			if (result.directedLinkBetween(stations[i], stations[j]))
			{
				for (int currAdjNode = 0; currAdjNode < stations[i]->adjacentQuantity; currAdjNode++)
				{
					if (stations[i]->adjacent[currAdjNode]->id == stations[j]->id)
					{
						printf("%d ", stations[i]->weights[currAdjNode]);
						break;
					}
				}
			}
			else printf("0 ");
		}
		printf("\n");
	}
	printf("\n");
	printf("With the following trains:\n");
	Train* trains = result.getTrains();
	int trainQuantity = result.getTrainsQuantity();
	for (int i = 0; i < trainQuantity; i++)
	{
		int currCarriagesQuantity = trains[i].getCarriagesQuantity();
		int currPathLength = trains[i].getPathLength();
		int* currPath = trains[i].getPath();
		printf("------------------------------------\n");
		printf("Train %d\n", i);
		printf("Locomotive speed: %d\n", trains[i].getLocomotive().getSpeed());
		printf("Locomotive service time left: %d\n", trains[i].getLocomotive().getServiceTimeLeft());
		printf("Carriages: %d\n", currCarriagesQuantity);
		for (int j = 0; j < currCarriagesQuantity; j++)
		{
			printf("Carriage %d: ", j);
			if (trains[i].getCarriages()[j].getIsCargo()) printf("cargo carriage; ");
			else printf("passenger carriage; ");
			if (trains[i].getCarriages()[j].getIsLoaded()) printf("loaded\n");
			else printf("not loaded\n");
		}
		printf("Path: ");
		for (int j = 0; j < currPathLength; j++)
		{
			if (j > 0) printf("-");
			printf("%d", currPath[j]);
		}
		printf("\n");
	}
	printf("=========================================================\n");
}