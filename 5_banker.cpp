#include <iostream>
using namespace std;

int n, m;
int Allocation[10][10];
int Max[10][10];
int Need[10][10];
int Available[10];
int Work[10];
int Finish[10];
int Sequence[10];

// Function to check system safety and print safe sequence
bool Safety() {
    for (int i = 0; i < m; i++)
        Work[i] = Available[i];

    for (int i = 0; i < n; i++)
        Finish[i] = 0;

    int count = 0;

    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!Finish[i]) {
                bool canRun = true;
                for (int j = 0; j < m; j++) {
                    if (Need[i][j] > Work[j]) {
                        canRun = false;
                        break;
                    }
                }
                if (canRun) {
                    for (int j = 0; j < m; j++)
                        Work[j] += Allocation[i][j];
                    Sequence[count++] = i;
                    Finish[i] = 1;
                    found = true;
                }
            }
        }
        if (!found) {
            cout << "System is not in a safe state.\n";
            return false;
        }
    }

    cout << "Safe sequence: ";
    for (int i = 0; i < n; i++) {
        cout << "P" << Sequence[i] << " ";
    }
    cout << endl;
    return true;
}

int main() {
    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter the number of resources: ";
    cin >> m;

    cout << "Enter the Max matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> Max[i][j];

    cout << "Enter the Allocation matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> Allocation[i][j];

    // Calculate Need matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            Need[i][j] = Max[i][j] - Allocation[i][j];

    cout << "Enter the Available resources: ";
    for (int i = 0; i < m; i++)
        cin >> Available[i];

    Safety();

    return 0;
}
