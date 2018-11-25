#include "process.h"


/*
	constructor of the process class.I seperate the variables according to the definiton.txt file and also � added proce_num whiich is use this like an process ID.
*/
process::process(string _name,int _priority, string _code, int _Arrival_time, int _process_num )
{
	process_num = _process_num;
	IsFinish = false;
	InQueue=false;
	process_name = _name;
	arrival_time = _Arrival_time;
	turnAround_time;
	data_Text = _code;
	index;
	priority=_priority;

	
}

process& process::operator = (const process &other){
	this->arrival_time=other.arrival_time;
	this->priority=other.priority;
	return *this;
}

bool process::operator==(const process &other) const {
    return this->priority==other.priority;
}

bool process::operator<(const process &other) const {
    return this->priority > other.priority || (this->priority==other.priority && this->arrival_time>other.arrival_time) ||
            ((this->priority==other.priority && this->arrival_time==other.arrival_time && this->process_num > other.process_num));
}

#endif

