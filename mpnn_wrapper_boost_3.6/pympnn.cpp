#include <boost/python.hpp>
#include <boost/python/return_value_policy.hpp>
#include <boost/python/return_internal_reference.hpp>
#include <multiann.h>
#include "list2vec.h"
#include "tuple2tuple.h"

using namespace boost::python;

std::tuple< std::vector<double>, std::vector<int> > (MultiANN::*k_NN)(std::vector<double>, int) = &MultiANN::NearestNeighbor;
void (MultiANN::*add_this_point)(std::vector<double>) = &MultiANN::AddPoint;


//static List2Vec<int> reg{};
//static List2Vec<double> reg2{};

BOOST_PYTHON_MODULE(pympnn)
{

//    List2Vec()
//      .from_python<int>()
//      .from_python<double>();

#define VECTOR_SEQ_CONV(Type) custom_vector_from_seq<Type>();  to_python_converter<std::vector<Type>, custom_vector_to_list<Type> >();
		VECTOR_SEQ_CONV(int);
		VECTOR_SEQ_CONV(double);

		create_tuple_converter< std::vector<double>, std::vector<int> >();

//    typedef	double	ANNcoord;		// coordinate data type
//    typedef ANNcoord *ANNpoint;		// a point
//    typedef ANNpoint *ANNpointArray;	// an array of points

//    typedef double *ANNpoint;

    class_< MultiANN >("KDTree_topologies", init<int, int, std::vector<int>, std::vector<double>, int>())
      .def("add_point", add_this_point)
      .def("k_nearest_neighbor", k_NN);

}