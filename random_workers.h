//
// Created by dongwei on 10/9/19.
//
#include <vector>
#include <cstdlib>
#include <math.h>
#include <iostream>
#include <random>
#include <assert.h>
#include <curses.h>

using namespace std;
#ifndef MAXLEARNING_RANDOM_WORKERS_H
#define MAXLEARNING_RANDOM_WORKERS_H
namespace random_w{
    int zipf(double alpha, int n)
    {
        static int first = TRUE;      // Static first time flag
        static double c = 0;          // Normalization constant
        static double *sum_probs;     // Pre-calculated sum of probabilities
        double z;                     // Uniform random number (0 < z < 1)
        int zipf_value;               // Computed exponential value to be returned
        int    i;                     // Loop counter
        int low, high, mid;           // Binary-search bounds

        // Compute normalization constant on first call only
        if (first == TRUE)
        {
            for (i=1; i<=n; i++)
                c = c + (1.0 / pow((double) i, alpha));
            c = 1.0 / c;

            sum_probs = static_cast<double *>(malloc((n + 1) * sizeof(*sum_probs)));
            sum_probs[0] = 0;
            for (i=1; i<=n; i++) {
                sum_probs[i] = sum_probs[i-1] + c / pow((double) i, alpha);
            }
            first = FALSE;
        }

        // Pull a uniform random number (0 < z < 1)
        default_random_engine generator;
        uniform_real_distribution<double> distribution(0.0,1.0);
        do
        {
            z = distribution(generator);
        }
        while ((z == 0) || (z == 1));

        // Map z to the value
        low = 1, high = n, mid;
        do {
            mid = floor((low+high)/2);
            if (sum_probs[mid] >= z && sum_probs[mid-1] < z) {
                zipf_value = mid;
                break;
            } else if (sum_probs[mid] >= z) {
                high = mid-1;
            } else {
                low = mid+1;
            }
        } while (low <= high);

        // Assert that zipf_value is between 1 and N
        assert((zipf_value >=1) && (zipf_value <= n));

        return(zipf_value);
    }




    vector<double> rWorkers_logNormal(int n,double std){
        default_random_engine generator;
        normal_distribution<double> distribution(0.0,std);
        vector<double> res;
        for(int i =0;i<n;i++){
            double t = distribution(generator);
            t =exp(t);
            res.push_back(t);
        }
        return res;
    }
    vector<int> rWorkers_zipf(int n){
        vector<int> res;
        for(int i =0;i<n;i++){
            int t =zipf(1.0,10);
            res.push_back(t);
        }
        return res;
    }
}




#endif //MAXLEARNING_RANDOM_WORKERS_H
