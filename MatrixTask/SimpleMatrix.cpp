#include "SimpleMatrix.h"


template<typename T>
SimpleMatrix<T>& SimpleMatrix<T>::Add(const SimpleMatrix<T>& left, const SimpleMatrix<T>& right)
{
	SimpleMatrix<T>* result = new SimpleMatrix<T>{ left };
	result->Add(right);
	return *result;
}

template<typename T>
SimpleMatrix<T>& SimpleMatrix<T>::Mul(const SimpleMatrix<T>& left, const SimpleMatrix<T>& right)
{
	SimpleMatrix<T>* result = new SimpleMatrix<T>{ left };
	result->Mul(right);
	return *result;
}
