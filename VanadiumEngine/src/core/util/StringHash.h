#pragma once

#include "pch.h"
#include "core/CoreTypes.h"

constexpr u64 hash_sv(std::string_view sv) {
    u64 hash = 14695981039346656037ull; // FNV-1a
    for (char c : sv) {
        hash ^= static_cast<uint8_t>(c);
        hash *= 1099511628211ull;
    }
    return hash;
}

constexpr u64 operator"" _id(const char* str, size_t len) {
    return hash_sv({ str, len });
}