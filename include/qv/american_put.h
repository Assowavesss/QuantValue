#ifndef QV_EUROPEAN_PUT_H
#define QV_EUROPEAN_PUT_H

#include "instrument/european.h"

namespace qv
{
	template<typename _M>
  struct european_put : 
		instrument::european_put<_M>
  {
    using base = instrument::european_put<_M>;
    using type = typename base::type;
    using base::european;
    
    static constexpr option_type value_type = base::value_type;

    _QV_CONSTEXPR_SCOPE
    european_put(const _M& model) :
      base(model)
    {}

    _QV_CONSTEXPR_SCOPE
    european_put(_M&& model) :
      base(std::forward<_M>(model))
    {}
  };

} // namespace qv

#endif // QV_EUROPEAN_PUT_H