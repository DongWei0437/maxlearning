//
// Created by dongwei on 10/8/19.
//

#ifndef MAXLEARNING_GROUPLEARNING_H
#define MAXLEARNING_GROUPLEARNING_H

#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;
namespace Dylearning{
        pair<float, vector<float>> improve(vector<vector<float>> gs){
            vector<float> res;
            vector<vector<float>> gsCopy(gs.size(),vector<float>(gs[0].size(),0.0));
            for(int k =0;k<gs.size();k++){
                sort(gs[k].begin(),gs[k].end());
                for(int i =0; i<gs[k].size()-1;i++){
                    for(int j =i+1;j<gs[k].size();j++){
                        float s = log((gs[k][j]-gs[k][i]))<0?0:log((gs[k][j]-gs[k][i]));
                        gsCopy[k][i] = gs[k][i] + s;
                    }
                }
            }
            for(auto i :gsCopy){
                res.insert(res.end(),i.begin(),i.end());
            }
            sort(res.begin(),res.end());
            float total =0;
            for(auto i: res){
                total+= i;
            }
            return {total,res};
        }


        vector<vector<float>> grouping_1(vector<float> people,int k){
            vector<vector<float>> res;
            int n = people.size();
            for(int i =0;i<k;i++){
                vector<float> temp;
                for(int j =0; j<n/k;j++){
                    temp.push_back(people[i+j*k]);
                }
                res.push_back(temp);
            }
            return res;
        }
        vector<vector<float>> grouping_2(vector<float> people,int k){
            vector<vector<float>> res;
            int n = people.size();
            if(n/k%2==0){
                for(int i =0;i<k;i++){
                    vector<float> temp;
                    for(int j =0; j<(n/k)/2;j++){
                        temp.push_back(people[i*((n/k)/2)+j]);
                        temp.push_back(people[n-i*((n/k)/2)-j]-1);
                    }
                    res.push_back(temp);
                }
            }
            else{
                vector<vector<float>> t1;
                vector<vector<float>> t2;
                for(int i =0;i<k;i++){
                    vector<float> temp;
                    for(int j =0; j<(n/k)/2;j++){
                        temp.push_back(people[i*((n/k)/2)+j]);
                        temp.push_back(people[n-i*((n/k)/2)-j-1]);
                    }
                    temp.push_back(people[i*((n/k)/2)+(n/k)/2]);
                    t1.push_back(temp);
                }
                for(int i =0;i<k;i++){
                    vector<float> temp;
                    for(int j =0; j<(n/k)/2;j++){
                        temp.push_back(people[i*((n/k)/2)+j]);
                        temp.push_back(people[n-i*((n/k)/2)-j-1]);
                    }
                    temp.push_back(people[i*((n/k)/2)+(n/k)/2]);
                    t2.push_back(temp);
                }
                pair<float, vector<float>> tr1 =  improve(t1);
                pair<float, vector<float>> tr2 =  improve(t2);
                res = tr1.first>tr2.first?t1:t2;
            }
            return res;
        }
        int dGroup(vector<float> people,int k){
            int iter =0;
            float epsilon =0.05;
            float preT =0;
            for(auto i: people){
                preT +=i;
            }
            vector<vector<float>> g1 = grouping_1(people,k);
            vector<vector<float>> g2 = grouping_2(people,k);
            pair<float, vector<float>> tr1 = improve(g1);
            pair<float, vector<float>> tr2 = improve(g2);
            vector<float> curGrp= tr1.first<tr2.first?tr2.second:tr1.second;
            float curT =0.0;
            for(auto i: curGrp){
                curT +=i;
            }
            while(curT - preT>epsilon){
                iter +=1;
                preT = curT;
                vector<vector<float>> g1 = grouping_1(curGrp,k);
                vector<vector<float>> g2 = grouping_2(curGrp,k);
                pair<float, vector<float>> tr1 = improve(g1);
                pair<float, vector<float>> tr2 = improve(g2);
                vector<float> curGrp= tr1.first<tr2.first?tr2.second:tr1.second;
                curT =0.0;
                for(auto i: curGrp){
                    curT +=i;
                }
            }
            return iter;
        }
}

#endif //MAXLEARNING_GROUPLEARNING_H
