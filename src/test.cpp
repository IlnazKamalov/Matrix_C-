#include "gtest/gtest.h"
#include "s21_matrix_oop.h"

TEST(AccessorTest, GetRowsAndCols) {
  S21Matrix m(3, 3);
  EXPECT_EQ(m.GetRows(), 3);
  EXPECT_EQ(m.GetCols(), 3);
}

TEST(CopyAndMoveTest, CopyAndMove) {
  S21Matrix m1(2, 2);
  S21Matrix m2(3, 3);
  m1 = m2;
  EXPECT_EQ(m1, m2);

  S21Matrix m3(2, 2);
  S21Matrix m4 = std::move(m3);
  EXPECT_EQ(m4(0, 0), 0);
}

TEST(SetRowsTest, SetRows) {
  S21Matrix m(2, 2);
  m.SetRows(1);
  EXPECT_EQ(m.GetRows(), 1);
}

TEST(EqualTest, Equality) {
  S21Matrix m1;
  S21Matrix m2;
  EXPECT_EQ(m1.EqMatrix(m2), true);

  S21Matrix m3;
  m3.SetRows(2);
  EXPECT_EQ(m1.EqMatrix(m3), false);

  S21Matrix m4(2, 2);
  S21Matrix m5(2, 2);
  m4(0, 0) = 0;
  m4(0, 1) = 1;
  m4(1, 0) = 2;
  m4(1, 1) = 3;

  m5(0, 0) = 0;
  m5(0, 1) = 1;
  m5(1, 0) = 2;
  m5(1, 1) = 3;
  EXPECT_EQ(m4.EqMatrix(m5), true);

  S21Matrix m6(2, 2);
  S21Matrix m7(2, 2);
  m6(0, 0) = 0;
  m6(0, 1) = 1;
  m6(1, 0) = 2;
  m6(1, 1) = 3;

  m7(0, 0) = 0;
  m7(0, 1) = 1;
  m7(1, 0) = 2;
  m7(1, 1) = 3;
  EXPECT_EQ(m6 == m7, true);
}

TEST(SumTest, Sum) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);
  m1(0, 0) = 0;
  m1(0, 1) = 1;
  m1(1, 0) = 2;
  m1(1, 1) = 3;

  m2(0, 0) = 0;
  m2(0, 1) = 1;
  m2(1, 0) = 2;
  m2(1, 1) = 3;
  m1.SumMatrix(m2);
  EXPECT_EQ(m1(0, 1), 2);
}

TEST(SumTest, OperatorSum) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);
  m1(0, 0) = 0;
  m1(0, 1) = 1;
  m1(1, 0) = 2;
  m1(1, 1) = 3;

  m2(0, 0) = 0;
  m2(0, 1) = 1;
  m2(1, 0) = 2;
  m2(1, 1) = 3;

  EXPECT_EQ((m1 + m2)(0, 1), 2.0);
}

TEST(SumTest, AssignmentSum) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);
  m1(0, 0) = 0;
  m1(0, 1) = 1;
  m1(1, 0) = 2;
  m1(1, 1) = 3;

  m2(0, 0) = 0;
  m2(0, 1) = 1;
  m2(1, 0) = 2;
  m2(1, 1) = 3;

  m1 += m2;
  EXPECT_EQ(m1(0, 1), 2.0);
}

TEST(SubTest, Subtraction) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);
  m1(0, 0) = 0;
  m1(0, 1) = 1;
  m1(1, 0) = 2;
  m1(1, 1) = 3;

  m2(0, 0) = 0;
  m2(0, 1) = 1;
  m2(1, 0) = 2;
  m2(1, 1) = 3;
  m1.SubMatrix(m2);
  EXPECT_EQ(m1(0, 1), 0);
}

TEST(SubTest, OperatorSubtraction) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);
  m1(0, 0) = 0;
  m1(0, 1) = 1;
  m1(1, 0) = 2;
  m1(1, 1) = 3;

  m2(0, 0) = 0;
  m2(0, 1) = 1;
  m2(1, 0) = 2;
  m2(1, 1) = 3;
  EXPECT_EQ((m1 - m2)(0, 1), 0);
}

TEST(SubTest, AssignmentSubtraction) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);
  m1(0, 0) = 0;
  m1(0, 1) = 1;
  m1(1, 0) = 2;
  m1(1, 1) = 3;

  m2(0, 0) = 0;
  m2(0, 1) = 1;
  m2(1, 0) = 2;
  m2(1, 1) = 3;
  m1 -= m2;
  EXPECT_EQ(m1(0, 1), 0);
}

TEST(MulNumberTest, MultiplyByNumber) {
  S21Matrix m(2, 2);
  m(0, 0) = 0;
  m(0, 1) = 1;
  m(1, 0) = 2;
  m(1, 1) = 3;
  m.MulNumber(2);
  EXPECT_EQ(m(1, 0), 4);
}

TEST(MulNumberTest, OperatorRightMultiply) {
  S21Matrix m(2, 2);
  m(0, 0) = 0;
  m(0, 1) = 1;
  m(1, 0) = 2;
  m(1, 1) = 3;
  EXPECT_EQ((m * 2)(1, 0), 4);
}

TEST(MulNumberTest, OperatorLeftMultiply) {
  S21Matrix m(2, 2);
  m(0, 0) = 0;
  m(0, 1) = 1;
  m(1, 0) = 2;
  m(1, 1) = 3;
  EXPECT_EQ((2 * m)(1, 0), 4);
}

