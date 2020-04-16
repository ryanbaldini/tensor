#pragma once

#include <vector>
#include <iostream>

class Tensor {
private:
	std::vector<int> dimensions;
	int totalSize;
	double* values;
	bool ownsData; //can only delete[] if true
	
public:
	std::vector<int> getDim() const {
		return dimensions;
	}
	
	double getValue() const {
		if(dimensions.size() != 0) {
			throw "can't get a tensor value unless it has a single value";
		}
	    return values[0];
	}
	
	Tensor(): totalSize(0), values(nullptr), ownsData(false) {}
	
	Tensor(const std::vector<int>& dim, double val = 0.0): dimensions(dim), ownsData(true) {
		totalSize = 1;
		for(int d : dimensions) {
			if(d==0) {
				throw "can't make vector with a dim of 0";
			}
			totalSize *= d;
		}
		values = new double[totalSize];
		for(int i=0; i<totalSize; i++) {
			values[i] = val;
		}
	}
	
	Tensor(const Tensor& t): dimensions(t.dimensions), ownsData(true) {
		totalSize = 1;
		for(int d : dimensions) {
			totalSize *= d;
		}
		values = new double[totalSize];
		for(int i=0; i<totalSize; i++) {
			values[i] = t.values[i];
		}
	}
	
	~Tensor() {
		if(ownsData) {
			delete[] values;
		}
	}
	
	//assignment operator: this tensor copies the values of the tensor passed in
	Tensor& operator=(const Tensor& t) {
		if(this == &t){
			return *this;
		}
		if(dimensions != t.dimensions) {
			throw "can't assign a tensor to another of a different dimension";
		}
		for(int i=0; i<totalSize; i++) {
			values[i] = t.values[i];
		}
		return *this;
	}
	
	Tensor& operator=(double x) {
		for(int i=0; i<totalSize; i++) {
			values[i] = x;
		}
		return *this;
	}
	
	//returns a tensor that does NOT own its data!
	Tensor operator[](int i) {
		if(dimensions.size() == 0) {
			throw "can't index a value";
		}
		if(i < 0) {
			throw "index can't be negative";
		} else if(i >= dimensions[0]) {
			throw "index too large";
		}
		Tensor t;
		t.ownsData = false;
		t.dimensions = dimensions;
		t.dimensions.erase(t.dimensions.begin());
		t.totalSize = 1;
		for(int d : t.dimensions) {
			t.totalSize *= d;
		}
		t.values = values + i*t.totalSize;
		return t;
	}

	Tensor& operator+=(const Tensor& t) {
		if(t.dimensions != dimensions) {
			throw "cannot add tensors of different dimensions";
		}
		
		for(int i=0; i<totalSize; i++) {
			values[i] += t.values[i];
		}
		return *this;
	}
	
	Tensor& operator+=(double x) {
		for(int i=0; i<totalSize; i++) {
			values[i] += x;
		}
		return *this;
	}
	
	Tensor& operator-=(const Tensor& t) {
		if(t.dimensions != dimensions) {
			throw "cannot subtract tensors of different dimensions";
		}
		
		for(int i=0; i<totalSize; i++) {
			values[i] -= t.values[i];
		}
		return *this;
	}
	
	Tensor& operator-=(double x) {
		for(int i=0; i<totalSize; i++) {
			values[i] -= x;
		}
		return *this;
	}
	
	Tensor& operator*=(const Tensor& t) {
		if(t.dimensions != dimensions) {
			throw "cannot add tensors of different dimensions";
		}
		
		for(int i=0; i<totalSize; i++) {
			values[i] *= t.values[i];
		}
		return *this;
	}
	
	Tensor& operator*=(double x) {
		for(int i=0; i<totalSize; i++) {
			values[i] *= x;
		}
		return *this;
	}
	
	Tensor& operator/=(const Tensor& t) {
		if(t.dimensions != dimensions) {
			throw "cannot add tensors of different dimensions";
		}
		
		for(int i=0; i<totalSize; i++) {
			values[i] /= t.values[i];
		}
		return *this;
	}
	
	Tensor& operator/=(double x) {
		for(int i=0; i<totalSize; i++) {
			values[i] /= x;
		}
		return *this;
	}
};

Tensor operator+(const Tensor& t1, const Tensor& t2) {
	if(t1.getDim() != t2.getDim()) {
		throw "cannot add tensors of different dimesions";
	}
	Tensor t(t1);
	t += t2;
	return t;
}

Tensor operator+(const Tensor& t, double x) {
	Tensor newT(t);
	newT += x;
	return newT;
}

Tensor operator+(double x, const Tensor& t) {
	return t + x;
}

Tensor operator-(const Tensor& t1, const Tensor& t2) {
	if(t1.getDim() != t2.getDim()) {
		throw "cannot subtract tensors of different dimesions";
	}
	Tensor t(t1);
	t -= t2;
	return t;
}

Tensor operator-(const Tensor& t, double x) {
	Tensor newT(t);
	newT -= x;
	return newT;
}

Tensor operator*(const Tensor& t1, const Tensor& t2) {
	if(t1.getDim() != t2.getDim()) {
		throw "cannot add tensors of different dimesions";
	}
	Tensor t(t1);
	t *= t2;
	return t;
}

Tensor operator*(const Tensor& t, double x) {
	Tensor newT(t);
	newT *= x;
	return newT;
}

Tensor operator*(double x, const Tensor& t) {
	return t * x;
}

Tensor operator/(const Tensor& t1, const Tensor& t2) {
	if(t1.getDim() != t2.getDim()) {
		throw "cannot add tensors of different dimesions";
	}
	Tensor t(t1);
	t /= t2;
	return t;
}

Tensor operator/(const Tensor& t, double x) {
	Tensor newT(t);
	newT /= x;
	return newT;
}

std::ostream& operator<< (std::ostream & out, const Tensor& t) {
    out << t.getValue();;
    return out;
}