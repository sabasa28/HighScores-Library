#include "HScores.h"

#include "pch.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

namespace scrs
{
	enum order
	{
		lowerToHigher,
		higherToLower,
		alphabetical,
		noOrder,
	};

	struct score
	{
		string name = "Player ";
		float value = 0;
	};

	static order listOrder = order::noOrder;
	score error = { "Not Found in list", -1};
	static vector<score> scores;

	static void updateList(vector<score>&list)
	{
		switch (listOrder)
		{
		case order::lowerToHigher:
			for (int i = 0; i < list.size(); i++)
			{
				int lowest = i;
				score aux;
				for (int j = i+1; j < list.size(); j++)
				{
					if (list[j].value < list[lowest].value) lowest = j;
				}
				aux = list[i];
				list[i] = list[lowest];
				list[lowest] = aux;
			}
			break;
		case order::higherToLower:
			for (int i = 0; i < list.size(); i++)
			{
				int highest = i;
				score aux;
				for (int j = i + 1; j < list.size(); j++)
				{
					if (list[j].value > list[highest].value) highest = j;
				}
				aux = list[i];
				list[i] = list[highest];
				list[highest] = aux;
			}
			break;
		case order::alphabetical:
			for (int i = 0; i < list.size(); i++)
			{
				int lowest = i;
				score aux;
				for (int j = i + 1; j < list.size(); j++)
				{
					bool asigned = false;
					int letterCompared = 0;
					while (!asigned)
					{
						if (letterCompared< list[j].name.size() && letterCompared < list[lowest].name.size())
						{
							if (list[j].name[letterCompared]== list[lowest].name[letterCompared])
							{
								letterCompared++;
							}
							else
							{
								asigned = true;
							}
						}
						else
						{
							asigned = true;
						}
					}
					if (list[j].name[letterCompared] < list[lowest].name[letterCompared]) lowest = j;
				}
				aux = list[i];
				list[i] = list[lowest];
				list[lowest] = aux;
			}
			break;
		case order::noOrder:
			break;
		}
	}

	void setScoresOrder(order orderToArrange)
	{
		listOrder = orderToArrange;
		updateList(scores);
	}

	void addScore(string name, float value)
	{
		scores.resize(scores.size() + 1);
		scores[scores.size() - 1].name = name;
		scores[scores.size() - 1].value = value;
		updateList(scores);
	}

	void addScore(score newScore)
	{
		scores.resize(scores.size() + 1);
		scores[scores.size() - 1] = newScore;
		updateList(scores);
	}

	void addScore(string playerName)
	{
		scores.resize(scores.size() + 1);
		scores[scores.size() - 1].name = playerName;
		updateList(scores);
	}

	void addScore(float value)
	{
		scores.resize(scores.size() + 1);
		scores[scores.size() - 1].name = "Player " + to_string(scores.size());
		scores[scores.size() - 1].value = value;
		updateList(scores);
	}

	void insertScore(int pos, string playerName, float value)
	{
		if (pos >= 0 && pos <scores.size())
		{	
			scores.resize(scores.size() + 1);
			for (int i = scores.size()-1; i > pos; i--)
			{
				scores[i] = scores[i - 1];
			}
			scores[pos] = { playerName,value };
			updateList(scores);
		}
	}

	void insertScore(int pos, string playerName)
	{
		if (pos >= 0 && pos < scores.size())
		{
			scores.resize(scores.size() + 1);
			for (int i = scores.size() - 1; i > pos; i--)
			{
				scores[i] = scores[i - 1];
			}
			scores[pos].name = playerName;
			updateList(scores);
		}
	}

	void insertScore(int pos, float value)
	{
		if (pos >= 0 && pos < scores.size())
		{
			scores.resize(scores.size() + 1);
			for (int i = scores.size() - 1; i > pos; i--)
			{
				scores[i] = scores[i - 1];
			}
			scores[pos] = { "Player " + to_string(scores.size()), value};
			updateList(scores);
		}
	}

	order getScoresOrder()
	{
		return listOrder;
	}

	score getScore(int position) 
	{
		if (position < scores.size() && position >= 0)
		{
			return scores[position];
		}
		return error;
	}

	float getScoreValue(int position)
	{
		if (position < scores.size() && position >= 0)
		{
			return scores[position].value;
		}
		return error.value;
	}

	string getScoreName(int position)
	{
		if (position < scores.size() && position >= 0)
		{
			return scores[position].name;
		}
		return error.name;
	}

	float getScoreValueFromName(string name)
	{
		for (int i = 0; i < scores.size(); i++)
		{
			if (scores[i].name==name)
			{
				return scores[i].value;
			}
		}
		return error.value;
	}

	int getScoreCount()
	{
		return scores.size();
	}

	vector<score> getScoresListCopy()
	{
		return scores;
	}

	vector<score> getScoresListCopy(order orderToArrange)
	{
		vector<score>copy = scores;
		order aux = listOrder;
		listOrder = orderToArrange;
		updateList(copy);
		listOrder = aux;
		return copy;
	}

	score extractScoreInPos(int pos)
	{
		if (pos >= scores.size()||pos<0)
		{
			return error;
		}
		score extracted = scores[pos];
		for (int i = pos; i < scores.size() -1; i++)
		{
			scores[i] = scores[i + 1];
		}
		scores.resize(scores.size() - 1);
		return extracted;
	}

	score extractScoreWithName(string name)
	{
		int extractedIndx = -1;
		score extracted = error;
		for (int i = 0; i < scores.size(); i++)
		{
			if (scores[i].name==name)
			{
				extractedIndx = i;
				extracted = scores[extractedIndx];
			}
		}
		if (extractedIndx == -1)
		{
			return extracted;
		}
		for (int i = extractedIndx; i < scores.size() - 1; i++)
		{
			scores[i] = scores[i + 1];
		}
		scores.resize(scores.size() - 1);
		return extracted;
	}

	void modifyScoreInPos(int pos, string newName, float newVal)
	{
		if (pos >= 0 && pos < scores.size())
		{
			scores[pos].name = newName;
			scores[pos].value = newVal;
			updateList(scores);
		}
	}

	void modifyScoreInPos(int pos, float newVal)
	{
		if (pos >= 0 && pos < scores.size())
		{
			scores[pos].value = newVal;
			updateList(scores);
		}
	}

	void modifyScoreInPos(int pos, string newName)
	{
		if (pos >= 0 && pos < scores.size())
		{
			scores[pos].name = newName;
			updateList(scores);
		}
	}

	void modifyScoreWithName(string currentName, string newName, float newVal)
	{
		for (int i = 0; i < scores.size(); i++)
		{
			if (scores[i].name == currentName)
			{
				scores[i].name = newName;
				scores[i].value = newVal;
			}
		}
		updateList(scores);
	}

	void modifyScoreWithName(string currentName, float newVal)
	{
		for (int i = 0; i < scores.size(); i++)
		{
			if (scores[i].name == currentName)
			{
				scores[i].value = newVal;
			}
		}
		updateList(scores);
	}

	void modifyScoreWithName(string currentName, string newName)
	{
		for (int i = 0; i < scores.size(); i++)
		{
			if (scores[i].name == currentName)
			{
				scores[i].name = newName;
			}
		}
		updateList(scores);
	}

	void clearScores()
	{
		scores.resize(0);
	}

}