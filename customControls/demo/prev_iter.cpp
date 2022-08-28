#include <vector>
#include <iostream>
#include <list>



static void printLists(std::list<int>& _l) {
    for( auto iter = _l.begin(); iter != _l.end(); ++iter) {
        std::cout << *iter << " --> ";
    }
    std::cout << "null"<< std::endl;
}

int main(int argc, char* argv[]) {
    std::list<int> lists {1,2,3,4,5,6};
    printLists(lists);

    std::list<int>::reverse_iterator iter = lists.rbegin();
    ++iter;
    ++iter;
    ++iter;
    std::list<int>::iterator forwardIter = std::prev(iter.base());

    std::cout << *iter << ", " << *forwardIter << std::endl;

    lists.push_back(*iter);
    lists.erase(forwardIter);

    printLists(lists);

    return 0;
}