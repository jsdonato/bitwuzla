#ifndef BZLA_SOLVER_FP_FLOATING_POINT_H_INCLUDED
#define BZLA_SOLVER_FP_FLOATING_POINT_H_INCLUDED

#include <memory>

extern "C" {
#include "bzlabv.h"
#include "bzlasort.h"
}

#include "solver/fp/rounding_mode.h"

namespace symfpu {
template <class T>
class unpackedFloat;
}

namespace bzla {
namespace fp {

class BzlaFPTraits;
class FloatingPointSortInfo;
class WordBlaster;

using UnpackedFloat = ::symfpu::unpackedFloat<BzlaFPTraits>;

/* -------------------------------------------------------------------------- */

class FloatingPoint
{
  friend WordBlaster;

 public:
  /**
   * Create a floating-point of given sort converted from the given real
   * constant represented as a decimal string w.r.t. to the given rounding
   * mode.
   * @param sort The sort.
   * @param rm   The rounding mode.
   * @param real A string representing the real to convert from.
   * @return A floating-point of given sort converted from the given real.
   */
  static FloatingPoint from_real(BzlaSortId sort,
                                 const RoundingMode rm,
                                 const std::string &real);
  /**
   * Create a floating-point of given sort converted from the given rational
   * constant represented as a numerator and denominator decimal string w.r.t.
   * to the given rounding mode.
   * @param sort The sort.
   * @param rm  The rounding mode.
   * @param num A string representing the numerator of the rational.
   * @param den A string representing the denominator of the rational.
   * @return A floating-point of given sort converted from the given rational.
   */
  static FloatingPoint from_rational(BzlaSortId sort,
                                     const RoundingMode rm,
                                     const std::string &num,
                                     const std::string &den);

  /**
   * Create a floating-point of given sort representing zero.
   * @param sort The sort.
   * @param sign False for +zero and true for -zero.
   * @return A floating-point of given sort representing zero.
   */
  static FloatingPoint fpzero(BzlaSortId sort, bool sign);

  /**
   * Create a floating-point of given sort representing infinity.
   * @param sort The sort.
   * @param sign False for +inf and true for -inf.
   * @return A floating-point of given sort representing infinity.
   */
  static FloatingPoint fpinf(BzlaSortId sort, bool sign);

  /**
   * Create a floating-point of given sort representing nan.
   * @param sort The sort.
   * @return A floating-point of given sort representing nan.
   */
  static FloatingPoint fpnan(BzlaSortId sort);

  /**
   * Create a floating-point from its IEEE-754 bit-vector representation given
   * as sign bit, exponent bits, and significand bits.
   * @param sign A bit-vector of size 1 representing the sign bit.
   * @param exp A bit-vector representing the exponent.
   * @param sig A bit-vector representing the significand.
   * @return The floating-point corresponding to the given IEEE-754 bit-vector
   *         representation.
   */
  static FloatingPoint fpfp(BzlaBitVector *sign,
                            BzlaBitVector *exp,
                            BzlaBitVector *sig);
  /**
   * Constructor.
   * Create new nullary floating-point of given sort.
   * @param sort The floating-point sort.
   */
  FloatingPoint(BzlaSortId sort);
  /**
   * Constructor.
   * Create new nullary floating-point of given size.
   * @param size The floating-point size.
   */
  FloatingPoint(const FloatingPointSortInfo &size);
  /**
   * Constructor.
   * Create new floating-point of given sort, wrapping the given symFPU
   * unpacked float.
   * @param sort The floating-point sort.
   * @param uf The symFPU unpacked float.
   */
  FloatingPoint(BzlaSortId sort, const UnpackedFloat &uf);
  /**
   * Constructor.
   * Create new floating-point of given sort from an IEEE-754 bit-vector.
   * @param sort The sort.
   * @param bv The IEEE-754 bit-vector representation of the floating-point.
   */
  FloatingPoint(BzlaSortId sort, const BzlaBitVector *bv);
  /**
   * Constructor.
   * Create new floating-point of given sort converted from the given
   * floating-point constant w.r.t. to the given rounding mode.
   * @param sort The sort.
   * @param rm The rounding mode.
   * @param fp The floating-point to convert from.
   */
  FloatingPoint(BzlaSortId sort,
                const RoundingMode rm,
                const FloatingPoint &fp);
  /**
   * Constructor.
   * Create new floating-point of given sort converted from the given
   * bit-vector constant (interpreted as signed or unsigned machine integer)
   * w.r.t. to the given rounding mode.
   * @param sort The sort.
   * @param rm The rounding mode.
   * @param bv The bit-vector to convert from (interpreted as signed if `sign`
   *           is true).
   * @param sign True if `bv` is to be interpreted as signed machine integer,
   *             else unsigned.
   */
  FloatingPoint(BzlaSortId sort,
                const RoundingMode rm,
                const BzlaBitVector *bv,
                bool sign);

