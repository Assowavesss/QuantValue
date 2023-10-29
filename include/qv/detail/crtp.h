#ifndef QV_DETAIL_CRTP_H
#define QV_DETAIL_CRTP_H

#include "config.h"

namespace qv
{

_BEGIN_NAMESPACE_DETAIL

  template<typename _Derived>
  class crtp
  { 
    _QV_CONSTEXPR_SCOPE
    crtp() noexcept = default;
    
    friend _Derived;
  
  public:
    using type = _Derived;

    RULE_OF_FIVE_BASE(crtp) 
    
    _QV_CONSTEXPR_SCOPE
    _Derived& impl() noexcept
    { return static_cast<_Derived&>(*this); }

    _QV_CONSTEXPR_SCOPE
    const _Derived& impl() const noexcept
    { return static_cast<const _Derived&>(*this); }
  };

_END_NAMESPACE_DETAIL

} // namespace qv

#endif // QV_DETAIL_CRTP_H
