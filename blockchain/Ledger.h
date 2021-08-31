//
// Created by SLIMS-PC on 5/23/2021.
//

#ifndef SLIMCOIN_LEDGER_H
#define SLIMCOIN_LEDGER_H

#include <iostream>
#include <vector>
#include "Transaction.h"

using namespace std;


class Ledger {
public:
    Ledger();
    Ledger(const Ledger&);

    Transaction     get(int) const;
    void            append_transaction(const Transaction&);
    unsigned int    ledger_len() const;
    string          get_string();
    unsigned int    get_size() const;
private:
    vector<Transaction> _transactions;
};


#endif //SLIMCOIN_LEDGER_H
