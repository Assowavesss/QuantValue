#ifndef QV_EUROPEAN_PUT_H
#define QV_EUROPEAN_PUT_H

#include "instrument/european.h"

namespace qv
{
  template<typename _M>
  struct european_put : 
		public instrument::european_put<_M>
  {
    using base = instrument::european_put<_M>;
    using model_type = typename base::model_type;
    using data_type = typename base::data_type;
    
    static constexpr option_type exercice_value = base::exercice_value;
    
    RULE_OF_FIVE_FINAL(european_put)

    _QV_CONSTEXPR_SCOPE
    explicit european_put(const _M& model) :
      base(model)
    {}

    _QV_CONSTEXPR_SCOPE
    explicit european_put(_M&& model) :
      base(std::forward<_M>(model))
    {}
  };

} // namespace qv

#endif // QV_EUROPEAN_PUT_H
