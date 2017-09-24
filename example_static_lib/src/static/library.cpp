// Copyright 2017 Jani Arola, All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#include <iostream>
#include <string>

#include "static/library.hpp"

namespace static_lib {

library::library(int value) : value(value) {}

void library::call(const std::string &ext) {
// Check the pre-processor macro value defined in the CMakeLists.txt
#ifndef HEXADECIMAL
  std::cout << "Shared call result: " << std::hex << value << ext << std::endl;
#elif !defined OCTAL
  std::cout << "Shared call result: " << std::oct << value << ext << std::endl;
#else
  std::cout << "Shared call result: " << std::dec << value << ext << std::endl;
#endif
}

constexpr int library::something(int n) { return ++n; }

} // namespace static_lib