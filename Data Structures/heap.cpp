#include <vector>

template <typename Type>
class Heap{
private:
	std::vector<Type> heap;		// this is a min heap data structure
public:
	Heap() : heap{ 0 } {}		// the indexing will start from 1 

	void swap(Type& x, Type& y) {
		Type z = x;
		x = y;
		y = z;
	}

	Type getMin() { return heap[1]; }

	void pop() {				// deleting the min element
		if (heap.size() != 1) {

			swap(heap[1], heap[heap.size() - 1]);		 // moving the first element to the last position
			heap.erase(heap.begin() + heap.size() - 1);  // deleting it

			long long ind = 1;
			long long child = 2;
			if (child < heap.size()) {
				if (child + 1 < heap.size() && heap[child] > heap[child + 1]) {
					child++;  // if there exist a second child that has a lower value we take him
				}
				while (heap[child] < heap[ind]) {
					swap(heap[child], heap[ind]);
					ind = child;
					child = ind * 2;
					if (child >= heap.size()) { break; }  // we reached the end
					if (child + 1 < heap.size() && heap[child] > heap[child + 1]) {
						child++;	// if there exist a second child that has a lower value we take him
					}
				}
			}
		}
	}

	void push(int x) {
		long long ind = heap.size();
		heap.push_back(x);
		while (heap[ind] < heap[ind / 2] && ind > 1) {
			swap(heap[ind], heap[ind / 2]);
			ind /= 2;
		}
	}

	bool empty() {
		if (heap.size() == 1) { return true; }
		else { return false; }
	}

	void merge(Heap& other) {
		while (!other.empty()) {
			this->push(other.getMin());
			other.pop();
		}
	}

	~Heap() = default;

};
