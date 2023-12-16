#include "attribute_set.hpp"

AttributeSet::AttributeSet(const std::initializer_list<Attribute>& list)
    : attrs_{list}
{
}

void AttributeSet::insert(const Attribute& attr)
{
  attrs_.insert(attr);
}

void AttributeSet::erase(const Attribute& attr)
{
  if (attrs_.find(attr) != attrs_.end())
    attrs_.erase(attrs_.find(attr));
}

size_t AttributeSet::size() const noexcept
{
  return attrs_.size();
}

bool AttributeSet::empty() const noexcept
{
  return attrs_.empty();
}

AttributeSet::Iterator AttributeSet::iterator() const
{
  return Iterator(attrs_.begin(), attrs_.end());
}

bool AttributeSet::find(const Attribute& attr) const
{
  return attrs_.find(attr) != attrs_.end();
}

bool AttributeSet::operator<=(const AttributeSet& a) const
{
  for (auto attr : attrs_)
    if (!a.find(attr))
      return false;
  return true;
}

bool AttributeSet::operator>=(const AttributeSet& a) const
{
  return a <= *this;
}

bool AttributeSet::operator==(const AttributeSet& a) const
{
  return *this <= a && a <= *this;
}

bool AttributeSet::operator!=(const AttributeSet& a) const
{
  return !(*this == a);
}

bool AttributeSet::operator<(const AttributeSet& a) const
{
  return *this <= a && *this != a;
}

bool AttributeSet::operator>(const AttributeSet& a) const
{
  return *this >= a && *this != a;
}

AttributeSet AttributeSet::operator+(const AttributeSet& a) const
{
  AttributeSet res{*this};
  for (auto attr : a.attrs_)
    res.insert(attr);
  return res;
}

AttributeSet AttributeSet::operator-(const AttributeSet& a) const
{
  AttributeSet res{*this};
  for (auto attr : a.attrs_)
    res.erase(attr);
  return res;
}

AttributeSet AttributeSet::operator*(const AttributeSet& a) const
{
  return operator-(operator-(a));
}

AttributeSet& AttributeSet::operator+=(const AttributeSet& a)
{
  return *this = *this + a;
}

AttributeSet& AttributeSet::operator-=(const AttributeSet& a)
{
  return *this = *this - a;
}

AttributeSet& AttributeSet::operator*=(const AttributeSet& a)
{
  return *this = *this * a;
}

std::ostream& operator<<(std::ostream& os, const AttributeSet& a)
{
  os << "(";
  for (auto it = a.attrs_.begin(); it != a.attrs_.end(); it++)
  {
    os << *it;
    if (it != --a.attrs_.end())
      os << ",";
  }
  os << ")";
  return os;
}

AttributeSet::Iterator::Iterator(std::set<Attribute>::iterator first, std::set<Attribute>::iterator last)
    : iter{first}
    , end{last}
{
}

bool AttributeSet::Iterator::hasNext() const
{
  return iter != end;
}

Attribute AttributeSet::Iterator::next()
{
  Attribute res = *iter;
  ++iter;
  return res;
}
