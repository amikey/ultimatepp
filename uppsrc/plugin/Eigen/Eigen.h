#ifndef _Eigen_Eigen_h
#define _Eigen_Eigen_h

#include <Core/Core.h>

#define EIGEN_MATRIX_PLUGIN 	<plugin/Eigen/ToStringPlugin.h>
#define EIGEN_DENSEBASE_PLUGIN 	<plugin/Eigen/ToStringPlugin.h>
#define EIGEN_TENSOR_PLUGIN		<plugin/Eigen/ToStringPlugin.h>

#ifndef _DEBUG
#define EIGEN_NO_DEBUG
#endif

#define EIGEN_EXCEPTIONS

#define eigen_assert(x) ASSERT(x)

#undef Success  
#include "Eigen/Eigen"
#include <plugin/Eigen/unsupported/Eigen/NonLinearOptimization>
#include <plugin/Eigen/unsupported/Eigen/FFT>
#include <plugin/Eigen/unsupported/Eigen/CXX11/Tensor>


namespace Upp {

template<typename _Scalar, ptrdiff_t nx = Eigen::Dynamic, ptrdiff_t ny = Eigen::Dynamic>
struct NonLinearOptimizationFunctor {
	typedef _Scalar Scalar;
	enum {
		InputsAtCompileTime = nx,
		ValuesAtCompileTime = ny
	};
	typedef Eigen::Matrix<double, InputsAtCompileTime, 1> InputType;
	typedef Eigen::Matrix<double, ValuesAtCompileTime, 1> ValueType;
	typedef Eigen::Matrix<double, ValuesAtCompileTime, InputsAtCompileTime> JacobianType;
	
	Eigen::Index unknowns, datasetLen;
	
	NonLinearOptimizationFunctor() : unknowns(InputsAtCompileTime), datasetLen(ValuesAtCompileTime) {}
	NonLinearOptimizationFunctor(int unknowns, int datasetLen) : unknowns(unknowns), datasetLen(datasetLen) {}
	
