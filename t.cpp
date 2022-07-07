#include <iostream>
#include <bitset>
#include <cstdint>
#include <istream>
#include <algorithm>

struct Type {
	uint8_t t : 3;
} p[2][3] = {
	{
		0x0, 	// 0 0 0 | 0 1 2
		0x0, 	// 0 0 0 | 3 4 5
		0x0	// 0 0 0 | 6 7 8
	},
	{
		0x0, 	// 0 0 0
		0x0, 	// 0 0 0
		0x0	// 0 0 0
	},
},
masks[][3] = {
	{
		0x7,	// 1 1 1
		0x0,	// 0 0 0
		0x0	// 0 0 0 
	},
	{
		1 << 2, // 1 0 0 // 1 1 0
		1 << 2, // 1 0 0 // 1 0 0
		1 << 2, // 1 0 0 // 1 0 1
	},
	{
		1,	// 0 0 1
		1,	// 0 0 1
		1	// 0 0 1
	},
	{
		0,	// 0 0 0
		0,	// 0 0 0
		0x7	// 1 1 1
	},
	{
		1 << 2,	// 1 0 0
		1 << 1,	// 0 1 0
		1	// 0 0 1
	},
	{
		1,	// 0 0 1
		1 << 1,	// 0 1 0
		1 << 2	// 1 0 0
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

bool check(Type* m)
{
	Type (*maskp)[6][3];

	for(maskp = &masks; maskp != &masks + 5; maskp++)
	{
		if((m[0].t & (*maskp)[0][0].t) && (m[1].t & (*maskp)[0][1].t) && (m[2].t & (*maskp)[0][2].t)) return true;
	}

	return false;
	/*
	return std::find_if(masks, masks + 5, [&] (Type *y) {
			std::cout << (m[0].t & y[0].t) << "\n" << (m[1].t & y[1].t) << "\n" << (m[2].t & y[2].t) << "\nend\n";

			if((m[0].t & y[0].t) && (m[1].t & y[1].t) && (m[2].t & y[2].t)) return true;
			return false;
	});
	*/
}

int main()
{
	union {
		uint8_t index : 3;
	};

	bool winner { false }, player { true };

	int answer;

	std::cout << "start" << std::endl;

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

		if(check(p[player])) winner = true;

		player = !player;
	}

	std::cout << "player" << player << "won";
}
