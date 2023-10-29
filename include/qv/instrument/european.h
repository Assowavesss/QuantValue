#ifndef QV_INSTRUMENT_EUROPEAN_H
#define QV_INSTRUMENT_EUROPEAN_H

#include "vanilla.h"

namespace qv
{
_BEGIN_NAMESPACE_INSTRUMENT

	template<typename _M, option_type _Ex>
	struct european : public vanilla<_M, _Ex>
	{
    using base = vanilla<_M, _Ex>;
    using model_type = typename base::model_type;
    using data_type = typename base::data_type;
    
    static constexpr option_type value_type = base::exercice_value;
    
    RULE_OF_FIVE_BASE(european)

    _QV_CONSTEXPR_SCOPE
    explicit european(const _M& model) :
      base(model)
    {}

    _QV_CONSTEXPR_SCOPE
    explicit european(_M&& model) :
      base(std::forward<_M>(model))
    {}

    _QV_CONSTEXPR_SCOPE
    european(
      const _M& model, 
      const data_type y_target, 
      data_type m, 
      data_type n
    ) noexcept :
      base(model, y_target, m, n)
    {}
  };

	template<typename _M>
	using european_call = european<_M, option_type::Call>;
	
	template<typename _M>
	using european_put = european<_M, option_type::Put>;

_END_NAMESPACE_INSTRUMENT

} // namespace qv

#endif // QV_INSTRUMENT_EUROPEAN_H
