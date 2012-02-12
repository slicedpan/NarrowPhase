#pragma once

#include <vector>
#define FIRSTOVERLAP 1
#define SECONDOVERLAP 2

class RigidBody;

struct BroadPhaseEntry
{
	int index;
	bool start;
	float value;
	RigidBody* body;
};

struct BroadPhasePair
{
	RigidBody* p1;
	RigidBody* p2;
};

class BroadPhase
{
public:
	BroadPhase(void);
	~BroadPhase(void);
	std::vector<RigidBody*> bodies;	
	std::vector<RigidBody*> newBodies;
	void GenerateCollisions();
	void AddBody(RigidBody* body);
	void SetAxisOrder(int firstAxis, int secondAxis, int thirdAxis)
	{
		first = firstAxis;
		second = secondAxis;
		third = thirdAxis;
	}
	std::vector<BroadPhasePair>& GetPairs() 
	{
		return pairs;
	}
private:
	unsigned char overlapBitMask[8];
	std::vector<BroadPhaseEntry> entries[3];
	std::vector<BroadPhasePair> pairs;	
	void GenerateEntries();
	void SortEntries();
	void AddEntries();
	void AddEntry(RigidBody* body, int index);
	void UpdateEntries();
	bool needsResync;
	int first;
	int second;
	int third;
	std::vector<int> indexActive;
	unsigned char* overlapMask;
	void ReallocateMask();
	int maxPairs;
	int maskByteSize;
	void SetMask(int index1, int index2, int pos)
	{		
		if (index1 > index2)
		{
			int i;
			i = index2;
			index2 = index1;
			index1 = i;
		}
		int flatIndex = index1 + index2 * bodies.size();
		int maskIndex = flatIndex % 4;
		flatIndex /= 4;
		*(overlapMask + flatIndex) |= overlapBitMask[(maskIndex * 2) + pos];	
	}
	bool CheckMask(int index1, int index2, int pos)
	{
		if (index1 > index2)
		{
			int i;
			i = index2;
			index2 = index1;
			index1 = i;
		}
		int flatIndex = index1 + index2 * bodies.size();
		int maskIndex = flatIndex % 4;
		flatIndex /= 4;
		return *(overlapMask + flatIndex) & overlapBitMask[(maskIndex * 2) + pos];
	}

};



