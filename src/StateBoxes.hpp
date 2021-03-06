#pragma once
#include <CGUL.hpp>
#include "State.hpp"
#include "Circle.hpp"
#include "AxisAlignedBox.hpp"
#include "OrientedBox.hpp"
#include "Line.hpp"

class StateBoxes : public State
{
    OrientedBox box1;
    OrientedBox box2;
    AxisAlignedBox box3;
    Line line;
    Circle circle;
public:
    StateBoxes();
    ~StateBoxes();

    void Enter();
    void Update(CGUL::Float32 deltaTime);
    void Exit();
};
