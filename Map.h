#ifndef MAP_H
#define MAP_H

#include "Platform.h"
#include "Position.h"

#include <vector>

class Map
{
public:

    /**
     * Construct new map.
     */
    Map();

    /**
     * Calculate the character position from the required position.
     */
    Position calcPosition(const Position& requiredPosition);

    /**
     * Calculate the position from original position and the velocity.
     */
    Position calcPosition(const Position& position, const Velocity& velocity);

protected:

    /**
     * Load the platform.
     */
    void loadPlatforms();

private:

    /**
     * The platforms for floor collision detection
     */
    std::vector<Platform> m_platforms;
};

