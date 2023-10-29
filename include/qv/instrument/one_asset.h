#ifndef QV_INSTRUMENT_ONE_ASSET_H
#define QV_INSTRUMENT_ONE_ASSET_H

#include "option.h"
#include "greeks.h"

namespace qv
{

_BEGIN_NAMESPACE_INSTRUMENT
 
  template<typename _M, option_type _Ex>
  class one_asset : 
    public option<_M, _Ex>
  {
  public:
    using base = option<_M, _Ex>;
    using model_type = typename base::model_type;
    using data_type = typename base::data_type;
        
    static constexpr option_type value_exercice = base::value_exercice; 
     
    RULE_OF_FIVE_BASE(one_asset)
   
    template<typename ..._T>
    _QV_CONSTEXPR_SCOPE
    one_asset(const _T&... args) noexcept :
      base(args...) 
    {}
    
    _QV_CONSTEXPR_SCOPE
		explicit one_asset(const _M& model) noexcept :
		  base(model) 
		{}
    
    _QV_CONSTEXPR_SCOPE
		explicit one_asset(_M&& model) noexcept :  
		  base(std::forward<_M>(model))		
    {}

  public:  
    _QV_CONSTEXPR_SCOPE
    auto payoff() const noexcept
    {
      if constexpr(_Ex == option_type::Call)
        return 0;
      else
        return 1;
    }
    
    _QV_CONSTEXPR_SCOPE
    data_type implied_volatility() const noexcept
    { return base::impl().implied_volatility(); }

  };
  
_END_NAMESPACE_INSTRUMENT

} // namespace qv

#endif // QV_INSTRUMENT_ONE_ASSET_H
