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
    process(const process& other);
    process& operator=(const process& other);



    bool operator==(const process& other) const;
    bool operator<(const process& other) const;
	
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

process::process(const process &other) {
	this->PID=other.PID;
	this->IsFinish=other.IsFinish;
	this->InQueue=other.InQueue;
	this->process_name=other.process_name;
	this->arrival_time=other.arrival_time;
	this->TurnAroundTime=other.TurnAroundTime;
	this->data_Text=other.data_Text;
	this->index=other.index;
	this->priority=other.priority;
}

process& process::operator = (const process &other){
	this->PID=other.PID;
	this->IsFinish=other.IsFinish;
	this->InQueue=other.InQueue;
	this->process_name=other.process_name;
	this->arrival_time=other.arrival_time;
	this->TurnAroundTime=other.TurnAroundTime;
	this->data_Text=other.data_Text;
	this->index=other.index;
	this->priority=other.priority;
	return *this;
}

bool process::operator==(const process &other) const {
    return this->priority==other.priority;
}

bool process::operator<(const process &other) const {
    return this->priority > other.priority || (this->priority==other.priority && this->arrival_time>other.arrival_time) ||
            ((this->priority==other.priority && this->arrival_time==other.arrival_time && this->PID > other.PID));
}

#endif
