#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

// Example: Bank account with proper encapsulation
class BankAccount {
private:
    // Private member variables
    std::string accountNumber;
    std::string accountHolder;
    double balance;
    std::vector<std::string> transactionHistory;
    
    // Private helper method
    void recordTransaction(const std::string& description) {
        transactionHistory.push_back(description);
    }
    
public:
    // Constructor
    BankAccount(const std::string& accountNumber, 
                const std::string& accountHolder,
                double initialBalance)
        : accountNumber(accountNumber),
          accountHolder(accountHolder),
          balance(initialBalance) {
        recordTransaction("Account opened with initial balance: $" + 
                         std::to_string(initialBalance));
    }
    
    // Destructor
    ~BankAccount() = default;
    
    // Getters - read-only access
    const std::string& getAccountNumber() const {
        return accountNumber;
    }
    
    const std::string& getAccountHolder() const {
        return accountHolder;
    }
    
    double getBalance() const {
        return balance;
    }
    
    // Public methods with validation
    bool deposit(double amount) {
        if (amount <= 0) {
            std::cout << "Error: Deposit amount must be positive\n";
            return false;
        }
        balance += amount;
        recordTransaction("Deposited: $" + std::to_string(amount));
        std::cout << "Deposit successful. New balance: $" 
                  << std::fixed << std::setprecision(2) << balance << std::endl;
        return true;
    }
    
    bool withdraw(double amount) {
        if (amount <= 0) {
            std::cout << "Error: Withdrawal amount must be positive\n";
            return false;
        }
        if (amount > balance) {
            std::cout << "Error: Insufficient funds. Available: $" 
                      << std::fixed << std::setprecision(2) << balance << std::endl;
            return false;
        }
        balance -= amount;
        recordTransaction("Withdrew: $" + std::to_string(amount));
        std::cout << "Withdrawal successful. New balance: $" 
                  << std::fixed << std::setprecision(2) << balance << std::endl;
        return true;
    }
    
    void displayHistory() const {
        std::cout << "\n=== Transaction History for " << accountHolder << " ===\n";
        if (transactionHistory.empty()) {
            std::cout << "No transactions\n";
            return;
        }
        for (size_t i = 0; i < transactionHistory.size(); ++i) {
            std::cout << (i + 1) << ". " << transactionHistory[i] << std::endl;
        }
    }
};

int main() {
    BankAccount account("ACC-12345", "Alice Smith", 1000.00);
    
    std::cout << "Account Holder: " << account.getAccountHolder() << std::endl;
    std::cout << "Account Number: " << account.getAccountNumber() << std::endl;
    std::cout << "Initial Balance: $" << std::fixed << std::setprecision(2) 
              << account.getBalance() << std::endl;
    
    std::cout << "\n--- Transactions ---\n";
    account.deposit(500.00);
    account.withdraw(200.00);
    account.withdraw(2000.00);  // Will fail
    account.deposit(300.00);
    
    account.displayHistory();
    
    std::cout << "\nFinal Balance: $" << std::fixed << std::setprecision(2) 
              << account.getBalance() << std::endl;
    
    // These would cause compiler errors (private members):
    // account.balance = -1000;  // ERROR
    // account.transactionHistory.clear();  // ERROR
    
    return 0;
}
