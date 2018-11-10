/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once
#ifndef _MSC_VER
#include <libintl.h>
#endif
#include <fc/variant.hpp>

namespace eosio { namespace client { namespace localize {
   #if !defined(_)
   #define _(str) str
   #endif

   #define localized(str, ...) localized_with_variant((str), fc::mutable_variant_object() __VA_ARGS__ )

   inline auto localized_with_variant( const char* raw_fmt, const fc::variant_object& args) {
      if (raw_fmt != nullptr) {
         try {
#ifdef _MSC_VER
			 return fc::format_string(raw_fmt, args);
#else
            return fc::format_string(::gettext(raw_fmt), args);
#endif
         } catch (...) {
         }
         return std::string(raw_fmt);
      }
      return std::string();
   }
}}}
