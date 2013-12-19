#ifndef BLOBIT_H
#define BLOBIT_H
#include <memory>
#include "<vector>"
#include "Blob.h"

template<class T>
class BlobIt {
	typedef typename std::vector<T>::size_type size_type;
	BlobIt() : curr(0) {};
	BlobIt(Blob<T>&a, size_type sz=0) : wptr(a.data), curr(sz) {};
	private:
	std::weak_ptr<T> wptr;
	size_type curr;
};
#endif
