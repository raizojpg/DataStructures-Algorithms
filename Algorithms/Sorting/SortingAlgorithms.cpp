#include <vector>
#include <queue>
#include <random>	

namespace Bubble {
	
	template <typename Type>
	void swap(Type& x, Type& y) {
		Type z = x;
		x = y;
		y = z;
	}

	template<typename Type>
	void bubbleSort(std::vector<Type>& vec) {
		bool swapped = true;
		while (swapped) {
			swapped = false;
			for (int i = 0; i < vec.size() - 1; i++) {
				if (vec[i] > vec[i + 1]) {
					swap(vec[i], vec[i + 1]);
					swapped = true;
				}
			}
		}
	}

	template<typename Type>
	void bubbleSort2(std::vector<Type>& vec) {
		for (int i = 0; i < vec.size(); i++) {
			for (int j = i + 1; j < vec.size(); j++) {
				if (vec[i] > vec[j]) {
					swap(vec[i], vec[j]);
				}
			}
		}
	}
	
}

namespace Insertion {
	
	template <typename Type>
	void insertionSort(std::vector<Type>& vec) {
		for (int i = 1; i < vec.size(); i++) {
			int j = i - 1;
			Type x = vec[i];
			while (j >= 0 && x < vec[j]) {
				vec[j + 1] = vec[j];
				j--;
			}
			vec[j + 1] = x;
		}
	}

	template <typename Type>
	void shellSort(std::vector<Type>& vec) {
		for (long long gap = vec.size() / 2; gap > 0; gap /= 2) {
			for (long long i = gap; i < vec.size(); i++) {
				long long j = i - gap;
				Type x = vec[i];
				while (j >= 0 && x < vec[j]) {
					vec[j + gap] = vec[j];
					j -= gap;
				}
				vec[j + gap] = x;
			}
		}
	}

}

namespace Quick {

	template <typename Type>
	void swap(Type& x, Type& y) {
		Type z = x;
		x = y;
		y = z;
	}

	template <typename Type>
	void quick_sort(std::vector<Type>& vec, long long l, long long r) {
		if (l < r) {
			long long pivot = l + (rand() % (r - l + 1));
			swap(vec[pivot], vec[r]); // moving the pivot at the end of the vector
			long long j = l - 1;
			for (long long i = l; i < r; i++) {
				if (vec[i] < vec[r]) {
					j++;
					swap(vec[i], vec[j]);
				}
			}
			j++;
			swap(vec[r], vec[j]); // returning the pivot in it's place
			// j is the partition point
			quick_sort(vec, l, j - 1);
			// checking for equal values
			while (j + 1 < r and vec[j] == vec[j + 1]) {
				j++;
			}
			quick_sort(vec, j + 1, r);
		}
	}

	template <typename Type>
	void quickSort(std::vector<Type>& vec) {
		quick_sort(vec, 0, vec.size() - 1);
	}

}

namespace Merge {

	template <typename Type>
	void merge_sort(std::vector<Type>& vec, std::vector<Type>& aux, long long l, long long r) {
		if (l < r) {
			long long mid = l + ((r - l) / 2); // finding the mid without overflow
			//we swap aux with vec beacuse we don't want to do an extra iteration after  
			merge_sort(aux, vec, l, mid);
			merge_sort(aux, vec, mid + 1, r);
			long long i = l;
			long long j = mid + 1;
			long long h = l;
			while (i <= mid && j <= r) {
				if (aux[i] < aux[j]) {
					vec[h] = aux[i];
					h++; i++;
				}
				else {
					vec[h] = aux[j];
					h++; j++;
				}
			}
			while (i <= mid) {
				vec[h] = aux[i];
				h++; i++;
			}
			while (j <= r) {
				vec[h] = aux[j];
				h++; j++;
			}
		}
	}

	template <typename Type>
	void mergeSort(std::vector<Type>& vec) {
		std::vector<Type> aux = vec;
		merge_sort(vec, aux, 0, vec.size() - 1);
	}

}

namespace Radix {

	template <typename Type>
	void prefix_sum(std::vector<Type>& vec) {
		for (long long i = 1; i < vec.size(); i++) {
			vec[i] = vec[i] + vec[i - 1];
		}
	}

	template <typename Type>
	void radixSortCounts(std::vector<Type>& vec) {
		std::vector<long long> counts(10, 0);
		std::vector<Type> aux(vec.size());
		long long mask = 10;
		while (true) {
			counts = std::vector<long long>(10, 0);
			for (long long i = 0; i < vec.size(); i++) {
				int digit = (vec[i] % mask) / (mask / 10);
				counts[digit]++;
			}
			if (counts[0] == vec.size()) { break; }
			prefix_sum(counts);
			for (long long i = vec.size() - 1; i >= 0; i--) {
				int digit = (vec[i] % mask) / (mask / 10);
				counts[digit]--;
				aux[counts[digit]] = vec[i];
			}
			vec = aux;
			mask *= 10;
		}
	}

	template <typename Type>
	void radixSortBucketsVector(std::vector<Type>& vec) {
		std::vector<std::vector<Type>> buckets(10);
		long long mask = 10;
		while (true) {
			for (auto& bucket : buckets) {
				bucket.clear();
			}
			for (long long i = 0; i < vec.size(); i++) {
				int digit = (vec[i] % mask) / (mask / 10);
				buckets[digit].push_back(vec[i]);
			}
			if (buckets[0].size() == vec.size()) { break; }
			long long idx = 0;
			for (long long i = 0; i < 10; i++) {
				for (long long j = 0; j < buckets[i].size(); j++) {
					vec[idx] = buckets[i][j];
					idx++;
				}
			}
			mask *= 10;
		}
	}

