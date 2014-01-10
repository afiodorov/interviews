#include <iostream>
#include <stack>
#include <memory>
#include <vector>

namespace heap {
	template<typename T>
	class MaxHeap {
		typedef long size_type;
		friend std::ostream& operator<<(std::ostream& out, const MaxHeap& rhs) {
			return rhs.show(out);
		}

		public:
			MaxHeap(const std::vector<T>& vector) : data(vector), heapSize(vector.size()) {
				buildHeap();
			}
			MaxHeap(std::vector<T>&& vector) : data(std::forward(vector)), heapSize(vector.size()) {
				buildHeap();
			}

		void buildHeap() {
			for(size_type it = data.size()/2-1; it>=0; it--) {
				maxHeaptify(it);
			}
		}

		void maxHeaptify(size_type it) {
			size_type largest;

			if((left(it) < heapSize) && (data[it] < data[left(it)])) {
					largest = left(it);
			} else {
					largest = it;
			}

			if((right(it) < heapSize) && (data[largest] < data[right(it)])) {
					largest = right(it);
			}

			if(it != largest) {
				using std::swap;
				swap(data[it], data[largest]);
				maxHeaptify(largest);
			}
		}

		size_type left(size_type index) {
			return (index+1) * 2 - 1;
		}

		size_type right(size_type index) {
			return (index+1) * 2;
		}

		void sort() {
			size_type oldHeapSize = heapSize;
			while(heapSize >= 2) {
				using std::swap;
				swap(data[0], data[heapSize-1]);
				heapSize--;
				maxHeaptify(0);
			}
			heapSize = oldHeapSize;
		}

		private:
			std::ostream& show(std::ostream& out) const {
				for(size_type it = 0; it<heapSize; it++)
					out << data[it] << " ";
				return out << std::endl;
			}

			std::vector<T> data;
			size_type heapSize;
	};
}
