#include "lab_m1/Tema1/Tema1.h"

#include "lab_m1/Tema1/object2D.h"
#include "lab_m1/Tema1/transform2D.h"
#include <iostream>
#include <map>
#include <random>
#include <vector>

using namespace std;
using namespace m1;
bool checker = false;
struct Elem {
  std::string name;
  int health;
  float xPos, yPos;
  float radius;
  float rotation;
  float shoot;
  bool fade;
  float scaleX, scaleY;
  // Add any other properties you need for an Ally
};

std::vector<Elem> allys;
std::vector<std::string> allyNames;

std::vector<Elem> enemys;
std::vector<Elem> bullets;
std::vector<Elem> points;
std::vector<Elem> buyings;

Tema1::Tema1() {}

Tema1::~Tema1() {}

void Tema1::Init() {
  glm::ivec2 resolution = window->GetResolution();
  resolutionX = resolution.x;
  resolutionY = resolution.y;

  auto camera = GetSceneCamera();
  camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f,
                          400);
  camera->SetPosition(glm::vec3(0, 0, 50));
  camera->SetRotation(glm::vec3(0, 0, 0));
  camera->Update();
  GetCameraInput()->SetActive(false);

  glm::vec3 corner = glm::vec3(0, 0, 0);

  // General Vars
  minPos = 20;
  gridSize = 3;
  allyTypes = 4;
  enemySpeed = 50;
  squareSide = 120; // latura
  maxResolutionX = resolutionX;
  maxResolutionY = 2 * squareSide - minPos;
  pointsCounter = 0;
  onMapPoints = 0;
  heartsCounter = 3;
  enemyTimeList = 0;
  spawnPointsTime = 2;
  spawnBulletTime = 2;
  spawnEnemyTime = 3;
  buyingTurret = false;
  buyingTurretX = 0;
  buyingTurretY = 0;
  pointTime = 0;
  enemyTime = 0;

  scaleSpeedAlly = 0.4f;
  scaleSpeedEnemy = 0.4f;

  std::map<int, glm::vec3> colorMap;
  colorMap[0] = glm::vec3(0.5f, 0.5f, 0.5f); // Grey
  colorMap[1] = glm::vec3(0, 0, 1);          // Blue
  colorMap[2] = glm::vec3(1, 0.5f, 0.5f);    // Pink
  colorMap[3] = glm::vec3(0.5f, 0, 0.5f);    // Purple
  colorMap[4] = glm::vec3(1, 1, 0);          // Yellow
  colorMap[5] = glm::vec3(1, 0, 0);          // Red

  bulletCenterX = corner.x;
  bulletCenterY = corner.y;
  bulletAngularStep = 0;

  // Initialize tx and ty (the translation steps)
  translateGridX = minPos + squareSide;
  translateGridY = minPos + squareSide / 2;
  translateHPGateX = minPos + squareSide / 6;
  translateHPGateY = 2 * minPos + squareSide + squareSide / 2;
  translateGUIX = squareSide / 2 + minPos;
  translateGUIY = 3 * squareSide + 3 * minPos;
  placeHolderX = squareSide * 0.75f;
  placeHolderY = 5 * squareSide + 2 * minPos;

  gridLine0Y = minPos + squareSide / 2;
  gridLine1Y = 2 * minPos + squareSide + squareSide / 2;
  gridLine2Y = 3 * minPos + 2 * squareSide + squareSide / 2;
  gridLine0X = translateGridX - minPos;
  gridLine1X = gridLine0X + squareSide + minPos;
  gridLine2X = gridLine0X + 2 * squareSide + 2 * minPos;

  // Initialize sx and sy (the scale factors)
  scaleHPGateX = 0.5f;
  scaleHPGateY = 3.35f;

  scaleTurretX = 0.4f;
  scaleTurretY = 0.35f;
  scaleEnemyX = scaleTurretX;
  scaleEnemyY = scaleTurretY;
  scaleBulletX = scaleTurretX / 3;
  scaleBulletY = scaleTurretY / 3;

  scalePointX = scaleTurretX * 0.75f;
  scalePointY = scaleTurretY * 0.75f;

  for (int i = 0; i < gridSize; ++i) {
    for (int j = 0; j < gridSize; ++j) {
      float tempXPOS = i * squareSide + i * minPos;
      float tempYPOS = j * squareSide + j * minPos;

      std::string tempSquareName =
          "square_" + std::to_string(i) + "," + std::to_string(j);

      Mesh *square = object2D::CreateSquare(
          tempSquareName.c_str(), glm::vec3(tempXPOS, tempYPOS, 0), squareSide,
          glm ::vec3(0, 1, 0), true);
      AddMeshToList(square);
    }
  }

  Mesh *hpGate =
      object2D::CreateSquare("hpGate", corner, squareSide, colorMap[5], true);
  AddMeshToList(hpGate);

  for (int i = 0; i < allyTypes; ++i) {
    float tempXPOS = i * squareSide + 2 * i * minPos + squareSide / 4;
    float tempYPOS = maxResolutionY;

    std::string tempPlaceholderName = "placeholder_" + std::to_string(i);
    Mesh *placeholder = object2D::CreateSquare(
        tempPlaceholderName.c_str(), glm::vec3(tempXPOS, tempYPOS, 0),
        squareSide, glm::vec3(1, 1, 1), false);
    AddMeshToList(placeholder);
  }
  for (int i = 0; i < allyTypes; ++i) {
    std::string tempAllyName = "allyName_" + std::to_string(i);
    allyNames.push_back(tempAllyName);
    Mesh *ally = object2D::CreateTurret(tempAllyName.c_str(), corner,
                                        squareSide, colorMap[i], true);
    AddMeshToList(ally);
  }
  for (int i = 0; i < allyTypes; ++i) {
    std::string tempEnemyName = "enemyName_" + std::to_string(i);
    Mesh *enemy =
        object2D::CreateEnemy(tempEnemyName.c_str(), corner, squareSide,
                              colorMap[i], colorMap[5], true);
    AddMeshToList(enemy);
  }
  for (int i = 0; i < allyTypes; ++i) {
    std::string tempBulletName = "bullet_" + std::to_string(i);
    Mesh *bullet = object2D::CreateStar(tempBulletName.c_str(), corner,
                                        squareSide, colorMap[i], true);
    AddMeshToList(bullet);
  }
  float temp = object2D::GetCenterY();
  bulletCenterY += temp * 0.7f;

  Mesh *points =
      object2D::CreateStar("points", corner, squareSide, colorMap[4], true);
  AddMeshToList(points);

  Mesh *hearts =
      object2D::CreateHeart("hearts", corner, squareSide, colorMap[5], true);
  AddMeshToList(hearts);
}

