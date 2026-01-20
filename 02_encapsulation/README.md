# Encapsulation

## 1. Introduction

Encapsulation is the bundling of data and methods together with controlled access. It establishes clear boundaries between what's internal (hidden) and what's external (exposed).

**Core principle:** Private data + public interface = controlled access

In C++, three access modifiers control visibility:
- **`private`:** Only accessible within the class itself (default for classes)
- **`public`:** Accessible from anywhere
- **`protected`:** Accessible within the class and derived classes

This allows us to:
- Hide implementation details
- Control how data is accessed and modified
- Enforce invariants (rules that must always be true)
- Change internals without affecting external code

## 2. Encapsulation in Practice

Let's explore encapsulation through a realistic example of a bank account:

```cpp
#include <iostream>
#include <string>
#include <vector>

class BankAccount {
private:
    // Private member variables - hidden implementation details
    std::string accountNumber;
    std::string accountHolder;
    double balance;
    std::vector<std::string> transactionHistory;
    
    // Private helper method - used internally only
    void recordTransaction(const std::string& transaction) {
        transactionHistory.push_back(transaction);
    }
    
public:
    // Constructor - initializes the account
    BankAccount(const std::string& number, const std::string& holder, double initialBalance)
        : accountNumber(number), accountHolder(holder), balance(initialBalance) {
        recordTransaction("Account opened with balance: $" + std::to_string(initialBalance));
    }
    
    // Destructor
    ~BankAccount() = default;
    
    // Public getters - read-only access to private data
    const std::string& getAccountNumber() const {
        return accountNumber;
    }
    
    const std::string& getAccountHolder() const {
        return accountHolder;
    }
    
    double getBalance() const {
        return balance;
    }
    
    // Public methods - controlled access with validation
    bool deposit(double amount) {
        if (amount <= 0) {
            std::cout << "Error: Deposit amount must be positive\n";
            return false;
        }
        balance += amount;
        recordTransaction("Deposited: $" + std::to_string(amount));
        std::cout << "Deposit successful. New balance: $" << balance << std::endl;
        return true;
    }
    
    bool withdraw(double amount) {
        if (amount <= 0) {
            std::cout << "Error: Withdrawal amount must be positive\n";
            return false;
        }
        if (amount > balance) {
            std::cout << "Error: Insufficient funds\n";
            return false;
        }
        balance -= amount;
        recordTransaction("Withdrew: $" + std::to_string(amount));
        std::cout << "Withdrawal successful. New balance: $" << balance << std::endl;
        return true;
    }
    
    void displayHistory() const {
        std::cout << "\nTransaction History for " << accountHolder << ":\n";
        for (const auto& transaction : transactionHistory) {
            std::cout << "  - " << transaction << std::endl;
        }
    }
};

int main() {
    BankAccount account("123456", "Alice", 1000);
    
    // Users can read balance
    std::cout << "Initial balance: $" << account.getBalance() << std::endl;
    
    // Users can deposit (with validation)
    account.deposit(500);
    account.withdraw(200);
    account.withdraw(2000);  // Will fail - insufficient funds
    
    // Users cannot directly modify balance
    // account.balance = -1000;  // ERROR: 'balance' is private
    
    // Users cannot access transaction history directly
    // account.transactionHistory.push_back("Hacked!");  // ERROR: private
    
    account.displayHistory();
    
    return 0;
}
```

**Output:**
```
Initial balance: $1000
Deposit successful. New balance: $1500
Withdrawal successful. New balance: $1300
Error: Insufficient funds
Transaction History for Alice:
  - Account opened with balance: $1000.000000
  - Deposited: $500.000000
  - Withdrew: $200.000000
```

**Key benefits demonstrated:**
- ✅ Balance can't be set to negative values
- ✅ Transactions are automatically recorded
- ✅ Internal logic is hidden - only the interface matters
- ✅ We could change how transactions are stored without affecting users

## 3. Access Modifiers and Class Hierarchy

Understanding how access modifiers interact with inheritance is crucial:

```cpp
#include <iostream>

class Animal {
private:
    std::string privateSecret = "Internal data";  // No access from derived classes
    
protected:
    std::string protectedInfo = "Can access from derived classes";
    
public:
    std::string publicInfo = "Can access from anywhere";
    
    void publicMethod() const {
        std::cout << "Public method\n";
    }
    
protected:
    void protectedMethod() const {
        std::cout << "Protected method (used by derived classes)\n";
    }
};

class Dog : public Animal {
public:
    void showAccess() const {
        // Can access protected members
        std::cout << protectedInfo << std::endl;
        protectedMethod();
        
        // Can access public members
        std::cout << publicInfo << std::endl;
        publicMethod();
        
        // Cannot access private members
        // std::cout << privateSecret << std::endl;  // COMPILER ERROR
    }
};

int main() {
    Animal animal;
    
    // Can access public
    std::cout << animal.publicInfo << std::endl;
    animal.publicMethod();
    
    // Cannot access protected or private
    // std::cout << animal.protectedInfo << std::endl;  // ERROR
    // std::cout << animal.privateSecret << std::endl;  // ERROR
    
    Dog dog;
    dog.showAccess();
    
    return 0;
}
```

### Access Modifier Summary

| Member Type | Class | Derived Classes | Outside |
|-------------|-------|-----------------|---------|
| `private` | ✅ | ❌ | ❌ |
| `protected` | ✅ | ✅ | ❌ |
| `public` | ✅ | ✅ | ✅ |

**Rule of thumb:** 
- **Private:** Implementation details - hide from everyone
- **Protected:** For derived classes - shared implementation
- **Public:** The interface - what users interact with


---

**Article Updated:** January 2026 | Licensed under CC BY-NC-SA 4.0
