//
// this file represents the coin network
//

#include <iostream>
#include <thread>

using namespace std;
// #include "Block.h"
// #include "../link.h"
// #include "../nonblocking/server.h"
#include "Blockchain.h"
#define MAX_TRANSACTIONS 500

void init(Blockchain&);

typedef unsigned long long ull;

void init(Blockchain& blockchain) {
    Block block(0, "0000000000000000000000000000000000000000000000000000000000000000");
    block.add_transaction(Transaction("slimcoin network", "saleem", 1000));
    blockchain.add_block(block);
}

int main() {
    Blockchain blockchain = Blockchain();
    // Server server = Server();
    // thread serverThread = thread(&Server::start, server);

    init(blockchain);

    ull id = 1;
    Block b = blockchain.get(0);
    cout << b.block_string() << endl;
    cout << b.get_size() << endl;
    for (int i = 0; i < 21; i++)
        b.add_transaction(Transaction("saleem", "slim", 20));
    cout << b.block_string() << endl;
    cout << b.get_size() << endl;
    
    // while (Link::serverRunning) {
    //     if (Link::mtx.try_lock()) {
    //         if (!Link::link_list.empty()) {
    //             string str = Link::link_list.front();
                
    //             if (str.find("TRANS") != string::npos) {
    //                 string sender = str.substr(str.find("FROM:") + 5, (str.find("TO:") - 1) - (str.find("FROM:") + 5));
    //                 string recevier = str.substr(str.find("TO:") + 3, (str.find("AMOUNT:") - 1) - (str.find("TO:") + 3));
    //                 int amount = stoi(str.substr(str.find("AMOUNT:") + 7, str.length() - (str.find("AMOUNT:") + 7)));
    //                 // b.add_transaction(Transaction()))
    //                 cout << sender + " " + recevier + " " << amount << endl;
    //             }
                
    //             // cout << str.substr(str.find('>') + 2, str.length() - str.find('>') + 1) << endl;


    //             Link::link_list.pop_front();
    //         }
    //         Link::mtx.unlock();
    //     }
    // }

//    for (;;) {
//
//        id++;
//    }

//    this part will be coded with visual studio due to threads not working with other IDE for unknown reasons 
//	  
//	this block of code will be executed in threads
// 	make block: Block block(id, "")
//  while (true) {
//  	gets transaction from the internet "sender:{}, receiver:{}, amount:{}"
//		get the sender, receiver and amount as variables
//		make a Transaction object : Transaction transaction(sender, receiver, amount)
//		block.add_transaction(transaction)
//		if (block.ledger_len() == MAX_TRANSACTIONS) {
//      	blockchain.add_unverified_block(block)
//			id++;
//			block = Block(id, "")
//		}
//	}

    // wait for the server to properly shutdown
    // if (serverThread.joinable())
    //     serverThread.join();
    cout << "main exit" << endl;
    return 0;
}

