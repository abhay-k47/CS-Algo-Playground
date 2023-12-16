#include "schema.hpp"

Schema::Schema(const Attribute& name, const AttributeSet& R, const DependencySet& deps)
    : name_{name}
    , R_(R)
    , deps_(deps)
{
  for (size_t i = 0; i < deps_.size(); i++)
    if (!(deps_[i].alpha <= R && deps_[i].beta <= R))
      throw std::domain_error("Dependency Set has attributes unrelated to schema R");
}

DependencySet Schema::closure() const
{
  DependencySet res;
  for (int mask = 1; mask < (1 << R_.size()); mask++)
  {
    AttributeSet alpha;
    auto it = R_.iterator();
    size_t idx = 0;
    while (it.hasNext())
    {
      auto attr = it.next();
      if ((mask & (1 << idx)))
        alpha.insert(attr);
      idx++;
    }
    auto alpha_plus = deps_.closure(alpha);
    res.add(Dependency(alpha, alpha_plus));
    // for (int mask = 1; mask < (1 << alpha_plus.size()); mask++)
    // {
    //   AttributeSet beta;
    //   auto it = alpha_plus.iterator();
    //   size_t idx = 0;
    //   while (it.hasNext())
    //   {
    //     auto attr = it.next();
    //     if ((mask & (1 << idx)))
    //       beta.insert(attr);
    //     idx++;
    //   }
    //   res.add(Dependency(alpha, beta));
    // }
  }
  return res;
}

std::vector<AttributeSet> Schema::getSuperKeys() const
{
  auto F_plus = closure();
  std::vector<AttributeSet> res;
  for (size_t idx = 0; idx < F_plus.size(); idx++)
    if (F_plus[idx].alpha + F_plus[idx].beta == R_)
      res.push_back(F_plus[idx].alpha);
  return res;
}

std::vector<AttributeSet> Schema::getCandidateKeys() const
{
  std::vector<AttributeSet> res = getSuperKeys();
  bool flag, isCandidateKey;
  do
  {
    flag = false;
    for (size_t i = 0; i < res.size(); i++)
    {
      isCandidateKey = true;
      for (size_t j = 0; j < res.size(); j++)
      {
        if (res[i] > res[j])
        {
          isCandidateKey = false;
          break;
        }
      }
      if (!isCandidateKey)
      {
        std::swap(res[i], res.back());
        res.pop_back();
        flag = true;
        break;
      }
    }
  } while (flag);
  return res;
}

std::ostream& operator<<(std::ostream& os, const Schema& schema)
{
  os << schema.name_ << schema.R_ << std::endl << schema.deps_;
  return os;
}
