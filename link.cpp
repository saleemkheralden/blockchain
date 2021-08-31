#include <iostream>
#include "link.h"

list<string> Link::link_list = list<string>();
bool Link::serverRunning = true;
mutex Link::mtx;

