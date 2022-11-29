#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
struct Process {
    string Pname;
    int Arrival;
    int Burst;
    int WT;
    int RT;
    int TaT;
    int Start;
    int Fin;
};
bool Condition(Process a,Process b) {
    return a.Arrival <= b.Arrival;
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
void SJF(vector<Process>& New, vector<Process>& Ready, vector<Process>& Term, int n) {
    sort(New.begin(), New.end(), Condition);
    New[0].Start = New[0].Arrival;
    New[0].Fin = New[0].Burst + New[0].Start;
    New[0].WT = 0;
    New[0].RT = 0;
    New[0].TaT = New[0].Burst;

    Ready = {New[0]};

    New.erase(New.begin());

    while(true) {
        if (New.size() > 0 && New[0].Arrival <= Ready[0].Fin) {
            auto i = Ready.begin() + 1;
            while(i < Ready.end() && (*i).Burst <= New[0].Burst) {
                i++;
            }
            Ready.insert( i, New[0]);
            New.erase(New.begin());
        }
        else if (Ready.size() > 1) {
            Term.push_back(Ready[0]);
            Ready.erase(Ready.begin());

            Ready[0].Start = Term.back().Fin;
            Ready[0].Fin = Ready[0].Start + Ready[0].Burst;
            Ready[0].RT = Ready[0].Start - Ready[0].Arrival;
            Ready[0].WT = Ready[0].RT;
            Ready[0].TaT = Ready[0].Fin - Ready[0].Arrival;
        }
        else {
            Term.push_back(Ready[0]);
            Ready.erase(Ready.begin());
            break;
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
int main() {
    int n;
    vector<Process> New(n);
    Input( n, New);
    if (n <= 0) {
        return 0;
    }
    vector<Process> Ready, Term;
    SJF(New, Ready, Term, n);
    Output( Term, n);
    return 0;
}