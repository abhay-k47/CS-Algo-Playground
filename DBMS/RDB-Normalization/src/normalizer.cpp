#include "normalizer.hpp"

std::vector<Schema> Normalizer2NF::normalize(const Schema& r) const
{
  std::vector<Schema> res;
  return res;
}

bool Normalizer2NF::test(const Schema& r) const
{
  auto candidateKeys = r.getCandidateKeys();
  auto nonPrimeAttrs = r.R_;
  for (auto candidateKey : candidateKeys)
    nonPrimeAttrs -= candidateKey;
  auto it = nonPrimeAttrs.iterator();
  while (it.hasNext())
  {
    auto A = it.next();
    for (auto candidateKey : candidateKeys)
    {
      for (int mask = 1; mask < (1 << candidateKey.size()) - 1; mask++)
      {
        auto it = candidateKey.iterator();
        size_t idx = 0;
        AttributeSet subset;
        while (it.hasNext())
        {
          auto attr = it.next();
          if ((mask & (1 << idx)))
            subset.insert(attr);
          idx++;
        }
        if (r.deps_.closure(subset).find(A))
          return false;
      }
    }
  }
  return true;
}

std::vector<Schema> Normalizer3NF::normalize(const Schema& r) const
{
  std::vector<Schema> res;
  auto Fc = r.deps_.canonicalCover();
  for (size_t idx = 0; idx < Fc.size(); idx++)
    res.push_back(Schema(r.name_ + "_" + std::to_string(idx + 1), Fc[idx].alpha + Fc[idx].beta, DependencySet()));
  bool flag = false;
  for (auto ri : res)
    if (r.deps_.closure(ri.R_) == r.R_)
    {
      flag = true;
      break;
    }
  if (!flag)
    res.push_back(
        Schema(r.name_ + "_" + std::to_string(res.size() + 1), r.getCandidateKeys().front(), DependencySet()));
  do
  {
    flag = false;
    for (size_t i = 0; i < res.size(); i++)
    {
      for (size_t j = 0; j < res.size(); j++)
        if (j != i && res[i].R_ <= res[j].R_)
        {
          std::swap(res[i], res.back());
          res.pop_back();
          flag = true;
          break;
        }
      if (flag)
        break;
    }
  } while (flag);

  for (size_t idx = 0; idx < r.deps_.size(); idx++)
    for (auto& ri : res)
      if (r.deps_[idx].alpha + r.deps_[idx].beta <= ri.R_)
        ri.deps_.add(r.deps_[idx]);
  return res;
}

bool Normalizer3NF::test(const Schema& r) const
{
  auto candidateKeys = r.getCandidateKeys();
  for (size_t idx = 0; idx < r.deps_.size(); idx++)
    if (r.deps_.closure(r.deps_[idx].alpha) != r.R_)
    {
      auto it = r.deps_[idx].beta.iterator();
      while (it.hasNext())
      {
        auto A = it.next();
        bool flag = false;
        for (auto candidateKey : candidateKeys)
          if (candidateKey.find(A))
          {
            flag = true;
            break;
          }
        if (!flag)
          return false;
      }
    }
  return true;
}

std::vector<Schema> NormalizerBCNF::normalize(const Schema& r) const
{
  std::vector<Schema> res = {r};
  bool flag;
  do
  {
    flag = false;
    for (auto& ri : res)
    {
      auto [rname, Ri, __] = ri;
      for (int mask = 1; mask < (1 << Ri.size()); mask++)
      {
        AttributeSet alpha;
        auto it = Ri.iterator();
        size_t idx = 0;
        while (it.hasNext())
        {
          auto attr = it.next();
          if ((mask & (1 << idx)))
            alpha.insert(attr);
          idx++;
        }
        auto alpha_plus = r.deps_.closure(alpha);
        if (!(Ri <= alpha_plus || ((alpha_plus - alpha) * Ri).empty()))
        {
          auto beta = (alpha_plus - alpha) * Ri;
          std::swap(ri, res.back());
          res.pop_back();
          res.push_back(Schema(rname + "_1", Ri - beta, DependencySet()));
          res.push_back(Schema(rname + "_2", alpha + beta, DependencySet()));
          flag = true;
          break;
        }
      }
      if (flag)
        break;
    }
  } while (flag);
  auto deps = r.closure();
  for (size_t idx = 0; idx < deps.size(); idx++)
    for (auto& ri : res)
      if (deps[idx].alpha <= ri.R_)
        ri.deps_.add(Dependency(deps[idx].alpha, deps[idx].beta * ri.R_));
  return res;
}

bool NormalizerBCNF::test(const Schema& r) const
{
  for (size_t idx = 0; idx < r.deps_.size(); idx++)
    if (r.deps_.closure(r.deps_[idx].alpha) != r.R_)
      return false;
  return true;
}

std::vector<Schema> Normalizer4NF::normalize(const Schema& r) const
{
  std::vector<Schema> res;
  return res;
}

bool Normalizer4NF::test(const Schema& r) const
{
  bool res = false;
  return res;
}