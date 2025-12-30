#pragma once
#include <concepts>
#include <teams_lib/common.hpp>
#include <teams_lib/models/Message.hpp>

namespace teams::priv {

template <typename... Ts>
struct TypesBundle {};

using SoftRemovables = TypesBundle<Message>;

template <typename T, typename Bundle>
struct IsInTypeBundle;

template <typename T, typename... Ts>
struct IsInTypeBundle<T, TypesBundle<Ts...>>
    : std::bool_constant<(std::same_as<T, Ts> || ...)> {};

template <typename T>
concept IsInSoftRemovables = IsInTypeBundle<T, SoftRemovables>::value_type;

template <typename T>
concept IsCollection = requires { typename T::value_type; } &&
                       std::same_as<T, std::vector<typename T::value_type>>;

template <typename T>
concept IsSoftRemovable = !IsCollection<T> && !IsInSoftRemovables<T>;

template <typename T>
concept IsRemovable = !IsCollection<T> && !IsInSoftRemovables<T>;

template <typename T>
concept IsPatchable = !IsCollection<T>;

template <typename T>
concept IsPostable = IsCollection<T>;

}  // namespace teams::priv