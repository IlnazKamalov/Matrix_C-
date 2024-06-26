#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() {
  rows_ = 0;
  cols_ = 0;
  this->CreateMatrix();
}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows < 1 || cols < 1) throw std::out_of_range("Error: Invalid size");
  this->CreateMatrix();
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  this->CreateMatrix();
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_) {
  this->matrix_ = other.matrix_;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() { this->RemoveMatrix(); }

void S21Matrix::CreateMatrix() {
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_]();
  }
}

void S21Matrix::RemoveMatrix() {
  if (this->matrix_ != nullptr) {
    for (int i = 0; i < rows_; ++i) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    cols_ = 0;
    rows_ = 0;
    matrix_ = nullptr;
  }
}

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  bool res = true;
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    res = false;
  }

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (std::fabs(matrix_[i][j] - other.matrix_[i][j]) >=
          std::numeric_limits<double>::epsilon()) {
        res = false;
      }
    }
  }
  return res;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range(
        "Error: Incorrect input, matrices must have the same size");
  }

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range(
        "Error: Incorrect input, matrices should have the same size");
  }

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::out_of_range(
        "Error: The number of columns of the first "
        "matrix is not equal to the number of rows of the second matrix");
  }

  S21Matrix temp_m = *this;
  this->SetCols(other.cols_);

  for (int i = 0; i < this->rows_; ++i) {
    for (int j = 0; j < this->cols_; ++j) {
      double sum = 0.0;
      for (int k = 0; k < temp_m.cols_; ++k) {
        sum += temp_m(i, k) * other.matrix_[k][j];
      }
      this->matrix_[i][j] = sum;
    }
  }
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix result(this->cols_, this->rows_);
  for (int i = 0; i < result.rows_; ++i) {
    for (int j = 0; j < result.cols_; ++j) {
      result.matrix_[i][j] = matrix_[j][i];
    }
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (rows_ != cols_) {
    throw std::out_of_range(
        "Error: Incorrect input, the number of matrix rows must be equal to "
        "the "
        "columns");
  }

  S21Matrix result(rows_, cols_);
  if (rows_ > 1) {
    for (int i = 0; i < this->rows_; ++i) {
      for (int j = 0; j < this->cols_; ++j) {
        double det = this->CutElement(j, i).Determinant();
        result.matrix_[i][j] = det * pow(-1.0, i + 1 + j + 1);
      }
    }
  } else {
    result(0, 0) = 1.0;
  }
  return result;
}

double S21Matrix::Determinant() const {
  if (rows_ != cols_) {
    throw std::out_of_range("Error: Matrix is not square");
  }

  double result = 0;
  double pow = -1.0;

  if (rows_ == 1) {
    result = matrix_[0][0];
  } else if (rows_ == 2) {
    result = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else {
    for (int j = 0; j < cols_; ++j) {
      pow *= -1.0;
      result +=
          pow * this->matrix_[0][j] * this->CutElement(j, 0).Determinant();
    }
  }
  return result;
}

S21Matrix S21Matrix::CutElement(int col, int row) const {
  S21Matrix result(this->rows_ - 1, this->cols_ - 1);
  int result_i = 0;
  int result_j = 0;
  for (int i = 0; i < this->rows_; ++i) {
    for (int j = 0; j < this->cols_; ++j) {
      if (j != col && i != row) {
        result.matrix_[result_i][result_j] = this->matrix_[i][j];
        result_j++;
      }
    }
    if (i != row) {
      result_i++;
    }
    result_j = 0;
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() const {
  double det = this->Determinant();

  if (det == 0) {
    throw std::out_of_range("Error: Incorrect matrix size for Inverse");
  }

  S21Matrix result = this->CalcComplements().Transpose();
  result.MulNumber(1.0 / det);
  return result;
}

int S21Matrix::GetRows() const { return rows_; }
int S21Matrix::GetCols() const { return cols_; }

void S21Matrix::SetRows(const int rows) {
  if (rows == 0) {
    throw std::out_of_range("Error: Matrix rows count must be non-negative");
  }

  S21Matrix temp_m = *this;
  this->RemoveMatrix();
  rows_ = rows;
  cols_ = temp_m.cols_;
  this->CreateMatrix();

  int rows_to_copy = std::min(rows_, temp_m.rows_);
  int cols_to_copy = std::min(cols_, temp_m.cols_);
  for (int i = 0; i < rows_to_copy; ++i) {
    for (int j = 0; j < cols_to_copy; ++j) {
      matrix_[i][j] = temp_m.matrix_[i][j];
    }
  }
}

void S21Matrix::SetCols(const int cols) {
  if (cols == 0) {
    throw std::out_of_range("Error: Matrix columns should be positive number");
  }

  S21Matrix temp_m = *this;
  this->RemoveMatrix();
  cols_ = cols;
  rows_ = temp_m.rows_;
  this->CreateMatrix();

  int rows_to_copy = std::min(rows_, temp_m.rows_);
  int cols_to_copy = std::min(cols_, temp_m.cols_);
  for (int i = 0; i < rows_to_copy; ++i) {
    for (int j = 0; j < cols_to_copy; ++j) {
      matrix_[i][j] = temp_m.matrix_[i][j];
    }
  }
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const double num) const {
  S21Matrix result(*this);
  result.MulNumber(num);
  return result;
}

S21Matrix operator*(const double num, const S21Matrix& other) {
  S21Matrix result(other);
  result.MulNumber(num);
  return result;
}

bool S21Matrix::operator==(const S21Matrix& other) const {
  return EqMatrix(other);
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  this->RemoveMatrix();
  rows_ = other.rows_;
  cols_ = other.cols_;
  this->CreateMatrix();

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
  return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  this->SumMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  this->SubMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  this->MulMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const double num) {
  this->MulNumber(num);
  return *this;
}

double& S21Matrix::operator()(const int i, const int j) {
  if (i < 0 || i > rows_ || j < 0 || j > cols_) {
    throw std::out_of_range("Error: Indexes out of range");
  }
  return matrix_[i][j];
}
