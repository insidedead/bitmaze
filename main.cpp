#include <iostream>
#include <cstdint>

#define Hex(x) std::cout << std::hex << x;

uint16_t map[6] = {
	0, 	// 0000 0000 0000 0000
	1 << 2, // 0000 0000 0000 0100
	0, 	// 0000 0000 0000 0000
       	0, 	// 0000 0000 0000 0000
	0, 	// 0000 0000 0000 0000
	1 << 11	// 0000 1000 0000 0000
};


std::ostream& operator << (std::ostream &out, uint16_t *m)
{
	for(uint16_t i = 0; i < 6; i++)
	{
		out << std::hex << *(m + i) << std::endl;
	}
	return out;
}

int main()
{
	union {
		uint8_t index : 3;
	};

	index = 5;

	bool target { false };

	if(map[index] & 0xFFFF)
	{
		while(!target)
		{
			char pos {0};
			uint16_t start = 0x8000;

			while((start & 0xFFFF) != (map[index] & 0xFFFF))
			{
				start >>=1;
				++pos;
			}

			uint16_t left = map[index] << 1;
			uint16_t right = map[index] << 1;
			uint16_t top = map[index - 1] | (0x8000 >> pos); // todo
			uint16_t bottom = map[index + 1] | map[index];

			if (left & map[index] || right & map[index] || top & map[index - 1] || bottom & map[index + 1]) target = true;

			map[index] |= left | right;
			map[index - 1] |= top;
			map[index + 1] |= bottom;

			index = ((left | right) & 0xFFFF) ?  index : (top & 0xFFFF) ? top : bottom;
		}
	}

	std::cout << map;
}
