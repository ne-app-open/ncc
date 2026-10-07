// SPDX-License-Identifier: Apache-2.0
// Copyright 2026, Amlal El Mahrouss (amlal@nekernel.org)
// Licensed under the Apache License, Version 2.0 (See accompanying
// file LICENSE or copy at http://www.apache.org/licenses/LICENSE-2.0)
// Official repository: https://github.com/ne-app-eu/ncc

/// BUGS: 0

#include <CompilerKit/AST.h>
#include <CompilerKit/Detail/AMD64.h>
#include <CompilerKit/PEF.h>
#include <CompilerKit/UUID.h>
#include <CompilerKit/Utils/Compiler.h>

/* C++ Compiler Check Driver. */
/* This is part of the CompilerKit. */
/* (c) Amlal El Mahrouss 2026 */

using namespace CompilerKit;

static bool kInIfBody        = false;
static bool kInNamespaceBody = false;

/// @brief Returns true if `input` contains a bare `=` (not `==`, `!=`, `<=`, `>=`, `+=`, `-=`).
static bool cxx_has_assignment(const CompilerKit::STLString& input) {
  for (std::size_t i = 0; i < input.size(); ++i) {
    if (input[i] != '=') continue;

    const char prev = (i > 0) ? input[i - 1] : '\0';
    const char next = (i + 1 < input.size()) ? input[i + 1] : '\0';

    if (prev == '!' || prev == '<' || prev == '>' || prev == '+' || prev == '-' || prev == '=')
      continue;
    if (next == '=') continue;

    return true;
  }
  return false;
}

NC_IMPORT_C bool CxxCheckLine(CompilerKit::STLString& input) {
  if (input.empty()) return true;

  // Unmatched parentheses.
  if (input.find("(") != CompilerKit::STLString::npos) {
    if (input.find(")") == CompilerKit::STLString::npos) {
      Detail::print_error("Unmatched '(', missing closing ')'.", "check");
      return false;
    }
  }

  // export / import / extern declarations must end with ';'.
  for (const auto& kw : {"export ", "import ", "extern "}) {
    if (input.find(kw) != CompilerKit::STLString::npos && !input.ends_with(";")) {
      if (cxx_has_assignment(input)) {
        Detail::print_error("A declaration must always end with ';'", "check");
        return false;
      } else {
        Detail::print_error("A declaration marked export, import, extern is not supported", "check");
      }
    }
  }

  // `auto` declarations: must have `=` (auto requires an initializer) and end with ';'.
  if (input.find("auto ") != CompilerKit::STLString::npos) {
    if (!input.ends_with(";")) {
      if (cxx_has_assignment(input)) {
        Detail::print_error("An 'auto' declaration must end with ';'", "check");
        return false;
      }
    }

    if (input.ends_with(";") && !cxx_has_assignment(input) &&
        input.find("(") == CompilerKit::STLString::npos) {
      Detail::print_error("An 'auto' declaration must include '=' (type deduction requires an initializer).",
                          "check");
      return false;
    }
  }

  // `const` declarations: must have `=` and end with ';'.
  if (input.find("const ") != CompilerKit::STLString::npos) {
    if (!input.ends_with(";")) {
      if (cxx_has_assignment(input)) {
        Detail::print_error("A 'const' declaration must end with ';'", "check");
        return false;
      }
    }

    if (input.ends_with(";") && !cxx_has_assignment(input) &&
        input.find("(") == CompilerKit::STLString::npos) {
      Detail::print_error("A 'const' declaration must include '='", "check");
      return false;
    }
  }

  // Any bare assignment must end with ';'.
  if (cxx_has_assignment(input)) {
    if (input.find(";") == CompilerKit::STLString::npos) {
      Detail::print_error("An assignment must always end with ';'", "check");
      return false;
    }
  }

  // Function calls (lines with `(`) that are not declarations or control-flow must end with ';'.
  if (input.find("(") != CompilerKit::STLString::npos) {
    const bool isDecl = input.find("auto ") != CompilerKit::STLString::npos ||
                        input.find("const ") != CompilerKit::STLString::npos;
    const bool isControl = input.find("if ") != CompilerKit::STLString::npos ||
                           input.find("else") != CompilerKit::STLString::npos ||
                           input.find("while ") != CompilerKit::STLString::npos ||
                           input.find("for ") != CompilerKit::STLString::npos ||
                           input.find("switch ") != CompilerKit::STLString::npos;
    const bool isFuncDef = input.find("{") != CompilerKit::STLString::npos;

    if (!isDecl && !isControl && !isFuncDef) {
      if (input.find(";") == CompilerKit::STLString::npos) {
        Detail::print_error("A function call must always end with ';'", "check");
        return false;
      }
    }
  }

  // Track scope closings.
  if (input == "}" || input == "}\n" || input == "}\r\n") {
    if (kInIfBody) kInIfBody = false;
    if (kInNamespaceBody) kInNamespaceBody = false;
  }

  if (input.find("if ") != CompilerKit::STLString::npos) kInIfBody = true;

  if (input.find("namespace ") != CompilerKit::STLString::npos) kInNamespaceBody = true;

  return true;
}
