#include <list>
#include <mutex>

using namespace std;


class Link {
public:
    static list<string> link_list;
    static bool serverRunning;
    static mutex mtx;
};