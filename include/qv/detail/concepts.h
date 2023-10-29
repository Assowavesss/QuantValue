#ifndef QV_DETAIL_CONCEPTS_H 
#define QV_DETAIL_CONCEPTS_H

#include "type_traits.h"

namespace qv
{

_BEGIN_NAMESPACE_DETAIL

#ifdef QV_HAS_CONCEPTS
  template<typename T>
  concept real = is_variadic_convertible_to_real_v<T>;

  template<typename T>
  concept integral = is_variadic_convertible_to_integral_v<T>;
#endif // QV_HAS_CONCEPTS

_END_NAMESPACE_DETAIL

} // namespace qv

#endif // QV_DETAIL_CONCEPTS_H
