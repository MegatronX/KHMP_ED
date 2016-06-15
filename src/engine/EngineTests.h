#pragma once
#ifndef _ENGINETESTS_H_
#define _ENGINETESTS_H_

#include <Engine.h>

extern bool inputEventTest(ev_ptr data);

extern bool testEngine(Engine* engine);

extern bool freeEngine(Engine* engine);

extern void bigTextureTest();

extern bool statManagerTest(Engine* engine);

extern bool musicTest(Engine* engine, std::string musicFile);

extern bool timingWindowTest(Engine* engine);

extern bool htmlWindowTest(Engine* engine);

extern bool mechanicsTest(Engine* engine);

extern bool attacksTest(Engine* engine);
#endif