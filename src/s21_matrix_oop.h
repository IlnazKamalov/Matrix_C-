#ifndef __S21MATRIX_H__
#define __S21MATRIX_H__
#include <math.h>

#include <iostream>
#include <limits>

class S21Matrix {
  // only privats
 private:
  int rows_, cols_;
  double** matrix_;

  S21Matrix CutElement(const int col, const int row) const;
  void CreateMatrix();
  void RemoveMatrix();

  // only publics
 public:
  S21Matrix();
  S21Matrix(const int rows, const int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix();

  // basic methods
  bool EqMatrix(const S21Matrix& other) const;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose() const;
  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;

  // getters, setters (accessors, mutators)
  int GetRows() const;
  int GetCols() const;
  void SetRows(const int rows);
  void SetCols(const int cols);

  // overloads operators
  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix operator*(const S21Matrix& other) const;
  S21Matrix operator*(const double num) const;
  friend S21Matrix operator*(const double num, const S21Matrix& other);
  bool operator==(const S21Matrix& other) const;
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double num);
  double& operator()(const int i, const int j);
};

#endif