  /** Copy constructor. */
  FloatingPoint(const FloatingPoint &other);
  /** Destructor. */
  ~FloatingPoint();

  /** @return The exponent size of this floating-point. */
  uint64_t get_exponent_size() const;
  /** @return The significand size of this floating-point. */
  uint64_t get_significand_size() const;

  /** @return The size of this floating-point. */
  FloatingPointSortInfo *size() const;
  /** @return The wrapped symFPU unpacked float. */
  UnpackedFloat *unpacked() const;
  /**
   * Set the wrapped symFPU unpacked float.
   * @param uf The unpacked float to wrap.
   */
  void set_unpacked(const UnpackedFloat &uf);

  /** @return The hash value of this floating-point. */
  size_t hash() const;

  /**
   * Compare this floating-point with given floating-point.
   *
   * @param fp The floating-point to compare this floating-point with.
   * @return 0 if the floating-points are equal and -1 if they are disequal.
   */
  int32_t compare(const FloatingPoint &fp) const;

  /**
   * Equality comparison operator.
   * @param other The floating-point to compare this floating-point to.
   */
  bool operator==(const FloatingPoint &other) const;
  /**
   * Disequality comparison operator.
   * @param other The floating-point to compare this floating-point to.
   */
  bool operator!=(const FloatingPoint &other) const;

  /** @return True if this floating-point represents a zero value. */
  bool is_zero() const;

  /** @return True if this floating-point represents a normal value. */
  bool is_normal() const;

  /** @return True if this floating-point represents a subnormal value. */
  bool is_subnormal() const;

  /** @return True if this floating-point represents a nan value. */
  bool is_nan() const;

  /** @return True if this floating-point represents a infinite value. */
  bool is_inf() const;

  /** @return True if this floating-point represents a negative value. */
  bool is_neg() const;

  /** @return True if this floating-point represents a positive value. */
  bool is_pos() const;

  /** @return True if this floating-point is equal to `fp`. */
  bool is_eq(const FloatingPoint &fp) const;

  /** @return True if this floating-point is less than `fp`. */
  bool is_lt(const FloatingPoint &fp) const;

  /** @return True if this floating-point is less than or equal `fp`. */
  bool is_le(const FloatingPoint &fp) const;

  /**
   * Create a floating-point representing the absolute value of this
   * floating-point.
   * @return The absolute value of this floating-point.
   */
  FloatingPoint fpabs() const;

  /**
   * Create a floating-point representing the negation of this
   * floating-point.
   * @return The negation of this floating-point.
   */
  FloatingPoint fpneg() const;

  /**
   * Create a floating-point representing the square root of this
   * floating-point w.r.t. to the given rounding mode.
   * @param rm The rounding mode.
   * @return The square root of the given floating-point.
   */
  FloatingPoint fpsqrt(const RoundingMode rm) const;

  /**
   * Create a floating-point representing the round-to-integral of this
   * floating-point w.r.t. to the given rounding mode.
   * @param rm The rounding mode.
   * @param fp The floating-point.
   * @return The round-to-integral of the given floating-point.
   */
  FloatingPoint fprti(const RoundingMode rm) const;

  /**
   * Create a floating-point representing the remainder operation of this and
   * the given floating-point.
   * @param fp The other operand.
   * @return The result of the remainder operation.
   */
  FloatingPoint fprem(const FloatingPoint &fp) const;

  /**
   * Create a floating-point representing the addition of this and the  given
   * floating-point w.r.t. given rounding mode.
   * @param rm The rounding mode.
   * @param fp The other operand.
   * @return The addition of the operands.
   */
  FloatingPoint fpadd(const RoundingMode rm, const FloatingPoint &fp) const;

  /**
   * Create a floating-point representing the multiplication of this and the
   * given floating-point w.r.t. to the given rounding mode.
   * @param rm The rounding mode.
   * @param fp The other operand.
   * @return The multiplication of the operands.
   */
  FloatingPoint fpmul(const RoundingMode rm, const FloatingPoint &fp) const;

  /**
   * Create a floating-point representing the division of this and the given
   * floating-point constants w.r.t. to the given rounding mode.
   * @param rm The rounding mode.
   * @param fp The other operand.
   * @return The result of the division.
   */
  FloatingPoint fpdiv(const RoundingMode rm, const FloatingPoint &fp) const;

  /**
   * Create a floating-point representing the fused multiplication and addition
   * operation of this and the given floating-point constants w.r.t. to the
   * given rounding mode.
   * @param rm The rounding mode.
   * @param fp0 The operand to the multiplication.
   * @param fp1 The operand to the addition.
   * @return The result of the division.
   */
  FloatingPoint fpfma(const RoundingMode rm,
                      const FloatingPoint &fp0,
                      const FloatingPoint &fp1) const;

