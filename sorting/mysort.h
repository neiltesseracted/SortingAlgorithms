//
//  mysort.h
//  sorting
//
//  Created by Zesheng Li on 11/4/15.
//  Copyright © 2015 neil. All rights reserved.
//

#ifndef mysort_h
#define mysort_h
#endif /* mysort_h */

#include <math.h>
using namespace std;

enum order{ascending=0, descending=1};

namespace mysort{
    typedef unsigned long vidx_t;
    typedef unsigned long performance_t;
    
    struct perf{
        perf(){num_of_elem=0;}
        perf(performance_t sz){num_of_elem=sz;}
        performance_t compare=0;
        performance_t swap=0;
        performance_t call=0;
        performance_t N(){return num_of_elem;}
        perf operator += (perf pf1){
            compare+=pf1.compare;
            swap+=pf1.swap;
            call+=pf1.call;
            return *this;
        }
        void print(double t=-1){
            cout<<"Compare= "<<compare<<"  Swap= "<<swap<<"  Call= "<<call;
            if (t!=-1) {
                cout<<"  Time: "<<t<<"ms";
            }
            cout<<endl;
            cout<<"n="<<N()<<", nlogn="<<N()*log2(N())<<", tri(n)="<<((N()+1)*N())/2<<endl<<endl;
        }
    private:
        performance_t num_of_elem;
    };
    
    template<class T>
    T pivot(const vector<T> &v, const vidx_t &lo, const vidx_t &hi){
        return v[(hi-lo)/2 + lo];
    }
    
// MARK: qsort_fat
    template<class T>
    perf qsort_fat(vector<T> &v, vidx_t lo, vidx_t hi, const bool de=false){
        perf pf;
        pf.call++;
        // base case:
        if (lo>=hi || hi==-1) {
            return pf;
        }
        
        // fat patition
        vidx_t mbed=lo, mceil=hi;
        T p = pivot(v, lo, hi), temp;
        for (vidx_t i=lo; i<=mceil; i++){
            if (v[i]< p) {
                temp=v[mbed];
                v[mbed++]=v[i];
                v[i]=temp;
                pf.swap++;
            }else if (v[i]> p){
                temp=v[mceil];
                v[mceil--]=v[i];
                v[i--]=temp;
                pf.swap++;
            }
            pf.compare++;
        }
        
        pf+=qsort_fat<T>(v, lo, mbed-1, de);
        pf+=qsort_fat<T>(v, mceil+1, hi, de);
        return pf;
    }
    perf qsort_fat(vector<int> &v, const bool de=false){
        perf pf (v.size());
        if (v.empty()){
            return pf;
        }
        pf+=qsort_fat<int>(v, 0, v.size()-1, de);
        cout<<"Sorting function used: "<<__func__<<endl;
        return pf;
    }


// MARK: qsort_hoare
    template<class T>
    perf qsort_hoare(vector<T> &v, vidx_t lo, vidx_t hi, const bool de=false){
        perf pf;
        pf.call++;
        // base case:
        if (lo>=hi) {
            return pf;
        }
        
        // Hoare partition
        vidx_t left=lo-1, right=hi+1;
        T p = pivot(v, lo, hi), temp;
        while (true){
            do {left++; pf.compare++;}while (v[left]<p);
            do {right--; pf.compare++;}while (v[right]>p);
            if(left<right){
                temp=v[left];
                v[left]=v[right];
                v[right]=temp;
                pf.swap++;
            }else{
                break;
            }
        }
        
        pf+=qsort_hoare<T>(v, lo, right, de);
        pf+=qsort_hoare<T>(v, right+1, hi, de);
        return pf;
    }
    perf qsort_hoare(vector<int> &v, const bool de=false){
        perf pf (v.size());
        if (v.empty()){
            return pf;
        }
        pf+=qsort_hoare<int>(v, 0, v.size()-1, de);
        cout<<"Sorting function used: "<<__func__<<endl;
        return pf;
    }

// MARK: isort
    template<class T>
    perf isort(vector<T> &v, vidx_t lo, vidx_t hi, const bool de=false){
        perf pf; pf.call++;
        vidx_t left;
        T vi;
        for (vidx_t i=lo+1; i<=hi; i++){
            left=i;
            vi=v[i];
            while (left>lo && v[left-1] > vi){
                v[left]=v[left-1];
                left--;
                pf.compare++;
                pf.swap++;
            }
            v[left]=vi;
            pf.compare++;
        }
        return pf;
    }
    perf isort(vector<int> &v, const bool de=false){
        perf pf(v.size());
        if (v.empty()){
            return pf;
        }
        pf+=isort<int>(v, 0, v.size()-1, de);
        cout<<"Sorting function used: "<<__func__<<endl;
        return pf;
    }
    
// MARK: msort_bu
    template<class T>
    perf msort_bu(vector<T> &v, vector<T> &w, vidx_t sub, vidx_t lo, vidx_t hi, const bool de=false){
        perf pf; pf.call++;
        // base case
        if (sub>(hi-lo)){
            w=v;
            return pf;
        }
        
        // bottom-up recursive merge from subsets of size 1
        vidx_t ileft, iright, rightstart, rightend;
        for (vidx_t iw=lo; iw<=hi;){
            ileft=iw;
            rightstart=min(iw+sub, hi);
            iright=rightstart;
            rightend=min(iw+2*sub-1, hi);
            for (; iw<=rightend; iw++){
                if (ileft<rightstart && (iright>rightend || v[ileft]<=v[iright]) ){
                    w[iw]=v[ileft++];
                }else{
                    w[iw]=v[iright++];
                }
                pf.compare++; pf.swap++;
            }
        }
        
        pf+=msort_bu(w, v, sub*2, lo, hi, de);
        return pf;
    }
    perf msort_bu(vector<int> &v, const bool de=false){
        perf pf(v.size());
        if (v.empty()){
            return pf;
        }
        vector<int> w(v.size());
        pf+=msort_bu(v, w, 1, 0, v.size()-1, de);
        cout<<"Sorting function used: "<<__func__<<endl;
        return pf;
    }
}