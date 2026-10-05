#pragma once

class Test
{
public:
	Test(){};
	~Test(){};


	int number2{3};

	float multiply()
	{
		return number2 * number;
	};

	void setFloat(float In)
	{
		number = In;
	}

private:
		float number{1.3f};
};
