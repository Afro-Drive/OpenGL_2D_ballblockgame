#include "input.h"


const unsigned int Input::KEY_COUNT = 1024;
bool Input::Keys[Input::KEY_COUNT] = {};
bool Input::KeysProcessed[Input::KEY_COUNT] = {};
glm::vec2 Input::velocity = glm::vec2(0.0f);

void Input::Update()
{
    // update key state from previous frame to current frame
    // current keys are only updated when it is called back by GLFW.
    for (int i = 0; i < KEY_COUNT; ++i)
        Input::KeysProcessed[i] = Input::Keys[i];
}

void Input::Init()
{
}

glm::vec2 Input::Velocity()
{
    return velocity;
}

bool Input::getKeyTrigger(int key)
{
    return Input::Keys[key] && !Input::KeysProcessed[key];
}

bool Input::getKeyState(int key)
{
    return Input::Keys[key] && Input::KeysProcessed[key];
}

void Input::UpdateVelocity()
{
    // initialize in every frame
    velocity = glm::vec2(0.0f);

    // right
    if (Input::Keys[GLFW_KEY_RIGHT] || Input::Keys[GLFW_KEY_D])
        velocity.x += 1.0f;
    // left
    if (Input::Keys[GLFW_KEY_LEFT] || Input::Keys[GLFW_KEY_A])
        velocity.x -= 1.0f;
    // up
    if (Input::Keys[GLFW_KEY_UP] || Input::Keys[GLFW_KEY_W])
        velocity.y -= 1.0f;
    // down
    if (Input::Keys[GLFW_KEY_DOWN] || Input::Keys[GLFW_KEY_S])
        velocity.y += 1.0f;
}
