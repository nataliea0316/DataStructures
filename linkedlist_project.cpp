#include <iostream>
#include <string>

using namespace std;

struct Student{
    int id;
    string name;
    float gpa;
    Student*next;

};

void addStudent(Student*& head){
    Student*next;
    Student*temp;
    int data;
    string tempname;
    float tempgpa;
    next = new Student;
    cout<<"Please enter Student ID"<<endl;
    cin>>data;
    next->id=data;
    cout<<"Please enter Student name"<<endl;
    cin>>tempname;
    next->name=tempname;
    cout<<"Please enter Student GPA"<<endl;
    cin>>tempgpa;
    next->gpa=tempgpa;
    next->next = nullptr;        

    if (head == nullptr) {       // empty list -> new node is head
        head = next;
    } else {                     // append: walk to end and link
        Student* p = head;
        while (p->next != nullptr) p = p->next;
        p->next = next;
    }
}


void displayAll(Student*& head){

    for (Student* p = head; p != nullptr; p = p->next) {
        cout << p->name<< " ";
    }
    cout << endl;
}

void searchbyID(Student*& head){
    int student_id;
    cout<<"Enter Student ID: "<<endl;
    cin>>student_id;

    bool found = false;   
    for (Student* p = head; p != nullptr; p = p->next){
        if(student_id==p->id){
            cout<<p->name<<endl;
            found = true;
            break;       
        }
    }
    if (!found) {
        cout<<"Invalid Student id"<<endl;
    }
}



bool deleteByID(Student*& head){
    int student_id;
    cout<<"Enter Student ID: "<<endl;
    cin>>student_id;
    for (Student* p = head; p != nullptr; p = p->next){
        if(student_id==p->id){
            delete p;
            return true;
        }
    } 

    return false;
}

int countStudents(Student*& head){
    int count = 0;
    for (Student* p = head; p != nullptr; p = p->next){
        count++;
    }
    return count;
}


int main(){
    Student* head = nullptr;

    while (true) {
        int option;
        cout<<"====Student Roster===="<<endl;
        cout<<"1. Add Student"<<endl;
        cout<<"2. Display All"<<endl;
        cout<<"3. Search Student"<<endl;
        cout<<"4. Delete Students"<<endl;
        cout<<"5. Count students"<<endl;
        cout<<"6. Exit"<<endl;
        cout<<"Choose an option"<<endl;

        if (!(cin >> option)) return 0;

        switch(option){
            case 1: {
                char again;
                do {
                    addStudent(head);
                    cout << "Add another student? (y/n): ";
                    cin >> again;
                } while (again == 'y' || again == 'Y');
                break;
            }
            case 2:
                displayAll(head);
                break;
            case 3:
                searchbyID(head);
                break;
            case 4:
                deleteByID(head);
                break;
            case 5:
                cout << "Total students: " << countStudents(head) << endl;
                break;
            case 6:
                cout<<"Exited "<<endl;
                return 0;
            default:
                cout<<"invalid choice"<<endl;
                break;
        }
    }
}
