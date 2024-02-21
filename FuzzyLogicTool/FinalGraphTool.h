#pragma once
#include "GraphingTool.h"
class FinalGraphTool :
    public GraphingTool
{
public:
    void AddPoints(const std::vector<sf::Vector2f>& points_);
    std::vector<sf::Vector2f> ChangeRange(const std::vector<sf::Vector2f>& points_);

    void ClearGraph();
private:

};

