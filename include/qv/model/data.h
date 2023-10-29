#ifndef QV_MODEL_DATA_H
#define QV_MODEL_DATA_H

#include "./detail/utils.h"

namespace qv
{

_BEGIN_NAMESPACE_MODEL

#ifdef QV_HAS_CONCEPTS 
	template<detail::real _R>
#else
	template<typename _R, typename = detail::is_convertible_real<_R>>
#endif // QV_HAS_CONCEPTS
  class data
  {
  public:
    using data_type = _R;

    _QV_CONSTEXPR_SCOPE
    data() noexcept = default;

    RULE_OF_FIVE_FINAL(data)  
    
    _QV_CONSTEXPR_SCOPE
		data(
			const _R S, 
			const _R K, 
			const _R T, 
			const _R r, 
			const _R sigma
		) noexcept : _S(S), _K(K), _T(T), _r(r), _sigma(sigma)
	  {}

    _QV_CONSTEXPR_SCOPE
		_R S() const noexcept
		{ return _S; }
		
		_QV_CONSTEXPR_SCOPE
		_R K() const noexcept
		{ return _K; }
		
		_QV_CONSTEXPR_SCOPE
		_R T() const noexcept
		{ return _T; }
		
		_QV_CONSTEXPR_SCOPE
		_R r() const noexcept
		{ return _r; }
		
		_QV_CONSTEXPR_SCOPE
		_R sigma() const noexcept
		{ return _sigma; }
		
		_QV_CONSTEXPR_SCOPE
		void set_S(const _R S) noexcept
		{ _S = S; }
		
		_QV_CONSTEXPR_SCOPE
		void set_K(const _R K) noexcept
		{ _K = K; }
		
		_QV_CONSTEXPR_SCOPE
		void set_T(const _R T) noexcept
		{ _T = T; }
		
		_QV_CONSTEXPR_SCOPE
		void set_r(const _R r) noexcept
		{ _r = r; }
		
		_QV_CONSTEXPR_SCOPE
		void set_sigma(const _R sigma) noexcept
		{ _sigma = sigma; }
		
	private:
		_R _S;
		_R _K;
		_R _T;
		_R _r;
		_R _sigma;
  };

_END_NAMESPACE_MODEL

} // namespace qv

#endif // QV_MODEL_DATA_H
