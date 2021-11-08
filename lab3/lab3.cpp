#include "lab3header.h"

using namespace std;

int main()
{
	printf("This program will take information from an input file and model a game world with trains and stations and stuff.\n");
	printf("The stations and connections between them are represented as a weighted oriented graph, where the weights represent the distance between the stations.\n");
	printf("Each station in the game area has a type - cargo, passenger, or mixed.\n");
	printf("The trains will travel in a cyclic way in a specified route (each in their own route, though you can make the trains travel in identical routes).\n");
	printf("Each train starts off at the first station of its path with some base speed, service time and carriages.\n");
	printf("The carriages on the trains can be either cargo or passenger carriages. They can be loaded or unloaded from the start.\n");
	printf("Each empty carriage lowers the train speed by 1, and each loaded carriage lowers the train speed by 2.\n");
	printf("If the speed of a train falls to 0 or lower, it won't be able to move.\n");
	printf("You can load and unload the carriages of the trains or send them to the next station in their route.\n");
	printf("The trains' carriages can only be unloaded while the train is at a stop at a station of corresponding type.\n");
	printf("With each game turn, the service time left of every moving train will be reduced by its speed. If the service time left falls below 0, the train will break down and you won't be able to move it anymore.\n\n\n");

	printf("The first line of the input file should be the number of stations in your play area.\n");
	printf("The following lines should describe the stations themselves. The format is the following:\n\n");
	printf("station_index(number_of_adjacent, station_type): adjacent_station(weight), adjacent_station(weight), ...\n\n");
	printf("Please stick to the format shown above, down to the spaces.\n");
	printf("You can omit some stations and not describe them, for example, say that there are 4 stations and only describe 3. Omitted stations will still be in the play area, though they won't be connected to any other station.\n");
	printf("The station info section should be ended by an arbitrary number of underscores. No, 0 won't do it. Neither will 1.5. Bitter truth.\n");
	printf("Then comes the train info section. The format is the following:\n\n");
	printf("train_index: speed, starting_service_time, carriages_quantity, (Y/N, N/N, ...), (station, station, ...)\n\n");
	printf("The Y/N stuff in the first parentheses stands for carriage info: the first letter tells whether the i-th carriage is a cargo carriage (if not, then it's a passenger carriage), the second letter - whether or nor it is loaded on game start\n");
	printf("The station indeces in the second parentheses represent the path that the train will travel in a cyclic way. Note that if you specify a non-cyclic path (based on the station info provided before), it won't work.\n");
	printf("Also note that you need to describe all the trains - if you say that there will be 3 trains, please describe exactly 3. Their indeces may not be in succession (as well as the stations, by the way), but they all need to be there.\n");
	printf("Wrapped up, here's an example of a correct input file:\n\n");
	printf("3\n0(1, 1): 2(3)\n1(2, 2): 0(6), 2(10)\n2(1, 0): 0(15)\n___\n1\n0: 5, 150, 2, (Y/Y, N/Y), (0, 2)\n\n");
	printf("Input file path: ");
	string filePath;
	cin >> filePath;
	PlayArea playArea;
	try 
	{
		playArea = PlayArea(filePath);
	}
	catch (string errorText)
	{
		cout << errorText;
		return 0;
	}
	printPlayAreaCreationResult(playArea);
	int choice = -1;
	while (true)
	{
		printf("\nWhat would you like to do?\n");
		printf("1. Show current play area state\n");
		printf("2. Show train info\n");
		printf("3. Send/load/unload a train (trains)\n");
		printf("4. Continue to the next turn\n");
		printf("5. End game (why would you even choose this, this gameplay is fire)\n");
		cin >> choice;
		printf("\n");
		switch (choice)
		{
		case 1:
		{
			playArea.printPlayAreaState();
			break;
		}
		case 2:
		{
			int trainIndex;
			printf("Info on which train do you want to see?\n");
			cin >> trainIndex;
			playArea.getTrains()[trainIndex].printInfo();
			break;
		}
		case 3:
		{
			Train* trains = playArea.getTrains();
			char moreChanges;
			do
			{
				int editingTrainIndex;
				printf("Which train would you like to send to the next station/load/unload?\n");
				cin >> editingTrainIndex;
				if (editingTrainIndex > playArea.getTrainsQuantity() - 1)
				{
					printf("Such a train doesn't exist in this timeline. Seek an Einstein-Rosen bridge.\n");
					break;
				}
				if (trains[editingTrainIndex].isBroken())
				{
					printf("This train is broken and can't move.\n");
					break;
				}
				printf("\nWhat would you like to do with train %d?\n", editingTrainIndex);
				printf("1. Send to the next station\n");
				printf("2. Load\n");
				printf("3. Unload\n");
				printf("4. I changed my mind, this train is the embodiment of perfection and I would never do something as horrendously inappropriate and flatout stupid as change its characteristics\n");
				cin >> choice;
				printf("\n");
				switch (choice)
				{
				case 1:
				{
					if (trains[editingTrainIndex].isEnRoute())
					{
						printf("It's already en route to its next station. Did you think you could make it go faster? He's doing his best, show some respect. \n");
					}
					else
					{
						if (trains[editingTrainIndex].getLocomotive().getSpeed() <= 0)
						{
							printf("This train is overloaded and can't move. Consider unloading some of its carriages.\n");
						}
						else
						{
							playArea.sendTrain(editingTrainIndex);
							printf("Train now en route to its next destination. Toot-toot!\n");
						}
					}
					break;
				}
				case 2:
				{
					if (trains[editingTrainIndex].isEnRoute())
					{
						printf("This train is en route to its next station. You can't load it. Duh.\n");
					}
					else
					{
						trains[editingTrainIndex].load();
						printf("Empty carriages correlating with station type were loaded.\n");
					}
					break;
				}
				case 3:
				{
					if (trains[editingTrainIndex].isEnRoute())
					{
						printf("This train is en route to its next station. You can't unload it. Duh.\n");
					}
					else
					{
						trains[editingTrainIndex].unload();
						printf("Loaded carriages correlating with station type were unloaded.\n");
					}
					break;
				}
				default:
				{
					break;
				}
				}
				printf("Would you like to do anything else? Y/N: ");
				cin >> moreChanges;
			} 			
			while (moreChanges == 'Y' || moreChanges == 'y');
			break;
		}
		case 4:
		{
			playArea.nextTurn();
			break;
		}
		default:
		{
			return 0;
		}
		}
	}
	return 0;
}