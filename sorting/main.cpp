//
//  main.cpp
//  sorting
//
//  Created by Zesheng Li on 11/4/15.
//  Copyright © 2015 neil. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include "mysort.h"
#include "timer.h"
using namespace std;

vector<int> RNDvector(unsigned N, int seed=0, bool seq=true, unsigned range=500){
    srand(seed);
    vector<int> v(N), w(N);
    unsigned idx;
    if (seq){
        for (int i=N-1; i!=-1; i--){
            v[i]=i+1;
        }
        
        for (int i=N-1;i!=-1;i--){
            idx=rand()%N--;
            w[i]=v[idx];
            v.erase(v.begin()+idx);
        }
        return w;
    }else{
        for (int i=N-1; i!=-1; i--){
            v[i]=rand()%(range) +1;
        }
        return v;
    }
}

void vprint(const vector<int> &v){
    for (int i=0; i<v.size();i++){
        cout<<v[i]<<' ';
    }
    cout<<endl;
}

int main(int argc, const char * argv[]) {
    const unsigned N= 4096;
    int seed=(int)time(NULL);
    
    vector<int> v0=RNDvector(N, seed, 1, N), v=v0;
    vprint(v); cout<<endl;
    
    timer t1, t2;
    mysort::perf pf;
    
    t1=tic();
    pf=mysort::qsort_fat(v); t2=tic();
    //vprint(v);
    pf.print(time_diff(t1, t2)/1000);   v=v0;
    
    t1=tic();
    pf=mysort::qsort_hoare(v); t2=tic();
    //vprint(v);
    pf.print(time_diff(t1, t2)/1000);   v=v0;
    
    t1=tic();
    pf=mysort::isort(v); t2=tic();
    //vprint(v);
    pf.print(time_diff(t1, t2)/1000);   v=v0;
    
    t1=tic();
    pf=mysort::msort_bu(v); t2=tic();
    //vprint(v);
    pf.print(time_diff(t1, t2)/1000);   v=v0;
    
    return 0;
}
