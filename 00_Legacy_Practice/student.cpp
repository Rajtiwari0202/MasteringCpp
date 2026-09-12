#include<iostream>
using namespace std;

class Student{
    private:
        int id;
        string name;
        int mathMarks;
        int phyMarks;
        int chemMarks;

    public:
        Student(int r, string n, int m, int p, int c){
            roll = r;
            name=n;
            mathMarks = ,;
            phyMarks = p;
            chemMarks = c;
        }
        int total(){
            return mathMarks + phyMarks + chemMarks;
        }
        char grade(){
            float average = total()/3.0;
            if(average >= 90) return 'A';
            else if(average >= 80) return 'B';
            else if(average >= 70) return 'C';
            else if(average >= 60) return 'D';
            else return 'F';
        }
};
int main(){
    int roll;
    string name;
    int m,p,c;
    cout<<"Enter roll number: ";
    cin>>roll;
    cout<<"Enter name: ";
    cin>>name;      
    cout<<"Enter marks in Math, Physics and Chemistry: ";
    cin>>m>>p>>c;
    Student s(roll, name, m, p, c);
    cout<<"Total Marks: "<<s.total()<<endl;
    cout<<"Grade: "<<s.grade()<<endl;
}