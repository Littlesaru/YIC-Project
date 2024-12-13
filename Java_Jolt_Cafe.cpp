#include <iostream>
#include <vector>
using namespace std;

// Global variable
int security_tax = 10;

class Employee
{
private:
    int employee_ID;
    string employee_name;
    string employee_position;
    string employee_type;
    string start_date;
    double basic_salary;

public:
    // Getter methods
    int getEmployeeID() { return employee_ID; }
    string getName() { return employee_name; }
    string getPosition() { return employee_position; }
    string getEmployeeType() { return employee_type; }
    string getStartDate() { return start_date; }
    double getBasicSalary() { return basic_salary; }

    // Default constructor
    Employee() : employee_ID(0), employee_name(""), employee_position(""), employee_type(""), start_date(""), basic_salary(0) {}

    // Set employee data
    void setData()
    {
        cout << "Enter Employee ID: ";
        cin >> employee_ID;
        cin.ignore(); // Clear input buffer
        cout << "Enter Employee Name: ";
        getline(cin, employee_name);
        cout << "Enter Employee Position (Fulltime- Barista, Cashier, Supervisor (or) Part-time- Cleaner, Kitchen Staff, Waiter, Waitress): ";
        getline(cin, employee_position);
        cout << "Enter Employee Start Date (dd/mm/yy): ";
        cin >> start_date;

        // Set basic salary based on position
        if (employee_position == "Barista")
        {
            basic_salary = 1920;
            employee_type = "fulltime";
        }
        else if (employee_position == "Cashier")
        {
            basic_salary = 1790;
            employee_type = "fulltime";
        }
        else if (employee_position == "Cleaner")
        {
            basic_salary = 1400;
            employee_type = "parttime";
        }
        else if (employee_position == "Kitchen Staff")
        {
            basic_salary = 1850;
            employee_type = "parttime";
        }
        else if (employee_position == "Waiter" || employee_position == "Waitress")
        {
            basic_salary = 1700;
            employee_type = "parttime";
        }
        else if (employee_position == "Supervisor")
        {
            basic_salary = 2400;
            employee_type = "fulltime";
        }
        else
        {
            cout << "Invalid Employee Position" << endl;
            basic_salary = 0; // Reset salary to 0 for invalid position
        }
    }

    void getData()
    {
        cout << "ID : " << employee_ID << endl;
        cout << "Name : " << employee_name << endl;
        cout << "Position : " << employee_position << endl;
        cout << "Type : " << employee_type << endl;
        cout << "Start Date : " << start_date << endl;
        cout << "Basic Salary : " << basic_salary << endl;
    }
};

class FullTime : public Employee
{
private:
    int leave_days;
    double overtime_hours = 0;
    double bonus = 0;
    double overtime_fees = 0;
    double total_amount = 0;
    double tax_salary = 0;
    double net_salary = 0;

public:
    FullTime() : leave_days(0), overtime_hours(0.0) {}

    void setFullTimeData()
    {
        setData(); // Set common data from Employee
        cout << "Enter number of leave days: ";
        cin >> leave_days;
        cout << "Enter overtime hours: ";
        cin >> overtime_hours;
        if (leave_days == 0)
        {
            bonus = 300;
        }
        else if (leave_days == 1)
        {
            bonus = 200;
        }
        else if (leave_days == 2)
        {
            bonus = 100;
        }
        else
        {
            bonus = 0;
        }
    }

    // Calculate total salary
    double calculateFulltimeTotalSalary()
    {
        int salary = getBasicSalary();
        overtime_fees = (((salary / 30) / 8) * overtime_hours) * 2;
        tax_salary = (salary / 100) * 2;

        if (leave_days < 4 && overtime_hours >= 0)
        {
            total_amount = salary + (bonus + overtime_fees);
        }
        else if (leave_days > 4 && overtime_hours > 0)
        {
            total_amount = salary - (bonus + overtime_fees) - (salary / 100) * 1;
        }
        else
        {
            total_amount = salary - (bonus + overtime_fees);
        }
        return total_amount;
    }

    double calculateFulltimeTotalNetSalary()
    {
        if (total_amount == 0) // Ensure total_amount is calculated
            calculateFulltimeTotalSalary();

        net_salary = total_amount - ((total_amount / 100) * 2) - security_tax;
        return net_salary;
    }

    void getFullTimeData()
    {
        getData(); // Get common data from Employee
        cout << "Leave Days: " << leave_days << endl;
        cout << "Overtime Hours: " << overtime_hours << endl;
        cout << "Total Net Amount: " << calculateFulltimeTotalNetSalary() << endl;
        cout << endl;
    }
};

class PartTime : public Employee
{
private:
    double hourly_wage = 0;
    double working_hours = 0;
    double total_amount = 0;

public:
    PartTime() : working_hours(0) {}

    void setParttimeData()
    {
        setData(); // Set common data from Employee
        cout << "Enter working hours (Monthly): ";
        cin >> working_hours;
    }

