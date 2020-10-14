//
// Created by Dong Wei on 10/13/2019.
//

#ifndef MAXLEARNING_GROUP_LINEAR_H
#define MAXLEARNING_GROUP_LINEAR_H
#include <vector>
#include <set>
#include <math.h>
#include <algorithm>
#include "grouplearning.h"
#include <float.h>

using namespace std;

namespace Dylearn_linear{


    pair<float, vector<float>> improve(vector<vector<float>> gs,float rate){ //clique
        vector<float> res;
        vector<vector<float>> gsCopy(gs.size(),vector<float>(gs[0].size(),0.0));
        vector<vector<float>> gst(gs.size(),vector<float>(gs[0].size(),0.0));
        for(int i =0;i < gs.size(); i++){
            for(int j =0; j<gs[0].size();j++){
                gsCopy[i][j] = gs[i][j];
            }
        }
        for(int k =0;k<gs.size();k++){
            for(int i =0; i<gs[k].size()-1;i++){
                for(int j =i+1;j<gs[k].size();j++){
                    float s = gs[k][j]-gs[k][i];
                    if(gs[k][j]-gs[k][i]>0){
                        gsCopy[k][i] += rate*s;
                        gst[k][i]+=1;
                    }
                    else{
                        gsCopy[k][j] -=  rate*s;
                        gst[k][j]+=1;
                    }
                }
            }
        }
        for(int i =0;i < gs.size(); i++){
            for(int j =0; j<gs[0].size();j++){
                if(gst[i][j]>1)
                    gsCopy[i][j] = gs[i][j]+ (gsCopy[i][j]-gs[i][j])/gst[i][j];
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

//    pair<float, vector<float>> improve(vector<vector<float>> gs,float rate){ //clique
//        vector<float> res;
//        vector<vector<float>> gsCopy(gs.size(),vector<float>(gs[0].size(),0.0));
//        vector<vector<float>> gst(gs.size(),vector<float>(gs[0].size(),0.0));
//        for(int i =0;i < gs.size(); i++){
//            for(int j =0; j<gs[0].size();j++){
//                gsCopy[i][j] = gs[i][j];
//            }
//        }
//        for(int k =0;k<gs.size();k++){
//            float x=0;
//            for(int i =1; i<gs[k].size();i++){
//                x= ((float)(i-1)/(float)i)*x + gs[k][i-1] - gs[k][i];
//                gst[k][i]  = x;
//            }
//        }
//        for(int i =0;i < gs.size(); i++){
//            for(int j =0; j<gs[0].size();j++){
//                    gsCopy[i][j] = gs[i][j] + gst[i][j]*rate;
//            }
//        }
//        for(auto i :gsCopy){
//            res.insert(res.end(),i.begin(),i.end());
//        }
//        sort(res.begin(),res.end());
//        float total =0;
//        for(auto i: res){
//            total+= i;
//        }
//        return {total,res};
//    }

//    pair<float, vector<float>> improve(vector<vector<float>> gs,float rate){//star
//        vector<float> res;
//        vector<vector<float>> gsCopy(gs.size(),vector<float>(gs[0].size(),0.0));
//        for(int i =0;i < gs.size(); i++){
//            for(int j =0; j<gs[0].size();j++){
//                gsCopy[i][j] = gs[i][j];
//            }
//        }
//        for(int k =0;k<gs.size();k++){
//            float e = INT32_MIN;
//            for(auto i :gs[k]){e = max(e,i);}
//            for(int i =0; i<gs[k].size();i++){
//                float s = e-gs[k][i];
//                    gsCopy[k][i] += rate*s;
//            }
//        }
//        for(auto i :gsCopy){
//            res.insert(res.end(),i.begin(),i.end());
//        }
//        sort(res.begin(),res.end());
//        float total =0;
//        for(auto i: res){
//            total+= i;
//        }
//        return {total,res};
//    }

//
//
//
//
    vector<vector<float>> grouping_linear(vector<float> people,int k){//clique
        vector<vector<float>> res;
        sort(people.begin(),people.end(),greater<float>());
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

//
//    vector<vector<float>> grouping_linear(vector<float> people,int k){//star
//        vector<vector<float>> res;
//        sort(people.begin(),people.end());
//        int n = people.size();
//        for(int i =0;i<k;i++){
//            vector<float> temp;
//            for(int j =0; j<(n/k-1);j++) {
//                temp.push_back(people[i*(n/k-1) + j]);
//            }
//            res.push_back(temp);
//        }
//        for(int i =k;i>0;i--){
//            res[k-i].push_back(people[n-i]);
//        }
//        return res;
////

//    }
//









    pair<float,vector<float>> learning_clique(vector<vector<int>> groups,vector<float> workers,float rate){
        vector<float> res;
        vector<vector<float>> gsCopy(groups.size(),vector<float>(groups[0].size(),0.0));
        vector<vector<float>> gst(groups.size(),vector<float>(groups[0].size(),0.0));
        for(int i =0;i < groups.size(); i++){
            for(int j =0; j<groups[0].size();j++){
                gsCopy[i][j] = workers[groups[i][j]];
            }
        }
        float total =0;
        for(int k =0;k<gsCopy.size();k++){
            for(int i =0; i<gsCopy[k].size()-1;i++){
                for(int j =i+1;j<gsCopy[k].size();j++){
                    float s = workers[groups[k][j]]-workers[groups[k][i]];
                    if(s>0){
                        gsCopy[k][i] += rate*s;
                        gst[k][i]+=1;
                    }
                    else{
                        gsCopy[k][j] -=  rate*s;
                        gst[k][j]+=1;
                    }
                }
            }
        }
        for(int i =0;i < gsCopy.size(); i++){
            for(int j =0; j<gsCopy[0].size();j++){
                if(gst[i][j]>1)
                    gsCopy[i][j] = workers[groups[i][j]]+ (gsCopy[i][j]-workers[groups[i][j]])/gst[i][j];
                total +=(gsCopy[i][j] -workers[groups[i][j]]);
            }
        }
        for(auto i :gsCopy){
            res.insert(res.end(),i.begin(),i.end());
        }
        sort(res.begin(),res.end());
        return {total,res};
    }

    pair<float,vector<float>> learning_star(vector<vector<int>> groups,vector<float> workers,float rate){
        vector<float> res;
        vector<vector<float>> gsCopy(groups.size(),vector<float>(groups[0].size(),0.0));
        float origin =0;
        for(int i =0;i < groups.size(); i++){
            for(int j =0; j<groups[0].size();j++){
                gsCopy[i][j] = workers[groups[i][j]];
                origin+=gsCopy[i][j];
            }
        }
        for(int k =0;k<gsCopy.size();k++){
            float e = INT32_MIN;
            for(auto i :gsCopy[k]){e = max(e,i);}
            for(int i =0; i<gsCopy[k].size();i++){
                float s = e-gsCopy[k][i];
                if(e-gsCopy[k][i]>0){
                    gsCopy[k][i] += rate*s;
                }
            }
        }
        for(auto i :gsCopy){
            res.insert(res.end(),i.begin(),i.end());
        }
        float total =0;
        for(auto i: res){
            total+= i;
        }
        sort(res.begin(),res.end());
        return {total-origin,res};
    }








    pair<float,int> dGroup_linear2(vector<float> people, int k, float rate, float epsilon){
        float origin=0;
        float preT =0;
        for(auto i: people){
            preT +=i;
            origin+=i;
        }
        vector<vector<float>> g1 = grouping_linear(people,k);
        pair<float, vector<float>> tr1 = improve(g1,rate);
        vector<float> curGrp= tr1.second;
        float curT =0.0;
        for(auto i: curGrp){
            curT +=i;
        }
        int iter =1;
        while((curT - preT)/preT>epsilon){
            iter +=1;
            preT = curT;
            g1 = grouping_linear(curGrp,k);
            tr1 = improve(g1,rate);
            curGrp= tr1.second;
            curT =0.0;
            for(auto i: curGrp){
                curT +=i;
            }
        }
        return {curT-origin,iter};
    }
    float dGroup_linear(vector<float> people, int k, float rate, float epsilon){
        float origin=0;
        float preT =0;
        for(auto i: people){
            preT +=i;
            origin+=i;
        }
        vector<vector<float>> g1 = grouping_linear(people,k);
        pair<float, vector<float>> tr1 = improve(g1,rate);
        vector<float> curGrp= tr1.second;
        float curT =0.0;
        for(auto i: curGrp){
            curT +=i;

        }

        int iter =1;
        while((curT - preT)/preT>epsilon){
            iter +=1;
            preT = curT;
            g1 = grouping_linear(curGrp,k);
            tr1 = improve(g1,rate);
            curGrp= tr1.second;
            curT =0.0;
            for(auto i: curGrp){
                curT +=i;
            }
        }
        return curT-origin;
    }

    vector<vector<float>> grouping_kdd(vector<float> people,int k) {
        vector<vector<float>> res;
        sort(people.begin(),people.end());
        int n = people.size();
        int x = n/k;
        vector<float> B_low;
        vector<float> B_high;
        for(int i =0; i<k;i++){
            B_low.push_back(people[i]);
            B_high.push_back(people[n-i-1]);
        }
        random_shuffle(B_low.begin(),B_low.end());
        random_shuffle(people.begin()+k,people.end()-k);
        vector<float> T(people.begin()+k,people.end()-k);
        for (int j = 0; j <k ; ++j) {
            vector<float> TempG;
            TempG.push_back(B_low[j]);
            TempG.push_back(B_high[j]);
            for (int i = 0; i < x-2 ; ++i) {
                TempG.push_back(T[j*(x-2)+i]);
            }
            res.push_back(TempG);
        }
        return res;
    }
    float kddGroup_Li(vector<float> people,int k,float rate,float epsilon){
        float origin =0;
        float preT =0;
        for(auto i: people){
            preT +=i;
            origin+=i;
        }
        vector<vector<float>> g = grouping_kdd(people,k);
        pair<float, vector<float>> t = improve(g,rate);
        vector<float> curG = t.second;
        int iter = 0;
        float curT =0;
        for(auto i: curG){
            curT +=i;
        }
        while((curT - preT)/preT>epsilon) {
            iter+=1;
            preT = curT;
            vector<vector<float>> g = grouping_kdd(curG,k);
            pair<float, vector<float>> t = improve(g,rate);
            vector<float> curG = t.second;
            curT =0;
            for(auto i: curG){
                curT +=i;
            }
        }
        return curT-origin;
    }


    vector<vector<float>> grouping_rakesh(vector<float> people,int k) {
        sort(people.begin(),people.end());
        //int p = rand()%100+1;
        int p = 75;
        int N = people.size();
        int n = N/k;
        vector<vector<float>> G(k,vector<float>());
        int m = 100/(100-p);
        int q = floor(float(n)/float(m));
        int qi = ceil(float(n)/float(m));
        vector<float> M;
        if(n % m != 0){
            for(int i =0;i<k;i++) {
                M.push_back(people[k * q + i]);
                G[i].push_back(M[i]);
            }
        }
        vector<float> H1;
        vector<float> H2;
        for(int i =0;i<k*q;i++){
            H1.push_back(people[i]);
        }
        for(int i = k*qi;i<N;i++){
            H2.push_back(people[i]);
        }
        random_shuffle(H1.begin(),H1.end());
        random_shuffle(H2.begin(),H2.end());
        for(int i =0;i<k;i++){
            for(int j =0;j<q;j++){
                G[i].push_back(H1[q*i+j]);
            }
            for(int l =0;l<(n-qi);l++){
                G[i].push_back(H2[(n-qi)*i+l]);
            }
        }

        return G;
    }

    float rakeshGroup_Li( vector<float> people,int k,float rate,float epsilon){
        float preT =0;
        float origin =0;
        for(auto i: people){
            preT +=i;
            origin+=i;
        }
        vector<vector<float>> g = grouping_rakesh(people,k);
        pair<float, vector<float>> t = improve(g,rate);
        vector<float> curG = t.second;
        int iter = 0;
        float curT =0;
        for(auto i: curG){
            curT +=i;
        }
        //cout<<"curT:\t"<<curT<<endl;

        while((curT - preT)/preT>epsilon) {
            iter+=1;
            preT = curT;
            vector<vector<float>> g = grouping_rakesh(curG,k);
            pair<float, vector<float>> t = improve(g,rate);
            vector<float> curG = t.second;
            curT =0;
            for(auto i: curG){
                curT +=i;
            }
        }
        return curT-origin;
    }



    vector<vector<float>> grouping_rand(vector<float> p,int k) {
        srand(time(NULL));
        vector<vector<float>> res;
        vector<float>people(p.begin(),p.end());
        int n = people.size();
        int x = n/k;
        random_shuffle(people.begin(),people.end());
        float c =0;
        for (int j = 0; j <k ; ++j) {
            vector<float> TempG;
            for (int i = 0; i < x ; ++i) {
                TempG.push_back(people[j*x+i]);
                c+=people[j*x+i];
            }
            sort(TempG.begin(),TempG.end());
            res.push_back(TempG);
        }
        return res;
    }


    vector<vector<float>> grouping_rand2(vector<float> p,int k) {
        srand(time(NULL));
        vector<vector<float>> res;
        vector<float>people(p.begin(),p.end());
        int n = people.size();
        int x = n/k;
        random_shuffle(people.begin(),people.end());
        float c =0;
        for (int j = 0; j <k ; ++j) {
            vector<float> TempG;
            for (int i = 0; i < x ; ++i) {
                TempG.push_back(people[j*x+i]);
                c+=people[j*x+i];
            }
            sort(TempG.begin(),TempG.end());
            res.push_back(TempG);
        }
        //cout<<"c:\t"<<c<<endl;
        return res;
    }

    float randGroup_Li(vector<float> people,int k,float rate,float epsilon){
        float preT =0;
        for(auto i: people){
            preT +=i;
        }
        vector<vector<float>> g = grouping_rand(people,k);
        float origin =0;
        for(auto i:people){
            origin += i;
        }
        pair<float, vector<float>> t = improve(g,rate);
        vector<float> curG = t.second;
        int iter = 0;
        float curT =0;
        for(auto i: curG){
            curT +=i;
        }
        while((curT - preT)/preT>epsilon) {
            iter+=1;
            preT = curT;
            vector<vector<float>> g = grouping_rand(curG,k);
            pair<float, vector<float>> t = improve(g,rate);
            vector<float> curG = t.second;
            curT =0;
            for(auto i: curG){
                curT +=i;
            }
        }
        return curT - origin;
    }


    vector<vector<float>> grouping_knn(vector<float> people,int k) {
        vector<vector<float>> res;
        int n= people.size();
        int x = n/k;
        random_shuffle(people.begin(),people.end());
        vector<float> center;
        for(int i=0;i<k;i++){
            center.push_back(people[i]);
            res.push_back({people[i]});
        }
        for(int i = k;i<n;i++){
            float m = FLT_MAX;
            int idx = -1;
            for(int j=0;j<k;j++){
                if(res[j].size()<x){
                    if(m>abs(people[i]-res[j][0])){
                        idx = j;
                        m = abs(people[i]-res[j][0]);
                    }
                }
            }
            res[idx].push_back(people[i]);
        }
        return res;
    }

    float knnGroup_Li(vector<float> people,int k,float rate,float epsilon){
        float preT =0;
        float origin=0;
        for(auto i: people){
            preT +=i;
            origin+=i;
        }
        vector<vector<float>> g = grouping_knn(people,k);
        pair<float, vector<float>> t = improve(g,rate);
        vector<float> curG = t.second;
        int iter = 0;
        float curT =0;
        for(auto i: curG){
            curT +=i;
        }
        while((curT - preT)/preT>epsilon) {
            iter+=1;
            preT = curT;
            vector<vector<float>> g = grouping_knn(curG,k);
            pair<float, vector<float>> t = improve(g,rate);
            vector<float> curG = t.second;
            curT =0;
            for(auto i: curG){
                curT +=i;
            }
        }
        return curT-origin;
    }

///////////////////////////////////////////////////////////////////////

    int knnGroup_Lit(vector<float> people,int k,float rate,float epsilon){
        float preT =0;
        float origin=0;
        for(auto i: people){
            preT +=i;
            origin+=i;
        }
        vector<vector<float>> g = grouping_knn(people,k);
        pair<float, vector<float>> t = improve(g,rate);
        vector<float> curG = t.second;
        int iter = 1;
        float curT =0;
        for(auto i: curG){
            curT +=i;
        }
        while((curT - origin)<epsilon and iter<20) {
            iter+=1;
            preT = curT;
            vector<vector<float>> g = grouping_knn(curG,k);
            pair<float, vector<float>> t = improve(g,rate);
            vector<float> curG = t.second;
            curT =0;
            for(auto i: curG){
                curT +=i;
            }
        }
        return iter;
    }
    int randGroup_Lit(vector<float> people,int k,float rate,float epsilon){
        float preT =0;
        for(auto i: people){
            preT +=i;
        }
        vector<vector<float>> g = grouping_rand(people,k);
        float origin =0;
        for(auto i:people){
            origin += i;
        }
        pair<float, vector<float>> t = improve(g,rate);
        vector<float> curG = t.second;
        int iter = 1;
        float curT =0;
        for(auto i: curG){
            curT +=i;
        }
        while((curT - origin)<epsilon and iter<20) {
            iter+=1;
            preT = curT;
            vector<vector<float>> g = grouping_rand(curG,k);
            pair<float, vector<float>> t = improve(g,rate);
            vector<float> curG = t.second;
            curT =0;
            for(auto i: curG){
                curT +=i;
            }
        }
        return iter;
    }
    int rakeshGroup_Lit( vector<float> people,int k,float rate,float epsilon){
        float preT =0;
        float origin =0;
        for(auto i: people){
            preT +=i;
            origin+=i;
        }
        vector<vector<float>> g = grouping_rakesh(people,k);
        pair<float, vector<float>> t = improve(g,rate);
        vector<float> curG = t.second;
        int iter = 1;
        float curT =0;
        for(auto i: curG){
            curT +=i;
        }
        //cout<<"curT:\t"<<curT<<endl;

        while((curT - origin)<epsilon and iter<20) {
            iter+=1;
            preT = curT;
            vector<vector<float>> g = grouping_rakesh(curG,k);
            pair<float, vector<float>> t = improve(g,rate);
            vector<float> curG = t.second;
            curT =0;
            for(auto i: curG){
                curT +=i;
            }
        }
        return iter;
    }

    int kddGroup_Lit(vector<float> people,int k,float rate,float epsilon){
        float origin =0;
        float preT =0;
        for(auto i: people){
            preT +=i;
            origin+=i;
        }
        vector<vector<float>> g = grouping_kdd(people,k);
        pair<float, vector<float>> t = improve(g,rate);
        vector<float> curG = t.second;
        int iter = 1;
        float curT =0;
        for(auto i: curG){
            curT +=i;
        }
        while((curT - origin)<epsilon and iter<20) {
            iter+=1;
            preT = curT;
            vector<vector<float>> g = grouping_kdd(curG,k);
            pair<float, vector<float>> t = improve(g,rate);
            vector<float> curG = t.second;
            curT =0;
            for(auto i: curG){
                curT +=i;
            }
        }
        return iter;
    }


    int dGroup_lineart(vector<float> people, int k, float rate, float epsilon){
        float origin=0;
        float preT =0;
        for(auto i: people){
            preT +=i;
            origin+=i;
        }
        vector<vector<float>> g1 = grouping_linear(people,k);
        pair<float, vector<float>> tr1 = improve(g1,rate);
        vector<float> curGrp= tr1.second;
        float curT =0.0;
        for(auto i: curGrp){
            curT +=i;
        }
        int iter =1;
        while((curT - origin)<epsilon and iter<20){
            iter +=1;
            preT = curT;
            g1 = grouping_linear(curGrp,k);
            tr1 = improve(g1,rate);
            curGrp= tr1.second;
            curT =0.0;
            for(auto i: curGrp){
                curT +=i;
            }
        }
        return iter;
    }
/////////////////////////////////////////////////////////////////////
    float knnGroup_Lii(vector<float> people,int k,float rate,int epsilon){
        float preT =0;
        float origin=0;
        for(auto i: people){
            preT +=i;
            origin+=i;
        }
        vector<vector<float>> g = grouping_knn(people,k);
        pair<float, vector<float>> t = improve(g,rate);
        vector<float> curG = t.second;
        int iter = 1;
        float curT =0;
        for(auto i: curG){
            curT +=i;
        }
        while(iter<epsilon) {
            iter+=1;
            preT = curT;
            vector<vector<float>> g = grouping_knn(curG,k);
            pair<float, vector<float>> t = improve(g,rate);
            vector<float> curG = t.second;
            curT =0;
            for(auto i: curG){
                curT +=i;
            }
        }
        return curT-origin;
    }
    float randGroup_Lii(vector<float> people,int k,float rate,int epsilon){
        float preT =0;
        for(auto i: people){
            preT +=i;
        }
        vector<vector<float>> g = grouping_rand(people,k);
        float origin =0;
        for(auto i:people){
            origin += i;
        }
        pair<float, vector<float>> t = improve(g,rate);
        vector<float> curG = t.second;
        int iter = 1;
        float curT =0;
        for(auto i: curG){
            curT +=i;
        }
        while(iter<epsilon) {
            iter+=1;
            vector<vector<float>> g = grouping_rand(curG,k);
            pair<float, vector<float>> t = improve(g,rate);
            vector<float> curG = t.second;
            curT =0;
            for(auto i: curG){
                curT +=i;
            }
        }
        return curT-origin;
    }
    float rakeshGroup_Lii( vector<float> people,int k,float rate,int epsilon){
        float preT =0;
        float origin =0;
        for(auto i: people){
            preT +=i;
            origin+=i;
        }
        vector<vector<float>> g = grouping_rakesh(people,k);
        pair<float, vector<float>> t = improve(g,rate);
        vector<float> curG = t.second;
        int iter = 1;
        float curT =0;
        for(auto i: curG){
            curT +=i;
        }
        //cout<<"curT:\t"<<curT<<endl;

        while(iter<epsilon) {
            iter+=1;
            vector<vector<float>> g = grouping_rakesh(curG,k);
            pair<float, vector<float>> t = improve(g,rate);
            vector<float> curG = t.second;
            curT =0;
            for(auto i: curG){
                curT +=i;
            }
        }
        return curT-origin;
    }

    float kddGroup_Lii(vector<float> people,int k,float rate,int epsilon){
        float origin =0;
        float preT =0;
        for(auto i: people){
            preT +=i;
            origin+=i;
        }
        vector<vector<float>> g = grouping_kdd(people,k);
        pair<float, vector<float>> t = improve(g,rate);
        vector<float> curG = t.second;
        int iter = 1;
        float curT =0;
        for(auto i: curG){
            curT +=i;
        }
        while(iter<epsilon) {
            iter+=1;
            vector<vector<float>> g = grouping_kdd(curG,k);
            pair<float, vector<float>> t = improve(g,rate);
            vector<float> curG = t.second;
            curT =0;
            for(auto i: curG){
                curT +=i;
            }
        }
        return curT-origin;
    }

    float norm_vari(vector<float> people){
        float m=0;
        int n = people.size();
        float mi=10000000,mx =0;
        for(auto i  : people){
            m+=i;
            mi = min(mi,i);
            mx = max(mx,i);
        }
        m /=n;
        float v=0;
        for(auto i : people){
            v += (i-m)*(i-m);
        }
        v /=n;
        return v;
    }




    float dGroup_lineari(vector<float> people, int k, float rate, int epsilon){
        float origin=0;
        float preT =0;
        for(auto i: people){
            preT +=i;
            origin+=i;
        }
        vector<vector<float>> g1 = grouping_linear(people,k);
        pair<float, vector<float>> tr1 = improve(g1,rate);
        vector<float> curGrp= tr1.second;
        float curT =0.0;
        for(auto i: curGrp){
            curT +=i;
        }
        int iter =1;
        while(iter<epsilon){
            iter +=1;
            g1 = grouping_linear(curGrp,k);
            tr1 = improve(g1,rate);
            curGrp= tr1.second;
        }
        curT =0.0;
        for(auto i: curGrp){
            curT +=i;
        }
        return curT-origin;
    }

    vector<float> dGroup_lineari_var(vector<float> people, int k, float rate, int epsilon){
        float origin=0;
        float preT =0;
        for(auto i: people){
            preT +=i;
            origin+=i;
        }
        vector<float> round_gain;
        vector<vector<float>> g1 = grouping_linear(people,k);
        pair<float, vector<float>> tr1 = improve(g1,rate);
        vector<float> curGrp= tr1.second;
        float curT =0.0;
        for(auto i: curGrp){
            curT +=i;
        }
        round_gain.push_back(norm_vari(curGrp));
        int iter =1;
        float mi = 100;
        while(iter<epsilon){
            preT = curT;
            iter +=1;
            g1 = grouping_linear(curGrp,k);
            tr1 = improve(g1,rate);
            curGrp= tr1.second;
            curT =0.0;
            mi = 100;
            for(auto i: curGrp){
                curT +=i;
                mi = min(mi,i);
            }
            round_gain.push_back(norm_vari(curGrp));
        }
        cout<<mi<<endl;
        return round_gain;
    }

///////////////////////////////////////////////////////////////////////////////////////////////

//
//
//
//


    void comb(vector<int> w, int offset,int k, set<set<set<int>>>& com,set<int>& grp){
        if(k==0){
            set<set<int>> temp;
            set<int> g2;
            temp.insert(grp);
            for(auto i:w){
                if(grp.find(i)==grp.end()){
                    g2.insert(i);
                }
            }
            temp.insert(g2);
            com.insert(temp);
            //grp.clear();
            return;
        }
        for(int i =offset;i<w.size();i++){
            grp.insert(i);
            comb(w,i+1,k-1,com,grp);
            grp.erase(i);
        }
    }


    void combG(set<set<set<int>>> com,vector<vector<vector<int>>>& pGroups){
        for(auto i: com){
            vector<vector<int>> tgs;
            for(auto j: i){
                vector<int> tg(j.begin(),j.end());
                tgs.push_back(tg);
            }
            pGroups.push_back(tgs);
        }
    }


    void allGroungs(int iter,int a,vector<vector<vector<int>>> groups,vector<vector<vector<int>>> pGroups,vector<vector<vector<vector<int>>>>& groupings){
        if(a==iter){
            groupings.push_back(groups);
            if(!groupings.size()%100000) {
                cout<<groupings.size()<<endl;
            }
        }
        else{
            for (int i = 0; i < pGroups.size(); ++i) {
                vector<vector<vector<int>>> gp2 = groups;
                gp2.push_back(pGroups[i]);
                allGroungs(iter,a+1,gp2,pGroups,groupings);
            }
        }
    }


    float grouingBF(vector<float> workers,int k,float rate,int iter){
        int n = workers.size();
        int x = n/k;
        //workers = {29   ,   85    ,  89   ,   90    ,  90    ,  92};
        sort(workers.begin(),workers.end());
        //aFun = {0.25  ,  0.35};
        set<set<set<int>>> com;
        set<int> grp;
        vector<int> idx;
        for(int i = 0;i<n;i++) idx.push_back(i);
        comb(idx,0,n/2,com,grp);
        vector<vector<vector<int>>> pGroups;
        vector<vector<vector<vector<int>>>> groupings;
        combG(com,pGroups);
        allGroungs(iter,0,{},pGroups,groupings);
        vector<vector<vector<int>>> mxG;
        vector<vector<float>> res;
        float mx =0;
        for(int i =0 ;i<groupings.size();i++){
            float addit =0;
            vector<vector<float>> temp;
            pair<float, vector<float>> t({0.0,workers});
            temp.push_back(workers);
            for (int j = 0; j < groupings[i].size(); ++j) {
                t  = learning_star(groupings[i][j],t.second,rate);
                addit +=t.first;
                temp.push_back(t.second);
            }
            if(addit>mx){
                mx = addit;
                mxG = groupings[i];
                res = temp;
            }
        }
//        for(auto i : res){
//            for(auto j :i){
//                cout<<j<<'\t';
//            }
//            cout<<endl;
//        }
        return mx;
    }

    vector<float> grouingBF2(vector<float> workers,int k,float rate,int iter){
        int n = workers.size();
        int x = n/k;
        //workers = {29   ,   85    ,  89   ,   90    ,  90    ,  92};
        //sort(workers.begin(),workers.end());
        //aFun = {0.25  ,  0.35};

        set<set<set<int>>> com;
        set<int> grp;
        vector<int> idx;
        for(int i = 0;i<n;i++) idx.push_back(i);
        comb(idx,0,n/2,com,grp);
        vector<vector<vector<int>>> pGroups;
        vector<vector<vector<vector<int>>>> groupings;
        combG(com,pGroups);
        allGroungs(iter,0,{},pGroups,groupings);
        vector<vector<vector<int>>> mxG;
        vector<vector<float>> res;
        float mx =0;
        vector<float> rg;
        for(int i =0;i<groupings.size();i++){
            float addit =0;
            vector<float> round_gain;
            vector<vector<float>> temp;
            float pre =0;
            for(int q : workers) pre +=q;
            pair<float, vector<float>> t({0.0,workers});
            temp.push_back(workers);
            for (int j = 0; j < groupings[i].size(); ++j) {
                t  = learning_star(groupings[i][j],t.second,rate);
                addit +=t.first;
                round_gain.push_back(t.first-pre);
                pre = t.first;
                temp.push_back(t.second);
            }
            if(addit>mx){
                mx = addit;
                mxG = groupings[i];
                res = temp;
                rg = round_gain;
            }
        }

        for(auto i : mxG){
            for(auto j :i){
                for(int q: j) {
                    cout << q << '\t';
                }
                cout<<"||\t";
            }
            cout<<endl;
        }

        for(auto i : res){
            for(auto j :i){
                    cout << j << '\t';
            }
            cout<<endl;
        }
        return rg;
    }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

    vector<vector<float>> vgrouping_linear(vector<float> people,int k){
        vector<vector<float>> res(k,vector<float>());
        sort(people.begin(),people.end());
        int n = people.size();
        for(int i = 0;i<k;i++){
            res[i].push_back(people[n-1-i]);
        }
        for(int i =0;i<k;i++){
            for(int j = i*(n/k-1);j<(n/k-1)*(i+1);j++){
                res[k-1-i].push_back(people[j]);
            }
        }
        return res;
    }

    vector<float> vdGroup_lineari(vector<float> people, int k, float rate, int epsilon){
        float origin=0;
        float preT =0;
        for(auto i: people){
            preT +=i;
            origin+=i;
        }
        vector<float> round_gain;
        vector<vector<float>> g1 = vgrouping_linear(people,k);
        pair<float, vector<float>> tr1 = improve(g1,rate);
        vector<float> curGrp= tr1.second;
        float curT =0.0;
        for(auto i: curGrp){
            curT +=i;
        }
        round_gain.push_back(curT-preT);
        int iter =1;
        while(iter<epsilon){
            preT = curT;
            iter +=1;
            g1 = vgrouping_linear(curGrp,k);
            tr1 = improve(g1,rate);
            curGrp= tr1.second;
            curT =0.0;
            for(auto i: curGrp){
                curT +=i;
            }
            round_gain.push_back(curT-preT);
        }
        return round_gain;
    }

    vector<float> newdGroup_lineari_var(vector<float> people, int k, float rate, int epsilon){
        float origin=0;
        float preT =0;
        for(auto i: people){
            preT +=i;
            origin+=i;
        }
        vector<float> round_gain;
        vector<vector<float>> g1 = vgrouping_linear(people,k);
        pair<float, vector<float>> tr1 = improve(g1,rate);
        vector<float> curGrp= tr1.second;
        float curT =0.0;
        for(auto i: curGrp){
            curT +=i;
        }
        round_gain.push_back(norm_vari(curGrp));
        int iter =1;
        float mi = 100;
        while(iter<epsilon){
            preT = curT;
            iter +=1;
            g1 = vgrouping_linear(curGrp,k);
            tr1 = improve(g1,rate);
            curGrp= tr1.second;
            curT =0.0;
            mi = 100;
            for(auto i: curGrp) {
                curT += i;
                mi = min(mi, i);
            }
            round_gain.push_back(norm_vari(curGrp));
        }
        cout<<mi;
        return round_gain;
    }

    float newdGroup_lineari(vector<float> people, int k, float rate, int epsilon){
        float origin=0;
        float preT =0;
        for(auto i: people){
            preT +=i;
            origin+=i;
        }
        vector<vector<float>> g1 = vgrouping_linear(people,k);
        pair<float, vector<float>> tr1 = improve(g1,rate);
        vector<float> curGrp= tr1.second;
        float curT =0.0;
        for(auto i: curGrp){
            curT +=i;
        }
        int iter =1;
        while(iter<epsilon){
            preT = curT;
            iter +=1;
            g1 = vgrouping_linear(curGrp,k);
            tr1 = improve(g1,rate);
            curGrp= tr1.second;
            curT =0.0;
            for(auto i: curGrp){
                curT +=i;
            }
        }
        return curT;
    }


    float newGroup_lineari(vector<float> people, int k, float rate, int epsilon){
        float origin=0;
        float preT =0;
        for(auto i: people){
            preT +=i;
            origin+=i;
        }
        vector<float> round_gain;
        vector<vector<float>> g1 = vgrouping_linear(people,k);
        pair<float, vector<float>> tr1 = improve(g1,rate);
        vector<float> curGrp= tr1.second;
        float curT =0.0;
        for(auto i: curGrp){
            curT +=i;
        }
        round_gain.push_back(curT-preT);
        int iter =1;
        while(iter<epsilon){
            preT = curT;
            iter +=1;
            g1 = vgrouping_linear(curGrp,k);
            tr1 = improve(g1,rate);
            curGrp= tr1.second;
            curT =0.0;
            for(auto i: curGrp){
                curT +=i;
            }
            round_gain.push_back(curT-preT);
        }
        return curT - origin;
    }

    float newdGroup_linear(vector<float> people, int k, float rate, float epsilon){
        float origin=0;
        float preT =0;
        for(auto i: people){
            preT +=i;
            origin+=i;
        }
        vector<vector<float>> g1 = vgrouping_linear(people,k);
        pair<float, vector<float>> tr1 = improve(g1,rate);
        vector<float> curGrp= tr1.second;
        float curT =0.0;
        for(auto i: curGrp){
            curT +=i;
        }
        int iter =1;
        while((curT - preT)/preT>epsilon){
            preT = curT;
            iter +=1;
            g1 = vgrouping_linear(curGrp,k);
            tr1 = improve(g1,rate);
            curGrp= tr1.second;
            curT =0.0;
            for(auto i: curGrp){
                curT +=i;
            }
        }
        return curT - origin;
    }


    vector<float> randGroup_Lii_var(vector<float> people,int k,float rate,int epsilon){
        float preT =0;
        for(auto i: people){
            preT +=i;
        }
        vector<vector<float>> g = grouping_rand(people,k);
        float origin =0;
        for(auto i:people){
            origin += i;
        }
        cout<<endl;
        vector<float> round_v;
        pair<float, vector<float>> t = improve(g,rate);
        vector<float> curG = t.second;
        round_v.push_back(norm_vari(curG));
        int iter = 1;
        float curT =0;
        for(auto i: curG){
            curT +=i;
        }
        while(iter<epsilon) {
            iter+=1;
            vector<vector<float>> g = grouping_rand(curG,k);
            pair<float, vector<float>> t = improve(g,rate);
            curG = t.second;
            round_v.push_back(norm_vari(curG));
            curT =0;
            for(auto i: curG){
                curT +=i;
            }
        }
        return round_v;
    }
}





#endif //MAXLEARNING_GROUP_LINEAR_H
