#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Process {
    int pid; 
    int bt;  
    int art; 
};


void findWaitingTime(vector<Process>& proc, vector<int>& wt) {
    vector<int> rt(proc.size());

    
    for (size_t i = 0; i < proc.size(); i++)
        rt[i] = proc[i].bt;

    int complete = 0, t = 0, minm = INT_MAX;
    int shortest = 0, finish_time;
    bool check = false;

    
    while (complete != proc.size()) {
        
        for (size_t j = 0; j < proc.size(); j++) {
            if (proc[j].art <= t && rt[j] < minm && rt[j] > 0) {
                minm = rt[j];
                shortest = j;
                check = true;
            }
        }

        if (check == false) {
            t++;
            continue;
        }

        
        rt[shortest]--;

        
        minm = rt[shortest];
        if (minm == 0)
            minm = INT_MAX;

        
        if (rt[shortest] == 0) {
            
            complete++;
            check = false;

            
            finish_time = t + 1;

            
            wt[shortest] = finish_time - proc[shortest].bt - proc[shortest].art;

            if (wt[shortest] < 0)
                wt[shortest] = 0;
        }

        
        t++;
    }
}


void findTurnAroundTime(const vector<Process>& proc, const vector<int>& wt, vector<int>& tat) {
    
    for (size_t i = 0; i < proc.size(); i++)
        tat[i] = proc[i].bt + wt[i];
}


void findAvgTime(vector<Process>& proc) {
    vector<int> wt(proc.size(), 0);
    vector<int> tat(proc.size(), 0);

    
    findWaitingTime(proc, wt);

    
    findTurnAroundTime(proc, wt, tat);

    
    cout << " P\tBT\tWT\tTAT\n";

    
    int total_wt = 0, total_tat = 0;
    for (size_t i = 0; i < proc.size(); i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        cout << " " << proc[i].pid << "\t" << proc[i].bt << "\t" << wt[i] << "\t" << tat[i] << endl;
    }

    
    cout << "\nAverage waiting time = " << (float)total_wt / proc.size();
    cout << "\nAverage turn around time = " << (float)total_tat / proc.size();
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> proc(n);

    
    for (int i = 0; i < n; i++) {
        cout << "Enter details for process " << i + 1 << ":" << endl;
        cout << "Process ID: ";
        cin >> proc[i].pid;
        cout << "Burst Time: ";
        cin >> proc[i].bt;
        cout << "Arrival Time: ";
        cin >> proc[i].art;
    }

    findAvgTime(proc);

    return 0;
}

