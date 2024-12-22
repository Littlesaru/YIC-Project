#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <limits> // For numeric_limits
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
    // Virtual destructor for polymorphism
    virtual ~Employee() {}

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

        // Loop until a valid employee position is entered
        while (true)
        {
            cout << "Enter Employee Position (Fulltime- Barista, Cashier, Supervisor (or) Part-time- Cleaner, Kitchen Staff, Waiter, Waitress): ";
            getline(cin, employee_position);

            if (employee_position == "Barista" || employee_position == "barista")
            {
                basic_salary = 1920;
                employee_type = "fulltime";
                break;
            }
            else if (employee_position == "Cashier" || employee_position == "cashier")
            {
                basic_salary = 1790;
                employee_type = "fulltime";
                break;
            }
            else if (employee_position == "Cleaner" || employee_position == "cleaner")
            {
                basic_salary = 1400;
                employee_type = "parttime";
                break;
            }
            else if (employee_position == "Kitchen Staff" || employee_position == "kitchen staff")
            {
                basic_salary = 1850;
                employee_type = "parttime";
                break;
            }
            else if (employee_position == "Waiter" || employee_position == "waiter" || employee_position == "Waitress" || employee_position == "waitress")
            {
                basic_salary = 1700;
                employee_type = "parttime";
                break;
            }
            else if (employee_position == "Supervisor" || employee_position == "supervisor")
            {
                basic_salary = 2400;
                employee_type = "fulltime";
                break;
            }
            else
            {
                cout << "Invalid Employee Position. Please try again." << endl;
            }
        }

        cout << "Enter Employee Start Date (dd/mm/yy): ";
        cin >> start_date;
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

        // Calculate bonus based on leave days
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

        // Explicitly calculate total salary to update dependent fields
        calculateFulltimeTotalSalary();
    }

    // Calculate total salary
    double calculateFulltimeTotalSalary()
    {
        double salary = getBasicSalary();

        // Calculate overtime fees
        overtime_fees = (((salary / 30) / 8) * overtime_hours) * 2;

        // Calculate total amount considering leave days and overtime
        if (leave_days < 4 && overtime_hours >= 0)
        {
            total_amount = salary + bonus + overtime_fees;
            // Calculate tax on salary
            tax_salary = (total_amount / 100) * 2;
        }
        else if (leave_days > 4 && overtime_hours > 0)
        {
            total_amount = salary - ((salary / 100) * 1) + overtime_fees - bonus;
            // Calculate tax on salary
            tax_salary = (total_amount / 100) * 2;
        }
        else
        {
            total_amount = salary - bonus + overtime_fees;
            // Calculate tax on salary
            tax_salary = (total_amount / 100) * 2;
        }

        return total_amount;
    }

    double calculateFulltimeTotalNetSalary()
    {
        if (total_amount == 0) // Ensure total_amount is calculated
            calculateFulltimeTotalSalary();

        // Calculate net salary after deductions
        net_salary = total_amount - ((total_amount / 100) * 2) - security_tax;
        return net_salary;
    }

    // setter
    double getOvertimeHours() { return overtime_hours; }
    double getOvertimeFees() { return overtime_fees; }
    double getTaxSalary() { return tax_salary; }
    double getTotalAmount() { return total_amount; }
    double getNetSalary() { return net_salary; }
    int getLeaveDay() { return leave_days; }
    double getBonus() { return bonus; }
};

class PartTime : public Employee
{
private:
    double hourly_wage = 0;
    double working_hours = 0;
    double total_amount = 0;
    double tax_deduction = 0;
    double net_salary = 0;

public:
    PartTime() : working_hours(0) {}

    void setParttimeData()
    {
        setData(); // Set common data from Employee
        cout << "Enter working hours (Monthly): ";
        cin >> working_hours;

        // Calculate salary components after setting data
        calculateParttimeTotalNetSalary();
    }

