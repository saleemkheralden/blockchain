//
// Created by SLIMS-PC on 5/23/2021.
//

#include "Transaction.h"

Transaction::Transaction(string sender, string receiver, int amount) {
    this->_sender =             move(sender);
    this->_receiver =           move(receiver);
    this->_amount =             amount;
    this->_transaction_time =   time(nullptr);
}

Transaction::Transaction(const Transaction &transaction) {
    this->_sender =             transaction._sender;
    this->_receiver =           transaction._receiver;
    this->_amount =             transaction._amount;
    this->_transaction_time =   transaction._transaction_time;
}

int Transaction::amount() const {
    return this->_amount;
}

string Transaction::receiver() {
    return this->_receiver;
}

string Transaction::sender() {
    return this->_sender;
}

string Transaction::get_time() {
    return asctime(localtime(&this->_transaction_time));
}

string Transaction::get_string() {
    return this->sender() + " -> " + this->receiver() + " : " + to_string(this->amount()) + " " + this->get_time();
}

unsigned int Transaction::get_size() const {
    return this->_sender.length() + this->_receiver.length() + sizeof(this->_amount) + sizeof(this->_transaction_time);
}


