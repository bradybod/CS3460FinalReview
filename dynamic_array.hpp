//
// Created by Brady Bodily on 12/10/19.
//
#pragma once

#include <stdexcept>
#include <initializer_list>
#include <iterator>

template <typename T, uint64_t Size>
class dynamic_array {
  using size_type = std::size_t;

private:
  size_type _array_size;
  size_type _current_size;
  T* _data;

public:

  ///
  ///Constructors
  ///
  dynamic_array();
  dynamic_array(std::initializer_list<T> initializerList);

  ///
  ///Operator Overloads
  ///

  T &operator [] (uint64_t index);
  T &operator * (){ return _data[0]; }
  bool operator== (const dynamic_array rhs);

  ///
  ///Functions
  ///
  void push_back(T val);

  ///
  ///Nested Iterator Class
  ///

  class iterator
  {
  public:
    using iterator_category = std::forward_iterator_tag;
    iterator() :
        m_pos(0),
        m_data(nullptr) {}
    iterator(const iterator& obj);
    iterator(T* m_data) :
        m_data(m_data),
        m_pos(0) {}
    iterator(size_type pos, T* m_data) :
        m_pos(m_pos),
        m_data(m_data) {}

    T& operator*() { return m_data[m_pos]; }

    iterator operator++();
    iterator operator++(int);

    bool operator==(const iterator& rhs)
    {
      return m_pos == rhs.m_pos && m_data == rhs.m_data;
    }

    bool operator!=(const iterator& rhs)
    {
      return !operator==(rhs);
    }

  private:
    size_type m_pos;
    T* m_data;
  };

  iterator begin() { return iterator(_data); }
  iterator end() { return iterator(_current_size, _data); }
};


///
///Array Constructors
///
template <typename T, uint64_t Size>
dynamic_array<T, Size>::dynamic_array(){
  _array_size = Size;
  _current_size = 0;
  _data = new T[_array_size];
}

template <typename T, uint64_t Size>
dynamic_array<T, Size>::dynamic_array(std::initializer_list<T> initializerList)
: _array_size(Size), _current_size(0), _data(new T[Size]) {
  if(initializerList.size() > _array_size){
    throw new std::out_of_range("More values than allocated for size");
  }
  for(auto val : initializerList){
    _data[_current_size++] = val;
  }
}


///
///operator overloads
///
template <typename T, uint64_t Size>
T& dynamic_array<T, Size>::operator[](uint64_t index) {
  if(index < 0 || index > _current_size)
    throw std::out_of_range("Index out of range good luck finding it");
  return _data[index];
}

template <typename T, uint64_t Size>
bool dynamic_array<T, Size>::operator==(const dynamic_array rhs){
  if(this->_current_size != rhs._current_size)
    return false;
  for(uint64_t i = 0; i < Size; i++){
    if(this->_data[i] != rhs._data[i])
      return false;
  }
  return true;
}

///
///Insert Function
///

template <typename T, uint64_t Size>
void dynamic_array<T, Size>::push_back(T val) {
  if(_current_size == _array_size){
    T* new_array = new T[_array_size * 2];
    for(uint64_t i = 0; i < _current_size; i++){
      new_array[i] = _data[i];
    }
    delete [] _data;
    _data = new_array;
    this->push_back(val);
  }else{
    _data[_current_size++] = val;
  }
}

///
///Iterator Functions
///

template <typename T, uint64_t Start>
dynamic_array<T, Start>::iterator::iterator(const iterator& obj)
{
  this->m_pos = obj.m_pos;
  this->m_data = obj.m_data;
}

/// Prefix ++i
template <typename T, uint64_t Size>
typename dynamic_array<T, Size>::iterator dynamic_array<T, Size>::iterator::operator++()
{
  m_pos++;
  return *this;
}

/// Postfix i++
template <typename T, uint64_t Size>
typename dynamic_array<T, Size>::iterator dynamic_array<T, Size>::iterator::operator++(int)
{
  iterator i = *this;
  m_pos++;
  return i;
}

// DYNAMICARRAY_DYNAMIC_ARRAY_HPP
