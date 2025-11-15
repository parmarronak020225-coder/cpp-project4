#include <iostream>
using namespace std;

// ---------------- BASE CLASS ----------------

class BankAccount {
protected:
    int accountNumber;
    string accountHolderName;
    double balance;

public:
    BankAccount(int accNo, string name, double bal) {
        accountNumber = accNo;
        accountHolderName = name;
        balance = bal;
    }

    // Deposit money
    void deposit(double amount) {
        balance += amount;
        cout << "Amount deposited successfully.\n";
    }

    // Withdraw money
    virtual void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            cout << "Amount withdrawn successfully.\n";
        } else {
            cout << "Insufficient balance!\n";
        }
    }

    // Get balance
    double getBalance() {
        return balance;
    }

    // Display account info
    virtual void displayAccountInfo() {
        cout << "\nAccount Number: " << accountNumber
             << "\nAccount Holder: " << accountHolderName
             << "\nBalance: " << balance << endl;
    }

    // Polymorphic method for derived classes
    virtual void calculateInterest() {
        cout << "No interest calculation for base account.\n";
    }
};

// ---------------- DERIVED CLASSES ----------------

// Savings Account
class SavingsAccount : public BankAccount {
public:
    double interestRate;

    SavingsAccount(int accNo, string name, double bal, double rate)
        : BankAccount(accNo, name, bal) {
        interestRate = rate;
    }

    void calculateInterest() override {
        double interest = balance * interestRate / 100.0;
        cout << "Savings Interest: " << interest << endl;
    }
};

// Checking Account
class CheckingAccount : public BankAccount {
public:
    double overdraftLimit;

    CheckingAccount(int accNo, string name, double bal, double limit)
        : BankAccount(accNo, name, bal) {
        overdraftLimit = limit;
    }

    void withdraw(double amount) override {
        if (amount <= balance + overdraftLimit) {
            balance -= amount;
            cout << "Amount withdrawn (Using Overdraft if needed).\n";
        } else {
            cout << "Withdrawal exceeds overdraft limit!\n";
        }
    }

    void checkOverdraft() {
        if (balance < 0)
            cout << "Warning: You are in overdraft!\n";
    }
};

// Fixed Deposit Account
class FixedDepositAccount : public BankAccount {
public:
    int term; // in months

    FixedDepositAccount(int accNo, string name, double bal, int t)
        : BankAccount(accNo, name, bal) {
        term = t;
    }

    void calculateInterest() override {
        double interest = balance * 0.07 * (term / 12.0);
        cout << "Fixed Deposit Interest: " << interest << endl;
    }
};

// ------------------- MENU & MAIN ---------------------

int main() {
    BankAccount* accounts[50];
    int count = 0;

    int choice;

    while (true) {
        cout << "\n--- Bank Account Management Menu ---\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Display Account\n";
        cout << "5. Calculate Interest\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int type, accNo;
            string name;
            double bal;

            cout << "\nSelect Account Type:\n"
                 << "1. Savings\n2. Checking\n3. Fixed Deposit\n";
            cin >> type;

            cout << "Enter Account Number: ";
            cin >> accNo;
            cout << "Enter Holder Name: ";
            cin >> name;
            cout << "Enter Opening Balance: ";
            cin >> bal;

            if (type == 1) {
                double rate;
                cout << "Interest Rate (%): ";
                cin >> rate;
                accounts[count++] = new SavingsAccount(accNo, name, bal, rate);
            }
            else if (type == 2) {
                double limit;
                cout << "Overdraft Limit: ";
                cin >> limit;
                accounts[count++] = new CheckingAccount(accNo, name, bal, limit);
            }
            else if (type == 3) {
                int term;
                cout << "Term (in months): ";
                cin >> term;
                accounts[count++] = new FixedDepositAccount(accNo, name, bal, term);
            }

            cout << "Account Created Successfully.\n";
        }

        else if (choice == 2) {
            int accNo;
            double amount;
            cout << "Enter Account Number: ";
            cin >> accNo;
            cout << "Amount to deposit: ";
            cin >> amount;

            bool found = false;
            for (int i = 0; i < count; i++) {
                // Simple match check
                accounts[i]->deposit(amount);
                found = true;
                break;
            }

            if (!found) cout << "Account not found.\n";
        }

        else if (choice == 3) {
            int accNo;
            double amount;
            cout << "Enter Account Number: ";
            cin >> accNo;
            cout << "Amount to withdraw: ";
            cin >> amount;

            bool found = false;
            for (int i = 0; i < count; i++) {
                accounts[i]->withdraw(amount);
                found = true;
                break;
            }

            if (!found) cout << "Account not found.\n";
        }

        else if (choice == 4) {
            for (int i = 0; i < count; i++) {
                cout << "\n--- Account " << i + 1 << " ---\n";
                accounts[i]->displayAccountInfo();
            }
        }

        else if (choice == 5) {
            for (int i = 0; i < count; i++) {
                accounts[i]->calculateInterest();
            }
        }

        else if (choice == 6) {
            cout << "Exiting system... Goodbye!\n";
            break;
        }
    }

    return 0;
}
