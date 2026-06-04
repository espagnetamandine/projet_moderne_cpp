#ifndef _CCARTE_H
#define _CCARTE_H

#include <string>
#include <iostream>

using namespace std;

class CCarte {
private :
	string sCAR_color;
	unsigned int uiCAR_value;

public :
	CCarte(string sColor, unsigned int uiValue)
	{
		sCAR_color = sColor;
		uiCAR_value = uiValue;
	};

	string getCAR_color() { return sCAR_color; };
	unsigned int getCAR_value() { return uiCAR_value; };

	friend std::ostream& operator<<(std::ostream& os, const CCarte& CarteAAfficher)
	{

		os << CarteAAfficher.uiCAR_value << " de " << CarteAAfficher.sCAR_color;

		return os;
	}
};

#endif 