/*
CSCI 104: Homework 1 Problem 1

Write a recursive function to split a sorted singly-linked
list into two sorted linked lists, where one has the even 
numbers and the other contains the odd numbers. Students 
will receive no credit for non-recursive solutions. 
To test your program write a separate .cpp file and #include
split.h.  **Do NOT add main() to this file**.  When you submit
the function below should be the only one in this file.
*/

#include "split.h"

void append(Node*& list, Node*& current);

void split(Node*& in, Node*& odds, Node*& evens)
{
  if(in == nullptr){
    return;
  }
  else{

    Node* current = in;
    in = current->next;
    current->next = nullptr;

    if(current->value % 2 == 1)
    {
      if(odds == nullptr)
        {
            odds = current;
        } 
        else
        {
            append(odds, current);
        }
    }
    else
    {
        if(evens == nullptr)
        {
            evens = current;
        }
        else
        {
            append(evens, current);
        }
    }
    split(in, odds, evens);
  }
}

void append(Node*& list, Node*& current)
{
    if(list->next == nullptr)
    {
        list->next = current;
    }
    else
    {
        append(list->next, current);
    }
}
