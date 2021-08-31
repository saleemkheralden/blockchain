//
// Created by SLIMS-PC on 5/20/2021.
//

#include "Miner firstVer.h"

Miner::Miner(int diff) {
    this->diff = diff;
}

string Miner::mine(Block* b) {
    while (!mined(b->get_hash()))
        b->inc_nonce();
    return b->get_hash();
}

int Miner::mined(string hash) {
    for(int i = 0; i < this->diff; i++)
        if (hash[i] != '0')
            return 0;
    return 1;
}
