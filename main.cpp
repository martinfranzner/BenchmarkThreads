//
//  main.cpp
//  BenchmarkThreads
//
//  Created by Martin Franzner on 24/08/17.
//  Copyright © 2017 Martin Franzner. All rights reserved.
//

#include <thread>
#include <iostream>
#include <stdio.h>
#include	<chrono>
#include	<cstdint>
#include	<iomanip>
#include <vector>

long double numberOfThreads = 64;
long double threadsVector[256];

uint64_t	rdtscp(){
				unsigned	int	lo,hi;
				asm	volatile	("rdtscp"	:	"=a"	(lo),	"=d"	(hi));
				return	((uint64_t)hi	<<	32)	|	lo;
}

void pifunc(int tam, int posVetor){
    using	namespace	std::chrono;
    using	namespace	std;
    //auto	t0 = steady_clock::now();
    //auto	r0 = rdtscp();
    long double soma=3.0, n=1.0;
    for (long double i = 0; i < tam; i++) {
        threadsVector[posVetor] += (4*n)/( (2 * i + 2)*(2 * i + 3)*(2 * i + 4));
        n=-n;
    }
    threadsVector[posVetor] += soma;
    //auto	d = steady_clock::now() - t0;
    //auto dc = rdtscp() - r0;
    //cout << duration_cast<milliseconds>(d).count() << "ms" << endl;
    
}

int main(int argc, const char * argv[]) {
    using namespace std;
    using	namespace	std::chrono;
    using	namespace	std;
    /*using	namespace	std::chrono;
    using	namespace	std;
    
    
    auto	t0 = steady_clock::now();
    auto	r0 = rdtscp();
    long double soma=3.0, n=1.0;
    for (long double i = 0; i < 1000000000; i++) {
        soma += (4*n)/( (2 * i + 2)*(2 * i + 3)*(2 * i + 4));
        n=-n;
    }
    auto	d = steady_clock::now() - t0;
    auto dc = rdtscp() - r0;
    cout << duration_cast<milliseconds>(d).count() << "ms" << endl;
    cout<< "Clock: "<< dc<<endl;
    */
    
    long double timesGlobal = 1000000000;
    
    long double times = timesGlobal / numberOfThreads;
    vector<thread> vet (256);

    
    
    auto	t0 = steady_clock::now();
    for(int i = 0; i < numberOfThreads; i = i+4){
        vet[i] = thread(pifunc,times,i);
    }
    for(int i = 0; i < numberOfThreads; i= i+4){
        vet[i].join();
    }
    /*thread t1(pifunc,times,0);
    thread t2(pifunc,times,1);
    t1.join();
    t2.join();
    */
    auto	d = steady_clock::now() - t0;
    cout << duration_cast<milliseconds>(d).count() << "ms" << endl;

    for(int i = 0; i < numberOfThreads; i++){
        cout<<threadsVector[i]<<endl;
    }
    /*
    long double contaFinal =threadsVector[0];
    cout<< "resultado thread 1:"<<contaFinal<<endl;
    contaFinal = threadsVector[1];
    cout<< "resultado thread 1:"<< contaFinal<<endl;
     */

    
     
    return 0;
}
