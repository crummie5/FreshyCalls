// Copyright (c) 2020 ElephantSe4l. All Rights Reserved.
// Released under MPL-2.0, see LICENCE for more information.

#include "utils.hpp"
#include <Windows.h>
#include <stdexcept>

std::string freshycalls::utils::GetErrorMessage(uint32_t error_code, bool is_ntstatus) {
  LPSTR error_msg_buffer{};
  size_t error_msg_size{};

  if (is_ntstatus) {
    error_msg_size =
        FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_HMODULE | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_MAX_WIDTH_MASK,
                       (HMODULE) GetModuleHandle(L"ntdll.dll"),
                       error_code,
                       0,
                       reinterpret_cast<LPSTR>(&error_msg_buffer),
                       0,
                       nullptr);
    if (error_msg_size == 0) {
      throw std::runtime_error(utils::FormatString("[freshycalls::utils::GetErrorMessage] FormatMessageA failed to format (Error Code: %#010x)",
                                                   GetLastError()).data());
    }
  } else {
    error_msg_size =
        FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_MAX_WIDTH_MASK,
                       nullptr,
                       error_code,
                       0,
                       reinterpret_cast<LPSTR>(&error_msg_buffer),
                       0,
                       nullptr);
    if (error_msg_size == 0) {
      throw std::runtime_error(utils::FormatString("[freshycalls::utils::GetErrorMessage] FormatMessageA failed to format (Error Code: %#010x)",
                                                   GetLastError()).data());
    }
  }

  std::string error_msg(error_msg_buffer, error_msg_size);

  return error_msg;
}