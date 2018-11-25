#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <cstdio>
#include "read.h"
#include "process.h"

using namespace std;
ofstream out("output.txt");//definition of output.txt
/*
	this function reads the denifition.txt file then create the proceses according to process_name - data_Text - arrival_time
*/
void printQueue(priority_queue<process> readyQ, int time){
    priority_queue<process> showQueue;
    //write to the output.txt
    showQueue=readyQ;	
    out<<time<<":HEAD";
    while(!showQueue.empty()){
		out << "-" <<showQueue.top().process_name << "[" << showQueue.top().index+1 << "]" ;
        showQueue.pop();
	}
    out<<"-TAIL"<<endl;
    //write to the terminal
    showQueue=readyQ;
    cout<<time<<":HEAD";
    while(!showQueue.empty()){
	cout << "-" <<showQueue.top().process_name << "[" << showQueue.top().index+1 << "]" ;
        showQueue.pop();
	}
    cout<<"-TAIL"<<endl;	
}



priority_queue<process> insertQueue(priority_queue<process> readyQ, vector<process>& process_table, int time){
    priority_queue<process> outputQueue;
    int i=0;
    while(i<process_table.size()){
    	if (process_table[i].arrival_time <= time && !process_table[i].IsFinish){
        	if(!readyQ.empty()){
                int var=0;
                outputQueue=readyQ;
                for(int j=0;j<readyQ.size();j++){
                    if(outputQueue.top().PID==process_table[i].PID){
                        var++;
                        break;
                    }
                    else{
                    	outputQueue.pop();
                    }
                }
                if(var==0){
					readyQ.push(process_table[i]);
				}
			}
			else{
                readyQ.push(process_table[i]);
            }
        }
        i++;
    }
	return readyQ;
}

void run_process(vector<process>& process_table){//run processes with calculating time
    priority_queue<process> readyQ;
    vector<code_num> instructions;
    int i=0;
    int time=process_table[0].arrival_time;
    read r;
    int isChanged=0;
    bool idle=false;
    out<<"0:HEAD-TAIL"<<endl;
    cout<<"0:HEAD-TAIL"<<endl;
    while(true){// run until processes is done
        readyQ=insertQueue(readyQ,process_table,time);
        if(isChanged!=readyQ.size() || isChanged==0||idle){//add first process
        	if(!readyQ.empty() || time==process_table[0].arrival_time){
        		printQueue(readyQ, time);
                 idle=false;
        	}
        }
        else if(process_table[0].arrival_time==time){
        	printQueue(readyQ, time);
        }
		if(!readyQ.empty()){
            instructions=r.read_all(readyQ.top().data_Text);
            int i = readyQ.top().index;
            while( i < instructions.size()){// run process with its burst
                
                priority_queue<process> count_WaitingTime_Queue;
                count_WaitingTime_Queue=readyQ;
                count_WaitingTime_Queue.pop();
                int firstWaiting=0;
                if(readyQ.top().InQueue==false){
                    firstWaiting = time-readyQ.top().arrival_time;
                    process_table[readyQ.top().PID].InQueue=true;
                    process_table[readyQ.top().PID].WaitingTime+=firstWaiting;
                }
                while(!count_WaitingTime_Queue.empty()&&count_WaitingTime_Queue.top().InQueue){
                    process_table[count_WaitingTime_Queue.top().PID].WaitingTime+=instructions[i].burst;
                    count_WaitingTime_Queue.pop();
                }
                if(!count_WaitingTime_Queue.empty()&&!count_WaitingTime_Queue.top().InQueue){
                	if(count_WaitingTime_Queue.size()>1){
                		count_WaitingTime_Queue.pop();
                		while(count_WaitingTime_Queue.size()>1){
                			if(count_WaitingTime_Queue.top().InQueue){
                				process_table[count_WaitingTime_Queue.top().PID].WaitingTime+=instructions[i].burst;
                			}
                			count_WaitingTime_Queue.pop();
                		}
                	}
                }
                time += instructions[i].burst;
                process_table[readyQ.top().PID].index = i+1;
                if(instructions[i].inst_name == "exit"){
                    process_table[readyQ.top().PID].IsFinish = true;
                    process_table[readyQ.top().PID].TurnAroundTime=time-process_table[readyQ.top().PID].arrival_time;
                    readyQ.pop();
                    if(readyQ.size()==0){
                        printQueue(readyQ, time);
                        idle=true;
                }
                    i++;
                    break;
                    
                }
                
                else{
		            readyQ.pop();
                }
                i++;
                break;	
            }
        }
        
            
            
        
        bool Exit = true;
        for(int i=0; i < process_table.size(); i++){
            if(!process_table[i].IsFinish)
                Exit=false;
        }
        if(Exit)
            break;
		else if(idle){
            for(int p=0;p<process_table.size();p++){
                if(process_table[p].IsFinish==false){
                    time=process_table[p].arrival_time;
                    break;
                }
            }
        }
		isChanged=readyQ.size()+1;
    }
    cout<<endl;
    out<<endl;
    for(int t=0;t<process_table.size();t++){
    	cout << "Turnaround time for P"<<process_table[t].PID+1<<" = "<<process_table[t].TurnAroundTime<<" ms"<<endl;
        cout << "Waiting time for P"<<process_table[t].PID+1<<" = "<<process_table[t].WaitingTime<<endl ;
        out << "Turnaround time for P"<<process_table[t].PID+1<<" = "<<process_table[t].TurnAroundTime<<" ms"<<endl;
        out << "Waiting time for P"<<process_table[t].PID+1<<" = "<<process_table[t].WaitingTime<<endl ;
    }
    
}


int main() {// I add processes to process table and call run_process
	vector<process> process_table;
	ifstream file("definition.txt");
	string process_name;
	string data_Text;
	int arrival_time;
	int PID = 0;
	int priority;
	while (file >> process_name >> priority >> data_Text >> arrival_time)
	{
		process newprocess(process_name, priority , data_Text, arrival_time, PID);
		PID++;
		process_table.push_back(newprocess);
	}
	file.close();
    run_process(process_table);
    
}
