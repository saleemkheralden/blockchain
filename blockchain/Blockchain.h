//
// Created by SLIMS-PC on 5/23/2021.
//

#ifndef SLIMCOIN_BLOCKCHAIN_H
#define SLIMCOIN_BLOCKCHAIN_H

#include <iostream>
#include <vector>
#include "Block.h"

using namespace std;

class Blockchain {
public:
    Blockchain();

    void    add_block(Block block);
    void    add_unverified_block(const Block &block);
    Block   get_unveridied_block();

    Block   get(int) const;
    void    print_blocks();

private:
    int             last_verified_block;
    vector<Block>   blocks;
    vector<Block>   blocks_pool;
};


#endif //SLIMCOIN_BLOCKCHAIN_H