  /** @return The IEEE-754 bit-vector representation of  this floating-point. */
  BzlaBitVector *as_bv() const;

  /**
   * Get the triple of IEEE-754 bit-vectors representing this floating-point.
   * @param sign The output parameter for the bit-vector representation of the
   *             sign bit.
   * @param exp  The output parameter for the bit-vector representation of the
   *             exponent.
   * @param sig  The output parameter for the bit-vector representation of the
   *             significand.
   */
  void as_bvs(BzlaBitVector **sign,
              BzlaBitVector **exp,
              BzlaBitVector **sig) const;

 private:
  static inline uint32_t s_hash_primes[] = {
      333444569u, 111130391u, 22237357u, 33355519u, 456790003u, 76891121u};

  /**
   * Helper to create a floating-point from its unpacked bit-vector
   * representation given as sign bit, exponent bits, and significand bits.
   *
   * @see constructor FloatingPointSortInfo(BzlaSortId sort, BzlaBitVector
   * *sign, BzlaBitvector *exp, BzlaBitvector *sig).
   *
   * This unpacked representation accounts for additional bits required for the
   * exponent to allow subnormals to be normalized.
   *
   * @note This should NOT be used to create a literal from its IEEE-754
   *       bit-vector representation -- for this, fpfp() is to be used.
   *
   * @param sign A bit-vector of size 1 representing the sign bit.
   * @param exp  A bit-vector representing the unpacked exponent.
   * @param sig  A bit-vector representing the unpacked significand.
   * @return The floating-point corresponding to the given unpacked bit-vector
   *         representation.
   */
  static FloatingPoint from_unpacked(BzlaBitVector *sign,
                                     BzlaBitVector *exp,
                                     BzlaBitVector *sig);
  /**
   * Helper for constructors from real and rational strings.
   * @param sort The floating-point sort.
   * @param rm   The rounding mode.
   * @param num  The string denoting the numerator.
   * @param den  The string denoting the denominator, nullptr for from real.
   * @return The constructed floating-point.
   */
  static FloatingPoint convert_from_rational_aux(BzlaSortId sort,
                                                 const RoundingMode rm,
                                                 const char *num,
                                                 const char *den);

  static inline Bzla *s_bzla = nullptr;
  std::unique_ptr<FloatingPointSortInfo> d_size;
  std::unique_ptr<UnpackedFloat> d_uf;
};

/* -------------------------------------------------------------------------- */

/**
 * Wrapper for floating-point sorts providing the interface required by symFPU.
 */
class FloatingPointSortInfo
{
  friend WordBlaster;

 public:
  /**
   * Constructor.
   * @param sort The Bitwuzla floating-point sort.
   */
  FloatingPointSortInfo(const BzlaSortId sort);
  /**
   * Constructor.
   * @param esize The size of the exponent.
   * @param ssize The size of the significand.
   */
  FloatingPointSortInfo(uint32_t esize, uint32_t ssize);
  /** Copy constructor. */
  FloatingPointSortInfo(const FloatingPointSortInfo &other);
  /** Destructor. */
  ~FloatingPointSortInfo();

  /** @return The associated floating-point sort. */
  BzlaSortId get_sort(void) const;

  /* symFPU interface --------------------------------------------- */

  /** @return The exponent size of this format. */
  uint32_t exponentWidth() const { return d_esize; }
  /** @return The significand size of this format (incl. the sign bit). */
  uint32_t significandWidth() const { return d_ssize; }
  /**
   * @return The bit-width of the IEEE-754 representation of a floating-point
   *         of this size.
   */
  uint32_t packedWidth() const { return d_esize + d_ssize; }
  /**
   * @return The exponent size of this format in the IEEE-754 representation
   *         (same as exponentWidth()).
   */
  uint32_t packedExponentWidth() const { return d_esize; }
  /**
   * @return The actual significand size of this format in the IEEE-754
   *         representation (without sign bit).
   */
  uint32_t packedSignificandWidth() const { return d_ssize - 1; }

 private:
  static inline Bzla *s_bzla = nullptr;
  /** The size of exponent. */
  uint32_t d_esize;
  /** The size of significand. */
  uint32_t d_ssize;
  /** The wrapped floating-point sort. */
  BzlaSortId d_sort;
};

/* -------------------------------------------------------------------------- */
}  // namespace fp
}  // namespace bzla

namespace std {

/** Hash function. */
template <>
struct hash<bzla::fp::FloatingPoint>
{
  size_t operator()(const bzla::fp::FloatingPoint &fp) const;
};

}  // namespace std

#endif
