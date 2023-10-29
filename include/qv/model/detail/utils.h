#ifndef QV_MODEL_DETAIL_UTILS_H
#define QV_MODEL_DETAIL_UTILS_H

#include "../../detail/math.h"

namespace qv
{

_BEGIN_NAMESPACE_MODEL

_BEGIN_NAMESPACE_DETAIL

  template<typename _I>
  using is_convertible_integral = qv::detail::is_convertible_integral<_I>;

  template<typename _R>
  using is_convertible_real = qv::detail::is_convertible_real<_R>;
 
#ifdef QV_HAS_CONCEPTS
  
  template<typename _I>
  concept integral = qv::detail::integral<_I>;

  template<typename _R>
  concept real = qv::detail::real<_R>;

#endif // QV_HAS_CONCEPTS
 
_END_NAMESPACE_DETAIL

  using qv::detail::log;
  using qv::detail::pow2;
  using qv::detail::sqrt;
  using qv::detail::cnd;
	
_END_NAMESPACE_MODEL

} // namespace qv

#endif // QV_MODEL_DETAIL_UTILS_H
