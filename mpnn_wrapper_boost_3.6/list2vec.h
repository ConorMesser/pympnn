using namespace boost::python;
#include <vector>
#include <boost/python.hpp>
#include<boost/python/class.hpp>
#include<boost/python/module.hpp>
#include<boost/foreach.hpp>
#ifndef FOREACH
	#define FOREACH BOOST_FOREACH
#endif

//template<typename elem_t>
//struct List2Vec {
//
//    /// The type of the vector we convert the Python list into
//    typedef std::vector<elem_t> vec_t;
//
//    /// constructor
//    /// registers the converter
//    from_python() {
//        bpy::converter::registry::push_back(
//            &convertible,
//            &construct,
//            bpy::type_id<vec_t>()
//#ifdef BOOST_PYTHON_SUPPORTS_PY_SIGNATURES
//            , &bpy::converter::wrap_pytype<&PyList_Type>::get_pytype
//#endif
//        );
//        return *this;
//    }
//
//    /// Check if conversion is possible
//    static void* convertible(PyObject* objptr) {
//        return PyList_Check(objptr)? objptr: nullptr;
//    }
//
//    /// Perform the conversion
//    static void construct(
//        PyObject* objptr,
//        bpy::converter::rvalue_from_python_stage1_data* data
//    ) {
//        // convert the PyObject pointed to by `objptr` to a bpy::list
//        bpy::handle<> objhandle{ bpy::borrowed(objptr) };   // "smart ptr"
//        bpy::list lst{ objhandle };
//
//        // get a pointer to memory into which we construct the vector
//        // this is provided by the Python side somehow
//        void* storage =
//            reinterpret_cast<
//                bpy::converter::rvalue_from_python_storage<vec_t>*
//            >(data)->storage.bytes;
//
//        // placement-new allocate the result
//        new(storage) vec_t{};
//
//        // iterate over the list `lst`, fill up the vector `vec`
//        int elemcount{ static_cast<int>(bpy::len(lst)) };
//        vec_t& vec{ *(static_cast<vec_t *>(storage)) };
//        for (int i = 0; i < elemcount; ++i) {
//            // get the element
//            bpy::object elemobj{ lst[i] };
//            bpy::extract<elem_t> elemproxy{ elemobj };
//            if (! elemproxy.check()) {
//                PyErr_SetString(PyExc_ValueError, "Bad element type");
//                bpy::throw_error_already_set();
//            }
//            elem_t elem = elemproxy();
//            vec.push_back(elem);
//        }
//
//        // remember the location for later
//        data->convertible = storage;
//    }
//};

/*** c++-list to python-list */
template<typename containedType>
struct custom_vector_to_list{
	static PyObject* convert(const std::vector<containedType>& v){
		list ret; FOREACH(const containedType& e, v) ret.append(e);
		return incref(ret.ptr());
	}
};

template<typename containedType>
struct custom_vector_from_seq{
	custom_vector_from_seq(){ converter::registry::push_back(&convertible,&construct,type_id<std::vector<containedType> >()); }
	static void* convertible(PyObject* obj_ptr){
		// the second condition is important, for some reason otherwise there were attempted conversions of Body to list which failed afterwards.
		if(!PySequence_Check(obj_ptr) || !PyObject_HasAttrString(obj_ptr,"__len__")) return 0;
		return obj_ptr;
	}
	static void construct(PyObject* obj_ptr, converter::rvalue_from_python_stage1_data* data){
		 void* storage=((converter::rvalue_from_python_storage<std::vector<containedType> >*)(data))->storage.bytes;
		 new (storage) std::vector<containedType>();
		 std::vector<containedType>* v=(std::vector<containedType>*)(storage);
		 int l=PySequence_Size(obj_ptr); if(l<0) abort(); /*std::cerr<<"l="<<l<<"; "<<typeid(containedType).name()<<std::endl;*/ v->reserve(l); for(int i=0; i<l; i++) { v->push_back(extract<containedType>(PySequence_GetItem(obj_ptr,i))); }
		 data->convertible=storage;
	}
};