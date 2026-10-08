// sllist.h - singly linked list class
// Copyright 2026 Humberto Ortiz Zuazaga
// Based on SLList class by Pat Morin
// in https://opendatastructures.org/
// Released under
// https://creativecommons.org/licenses/by/2.5/ca/

#include <mutex>
#ifndef SLLIST_H
#define SLLIST_H

template<class T>
class SLList {
  class Node {
    
  public:
    T value;
    Node *next;

    Node(T x) {
      value = x;
      next = nullptr;
    }
  };
  // Son listas dentro del arreglo que apuntan a nodos. Aquí es donde los ip addresses se encuentran o se ponen. 
  public:

  Node* head;   
  Node* tail;     
  int count; 
  mutable std::mutex mtx; 

 public:

  // Constructor
  SLList() { 
    // Las listas empiezan no conteniendo nada.
    head = tail = nullptr;
    count = 0;
  }

  ~SLList () {
    Node *u = head;
    while (u != nullptr) {
      Node *w = u;              // dereferenced w es igual a u.
      u = u->next;              // se pasa u al próximo espacio.
      delete w;
    }
    head = nullptr;
    tail = nullptr;
  }

  void push(T x) {
    std::lock_guard<std::mutex> guard(mtx);
    
    Node *u = new Node(x);

    u->next = head;
    head = u;

    if (tail == nullptr){
      tail = u;
      count++;
    }
  }

  T pop() {
    std::lock_guard<std::mutex> guard(mtx);
    if(head == nullptr){
      throw std::runtime_error("El stack está vacío");
    }

    Node *u = head;
    T x = u->value;
    head = u->next;
    delete u;
    if (nullptr == head) tail = nullptr;
    count--;
    return x;
  }

  void enqueue(T x) {
    std::lock_guard<std::mutex> guard(mtx);
    Node *u = new Node(x);
    if (nullptr == head) {	// si la lista esta vacia
      head = u;			// enlazamos u al principio
    } else {			// si no
      tail->next = u;		// enlazamos u al final
    }
    tail = u;
    count++;
  }

  T dequeue() {
    std::lock_guard<std::mutex> guard(mtx);
    return pop();
  }   

  void add(T x) {
    std::lock_guard<std::mutex> guard(mtx);
     // TODO: Add x to the linked list
    enqueue(x);
  }

  bool find(T x) {
    std::lock_guard<std::mutex> guard(mtx);
    // TODO: return true if x is in the list
    Node *u = head;
    while(u != nullptr){
        if(u->value == x){
            return true;
        }
        u = u->next;
    }
    return false;
  }

   bool is_empty() {
    std::lock_guard<std::mutex> guard(mtx);
    return head == nullptr;
  }

  //Añado método size
  int size(){
    std::lock_guard<std::mutex> guard(mtx);
    return count;
  }

};

#endif