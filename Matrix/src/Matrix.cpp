#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;

class Matrix {
public:
	Matrix() {
		num_rows = 0;
		num_cols = 0;
	}
	Matrix(int rows, int cols) {
		Reset(rows, cols);
	}
	void Reset(int rows, int cols) {
		if (rows < 0 || cols < 0) {
			throw out_of_range("");
		} else {
			if (rows == 0 || cols == 0) {
				rows = cols = 0;
			}
			num_rows = rows;
			num_cols = cols;
			mtrx.assign(rows, vector<int>(cols));
		}

	}
	int At(int n, int m) const {
		if (n > num_rows || m > num_cols || n < 0 || m < 0) {
			throw out_of_range("");
		} else {
			return mtrx.at(n).at(m);
		}
	}
	int& At(int n, int m) {
		if (n > num_rows || m > num_cols || n < 0 || m < 0) {
			throw out_of_range("");
		} else {
			return mtrx.at(n).at(m);
		}
	}
	int GetNumColumns() const {
		return num_cols;
	}
	int GetNumRows() const {
		return num_rows;
	}
	vector<vector<int>> Return() const {
		return mtrx;
	}
private:
	vector<vector<int>> mtrx;
	int num_rows;
	int num_cols;
};

istream& operator >>(istream &input, Matrix &a) {
	int n = 0;
	int m = 0;
	input >> n >> m;
	a.Reset(n, m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			input >> a.At(i, j);
		}
	}
	return input;
}
ostream& operator <<(ostream &out, const Matrix &a) {
	out << a.GetNumRows() << " " << a.GetNumColumns() << endl;
	for (int i = 0; i < a.GetNumRows(); i++) {
		for (int j = 0; j < a.GetNumColumns(); j++) {
			out << a.At(i, j);
			if (j == a.GetNumColumns() - 1) {
				out << endl;
			} else {
				out << " ";
			}
		}
	}
	return out;
}
bool operator ==(const Matrix &a, const Matrix &b) {
	if (a.GetNumColumns() == b.GetNumColumns()
			&& a.GetNumRows() == b.GetNumRows()) {
		if (a.Return() == b.Return()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}
Matrix operator +(const Matrix &a, const Matrix &b) {
	if (a.GetNumColumns() != b.GetNumColumns()
			|| a.GetNumRows() != b.GetNumRows()) {
		throw invalid_argument("");
	} else {
		int n = a.GetNumRows();
		int m = a.GetNumColumns();
		Matrix c(a.GetNumRows(), a.GetNumColumns());
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				c.At(i, j) = a.At(i, j) + b.At(i, j);
			}
		}
		return c;
	}

}
int main() {
	Matrix one;
	Matrix two;
	cin >> one >> two;
	cout << one + two << endl;
	return 0;
}
