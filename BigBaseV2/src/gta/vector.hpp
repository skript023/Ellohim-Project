#pragma once

namespace rage
{
	struct ivector2
	{
		int x{};
		int y{};
	};

	struct ivector3
	{
		int x{};
		int y{};
		int z{};
	};

	struct ivector4
	{
		int x{};
		int y{};
		int z{};
		int w{};
	};

	struct vector2
	{
		vector2() = default;
		vector2(float x, float y):
			x(x), y(y)
		{}

		float x{};
		float y{};
	};

	struct vector3
	{
		vector3() = default;
		vector3(float x, float y, float z):
			x(x), y(y), z(z)
		{}

		float x{};
		float y{};
		float z{};
	};

	struct vector4
	{
		float x{};
		float y{};
		float z{};
		float w{};
	};

#pragma pack(push, 1)
	class scrVector
	{
	public:
		scrVector() = default;

		scrVector(float x, float y, float z) :
			x(x), y(y), z(z)
		{}
	public:
		float x{};
	private:
		char m_padding1[0x04];
	public:
		float y{};
	private:
		char m_padding2[0x04];
	public:
		float z{};
	private:
		char m_padding3[0x04];

	public:
		inline scrVector operator+(scrVector vec) { return { x + vec.x, y + vec.y, z + vec.z }; };
		inline scrVector operator-(scrVector vec) { return { x - vec.x, y - vec.y, z - vec.z }; };
		inline scrVector operator*(scrVector vec) { return { x * vec.x, y * vec.y, z * vec.z }; };
		inline scrVector operator/(scrVector vec) { return { x / vec.x, y / vec.y, z / vec.z }; };

		inline bool operator==(const scrVector vec) { return x == vec.x && y == vec.y && z == vec.z; };
		inline bool operator==(const vector3 vec) { return x == vec.x && y == vec.y && z == vec.z; };
	};
#pragma pack(pop)
}
