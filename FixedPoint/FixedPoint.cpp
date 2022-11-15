#include <concepts>
#include <ostream>
#include <tgmath.h>

// #include "../include/TypeChecker.h"

// https://inst.eecs.berkeley.edu/~cs61c/sp06/handout/fixedpt.html

/**
 * @brief Implementation of a fixed floating point data type.
 *
 * @tparam T Used Type for representation. Must be of: int[8,16,32,64]_t type.
 * @tparam FracBits Number of bits used to represent the part smaller 0.
 */
template <std::integral T, T FracBits>
requires (sizeof(T) * 8 > FracBits)
class Fixp {
  T Value = 0;

public:
  Fixp(T In) {
    Value = In;
  }

  /**
   * @brief Get the int value
   *
   * @return T
   */
  inline T getValue() const { return Value; }

  /**
   * @brief Get the Portion of the fixed point before the ".", bianry encoded.
   *        This Value is also the ceiling function (integer rounding) of the
   *        fixed point.
   *
   * @return T
   */
  inline T getIntVal() {
    return (Value >= 0) ? (Value >> FracBits) : (-Value >> FracBits);
  }

  /**
   * @brief Get the Portion of the fixed point behind the ".", binary encoded.
   *
   * @return T
   */
  T getFracVal() {
    T TempVal = Value;
    T Ret = 0;
    for (int I = 1; I <= FracBits; I++) {
      if (TempVal % 2)
        Ret = (Ret << 1) + 1;
    }
    return Ret;
  }

  /**
   * @brief Summation of two Fixed Points.
   *        In case two fixed points with different accuracy are added,
   *        The resulting fixed point will use the higher accuracy/FracBits.
   *
   * @tparam FracBitsIn
   * @param In
   * @return Fixp
   */
  template <T FracBitsIn>
  Fixp<T, std::max(FracBits, FracBitsIn)> operator+(Fixp<T, FracBitsIn> In) {
    //=====================================
    //===== Your Code goes here ===========
    //=====================================
    return In; // This is obviously wrong
  }

  /**
   * @brief Substraction of two fixed points.
   *        In case two fixed points with different accuracy are substracted,
   *        The resulting fixed point will use the higher accuracy/FracBits.
   *
   * @tparam FracBitsIn
   * @param In
   * @return Fixp
   */
  template <T FracBitsIn>
  Fixp<T, std::max(FracBits, FracBitsIn)> operator-(Fixp<T, FracBitsIn> In) {
    //=====================================
    //===== Your Code goes here ===========
    //=====================================
    return In; // This is obviously wrong
  }

  /**
   * @brief Multiplication of two fixed points.
   *        The resulting fixed point will use the product of both FracBits.
   *
   * @tparam FracBitsIn
   * @param In
   * @return Fixp<T, FracBits * FracBitsIn>
   */
  template <T FracBitsIn>
  Fixp<T, FracBits + FracBitsIn> operator*(Fixp<T, FracBitsIn> In) {
    // The wanted behaviour is that the result keeps its accuracy.
    // This means that the resulting Fixed Point type after the
    //    multiplication will use more frac bits.
    //=====================================
    //===== Your Code goes here ===========
    //=====================================
    return Fixp<T, FracBits + FracBitsIn>(0); // This is obviously wrong
  }

  /**
   * @brief Division of two fixed points.
   *         Te resulting fixed point will use the division of both FracBits.
   *
   * @tparam FracBitsIn
   * @param In
   * @return Fixp<T, (T)((FracBits / FracBitsIn))>
   */
  template <T FracBitsIn>
  Fixp<T, (T)((FracBits - FracBitsIn))> operator/(Fixp<T, FracBitsIn> In) {
    // No need to implement Division
    return Fixp<T, (T)((FracBits - FracBitsIn))>((T)Value / In.getValue());
  }

  /**
   * @brief Checking for Value equality.
   *         Can only be used on fixed points of same dataType and accuracy.
   *
   * @param In
   * @return true
   * @return false
   */
  bool const operator==(Fixp In) {
    return Value == In.getValue();
  }

  /**
   * @brief Checking for Value inequality.
   *         Can only be used on fixed points of same dataType and accuracy.
   *
   * @param In
   * @return true
   * @return false
   */
  bool const operator!=(Fixp In) {
    return this->Value != In.getValue();
  }

  /**
   * @brief Printfunction for fixed points.
   *         Some digits after the "." may be cut off during printing.
   *
   * @param Os
   * @param In
   * @return std::ostream&
   */
  friend std::ostream &operator<<(std::ostream &Os, const Fixp In) {
    constexpr int Pow10 = log10(pow(2, (sizeof(T) * 8))) + 1;

    long IntValue = (In.getValue() >> FracBits) + (In.getValue() < 0);
    long TempValue = In.getValue();

    unsigned long FracDec =
        (In.getValue() >= 0) ? 0 : (pow(2, -FracBits) * pow(10, Pow10));

    for (int I = 0; I < FracBits; I++) {
      if ((In.getValue() >= 0) == (TempValue % 2)) {
        FracDec += pow(2, I - FracBits) * pow(10, Pow10);
      }
      TempValue >>= 1;
    }

    if (In.getValue() < 0 && IntValue >= 0)
      Os << '-';
    if (FracDec == pow(10, Pow10)) {
      Os << IntValue + 1 << ".0";
    } else {
      Os << IntValue << "." << FracDec;
    }

    return Os;
  }
};
