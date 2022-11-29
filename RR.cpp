#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>

using namespace std;

struct Process{
    string Pro_ID;
    int Arrival;
    int Burst;
    int WT, RT, TAT;
    int runtime, Start, Fin; 
};

int quantum_time;
Process getProcess(){
    Process result;
    cin>>result.Pro_ID>>result.Arrival>>result.Burst;
    result.runtime = result.Burst;
    result.WT=result.RT=result.TAT=result.Start=result.Fin=0;
    return result;
}

bool Condition(Process A, Process B){
    return A.Arrival <= B.Arrival;
}

void getNew(queue<Process> &New, int n){
    Process A;
    vector<Process> vector_New;
    for(int i = 0; i < n; i++){
        A = getProcess();
        vector_New.push_back(A);
    }
    sort(vector_New.begin(), vector_New.end(), Condition);
    for(int i = 0; i < n; i++){
        New.push(vector_New[i]);
    }
}

void printProcess(Process myPro){
    cout<<myPro.Pro_ID<<"\t\t"<<myPro.RT<<"\t\t"<<myPro.WT<<"\t\t"<<myPro.TAT<<endl;
}



void output(queue<Process> Terminated, int n){
    float totRT = 0, totWT = 0, totTAT = 0;
    cout<<"Pro_ID|   Response Time|  Waiting Time|   Turnaround Time"<<endl;
    while(!Terminated.empty()){
        printProcess(Terminated.front());
        totRT += Terminated.front().RT;
        totWT += Terminated.front().WT;
        totTAT += Terminated.front().TAT;
        Terminated.pop();
    }
    cout<<"Average Response Time: "<<totRT/n<<endl;
    cout<<"Average Waiting Time: "<<totWT/n<<endl;
    cout<<"Average Turnaround Time: "<<totTAT/n<<endl;
}

void RR(queue<Process>& New, queue<Process>& Ready, queue<Process>& Terminated,int n){
    int currentTime = New.front().Arrival;
    while(Terminated.size()<n)
    {
        while((New.size()>0) && (New.front().Arrival<=currentTime))
        {
            Ready.push(New.front());
            New.pop();
        }
        if(Ready.size()>0)
        {
            if(Ready.front().runtime!=0)
            {
                Ready.push(Ready.front());
                Ready.pop();
            }
            else
            {
                Terminated.push(Ready.front());
                Ready.pop();
            }
            if(!Ready.empty()){
                if(currentTime==Ready.front().Arrival)
                {
                    Ready.front().Start=Ready.front().Arrival;
                    Ready.front().RT=0;
                    Ready.front().Fin=Ready.front().Arrival;
                }
                else{
                    if(Ready.front().Start==0 && Ready.front().Fin==0)
                    {
                        Ready.front().Start=currentTime;
                        Ready.front().RT=currentTime-Ready.front().Arrival;
                        Ready.front().Fin=currentTime;
                        Ready.front().WT=Ready.front().RT;
                    
                    }
                }
                if(Ready.front().runtime<=quantum_time)
                {
                    Ready.front().WT+=currentTime-Ready.front().Fin;
                    Ready.front().Fin=currentTime+Ready.front().runtime;
                    Ready.front().TAT=Ready.front().Fin-Ready.front().Arrival;
                    currentTime+=Ready.front().runtime;
                    Ready.front().runtime=0;
                }
                else
                {
                    Ready.front().WT+=currentTime-Ready.front().Fin;
                    Ready.front().Fin=currentTime+quantum_time;
                    Ready.front().runtime-=quantum_time;
                    currentTime+=quantum_time;
                }
            }
        }
    }
}

int main(){
    int n;
    cin>>n;
    cin>>quantum_time;
    queue<Process> New;
    queue<Process> Ready;
    queue<Process> Terminated;
    getNew(New, n);
    RR(New, Ready, Terminated, n);
    output(Terminated, n);
    return 0;
}