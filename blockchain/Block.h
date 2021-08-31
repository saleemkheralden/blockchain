//
// Created by SLIMS-PC on 5/23/2021.
//

#ifndef SLIMCOIN_BLOCK_H
#define SLIMCOIN_BLOCK_H

#include <iostream>
#include <vector>
#include <string>
#include "Ledger.h"
#include "sha256.h"

#define DEFAULT_NONCE 0

using namespace std;
typedef unsigned long long ull;

class Block {
public:
    Block(ull id, string prev_hash);
    Block(const Block& block);

    unsigned int    ledger_len();
	void            inc_nonce();
    void            set_nonce(ull nonce);
    void            add_transaction(const Transaction& transaction);
    void            set_prev_hash(string hash);
    string          block_string();

    string          get_hash() const;
    string          prev_hash() const;
    ull             get_id() const;
    ull             get_nonce() const;
    Ledger          get_ledger() const;
    unsigned int    get_size() const;

private:
    string          block_str_hash();
    string          block_hash();
    void            set_hash(string hash);


    ull     _id;
    string  _prev_hash;
    string  _hash;
    ull     _nonce;
    Ledger  _ledger;


};


#endif //SLIMCOIN_BLOCK_H
