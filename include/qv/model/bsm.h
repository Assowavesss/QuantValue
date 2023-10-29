#ifndef QV_MODEL_BSM_H
#define QV_MODEL_BSM_H

#include "data.h"
#include "../option_type.h"

namespace qv {
_BEGIN_NAMESPACE_MODEL

#ifdef QV_HAS_CONCEPTS
template<detail::real _R, bool dividend = false>
#else
template<typename _R, bool dividend = false>
#endif // QV_HAS_CONCEPTS
class bsm
{
public:
  using data_type = _R;

  static constexpr bool value_dividend = false;

  RULE_OF_FIVE_FINAL(bsm)

  _QV_CONSTEXPR_SCOPE
  bsm(const _R S, const _R K, const _R T, const _R r, const _R sigma) noexcept
    : _model(S, K, T, r, sigma)
  {
  }

  struct compute
  {

    _QV_CONSTEXPR_SCOPE
    static _R d1(const _R S, const _R K, const _R T, const _R r, const _R sigma)
    {
      _QV_STATIC_CONSTEXPR auto half{0.5};
      return (log(S / K) + (r + half * pow2(sigma)) * T) / (sigma * sqrt(T));
    }

    _QV_CONSTEXPR_SCOPE
    static _R d2(const _R S, const _R K, const _R T, const _R r, const _R sigma)
    {
      return d1(S, K, T, r, sigma) - sigma * sqrt(T);
    }

    _QV_CONSTEXPR_SCOPE
    static std::pair<_R, _R>
    d1_d2(const _R S, const _R K, const _R T, const _R r, const _R sigma)
    {
      const auto d1_result = d1(S, K, T, r, sigma);
      return std::make_pair(d1_result, d1_result - sigma * sqrt(T));
    }

    _QV_CONSTEXPR_SCOPE
    static _R
    call(const _R S, const _R K, const _R T, const _R r, const _R sigma)
    {
      const auto [d1, d2] = d1_d2(S, K, T, r, sigma);
      return S * cnd(d1) - K * exp(-r * T) * cnd(d2);
    }

    _QV_CONSTEXPR_SCOPE
    static _R
    put(const _R S, const _R K, const _R T, const _R r, const _R sigma)
    {
      const auto [d1, d2] = d1_d2(S, K, T, r, sigma);
      return K * exp(-r * T) * cnd(-d2) - S * cnd(-d1);
    }

    _QV_CONSTEXPR_SCOPE
    static std::pair<_R, _R>
    call_put(const _R S, const _R K, const _R T, const _R r, const _R sigma)
    {
      const auto [d1, d2] = d1_d2(S, K, T, r, sigma);
      return std::make_pair(S * cnd(d1) - K * exp(-r * T) * cnd(d2),
                            K * exp(-r * T) * cnd(-d2) - S * cnd(-d1));
    }

    template<option_type _Ex>
    _QV_CONSTEXPR_SCOPE static _R
    exercice(const _R S, const _R K, const _R T, const _R r, const _R sigma)
    {
      if constexpr (_Ex == option_type::Call)
        return call(S, K, T, r, sigma);
      else
        return put(S, K, T, r, sigma);
    }
  };

  _QV_CONSTEXPR_SCOPE
  _R d1() const noexcept { return compute::d1(S(), K(), T(), r(), sigma()); }

  _QV_CONSTEXPR_SCOPE
  _R d2() const noexcept { return compute::d2(S(), K(), T(), r(), sigma()); }

  _QV_CONSTEXPR_SCOPE
  std::pair<_R, _R> d1_d2() const noexcept
  {
    return compute::d1_d2(S(), K(), T(), r(), sigma());
  }

  _QV_CONSTEXPR_SCOPE
  _R call() const noexcept
  {
    return compute::call(S(), K(), T(), r(), sigma());
  }

  _QV_CONSTEXPR_SCOPE
  _R put() const noexcept { return compute::put(S(), K(), T(), r(), sigma()); }

  _QV_CONSTEXPR_SCOPE
  std::pair<_R, _R> call_put() const noexcept
  {
    return compute::call_put(S(), K(), T(), r(), sigma());
  }

  _QV_CONSTEXPR_SCOPE
  _R S() const noexcept { return _model.S(); }

  _QV_CONSTEXPR_SCOPE
  _R K() const noexcept { return _model.K(); }

  _QV_CONSTEXPR_SCOPE
  _R T() const noexcept { return _model.T(); }

  _QV_CONSTEXPR_SCOPE
  _R r() const noexcept { return _model.r(); }

  _QV_CONSTEXPR_SCOPE
  _R sigma() const noexcept { return _model.sigma(); }

  _QV_CONSTEXPR_SCOPE
  void set_S(const _R S) noexcept { _model.set_S(S); }

  _QV_CONSTEXPR_SCOPE
  void set_K(const _R K) noexcept { _model.set_K(K); }

