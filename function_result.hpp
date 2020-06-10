// Copyright (c) 2020 ElephantSe4l. All Rights Reserved.
// Released under MPL-2.0, see LICENCE for more information.

#ifndef FRESHYCALLS_FUNCTION_RESULT_HPP_
#define FRESHYCALLS_FUNCTION_RESULT_HPP_

#include <string>
#include "utils.hpp"

namespace freshycalls {

// Formats an error message. Will try to locate "{{result_as_hex}}" and replace it with the
// hexadecimal representation of the result of the function. It will also try to locate
// "{{result_msg}}" and replace it with the error message associated to the result. Returns
// the formatted message.

template<typename Result, typename... FormatArgs>
std::string FormatErrorMsg(Result result, std::string error_msg, bool is_ntstatus, FormatArgs... format_args) {
  auto result_placeholder = error_msg.find("{{result_as_hex}}");
  auto result_msg_placeholder = error_msg.find("{{result_msg}}");

  if (result_placeholder != std::string::npos) {
    // std::string("{{result_as_hex}}").length() == 17
    error_msg.replace(result_placeholder, 17, "%#010x");
  }
  if (result_msg_placeholder != std::string::npos) {
    // std::string("{{result_msg}}").length() == 14
    error_msg.replace(result_msg_placeholder, 14, "%s");
  }

  if (result_placeholder != std::string::npos && result_msg_placeholder != std::string::npos) {
    if (result_msg_placeholder < result_placeholder) {
      return utils::FormatString(error_msg, utils::GetErrorMessage(result, is_ntstatus).data(), result, std::forward<FormatArgs>(format_args)...);
    } else {
      return utils::FormatString(error_msg, result, utils::GetErrorMessage(result, is_ntstatus).data(), std::forward<FormatArgs>(format_args)...);
    }
  } else if (result_placeholder != std::string::npos) {
    return utils::FormatString(error_msg, result, std::forward<FormatArgs>(format_args)...);

  } else if (result_msg_placeholder != std::string::npos) {
    return utils::FormatString(error_msg, utils::GetErrorMessage(result, is_ntstatus).data(), std::forward<FormatArgs>(format_args)...);
  }

  return utils::FormatString(error_msg, std::forward<FormatArgs>(format_args)...);
}


// Represents the result of a function. If no expected value is given it will assume the "OK"
// value is 0.

template<typename Result>
struct FunctionResult {
  Result result;

  explicit FunctionResult(Result result) noexcept {
    this->result = result;
  }


  // Throws if result isn't 0, otherwise it will return the result.

  template<typename... FormatArgs>
  Result OrDie(std::string_view error_msg, FormatArgs... format_args) {
    if (result == 0) {
      return result;
    } else {
      bool is_ntstatus = std::is_same_v<Result, uint32_t>;
      throw std::runtime_error(FormatErrorMsg<Result>(result, error_msg.data(), is_ntstatus, std::forward<FormatArgs>(format_args)...));
    }
  }


  // Throws if result isn't `expected_result`, otherwise it will return the result.

  template<typename... FormatArgs>
  Result ExpectedResultOrDie(Result expected_result, std::string_view error_msg, FormatArgs... format_args) {
    if (result == expected_result) {
      return result;
    } else {
      bool is_ntstatus = std::is_same_v<Result, uint32_t>;
      throw std::runtime_error(FormatErrorMsg<Result>(result, error_msg.data(), is_ntstatus, std::forward<FormatArgs>(format_args)...));
    }
  }
};
}

#endif
