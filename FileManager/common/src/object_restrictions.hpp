#ifndef OBJECT_RESTRICTIONS_H
#define OBJECT_RESTRICTIONS_H

namespace ors
{
//-----------------------------------------------------------------------------
///
/// \brief The NonCopyble class - Объект запрещено копировать
///
class NonCopyble
{
public:

    NonCopyble(const NonCopyble&) = delete;
    NonCopyble& operator=(const NonCopyble&) = delete;

protected:

    NonCopyble() = default;
    ~NonCopyble() = default;
};
//-----------------------------------------------------------------------------
///
/// \brief The NonMovable class - Объект запрещено перемещать
///
class NonMovable
{
public:

    NonMovable(const NonMovable&&) = delete;
    NonMovable& operator=(const NonMovable&&) = delete;

protected:

    NonMovable() = default;
    ~NonMovable() = default;
};
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
///
/// \brief The FixedObject class - "Неподвижный" объект
///
class FixedObject : NonCopyble, NonMovable
{
protected:

    FixedObject() = default;
    ~FixedObject() = default;
};
//-----------------------------------------------------------------------------
} // namespace ors

#endif // OBJECT_RESTRICTIONS_H
