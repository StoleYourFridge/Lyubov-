#include "lab3header.h"

using namespace std;

PlayArea::PlayArea() {}

PlayArea::PlayArea(string inputFilePath)
{
	fillPlayAreaFromFile(inputFilePath);
}

void PlayArea::fillPlayAreaFromFile(string filePath)
{
	try 
	{
		ifstream input;
		input.open(filePath);
		fillStationsInfo(input);
		fillTrainsInfo(input);
	}
	catch (string errorText)
	{
		throw errorText;
	}
}

void PlayArea::fillStationsInfo(ifstream& input)
{
	try
	{
		string currLine;
		getline(input, currLine);
		stationsQuantity = stoi(currLine);
		stations = new PlayAreaNode * [stationsQuantity];
		for (int i = 0; i < stationsQuantity; i++) stations[i] = new PlayAreaNode;
		readStationInfoUntilUnderscore(input);
		for (int i = 0; i < stationsQuantity; i++) stations[i]->id = i;
	}
	catch (...)
	{
		string errorText = "Whoops! It seems like something went wrong while reading stations information. Please check input file correctness.\n\n";
		throw errorText;
	}
}
void PlayArea::fillStationInfo(string input)
{
	try
	{
		int currIndex = 0;
		int stationIndex = scanForInt(input, &currIndex, '(');
		currIndex++;
		allocMemoryForAdjacent(stations[stationIndex], scanForInt(input, &currIndex, ','));
		currIndex += 2;
		int currStationType = scanForInt(input, &currIndex, ')');
		currIndex += 2;
		setAdjacent(stations[stationIndex], input, currIndex);
		stations[stationIndex]->type = currStationType;
	}
	catch (...)
	{
		throw;
	}
}
void PlayArea::readStationInfoUntilUnderscore(ifstream& input)
{
	try
	{
		string currLine;
		getline(input, currLine);
		while (currLine[0] != '_')
		{
			fillStationInfo(currLine);
			getline(input, currLine);
		}
	}
	catch (...)
	{
		throw;
	}
}

