#include <stdio.h>
#include <assert.h>

// Structures
typedef enum {
    Savings,
    Cheking,
    MoneyMarket,
    CD
} AccountType;

// Functions
void assignInterestRate(AccountType account) {
    double interestRate;
    switch (account) {
        case Savings:
            interestRate = 3.0;
            break;
        case Cheking:
            interestRate = 1.0;
            break;
        case MoneyMarket:
            interestRate = 4.5;
            break;
    }
    printf("Interest rate: %f", interestRate);
}

// Main
int main(int argc, char **argv) {
    assignInterestRate(CD);
}