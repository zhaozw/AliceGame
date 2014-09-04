// GRecord_Others.cpp

#include "GRecord_Others.h"

GRecord_Others::GRecord_Others() : data(){

}

bool GRecord_Others::Initialize(){
	return true;
}

void GRecord_Others::GenerateAliceID(){
	// É_É~Å[
	data.aliceID = 0;
	data.nextDollID = FIRST_DOLL_ID;
}

DWORD GRecord_Others::GetDollID(){
	int id = data.nextDollID;
	data.nextDollID++;
	return id;
}

