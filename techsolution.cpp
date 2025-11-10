#include <iostream>
#include <cstring>
using namespace std;

class Employee 
{
 private:
    char* name;                                             /*Employee name ke sath humne jo pointer use
                                                            kiya hai iska mtlb hai keh humne dynamically
                                                            memory allocate krdi hai*/
    int id;
    double salary;
    static int totalEmployees;                             // static member to count total employees
    static  string companyName;                            // static member for fixed company name

 public:
    // I use Constructor initializer list for dynamically memory allocate
    Employee(const char* n, int i, double s) : id(i), salary(s) 
    {
        this->name = new char[strlen(n) + 1];
        strcpy_s(name, strlen(n) + 1, n);
        totalEmployees++;
    }

    //  Copy Constructor (Deep Copy) using 'this' pointer  
    Employee(const Employee& e)
    {
        this->name = new char[strlen(e.name) + 1];
        strcpy_s(name, strlen(e.name) + 1, e.name);
        this->id = e.id;
        this->salary = e.salary;
        totalEmployees++;
    }

    // Destructor to free allocated memory  
    ~Employee() 
    {
        delete[] name;
        totalEmployees--;
    }

    //  Const Function to display data (does not modify object)  
    void display() const
    {
        cout << "Company: " << companyName << endl;
        cout << "Employee Name: " << name << endl;
        cout << "Employee ID: " << id << endl;
        cout << "Salary: " << salary << endl;
        cout << endl;
    }

    //  Static Function to show total employees  
    static void displayTotalEmployees() 
    {
        cout << "Total Employees in " << companyName << ": " << totalEmployees << endl;
    }

    //  Function to change salary using 'this' pointer  
    void setSalary(double newSalary)
    {
        this->salary = newSalary;
    }

    //  Function to returning an object   
    Employee getCopy() 
    {
        Employee temp(*this);                                                //yeh current employee jo hoga usko copy krde ga  
        return temp;                                                        //object ko return krde ga
    }

    // Function to show shallow vs deep copy difference  
    void modifyName(const char* newName) 
    {
        strcpy_s(name, strlen(newName) + 1, newName);
    }

    //Friend Function declare krdiya hai humne class ke ander for salary comparison
    friend void compareSalary(const Employee& e1, const Employee& e2);
};

//  Static members initialization
int Employee::totalEmployees = 0;
string Employee::companyName = "TechSolutions";

//Friend Function implementation
void compareSalary(const Employee& e1, const Employee& e2)
{
    cout << "Salary Comparison:" << endl;
    cout << "Employee 1: " << e1.name << " " << e1.salary << endl;
    cout << "Employee 2: " << e2.name << " " << e2.salary << endl;
    if (e1.salary > e2.salary)
    {
        cout << e1.name << " has higher salary." << endl;
    }
    else if (e2.salary > e1.salary) 
    {
        cout << e2.name << " has higher salary." << endl;
    }
    else
    {
        cout << "Both have equal salary." << endl;
        cout << endl;
    }
}

int main()
{
    cout << " TechSolutions Employee Management System " << endl;
    cout<< endl;

    Employee e1("Fatima", 26, 50000);
    e1.display();

    Employee e2("Samara", 27, 60000);
    e2.display();

    Employee::displayTotalEmployees();
    cout << endl;

    cout << " Dynamic Object Allocation " << endl;
    Employee* e3 = new Employee("Hadiya", 28, 70000);
    e3->display();
    Employee::displayTotalEmployees();
    cout << endl;

    cout << " Passing Object as Function Argument " << endl;
    cout << "Salary updated successfully!" << endl;
    e1.setSalary(52000);
    e1.display();

    cout << " Returning Object from Function " << endl;
    Employee e4("Maryam", 50, 80000);
    e4.display();
    cout << endl;

    cout << " Friend Function" << endl;
    compareSalary(e1, e2);
    cout << endl;

    cout << " Shallow vs Deep Copy " << endl;
    Employee e5("Tahreem",30, 40000);
    cout << "Original Employee:" << endl;
    e5.display();

    Employee e6 = e5;  // Deep copy using copy constructor
    cout << "Before modify: " << endl;
    e6.display();

    cout << "After modifying original:" << endl;
    e5.modifyName("Tahreem");
    e5.setSalary(45000);
    e5.display();

    cout << "Deep Copy unchanged:" << endl;
    e6.display();
    cout << endl;

    cout << " Object Returning " << endl;
    Employee e7 = e2.getCopy();  // Return object 

    e7.modifyName("Samara");
    e7.setSalary(55500);

    cout << "Original:" << endl;
    e2.display(); 

    cout << "Copied and Modified:" << endl;
    e7.display();

    cout << " Final Employee Count " << endl;
    Employee::displayTotalEmployees();
    cout << endl;


    delete e3; // free memory

    system("pause");
    return 0;
}