#include <iostream>
#include <vector>
#include <limits.h>
#include <stdexcept>
using namespace std;

#define MAX_FRAMES 10
#define MAX_PAGES 50

int n, Size;

bool isHit(vector<int> &Frame, int page)
{
    for (int i = 0; i < Size; i++)
    {
        if (Frame[i] == page)
            return true;
    }
    return false;
}

void FCFS(vector<int> &PageSeq)
{
    cout << "\n--- FCFS Page Replacement ---\n";
    vector<int> Frame(Size, -1);
    int front = 0, faults = 0;

    for (int i = 0; i < n; i++)
    {
        if (!isHit(Frame, PageSeq[i]))
        {
            faults++;
            Frame[front] = PageSeq[i];
            front = (front + 1) % Size;
        }

        cout << "Page " << PageSeq[i] << ": ";
        for (int j = 0; j < Size; j++)
            cout << (Frame[j] == -1 ? "- " : to_string(Frame[j]) + " ");
        cout << endl;
    }

    cout << "Total Page Faults (FCFS): " << faults << endl;
    cout << "Total Page Hits (FCFS): " << n - faults << endl;
    cout << "Hit Ratio: " << ((float)(n - faults) / n) * 100 << "%" << endl;
}

void LRU(vector<int> &PageSeq)
{
    cout << "\n--- LRU Page Replacement ---\n";
    vector<int> Frame(Size, -1);
    vector<int> count(Size, 0);
    int Time = 0, faults = 0;

    for (int i = 0; i < n; i++)
    {
        Time++;
        bool hit = false;

        for (int j = 0; j < Size; j++)
        {
            if (Frame[j] == PageSeq[i])
            {
                hit = true;
                count[j] = Time;
                break;
            }
        }

        if (!hit)
        {
            faults++;
            int minTime = INT_MAX, replace_index = -1;

            for (int j = 0; j < Size; j++)
            {
                if (Frame[j] == -1)
                {
                    replace_index = j;
                    break;
                }
                else if (count[j] < minTime)
                {
                    minTime = count[j];
                    replace_index = j;
                }
            }

            Frame[replace_index] = PageSeq[i];
            count[replace_index] = Time;
        }

        cout << "Page " << PageSeq[i] << ": ";
        for (int j = 0; j < Size; j++)
            cout << (Frame[j] == -1 ? "- " : to_string(Frame[j]) + " ");
        cout << endl;
    }

    cout << "Total Page Faults (LRU): " << faults << endl;
    cout << "Total Page Hits (LRU): " << n - faults << endl;
    cout << "Hit Ratio: " << ((float)(n - faults) / n) * 100 << "%" << endl;
}

int predict(vector<int> &PageSeq, vector<int> &Frame, int index)
{
    int farthest = -1, pos = -1;
    for (int i = 0; i < Size; i++)
    {
        int j;
        for (j = index; j < n; j++)
        {
            if (Frame[i] == PageSeq[j])
            {
                if (j > farthest)
                {
                    farthest = j;
                    pos = i;
                }
                break;
            }
        }
        if (j == n)
            return i;
    }
    return (pos == -1) ? 0 : pos;
}

void Optimal(vector<int> &PageSeq)
{
    cout << "\n--- Optimal Page Replacement ---\n";
    vector<int> Frame(Size, -1);
    int faults = 0;

    for (int i = 0; i < n; i++)
    {
        if (!isHit(Frame, PageSeq[i]))
        {
            faults++;
            int j;
            for (j = 0; j < Size; j++)
            {
                if (Frame[j] == -1)
                {
                    Frame[j] = PageSeq[i];
                    break;
                }
            }

            if (j == Size)
            {
                int idx = predict(PageSeq, Frame, i + 1);
                Frame[idx] = PageSeq[i];
            }
        }

        cout << "Page " << PageSeq[i] << ": ";
        for (int j = 0; j < Size; j++)
            cout << (Frame[j] == -1 ? "- " : to_string(Frame[j]) + " ");
        cout << endl;
    }

    cout << "Total Page Faults (Optimal): " << faults << endl;
    cout << "Total Page Hits (Optimal): " << n - faults << endl;
    cout << "Hit Ratio: " << ((float)(n - faults) / n) * 100 << "%" << endl;
}

int main()
{
    try
    {
        vector<int> PageSeq(MAX_PAGES);
        int choice;

        cout << "Enter Number of Pages: ";
        cin >> n;
        if (cin.fail() || n <= 0 || n > MAX_PAGES)
            throw invalid_argument("Invalid number of pages.");

        cout << "Enter The Page Reference String:\n";
        for (int i = 0; i < n; i++)
        {
            cin >> PageSeq[i];
            if (cin.fail())
                throw invalid_argument("Invalid page reference input.");
        }

        cout << "Enter The Number of Frames: ";
        cin >> Size;
        if (cin.fail() || Size <= 0 || Size > MAX_FRAMES)
            throw invalid_argument("Invalid number of frames.");

        do
        {
            cout << "\nChoose Paging Algorithm:\n";
            cout << "1. FCFS\n";
            cout << "2. LRU\n";
            cout << "3. Optimal\n";
            cout << "4. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            if (cin.fail())
                throw invalid_argument("Invalid menu choice.");

            switch (choice)
            {
            case 1:
                FCFS(PageSeq);
                break;
            case 2:
                LRU(PageSeq);
                break;
            case 3:
                Optimal(PageSeq);
                break;
            case 4:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
            }
        } while (choice != 4);
    }
    catch (const exception &e)
    {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
