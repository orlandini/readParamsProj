// ---------------------------------------------------------------------
//
// Copyright (C) 2017 by the deal.II authors
//
// This file is part of the deal.II library.
//
// The deal.II library is free software; you can use it, redistribute
// it, and/or modify it under the terms of the GNU Lesser General
// Public License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
// The full text of the license can be found in the file LICENSE at
// the top level of the deal.II distribution.
//
// ---------------------------------------------------------------------
#ifndef dealii_cxx14_utility_h
#define dealii_cxx14_utility_h


#include <utility>

// needed for array type check
#  include <type_traits>

namespace std_cxx14
{
  template <size_t... Ints>
  struct index_sequence
  {
    using type = index_sequence;
    using value_type = size_t;
    static constexpr std::size_t size() noexcept { return sizeof...(Ints); }
  };

  // --------------------------------------------------------------
  namespace internal
  {
    template <class Sequence1, class Sequence2>
    struct merge_and_renumber;

    template <size_t... I1, size_t... I2>
    struct merge_and_renumber<index_sequence<I1...>, index_sequence<I2...>>
      : index_sequence<I1..., (sizeof...(I1)+I2)...>
        { };
  }
  // --------------------------------------------------------------

  template <size_t N>
  struct make_index_sequence
    : internal::merge_and_renumber<typename make_index_sequence<N/2>::type,
      typename make_index_sequence<N - N/2>::type>
  {};

  template<> struct make_index_sequence<0> : index_sequence<> { };
  template<> struct make_index_sequence<1> : index_sequence<0> { };

  template<class... T>
  using index_sequence_for = make_index_sequence<sizeof...(T)>;
}

#endif // dealii_cxx14_memory_h
