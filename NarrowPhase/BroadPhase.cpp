#include "BroadPhase.h"
#include "RigidBody.h"
#include "AABB.h"
#include <algorithm>

bool EntrySortFunc(BroadPhaseEntry& entry1, BroadPhaseEntry& entry2)
{
	return entry1.value < entry2.value;
}

BroadPhase::BroadPhase(void) : needsResync(false)
{
	first = 0;
	second = 1;
	third = 2;
	overlapMask = (unsigned char*)malloc(sizeof(unsigned char) * 2500);
	for (int i = 0; i < 8; ++i)
	{
		overlapBitMask[i] = 1 << i;
	}
	maxPairs = 10000;	
	maskByteSize = 2500;
}

BroadPhase::~BroadPhase(void)
{
}

void BroadPhase::ReallocateMask()
{
	maskByteSize *= 2;
	realloc(overlapMask, sizeof(unsigned char) * maskByteSize);
	maxPairs = maskByteSize * 4;
}

void BroadPhase::GenerateCollisions()
{	
 	int numPairs = bodies.size() * bodies.size();
	memset(overlapMask, 0, sizeof(unsigned char) * maskByteSize);
	pairs.clear();
	if (numPairs > maxPairs)
		ReallocateMask();

	if (bodies.size() * 2 < entries[0].size())
	{
		GenerateEntries();
	}
	else if(newBodies.size() > 0)
	{
		UpdateEntries();
		AddEntries();	//this way the newly added entries won't get updated since they will already be up to date
	}
	else
	{
		UpdateEntries();
	}
	SortEntries();

	indexActive.clear();
	
	for (int i = 0; i < entries[first].size(); ++i)
	{
		if (entries[first][i].start)
		{
			indexActive.push_back(entries[first][i].index);
			for (int j = 0; j < indexActive.size() - 1; ++j)
			{
				SetMask(entries[first][i].index, indexActive[j], 0);								
			}
		}
		else
		{
			for (int j = 0; j < indexActive.size(); ++j)
			{
				if (indexActive[j] == entries[first][i].index)
					indexActive.erase(indexActive.begin() + j);
			}
		}
	}

	for (int i = 0; i < entries[second].size(); ++i)
	{
		if (entries[second][i].start)
		{
			indexActive.push_back(entries[second][i].index);
			for (int j = 0; j < indexActive.size() - 1; ++j)
			{
				SetMask(entries[second][i].index, indexActive[j], 1);
			}
		}
		else
		{
			for (int j = 0; j < indexActive.size(); ++j)
			{
				if (indexActive[j] == entries[second][i].index)
					indexActive.erase(indexActive.begin() + j);
			}
		}
	}

	for (int i = 0; i < entries[third].size(); ++i)
	{
		if (entries[third][i].start)
		{
			indexActive.push_back(entries[third][i].index);
			for (int j = 0; j < indexActive.size() - 1; ++j)
			{
				if (CheckMask(entries[third][i].index, indexActive[j], 0) && CheckMask(entries[third][i].index, indexActive[j], 1))
				{
					BroadPhasePair pair;
					pair.p1 = bodies[entries[third][i].index];
					pair.p2 = bodies[indexActive[j]];
					pair.p1->SetDebugColour(Vec4(1, 0, 0, 1));
					pair.p2->SetDebugColour(Vec4(1, 0, 0, 1));
					pairs.push_back(pair);
				}
			}
		}
		else
		{
			for (int j = 0; j < indexActive.size(); ++j)
			{
				if (indexActive[j] == entries[third][i].index)
					indexActive.erase(indexActive.begin() + j);
			}
		}
	}
}

void BroadPhase::AddBody(RigidBody* body)
{
	newBodies.push_back(body);
}

void BroadPhase::GenerateEntries()
{
	for (int i = 0; i < 3; ++i)
	{
		entries[i].clear();		
	}
	for (int i = 0; i < bodies.size(); ++i)
	{
		AddEntry(bodies[i], i);
	}	
}

void BroadPhase::AddEntry(RigidBody* body, int index)
{
	for (int j = 0; j < 3; ++j)
	{
		BroadPhaseEntry startEntry, endEntry;
		startEntry.index = index;
		endEntry.index = index;
		startEntry.start = true;
		endEntry.start = false;
		startEntry.value = body->GetAABB().GetMin()[j];
		endEntry.value = body->GetAABB().GetMax()[j];
		startEntry.body = body;
		endEntry.body = body;
		entries[j].push_back(startEntry);
		entries[j].push_back(endEntry);
	}
}

void BroadPhase::AddEntries()
{
	if (bodies.size() < newBodies.size())
	{
		for (int i = 0; i <  newBodies.size(); ++i)
		{
			bodies.push_back(newBodies[i]);
		}
		newBodies.clear();
		GenerateEntries();
		return;
	}
	int newIndex = bodies.size();
	for (int i = 0; i < newBodies.size(); ++i)
	{
		bodies.push_back(newBodies[i]);
		AddEntry(newBodies[i], newIndex);		
		++newIndex;
	}
	newBodies.clear();
}

void BroadPhase::SortEntries()
{
	for (int j = 0; j < 3; ++j)
	{
		std::sort(entries[j].begin(), entries[j].end(), EntrySortFunc);
	}
}

void BroadPhase::UpdateEntries()
{
	for (int j = 0; j < 3; ++j)
	{
		for (int i = 0; i < entries[j].size(); ++i)
		{
			if (entries[j][i].start)
				entries[j][i].value = entries[j][i].body->GetAABB().GetMin()[j];
			else
				entries[j][i].value = entries[j][i].body->GetAABB().GetMax()[j];
		}
	}
}
