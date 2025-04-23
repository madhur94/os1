#include <bits/stdc++.h>
using namespace std;

// FCFS Page Replacement
void FCFS(vector<int> pages, int capacity) 
{ 
    unordered_set<int> memory;
    queue<int> order;
    int faults = 0;

    for (int page : pages) {
        if (memory.find(page) == memory.end()) {
            faults++;
            if (memory.size() == capacity) {
                int old = order.front();
                order.pop();
                memory.erase(old);
            }
            memory.insert(page);
            order.push(page);
        }
    }

    cout << "FCFS Page Faults: " << faults << endl;
}

// LRU Page Replacement
void LRU(vector<int> pages, int capacity) {
    unordered_set<int> memory;
    unordered_map<int, int> recent;
    int faults = 0;

    for (int i = 0; i < pages.size(); i++) {
        int page = pages[i];

        if (memory.find(page) == memory.end()) {
            faults++;
            if (memory.size() == capacity) {
                int lru = pages[i];
                int least = i;
                for (int memPage : memory) {
                    if (recent[memPage] < least) {
                        least = recent[memPage];
                        lru = memPage;
                    }
                }
                memory.erase(lru);
            }
            memory.insert(page);
        }
        recent[page] = i;
    }

    cout << "LRU Page Faults: " << faults << endl;
}

// Optimal Page Replacement
void Optimal(vector<int> pages, int capacity) {
    unordered_set<int> memory;
    int faults = 0;

    for (int i = 0; i < pages.size(); ++i) {
        int page = pages[i];

        if (memory.find(page) == memory.end()) {
            faults++;
            if (memory.size() == capacity) {
                int farthest = i, val = -1;

                for (int memPage : memory) {
                    int j;
                    for (j = i + 1; j < pages.size(); ++j) {
                        if (pages[j] == memPage)
                            break;
                    }
                    if (j > farthest) {
                        farthest = j;
                        val = memPage;
                    }
                }

                if (val != -1)
                    memory.erase(val);
                else
                    memory.erase(memory.begin());
            }
            memory.insert(page);
        }
    }

    cout << "Optimal Page Faults: " << faults << endl;
}

int main() {
    try {
        int n, capacity;
        cout << "Enter number of pages: ";
        cin >> n;
        if (cin.fail() || n <= 0)
            throw invalid_argument("Invalid number of pages.");

        vector<int> pages(n);
        cout << "Enter the page reference string:\n";
        for (int i = 0; i < n; ++i) {
            cin >> pages[i];
            if (cin.fail())
                throw invalid_argument("Invalid page reference input.");
        }

        cout << "Enter frame capacity: ";
        cin >> capacity;
        if (cin.fail() || capacity <= 0)
            throw invalid_argument("Invalid frame capacity.");

        int choice;
        do {
            cout << "\nChoose Replacement Algorithm:\n";
            cout << "1. FCFS\n2. LRU\n3. Optimal\n4. Exit\nEnter choice: ";
            cin >> choice;
            if (cin.fail())
                throw invalid_argument("Invalid menu choice.");

            switch (choice) {
                case 1:
                    FCFS(pages, capacity);
                    break;
                case 2:
                    LRU(pages, capacity);
                    break;
                case 3:
                    Optimal(pages, capacity);
                    break;
                case 4:
                    cout << "Exiting program.\n";
                    break;
                default:
                    cout << "Invalid choice\n";
            }
        } while (choice != 4);
    } catch (const exception &e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
