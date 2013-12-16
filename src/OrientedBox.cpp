#include "OrientedBox.hpp"

#include "Circle.hpp"
#include "AxisAlignedBox.hpp"
#include "Line.hpp"

OrientedBox::OrientedBox() :
    Collision(Collision::ORIENTED_BOX),
    color(0, 0, 0)
{
}

OrientedBox::OrientedBox(const CGUL::Vector2& position, const CGUL::Vector2& halfExtents, CGUL::Float32 orientation) :
    Collision(Collision::ORIENTED_BOX),
    color(0, 0, 0),
    position(position),
    halfExtents(halfExtents),
    orientation(orientation)
{
}

void OrientedBox::SetPosition(const CGUL::Vector2& position)
{
    this->position = position;
}

void OrientedBox::SetHalfExtents(const CGUL::Vector2& halfExtents)
{
    this->halfExtents = halfExtents;
}

void OrientedBox::SetOrientation(CGUL::Float32 orientation)
{
    this->orientation = orientation;
}

CGUL::Vector2 OrientedBox::GetPosition() const
{
    return position;
}

CGUL::Vector2 OrientedBox::GetHalfExtents() const
{
    return halfExtents;
}

CGUL::Float32 OrientedBox::GetOrientation() const
{
    return orientation;
}

CGUL::Vector2 OrientedBox::GetClosestPoint(const CGUL::Vector2& position) const
{
    using namespace CGUL;

    Vector2 axes[] =
    {
        Vector2(Math::Cos(orientation), Math::Sin(orientation)),
        Vector2(Math::Sin(orientation), -Math::Cos(orientation))
    };

    Vector2 difference = position - this->position;
    Vector2 converted(Vector2::DotProduct(difference, axes[0]), Vector2::DotProduct(difference, axes[1]));

    converted.x = Math::Clamp(converted.x, -halfExtents.x, halfExtents.x);
    converted.y = Math::Clamp(converted.y, -halfExtents.y, halfExtents.y);

    Vector2 result = this->position;
    result += axes[0] * converted.x;
    result += axes[1] * converted.y;

    return result;
}

void OrientedBox::ProjectionOnAxis(const CGUL::Vector2& axis, CGUL::Float32* min, CGUL::Float32* max) const
{
    CGUL::Matrix world;
    world = world * CGUL::Matrix::MakeRotation(orientation);
    world = world * CGUL::Matrix::MakeTranslation(position);

    CGUL::Vector2 points[] =
    {
        CGUL::Vector2( halfExtents.x,  halfExtents.y) * world,
        CGUL::Vector2(-halfExtents.x,  halfExtents.y) * world,
        CGUL::Vector2( halfExtents.x, -halfExtents.y) * world,
        CGUL::Vector2(-halfExtents.x, -halfExtents.y) * world
    };

    return Collision::ProjectionOnAxis(points, 4, axis, min, max);
}

bool OrientedBox::CollidingCircle(const Circle& other) const
{
    return CheckCircleAndOrientedBox(other, *this);
}

bool OrientedBox::CollidingAxisAlignedBox(const AxisAlignedBox& other) const
{
    return CheckAxisAlignedBoxAndOrientedBox(other, *this);
}

bool OrientedBox::CollidingOrientedBox(const OrientedBox& other) const
{
    return CheckOrientedBoxAndOrientedBox(*this, other);
}

bool OrientedBox::CollidingLine(const Line& other) const
{
    return CheckOrientedBoxAndLine(*this, other);
}

void OrientedBox::Draw() const
{
    render->Box(position, halfExtents * 2, orientation, color);
}
