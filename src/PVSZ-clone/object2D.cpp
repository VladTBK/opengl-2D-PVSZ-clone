#include "object2D.h"
#include "core/engine.h"
#include "utils/gl_utils.h"
#include <cmath>
#include <iostream>
#include <vector>

float centerStarY;
Mesh *object2D::CreateSquare(const std::string &name,
                             glm::vec3 leftBottomCorner, float length,
                             glm::vec3 color, bool fill) {
  glm::vec3 corner = leftBottomCorner;

  std::vector<VertexFormat> vertices = {
      VertexFormat(corner, color), // 0
      VertexFormat(corner + glm::vec3(-length * 0.5f, length * 0.5f, 0),
                   color), // 1
      VertexFormat(corner + glm::vec3(length * 0.5f, length * 0.5f, 0),
                   color), // 2
      VertexFormat(corner + glm::vec3(length * 0.5f, -length * 0.5f, 0),
                   color), // 3
      VertexFormat(corner + glm::vec3(-length * 0.5f, -length * 0.5f, 0),
                   color)}; // 4

  Mesh *square = new Mesh(name);
  std::vector<unsigned int> indices = {1, 0, 2, 2, 0, 3, 3, 0, 4, 4, 0, 1};

  if (!fill) {
    indices = {1, 2, 3, 4};
    square->SetDrawMode(GL_LINE_LOOP);
  } else {
    indices.push_back(2);
  }

  square->InitFromData(vertices, indices);
  return square;
}
Mesh *object2D::CreateHeart(const std::string &name,
                             glm::vec3 leftBottomCorner, float length,
                             glm::vec3 color, bool fill) {
  glm::vec3 corner = leftBottomCorner;

  std::vector<VertexFormat> vertices = {
      VertexFormat(corner, color), // 0
      VertexFormat(corner + glm::vec3(length * 0.5f, length * 0.5f, 0),
                   color),                                           // 1
      VertexFormat(corner + glm::vec3(length * 0.8f, 0, 0), color),  // 2
      VertexFormat(corner + glm::vec3(0, -length, 0), color),        // 3
      VertexFormat(corner + glm::vec3(-length * 0.8f, 0, 0), color), // 4
      VertexFormat(corner + glm::vec3(-length * 0.5f, length * 0.5f, 0),
                   color), // 5
  };
  Mesh *heart = new Mesh(name);
  std::vector<unsigned int> indices = {0, 1, 2, 0, 3, 2, 0, 4, 3, 0, 5, 4};

  if (!fill) {
    indices = {1, 2, 3, 4};
    heart->SetDrawMode(GL_LINE_LOOP);
  } else {
    indices.push_back(2);
  }

  heart->InitFromData(vertices, indices);
  return heart;
}

Mesh *object2D::CreateTurret(const std::string &name,
                             glm::vec3 leftBottomCorner, float length,
                             glm::vec3 color, bool fill) {
  glm::vec3 corner = leftBottomCorner;

  std::vector<VertexFormat> vertices = {
      VertexFormat(corner + glm::vec3(0, 0, 1), color),               // 0
      VertexFormat(corner + glm::vec3(0, length, 1), color),          // 1
      VertexFormat(corner + glm::vec3(length * 0.66f, 0, 1), color),  // 2
      VertexFormat(corner + glm::vec3(0, -length, 1), color),         // 3
      VertexFormat(corner + glm::vec3(-length * 0.66f, 0, 1), color), // 4
      VertexFormat(corner + glm::vec3(0, length * 0.33f, 1), color),  // 5
      VertexFormat(corner + glm::vec3(length * 1.33f, length * 0.33f, 1),
                   color), // 6
      VertexFormat(corner + glm::vec3(length * 1.33f, -length * 0.33f, 1),
                   color),                                            // 7
      VertexFormat(corner + glm::vec3(0, -length * 0.33f, 1), color), // 8
  };

  Mesh *square = new Mesh(name);
  std::vector<unsigned int> indices = {1, 0, 2, 2, 0, 3, 3, 0, 4,
                                       4, 0, 1, 5, 6, 7, 5, 7, 8};

  if (!fill) {
    square->SetDrawMode(GL_LINE_LOOP);
  } else {
    // Draw 2 triangles. Add the remaining 2 indices
    indices.push_back(0);
    indices.push_back(2);
  }

  square->InitFromData(vertices, indices);
  return square;
}

