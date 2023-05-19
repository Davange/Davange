#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

struct MemoryBlock {
    int size;       
    int processId;  
};


void allocateMemory(vector<MemoryBlock>& memory, int processId, int requestedSize) {
    int n = memory.size();  

    
    int blockSize = pow(2, ceil(log2(requestedSize)));

    
    int blockIndex = -1;
    for (int i = 0; i < n; i++) {
        if (memory[i].size == blockSize && memory[i].processId == -1) {
            blockIndex = i;
            break;
        }
    }

    
    if (blockIndex != -1) {
        memory[blockIndex].processId = processId;
        cout << "Memory block of size " << blockSize << " allocated to Process " << processId << endl;
        return;
    }

    
    for (int size = blockSize * 2; size <= memory[n - 1].size; size *= 2) {
        
        for (int i = 0; i < n; i++) {
            if (memory[i].size == size && memory[i].processId == -1) {
                blockIndex = i;
                break;
            }
        }

        
        if (blockIndex != -1) {
            int halfSize = size / 2;
            memory[blockIndex].processId = processId;

            
            for (int i = blockIndex + 1; i < n; i++) {
                if (memory[i].size == halfSize && memory[i].processId == -1) {
                    memory[i].size = halfSize;
                    break;
                }
            }

            for (int i = blockIndex + 1; i < n; i++) {
                if (memory[i].size == halfSize && memory[i].processId == -1) {
                    memory[i].size = halfSize;
                    break;
                }
            }

            cout << "Memory block of size " << blockSize << " allocated to Process " << processId << endl;
            return;
        }
    }

    
    cout << "Memory allocation failed for Process " << processId << endl;
}


void deallocateMemory(vector<MemoryBlock>& memory, int processId) {
    int n = memory.size();

    
    for (int i = 0; i < n; i++) {
        if (memory[i].processId == processId) {
            memory[i].processId = -1;
            cout << "Memory block allocated to Process " << processId << " deallocated" << endl;
            return;
        }
    }

    
    cout << "No memory block allocated to Process " << processId << endl;
}


void displayMemoryStatus(const vector<MemoryBlock>& memory) {
    int n = memory.size();
    cout << "Memory Status:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Block " << i + 1 << ": ";
        if (memory[i].processId == -1) {
            cout << "Unoccupied" << endl;
        } else {
            cout << "Process " << memory[i].processId << endl;
        }
    }
}
int main() {
    
    vector<MemoryBlock> memory = {
        { 64, -1 },
        { 32, -1 },
        { 16, -1 },
        { 8, -1 }
    };

    
    displayMemoryStatus(memory);

    int processId, requestedSize;
    char option;

    do {
        cout << "\nEnter 'A' to allocate memory or 'D' to deallocate memory (or 'Q' to quit): ";
        cin >> option;

        if (option == 'A' || option == 'a') {
            cout << "Enter the process ID: ";
            cin >> processId;

            cout << "Enter the requested memory size: ";
            cin >> requestedSize;

            allocateMemory(memory, processId, requestedSize);
        } else if (option == 'D' || option == 'd') {
            cout << "Enter the process ID to deallocate memory: ";
            cin >> processId;

            deallocateMemory(memory, processId);
        } else if (option == 'Q' || option == 'q') {
            break;
        } else {
            cout << "Invalid option. Please try again." << endl;
        }

        
        displayMemoryStatus(memory);

    } while (option != 'Q' && option != 'q');

    return 0;
}