void PlayArea::fillTrainsInfo(ifstream& input)
{
	try
	{
		string currLine;
		getline(input, currLine);
		trainsQuantity = stoi(currLine);
		trains = new Train[trainsQuantity];
		readTrainInfoUntilEOF(input);
	}
	catch (...)
	{
		string errorText = "Whoops! It seems like something went wrong while reading trains information. Please check input file correctness.\n\n";
		throw errorText;
	}
}
void PlayArea::fillTrainInfo(string input)
{
	try
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
		if (currLocomotiveSpeed <= 0) throw;
		currIndex += 3;
		allocMemoryForCarriagesInfo(&currCarriagesInfo, currCarriagesQuantity);
		fillCarriagesInfo(currCarriagesInfo, input, &currIndex);
		currIndex += 2;
		int pathLength = calcPathLength(input, currIndex);
		int* stationIndeces = readPath(input, pathLength, currIndex);
		if (!isCyclicPath(stationIndeces, pathLength)) throw;
		currTrain = Train(currLocomotiveSpeed, currLocomotiveServiceTimeLeft, currCarriagesQuantity, currCarriagesInfo, stationIndeces, pathLength);
		currTrain.setCurrStation(stationIndeces[0]);
		currTrain.setCurrStationType(stations[stationIndeces[0]]->type);
		if (pathLength > 1)
		{
			currTrain.setCurrDestination(stationIndeces[1]);
			currTrain.setCurrDistanceToDestination(getLinkWeight(stationIndeces[0], stationIndeces[1]));
		}
		else
		{
			currTrain.setCurrDestination(stationIndeces[0]);
			currTrain.setCurrDistanceToDestination(getLinkWeight(stationIndeces[0], stationIndeces[0]));
		}
		trains[trainIndex] = currTrain;
	}
	catch (...)
	{
		throw;
	}
}
void PlayArea::readTrainInfoUntilEOF(ifstream& input)
{
	try
	{
		string currLine;
		while (getline(input, currLine) && currLine != "")
		{
			fillTrainInfo(currLine);
		}
	}
	catch (...)
	{
		throw;
	}
}
void PlayArea::allocMemoryForCarriagesInfo(bool*** carriagesInfo, int carriagesQuantity)
{
	try
	{
		*carriagesInfo = new bool* [carriagesQuantity];
		for (int i = 0; i < carriagesQuantity; i++)
		{
			(*carriagesInfo)[i] = new bool[2];
		}
	}
	catch (...)
	{
		throw;
	}
}
void PlayArea::fillCarriagesInfo(bool** carriagesInfo, string input, int* startingIndexAddress)
{
	try
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
	catch (...)
	{
		throw;
	}
}
int PlayArea::calcPathLength(string input, int startingIndex)
{
	try
	{
		int pathLength = 0;
		for (int i = startingIndex; input[i] != ')'; i++)
		{
			if (input[i] == ',') pathLength++;
		}
		return pathLength + 1;
	}
	catch (...)
	{
		throw;
	}
}
int* PlayArea::readPath(string input, int pathLength, int startingIndex)
{
	try
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
	catch (...)
	{
		throw;
	}
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
int PlayArea::getLinkWeight(int from, int to)
{
	for (int currAdjacentIndex = 0; currAdjacentIndex < stations[from]->adjacentQuantity; currAdjacentIndex++)
	{
		if (stations[from]->adjacent[currAdjacentIndex]->id == to) return stations[from]->weights[currAdjacentIndex];
	}
}


Carriage::Carriage()
{
	cargoCarriage = false;
	loaded = false;
}
Carriage::Carriage(bool isCargoCarriageInput, bool isLoadedInput)
{
	cargoCarriage = isCargoCarriageInput;
	loaded = isLoadedInput;
}

void Carriage::load() {loaded = true; }
void Carriage::unload() { loaded = false; }

bool Carriage::isCargo() { return cargoCarriage; }
bool Carriage::isLoaded() { return loaded; }


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

void Locomotive::reduceServiceTimeLeftBy(int input) { serviceTimeLeft -= input; }

int Locomotive::getSpeed() { return speed; }
int Locomotive::getServiceTimeLeft() { return serviceTimeLeft; }


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
void Train::setPathLength(int input) { pathLength = input; }
void Train::setEnRoute(bool input) { enRoute = input; }
void Train::setCurrStation(int input) { currStation = input; }
void Train::setCurrStationType(int input) { currStationType = input; }
void Train::setCurrDestination(int input) { currDestination = input; }
void Train::setCurrDistanceToDestination(int input) { currDistanceToDestination = input; }
void Train::send() { enRoute = true; }
void Train::stop() 
{ 
	enRoute = false;
	currStation = currDestination;
	currStationInPathIndex = (currStationInPathIndex % pathLength);
	currDestination = path[(currStationInPathIndex + 1) % pathLength];
}
void Train::load()
{
	int stationType = getCurrStationType();
	for (int i = 0; i < carriagesQuantity; i++) 
	{
		if (carriages[i].isCargo() && !carriages[i].isLoaded() && (stationType != 0)) carriages[i].load();
		if (!carriages[i].isCargo() && !carriages[i].isLoaded() && (stationType != 1)) carriages[i].load();
	}
}
void Train::unload()
{
	int stationType = getCurrStationType();
	for (int i = 0; i < carriagesQuantity; i++)
	{
		if (carriages[i].isCargo() && carriages[i].isLoaded() && (stationType != 0)) carriages[i].unload();
		if (!carriages[i].isCargo() && carriages[i].isLoaded() && (stationType != 1)) carriages[i].unload();
	}
}
void Train::disintegrate() { broken = true; }

Locomotive Train::getLocomotive() { return locomotive; }
Carriage* Train::getCarriages() { return carriages; }
int Train::getCarriagesQuantity() { return carriagesQuantity; }
int* Train::getPath() { return path; }
int Train::getPathLength() { return pathLength; }
bool Train::isEnRoute() { return enRoute; }
int Train::getCurrStation() { return currStation; }
int Train::getCurrStationType() { return currStationType; }
int Train::getCurrDestination() { return currDestination; }
int Train::getCurrDistanceToDestination() { return currDistanceToDestination; }
int Train::turnsLeftToDestination()
{
	int speed = getLocomotive().getSpeed();
	int distanceLeft = getCurrDistanceToDestination();
	int timeLeft = distanceLeft / speed;
	if (distanceLeft % speed != 0) timeLeft++;
	return timeLeft;
}

void Train::printInfo()
{
	printf("\n");
	if (isEnRoute()) printf("Currently en route to station %d\n", currDestination);
	else printf("Currently waiting at station %d; next destination - station %d\n", currStation, currDestination);
	printf("Locomotive speed: %d\n", getLocomotive().getSpeed());
	printf("Locomotive service time left: %d\n", getLocomotive().getServiceTimeLeft());
	printf("%d carriages\n", carriagesQuantity);
	for (int i = 0; i < carriagesQuantity; i++)
	{
		printf("Carriage %d: ", i);
		if (carriages[i].isCargo()) printf("cargo; ");
		else printf("passenger; ");
		if (carriages[i].isLoaded()) printf("loaded\n");
		else printf("unloaded\n");
	}
}


PlayAreaNode** PlayArea::getStations() { return stations; }
Train* PlayArea::getTrains() { return trains; }
int PlayArea::getStationsQuantity() { return stationsQuantity; }
int PlayArea::getTrainsQuantity() { return trainsQuantity; }
void PlayArea::sendTrain(int trainIndex)
{
	Train train = trains[trainIndex];
	train.send();
}
void PlayArea::stopTrain(int trainIndex)
{
	Train train = trains[trainIndex];
	train.stop();
	train.setCurrStationType(stations[train.getCurrStation()]->type);
	train.setCurrDistanceToDestination(getLinkWeight(train.getCurrStation(), train.getCurrDestination()));
}
void PlayArea::nextTurn()
{
	Train currTrain;
	Locomotive currLocomotive;
	int speed;
	for (int i = 0; i < trainsQuantity; i++)
	{
		currTrain = trains[i];
		currLocomotive = currTrain.getLocomotive();
		speed = currLocomotive.getSpeed();
		if (currTrain.isEnRoute())
		{
			currTrain.setCurrDistanceToDestination(currTrain.getCurrDistanceToDestination() - speed);
			currLocomotive.reduceServiceTimeLeftBy(currTrain.getCarriagesQuantity());
			if (currLocomotive.getServiceTimeLeft() < 0)
			{
				currTrain.disintegrate();
				continue;
			}
			if (currTrain.getCurrDistanceToDestination() <= 0)
			{
				stopTrain(i);
			}
		}
	}
}

void PlayArea::printPlayAreaState()
{
	printf("\n\n");
	for (int i = 0; i < trainsQuantity; i++)
	{
		printf("Train %d is ", i);
		if (trains[i].isEnRoute()) printf("en route to station %d; %d turns left", trains[i].getCurrDestination(), trains[i].turnsLeftToDestination());
		else printf("waiting at station %d; next stop - station %d", trains[i].getCurrStation(), trains[i].getCurrDestination());
		printf("\n");
	}
	printf("\n\n");
}

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
	for (int i = 0; i < stationsQuantity; i++)
	{
		printf("Station %d - ", i);
		switch (stations[i]->type)
		{
		case 0:
		{
			printf("passenger");
			break;
		}
		case 1:
		{
			printf("cargo");
			break;
		}
		case 2:
		{
			printf("passenger/cargo");
			break;
		}
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
			if (trains[i].getCarriages()[j].isCargo()) printf("cargo carriage; ");
			else printf("passenger carriage; ");
			if (trains[i].getCarriages()[j].isLoaded()) printf("loaded\n");
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