Mesh *object2D::CreateStar(const std::string &name, glm::vec3 leftBottomCorner,
                           float length, glm::vec3 color, bool fill) {
  glm::vec3 corner = leftBottomCorner;

  glm::vec3 initialStarTip = corner + glm::vec3(0, length, 1);

  std::vector<glm::vec3> points;

  // create star points
  for (int i = 1; i < 5; ++i) {
    float theta = -i * 1.256637; // 78 de grade in rads
    float x = initialStarTip.x * cos(theta) - initialStarTip.y * sin(theta);
    float y = initialStarTip.y * cos(theta) + initialStarTip.x * sin(theta);

    glm::vec3 newPoint(x, y, 1);
    points.push_back(newPoint);
  }

  // calculate the yPos of center
  centerStarY = ((initialStarTip.y + abs(points[0].y) + abs(points[1].y) +
                  abs(points[2].y) + abs(points[3].y)) /
                 5);

  // Added some ofsets to make it more like a star
  std::vector<VertexFormat> vertices = {
      VertexFormat(corner, color), // 0
      VertexFormat(initialStarTip + glm::vec3(0, length * 0.6f, 0),
                   color), // 1
      VertexFormat(points[0] + glm::vec3(length * 0.1f, length * 0.5f, 0),
                   color), // 2
      VertexFormat(points[1] + glm::vec3(length * 0.1f, length * 0.3f, 0),
                   color), // 3
      VertexFormat(points[2] + glm::vec3(-length * 0.1f, length * 0.3f, 0),
                   color), // 4
      VertexFormat(points[3] + glm::vec3(-length * 0.1f, length * 0.5f, 0),
                   color) // 5
  };
  Mesh *square = new Mesh(name);
  std::vector<unsigned int> indices = {1, 4, 0, 0, 2, 5, 1, 0, 3};
  if (!fill) {
    square->SetDrawMode(GL_LINE_LOOP);
  } else {
    // Draw 2 triangles. Add the remaining 2 indices
    indices.push_back(0);
    indices.push_back(2);
  }

  square->InitFromData(vertices, indices);
  return square;
}
float object2D::GetCenterY() { return centerStarY; }

Mesh *object2D::CreateEnemy(const std::string &name, glm::vec3 leftBottomCorner,
                            float length, glm::vec3 color1, glm::vec3 color2,
                            bool fill) {
  glm::vec3 corner = leftBottomCorner;
  glm::vec3 bigHexagonTip = corner + glm::vec3(0, length, 2);
  glm::vec3 smallHexagonTip = corner + glm::vec3(0, length * 0.5f, 3);
  glm::vec3 scale = glm::vec3(0, -length * 0.3f, 1);
  std::vector<glm::vec3> pointsBig;
  std::vector<glm::vec3> pointsSmall;

  // create Big Hexagone
  for (int i = 1; i < 6; ++i) {
    float theta = -i * 1.047198; // 60 de grade in radians
    float x = bigHexagonTip.x * cos(theta) - bigHexagonTip.y * sin(theta);
    float y = bigHexagonTip.y * cos(theta) + bigHexagonTip.x * sin(theta);

    glm::vec3 newPoint(x, y, 2);
    pointsBig.push_back(newPoint);
  }

  // create Small Hexagone
  for (int i = 1; i < 6; ++i) {
    float theta = -i * 1.047198; // 60 de grade in radians
    float x = smallHexagonTip.x * cos(theta) - smallHexagonTip.y * sin(theta);
    float y = smallHexagonTip.y * cos(theta) + smallHexagonTip.x * sin(theta);

    glm::vec3 newPoint(x, y, 3);
    pointsSmall.push_back(newPoint);
  }

  std::vector<VertexFormat> vertices = {
      VertexFormat(corner + glm::vec3(0, 0, 2),
                   color1),                              // 0
      VertexFormat(bigHexagonTip, color1),               // 1
      VertexFormat(pointsBig[0], color1),                // 2
      VertexFormat(pointsBig[1], color1),                // 3
      VertexFormat(pointsBig[2], color1),                // 4
      VertexFormat(pointsBig[3], color1),                // 5
      VertexFormat(pointsBig[4], color1),                // 6
      VertexFormat(corner + glm::vec3(0, 0, 3), color2), // 7
      VertexFormat(smallHexagonTip, color2),             // 8
      VertexFormat(pointsSmall[0], color2),              // 9
      VertexFormat(pointsSmall[1], color2),              // 10
      VertexFormat(pointsSmall[2], color2),              // 11
      VertexFormat(pointsSmall[3], color2),              // 12
      VertexFormat(pointsSmall[4], color2),              // 13
  };
  Mesh *square = new Mesh(name);
  std::vector<unsigned int> indices = {
      0, 1, 2, 2, 0, 3,  3,  0, 4,  4,  0, 5,  5,  0, 6,  6,  0, 1,
      8, 7, 9, 9, 7, 10, 10, 7, 11, 11, 7, 12, 12, 7, 13, 13, 7, 8};

  if (!fill) {
    square->SetDrawMode(GL_LINE_LOOP);
  } else {
    // Draw 2 triangles. Add the remaining 2 indices
    indices.push_back(0);
    indices.push_back(2);
  }

  square->InitFromData(vertices, indices);
  return square;
}
