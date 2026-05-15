#include<bits/stdc++.h>
using namespace std;

class Account{
    double amount;
    string type_of_Account;
    public:
    Account(double amount, string type_of_Account){
        this->amount = amount;
        this->type_of_Account = type_of_Account;
    }

    double getAmount()
    {
        return this->amount;
    }

    void setAmount(double amount)
    {
        this->amount = amount;
    }
};

class SavingsAccount: public Account{
    vector<string,double> transactions;
    public:
    SavingsAccount(double amount, string type_of_Account): Account(amount, type_of_Account){}

    double checkBalance(Account &acc)
    {
        return acc.getAmount();
    }

    void deposit(double amount, Account &acc)
    {
        acc.setAmount(acc.getAmount() + amount);
        transactions.push_back({"Deposit", amount});
    }

    int withdraw(double amount , Account &acc)
    {
        if(acc.getAmount()<amount)
        {
            cout<<"Insufficent Balance"<<endl;
            return -1;
        }

        acc.setAmount(acc.getAmount() - amount);
        transactions.push_back({"Withdraw", amount});
        return 0;
    }
        
    double interest(double rate=5, int time, Account &acc)
    {
        double interest = (acc.getAmount() * rate * time) / 100;
        acc.setAmount(acc.getAmount() + interest);
        transactions.push_back({"Interest", interest});
        return interest;
    }

};



class CurrentAccount: public Account{
    vector<string,double> transactions;
    public:
    CurrentAccount(double amount, string type_of_Account): Account(amount, type_of_Account){}
    
    double checkBalance(Account &acc)
    {
        return acc.getAmount();
    }

    void deposit(double amount, Account &acc)
    {
        acc.setAmount(acc.getAmount() + amount);
        transactions.push_back({"Deposit", amount});
    }

    int withdraw(double amount , Account &acc)
    {
        if(acc.getAmount()<amount)
        {
            cout<<"Insufficent Balance"<<endl;
            return -1;
        }

        acc.setAmount(acc.getAmount() - amount);
        transactions.push_back({"Withdraw", amount});
        return 0;
    }

};