void Tema1::FrameStart() {
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glm::ivec2 resolution = window->GetResolution();
  glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds) {
  if (heartsCounter == 0) {
    exit(0);
  }
  displayGrid();
  displayHPGate();
  displayGUI();
  generatePoints(deltaTimeSeconds);
  generateEnemy(deltaTimeSeconds);

  for (auto it = enemys.begin(); it != enemys.end();) {
    Elem &enemy = *it; // Get current point
    for (auto itt = bullets.begin(); itt != bullets.end();) {
      Elem &bullet = *itt;
      float distance = glm::distance(glm::vec2(enemy.xPos, enemy.yPos),
                                     glm::vec2(bullet.xPos, bullet.yPos));
      if (distance <= (enemy.radius + bullet.radius) &&
          enemy.name[enemy.name.size() - 1] ==
              bullet.name[bullet.name.size() - 1]) {
        itt = bullets.erase(itt);
        enemy.health -= 1;
        if (enemy.health == 0)
          enemy.fade = true;
        break;
      }
      ++itt;
    }
    if (!enemy.fade) {
      enemy.xPos -= enemySpeed * deltaTimeSeconds;
      displayEnemy(enemy.name, deltaTimeSeconds, enemy.xPos, enemy.yPos,
                   enemy.scaleX, enemy.scaleY);
      if (enemy.xPos < minPos + squareSide / 2)
        enemy.fade = true;
      ++it;
    }
    if (enemy.fade) {
      if (enemy.scaleX > 0 && enemy.scaleY > 0) {
        fadeAnimation(enemy.scaleX, enemy.scaleY, scaleSpeedEnemy,
                      deltaTimeSeconds);
        enemy.xPos -= enemySpeed * deltaTimeSeconds;
        displayEnemy(enemy.name, deltaTimeSeconds, enemy.xPos, enemy.yPos,
                     enemy.scaleX, enemy.scaleY);
        ++it;
      } else {
        if (enemy.xPos < minPos + squareSide / 2)
          heartsCounter -= 1;
        it = enemys.erase(it);
      }
    }
  }
  for (auto it = allys.begin(); it != allys.end();) {
    Elem &ally = *it;
    ally.shoot += deltaTimeSeconds;
    for (auto itt = enemys.begin(); itt != enemys.end();) {
      Elem &enemy = *itt;
      float distance = glm::distance(glm::vec2(ally.xPos, ally.yPos),
                                     glm::vec2(enemy.xPos, enemy.yPos));
      if (distance <= (enemy.radius + ally.radius)) {
        ally.fade = true;
      }
      ++itt;
    }
    if (ally.fade) {
      if (ally.scaleX > 0 && ally.scaleY > 0) {
        fadeAnimation(ally.scaleX, ally.scaleY, scaleSpeedAlly,
                      deltaTimeSeconds);
        displayAlly(ally.name, ally.xPos, ally.yPos, ally.scaleX, ally.scaleY);
        ++it;
      } else {
        it = allys.erase(it);
      }
    } else {
      for (const Elem &enemy : enemys) {
        if (enemy.yPos == ally.yPos && ally.name[ally.name.size() - 1] ==
                                           enemy.name[enemy.name.size() - 1]) {
          if (ally.shoot > spawnBulletTime*0.5f) {
            std::string tempName = "";
            if (ally.name == "allyName_0")
              tempName = "bullet_0";
            if (ally.name == "allyName_1")
              tempName = "bullet_1";
            if (ally.name == "allyName_2")
              tempName = "bullet_2";
            if (ally.name == "allyName_3")
              tempName = "bullet_3";
            createElem(tempName, ally.xPos, ally.yPos, scaleBulletX,
                       scaleBulletY, 2);
            ally.shoot = 0;
          }
        }
      }
      displayAlly(ally.name, ally.xPos, ally.yPos, ally.scaleX, ally.scaleY);
      ++it;
    }
  }
  for (const Elem &buy : buyings) {
    displayAlly(buy.name, buy.xPos, buy.yPos, buy.scaleX, buy.scaleY);
  }
  for (const Elem &point : points) {
    displayPoint(point.xPos, point.yPos, scalePointX, scalePointY);
  }
  for (Elem &bullet : bullets) {
    bullet.xPos += enemySpeed * 5 * deltaTimeSeconds;
    bullet.rotation += 20 * deltaTimeSeconds;
    displayBullet(bullet.name, bullet.xPos, deltaTimeSeconds, bullet.rotation,
                  bullet.yPos - minPos / 2);
  }
}