    double calculateParttimeTotalNetSalary()
    {
        // Calculate hourly wage from basic salary
        double salary = getBasicSalary();
        hourly_wage = (salary / 30) / 8;

        // Calculate gross total amount based on working hours
        total_amount = hourly_wage * working_hours;

        // Calculate tax deduction (2% of total amount)
        tax_deduction = (total_amount / 100) * 2;

        // Calculate net salary after tax and security deduction
        net_salary = total_amount - tax_deduction - security_tax;

        return net_salary;
    }

    // New getters for detailed data
    double getWorkingHours() { return working_hours; }
    double getHourlyWage() { return hourly_wage; }
    double getPartTaxDeduction() { return tax_deduction; }
    double getPartNetSalary() { return net_salary; }
    double getPartTotalAmount() { return total_amount; }
};

// Global vectors to store employees
vector<FullTime> Fulltime_Employees;
vector<PartTime> PartTime_Employees;

int main()
{
    int opt = 0; // Initialize opt to avoid undefined behavior
    cout << "--------------------------------------------" << endl;
    cout << "*---___ Java_Jolt_Cafe Manager __---*" << endl;
    cout << "--------------------------------------------" << endl;
    int fulltime_employee = 0, parttime_employee = 0;
    double fulltime_employee_salary = 0, parttime_employee_salary = 0, monthly_total = 0;
    while (opt != 6)
    {
        cout << "\nMenu" << endl;
        cout << "1. Insert Employee Data \n"
             << "2. Update Employee Data \n"
             << "3. View Fulltime Employees Salary \n"
             << "4. View Parttime Employees Salary \n"
             << "5. View All Employees Salary (Sorted by Net Salary) \n"
             << "6. Exit" << endl;
        cout << "Choose an option: ";
        cin >> opt;

        // Clear invalid input
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number between 1 and 6." << endl;
            continue;
        }

        cin.ignore(); // Clear input buffer

        switch (opt)
        {
        case 1:
        {
            int n;
            cout << "Enter the number of employees you want to insert: ";
            cin >> n;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            for (int i = 0; i < n; i++)
            {
                cout << "Enter details for Employee " << i + 1 << ":" << endl;
                string employee_type;
                cout << "Which Type Of Employee Data You Want To Insert (fulltime/parttime): ";
                cin >> employee_type;
                cin.ignore(); // Clear buffer after reading employee_type

                if (employee_type == "fulltime")
                {
                    FullTime New_Employee;
                    New_Employee.setFullTimeData();
                    cout << endl;
                    Fulltime_Employees.push_back(New_Employee);
                    fulltime_employee++;
                    fulltime_employee_salary += New_Employee.calculateFulltimeTotalNetSalary();
                }
                else if (employee_type == "parttime")
                {
                    PartTime New_Employee;
                    New_Employee.setParttimeData();
                    cout << endl;
                    PartTime_Employees.push_back(New_Employee);
                    parttime_employee++;
                    parttime_employee_salary += New_Employee.calculateParttimeTotalNetSalary();
                }
                else
                {
                    cout << "Invalid Employee Type!!!!" << endl;
                }
            }

            monthly_total = fulltime_employee_salary + parttime_employee_salary;
            cout << "!!Employee Data Add Successful!!" << endl;
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
                cout << "***** ( Full-Time Employees ) *****" << endl;

                // Table Headers
                cout << left << setw(10) << "ID"
                     << setw(10) << "Name"
                     << setw(15) << "Position"
                     << setw(12) << "Start Date"
                     << setw(12) << "Basic Sal."
                     << setw(12) << "Leave Days"
                     << setw(12) << "Overtime Hrs"
                     << setw(12) << "Overtime Fee"
                     << setw(12) << "Bonus"
                     << setw(12) << "Tax Ded."
                     << setw(12) << "Sec. Ded."
                     << setw(12) << "Total Amt"
                     << setw(12) << "Net Salary" << endl;

                // Table Rows
                for (int i = 0; i < Fulltime_Employees.size(); i++)
                {
                    Fulltime_Employees[i].calculateFulltimeTotalSalary();
                    Fulltime_Employees[i].calculateFulltimeTotalNetSalary();

                    cout << left << setw(10) << Fulltime_Employees[i].getEmployeeID()
                         << setw(10) << Fulltime_Employees[i].getName()
                         << setw(15) << Fulltime_Employees[i].getPosition()
                         << setw(12) << Fulltime_Employees[i].getStartDate()
                         << setw(12) << fixed << setprecision(2) << Fulltime_Employees[i].getBasicSalary()
                         << setw(12) << Fulltime_Employees[i].getLeaveDay()
                         << setw(12) << fixed << setprecision(2) << Fulltime_Employees[i].getOvertimeHours()
                         << setw(12) << fixed << setprecision(2) << Fulltime_Employees[i].getOvertimeFees()
                         << setw(12) << fixed << setprecision(3) << Fulltime_Employees[i].getBonus()
                         << setw(12) << fixed << setprecision(2) << Fulltime_Employees[i].getTaxSalary()
                         << setw(12) << fixed << setprecision(2) << security_tax
                         << setw(12) << fixed << setprecision(2) << Fulltime_Employees[i].getTotalAmount()
                         << setw(12) << fixed << setprecision(2) << Fulltime_Employees[i].getNetSalary() << endl;
                }

                cout << "***********************************" << endl;
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
                cout << "***** ( Part-Time Employees ) *****" << endl;
                // Table Header
                cout << left << setw(10) << "ID"
                     << setw(10) << "Name"
                     << setw(15) << "Position"
                     << setw(12) << "Start Date"
                     << setw(15) << "Basic Salary"
                     << setw(12) << "Hours"
                     << setw(12) << "Hourly Wage"
                     << setw(12) << "Total Amt"
                     << setw(12) << "Tax Ded."
                     << setw(12) << "Sec. Ded."
                     << setw(12) << "Net Amount" << endl;

                // Table Rows
                for (int i = 0; i < PartTime_Employees.size(); i++)
                {
                    PartTime_Employees[i].calculateParttimeTotalNetSalary();

                    cout << left << setw(10) << PartTime_Employees[i].getEmployeeID()
                         << setw(10) << PartTime_Employees[i].getName()
                         << setw(15) << PartTime_Employees[i].getPosition()
                         << setw(12) << PartTime_Employees[i].getStartDate()
                         << setw(15) << fixed << setprecision(2) << PartTime_Employees[i].getBasicSalary()
                         << setw(12) << fixed << setprecision(2) << PartTime_Employees[i].getWorkingHours()
                         << setw(12) << fixed << setprecision(2) << PartTime_Employees[i].getHourlyWage()
                         << setw(12) << fixed << setprecision(2) << PartTime_Employees[i].getPartTotalAmount()
                         << setw(12) << fixed << setprecision(2) << PartTime_Employees[i].getPartTaxDeduction()
                         << setw(12) << fixed << setprecision(2) << security_tax
                         << setw(12) << fixed << setprecision(2) << PartTime_Employees[i].getPartNetSalary() << endl;
                }

                cout << "***********************************" << endl;
            }
            break;
        }
        case 5:
        {
            // Struct to hold employee details for sorting
            struct EmployeeInfo
            {
                string type;                 // "FullTime" or "PartTime"
                double net_salary;           // Net salary for sorting
                int employee_id;             // Employee ID
                string employee_name;        // Employee Name
                Employee *employee_instance; // Pointer to original object
            };

            vector<EmployeeInfo> all_employees;

            // Collect full-time employees
            for (int i = 0; i < Fulltime_Employees.size(); i++)
            {
                EmployeeInfo info;
                info.type = "FullTime";
                info.net_salary = Fulltime_Employees[i].calculateFulltimeTotalNetSalary();
                info.employee_id = Fulltime_Employees[i].getEmployeeID();
                info.employee_name = Fulltime_Employees[i].getName();
                info.employee_instance = &Fulltime_Employees[i];
                all_employees.push_back(info);
            }

            // Collect part-time employees
            for (int i = 0; i < PartTime_Employees.size(); i++)
            {
                EmployeeInfo info;
                info.type = "PartTime";
                info.net_salary = PartTime_Employees[i].calculateParttimeTotalNetSalary();
                info.employee_id = PartTime_Employees[i].getEmployeeID();
                info.employee_name = PartTime_Employees[i].getName();
                info.employee_instance = &PartTime_Employees[i];
                all_employees.push_back(info);
            }

            // Implement insertion sort by net salary in descending order
            for (size_t i = 1; i < all_employees.size(); i++)
            {
                EmployeeInfo key = all_employees[i];
                int j = i - 1;

                // Move elements of all_employees[0..i-1], that are less than key.net_salary,
                // to one position ahead of their current position
                while (j >= 0 && all_employees[j].net_salary < key.net_salary)
                {
                    all_employees[j + 1] = all_employees[j];
                    j--;
                }
                all_employees[j + 1] = key;
            }

            // Display sorted employees
            if (all_employees.empty())
            {
                cout << "No employees found to display!" << endl;
                break;
            }

            // Table Headers
            cout << "\n***** Employees Sorted by Total Net Salary (High to Low) *****\n";
            cout << left << setw(5) << "No"
                 << setw(10) << "ID"
                 << setw(12) << "Name"
                 << setw(12) << "Position"
                 << setw(12) << "Type"
                 << setw(12) << "Net Salary"
                 << setw(12) << "Details" << endl;

            // Table Rows
            for (int i = 0; i < all_employees.size(); i++)
            {
                cout << left << setw(5) << i + 1
                     << setw(10) << all_employees[i].employee_id
                     << setw(12) << all_employees[i].employee_name;

                // Determine type and display additional details
                if (all_employees[i].type == "FullTime")
                {
                    FullTime *emp = dynamic_cast<FullTime *>(all_employees[i].employee_instance);
                    cout << setw(12) << emp->getPosition()
                         << setw(12) << "FullTime"
                         << setw(12) << fixed << setprecision(2) << emp->getNetSalary()
                         << "Leave: " << emp->getLeaveDay()
                         << ", Overtime: " << emp->getOvertimeHours()
                         << ", Bonus: " << emp->getBonus();
                }
                else if (all_employees[i].type == "PartTime")
                {
                    PartTime *emp = dynamic_cast<PartTime *>(all_employees[i].employee_instance);
                    cout << setw(12) << emp->getPosition()
                         << setw(12) << "PartTime"
                         << setw(12) << fixed << setprecision(2) << emp->getPartNetSalary()
                         << "Hours: " << emp->getWorkingHours()
                         << ", Wage: " << emp->getHourlyWage();
                }
                cout << endl;
            }

            cout << "***************************************************************" << endl;
            cout << " Monthly Fulltime Salary Cost " << endl;
            cout << "------------------------------------" << endl;
            cout << " Total Fulltime Employee : " << fulltime_employee << endl;
            cout << " Total Fulltime Monthly Salary Cost : " << fulltime_employee_salary << endl;

            cout << " Monthly Parttime Salary Cost " << endl;
            cout << "-------------------------------------" << endl;
            cout << " Total Parttime Employee : " << parttime_employee << endl;
            cout << " Total Parrttime Monthly Salary Cost : " << parttime_employee_salary << endl;
            cout << "***************************************************************" << endl;
            cout << "Total Monthly Salary of All Employee : " << monthly_total << endl;
            cout << "***************************************************************" << endl;
            break;
        }
        case 6:
            cout << "Exiting program. Goodbye!" << endl;
            return 0;
        default:
            cout << "Invalid option, please try again." << endl;
            break;
        }
    }
}
