// fast.cpp threaded test singly linked list stacks
// Copyright 2026 Humberto Ortiz Zuazaga
// Released under
// https://creativecommons.org/licenses/by/4.0/deed.en

#include <iostream>
#include <thread>
#include "sllist.h"
using namespace std;

// how many entries to push and pop
#define STACK_OPS 10		

// a global list, both threads will use this same list
SLList<int> l;

void push_task() {
  
  for (int i = 1; i <= STACK_OPS; i++) {
    
    // hacer push a la lista global del 0 hasta la cantidad de STACK_OPS
    l.push(i);

    // Output de un mensaje
    cout << "Push " << i << endl;
  }
}

void pop_task() {
  int value;

  while(l.size() == 0){

  }

  while(l.size() < STACK_OPS){

  }

  for (int i = 0; i < STACK_OPS; i++) {
    // Verificar si la lista esta vacía
    // if(l.is_empty()){
    //   cout << "La lista esta vacía." << endl;
    //   break;
    // }

    // Verificar si la Lista esta vacía
    // while(l.is_empty() < STACK_OPS){
    //   // Espera a q push termine
    // }
    

    // 
    value = l.pop();
    // Output de un mensaje 
    cout << "Pop " << value << endl;
  }
}

int main() {

  // thread es una clase de STL
  thread t1(push_task);	// make a thread to push
  thread t2(pop_task);	// make a thread to pop

  t1.detach();			// start the push thread and don't wait
  t2.join();			// start the pop thread, and wait for it to finish
  
  return 0;
}