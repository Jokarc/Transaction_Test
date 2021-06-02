#include <iostream>
#include "User.h"
#include "Customer.h"
#include "Merchant.h"
#include "Process.h"
using namespace std;

int main() {
    int Logged = 0, op = 0;
    Process process1;
    User *CurrentUser = NULL;
    Customer CurrentCustomer;
    Merchant CurrentMerchant;
    process1.work(CurrentUser, Logged, CurrentCustomer, CurrentMerchant);
    delete CurrentUser;
    return 0;
}
