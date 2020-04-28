#ifndef HSCORES_H
#define HSCORES_H

#include <string>
#include <vector>

using namespace std;
namespace scrs
{
#pragma region vars
	extern enum order
	{
		lowerToHigher,
		higherToLower,
		alphabetical,
		noOrder,
	};
	extern struct score
	{
		string name;
		float value;
	};

#pragma endregion Variables

#pragma region funcs

	//Sets the lists order. The list updates to be in correct order every set/add/insert/modify function
	void setScoresOrder(order orderToArrange);
	//Adds a score to the end of the list
	void addScore(string name, float value);
	void addScore(score newScore);
	void addScore(string playerName);
	void addScore(float value);
	//Inserts a score in a specific position of the list
	void insertScore(int pos, string playerName, float value);
	void insertScore(int pos, string playerName);
	void insertScore(int pos, float value);
	//Returns list order.
	order getScoresOrder();
	//Returns a score in a specific position of the list
	score getScore(int position);
	float getScoreValue(int position);
	string getScoreName(int position);
	//Returns a score with a specific name
	float getScoreValueFromName(string name);
	//Returns the size of the list
	int getScoreCount();
	//Returns a copy of the list
	vector<score> getScoresListCopy();
	//Returns a copy of the list with specific order. This will not modify the original list.
	vector<score> getScoresListCopy(order orderToArrange);
	//Deletes and returns a score in a specific position of the list
	score extractScoreInPos(int pos);
	//Deletes and returns a score with a specific name
	score extractScoreWithName(string name);
	//Modifies a score in a specific position of the list
	void modifyScoreInPos(int pos, string newName, float newVal);
	void modifyScoreInPos(int pos, float newVal);
	void modifyScoreInPos(int pos, string newName);
	//Modifies a score with a specific name
	void modifyScoreWithName(string currentName, string newName, float newVal);
	void modifyScoreWithName(string currentName, float newVal);
	void modifyScoreWithName(string currentName, string newName);
	//Resets the list
	void clearScores();

#pragma endregion Functions
}

#endif //HSCORES_H

