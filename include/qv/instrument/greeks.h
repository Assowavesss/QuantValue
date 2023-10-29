#ifndef QV_INSTRUMENT_GREEKS_H
#define QV_INSTRUMENT_GREEKS_H

#include "./detail/utils.h"
#include "../model/bsm.h"

namespace qv {

_BEGIN_NAMESPACE_INSTRUMENT

#ifdef QV_HAS_CONCEPTS
template<detail::real _R>
#else
template<typename _R, typename = detail::is_convertible_real<_R>>
#endif // QV_HAS_CONCEPTS
struct greeks_data
{
  using data_type = _R;

  _R delta;
  _R gamma;
  _R theta;
  _R vega;
  _R rho;
};

template<typename _M, option_type _Ex>
class greeks_base
{
public:
  using model_type = _M;
  using data_type = typename _M::data_type;

protected:
  template<typename... _T>
  _QV_CONSTEXPR_SCOPE greeks_base(const _T&... args) noexcept : _model(args...)
  {
  }

  _QV_CONSTEXPR_SCOPE
  explicit greeks_base(const model_type& model) noexcept : _model(model) {}

  _QV_CONSTEXPR_SCOPE
  explicit greeks_base(model_type&& model) noexcept : _model(std::move(model))
  {
  }

public:
  _QV_CONSTEXPR_SCOPE
  data_type exercice() noexcept
  {
    if constexpr (_Ex == option_type::Call)
      return _model.call();
    else
      return _model.put();
  }

  _QV_CONSTEXPR_SCOPE
  _M& model() noexcept { return _model; }

  _QV_CONSTEXPR_SCOPE
  const _M& model() const noexcept { return _model; }

  _QV_CONSTEXPR_SCOPE
  void set_model(const _M& model) noexcept { _model = model; }

  _QV_CONSTEXPR_SCOPE
  void set_model(_M&& model) noexcept { _model = std::move(model); }

private:
  _M _model;
};

template<class _M, option_type _Ex>
struct greeks;

template<typename _R, bool _Div, option_type _Ex>
class greeks<qv::model::bsm<_R, _Div>, _Ex>
  : public greeks_base<qv::model::bsm<_R, _Div>, _Ex>
{
public:
  using base = greeks_base<qv::model::bsm<_R, _Div>, _Ex>;
  using model_type = typename base::model_type;
  using data_type = typename base::data_type;

protected:
  using base::greeks_base;

public:
  using base::exercice;

  _QV_CONSTEXPR_SCOPE
  _R compute_delta() noexcept
  {
    set_delta(exercice());
    return delta();
  }

  _QV_CONSTEXPR_SCOPE
  _R compute_gamma() noexcept
  {
    set_gamma(exercice());
    return gamma();
  }

  _QV_CONSTEXPR_SCOPE
  _R compute_theta() noexcept
  {
    set_theta(exercice());
    return theta();
  }

  _QV_CONSTEXPR_SCOPE
  _R compute_vega() noexcept
  {
    set_vega(exercice());
    return vega();
  }

  _QV_CONSTEXPR_SCOPE
  _R compute_rho() noexcept
  {
    set_rho(exercice());
    return rho();
  }

  _QV_CONSTEXPR_SCOPE
  _R delta() const noexcept { return _data.delta; }

  _QV_CONSTEXPR_SCOPE
  _R gamma() const noexcept { return _data.gamma; }

  _QV_CONSTEXPR_SCOPE
  _R theta() const noexcept { return _data.gamma; }

  _QV_CONSTEXPR_SCOPE
  _R vega() const noexcept { return _data.vega; }

  _QV_CONSTEXPR_SCOPE
  _R rho() const noexcept { return _data.rho; }

  _QV_CONSTEXPR_SCOPE
  void set_delta(const _R delta) noexcept { _data.delta = delta; }

  _QV_CONSTEXPR_SCOPE
  void set_gamma(const _R gamma) noexcept { _data.gamma = gamma; }

  _QV_CONSTEXPR_SCOPE
  void set_theta(const _R theta) noexcept { _data.theta = theta; }

  _QV_CONSTEXPR_SCOPE
  void set_vega(const _R vega) noexcept { _data.vega = vega; }

  _QV_CONSTEXPR_SCOPE
  void set_rho(const _R rho) noexcept { _data.rho = rho; }

private:
  greeks_data<_R> _data{};
};

_END_NAMESPACE_INSTRUMENT

} // namespace qv

#endif // QV_INSTRUMENT_GREEKS_H