void Tema1::fadeAnimation(float &scaleX, float &scaleY, float scaleSpeed,
                          float deltaTime) {
  scaleX -= deltaTime * scaleSpeed;
  scaleY -= deltaTime * scaleSpeed;
}
void Tema1::createElem(std::string name, float xPos, float yPos, float scaleX,
                       float scaleY, int elemType) {

  Elem elem;
  elem.xPos = xPos;
  elem.yPos = yPos;
  elem.scaleX = scaleX;
  elem.scaleY = scaleY;
  elem.name = name;
  elem.rotation = bulletAngularStep;
  elem.shoot = 0;
  elem.fade = false;
  elem.health = 3;
  std::string bulletType = name;

  switch (elemType) {
  case 0:
    elem.radius = (scaleTurretY * squareSide + scaleTurretX * squareSide) / 2;
    allys.push_back(elem);
    break;
  case 1:
    elem.radius = (scaleEnemyY * squareSide + scaleEnemyX * squareSide) / 2;
    enemys.push_back(elem);
    break;
  case 2:
    elem.radius = (scaleBulletY * squareSide + scaleBulletX * squareSide) / 2;
    bullets.push_back(elem);
    break;
  case 3:
    elem.radius = 40.0f;
    points.push_back(elem);
    break;
  case 4:
    buyings.push_back(elem);
    break;
  }
}

