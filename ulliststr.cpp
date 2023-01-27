
#include <cstddef>
#include <stdlib.h>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE

void ULListStr::push_back(const std::string& val)
{
  //Case for very first item
  if(tail_ == NULL)
  {
    tail_ = new Item();
    tail_->last++;
    tail_->val[tail_->first] = val;
    head_=tail_;
    ++size_;
  }
  //Case for one or more items
  else
  {
    //if right side of item is full, create next item and insert into the first val
    if(tail_->last < ARRSIZE)
    {
      tail_->val[tail_->last] = val;
      tail_->last++;
      size_++;
      
    }
    //if right side isnt full yet add to current item
    else
    {
     Item* current = new Item;
      current->val[current->last] = val;
      current->last++;
      tail_->next = current;
      current-> prev = tail_;
      tail_= current;
      size_++;
      current->next = NULL;
    }
  }
}


void ULListStr::pop_back()
{
  if(head_ == NULL){
    throw std::invalid_argument("Error");
  }
  else if(tail_){
    tail_->last--;
    size_--;
  }

  if(tail_->first == tail_->last){
    if(head_ == tail_){
      delete head_;
      head_ = NULL;
      tail_ = NULL;
    }
    //case if there is only one value left in the item
    else{
      Item* current = tail_;
      tail_ = tail_->prev;
      delete current;
      tail_->next = NULL;
    }
  }
}
  //case if there is more than one value left in the tail item


void ULListStr::push_front(const std::string& val)
{
  //Case for very first item
  if(head_ == NULL)
  {
    Item* current = new Item;
    head_ = current;
    tail_ = current;
    current->last = 1;
    current->first = 0;
    current->val[0] = val;
    size_++;
  }
  //case for one or more items
  else
  {
    //if left side of item is full, create next item and insert into the last val
    if(head_->first == 0)
    {
      Item* current = new Item;
      current->next = head_;
      head_->prev = current;
      head_ = current;
      head_->val[ARRSIZE-1] = val;
      head_->first = ARRSIZE-1;
      head_->last = ARRSIZE;
      size_++;
    }
    //if left side isnt full yet add to current item
    else
    {
      head_->val[head_->first - 1] = val;
      head_->first--;
      size_++;
    }
  }

}


void ULListStr::pop_front()
{

  if(head_ == NULL){
    throw std::invalid_argument("Error");
  }
  else{
    head_->first++;
    size_--;
  }
  //case if there is only one value left in the item
  if(head_->first == head_->last){
    if(head_ == tail_){
      tail_ = NULL;
      delete head_;
      head_=NULL;
    }else{
      Item* current = head_;
      head_= head_->next;
      delete current;
      head_ ->prev = NULL;
    }
  }
}
  //case if there is more than one value left in the tail item



std::string const & ULListStr::back() const
{
  return tail_->val[tail_->last - 1];
}

std::string const & ULListStr::front() const
{
  return head_->val[head_->first];
}

std::string* ULListStr::getValAtLoc(size_t loc) const
{
  if(loc > size_){
    return NULL;
  }
  if(empty()){
    return NULL;
  }


  Item* current = head_;
  size_t counter = 0;

    // Iterate through the list until the item at the requested index is found
  while (counter + (current->last - current->first) <= loc) {
    counter += current->last - current->first;
    current = current->next;
  }

    // Return a pointer to the requested value
  return &(current->val[loc - counter + current->first]);

}


void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}