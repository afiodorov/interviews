#ifndef BLOB_H
#define BLOB_H
#include "commonblob.h"
#include "Blobit.h"

template <typename> class BlobIt;

template <class T>
class Blob {
	friend class BlobIt<T>;
	typedef typename std::vector<T>::size_type size_type;

	public:
	Blob() : data(new std::vector<T>()) {};
	Blob(std::initializer_list<T> il) : data(new std::vector<T>(il)) {};
	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }
	void push_back(const T& t) { data->push_back(t); }
	T& front() const {
		check(0, "front on empty Blob");
		return data->back();
	};
	T& back() const {
		check(0, "back on empty Blob");
		return data->back();
	};
	void pop_back() {
		check(0, "pop_back on empty Blob");
		data->pop_back();
	}
	BlobIt<T> begin() { 
		BlobIt<T> ret(*this);
		return ret;
	}
	BlobIt<T> end() { 
		BlobIt<T> ret(*this, data->size());
		return ret;
	}
	private:
	std::shared_ptr<std::vector<T>> data;
	void check(size_type i, const std::string &msg) const {
		if (i >= data->size())
			throw std::out_of_range(msg);
	}
};
#endif
