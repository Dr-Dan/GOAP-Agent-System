//
//  TimeMaster.h
//  AgentGOBGridTest
//
//  Created by D J Clarke on 02/05/2015.
//
//

#ifndef __AgentGOBGridTest__TimeMaster__
#define __AgentGOBGridTest__TimeMaster__

#include <stdio.h>
#include <map>
#include <string>

using namespace std;

class TimeMaster{
    static long long curMilli;
    static long long prevMilli;
    
//	int stepTimeMillis = 250; // time in millis per step
	
	static int bufferIndex;
	
	// this may be better as vectors
//	typedef map<string, int> mapTimer;
	typedef pair<string, long long> pairTimer;
	
	map<string, long long> timers;

	map<string, long long> pMilliMap;
	
public:
	
	void AddTimer(string name, int stepTimeMillis_);
	
//	void SetStepTime(int stepTimeMillis_);
	void SetStepTime(string tmrName, int stepTimeMillis_);

     void SetFromSystem();
    
//     bool IsNextStep();
	bool IsNextStep(string tmrName);

	 long long GetCurrentTime();
	
	 int nextBufferIndex();
	
	void Update(string tmrName);
};
#endif /* defined(__AgentGOBGridTest__TimeMaster__) */
