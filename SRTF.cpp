#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>

using namespace std;

struct Process{
    string Pname;
    int Arrival;
    int Burst;
    int WT;
    int RT;
    int TaT;
    int runtime, Start, Fin; 
};
bool Condition(Process A, Process B){
    return A.Arrival <= B.Arrival;
}
void Input(int &n, vector<Process> &New) {
    cout << "Nhap n: ";
    cin >> n;

    New = vector<Process>(n);

    for (int i = 0; i < n; i++) {
        cout << "Nhap thong tin process " << i + 1 << ':' << endl;
        cout << "\tTen: ";
        cin >> New[i].Pname; 
        cout << "\tArrival time: ";
        cin >> New[i].Arrival; 
        cout << "\tBurst time: ";
        cin >> New[i].Burst; 
    }
}
void addElement(queue<Process> &myQueue, Process element){
    Process cur;
    int sizeQueue = myQueue.size();
    for(int i = 0; i < sizeQueue; i++){
        cur = myQueue.front();
        if(sizeQueue == myQueue.size() && cur.runtime > element.runtime) myQueue.push(element);
        myQueue.pop();
        myQueue.push(cur);
    }
    if(sizeQueue == myQueue.size()) myQueue.push(element);
}
void SRTF(vector<Process>& New, queue<Process>& Ready, vector<Process>& Term, int n){
    for (Process &proc: New) {
        proc.runtime = proc.Burst;
    }
    sort(New.begin(), New.end(), Condition);
    int currentTime = New[0].Arrival;
    while(Term.size() != n){
        while(New.size() > 0 && New[0].Arrival == currentTime){
            addElement(Ready, New[0]);
            New.erase( New.begin());
        }
        if(Ready.front().Burst == Ready.front().runtime){
            Ready.front().Start = currentTime;
            Ready.front().RT = currentTime - Ready.front().Arrival;
        }
        currentTime++;
        Ready.front().runtime--;
        if(Ready.front().runtime == 0){
            Ready.front().Fin = currentTime;
            Ready.front().TaT = currentTime - Ready.front().Arrival;
            Ready.front().WT = Ready.front().TaT - Ready.front().Burst;
            Term.push_back(Ready.front());
            Ready.pop();
        }
    }
}
void Output(vector<Process>& Term, int n) {
    int sumRT = 0, sumWT = 0, sumTaT = 0;
    cout << endl << "Name | Start T | Finish T | Response T | Waiting T | Turnaround T" << endl;

    for (Process proc: Term) {
        cout.width(4);
        cout << proc.Pname << " | ";
        cout.width(7);
        cout << proc.Start << " | ";
        cout.width(8);
        cout << proc.Fin << " | ";
        cout.width(10);
        cout << proc.RT << " | ";
        cout.width(9);
        cout << proc.WT << " | ";
        cout.width(12);
        cout << proc.TaT << endl;

        sumRT += proc.RT;
        sumWT += proc.WT;
        sumTaT += proc.TaT;
    }
    cout << "Response time trung binh: " << float(sumRT) / n << endl;
    cout << "Waiting time trung binh: " << float(sumWT) / n << endl;
    cout << "Turnaround time trung binh: " << float(sumTaT) / n << endl;
}
int main(){
    int n;
    vector<Process> New;
    queue<Process> Ready;
    vector<Process> Term;
    Input( n, New);
    SRTF(New, Ready, Term, n);
    Output( Term, n);
    return 0;
}
