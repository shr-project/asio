//
// traits/query_static_constexpr_member.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASIO_TRAITS_QUERY_STATIC_CONSTEXPR_MEMBER_HPP
#define ASIO_TRAITS_QUERY_STATIC_CONSTEXPR_MEMBER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"
#include "asio/detail/type_traits.hpp"

namespace asio {
namespace detail {

#if defined(ASIO_HAS_DECLTYPE) \
  && defined(ASIO_HAS_NOEXCEPT)

template <typename T, typename Property, typename = void>
struct query_static_constexpr_member_trait
{
  ASIO_STATIC_CONSTEXPR(bool, is_valid = false);
};

template <typename T, typename Property>
struct query_static_constexpr_member_trait<T, Property,
  typename enable_if<
    (static_cast<void>(T::query(Property{})), true)
  >::type>
{
  ASIO_STATIC_CONSTEXPR(bool, is_valid = true);

  using result_type = decltype(T::query(Property{}));

  ASIO_STATIC_CONSTEXPR(bool, is_noexcept =
    noexcept(T::query(Property{})));

  static ASIO_CONSTEXPR result_type value() noexcept(is_noexcept)
  {
    return T::query(Property{});
  }
};

#else // defined(ASIO_HAS_DECLTYPE)
      //   && defined(ASIO_HAS_NOEXCEPT)

template <typename T, typename Property>
struct query_static_constexpr_member_trait
{
  ASIO_STATIC_CONSTEXPR(bool, is_valid = false);
  ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
};

#endif // defined(ASIO_HAS_DECLTYPE)
       //   && defined(ASIO_HAS_NOEXCEPT)
       //   && defined(ASIO_HAS_VARIABLE_TEMPLATES)

} // namespace detail
namespace traits {

template <typename T, typename Property, typename = void>
struct query_static_constexpr_member_default :
  detail::query_static_constexpr_member_trait<T, Property>
{
};

template <typename T, typename Property, typename = void>
struct query_static_constexpr_member :
  query_static_constexpr_member_default<T, Property>
{
};

} // namespace traits
} // namespace asio

#endif // ASIO_TRAITS_QUERY_STATIC_CONSTEXPR_MEMBER_HPP
