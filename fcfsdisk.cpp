#include <iostream>
#include <conio.h>
#include <math.h>
using namespace std;

int main()
{
    int size;
    cout << "Enter the size of the request array: ";
    cin >> size;
    int arr[size];
    cout << "Enter the request array: ";
    for (int i = 0; i < size; i++)
    {
        cin >> arr[i];
    }
    int head;
    cout << "Enter the initial position of head: ";
    cin >> head;

    int seek_count = 0;
    int distance, cur_track;

    for (int i = 0; i < size; i++)
    {
        cur_track = arr[i];

        distance = abs(cur_track - head);

        seek_count += distance;

        head = cur_track;
    }

    cout << "Total number of seek operations = "
         << seek_count << endl;

    cout << "Seek Sequence is" << endl;

    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << endl;
    }

    return 0;
}

