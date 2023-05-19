#include <sstream>
#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <queue>
using namespace std;

void worstFit(int blockSize[], int m, int processSize[], int n)
{

    int allocation[100];

    memset(allocation, -1, sizeof(allocation));

    for (int i = 0; i < n; i++)
    {

        int wstIdx = -1;
        for (int j = 0; j < m; j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                if (wstIdx == -1)
                    wstIdx = j;
                else if (blockSize[wstIdx] < blockSize[j])
                    wstIdx = j;
            }
        }

        if (wstIdx != -1)
        {

            allocation[i] = wstIdx;

            blockSize[wstIdx] -= processSize[i];
        }
    }

    cout << "\nProcess No.\tProcess Size\tBlock no\tRemaining Block Size.\n";
    for (int i = 0; i < n; i++)
    {
        cout << " " << i + 1 << "\t\t" << processSize[i] << "\t\t";
        if (allocation[i] != -1)
            cout << allocation[i] + 1 << "\t\t" << blockSize[allocation[i]] << endl;
        else
            cout << "Not Allocated\n";
    }

   cout << "\nBlock No.\tBlock Size\tFree Space\n";
for (int i = 0; i < m; i++)
{
    cout << " " << i + 1 << "\t\t" << blockSize[i] << "\t\t" << blockSize[i] << endl;
}
}

void bestFit(int blockSize[], int m, int processSize[], int n)
{

    int allocation[100];

    for (int i = 0; i < n; i++)
        allocation[i] = -1;

    for (int i = 0; i < n; i++)
    {

        int bestIdx = -1;
        for (int j = 0; j < m; j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                if (bestIdx == -1)
                    bestIdx = j;
                else if (blockSize[bestIdx] > blockSize[j])
                    bestIdx = j;
            }
        }

        if (bestIdx != -1)
        {

            allocation[i] = bestIdx;

            blockSize[bestIdx] -= processSize[i];
        }
    }

    cout << "\nProcess No.\tProcess Size\tBlock no\tRemaining Block Size.\n";
    for (int i = 0; i < n; i++)
    {
        cout << " " << i + 1 << "\t\t" << processSize[i] << "\t\t";
        if (allocation[i] != -1)
            cout << allocation[i] + 1 ;
        else
            cout << "Not Allocated";
        cout << endl;
    }

     cout << "\nBlock No.\tBlock Size\tFree Space\n";
for (int i = 0; i < m; i++)
{
    cout << " " << i + 1 << "\t\t" << blockSize[i] << "\t\t" << blockSize[i] << endl;
}
}

void firstFit(int blockSize[], int m, int processSize[], int n)
{

    int allocation[100];

    memset(allocation, -1, sizeof(allocation));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (blockSize[j] >= processSize[i])
            {

                allocation[i] = j;

                blockSize[j] -= processSize[i];

                break;
            }
        }
    }

    cout << "\nProcess No.\tProcess Size\tBlock no\tRemaining Block Size.\n";
    for (int i = 0; i < n; i++)
    {
        cout << " " << i + 1 << "\t\t"
             << processSize[i] << "\t\t";
        if (allocation[i] != -1)
            cout << allocation[i] + 1  ;
        else
            cout << "Not Allocated";
        cout << endl;
    }

    cout << "\nBlock No.\tBlock Size\tFree Space\n";
for (int i = 0; i < m; i++)
{
    cout << " " << i + 1 << "\t\t" << blockSize[i] << "\t\t" << blockSize[i] << endl;
}
}

void NextFit(int blockSize[], int m, int processSize[], int n)
{

    int allocation[100], j = 0, t = m - 1;

    memset(allocation, -1, sizeof(allocation));

    for (int i = 0; i < n; i++)
    {

        while (j < m)
        {
            if (blockSize[j] >= processSize[i])
            {

                allocation[i] = j;

                blockSize[j] -= processSize[i];

                t = (j - 1) % m;
                break;
            }
            if (t == j)
            {

                t = (j - 1) % m;

                break;
            }

            j = (j + 1) % m;
        }
    }

    cout << "\nProcess No.\tProcess Size\tBlock no\tRemaining Block Size.\n";
    for (int i = 0; i < n; i++)
    {
        cout << " " << i + 1 << "\t\t\t\t" << processSize[i]
             << "\t\t\t\t";
        if (allocation[i] != -1)
            cout << allocation[i] + 1 ;
        else
            cout << "Not Allocated";
        cout << endl;
    }

     cout << "\nBlock No.\tBlock Size\tFree Space\n";
for (int i = 0; i < m; i++)
{
    cout << " " << i + 1 << "\t\t" << blockSize[i] << "\t\t" << blockSize[i] << endl;
}
}

int main()
{
    int noblock, noprocess, choice;
    cout << "Enter no of Blocks" << endl;
    cin >> noblock;
    int blockSize[noblock];

    cout << "Enter Size of Blocks" << endl;
    for (int i = 0; i < noblock; i++)
    {
        cin >> blockSize[i];
    }
    cout << "Enter no of Process" << endl;
    cin >> noprocess;

    int processSize[noprocess];
    cout << "Enter Size of Process" << endl;
    for (int i = 0; i < noprocess; i++)
    {
        cin >> processSize[i];
    }
    int m = sizeof(blockSize) / sizeof(blockSize[0]);
    int n = sizeof(processSize) / sizeof(processSize[0]);

    while (1)
    {
        cout<<endl;
        cout << "For Worst Fit Press 1" << endl;
        cout << "For Best Fit Press 2" << endl;
        cout << "For First Fit Press 3" << endl;
        cout << "For Next Fit Press 4" << endl;
        cout << "To Exit Press -1" << endl <<endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            worstFit(blockSize, m, processSize, n);
            break;
        case 2:
            bestFit(blockSize, m, processSize, n);
            break;
        case 3:
            firstFit(blockSize, m, processSize, n);
            break;
        case 4:
            NextFit(blockSize, m, processSize, n);
            break;

        case -1:
            exit(0);
        default:
            break;
        }
    }

    return 0;
}