void Tema1::generatePoints(float deltaTime) {
  if ((pointTime > spawnPointsTime) && (onMapPoints < 3)) {
    createRandomPoint();
    createRandomPoint();
    createRandomPoint();
    pointTime = 0;
  } else {
    std::random_device rd;
    std::mt19937 gen(rd()); // Mersenne Twister pseudo-random number generator
    std::uniform_real_distribution<float> randDist(0,1);
    float randTime = randDist(gen);
    pointTime += deltaTime * randTime;
 
  }
}
void Tema1::generateEnemy(float deltaTime) {
  enemyTime += deltaTime;

  std::random_device rd;
  std::mt19937 gen(rd()); // Mersenne Twister pseudo-random number generator
  std::uniform_real_distribution<float> randName(0, 1);
  std::uniform_real_distribution<float> randY(0, 1);
  float yType = randY(gen);
  float nameType = randName(gen);
  std::string name = "";
  float xPos = 0;
  float yPos = 0;

  if (nameType < 0.25f) {
    name = "enemyName_0";
  } else if (nameType < 0.5f) {
    name = "enemyName_1";
  } else if (nameType < 0.75f) {
    name = "enemyName_2";
  } else {
    name = "enemyName_3";
  }
  if (yType < 0.33f) {
    yPos = gridLine0Y;
  } else if (yType < 0.66f) {
    yPos = gridLine1Y;
  } else {
    yPos = gridLine2Y;
  }

  switch (enemyTimeList) {
  case 0:
    if ((enemyTime >= spawnEnemyTime)) {
      createElem(name, maxResolutionX, yPos, scaleEnemyX, scaleEnemyY, 1);
      enemyTime = 0;
    }
    break;
  case 1:
    if ((enemyTime >= spawnEnemyTime * 0.5f)) {
      createElem(name, maxResolutionX, yPos, scaleEnemyX, scaleEnemyY, 1);
      enemyTime = 0;
    }
    break;
  case 2:
    if ((enemyTime >= spawnEnemyTime * 0.25f)) {
      createElem(name, maxResolutionX, yPos, scaleEnemyX, scaleEnemyY, 1);
      enemyTime = 0;
    }
    break;
  }
}

