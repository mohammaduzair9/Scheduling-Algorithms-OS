#include <iostream>
#include <numeric>
#include <math.h>
using namespace std;
#define MAX_PROCESS 10

int num_of_process=3, count, remain, time_quantum;
int execution_time[MAX_PROCESS], period[MAX_PROCESS], remain_time[MAX_PROCESS], deadline[MAX_PROCESS], remain_deadline[MAX_PROCESS];
int burst_time[MAX_PROCESS], wait_time[MAX_PROCESS], completion_time[MAX_PROCESS], arrival_time[MAX_PROCESS];

//collecting details of processes
void get_process_info(int selected_algo){
	cout << "Enter total number of processes(maximum "<< MAX_PROCESS << "): ";
   	cin >> num_of_process;
   	if (num_of_process < 1){
   		cout << "Do you really want to schedule "<< num_of_process << " processes? -_-" << endl;
   		exit(0);
   	}
	if (selected_algo == 2){
		cout << endl << "Enter Time Quantum: ";
		cin >> time_quantum;
		if (time_quantum < 1){
			cout << "Invalid Input: Time quantum should be greater than 0" << endl;
			exit(0);
		}
	}

	for (int i = 0; i < num_of_process; i++){
		cout << endl << "Process "<< i+1 << ":-" << endl;
		if (selected_algo == 1){	
			cout << "==> Burst time: ";
			cin >> burst_time[i]; 
		}
		else if (selected_algo == 2){
			cout << "=> Arrival Time: "; 
			cin >> arrival_time[i];
  			cout << "=> Burst Time: "; 
  			cin >> burst_time[i];
  			remain_time[i] = burst_time[i];
		}
		else if (selected_algo > 2){
			cout << "==> Execution time: ";
			cin >> execution_time[i];
			remain_time[i] = execution_time[i];
			if (selected_algo == 4){
				cout << "==> Deadline: ";
				cin >> deadline[i];
			} else {
				cout << "==> Period: ";
				cin >> period[i];
			}
		}
	}
}

//calculating the observation time for scheduling timeline
int get_observation_time(int selected_algo){
		int sum=0;
		for(int i=0; i<num_of_process; i++){
			sum += burst_time[i];
		}
		return sum;
	
}

//print scheduling sequence
void print_schedule(int process_list[], int cycles){
	cout << endl << "Scheduling:-" << endl << endl;
	cout << "Time: ";
	for (int i=0; i<cycles; i++){
		if (i < 10)
			cout << "| 0" << i << " ";
		else
			cout << "| " << i << " ";
	}
	cout << "|" << endl;

	for (int i=0; i<num_of_process; i++){
		cout << "P[" << i+1 << "]: ";
		for (int j=0; j<cycles; j++){
			if (process_list[j] == i+1)
				cout << "|####";
			else
				cout << "|    ";
		}
		cout << "|" << endl;
	}
}

void first_come_first_serve(int time){
	int process_list[time];
	int execution_time[num_of_process];

	int accsum, total_wait_time = 0, total_completion_time = 0;
    float average_wait_time = 0.0, average_completion_time = 0.0;

    /* start computing waiting time */
    wait_time[0]=0;    //first process doesn't wait
    for(int i=1; i<num_of_process; i++){
        wait_time[i] = 0;
        for(int j=0; j<i; j++)
            wait_time[i] += burst_time[j];
    }    /* end computing waiting time */

    //computing completion time of each process
    partial_sum (burst_time, burst_time+num_of_process, completion_time);

    cout << endl << "Process\t\tBurst Time\tWaiting Time\tCompletion Time";

    for(int i=0; i<num_of_process; i++){   
		accsum = burst_time[i];
        total_wait_time += wait_time[i];
        total_completion_time += completion_time[i];
        cout << endl << " P["<<i+1<<"]\t\t   " << burst_time[i] << "\t\t    " << wait_time[i] <<"\t\t    " << completion_time[i];
    }
 
    average_wait_time = total_wait_time*1.0/num_of_process;
    average_completion_time = total_completion_time*1.0/num_of_process;
    cout << endl << endl << "Average Waiting Time: " << average_wait_time;
    cout << endl << "Average Complettion Time: " << average_completion_time << endl;
    
    int proc=0;
    //computing process list
    for(int i=0; i<time; i++){
    	if (burst_time[proc]-- < 1){
    	    proc++;
    	    burst_time[proc]--;
    	}	
    	process_list[i] = proc+1;	//process' number start from 1 not 0.
    }

    print_schedule(process_list,time);
}

int main(int argc, char* argv[]) {
	int option = 0;
	cout << "-----------------------------" << endl;
	cout << "CPU Scheduling Algorithms: " << endl;
	cout << "-----------------------------" << endl;
	cout << "1. First Come First Serve" << endl;
	cout << "-----------------------------" << endl;
	cout << "Select > "; cin >> option;
	cout << "-----------------------------" << endl;

	get_process_info(option);		//collecting processes detail
	int observation_time = get_observation_time(option);

	if (option == 1)
	 	first_come_first_serve(observation_time);
	return 0;
}