  _QV_CONSTEXPR_SCOPE
  void set_T(const _R T) noexcept { _model.set_T(T); }

  _QV_CONSTEXPR_SCOPE
  void set_r(const _R r) noexcept { _model.set_r(r); }

  _QV_CONSTEXPR_SCOPE
  void set_sigma(const _R sigma) noexcept { _model.set_sigma(sigma); }

private:
  data<_R> _model;
};

#ifdef QV_HAS_CONCEPTS
template<detail::real _R>
#else
template<typename _R>
#endif // QV_HAS_CONCEPTS
class bsm<_R, true>
{

  class data_impl : data<_R>
  {
    using data_type = _R;
    using base = data<_R>;

  public:
    using base::base;
    using base::K;
    using base::r;
    using base::S;
    using base::sigma;
    using base::T;

    _QV_CONSTEXPR_SCOPE
    data_impl(const _R S,
              const _R K,
              const _R T,
              const _R r,
              const _R sigma,
              const _R q) noexcept
      : base(S, K, T, r, sigma), _q(q)
    {
    }

    _QV_CONSTEXPR_SCOPE
    _R q() const noexcept { return _q; }

    _QV_CONSTEXPR_SCOPE
    void set_q(const _R q) noexcept { _q = q; }

  private:
    _R _q;
  };

public:
  using data_type = _R;

  static constexpr bool dividend_value = true;

  RULE_OF_FIVE_FINAL(bsm)

  _QV_CONSTEXPR_SCOPE
  bsm(const _R S,
      const _R K,
      const _R T,
      const _R r,
      const _R sigma,
      const _R q) noexcept
    : _model(S, K, T, r, sigma, q)
  {
  }

  _QV_CONSTEXPR_SCOPE _R d1() const noexcept
  {
    _QV_STATIC_CONSTEXPR auto half{0.5};
    return (log(S() / K()) + (r() - q() + half * pow2(sigma())) * T())
           / (sigma() * sqrt(T()));
  }

  _QV_CONSTEXPR_SCOPE _R d2() const noexcept
  {
    return d1() - sigma() * sqrt(T());
  }

  _QV_CONSTEXPR_SCOPE
  std::pair<_R, _R> d1_d2() const noexcept
  {
    const auto d1_result = d1();
    return std::make_pair(d1_result, d1_result - sigma() * sqrt(T()));
  }

  _QV_CONSTEXPR_SCOPE
  auto call() const noexcept
  {
    const auto [d1, d2] = d1_d2();
    return S() * exp(-q() * T()) * cnd(d1) - K() * exp(-r() * T()) * cnd(d2);
  }

  _QV_CONSTEXPR_SCOPE
  auto put() const noexcept
  {
    const auto [d1, d2] = d1_d2();
    return K() * exp(-r() * T()) * cnd(-d2) - S() * exp(-q() * T()) * cnd(-d1);
  }

  _QV_CONSTEXPR_SCOPE
  std::pair<_R, _R> call_put() const noexcept
  {
    const auto [d1, d2] = d1_d2();
    return std::make_pair(
        S() * exp(-q() * T()) * cnd(d1) - K() * exp(-r() * T()) * cnd(d2),
        K() * exp(-r() * T()) * cnd(-d2) - S() * exp(-q() * T()) * cnd(-d1));
  }

  _QV_CONSTEXPR_SCOPE
  _R S() const noexcept { return _model.S(); }

  _QV_CONSTEXPR_SCOPE
  _R K() const noexcept { return _model.K(); }

  _QV_CONSTEXPR_SCOPE
  _R T() const noexcept { return _model.T(); }

  _QV_CONSTEXPR_SCOPE
  _R r() const noexcept { return _model.r(); }

  _QV_CONSTEXPR_SCOPE
  _R sigma() const noexcept { return _model.sigma(); }

  _QV_CONSTEXPR_SCOPE
  _R q() const noexcept { return _model.q(); }

  _QV_CONSTEXPR_SCOPE
  void set_S(const _R S) noexcept { _model.set_S(S); }

  _QV_CONSTEXPR_SCOPE
  void set_K(const _R K) noexcept { _model.set_K(K); }

  _QV_CONSTEXPR_SCOPE
  void set_T(const _R T) noexcept { _model.set_T(T); }

  _QV_CONSTEXPR_SCOPE
  void set_r(const _R r) noexcept { _model.set_r(r); }

  _QV_CONSTEXPR_SCOPE
  void set_sigma(const _R sigma) noexcept { _model.set_sigma(sigma); }

  _QV_CONSTEXPR_SCOPE
  void set_q(const _R q) noexcept { _model.set_q(q); }

private:
  data_impl _model;
};

_END_NAMESPACE_MODEL

} // namespace qv

#endif // QV_MODEL_BSM_H
