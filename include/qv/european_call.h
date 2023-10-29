#ifndef QV_EUROPEAN_CALL_H
#define QV_EUROPEAN_CALL_H

#include "instrument/european.h"

namespace qv
{
	template<typename _M>
  struct european_call : 
		public instrument::european_call<_M>
  {
    using base = instrument::european_call<_M>;
    using model_type = typename base::model_type;
    using data_type = typename base::data_type;
    
    static constexpr option_type value_type = base::exercice_value;
    
    RULE_OF_FIVE_FINAL(european_call)

    _QV_CONSTEXPR_SCOPE
    explicit european_call(const _M& model) :
      base(model)
    {}

    _QV_CONSTEXPR_SCOPE
    explicit european_call(_M&& model) :
      base(std::forward<_M>(model))
    {}

    _QV_CONSTEXPR_SCOPE
    european_call(
      const _M& model, 
      const data_type y_target, 
      data_type m, 
      data_type n
    ) noexcept :
      base(model, y_target, m, n)
    {}

  };

} // namespace qv

#endif // QV_EUROPEAN_CALL_H
