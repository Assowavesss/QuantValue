#ifndef QV_DETAIL_MATH_H 
#define QV_DETAIL_MATH_H 

#include <limits>
#include <cmath>

#if __has_include(<concepts>)
#include "concepts.h"
#else
#include "type_traits.h"
#endif // __has_include(<concepts>)

namespace qv
{
_BEGIN_NAMESPACE_DETAIL
  
  template<typename _T>
  using limit = std::numeric_limits<_T>; 

  constexpr
  auto sqrt2() noexcept
  { return std::sqrt(2); }

#ifdef QV_HAS_CONCEPTS
    template<
      real _R, 
      integral _I,
      auto real_zero = _R(0),
      auto integral_zero = _I(0)
    >
    _QV_CONSTEXPR
    auto pow(const _R base, const _I exp) noexcept
    { 
      if(base < real_zero && exp <= integral_zero)
        limit<_R>::quiet_NaN();
      
      return std::pow(base, exp); 
    }
    
    template<real _R>
    _QV_CONSTEXPR 
    auto pow2(const _R base) noexcept 
    { return base * base; }

    template<real _R>
    _QV_CONSTEXPR
    auto pow3(const _R base) noexcept
    { return base * pow2(base); }

    template<real _R, auto real_zero = _R(0)>
    _QV_CONSTEXPR
    auto sqrt(const _R num) noexcept
    { 
      if(num < real_zero)
        limit<_R>::quiet_NaN();
      
      return std::sqrt(num); 
    }

    template<real _R>
    _QV_CONSTEXPR
    auto erf(const _R num) noexcept
    { return std::erf(num); }

    template<real _R, auto real_zero = _R(0)>
    _QV_CONSTEXPR
    _R log(const _R num)
    { 
      if(num == real_zero)
        return limit<_R>::min();
      else if(num < real_zero)
        return limit<_R>::quiet_NaN();

      return std::log(num); 
    }

    template<real _R>
    _QV_CONSTEXPR
    auto exp(const _R num) noexcept
    { return std::exp(num); }

    template<
      real _R,
      auto half = 0.5,
      auto one = 1,
      auto sqrt_two = sqrt2()
    >
    _QV_CONSTEXPR
    auto cnd(const _R x, const _R mean = 0.0, const _R stddev = 1.0) noexcept
    { return half * (one + erf((x - mean) / (stddev * sqrt_two))); }
		
		template<
			real _R,
			auto half = 0.5,
			auto one = 1,
			auto two = 2
		>
		_QV_CONSTEXPR
		_R pdf(const _R x) noexcept
		{ return (one / sqrt(two * M_PI)) * exp(-half * pow2(x)); }
		
    template<
      real _R,
      auto half = 0.5,
      auto sqrt_two = sqrt2()
    >
		_QV_CONSTEXPR
    _R normal_cdf(const _R x) noexcept
    { return std::erfc(-x / sqrt_two) * half;}
#else
    template<
      typename _R, 
      typename _I,
      typename = is_convertible_real<_R>,
      typename = is_convertible_integral<_I>
    >
    _QV_CONSTEXPR
    auto pow(const _R base, const _I exp) noexcept
    { 
      _QV_STATIC_CONSTEXPR auto real_zero{ _R(0) };
      _QV_STATIC_CONSTEXPR auto integral_zero { _I(0) };

      if(base < real_zero && exp <= integral_zero)
        limit<_R>::quiet_NaN();
      
      return std::pow(base, exp); 
    }    
    
    template<typename _R, typename = is_convertible_real<_R>>
    _QV_CONSTEXPR 
    auto pow2(const _R base) noexcept 
    { return base * base; }

    template<typename _R, typename = is_convertible_real<_R>>
    _QV_CONSTEXPR 
    auto pow3(const _R base) noexcept 
    { return base * pow2(base); }

    template<typename _R, typename = is_convertible_real<_R>>
    _QV_CONSTEXPR
    auto sqrt(const _R num) noexcept
    { 
      _QV_STATIC_CONSTEXPR auto real_zero{ _R(0) };
      
      if(num < real_zero)
        limit<_R>::quiet_NaN();
      
      return std::sqrt(num); 
    }

    template<typename _R, typename = is_convertible_real<_R>>
    _QV_CONSTEXPR
    auto erf(const _R num) noexcept
    { return std::erf(num); }

    template<typename _R, typename = is_convertible_real<_R>>
    _QV_CONSTEXPR
    _R log(const _R num) noexcept
    { 
      _QV_STATIC_CONSTEXPR const auto real_zero{ _R(0) };
      
      if(num == real_zero)
        return limit<_R>::min();
      else if(num < real_zero)
        return limit<_R>::quiet_NaN();

      return std::log(num); 
    }

    template<typename _R, typename = is_convertible_real<_R>>
    _QV_CONSTEXPR
    auto exp(const _R num) noexcept
    { return std::exp(num); }

    template<typename _R, typename = is_convertible_real<_R>>
    _QV_CONSTEXPR
    auto cnd(const _R x, const _R mean = 0.0, const _R stddev = 1.0) noexcept
    { 
      _QV_STATIC_CONSTEXPR auto half{ 0.5 };
      _QV_STATIC_CONSTEXPR auto one { 1.0 };
      _QV_STATIC_CONSTEXPR auto sqrt_two { sqrt2() };
      return half * (one + erf((x - mean) / (stddev * sqrt_two))); 
    }
		
		template<typename _R, typename = is_convertible_real<_R>>
		_QV_CONSTEXPR
		_R pdf(const _R x) noexcept
		{ 
			_QV_STATIC_CONSTEXPR auto half{ 0.5 };
      _QV_STATIC_CONSTEXPR auto one { 1.0 };
			_QV_STATIC_CONSTEXPR auto two { 2.0 };
			return (one / sqrt(two * M_PI)) * exp(-half * pow2(x)); 
		}

    template<typename _R, typename = is_convertible_real<_R>>
		_QV_CONSTEXPR
    _R normal_cdf(const _R x) noexcept
    { 
      _QV_STATIC_CONSTEXPR auto half { 0.5 };
      _QV_STATIC_CONSTEXPR auto sqrt_two { sqrt2() };
      return std::erfc(-x / sqrt_two) * half;
    } 

  #endif // QV_HAS_CONCEPTS

_END_NAMESPACE_DETAIL
}

#endif // QV_MATH_H
