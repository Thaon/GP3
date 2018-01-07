#ifndef INPUT_H
#define INPUT_H

class Input
{
public:
	static bool* m_keyStates;
	static void Init();
	static bool KeyPressed(unsigned char key);

private:
	Input() {}; //disable the creation of an object of this class
};

#endif