    double calculateParttimeTotalNetSalary()
    {
        // Calculate hourly wage from basic salary
        double salary = getBasicSalary();
        hourly_wage = (salary / 30) / 8;

        // Calculate total amount
        total_amount = (hourly_wage * working_hours); // Total salary based on working hours
        total_amount -= (total_amount / 100) * 2;     // Deduct 2% income tax
        total_amount -= security_tax;                 // Deduct fixed security tax

        return total_amount;
    }

    void getParttimeData()
    {
        getData(); // Get common data from Employee
        cout << "Working Hours: " << working_hours << endl;
        cout << "Total Net Amount: " << calculateParttimeTotalNetSalary() << endl;
        cout << endl;
    }
};

vector<FullTime> Fulltime_Employees;
vector<PartTime> PartTime_Employees;

int main()
{
    int opt;
    cout << "--------------------------------------------" << endl;
    cout << "*---___ Java_Jolt_Cafe Manager __---*" << endl;
    cout << "--------------------------------------------" << endl;

    while (true)
    {
        cout << "\nMenu" << endl;
        cout << "1. Insert Employee Data \n"
             << "2. Update Employee Data \n"
             << "3. View Fulltime Employees Salary \n"
             << "4. View Parttime Employees Salary \n"
             << "5. View All Employees Salary \n"
             << "6. Exit" << endl;
        cin >> opt;
        cin.ignore();

        switch (opt)
        {
        case 1:
        {
            int n = 0;
            cout << "Enter the number of employees you want to insert: ";
            cin >> n;
            cin.ignore(); // Clear input buffer

            for (int i = 0; i < n; i++)
            {
                cout << "Enter details for Employee " << i + 1 << ":" << endl;
                string employee_type;
                cout << "Which Type Of Employee Data You Want To Insert (fulltime/parttime): ";
                cin >> employee_type;

                if (employee_type == "fulltime")
                {
                    FullTime New_Employee;
                    New_Employee.setFullTimeData();
                    Fulltime_Employees.push_back(New_Employee);
                }
                else if (employee_type == "parttime")
                {
                    PartTime New_Employee;
                    New_Employee.setParttimeData();
                    PartTime_Employees.push_back(New_Employee);
                }
                else
                {
                    cout << "Invalid Employee Type!!!!" << endl;
                }
            }
            break;
        }
         case 2:
        {
            int num;
            string type;
            bool found = false;

            cout << "Enter The Employee Type to Update Data (fulltime/parttime): ";
            cin >> type;

            if (type == "fulltime")
            {
                cout << "Enter Employee ID You Want To Update: ";
                cin >> num;
                for (int i = 0; i < Fulltime_Employees.size(); i++)
                {
                    if (num == Fulltime_Employees[i].getEmployeeID())
                    {
                        cout << "Updating data for Full-Time Employee ID: " << num << endl;
                        Fulltime_Employees[i].setFullTimeData();
                        // Recalculate salary after updating
                        Fulltime_Employees[i].calculateFulltimeTotalSalary();
                        Fulltime_Employees[i].calculateFulltimeTotalNetSalary();
                        found = true;
                        break;
                    }
                }
                if (!found)
                {
                    cout << "No Full-Time Employee found with ID: " << num << endl;
                }
            }
            else if (type == "parttime")
            {
                cout << "Enter Employee ID You Want To Update: ";
                cin >> num;
                for (int i = 0; i < PartTime_Employees.size(); i++)
                {
                    if (num == PartTime_Employees[i].getEmployeeID())
                    {
                        cout << "Updating data for Part-Time Employee ID: " << num << endl;
                        PartTime_Employees[i].setParttimeData();
                        // Recalculate salary after updating
                        PartTime_Employees[i].calculateParttimeTotalNetSalary();
                        found = true;
                        break;
                    }
                }
                if (!found)
                {
                    cout << "No Part-Time Employee found with ID: " << num << endl;
                }
            }
            else
            {
                cout << "Invalid Employee Type! Please enter 'fulltime' or 'parttime'." << endl;
            }

            break;
        }
        case 3:
        {
            if (Fulltime_Employees.empty())
            {
                cout << "No Full-Time Employees Found!" << endl;
            }
            else
            {
                for (int i = 0; i < Fulltime_Employees.size(); i++)
                {
                    cout << "Full Time Employee Data " << i + 1 << ":" << endl;
                    Fulltime_Employees[i].getFullTimeData();
                }
            }
            break;
        }
        case 4:
        {
            if (PartTime_Employees.empty())
            {
                cout << "No Part-Time Employees Found!" << endl;
            }
            else
            {
                for (int i = 0; i < PartTime_Employees.size(); i++)
                {
                    cout << "Part Time Employee Data " << i + 1 << ":" << endl;
                    PartTime_Employees[i].getParttimeData();
                }
            }
            break;
        }
        case 5:
        {
            cout << "Full-Time Employees:" << endl;
            for (int i = 0; i < Fulltime_Employees.size(); i++)
            {
                Fulltime_Employees[i].getFullTimeData();
            }
            cout << "Part-Time Employees:" << endl;
            for (int i = 0; i < PartTime_Employees.size(); i++)
            {
                PartTime_Employees[i].getParttimeData();
            }
            break;
        }
        case 6:
            return 0;
        default:
            cout << "Invalid option, please try again." << endl;
            break;
        }
    }
}
