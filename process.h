#ifndef _process_
#define _process_
#include<iostream>
#include <fstream>
#include <string>
#include "read.h"

using namespace std;
class process {
public:
	string process_name;
	string data_Text;
	int arrival_time;
	int TurnAroundTime = 0;
	int WaitingTime = 0;
	bool IsFinish;
	int PID;
	int index = 0;
	int priority;
	bool InQueue;
	process(string _name,int _priority, string _code, int _Arrival_time, int _PID);
    process(const process& compare);
    process& operator=(const process& compare);



    bool operator==(const process& compare) const;
    bool operator<(const process& compare) const;
	
};
/*
	constructor of the process class.I seperate the variables according to the definiton.txt file and also � added proce_num whiich is use this like an process ID.
*/
process::process(string _name,int _priority, string _code, int _Arrival_time, int _PID )
{
	PID = _PID;
	IsFinish = false;
	InQueue=false;
	process_name = _name;
	arrival_time = _Arrival_time;
	TurnAroundTime;
	data_Text = _code;
	index;
	priority=_priority;
}

process::process(const process &compare) {
	this->PID=compare.PID;
	this->IsFinish=compare.IsFinish;
	this->InQueue=compare.InQueue;
	this->process_name=compare.process_name;
	this->arrival_time=compare.arrival_time;
	this->TurnAroundTime=compare.TurnAroundTime;
	this->data_Text=compare.data_Text;
	this->index=compare.index;
	this->priority=compare.priority;
}

process& process::operator = (const process &compare){
	this->PID=compare.PID;
	this->IsFinish=compare.IsFinish;
	this->InQueue=compare.InQueue;
	this->process_name=compare.process_name;
	this->arrival_time=compare.arrival_time;
	this->TurnAroundTime=compare.TurnAroundTime;
	this->data_Text=compare.data_Text;
	this->index=compare.index;
	this->priority=compare.priority;
	return *this;
}

bool process::operator==(const process &compare) const {
    return this->priority==compare.priority;
}

bool process::operator<(const process &compare) const {
    if (this->priority==compare.priority)
		return this->arrival_time>compare.arrival_time;
	return this->priority>compare.priority;
}

#endif
