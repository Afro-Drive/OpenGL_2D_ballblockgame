#ifndef INPUT_H
#define INPUT_H

#include<glad/gl.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>


/// <summary>
/// Input device class is defined about processes from Keyboard, Mouse, GamePad,
/// multiple input devices.
/// </summary>
static class Input
{
	public:
		const static unsigned int KEY_COUNT;
		static bool Keys[];
		static bool KeysProcessed[];

		static void Init();
		static void Update();
		static glm::vec2 Velocity();

		/// <summary>
		/// Have key JUST been pressed?
		/// </summary>
		/// <param name="key"></param>
		/// <returns>whether current key is pressed and previous key was not or not.</returns>
		static bool getKeyTrigger(int key);

		/// <summary>
		/// Have key been pressed since previous frame?
		/// </summary>
		/// <param name="key"></param>
		/// <returns>whether current and previous keys are pressed or not.</returns>
		static bool getKeyState(int key);

	private:
		static glm::vec2 velocity;

		/// <summary>
		/// hidden constructor
		/// </summary>
		Input() { }
		
		static void UpdateVelocity();
};

#endif // !INPUT_H
