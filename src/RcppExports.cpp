// This file was generated by Rcpp::compileAttributes
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// test_parameter
Rcpp::List test_parameter(int num_stages, Rcpp::NumericVector parameters, double w, double h, Rcpp::IntegerVector init);
RcppExport SEXP facilitation_test_parameter(SEXP num_stagesSEXP, SEXP parametersSEXP, SEXP wSEXP, SEXP hSEXP, SEXP initSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< int >::type num_stages(num_stagesSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type parameters(parametersSEXP);
    Rcpp::traits::input_parameter< double >::type w(wSEXP);
    Rcpp::traits::input_parameter< double >::type h(hSEXP);
    Rcpp::traits::input_parameter< Rcpp::IntegerVector >::type init(initSEXP);
    __result = Rcpp::wrap(test_parameter(num_stages, parameters, w, h, init));
    return __result;
END_RCPP
}
