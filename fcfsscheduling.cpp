#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Process {
int id;
int arrival_time;
int burst_time;
};
bool compareByArrivalTime(Process a, Process b) {
return a.arrival_time < b.arrival_time;
}
void FCFS_Scheduling(vector<Process> processes) {
int n = processes.size();
int completion_time[n];
int waiting_time[n];
int turn_around_time[n];
int current_time = 0;
sort(processes.begin(), processes.end(), compareByArrivalTime);
cout << "Gantt Chart:\n";
cout << "------------------------------------\n";
for (int i = 0; i < n; i++) {
completion_time[i] = current_time + processes[i].burst_time;
waiting_time[i] = current_time - processes[i].arrival_time;
turn_around_time[i] = completion_time[i] - processes[i].arrival_time;
current_time = completion_time[i];
cout << "| " << "P" << processes[i].id << " |";
}
cout << "------------------------------------\n";
cout << 0;
for (int i = 0; i < n; i++) {
cout << " " << completion_time[i];
}
cout << endl << endl;
cout << "Process\t" << "Arrival Time\t" << "Burst Time\t" << "Completion Time\t" << "Waiting Time\t" << "Turn Around Time\t" << endl;
for (int i = 0; i < n; i++) {
cout << "P" << processes[i].id << "\t\t" << processes[i].arrival_time <<"\t\t" <<processes[i].burst_time << "\t\t" << completion_time[i] << "\t\t" << waiting_time[i]
<< "\t\t" << turn_around_time[i] << endl;
}
}
int main() {
vector<Process> processes;
int n, id, arrival_time, burst_time;
cout << "Enter the number of processes: ";
cin >> n;
cout << "Enter the process details (id, arrival time, burst time):\n";
for (int i = 0; i < n; i++) {
cin >> id >> arrival_time >> burst_time;
Process p = {id, arrival_time, burst_time};
processes.push_back(p);
}
FCFS_Scheduling(processes);
return 0;
}