void Tema1::createRandomPoint() {
  std::random_device rd;
  std::mt19937 gen(rd()); // Mersenne Twister pseudo-random number generator
  std::uniform_real_distribution<float> xDist(minPos,
                                              placeHolderX + 7.0f * squareSide);
  std::uniform_real_distribution<float> yDist(minPos,
                                              placeHolderY - 8 * minPos);
  // Generate random positions
  float xRand = xDist(gen);
  /* float yRand = yDist(gen); */
  float yRand = yDist(gen);
  onMapPoints += 1;
  createElem("point", xRand, yRand, scalePointX, scalePointY, 3);
}
void Tema1::displayBullet(std::string name, float xPos, float deltaTime,
                          float rotation, float yPos) {
  modelMatrix = glm::mat3(1);
  modelMatrix *= transform2D::Translate(xPos, yPos);
  modelMatrix *= transform2D::Scale(scaleBulletX, scaleBulletY);
  modelMatrix *= transform2D::Translate(bulletCenterX, bulletCenterY);
  modelMatrix *= transform2D::Rotate(rotation);
  modelMatrix *= transform2D::Translate(-bulletCenterX, -bulletCenterY);
  RenderMesh2D(meshes[name], shaders["VertexColor"], modelMatrix);
}
void Tema1::displayEnemy(std::string name, float deltaTime, float xPos,
                         float yPos, float scaleX, float scaleY) {
  /* fadeAnimation(scaleEnemyX, scaleEnemyY, deltaTime); */

  modelMatrix = glm::mat3(1);
  modelMatrix *= transform2D::Translate(xPos, yPos);
  modelMatrix *= transform2D::Scale(scaleX, scaleY);
  modelMatrix *= transform2D::Rotate(150);
  RenderMesh2D(meshes[name], shaders["VertexColor"], modelMatrix);
}
void Tema1::displayAlly(std::string name, float xPos, float yPos, float scaleX,
                        float scaleY) {

  modelMatrix = glm::mat3(1);
  modelMatrix *= transform2D::Translate(xPos, yPos);
  modelMatrix *= transform2D::Scale(scaleX, scaleY);
  RenderMesh2D(meshes[name], shaders["VertexColor"], modelMatrix);
}
void Tema1::displayPoint(float xPos, float yPos, float scaleX, float scaleY) {
  modelMatrix = glm::mat3(1);
  modelMatrix *= transform2D::Translate(xPos, yPos);
  modelMatrix *= transform2D::Scale(scaleX, scaleY);
  RenderMesh2D(meshes["points"], shaders["VertexColor"], modelMatrix);
}
void Tema1::displayHearth(float xPos, float yPos) {
  modelMatrix = glm::mat3(1);
  modelMatrix *= transform2D::Translate(xPos, yPos);
  modelMatrix *= transform2D::Scale(0.5f, 0.5f);
  RenderMesh2D(meshes["hearts"], shaders["VertexColor"], modelMatrix);
}
void Tema1::displayGrid() {
  modelMatrix = glm::mat3(1);
  modelMatrix *= transform2D::Translate(translateGridX, translateGridY);
  for (int i = 0; i < gridSize; ++i) {
    for (int j = 0; j < gridSize; ++j) {

      std::string tempSquareName =
          "square_" + std::to_string(i) + "," + std::to_string(j);
      RenderMesh2D(meshes[tempSquareName], shaders["VertexColor"], modelMatrix);
    }
  }
}
void Tema1::displayHPGate() {
  modelMatrix = glm::mat3(1);
  modelMatrix *= transform2D::Translate(translateHPGateX, translateHPGateY);
  modelMatrix *= transform2D::Scale(scaleHPGateX, scaleHPGateY);
  RenderMesh2D(meshes["hpGate"], shaders["VertexColor"], modelMatrix);
}
void Tema1::displayGUI() {
  modelMatrix = glm::mat3(1);
  modelMatrix *= transform2D::Translate(translateGUIX, translateGUIY);
  for (int i = 0; i < allyTypes; ++i) {
    std::string tempPlaceholderName = "placeholder_" + std::to_string(i);
    RenderMesh2D(meshes[tempPlaceholderName], shaders["VertexColor"],
                 modelMatrix);
  }
  for (int i = 0; i < allyTypes; ++i) {
    displayAlly(allyNames[i], placeHolderX + i * squareSide + 2 * i * minPos,
                placeHolderY, scaleTurretX, scaleTurretY);
  }
  float yPos = placeHolderY - squareSide / 2 - 1.5f * minPos;

  displayPoint(placeHolderX + minPos, yPos, scaleBulletX, scaleBulletY);

  displayPoint(placeHolderX + squareSide + 2 * minPos, yPos, scaleBulletX,
               scaleBulletY);
  displayPoint(placeHolderX + squareSide + 4 * minPos, yPos, scaleBulletX,
               scaleBulletY);

  displayPoint(placeHolderX + 2 * squareSide + 4 * minPos, yPos, scaleBulletX,
               scaleBulletY);
  displayPoint(placeHolderX + 2 * squareSide + 6 * minPos, yPos, scaleBulletX,
               scaleBulletY);

  displayPoint(placeHolderX + 3 * squareSide + 5 * minPos, yPos, scaleBulletX,
               scaleBulletY);
  displayPoint(placeHolderX + 3 * squareSide + 7 * minPos, yPos, scaleBulletX,
               scaleBulletY);
  displayPoint(placeHolderX + 3 * squareSide + 9 * minPos, yPos, scaleBulletX,
               scaleBulletY);
  for (int i = 0; i < pointsCounter; ++i) {
    if (placeHolderX + 5.5f * squareSide + 2 * i * minPos <
        maxResolutionX - minPos)
      displayPoint(placeHolderX + 5.5f * squareSide + 2 * i * minPos, yPos,
                   scaleBulletX, scaleBulletY);
    else if (placeHolderX + squareSide * 0.5f + 4 * minPos + 2 * i * minPos <
             maxResolutionX - minPos)
      displayPoint(placeHolderX + squareSide * 0.5f + 4 * minPos +
                       2 * i * minPos,
                   yPos - 2 * minPos, scaleBulletX, scaleBulletY);
    else
      displayPoint(-(placeHolderX + 2 * squareSide - 2 * minPos) +
                       2 * i * minPos,
                   yPos - 4 * minPos, scaleBulletX, scaleBulletY);
  }
  for (int i = 0; i < heartsCounter; ++i) {
    displayHearth(placeHolderX + 6 * squareSide + minPos + i * squareSide +
                      2 * i * minPos,
                  placeHolderY);
  }
}

void Tema1::FrameEnd() {}

void Tema1::OnInputUpdate(float deltaTime, int mods) {}

void Tema1::OnKeyPress(int key, int mods) {
  if (key == GLFW_KEY_F) {
    if (heartsCounter < 3)
      heartsCounter += 1;
  }
  if (key == GLFW_KEY_A) {
    pointsCounter -= 1;
    heartsCounter -= 1;
  }

  // Add key press event
}

