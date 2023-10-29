#ifndef QV_DETAIL_CONFIG_H
#define QV_DETAIL_CONFIG_H

#ifndef _BEGIN_NAMESPACE_DETAIL
# define _BEGIN_NAMESPACE_DETAIL namespace detail {
#endif // _BEGIN_NAMESPACE_INTERNAL

#ifndef _END_NAMESPACE_DETAIL
# define _END_NAMESPACE_DETAIL }
#endif // _END_NAMESPACE_INTERNAL

#ifndef _BEGIN_NAMESPACE_MODEL
# define _BEGIN_NAMESPACE_MODEL namespace model { 
#endif // BEGIN_NAMESPACE_MODEL

#ifndef _END_NAMESPACE_MODEL
# define _END_NAMESPACE_MODEL }
#endif // _END_NAMESPACE_MODEL

#ifndef _BEGIN_NAMESPACE_INSTRUMENT
# define _BEGIN_NAMESPACE_INSTRUMENT namespace instrument { 
#endif // BEGIN_NAMESPACE_INSTRUMENT

#ifndef _END_NAMESPACE_INSTRUMENT
# define _END_NAMESPACE_INSTRUMENT }
#endif // _END_NAMESPACE_INSTUMENT

#ifndef QV_HAS_CONCEPTS
# if (__cpp_lib_concepts >= 202002L)
#  define QV_HAS_CONCEPTS 1
# endif // (__cpp_lib_concepts >= 202002L)
#endif // QV_HAS_CONCEPTS

#ifndef QV_CPP20
# if (__cplusplus >= 202002L)
#  define QV_CPP20 1
# endif // (__cplusplus >= 202002L)
#endif // QV_CPP20

#ifdef QV_HAS_CONSTEXPR
# define _QV_CONSTEXPR        constexpr
# define _QV_CONSTEXPR_SCOPE  constexpr
# define _QV_STATIC_CONSTEXPR constexpr
#else
# define _QV_CONSTEXPR        inline
# define _QV_CONSTEXPR_SCOPE
# define _QV_STATIC_CONSTEXPR static constexpr
#endif // QV_HAS_CONSTEXPR

#ifdef QV_CPP20
# define RULE_OF_FIVE_BASE(name) \
	 _QV_CONSTEXPR_SCOPE \
	 name(const name& other) noexcept = default; \
	 _QV_CONSTEXPR_SCOPE \
	 name(name&& other) noexcept = default; \
	 _QV_CONSTEXPR_SCOPE \
	 name& operator=(const name& other) noexcept = default; \
	 _QV_CONSTEXPR_SCOPE \
	 name& operator=(name&& other) noexcept = default; \
   _QV_CONSTEXPR_SCOPE \
   virtual ~name() noexcept = default;
# define RULE_OF_FIVE_FINAL(name) \
	_QV_CONSTEXPR_SCOPE \
	name(const name& other) noexcept = default; \
	_QV_CONSTEXPR_SCOPE \
	name(name&& other) noexcept = default; \
	_QV_CONSTEXPR_SCOPE \
	name& operator=(const name& other) noexcept = default; \
	_QV_CONSTEXPR_SCOPE \
	name& operator=(name&& other) noexcept = default; \
  _QV_CONSTEXPR_SCOPE \
  ~name() noexcept = default;
#else
# define RULE_OF_FIVE_BASE(name) \
	 _QV_CONSTEXPR_SCOPE \
	 name(const name& other) noexcept = default; \
	 _QV_CONSTEXPR_SCOPE \
	 name(name&& other) noexcept = default; \
	 _QV_CONSTEXPR_SCOPE \
	 name& operator=(const name& other) noexcept = default; \
	 _QV_CONSTEXPR_SCOPE \
	 name& operator=(name&& other) noexcept = default; \
   ~name() noexcept = default;
# define RULE_OF_FIVE_FINAL(name) \
    RULE_OF_FIVE_BASE(name)  
#endif // QV_CPP20

#endif // QV_DETAIL_CONFIG_H
