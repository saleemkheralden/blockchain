//
// Created by SLIMS-PC on 5/23/2021.
//

#include "Blockchain.h"

Blockchain::Blockchain() {
    this->blocks =              vector<Block>();
    this->blocks_pool =         vector<Block>();
    this->last_verified_block = -1;
}

void Blockchain::add_block(Block block) {
    if (!this->blocks.empty() && block.prev_hash() != this->blocks[this->last_verified_block].get_hash())
        block.set_prev_hash(this->blocks[this->last_verified_block].get_hash());
    this->blocks.push_back(block);
    this->last_verified_block++;

    for (int index = 0; index < this->blocks_pool.size(); index++)
        if (this->blocks_pool[index].get_hash() == this->blocks[index].get_hash()) {
            this->blocks.erase(this->blocks.begin() + index);
            break;
        }
}

void Blockchain::add_unverified_block(const Block& block) {
    this->blocks_pool.push_back(block);
}

Block Blockchain::get_unveridied_block() {
    return this->blocks_pool.front();
}

void Blockchain::print_blocks() {
    for (Block block : this->blocks)
        cout << block.block_string() << endl << endl;
}

Block Blockchain::get(int index) const {
    return Block(this->blocks.at(index));
}
