#ifndef STD_ALLOC_H
#define STD_ALLOC_H
  // ---------------------- Allocator for using STL ------------------------

#include "xmmintrin.h"
#include <vector>
#include <limits>


namespace nsL1
{

// #define DEBUG_nsL1
  
  template <class T>
      class SimdAlloc {
        public:
        // type definitions
          typedef T        value_type;
          typedef T*       pointer;
          typedef const T* const_pointer;
          typedef T&       reference;
          typedef const T& const_reference;
          typedef std::size_t    size_type;
          typedef std::ptrdiff_t difference_type;

        // rebind allocator to type U
          template <class U>
              struct rebind {
            typedef SimdAlloc<U> other;
              };

          // return address of values
              pointer address (reference value) const {
                return &value;
              }
              const_pointer address (const_reference value) const {
                return &value;
              }

        /* constructors and destructor
              * - nothing to do because the allocator has no state
        */
              SimdAlloc() throw() {
              }
              SimdAlloc(const SimdAlloc&) throw() {
              }
              template <class U>
                  SimdAlloc (const SimdAlloc<U>&) throw() {
                  }
                  ~SimdAlloc() throw() {
                  }

              // return maximum number of elements that can be allocated
                  size_type max_size () const throw() {
                    return std::numeric_limits<std::size_t>::max() / sizeof(T);
                  }

              // allocate but don't initialize num elements of type T
                  pointer allocate (size_type num, const void* = 0) {
//               print message and allocate memory with global new
#ifdef DEBUG_nsL1
                    std::cerr << "Allocator: allocate " << num << " element(s)"
                        << " of size " << sizeof(T) << std::endl;
#endif // DEBUG_nsL1
                    pointer ret = reinterpret_cast<pointer>( /*T::*/operator new(num*sizeof(T)) );
#ifdef DEBUG_nsL1
                    std::cerr << " allocated at: " << (void*)ret << std::endl;
#endif // DEBUG_nsL1
                    return ret;
                  }

                // initialize elements of allocated storage p with value value
                  void construct (pointer p, const T& value) {
                 // initialize memory with placement new
#ifdef DEBUG_nsL1
                    std::cerr << "Allocator: construct " << p /*<< " " << value*/ << std::endl;
#endif // DEBUG_nsL1
                    new(p) T(value);
//                     p = reinterpret_cast<pointer>( operator new(sizeof(T), p) );
//                     *p = value;
#ifdef DEBUG_nsL1
                    std::cerr << "done." << std::endl;
#endif // DEBUG_nsL1
                  }

                // destroy elements of initialized storage p
                  void destroy (pointer p) {
                 // destroy objects by calling their destructor
#ifdef DEBUG_nsL1
                    std::cerr << "Allocator: destroy " << p << std::endl;
#endif // DEBUG_nsL1
                    p->~T();
#ifdef DEBUG_nsL1
                    std::cerr << "done." << std::endl;
#endif // DEBUG_nsL1
                  }

               // deallocate storage p of deleted elements
                  void deallocate (pointer p, size_type num) {
                  // print message and deallocate memory with global delete
#ifdef DEBUG_nsL1
                    std::cerr << "Allocator: deallocate " << num << " element(s)"
                        << " of size " << sizeof(T)
                        << " at: " << static_cast<void*>(p) << std::endl;
#endif // DEBUG_nsL1
                    /*T::*/operator delete(static_cast<void*>(p), num*sizeof(T));
#ifdef DEBUG_nsL1
                           std::cerr << "done." << std::endl;
#endif // DEBUG_nsL1
                  }


                  void *operator new(size_t size, void *ptr) { return ::operator new(size, ptr);}
                  void *operator new[](size_t size, void *ptr) { return ::operator new(size, ptr);}
                  void *operator new(size_t size) { return _mm_malloc(size, 16); }
                  void *operator new[](size_t size) { return _mm_malloc(size, 16); }
                  void operator delete(void *ptr, size_t) { _mm_free(ptr); }
                  void operator delete[](void *ptr, size_t) { _mm_free(ptr); }
      }; // SimdAlloc

      // return that all specializations of this allocator are interchangeable
      template <class T1, class T2>
          bool operator== (const SimdAlloc<T1>&, const SimdAlloc<T2>&) throw()
          {
            return true;
          };
      template <class T1, class T2>
          bool operator!= (const SimdAlloc<T1>&, const SimdAlloc<T2>&) throw()
          {
            return false;
          };

      template<typename T>
      struct vector
      {
        vector(){};
        virtual ~vector(){};
        
        typedef std::vector<T> TStd;
//         typedef std::vector<T > TSimd;
        typedef std::vector<T, SimdAlloc<T> > TSimd;
      };
  
      typedef nsL1::vector<fvec>::TSimd vector_fvec;
}; // namespace nsL1

template<typename T>
struct nsL1vector: public nsL1::vector<T>  // just for use std::vector simultaniosly
{
};

#endif 
