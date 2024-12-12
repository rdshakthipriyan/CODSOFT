#include <iostream>

using namespace std;

class Calculator {
public:
    
    double add(double x, double y) {
        return x + y;
    }

    
    double subtract(double x, double y) {
        return x - y;
    }

    
    double multiply(double x, double y) {
        return x * y;
    }


    double divide(double x, double y) {
        if (y == 0) {
            return -1; 
        }
        return x / y;
    }
};

int main() {
    double num1, num2;
    int choice;
    Calculator calc; 

    cout << "Welcome to the C++ Calculator!" << endl;
    cout << "Select an operation:" << endl;
    cout << "1. Add" << endl;
    cout << "2. Subtract" << endl;
    cout << "3. Multiply" << endl;
    cout << "4. Divide" << endl;
    cout << "Enter the number of the operation (1/2/3/4): ";
    cin >> choice;

    if (choice < 1 || choice > 4) {
        cout << "Invalid input! Please select a valid operation." << endl;
        return 1; 
    }

    cout << "Enter the first number: ";
    cin >> num1;
    cout << "Enter the second number: ";
    cin >> num2;

    // Perform the chosen operation
    if (choice == 1) {
        cout << "The result of " << num1 << " + " << num2 << " is: " << calc.add(num1, num2) << endl;
    }
    else if (choice == 2) {
        cout << "The result of " << num1 << " - " << num2 << " is: " << calc.subtract(num1, num2) << endl;
    }
    else if (choice == 3) {
        cout << "The result of " << num1 << " * " << num2 << " is: " << calc.multiply(num1, num2) << endl;
    }
    else if (choice == 4) {
        
        double result = calc.divide(num1, num2);
        if (result == -1) {
            cout << "Error! Division by zero." << endl;
        } else {
            cout << "The result of " << num1 << " / " << num2 << " is: " << result << endl;
        }
    }

    return 0;
}