void Tema1::OnKeyRelease(int key, int mods) {
  // Add key release event
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) {
  if (buyingTurret) {
    buyings[0].xPos = mouseX;
    buyings[0].yPos = resolutionY - mouseY;
  }
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {
  if (button == 2) {
    // Disable Ally
    for (auto it = allys.begin(); it != allys.end();) {
      Elem &ally = *it; // Get current point
      float distance = glm::distance(
          glm::vec2(mouseX, mouseY),
          glm::vec2(ally.xPos, resolutionY - ally.yPos - minPos / 2));
      if (distance < ally.radius) {
        ally.fade = true;
      
      }
      ++it;
    }
  }

  // Generate Points
  for (auto it = points.begin(); it != points.end();) {
    const Elem &point = *it; // Get current point
    float distance = glm::distance(
        glm::vec2(mouseX, mouseY),
        glm::vec2(point.xPos, resolutionY - point.yPos - minPos / 2));
    if (distance < point.radius) {
      it = points.erase(it); // Erase the element and update iterato
      pointsCounter += 1;
      onMapPoints -= 1;
    } else
      ++it;
  }

  for (int i = 1; i < allyTypes + 1; ++i) {
    float distance = glm::distance(
        glm::vec2(mouseX, mouseY),
        glm::vec2(i * squareSide + 2 * (i - 1) * minPos - minPos / 2,
                  resolutionY - placeHolderY));
    if (distance < squareSide / 2) {
      buyingTurret = true;
      bool canBuy = false;
      string name = "";
      switch (i) {
      case 1:
        name = "allyName_0";
        if (pointsCounter >= 1) {
          pointsCounter -= 1;
          canBuy = true;
        }
        break;
      case 2:
        name = "allyName_1";
        if (pointsCounter >= 2) {
          pointsCounter -= 2;
          canBuy = true;
        }
        break;
      case 3:
        name = "allyName_2";
        if (pointsCounter >= 2) {
          pointsCounter -= 2;
          canBuy = true;
        }
        break;
      case 4:
        name = "allyName_3";
        if (pointsCounter >= 3) {
          pointsCounter -= 3;
          canBuy = true;
        }
        break;
      }
      if (canBuy) {
        createElem(name, mouseX, resolutionY - mouseY, scaleTurretX,
                   scaleTurretY, 4);
      } else
        buyingTurret = false;
      break;
    }
  }
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {
  // Add mouse button release event
  buyingTurret = false;
  if (!buyings.empty()) {
    bool chooseX = false;
    bool chooseY = false;
    float xPos = 0;
    float yPos = 0;
    if (((buyings[0].xPos >= gridLine0X - squareSide / 2) &&
         (buyings[0].xPos <= gridLine0X + squareSide / 2)) &&
        !chooseX) {
      xPos = gridLine0X;
      chooseX = true;
    }
    if (((buyings[0].xPos >= gridLine1X - squareSide / 2) &&
         (buyings[0].xPos <= gridLine1X + squareSide / 2)) &&
        !chooseX) {
      xPos = gridLine1X;
      chooseX = true;
    }
    if (((buyings[0].xPos >= gridLine2X - squareSide / 2) &&
         (buyings[0].xPos <= gridLine2X + squareSide / 2)) &&
        !chooseX) {
      xPos = gridLine2X;
      chooseX = true;
    }
    if (((buyings[0].yPos >= gridLine0Y - squareSide / 2) &&
         (buyings[0].yPos <= gridLine0Y + squareSide / 2)) &&
        !chooseY) {
      yPos = gridLine0Y;
      chooseY = true;
    }
    if (((buyings[0].yPos >= gridLine1Y - squareSide / 2) &&
         (buyings[0].yPos <= gridLine1Y + squareSide / 2)) &&
        !chooseY) {
      yPos = gridLine1Y;
      chooseY = true;
    }
    if (((buyings[0].yPos >= gridLine2Y - squareSide / 2) &&
         (buyings[0].yPos <= gridLine2Y + squareSide / 2)) &&
        !chooseY) {
      yPos = gridLine2Y;
      chooseY = true;
    }
    bool alreadyOnMap = false;
    for (const Elem &ally : allys) {
      if (ally.xPos == xPos && ally.yPos == yPos) {
        alreadyOnMap = true;
      }
    }
    if (!alreadyOnMap && xPos != 0 && yPos != 0)
      createElem(buyings[0].name, xPos, yPos, scaleTurretX, scaleTurretY, 0);
    buyings.erase(buyings.begin());
  }
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) {}

void Tema1::OnWindowResize(int width, int height) {}
