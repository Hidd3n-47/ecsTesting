#pragma once

#define ECS_TEST 1

#if !ECS_TEST
#define COMPONENT(X) X : public IComponent
#else // ECS_TEST.
#define ECS
#define COMPONENT(X) X
#endif // ECS_TEST.