	template <typename Type>
	void radixSortCountsBase2(std::vector<Type>& vec) {
		int exp = 16;
		int base = 1 << exp;
		std::vector<long long> counts(base);
		std::vector<Type> aux(vec.size());
		long long mask = base - 1;
		int iter = 1;
		while (true) {
			counts = std::vector<long long>(base, 0);
			for (long long i = 0; i < vec.size(); i++) {
				int digit = ((vec[i] & mask) >> ((iter - 1) * exp));
				counts[digit]++;
			}
			if (counts[0] == vec.size()) { break; }
			prefix_sum(counts);
			for (long long i = vec.size() - 1; i >= 0; i--) {
				int digit = ((vec[i] & mask) >> ((iter - 1) * exp));
				counts[digit]--;
				aux[counts[digit]] = vec[i];
			}
			vec = aux;
			mask = mask << exp;
			iter++;
		}
	}

	template <typename Type>
	void radixSortBucketsVectorBase2(std::vector<Type>& vec) {
		int exp = 16;
		int base = 1 << exp;
		std::vector<std::vector<Type>> buckets(base);
		long long mask = base - 1;
		int iter = 1;
		while (true) {
			for (auto& bucket : buckets) {
				bucket.clear();
			}
			for (long long i = 0; i < vec.size(); i++) {
				int digit = ((vec[i] & mask) >> ((iter - 1) * exp));
				buckets[digit].push_back(vec[i]);
			}
			if (buckets[0].size() == vec.size()) { break; }
			long long idx = 0;
			for (long long i = 0; i < base; i++) {
				for (long long j = 0; j < buckets[i].size(); j++) {
					vec[idx] = buckets[i][j];
					idx++;
				}
			}
			mask = mask << exp;
			iter++;
		}
	}

	template <typename Type>
	void radixSortCountsSigned(std::vector<Type>& vec) {
		std::vector<Type> negative, pozitive;
		for (auto val : vec) {
			if (val < 0) { negative.push_back((-1) * val); }
			else { pozitive.push_back(val); }
		}
		radixSortCounts(negative);
		radixSortCounts(pozitive);
		long long i = 0;
		for (long long j = negative.size() - 1; j >= 0; j--) {
			vec[i++] = (-1) * negative[j];
		}
		for (long long j = 0; j < pozitive.size(); j++) {
			vec[i++] = pozitive[j];
		}
	}

	template <typename Type>
	void radixSortBucketsVectorSigned(std::vector<Type>& vec) {
		std::vector<Type> negative, pozitive;
		for (auto val : vec) {
			if (val < 0) { negative.push_back((-1) * val); }
			else { pozitive.push_back(val); }
		}
		radixSortBucketsVector(negative);
		radixSortBucketsVector(pozitive);
		long long i = 0;
		for (long long j = negative.size() - 1; j >= 0; j--) {
			vec[i++] = (-1) * negative[j];
		}
		for (long long j = 0; j < pozitive.size(); j++) {
			vec[i++] = pozitive[j];
		}
	}

	template <typename Type>
	void radixSortCountsBase2Signed(std::vector<Type>& vec) {
		std::vector<Type> negative, pozitive;
		for (auto val : vec) {
			if (val < 0) { negative.push_back((-1) * val); }
			else { pozitive.push_back(val); }
		}
		radixSortCountsBase2(negative);
		radixSortCountsBase2(pozitive);
		long long i = 0;
		for (long long j = negative.size() - 1; j >= 0; j--) {
			vec[i++] = (-1) * negative[j];
		}
		for (long long j = 0; j < pozitive.size(); j++) {
			vec[i++] = pozitive[j];
		}
	}

	template <typename Type>
	void radixSortBucketsVectorBase2Signed(std::vector<Type>& vec) {
		std::vector<Type> negative, pozitive;
		for (auto val : vec) {
			if (val < 0) { negative.push_back((-1) * val); }
			else { pozitive.push_back(val); }
		}
		radixSortBucketsVectorBase2(negative);
		radixSortBucketsVectorBase2(pozitive);
		long long i = 0;
		for (long long j = negative.size() - 1; j >= 0; j--) {
			vec[i++] = (-1) * negative[j];
		}
		for (long long j = 0; j < pozitive.size(); j++) {
			vec[i++] = pozitive[j];
		}
	}

}

namespace Count {

	template <typename Type>
	void countSort(std::vector<Type>& vec) {
		long long min_element = vec[0];
		long long max_element = vec[0];
		for (long long i = 0; i < vec.size(); i++) {
			if (vec[i] > max_element) { max_element = vec[i]; }
			else if (vec[i] < min_element) { min_element = vec[i]; }
		}
		if (max_element - min_element > INT32_MAX / 2) { throw 1; }
		int size = max_element - min_element + 1;
		std::vector<long long> aux(size, 0);

		for (long long i = 0; i < vec.size(); i++) {
			aux[vec[i] - min_element]++;
		}
		long long i = 0;
		for (long long j = 0; j < size; j++) {
			while (aux[j] > 0) {
				aux[j]--;
				vec[i] = min_element + j;
				i++;
			}
		}
	}

}
