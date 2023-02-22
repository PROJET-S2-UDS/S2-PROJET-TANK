#include "tankEnnemie.h"

TankEnnemie::TankEnnemie()
{
}

TankEnnemie::TankEnnemie(Tank* m_target, std::string m_name, int m_health, int m_x, int m_y, Type m_type) : Tank(m_name, m_health, m_x, m_y, m_type)
{
    target = m_target;
}

TankEnnemie::~TankEnnemie()
{
}

void TankEnnemie::setTarget(Tank* m_target)
{
    target = m_target;
}

Tank* TankEnnemie::getTarget()
{
    return target;
}