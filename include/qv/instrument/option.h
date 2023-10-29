#ifndef QV_INSTRUMENT_OPTION_H
#define QV_INSTRUMENT_OPTION_H

#include "../detail/crtp.h"
#include "greeks.h"

namespace qv {

_BEGIN_NAMESPACE_INSTRUMENT

template<typename _M, option_type _Ex>
class option : public greeks<_M, _Ex>, public qv::detail::crtp<option<_M, _Ex>>
{
public:
  using base = qv::detail::crtp<option<_M, _Ex>>;
  using model_type = _M;
  using data_type = typename _M::data_type;

  static constexpr option_type value_exercice = _Ex;

  RULE_OF_FIVE_BASE(option)

protected:
  using greeks_adaptor = greeks<_M, _Ex>;
  using greeks_adaptor::model;

  template<typename... _T>
  _QV_CONSTEXPR_SCOPE option(const _T&... args) noexcept
    : greeks_adaptor::greeks(args...)
  {
  }

  _QV_CONSTEXPR_SCOPE
  explicit option(const _M& model) noexcept : greeks_adaptor::greeks(model) {}

  _QV_CONSTEXPR_SCOPE
  explicit option(_M&& model) noexcept
    : greeks_adaptor::greeks(std::forward<_M>(model))
  {
  }

public:
  _QV_CONSTEXPR_SCOPE
  data_type payoff() const noexcept { return base::impl().payoff(); }
};

_END_NAMESPACE_INSTRUMENT

} // namespace qv

#endif // QV_INSTRUMENT_OPTION_H
