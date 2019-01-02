#pragma once
#include <list>
using namespace std;

class Observer
{
public:
	Observer();
	~Observer();
	virtual void update(string massage) = 0;
	virtual void update() = 0;
};





