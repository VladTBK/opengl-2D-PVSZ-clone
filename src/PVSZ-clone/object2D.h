#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"

namespace object2D {
Mesh *CreateSquare(const std::string &name, glm::vec3 leftBottomCorner,
                   float length, glm::vec3 color, bool fill = false);
Mesh *CreateTurret(const std::string &name, glm::vec3 leftBottomCorner,
                   float length, glm::vec3 color, bool fill = false);
Mesh *CreateStar(const std::string &name, glm::vec3 leftBottomCorner,
                 float length, glm::vec3 color, bool fill = false);
Mesh *CreateEnemy(const std::string &name, glm::vec3 leftBottomCorner,
                  float length, glm::vec3 color1, glm::vec3 color2,
                  bool fill = false);
Mesh *CreateHeart(const std::string &name, glm::vec3 leftBottomCorner,
                   float length, glm::vec3 color, bool fill = false);
float GetCenterY();
} // namespace object2D
