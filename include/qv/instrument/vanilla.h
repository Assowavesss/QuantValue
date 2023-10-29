#ifndef QV_INSTRUMENT_VANILLA_H
#define QV_INSTRUMENT_VANILLA_H

#include "one_asset.h"

namespace qv
{
_BEGIN_NAMESPACE_INSTRUMENT

	template<typename _M, option_type _Ex>
	class vanilla : 
    public one_asset<_M, _Ex>
	{
  public:
    using base = one_asset<_M, _Ex>;
    using model_type = typename base::model_type;
    using data_type = typename base::data_type;
    
    static constexpr option_type value_exercice = base::value_type;
    static constexpr bool value_dividend = model_type::value_dividend; 

    RULE_OF_FIVE_BASE(vanilla)
   
  protected:
    using base::one_asset;

    _QV_CONSTEXPR_SCOPE
    vanilla(
      const _M& model, 
      const data_type y_target, 
      data_type m, 
      data_type n
    ) noexcept :
      base(
        model.S(), 
        model.K(), 
        model.T(), 
        model.r(), 
        implied_volatility(model, y_target, m, n)
      )
    {}
    
  public:
    using base::model; 
    
    
    _QV_CONSTEXPR_SCOPE
    void set_implied_volatility(
      const data_type y_target, 
      data_type m, 
      data_type n
    ) noexcept
    { model().set_sigma(implied_volatility(model(), y_target, m, n)); }

    
    _QV_CONSTEXPR_SCOPE
    data_type implied_volatility(
      const data_type y_target, 
      data_type m, 
      data_type n
    ) const noexcept
    { return implied_volatility(model(), y_target, m, n); }

    _QV_CONSTEXPR_SCOPE
    data_type implied_volatility(
      const _M& model,
      const data_type y_target, 
      data_type m, 
      data_type n 
    ) const noexcept
    { 
      _QV_STATIC_CONSTEXPR auto half { 0.5 };
       
      data_type x{ half * (m + n) };
      
      data_type y = _M::compute::template exercice<_Ex>(model.S(), model.K(), model.T(), model.r(), x);
      
      do {
        if(y < y_target) 
          m = x;

        if(y > y_target)
          n = x;

        x = half * (m + n);
      
        y = _M::compute::template exercice<_Ex>(model.S(), model.K(), model.T(), model.r(), x);
      } while(std::fabs(y - y_target) > model.sigma());

      return x;
    } 
  };

_END_NAMESPACE_INSTRUMENT

}// namespace qv

#endif // QV_INSTRUMENT_VANILLA_H
