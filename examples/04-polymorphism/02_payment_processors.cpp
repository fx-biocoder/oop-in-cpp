#include <iostream>
#include <memory>
#include <iomanip>

// Abstract payment processor interface
class PaymentProcessor {
public:
    virtual ~PaymentProcessor() = default;
    
    virtual bool process(double amount) = 0;
    virtual void refund(double amount) = 0;
    virtual const char* getProcessorName() const = 0;
};

// Credit card processor
class CreditCardProcessor : public PaymentProcessor {
public:
    bool process(double amount) override {
        std::cout << "Processing $" << std::fixed << std::setprecision(2) 
                  << amount << " via credit card\n";
        std::cout << "  Connecting to payment gateway...\n";
        std::cout << "  Verifying card details...\n";
        std::cout << "  Transaction approved!\n";
        return true;
    }
    
    void refund(double amount) override {
        std::cout << "Refunding $" << std::fixed << std::setprecision(2) 
                  << amount << " to credit card\n";
    }
    
    const char* getProcessorName() const override {
        return "Credit Card Processor";
    }
};

// PayPal processor
class PayPalProcessor : public PaymentProcessor {
public:
    bool process(double amount) override {
        std::cout << "Processing $" << std::fixed << std::setprecision(2) 
                  << amount << " via PayPal\n";
        std::cout << "  Authenticating PayPal account...\n";
        std::cout << "  Transfer initiated...\n";
        std::cout << "  Transaction completed!\n";
        return true;
    }
    
    void refund(double amount) override {
        std::cout << "Refunding $" << std::fixed << std::setprecision(2) 
                  << amount << " to PayPal account\n";
    }
    
    const char* getProcessorName() const override {
        return "PayPal Processor";
    }
};

// Apple Pay processor
class ApplePayProcessor : public PaymentProcessor {
public:
    bool process(double amount) override {
        std::cout << "Processing $" << std::fixed << std::setprecision(2) 
                  << amount << " via Apple Pay\n";
        std::cout << "  Reading device biometric...\n";
        std::cout << "  Sending secure payment token...\n";
        std::cout << "  Transaction authorized!\n";
        return true;
    }
    
    void refund(double amount) override {
        std::cout << "Refunding $" << std::fixed << std::setprecision(2) 
                  << amount << " via Apple Pay\n";
    }
    
    const char* getProcessorName() const override {
        return "Apple Pay Processor";
    }
};

// Generic checkout function - works with ANY payment processor
void checkoutOrder(PaymentProcessor& processor, double cartTotal) {
    std::cout << "\n=== Checkout Order ===\n";
    std::cout << "Using: " << processor.getProcessorName() << std::endl;
    std::cout << "Total: $" << std::fixed << std::setprecision(2) << cartTotal << std::endl;
    std::cout << "\nProcessing payment...\n";
    
    if (processor.process(cartTotal)) {
        std::cout << "✓ Order completed successfully!\n";
    } else {
        std::cout << "✗ Payment failed\n";
    }
}

int main() {
    double orderTotal = 99.99;
    
    // Create different payment processors
    CreditCardProcessor creditCard;
    PayPalProcessor paypal;
    ApplePayProcessor applePay;
    
    // Same checkout function, different payment methods
    checkoutOrder(creditCard, orderTotal);
    checkoutOrder(paypal, orderTotal);
    checkoutOrder(applePay, orderTotal);
    
    // Using pointers for dynamic selection
    std::cout << "\n\n=== Dynamic Processor Selection ===\n";
    
    std::unique_ptr<PaymentProcessor> processor;
    
    int choice = 2;  // User selected PayPal
    
    switch (choice) {
        case 1:
            processor = std::make_unique<CreditCardProcessor>();
            break;
        case 2:
            processor = std::make_unique<PayPalProcessor>();
            break;
        case 3:
            processor = std::make_unique<ApplePayProcessor>();
            break;
        default:
            processor = std::make_unique<CreditCardProcessor>();
    }
    
    if (processor) {
        checkoutOrder(*processor, orderTotal);
    }
    
    return 0;
}
