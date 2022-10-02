#pragma once
#ifdef __linux__
#define __forceinline __attribute__((always_inline))
#endif
#include "ecs_core.h"
#include "ecs_event.h"
#include "ecs_tag.h"
#define SYSTEM(...)static __forceinline void
#define QUERY(...)
#define EVENT(...)static __forceinline void