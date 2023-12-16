#ifndef ATTRIBUTE_SET_HPP
#define ATTRIBUTE_SET_HPP

#include <iostream>
#include <set>
#include <string>
#include <vector>

using Attribute = std::string;

class AttributeSet
{
public:
  class Iterator;
  AttributeSet() = default;
  AttributeSet(const std::initializer_list<Attribute>& list);
  void insert(const Attribute& attr);
  void erase(const Attribute& attr);
  size_t size() const noexcept;
  bool empty() const noexcept;
  Iterator iterator() const;
  bool find(const Attribute& attr) const;
  bool operator<(const AttributeSet& a) const;
  bool operator<=(const AttributeSet& a) const;
  bool operator==(const AttributeSet& a) const;
  bool operator!=(const AttributeSet& a) const;
  bool operator>(const AttributeSet& a) const;
  bool operator>=(const AttributeSet& a) const;
  AttributeSet operator+(const AttributeSet& a) const;
  AttributeSet& operator+=(const AttributeSet& a);
  AttributeSet operator-(const AttributeSet& a) const;
  AttributeSet& operator-=(const AttributeSet& a);
  AttributeSet operator*(const AttributeSet& a) const;
  AttributeSet& operator*=(const AttributeSet& a);
  friend std::ostream& operator<<(std::ostream& os, const AttributeSet& a);
  class Iterator
  {
  public:
    Iterator(std::set<Attribute>::iterator first, std::set<Attribute>::iterator last);
    bool hasNext() const;
    Attribute next();

  private:
    std::set<Attribute>::iterator iter;
    std::set<Attribute>::iterator end;
  };

private:
  std::set<Attribute> attrs_;
};

#endif
