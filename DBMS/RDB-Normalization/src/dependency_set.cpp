

#include "dependency_set.hpp"
#include <iostream>

void DependencySet::add(const Dependency& dep)
{
  if (dep.beta <= dep.alpha)
    return;
  bool flag = false;
  for (auto& [alpha, beta] : deps_)
    if (alpha == dep.alpha)
      beta += dep.beta - dep.alpha, flag = true;
  if (!flag)
    deps_.push_back(Dependency(dep.alpha, dep.beta - dep.alpha));
}

AttributeSet DependencySet::closure(const AttributeSet& attrs) const
{
  AttributeSet res = attrs;
  bool flag;
  do
  {
    flag = false;
    for (auto [alpha, beta] : deps_)
      if (alpha <= res && res + beta != res)
        res += beta, flag = true;
  } while (flag);
  return res;
}

DependencySet DependencySet::canonicalCover() const
{
  DependencySet res{*this};
  bool flag;
  do
  {
    flag = false;
    for (size_t idx = 0; idx < res.size(); idx++)
    {
      auto [alpha, beta] = res[idx];
      auto ita = alpha.iterator();
      while (ita.hasNext())
      {
        auto A = ita.next();
        auto gamma = alpha;
        gamma.erase(A);
        if (beta <= res.closure(gamma))
        {
          std::swap(res[idx], res[res.size() - 1]);
          res.deps_.pop_back();
          res.add(Dependency(gamma, beta));
          flag = true;
          break;
        }
      }
      if (flag)
        break;
      auto itb = beta.iterator();
      while (itb.hasNext())
      {
        auto A = itb.next();
        res[idx].beta.erase(A);
        if (res.closure(alpha).find(A))
        {
          flag = true;
          break;
        }
        res[idx].beta.insert(A);
      }
      if (flag)
        break;
    }
  } while (flag);
  return res;
}

size_t DependencySet::size() const
{
  return deps_.size();
}

Dependency& DependencySet::operator[](size_t idx)
{
  if (idx >= size())
    throw std::out_of_range("argument:idx is out of bound");
  return deps_[idx];
}

const Dependency& DependencySet::operator[](size_t idx) const
{
  if (idx >= size())
    throw std::out_of_range("argument:idx is out of bound");
  return deps_[idx];
}

std::ostream& operator<<(std::ostream& os, const DependencySet& a)
{
  for (auto dep : a.deps_)
    os << dep << std::endl;
  return os;
}
