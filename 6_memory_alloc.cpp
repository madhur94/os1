#include<bits/stdc++.h>
using namespace std;

void firstfit(int n,int m,vector<int> frames,vector<int> processes){
    int index = 0;
    for(int i=0;i<n;i++){
        bool found = false;
        for(int j =0;j<m;j++){
            if(frames[j]>=processes[i]){
                found = true;
                index = j;
                break;
            }
            
        }
        if(!found){
            cout<<"Process "<<i+1<<"cannot be allocated "<<endl;
            break;
        }else{
            cout<<"Process "<<i+1<<" allocated to frame "<<index +1<<endl;
            frames[index]-=processes[i];
        }
    }
}

void bestfit(int n,int m , vector<int>frames,vector<int> processes){
    for(int i=0;i<n;i++){
        int index = -1;
        int small = INT_MAX;
        for(int j = 0;j<m;j++){
            if(frames[j]>=processes[i] and frames[j]<small){
                small = frames[j];
                index = j;
            }
        }
        if(index == -1){
            cout<<"Process "<<i+1<<"cannot be allocated "<<endl;
            break;
        }else{
            cout<<"Process "<<i+1<<" allocated to frame "<<index +1<<endl;
            frames[index]-=processes[i];
        }
    }
}

void worstfit(int n,int m,vector<int> frames,vector<int> processes){
    for(int i=0;i<n;i++){
        int index = -1;
        int large = INT_MIN;
        for(int j = 0;j<m;j++){
            if(frames[j]>=processes[i] and frames[j]>large){
                large = frames[j];
                index = j;
            }
        }
        if(index == -1){
            cout<<"Process "<<i+1<<" cannot be allocated"<<endl;
            break;
        } else{
            cout<<"Process "<<i+1<<" allocated to frame "<<index +1<<endl;
            frames[index]-=processes[i];
        }
    }

}

void nextfit(int n,int m , vector<int> frames,vector<int> processes){
    int index = 0;
    for(int i=0;i<n;i++){
        bool found = false;
        int count = 0;
        for(int j = index;count<m ; j = (j+1)%m){
            if(frames[j] >= processes[i]){
                found = true;
                index = j;
                break;
            }
            count++;
        }

        if(!found){
            cout<<"Process "<<i+1<<" cannot be allocated"<<endl;
            break;
        } else{
            cout<<"Process "<<i+1<<" allocated to frame "<<index +1<<endl;
            frames[index]-=processes[i];
        }
    }
}
int main(){
    int n,m;
    cout<<"Enter the frame size: "<<endl;
    cin>>m;
    cout<<"Enter the number of processes: "<<endl;
    cin>>n;
    vector<int> frames(m),processes(n);
    cout<<"Enter the frame sizes: "<<endl;
    for(int i=0;i<m;i++){
        cin>>frames[i];
    }
    
    cout<<"Enter the processes: "<<endl;
    for(int i=0;i<n;i++){
        cin>>processes[i];
    }

    cout<<"first fit"<<endl;
    firstfit(n,m,frames,processes);
    cout<<"best fit"<<endl;
    bestfit(n,m,frames,processes);
    cout<<"worst fit"<<endl;
    worstfit(n,m,frames,processes);
    cout<<"next fit"<<endl;
    nextfit(n,m,frames,processes);
    return 0;
}