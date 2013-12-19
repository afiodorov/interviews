#ifndef BLOB_H
#define BLOB_H
#include "commonblob.h"
#include "Blobit.h"

template <class T>
class Blob {
	friend class BlobIt<T>;
	typedef typename std::vector<T>::size_type size_type;
	public:
	Blob();
	Blob(std::initializer_list<T> il);
	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }
	void push_back(const T& t) { data->push_back(t);}
	T& front();
	T& back();
	private:
	std::shared_ptr<T> data;
	void check(size_type i, const std::string &msg) const;
};
#endif
