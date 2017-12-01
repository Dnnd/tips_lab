#include "Matrix.h"

GaluaMatrix::GaluaMatrix(std::size_t rows_number, std::size_t columns_number)
  : matrix(rows_number, RowType(columns_number, 0)),
    _rows_number{rows_number},
    _cols_number{columns_number} {
}

GaluaMatrix::GaluaMatrix(std::vector<GaluaMatrix::RowType> other)
  : matrix{std::move(other)},
    _rows_number{matrix.size()} {
  if (_rows_number > 0) {
    _cols_number = matrix[0].size();
  }
}

const GaluaMatrix::RowType &GaluaMatrix::operator[](std::size_t idx) const {
  return matrix[idx];
}

GaluaMatrix::RowType &GaluaMatrix::operator[](std::size_t idx) {
  return matrix[idx];
}

std::size_t GaluaMatrix::rowsNumber() const {
  return _rows_number;
}

std::size_t GaluaMatrix::colsNumber() const {
  return _cols_number;
}

std::size_t GaluaMatrix::diff(const GaluaMatrix &other) const {
  std::size_t diff{0};
  for (std::size_t i = 0; i < other.matrix.size(); ++i) {
    for (std::size_t j = 0; j < other.matrix[i].size(); ++j) {
      if (matrix[i][j] != other.matrix[i][j]) {
        ++diff;
      }
    }
  }
  return diff;
}

GaluaMatrix operator*(const GaluaMatrix &left, const GaluaMatrix &right) {
  GaluaMatrix result{left.rowsNumber(), right.colsNumber()};
  for (std::size_t i = 0; i < result.rowsNumber(); ++i) {
    for (std::size_t j = 0; j < result.colsNumber(); ++j) {
      bool res = 0;
      for (std::size_t k = 0; k < left.colsNumber(); ++k) {
        res = (res != (left[i][k] && right[k][j]));
      }
      result[i][j] = res;
    }
  }
  return result;
}

bool operator==(const GaluaMatrix &left, const GaluaMatrix &right) {

  if (left.rowsNumber() != right.rowsNumber() || left.colsNumber() != right.colsNumber()) {
    return false;
  }
  for (std::size_t i = 0; i < left.rowsNumber(); ++i) {
    for (std::size_t j = 0; j < left.colsNumber(); ++j) {
      if (left[i][j] != right[i][j]) {
        return false;
      }
    }
  }
  return true;
}

bool operator!=(const GaluaMatrix &left, const GaluaMatrix &right) {
  return !(left == right);
}
