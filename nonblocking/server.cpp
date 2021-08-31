#include "server.h"
#include "../link.h"

Server::Server(int port) {
    this->clients_thread_list = list<thread>();
    this->clients_sockets_list = list<SOCKET>();
    
    this->running = true;
    Link::serverRunning = true;

    this->cmd = "";
    this->port = port;
    // cout << "port " << port << endl;
}

Server::Server(const Server& other) {

}

void Server::shutdown() {
    cout << "shutting down" << endl;
    // while (!this->clients_sockets_list.empty()) {
    //     closesocket(this->clients_sockets_list.front());
    //     this->clients_sockets_list.pop_front();
    // }
    // cout << "sockets closed" << endl;
    WSACleanup();
    cout << "server shutdown" << endl;
}

boolean Server::init() {
    WSADATA wsData;
    WORD word = MAKEWORD(2, 2);
    int wsOk = WSAStartup(word, &wsData);

    if (wsOk != 0) {
        // cerr << "Can't initialize winwock! quitting" << endl;
        return false;
    }

    // cout << "Winsock initiated!" << endl;
    return true;
}

void Server::start() {
    if (!this->init()) {
        // cerr << "Server init failed!" << endl;
        return;
    }
    bool flag = true;
    cout << "Starting server..." << endl;
    thread serverControlThread = thread(&Server::server_control, this);
    
    while (this->running) {

        this->listening_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

        unsigned long nonBlocking = 1;
        ioctlsocket(this->listening_socket, FIONBIO, &nonBlocking);

        if (this->listening_socket == INVALID_SOCKET) {
            // cerr << "Can't create socket! quitting" << endl;
            return;
        }

        // bind the ip and port to a socket
        sockaddr_in hint;
        hint.sin_family = AF_INET;
        hint.sin_port = htons(PORT);
        hint.sin_addr.S_un.S_addr = INADDR_ANY;

        bind(this->listening_socket, (sockaddr*)&hint, sizeof(hint));

        if (flag) {
            cout << "Server is listening to clients..." << endl;
            flag = false;
        }

        // tell winsock the socket is for listening
        listen(this->listening_socket, SOMAXCONN);

        // wait for connection
        sockaddr_in client; // client sockaddr_in
        int clientSize = sizeof(client);

        this->clientSocket = NULL;
        ioctlsocket(this->clientSocket, FIONBIO, &nonBlocking);

        while (this->running) {
            this->clientSocket = accept(this->listening_socket, (sockaddr*)&client, &clientSize);

            if (this->clientSocket != (unsigned int)(-1) && this->running) {
                // start thread
                this->clients_sockets_list.push_back(this->clientSocket);
                this->clients_thread_list.push_back(thread(&Server::handle_client, this, clientSocket, client));

                //cout << "connected" << endl;
                break;
            }
        }

        closesocket(this->listening_socket);
    } // end while running

    // close this functions sockets 
    closesocket(this->listening_socket);
    closesocket(this->clientSocket);
    
    // wait for the serverControl function to close the Winsocket
    serverControlThread.join();
}

void Server::handle_client(SOCKET clientSocket, sockaddr_in client) {
    bool flag = false;
    list<string> request_list = list<string>();
    string port = to_string((int)(client.sin_port));
    string ip = this->get_ip(client);
       
    cout << ip << " " << port << " is connected" << endl;

    string client_request;
    const unsigned int buffer_size = 4096;
    char buffer[buffer_size];

    while (this->running) {
        ZeroMemory(buffer, buffer_size);
        int bytesReceived;

        try {
            bytesReceived = recv(clientSocket, buffer, buffer_size, 0);
        }
        catch (exception e) {
            // cerr << "exception in handle_client" << endl;
            this->clients_sockets_list.remove(clientSocket);
            closesocket(clientSocket);
            return;
        }

        if (bytesReceived > 0) {
            client_request = string(buffer, 0, bytesReceived);
            if (client_request != "") {
                print(ip + " " + port + "> " + client_request);
                
            }
            else {
                // cout << "client disconnected" << endl;
                this->clients_sockets_list.remove(clientSocket);
                closesocket(clientSocket);
                return;
            }
        }
        else if (bytesReceived == 0) {
            // cout << "client disconnected!" << endl;
            this->clients_sockets_list.remove(clientSocket);
            closesocket(clientSocket);
            break;
        }
    }
    closesocket(clientSocket);
}

string Server::get_ip(sockaddr_in client) {
    return to_string((int)(client.sin_addr.S_un.S_un_b.s_b1)) + "." +
        to_string((int)(client.sin_addr.S_un.S_un_b.s_b2)) + "." +
        to_string((int)(client.sin_addr.S_un.S_un_b.s_b3)) + "." +
        to_string((int)(client.sin_addr.S_un.S_un_b.s_b4));
}

void Server::server_control() {
    const unsigned int MAX_LEN = 200;
	for (;;) {
		cin >> this->cmd;

		if (false)
			continue;
		else if (this->cmd.find("broadcast") != string::npos) {
			// else if (this->cmd == "broadcast")
			// might change it to this
			char str_arr[MAX_LEN] = "";
			cin.getline(str_arr, MAX_LEN);
			string msg(str_arr);
			msg = msg.erase(0, 1);

			if (msg != "") {
				cout << "broadcast [" << msg << "] sent" << endl;
			
				for (SOCKET soc : this->clients_sockets_list)
					this->response_to_client(soc, msg + '\n');
			}
		}
		else if (this->cmd == "exit") {
            Link::mtx.lock();
            this->running = false;
            Link::serverRunning = false;
            
            // wait for clients to close sockets (the handle client function)
            while (!this->clients_thread_list.empty()) {
                if (this->clients_thread_list.front().joinable())
                    this->clients_thread_list.front().join();
                this->clients_thread_list.pop_front();
            }

            this->shutdown();
            Link::mtx.unlock();
			return;
		}
	}
}

void Server::response_to_client(SOCKET clientSocket, string response) {
	send(clientSocket, (response).c_str(), response.size() + 1, 0);
}

void Server::print(string str) {
    Link::mtx.lock();
    // cout << "server:: mtx locked and pushing to list" << endl;
    Link::link_list.push_back(str);
    // cout << "server:: unlocking mtx..." << endl;
    Link::mtx.unlock();
}