	ptrdiff_t inputs() const {return ptrdiff_t(unknowns);}
	ptrdiff_t values() const {return ptrdiff_t(datasetLen);}
	virtual void operator() (const InputType& , ValueType* , JacobianType*  = 0) const {};
};

struct Basic_functor : NonLinearOptimizationFunctor<double> {
	Basic_functor(Function <int(const Eigen::VectorXd &b, Eigen::VectorXd &err)> _function) : function(_function) {}
	int operator()(const Eigen::VectorXd &b, Eigen::VectorXd &fvec) const {return function(b, fvec);}
	Function <int(const Eigen::VectorXd &b, Eigen::VectorXd &err)> function;
};

template <class T>
bool NonLinearOptimization(T &coeff, int numData, Function <int(const T &b, T &err)>function) {
	Basic_functor functor(function);
	functor.unknowns = coeff.size();
	functor.datasetLen = numData;
	Eigen::NumericalDiff<Basic_functor> numDiff(functor);
	Eigen::LevenbergMarquardt<Eigen::NumericalDiff<Basic_functor> > lm(numDiff);
	int ret = lm.minimize(coeff);
	if (ret == Eigen::LevenbergMarquardtSpace::ImproperInputParameters || 
		ret == Eigen::LevenbergMarquardtSpace::TooManyFunctionEvaluation)
		return false;
	return true;
}


template <class T>
void Xmlize(XmlIO &xml, Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> &mat) {
	Size_<int64> sz(mat.cols(), mat.rows());
	xml ("size", sz);
	if(xml.IsStoring()) {
		for(int r = 0; r < mat.rows(); r++)
			for(int c = 0; c < mat.cols(); c++) {
				XmlIO io = xml.Add("item");
				T data = mat(r, c);
				Xmlize(io, data);
			}
	} else {
		mat.resize(ptrdiff_t(sz.cy), ptrdiff_t(sz.cx));
		int r = 0, c = 0;
		for(int i = 0; i < xml->GetCount(); i++) 
			if(xml->Node(i).IsTag("item")) {
				XmlIO io = xml.At(i);
				T data;
				Xmlize(io, data);
				mat(r, c) = data;
				++c;
				if (c == sz.cx) {
					c = 0;
					r++;
				}
			}
	}
}

template <class T>
void Xmlize(XmlIO &xml, Eigen::Matrix<T, Eigen::Dynamic, 1> &vec) {
	int64 sz = vec.size();
	xml ("size", sz);
	if(xml.IsStoring()) {
		for(int r = 0; r < sz; r++) {
			XmlIO io = xml.Add("item");
			T data = vec(r);
			Xmlize(io, data);
		}
	} else {
		vec.resize(ptrdiff_t(sz));
		int r = 0;
		for(int i = 0; i < xml->GetCount(); i++)
			if(xml->Node(i).IsTag("item")) {
				XmlIO io = xml.At(i);
				T data;
				Xmlize(io, data);
				vec(r++) = data;
			}
	}
}

template <class T>
void Jsonize(JsonIO &io, Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> &mat) {
	Vector<T> vector;
	Size_<int64> sz(mat.cols(), mat.rows());
	io("size", sz);
	if(io.IsStoring()) {
		vector.SetCount(int(sz.cx)*int(sz.cy));
		int i = 0;
		for(int r = 0; r < mat.rows(); r++)
			for(int c = 0; c < mat.cols(); c++) 
				vector[i++] = mat(r, c);
		io("data", vector);
	} else {
		io("data", vector);
		mat.resize(ptrdiff_t(sz.cy), ptrdiff_t(sz.cx));
		int r = 0, c = 0;
		for (int i = 0; i < vector.GetCount(); ++i) {
			mat(r, c) = vector[i];
			++c;
			if (c == sz.cx) {
				c = 0;
				r++;
			}
			if (r == sz.cy)
				break;
		}
	}
}

template <class T>
void Jsonize(JsonIO &io, Eigen::Matrix<T, Eigen::Dynamic, 1> &vec) {
	Vector<T> vector;
	int64 sz = vec.size();
	io("size", sz);
	if(io.IsStoring()) {
		vector.SetCount(int(sz));
		for (int i = 0; i < sz; ++i)
			vector[i] = vec(i);
		io("data", vector);
	} else {
		io("data", vector);
		vec.resize(ptrdiff_t(sz));
		for (int i = 0; i < vec.size(); ++i)
			vec(i) = vector[i];
	}
}

template <class T>
void Serialize(Stream& stream, Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> &mat) {
	Size_<int64> sz(mat.cols(), mat.rows());
	stream % sz;
	if(stream.IsStoring()) {
		for(int r = 0; r < mat.rows(); r++)
			for(int c = 0; c < mat.cols(); c++) {
				T data = mat(r, c);
				stream % data;	
			}
	} else {
		mat.resize(ptrdiff_t(sz.cy), ptrdiff_t(sz.cx));
		int r = 0, c = 0;
		for(int i = 0; i < sz.cy*sz.cx; i++) {
			T data;
			stream % data;
			mat(r, c) = data;
			++c;
			if (c == sz.cx) {
				c = 0;
				r++;
			}
			if (r == sz.cy)
				break;
		}	
	}
}

template <class T>
void Serialize(Stream& stream, Eigen::Matrix<T, Eigen::Dynamic, 1> &vec) {
	int64 sz = vec.size();
	stream % sz;
	if(stream.IsStoring()) {
		for (int i = 0; i < sz; ++i) {
			T data = vec(i);
			stream % data;
		}
	} else {
		vec.resize(ptrdiff_t(sz));
		for (int i = 0; i < sz; ++i) {
			T data;
			stream % data;
			vec(i) = data;
		}
	}
}

}

#endif
