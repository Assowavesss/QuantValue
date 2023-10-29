#ifndef QV_DETAIL_TYPE_TRAITS_H 
#define QV_DETAIL_TYPE_TRAITS_H

#include <type_traits>

#ifdef QV_HAS_CONCEPTS
# include <concepts>
#endif // QV_HAS_CONCEPTS

#include "config.h"

namespace qv
{
_BEGIN_NAMESPACE_DETAIL

#ifdef QV_HAS_CONCEPTS
  template<typename T, typename ...U>
  struct is_variadic_convertible_to : std::false_type {};

  template<typename T, typename ...U>
  requires std::disjunction_v<std::is_convertible<T, U>...>
  struct is_variadic_convertible_to<T, U...> : std::true_type {};
#else
  template <typename T, typename... U>
  struct is_variadic_convertible_to;

  template <typename T>
  struct is_variadic_convertible_to<T> : std::true_type {};

  template <typename T, typename Head, typename... Tail>
  struct is_variadic_convertible_to<T, Head, Tail...> : 
    std::conditional_t<
      std::is_convertible_v<T, Head>,
      is_variadic_convertible_to<T, Tail...>,
      std::false_type
    >
  {};
#endif // QV_HAS_CONCEPTS

  template<typename T, typename ...U>
  inline constexpr auto is_variadic_convertible_to_v { 
	  is_variadic_convertible_to<T, U...>::value 
  };

  template<typename T>
  struct is_variadic_convertible_to_real : 
    is_variadic_convertible_to<
      T, 
      float, 
      double, 
      long double
    >
  {};

  template<typename T>
  inline constexpr auto is_variadic_convertible_to_real_v { 
	  is_variadic_convertible_to_real<T>::value
  };

  template<typename T>
  struct is_variadic_convertible_to_integral : 
    is_variadic_convertible_to<
      T, 
      signed char, 
      unsigned char,  
      short int,
      unsigned short int,
      int,
      unsigned int,
      long int,
      unsigned long int,
      long long int,
      unsigned long long int
   >
  {};

  template<typename T>
  inline constexpr auto is_variadic_convertible_to_integral_v { 
    is_variadic_convertible_to_integral<T>::value
  };

  template<typename T>
  using is_convertible_real = typename std::enable_if_t<
    is_variadic_convertible_to_real_v<T>
  >;

  template<typename T>
  using is_convertible_integral = typename std::enable_if_t<
    is_variadic_convertible_to_integral_v<T>
  >;
  
_END_NAMESPACE_DETAIL

} // namespace qv

#endif // QV_DETAIL_TYPE_TRAITS_H
