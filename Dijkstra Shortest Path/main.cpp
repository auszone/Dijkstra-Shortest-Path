#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;
typedef pair<unsigned, unsigned> P;
const auto cmp = [](P a, P b) { return a.second > b.second; };
P my_pop(vector<P> &v) {
    P node = v.front();
    pop_heap (v.begin(),v.end(), cmp);
    v.pop_back();
    return node;
}
void my_push(vector<P> &v, P e) {
    v.push_back(e);
    push_heap(v.begin(), v.end(), cmp);
}
int main(int argc, const char * argv[]) {
    // input the map
    size_t numNodes;
    cout << "Input the number of nodes" << endl;
    cin >> numNodes;
    cin.ignore();
    vector<vector<P>> map(numNodes);
    
    for (int i = 0; i < numNodes; ++i) {
        unsigned des, dis;
        vector<P> list;
        cout << "Input the nodes and distance which are connect to node [" << i <<"] in one line: (End wit 'q')" << endl;
        while (1) {
            cin >> des >> dis;
            if(cin.fail()) {
                cin.clear();
                break;
            }
            list.push_back(P(des, dis));
        }
        cin.ignore();
        map[i] = list;
    }
    for (int i = 0; i < map.size(); ++i) {
        cout << "Node " << i << ": ";
        for (auto &p : map[i]) {
            cout << "(" << p.first << "," << p.second << ") ";
        }
        cout << endl;
    }
    unsigned s, d;
    cout << "input start and destination" << endl;
    cin >> s >> d;
    vector<P> open, close;
    close.push_back(P(s,0));
    
    make_heap(close.begin(), close.end(), cmp);
    make_heap(open.begin(), open.end(), cmp);
    while (1) {
        P cur = my_pop(close);
        for (auto &p : map[cur.first]) {
            my_push(open, P(p.first, cur.second + p.second));
        }
        // add the nearest node to close set
        P node = my_pop(open);
        if (node.first == d) {
            cout << "found with d:" << node.second << endl;
            break;
        }
        my_push(close, node);
    }
    return 0;
}