#pragma once
#include <algorithm>
#include <cstddef>
#include <ostream>
#include <utility>

template<class T, size_t BASE_CAPACITY = 10, float GROWTH_FACTOR = 2.0f>
class UnorderedVector {
  T* m_data = nullptr;
  std::size_t m_size = 0, m_capacity = 0;

public:
  explicit UnorderedVector(const size_t capacity = BASE_CAPACITY)
    : m_data(new T[capacity]), m_size(0), m_capacity(capacity) {}

  ~UnorderedVector() {
    delete[] m_data;
  }

  UnorderedVector(const UnorderedVector& other) {
    delete[] m_data;
    m_data = new T[other.m_capacity];
    std::copy(other.m_data, other.m_data + other.m_size, m_data);
  }

  UnorderedVector& operator=(const UnorderedVector& other) {
    if (this != &other) {
      delete[] m_data;
      m_data = new T[other.m_capacity];
      std::copy(other.m_data, other.m_data + other.m_size, m_data);
    }
    return *this;
  }

  UnorderedVector(UnorderedVector&& other) noexcept {
    m_data = std::exchange(other.m_data, nullptr);
    m_size = other.m_size;
    m_capacity = other.m_capacity;
  }

  UnorderedVector& operator=(UnorderedVector&& other) noexcept {
    UnorderedVector tmp(std::move(other));
    std::swap(m_data, tmp.m_data);
    std::swap(m_size, tmp.m_size);
    std::swap(m_capacity, tmp.m_capacity);
    return *this;
  }

  T& operator[](const std::size_t index) {
    return m_data[index];
  }

  const T& at(const std::size_t index) const {
    return m_data[index];
  }

  void remove_at(const std::size_t index) {
    std::swap(m_data[index], m_data[m_size - 1]);
    m_size--;
  }

  void push_back(const T& value) {
    if (m_size == m_capacity) {
      m_capacity *= GROWTH_FACTOR;
      T* new_data = new T[m_capacity];
      std::copy(m_data, m_data + m_size, new_data);
      delete[] m_data;
      m_data = new_data;
    }
    m_data[m_size++] = value;
  }

  std::size_t size() const {
    return m_size;
  }

  std::size_t find(const T& value) const {
    return std::find(m_data, m_data + m_size, value) - m_data;
  }

#ifndef CAPACITY_DOUBLE_ARROW_OP
  friend std::ostream& operator<<(std::ostream& os, UnorderedVector<T>& vec) {
    auto printElement = [&os](const T& value) {
      os << value << ", ";
    };

    os << '[' << ' ';
    std::for_each(vec.m_data, vec.m_data + (vec.m_size - 1), printElement);
    os << vec.m_data[vec.m_size - 1] << " ]\n";
    return os;
  }
#else
friend std::ostream& operator<<(std::ostream& os, UnorderedVector<T>& vec) {
    auto printElement = [&os](const T& value) {
      os << value << ", ";
    };

    os << '[' << ' ';
    std::for_each(vec.m_data, vec.m_data + (vec.m_size - 1), printElement);
    os << vec.m_data[vec.m_size - 1] << "| ";

    std::for_each(vec.m_data + vec.m_size, vec.m_data + vec.m_capacity - 1, printElement);
    os << vec.m_data[vec.m_capacity - 1] << " ]\n";
    return os;
  }
#endif

};

