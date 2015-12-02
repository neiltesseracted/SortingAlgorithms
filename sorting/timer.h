//
//  timer.h
//  sorting
//
//  Created by Zesheng Li on 11/10/15.
//  Copyright © 2015 neil. All rights reserved.
//

#ifndef timer_h
#define timer_h
#endif /* timer_h */

#include <chrono>

typedef chrono::high_resolution_clock::time_point timer;

double time_diff(timer t1, timer t2){
    return chrono::duration_cast<chrono::microseconds>( t2 - t1 ).count();
}

timer tic(){
    return chrono::high_resolution_clock::now();
}