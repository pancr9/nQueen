// nQueenSingleDimension.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>							//cin, cout
#include <time.h>							// clock
#include <stdlib.h>							// srand, rand
using namespace std;
int currentConflict = 0;					//Initialize #current conflicts to zero
int restarts = 0;							//Counter to count #restarts
int steps = 0;								//Counter to count hill climbing steps from Initial Random State
int actualSteps = 0;
int temp;									//Counter to calculate values
int minConflictHeuristic;					//Counter for minimum heuristics
int maxelements;						//Max Elements for interations
class nQueen
{
public:
	bool isSolution;						//Checks if reached state is a solution by Hill Climbing	
	bool isSolved;							//Checks if reached state is a solution by Minimum Conflicts Algorithm
	int n;									//n is the problem size
	int tempConflicts;						//Accounts for Direct & Indirect Conflicts for a temporary state
	int* state;								//Array to store location of Queen
	int bestCol, bestRow;					//Stores value of best possible next state row and column values
	int currentConflict, bestConflict;		//Stores value of currentConflicts & best Possible conflict
	int currentRow, currentCol;				//Stores values of row and column for current state
	int calcConflicts(int[]);				//Function to calculate conflicts for a state
	void start();							//Function to start processing of nQueen Problem
	void displayState();					//Function to display a state on screen
	void randomState();						//Function to generate a random state
	void hillClimbing();					//Calculates heuristic value for every possible state	
	void minConflicts();					//Function to evaluate minimum conflicts
};
void nQueen::start()
{
	std::cout << "Value of n: "; cin >> n; cout << endl;
	if (cin.fail())
	{
		std::cout << "Please enter integer only & try again. Thanks!" << endl;
		exit(0);
	}
	else if (n < 4)
	{
		std::cout << " No possible solution. Please try again for n > 4.";
		exit(0);
	}
	std::cout << "Processing.............................................." << endl;
	state = new int[n];								//Creating an array of size n
	isSolution = false;								//Indicates solution not found (Initial Value)
	isSolved = false;
	hillClimbing();									//Start Hill Climbing
	restarts = 0;
	minConflicts();									//Minimum Conflicts Algorithm
}
void nQueen::randomState()
{
	for (int i = 0; i < n; i++)
		state[i] = (rand() % n);
}
void nQueen::displayState()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << " ";
			if (j != state[i])
				cout << " _ ";
			else
				cout << " Q ";
		}
		cout << endl;
	}
}
void nQueen::hillClimbing()
{
	cout << "Hill Climbing Solution" << endl;
	while (!isSolution)
	{
		actualSteps = 0;
		randomState();
		currentConflict = calcConflicts(state);
		if (currentConflict == 0)			//Checks if current state is the solution
			isSolution = true;
		while (currentConflict > 0)			//Indicates conflicts exists
		{
			steps = steps + 1;				//Incrementing number of states required to reach solution 
			actualSteps = actualSteps + 1;
			bestConflict = currentConflict;
			for (int i = 0; i < n; i++)		//Check for every row
			{	
				currentRow = state[i];		//Stores acutal position of Queen in current row
				for (int j = 0; j < n; j++)	//Check for every element columnwise for a row
				{
					if (state[i] != j)		//Check conflicts only if position is not occupied by a Queen
					{
						state[i] = j;		//Temporary change of Queens' position
						tempConflicts = calcConflicts(state);
						if (tempConflicts < bestConflict)
						{					//updating bestSuccessor
							bestConflict = tempConflicts;
							bestRow = j;
							bestCol = i;
						}
						state[i] = currentRow;	//Obtaining actual Queens' position back
					}
				}
			}								//At end of this for loop, best Successor is obtained
			if (bestConflict == currentConflict) //To avoid local maxima condition
			{
				restarts = restarts + 1;
				cout << "Restart Number: " << restarts << endl;
				break;						//Random Restart initiated
			}
			else							//Store value of bestRow into state and update currentConflict value
			{
				state[bestCol] = bestRow;
				currentConflict = bestConflict;
			}
			if (bestConflict == 0)	//Solution found
			{
				isSolution = true;			//To move out of outer while loop
				cout << "Number of total state changes: " << steps << endl;
				cout << "Number of steps required from new random state: " << actualSteps << endl;
				cout << "Solution is: " << endl;
				displayState();				//Display Solution
				break;
			}
		}
	}
}
int nQueen::calcConflicts(int a[])
{
	temp = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if ((a[i] == a[j]) || (abs(i - j) == abs(a[i] - a[j])))		//Calulates conflicts caused due Direct and Indirect contact
				temp++;
		}
	}
	return temp;
}
void nQueen::minConflicts()
{
	cout << "Minimum Conflicts solution" << endl;
	while (!isSolved)
	{
		maxelements = 100;
		randomState();
		currentConflict = calcConflicts(state);
		if (currentConflict == 0)			//Checks if current state is the solution
			isSolved = true;

		while (currentConflict > 0)			//Indicates conflicts exists
		{
			bestConflict = currentConflict;
			{
				currentRow = rand() % n;
				
				//cout << "Max = " << maxelements << endl;
				currentCol = state[currentRow];//Displays position of Queen of currentRow
				for (int j = 0; j < n; j++)
				{
					state[currentRow] = j;
					tempConflicts = calcConflicts(state);
					if (tempConflicts <= bestConflict)
					{					//updating bestSuccessor
						bestConflict = tempConflicts;
						bestRow = j;
						bestCol = currentRow;
					}
				}
			}
				if (maxelements <1) //To confirm max iterations are performed.
				{
					restarts = restarts + 1;
					cout << "Restart Number: " << restarts << endl;
					break;						//Random Restart initiated
				}
				else							//Store value of bestRow into state and update currentConflict value
				{
					state[bestCol] = bestRow;
					currentConflict = bestConflict;
					maxelements--;
				}
				if (bestConflict == 0)	//Solution found
				{
					isSolved = true;			//To move out of outer while loop
					cout << "Solution is: " << endl;
					displayState();				//Display Solution
					break;
				}
			}
		}
	}



int main()
{
	clock_t start, finish, total;
	start = clock();
	srand(time(NULL));						//To generate random time seeds
	nQueen r;	
	r.start();
	delete[] r.state;						//Deletion of dynamic array				
	finish = clock();
	total = finish - start;
	cout << "Time taken: " << total << " msecs" << endl;
	system("pause");
	return 0;
}

