#pragma once

namespace sub::opts {
// Some commands might have common options such as limit, ordering
struct BaseListOptions {};
struct BaseAddOptions {};
struct BaseSendOptions {};
struct BaseShowOptions {};
struct BaseDeleteOptions {};

}  // namespace sub::opts