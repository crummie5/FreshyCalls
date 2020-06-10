// Copyright (c) 2020 ElephantSe4l. All Rights Reserved.
// Released under MPL-2.0, see LICENCE for more information.

#ifndef FRESHYCALLS_UTILS_HPP_
#define FRESHYCALLS_UTILS_HPP_

#include <string>
#include <cstdint>
#include <stdexcept>

namespace freshycalls::utils {

// Tries to get the error message associated to `error_code` using `FormatMessageA`. Returns
// a string containing the message.

std::string GetErrorMessage(uint32_t error_code, bool is_ntstatus = false);


// Tries to format a string using `snprintf`. Returns the formatted string.
// WARNING: Be aware this function is REALLY bug prone as it takes a message template with n arguments and passes it
// directly to `snprintf`. Does not make any kind of check.

template<typename... FormatArgs>
std::string FormatString(std::string_view string_template, FormatArgs... format_args) {
  const size_t string_size = snprintf(nullptr, 0, string_template.data(), std::forward<FormatArgs>(format_args)...);
  if (string_size <= 0) {
    throw std::runtime_error("[sisyphus::utils::FormatString] Formatted string size is negative or 0.");
  }

  auto formatted_string = new char[string_size + 1];
  snprintf(formatted_string, string_size + 1, string_template.data(), std::forward<FormatArgs>(format_args)...);

  return std::string(formatted_string);
}
}

#endif