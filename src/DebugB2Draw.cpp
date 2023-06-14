//
// Created by leo on 14/06/23.
//

#include "DebugB2Draw.h"
#include "PhysicsUtil.h"
#include "SFML/Graphics/ConvexShape.hpp"

DebugB2Draw::~DebugB2Draw() = default;

void DebugB2Draw::DrawPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color) {
    sf::ConvexShape polygon;
    polygon.setPointCount(vertexCount);
    for(int32 i = 0; i < vertexCount; i++){
        b2Vec2 vertex = vertices[i];
        polygon.setPoint(i,physics::b2Tosf(vertex));
    }
    polygon.setOutlineColor(sf::Color::Green);
    polygon.setFillColor(sf::Color::Transparent);
    window->draw(polygon);
}

void DebugB2Draw::DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color) {
    sf::ConvexShape polygon;
    polygon.setPointCount(vertexCount);
    for(int32 i = 0; i < vertexCount; i++){
        b2Vec2 vertex = vertices[i];
        polygon.setPoint(i,physics::b2Tosf(vertex));
    }
    polygon.setFillColor(sf::Color::Green);
    window->draw(polygon);
}

void DebugB2Draw::DrawCircle(const b2Vec2 &center, float radius, const b2Color &color) {

}

void DebugB2Draw::DrawSolidCircle(const b2Vec2 &center, float radius, const b2Vec2 &axis, const b2Color &color) {

}

void DebugB2Draw::DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color) {

}

void DebugB2Draw::DrawTransform(const b2Transform &xf) {

}

void DebugB2Draw::DrawPoint(const b2Vec2 &p, float size, const b2Color &color) {

}

DebugB2Draw::DebugB2Draw(sf::RenderWindow &window) : window(&window) {}
