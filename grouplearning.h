//
// Created by dongwei on 10/8/19.
//

#ifndef MAXLEARNING_GROUPLEARNING_H
#define MAXLEARNING_GROUPLEARNING_H

#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

class grouplearning {
    vector<float> improve(vector<vector<float>>& gs){
        vector<float> res;
        for(auto g: gs){
            sort(g.begin(),g.end());
            for(int i =0; i<g.size()-1;i++){
                for(int j =i+1;j<g.size();j++){
                    float s = log((g[j]-g[i]))<0?0:log((g[j]-g[i]));
                    g[i] += s;
                }
            }
        }
        for(auto i :gs){
            res.insert(res.end(),i.begin(),i.end());
        }
        sort(res.begin(),res.end());
        return res;
    }


    vector<vector<float>> grouping_1(vector<float> people){
        vector<vector<float>> res;



        return res;

    }

};


#endif //MAXLEARNING_GROUPLEARNING_H
