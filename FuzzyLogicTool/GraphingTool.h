#pragma once
#include <SFML/Graphics.hpp>
#include "GraphFunctionCalculator.h"
class GraphingTool : public sf::Drawable, public sf::Transformable
{
public:

    // add functions to play with the entity's geometry / colors / texturing...
    void CreatePoints(const int& index, const int& min, const int& max);
    float GetPoint(const int& index, const int& min, const int& max,const float& x);

    void CleanUp();
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        // apply the entity's transform -- combine it with the one that was passed by the caller
        states.transform *= getTransform(); // getTransform() is defined by sf::Transformable
        // you may also override states.shader or states.blendMode if you want
        // draw the vertex array
        target.draw(m_vertices, states);
    }

    sf::VertexArray m_vertices;
    GraphFunctionCalculator g;
};
