#pragma once

#define ECS_TEST 1
#define MT_EC    0 // todo implement
#define MT_ECS   0
#define GFX      0

#if !ECS_TEST
#define COMPONENT(X) X : public IComponent
#else // ECS_TEST.
#define ECS
#define COMPONENT(X) X
#endif // ECS_TEST.