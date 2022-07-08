#include <iostream>
#include <bitset>
#include <cstdint>
#include <istream>
#include <algorithm>

struct Type {
	uint8_t t : 3;
} p[2][3] = {
	{
		0x0,
		0x0,
		0x0
	},
	{
		0x0,
		0x0,
		0x0
	},
},
masks[][3] = {
	{
		0x7,
		0x0,
		0x0
	},
	{
		1 << 2, 
		1 << 2,
		1 << 2,
	},
	{
		1,
		1,
		1
	},
	{
		0,
		0,
		0x7
	},
	{
		1 << 2,
		1 << 1,
		1
	},
	{
		1,
		1 << 1,
		1 << 2
	}
};

std::ostream& operator << (std::ostream& os, Type* m)
{
	for(int i = 0; i < 3; i++)
	{
		std::cout << std::bitset<3>(m[i].t) << std::endl;
	}
	return os;
}

void check(Type* m, bool &winner)
{
	static union {
		uint16_t mask : 9;
	};

	static union {
		uint16_t k : 9;
	};

	std::for_each(masks, masks + 5, [&] (Type *y) {
			mask = (y[0].t & 0x7) | ((y[1].t & 0x7) << 3) | ((y[2].t & 0x7) << 6);
			
			k = (m[0].t & 0x7) | ((m[1].t & 0x7) << 3) | ((m[2].t & 0x7) << 6);
			
			if(((mask & k) & 0x1FF) == (mask & 0x1FF)) winner = true;
	});
}

int main()
{
	union {
		uint8_t index : 3;
	};

	bool winner { false }, player { true };

	int answer;

	while(!winner)
	{
		Type mask { 0x4 };

		std::cin >> answer;

		index = answer <  3 ? 0 : answer < 6 ? 1 : 2;

		if((p[player][index].t | p[!player][index].t) & (mask.t >> (index == 0 ? answer : index  == 1 ? answer - 3 : answer - 6)))
		{
			std::cout << "already bited" << std::endl;
			continue;
		}
		
		p[player][index].t |= ((mask.t & 0x7) >> (index == 0 ? answer : index  == 1 ? answer - 3 : answer - 6));

		std::cout << p[player];

		check(p[player], winner);

		player = !player;
	}

	std::cout << "player" << player << "won";
}