TEST(MulNumberTest, AssignmentMultiply) {
  S21Matrix m(2, 2);
  m(0, 0) = 0;
  m(0, 1) = 1;
  m(1, 0) = 2;
  m(1, 1) = 3;
  m *= 2;
  EXPECT_EQ(m(1, 0), 4);
}

TEST(MulMatrixTest, MultiplyByMatrix) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);
  m1(0, 0) = 0;
  m1(0, 1) = 1;
  m1(1, 0) = 2;
  m1(1, 1) = 3;

  m2(0, 0) = 0;
  m2(0, 1) = 1;
  m2(1, 0) = 2;
  m2(1, 1) = 3;
  m1.MulMatrix(m2);
  EXPECT_EQ(m1(1, 1), 11);
}

TEST(MulMatrixTest, MultiplyByMatrixRotate) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 4);
  m1(0, 0) = 0;
  m1(0, 1) = 1;
  m1(1, 0) = 2;
  m1(1, 1) = 3;

  m2(0, 0) = 0;
  m2(0, 1) = 1;
  m2(1, 0) = 2;
  m2(1, 1) = 3;
  m2(0, 2) = 0;
  m2(0, 3) = 5;
  m2(1, 2) = 5;
  m2(1, 3) = 0;
  m1.MulMatrix(m2);
  EXPECT_EQ(m1(1, 3), 10);
}

TEST(MulMatrixTest, OperatorMultiplyByMatrix) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 4);
  m1(0, 0) = 0;
  m1(0, 1) = 1;
  m1(1, 0) = 2;
  m1(1, 1) = 3;

  m2(0, 0) = 0;
  m2(0, 1) = 1;
  m2(1, 0) = 2;
  m2(1, 1) = 3;
  m2(0, 2) = 0;
  m2(0, 3) = 5;
  m2(1, 2) = 5;
  m2(1, 3) = 0;
  EXPECT_EQ((m1 * m2)(1, 3), 10);
}

TEST(MulMatrixTest, AssignmentMultiplyByMatrix) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 4);
  m1(0, 0) = 0;
  m1(0, 1) = 1;
  m1(1, 0) = 2;
  m1(1, 1) = 3;

  m2(0, 0) = 0;
  m2(0, 1) = 1;
  m2(1, 0) = 2;
  m2(1, 1) = 3;
  m2(0, 2) = 0;
  m2(0, 3) = 5;
  m2(1, 2) = 5;
  m2(1, 3) = 0;
  m1 *= m2;
  EXPECT_EQ(m1(1, 3), 10);
}

TEST(TransposeTest, TransposeMatrix) {
  S21Matrix m1(3, 2);
  S21Matrix m2(2, 3);
  m1(0, 0) = 1;
  m1(0, 1) = 4;
  m1(1, 0) = 2;
  m1(1, 1) = 5;
  m1(2, 0) = 3;
  m1(2, 1) = 6;

  m2(0, 0) = 1;
  m2(1, 0) = 4;
  m2(0, 1) = 2;
  m2(1, 1) = 5;
  m2(0, 2) = 3;
  m2(1, 2) = 6;
  EXPECT_EQ(m1.Transpose() == m2, true);
}

TEST(ComplementsTest, ComplementsMatrix) {
  S21Matrix m1(3, 3);
  S21Matrix m2(3, 3);
  m1(0, 0) = 1;
  m1(2, 2) = 1;
  m1(0, 1) = 2;
  m1(2, 1) = 2;
  m1(0, 2) = 3;
  m1(2, 0) = 5;
  m1(1, 0) = 0;
  m1(1, 2) = 2;
  m1(1, 1) = 4;

  m2(0, 0) = 0;
  m2(0, 2) = -20;
  m2(0, 1) = 10;
  m2(2, 2) = 4;
  m2(1, 0) = 4;
  m2(1, 1) = -14;
  m2(1, 2) = 8;
  m2(2, 0) = -8;
  m2(2, 1) = -2;
  EXPECT_EQ(m1.CalcComplements() == m2, true);
}

TEST(ComplementsTest, ComplementsOneMatrix) {
  S21Matrix m(1, 1);
  m(0, 0) = 5;
  EXPECT_EQ(m.CalcComplements()(0, 0), 1);
}

TEST(DeterminantTest, Determinant) {
  S21Matrix m(3, 3);
  m(0, 0) = 1;
  m(1, 2) = 6;
  m(0, 1) = 2;
  m(2, 0) = 7;
  m(0, 2) = 3;
  m(2, 1) = 8;
  m(1, 0) = 4;
  m(2, 2) = 9;
  m(1, 1) = 5;
  EXPECT_EQ(m.Determinant(), 0);
}

TEST(DeterminantTest, OneMatr) {
  S21Matrix m(1, 1);
  m(0, 0) = 1;
  EXPECT_EQ(m.Determinant(), 1);
}

TEST(InverseMatrixTest, InverseMatrix) {
  S21Matrix m1(3, 3);
  S21Matrix m2(3, 3);
  m1(0, 0) = 2;
  m1(1, 2) = 4;
  m1(0, 1) = 5;
  m1(2, 0) = 5;
  m1(0, 2) = 7;
  m1(2, 1) = -2;
  m1(1, 0) = 6;
  m1(2, 2) = -3;
  m1(1, 1) = 3;

  m2(0, 0) = 1;
  m2(1, 2) = -34;
  m2(0, 1) = -1;
  m2(1, 0) = -38;
  m2(0, 2) = 1;
  m2(2, 0) = 27;
  m2(1, 1) = 41;
  m2(2, 1) = -29;
  m2(2, 2) = 24;
  EXPECT_EQ(m1.InverseMatrix() == m2, true);
}
