#ifndef BLOBIT_H
#define BLOBIT_H
#include "commonblob.h"
#include "Blob.h"

template <typename> class Blob;

template <class T>
class BlobIt {
	typedef typename std::vector<T>::size_type size_type;
	public:
	BlobIt() : curr(0) {}
	BlobIt(const Blob<T>& a, size_type sz=0) : wptr(a.data), curr(sz) {}
	BlobIt(const BlobIt& in) : wptr(in.wptr), curr(in.curr) {}

	const T& operator*() const {
		return (*check(curr, "dereference past end"))[curr];
	}
	BlobIt& operator++() {
		curr++;
		return *this;
	}
	BlobIt operator++(int) {
		BlobIt ret(*this);
		++(*this);
		return ret;
	}
	BlobIt& operator--() { 
		curr--;
		return *this;
	}
	BlobIt operator--(int) { 
		BlobIt ret(*this);
		--(*this);
		return ret;
	}

	bool operator==(const BlobIt& rhs) const {
		auto thisOb = wptr.lock();
		auto rhsOb = wptr.lock();
		if (!thisOb || !rhsOb) return false;
		return (rhs.curr == curr) 
			&& (thisOb.get() == rhsOb.get());
	}

	bool operator!=(const BlobIt& rhs) const {
		return !operator==(rhs);
	}

	private:
	std::weak_ptr<std::vector<T>> wptr;
	size_type curr;

	std::shared_ptr<std::vector<T>> check(size_type i, const std::string &msg) const {
		auto ret = wptr.lock();
		if(!ret)
			throw std::runtime_error("unbound BlobIt");
		if(i >= ret->size())
			throw std::out_of_range(msg);
		return ret;
	}
};
#endif
