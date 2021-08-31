//
// Created by SLIMS-PC on 5/23/2021.
//

#ifndef SLIMCOIN_TRANSACTION_H
#define SLIMCOIN_TRANSACTION_H

#include <iostream>
#include <ctime>
#include <string>

using namespace std;

class Transaction {
public:
    Transaction(string sender, string receiver, int amount);
    Transaction(const Transaction& transaction);

    string          sender();
    string          receiver();
    int             amount() const;
    string          get_time();
    string          get_string();
    unsigned int    get_size() const;
private:
    string  _sender;
    string  _receiver;
    int     _amount;
    time_t  _transaction_time;

};


#endif //SLIMCOIN_TRANSACTION_H
