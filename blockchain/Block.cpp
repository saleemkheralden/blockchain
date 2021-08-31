//
// Created by SLIMS-PC on 5/23/2021.
//

#include "Block.h"

Block::Block(ull id, string prev_hash) {
    this->_id = id;
    this->_prev_hash = move(prev_hash);
    this->_nonce = DEFAULT_NONCE;
    this->_ledger = Ledger();
    this->_hash = block_hash();
}

Block::Block(const Block &block) {
    this->_id = block.get_id();
    this->_prev_hash = block.prev_hash();
    this->_nonce = block.get_nonce();
    this->_ledger = block.get_ledger();
    this->_hash = block._hash;
}

unsigned int Block::ledger_len() {
    return this->_ledger.ledger_len();
}

void Block::add_transaction(const Transaction& transaction) {
    this->_ledger.append_transaction(transaction);
}

string Block::get_hash() const {
    return this->_hash;
}

string Block::prev_hash() const {
    return this->_prev_hash;
}

void Block::set_prev_hash(string hash) {
    this->_prev_hash = move(hash);
    this->set_hash(block_hash());
}

void Block::set_hash(string hash) {
    this->_hash = move(hash);
}

void Block::inc_nonce() {
    this->_nonce++;
    this->set_hash(block_hash());
}

void Block::set_nonce(ull nonce) {
    this->_nonce = nonce > 0 ? nonce : DEFAULT_NONCE;
    this->_hash = block_hash();
}

string Block::block_string() {
    string ret = to_string(this->_id) + "\n";
    ret += this->_prev_hash + "\n";
    ret += this->_hash + "\n";
    ret += this->_ledger.get_string();
    ret += to_string(this->_nonce);
    return ret;
}

string Block::block_str_hash() {
    string ret = to_string(this->_id) + "\n";
    ret += this->_prev_hash + "\n";
    ret += this->_ledger.get_string();
    ret += to_string(this->_nonce);
    return ret;
}

string Block::block_hash() {
    return sha256(block_str_hash());
}

ull Block::get_id() const {
    return this->_id;
}

ull Block::get_nonce() const {
    return this->_nonce;
}

Ledger Block::get_ledger() const{
    return Ledger((Ledger&)this->_ledger);
}

unsigned int Block::get_size() const {
    return this->_ledger.get_size() + sizeof(this->_id) + this->_prev_hash.length() + this->_hash.length() + sizeof(this->_nonce);
}
