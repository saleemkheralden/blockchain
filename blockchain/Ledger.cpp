//
// Created by SLIMS-PC on 5/23/2021.
//

#include "Ledger.h"

Ledger::Ledger() {
    this->_transactions = vector<Transaction>();
}

Ledger::Ledger(const Ledger& ledger) {
    for (int i = 0; i < ledger.ledger_len(); i++) {
        this->append_transaction(Transaction(ledger.get(i)));
    }
}

Transaction Ledger::get(int index) const {
    return this->_transactions.at(index);
}

void Ledger::append_transaction(const Transaction& transaction) {
    this->_transactions.push_back(transaction);
}

unsigned int Ledger::ledger_len() const {
    return this->_transactions.size();
}

string Ledger::get_string() {
    string ret = "";
    unsigned int _size = this->_transactions.size();
    for (int i = 0; i < _size; ++i)
        ret += this->_transactions[i].get_string();
    return ret;
}

unsigned int Ledger::get_size() const {
    unsigned int size = 0;
    for (const Transaction& t : this->_transactions)
        size += t.get_size();
    return size;
}

