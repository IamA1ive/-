#include <iostream>
using namespace std;

void input(double** matrix, double** copy_matrix, int size1, int size2) {
	int i, j;
	for (i = 0; i < size1; i++) {
		cout << "Введи элементы строки " << i + 1 << "\n";
		for (j = 0; j <= size2; j++) {
			cin >> matrix[i][j];
			copy_matrix[i][j] = matrix[i][j];
		}
	}
}

void output(double** matrix, int row, int col) {
	int i, j, flag;
	for (i = row - 1; i >= 0; i--) {
		flag = 0;
		for (int j = i; j < col; j++) {
			if (matrix[i][j] != 0) {
				flag = 1;
				break;
			}
		}
		if (flag == 0) row--;
	}
	for (i = 0; i < row; i++) {
		for (j = 0; j <= col; j++) {
			if (j == col) {
				cout << "| ";
			}
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

void swap(double* first, double* second, int col) {
	double temp;
	for (int i = 0; i <= col; i++) {
		temp = first[i];
		first[i] = second[i];
		second[i] = temp;
	}
}

void forward(double** matrix, int row, int col) {
	int i, j, k;
	for (i = 0; i < row; i++) {
		if (matrix[i][i] != 0) {
			double coeff = matrix[i][i];
			for (j = i; j <= col; j++) {
				matrix[i][j] /= coeff;
			}
			for (k = i + 1; k < row; k++) {
				double nextcoeff = matrix[k][i];
				for (j = 0; j <= col; j++) {
					matrix[k][j] -= (matrix[i][j] * nextcoeff);
				}
			}
		}
		else {
			for (int j = i + 1; j < row; j++) {
				if (matrix[j][i] != 0) {
					swap(matrix[i], matrix[j], col);
				}
			}
		}
		output(matrix, row, col);
		cout << endl;
	}
}

void backward(double** matrix, double* x, int row, int col) {
	for (int i = row - 1; i >= 0; i--) {
		double sum = 0.0;
		for (int j = i + 1; j < col; j++) {
			sum += matrix[i][j] * x[j];
		}
		x[i] = (matrix[i][col] - sum) / matrix[i][i];
	}
}

void solution(double* x, int row) {
	for (int i = 0; i < row; i++) {
		if (abs(x[i]) < 0.00000001) {
			cout << "X[" << i + 1 << "] = " << 0 << endl;
		}
		else {
			cout << "X[" << i + 1 << "] = " << x[i] << endl;
		}
	}
}

void test(double** copy_matrix, double* x, int col) {
	double sum = 0.0;
	for (int i = 0; i < col; i++) {
		sum += copy_matrix[0][i] * x[i];
	}
	if ((sum == copy_matrix[0][col]) || (abs(copy_matrix[0][col] - sum < 0.001))) {
		cout << "Проверка пройдена успешно!" << endl;
	}
}

int main() {
	setlocale(LC_ALL, "Rus");
	double** matrix;
	double** copy_matrix;
	double* x;
	int row, col;

	cout << "Введи количество строк ";
	cin >> row;
	cout << "Введи количество столбцов ";
	cin >> col;

	//выделение памяти
	matrix = new double* [row];
	for (int i = 0; i < row; i++) {
		matrix[i] = new double[col + 1];
	}
	x = new double[row];

	copy_matrix = new double* [row];
	for (int i = 0; i < row; i++) {
		copy_matrix[i] = new double[col + 1];
	}

	input(matrix, copy_matrix, row, col);
	cout << endl;
	output(matrix, row, col);
	cout << endl;
	forward(matrix, row, col);
	cout << endl;
	backward(matrix, x, row, col);
	solution(x, row);
	cout << endl;
	test(copy_matrix, x, col);



	//освобождение памяти
	for (int i = 0; i < row; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
	for (int i = 0; i < row; i++) {
		delete[] copy_matrix[i];
	}
	delete[] copy_matrix;
	delete[] x;

	return 0;
}