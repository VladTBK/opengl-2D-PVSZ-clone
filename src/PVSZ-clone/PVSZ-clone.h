#pragma once

#include "components/simple_scene.h"
#include <map>
namespace m1 {
class Tema1 : public gfxc::SimpleScene {
public:
  Tema1();
  ~Tema1();
  void Init() override;

private:
  void FrameStart() override;
  void Update(float deltaTimeSeconds) override;
  void FrameEnd() override;

  void createElem(std::string name, float xPos, float yPos, float scaleX,
                  float scaleY, int elemType);
  void displayEnemy(std::string name, float deltaTime, float xPos, float yPos,
                    float scaleX, float scaleY);
  void displayAlly(std::string name, float xPos, float yPos, float scaleX,
                   float scaleY);
  void displayBullet(std::string name, float xPos, float deltaTime,
                     float rotation, float yPos);
  void displayPoint(float xPos, float yPos, float scaleX, float scaleY);
  void displayHearth(float xPos, float yPos);
  void fadeAnimation(float &scaleX, float &scaleY, float scaleSpeed,
                     float deltaTime);
  void displayGrid();
  void displayHPGate();
  void displayGUI();
  void createRandomPoint();
  void generatePoints(float deltaTime);
  void generateEnemy(float deltaTime);

  void OnInputUpdate(float deltaTime, int mods) override;
  void OnKeyPress(int key, int mods) override;
  void OnKeyRelease(int key, int mods) override;
  void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
  void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
  void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
  void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
  void OnWindowResize(int width, int height) override;

protected:
  float cx, cy;
  glm::mat3 modelMatrix;
  int gridSize, allyTypes, livesNumber, minPos, squareSide, resolutionX,
      resolutionY, maxResolutionX, maxResolutionY, enemySpeed, pointsCounter,
      heartsCounter, onMapPoints, spawnBulletTime, spawnPointsTime,
      spawnEnemyTime, enemyTimeList, turretType;
  float translateGridX, translateGUIX, placeHolderX, placeHolderY,
      translateGUIY, translateGridY, buyingTurretX, buyingTurretY,
      translateHPGateX, translateHPGateY, gridLine2Y, gridLine1Y, gridLine0Y,
      gridLine2X, gridLine1X, gridLine0X, scaleSpeedAlly, scaleSpeedEnemy,
      pointTime, enemyTime;
  float scaleHPGateX, scaleHPGateY, scaleTurretX, scaleTurretY, scaleEnemyX,
      scaleEnemyY, scaleBulletX, scaleBulletY, scalePointX, scalePointY;
  float bulletAngularStep;
  float bulletCenterX, bulletCenterY;
  float bulletOffsetY;
  bool buyingTurret;
};
} // namespace m1
  //
