#include<bits/stdc++.h>
using namespace std;

int n, head, DiskSize;

void FIFO(vector<int> Arr, int Head) {
    int TotalHM = 0;
    cout << "\nFIFO Order: " << Head;
    for (int i = 0; i < n; i++) {
        cout << " -> " << Arr[i];
        TotalHM += abs(Arr[i] - Head);
        Head = Arr[i];
    }
    cout << "\nTotal Head Movement (FIFO): " << TotalHM << "\n";
}

void SSTF(vector<int> Arr, int Head) {
    int TotalHM = 0;
    vector<bool> Finish(n, false);

    cout << "\nSSTF Order: " << Head;
    for (int i = 0; i < n; i++) {
        int min = 1e9, index = -1;
        for (int j = 0; j < n; j++) {
            if (!Finish[j] && abs(Arr[j] - Head) < min) {
                min = abs(Arr[j] - Head);
                index = j;
            }
        }
        Finish[index] = true;
        cout << " -> " << Arr[index];
        TotalHM += abs(Arr[index] - Head);
        Head = Arr[index];
    }
    cout << "\nTotal Head Movement (SSTF): " << TotalHM << "\n";
}

void SCAN(vector<int> Arr, int Head) {
    int TotalHM = 0, Dir;
    cout << "Enter Direction (Right = 1 / Left = 0): ";
    cin >> Dir;

    Arr.push_back(Head);
    sort(Arr.begin(), Arr.end());

    int pos = find(Arr.begin(), Arr.end(), Head) - Arr.begin();

    cout << "\nSCAN Order: " << Head;
    if (Dir == 1) {
        for (int i = pos + 1; i < Arr.size(); i++) {
            cout << " -> " << Arr[i];
            TotalHM += abs(Arr[i] - Head);
            Head = Arr[i];
        }
        if (Head != DiskSize - 1) {
            TotalHM += abs(DiskSize - 1 - Head);
            cout << " -> " << DiskSize - 1;
            Head = DiskSize - 1;
        }
        for (int i = pos - 1; i >= 0; i--) {
            cout << " -> " << Arr[i];
            TotalHM += abs(Arr[i] - Head);
            Head = Arr[i];
        }
    } else {
        for (int i = pos - 1; i >= 0; i--) {
            cout << " -> " << Arr[i];
            TotalHM += abs(Arr[i] - Head);
            Head = Arr[i];
        }
        if (Head != 0) {
            TotalHM += Head;
            cout << " -> 0";
            Head = 0;
        }
        for (int i = pos + 1; i < Arr.size(); i++) {
            cout << " -> " << Arr[i];
            TotalHM += abs(Arr[i] - Head);
            Head = Arr[i];
        }
    }

    cout << "\nTotal Head Movement (SCAN): " << TotalHM << "\n";
}

void CSCAN(vector<int> Arr, int Head) {
    int TotalHM = 0, Dir;
    cout << "Enter Direction (Right = 1 / Left = 0): ";
    cin >> Dir;

    Arr.push_back(Head);
    sort(Arr.begin(), Arr.end());

    int pos = find(Arr.begin(), Arr.end(), Head) - Arr.begin();

    cout << "\nC-SCAN Order: " << Head;
    if (Dir == 1) {
        for (int i = pos + 1; i < Arr.size(); i++) {
            cout << " -> " << Arr[i];
            TotalHM += abs(Arr[i] - Head);
            Head = Arr[i];
        }
        if (Head != DiskSize - 1) {
            cout << " -> " << DiskSize - 1;
            TotalHM += abs(DiskSize - 1 - Head);
            Head = DiskSize - 1;
        }
        cout << " -> 0";
        TotalHM += DiskSize - 1;
        Head = 0;

        for (int i = 0; i < pos; i++) {
            cout << " -> " << Arr[i];
            TotalHM += abs(Arr[i] - Head);
            Head = Arr[i];
        }
    } else {
        for (int i = pos - 1; i >= 0; i--) {
            cout << " -> " << Arr[i];
            TotalHM += abs(Arr[i] - Head);
            Head = Arr[i];
        }
        if (Head != 0) {
            cout << " -> 0";
            TotalHM += Head;
            Head = 0;
        }
        cout << " -> " << DiskSize - 1;
        TotalHM += DiskSize - 1;
        Head = DiskSize - 1;

        for (int i = Arr.size() - 1; i > pos; i--) {
            cout << " -> " << Arr[i];
            TotalHM += abs(Arr[i] - Head);
            Head = Arr[i];
        }
    }

    cout << "\nTotal Head Movement (C-SCAN): " << TotalHM << "\n";
}

int main() {
    int ch;
    cout << "Enter Number of Requests: ";
    cin >> n;

    vector<int> Arr(n);
    cout << "Enter the Request Sequence:\n";
    for (int i = 0; i < n; i++) cin >> Arr[i];

    cout << "Enter Initial Head Position: ";
    cin >> head;

    cout << "Enter Total Disk Size: ";
    cin >> DiskSize;

    do {
        cout << "\n******** MENU ********\n";
        cout << "1. FIFO\n";
        cout << "2. SSTF\n";
        cout << "3. SCAN\n";
        cout << "4. C-SCAN\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> ch;

        switch (ch) {
            case 1: FIFO(Arr, head); break;
            case 2: SSTF(Arr, head); break;
            case 3: SCAN(Arr, head); break;
            case 4: CSCAN(Arr, head); break;
            case 5: cout << "Thank you! Exiting...\n"; break;
            default: cout << "Invalid choice! Try again.\n";
        }

    } while (ch != 5);

    return 0;
}
