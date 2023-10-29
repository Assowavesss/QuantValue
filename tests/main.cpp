#include <iostream>
#include <memory>
#include <array>

#include <qv/model/bsm.h>
#include <qv/european_call.h>
#include <qv/european_put.h>


_QV_CONSTEXPR auto
test_bsm()
{
  qv::model::bsm b {
		200.0,
		250.0,
		1.0,
		0.03,
		0.15
	};
	
	return b.call_put();
}

_QV_CONSTEXPR auto
test_bsm_dividend()
{
	qv::model::bsm<double, true> b {
		200.0,
		250.0,
		1.0,
		0.0,
		0.15,
		0.22
	};
	
	return b.call_put();
}

inline void
test_option_derived()
{
  qv::model::bsm b {
		200.0,
		250.0,
		1.0,
		0.03,
		0.15
	};

  std::unique_ptr<
    qv::instrument::option<
      decltype(b),
      qv::option_type::Put
    > 
  > opt_call_derived{ 
      std::make_unique<
        qv::european_put<decltype(b)>
    >( qv::european_put(b) )  
  };
   
  std::cout << "Call exercice from base option : " 
            << opt_call_derived->exercice() << '\n'
            << "Call payoff from base option : "
            << static_cast<
              qv::european_put<
                decltype(b)>*
              >(opt_call_derived.get())->payoff()
            << '\n';   
}

_QV_CONSTEXPR auto 
test_greeks()
{
  qv::model::bsm b {
		200.0,
		250.0,
		1.0,
		0.03,
		0.15
	};

  qv::european_call opt { std::move(b) };

  
  return std::array<decltype(b)::data_type, 5>{
    opt.compute_delta(),
    opt.compute_gamma(),
    opt.compute_theta(),
    opt.compute_vega(),
    opt.compute_rho()
  };

} 


_QV_CONSTEXPR auto
test_european_instrument()
{
	qv::model::bsm b{
		200.0,
		250.0,
		1.0,
		0.03,
		0.15
	};
	
	qv::instrument::european<
		decltype(b), 
		qv::option_type::Call
	> opt_call_copy { b };

	qv::instrument::european<
		decltype(b),
		qv::option_type::Put
	> opt_put_move { std::move(b) };
	
	return std::make_pair(
		opt_call_copy.exercice(),
		opt_put_move.exercice()
	);
}

_QV_CONSTEXPR auto
test_european()
{
	qv::model::bsm b{
		200.0,
		250.0,
		1.0,
		0.03,
		0.15
	};
	
	qv::european_call opt_call_copy { b };
	
	qv::european_put opt_put_move { std::move(b) };
	
	return std::make_pair(
		opt_call_copy.exercice(),
		opt_put_move.exercice()
	);
}

_QV_CONSTEXPR double
test_implied_volatility()
{
  qv::model::bsm b {
    100.0,
    100.0,
    1.0,
    0.05,
    0.0001
  };

  qv::european_call opt { b};

  opt.set_implied_volatility(10.5, 0.05, 0.35);

  return opt.model().sigma(); 
}

int main()
{ 
  
  test_option_derived();
  
  _QV_CONSTEXPR_SCOPE auto
  greeks {
    test_greeks()
  };

  _QV_CONSTEXPR_SCOPE auto 
	bsm { 
		test_bsm() 
  };
	
	_QV_CONSTEXPR_SCOPE auto 
	bsm_with_dividend { 
		test_bsm_dividend() 
  };
	
	_QV_CONSTEXPR_SCOPE auto 
	european_instrument { 
		test_european_instrument() 
  };
	
	_QV_CONSTEXPR_SCOPE auto 
	european { 
		test_european() 
  };

  _QV_CONSTEXPR_SCOPE auto
  implied_volatility {
    test_implied_volatility()
  };

	std::cout << "bsm : " 
					<< bsm.first 
					<< ' ' 
					<< bsm.second 
					<< '\n';
	
	std::cout << "bsm with dividend: " 
					<< bsm_with_dividend.first 
					<< ' ' 
					<< bsm_with_dividend.second 
					<< '\n';
  std::cout << "greeks : \n";
  for(const auto& i : greeks)
    std::cout << i << '\n'; 
    
	std::cout << "european_instrument : " 
						<< european_instrument.first 
						<< ' ' 
						<< european_instrument.second 
						<< '\n';
	
	std::cout << "european : " 
						<< european.first 
						<< ' ' 
						<< european.second 
						<< '\n';
  std::cout << "implied volatility : "
            << implied_volatility
            << '\n';    
	std::cout << std::endl;
  return 0;
}
