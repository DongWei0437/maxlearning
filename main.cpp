#include <iostream>
#include <algorithm>
#include "grouplearning.h"
#include "random_workers.h"
using namespace Dylearning;
using namespace std;
using namespace random_w;
int main() {
    //int n =10;
    //vector<float> workers = rWorkers_logNormal(10, 0.5);
//    for(auto i : workers){
//        cout<<i<<endl;
//    }
    vector<float> workers = {0,1,2,3,4,5,6,7,8,9};
    int it = dGroup(workers,5);

    std::cout <<it << std::endl;
    return 0;
}
