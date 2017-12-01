#ifndef LAB_TIPS_MATRIX_H
#define LAB_TIPS_MATRIX_H


#include <utility>
#include <vector>

class GaluaMatrix {
public:
  using RowType = std::vector<bool>;

  explicit GaluaMatrix(std::size_t rows_number = 0, std::size_t columns_number = 0);

  explicit GaluaMatrix(std::vector<RowType> other);

  const RowType &operator[](std::size_t idx) const;

  RowType &operator[](std::size_t idx);

  std::size_t rowsNumber() const;

  std::size_t colsNumber() const;

  std::size_t  diff(const GaluaMatrix &other) const;


private:
  std::vector<RowType> matrix;
  std::size_t _rows_number{};
  std::size_t _cols_number{};
};

GaluaMatrix operator*(const GaluaMatrix &left, const GaluaMatrix &right);

bool operator==(const GaluaMatrix &left, const GaluaMatrix &right);

bool operator!=(const GaluaMatrix &left, const GaluaMatrix &right);

#endif //LAB_TIPS_MATRIX_H
