#include "lab3header.h"

using namespace std;

int main()
{
	string filePath;
	printf("Specify file path: ");
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
		printf("4. Leave everything as-is and continue to the next turn\n");
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
						playArea.sendTrain(editingTrainIndex);
						printf("Train now en route to its next destination. ");
					}
					break;
				}
				case 2:
				{
					if (trains[editingTrainIndex].isEnRoute())
					{
						printf("This train is en route to its next station. You can't load it. Duh. \n");
					}
					else
					{
						trains[editingTrainIndex].load();
						printf("Empty carriages correlating with station type were loaded. \n");
					}
					break;
				}
				case 3:
				{
					if (trains[editingTrainIndex].isEnRoute())
					{
						printf("This train is en route to its next station. You can't unload it. Duh. \n");
					}
					else
					{
						trains[editingTrainIndex].unload();
						printf("Loaded carriages correlating with station type were unloaded. \n");
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
			} 			while (moreChanges == 'Y' || moreChanges == 'y');
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