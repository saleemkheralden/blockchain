//
// Created by SLIMS-PC on 5/20/2021.
//

#ifndef TEMP_MINER_H
#define TEMP_MINER_H
#include "Block.h"
#include "Blockchain.h"

class Miner {
public:
    Miner(int diff);
    string mine(Block *b);
private:
    int diff;
    int mined(string hash);

};


#endif //TEMP_MINER_H
