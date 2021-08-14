#include <iostream>
#include <cstdint>

typedef uint8_t byte;
typedef uint16_t word;
typedef uint32_t dword;

struct MeteoPoint
{
    double lat, lon, height;

    MeteoPoint(double & lat_, double & lon_, double & height_) :
    lat(lat_),
    lon(lon_),
    height(height_)
    {
	
    };
};

struct DoubleBytes
{
	byte bytes[8];
	double data;

	void operator()( double & data)
	{
		uint64_t * data_ptr = (uint64_t *)(&data);
		for(uint32_t i = 0; i < 8; i++)
		{
			bytes[7 - i] = ( (*data_ptr) >> ( i * 8 ) ) & 0xFF;
		}
	};
	
	void operator()(uint32_t & high_part, uint32_t & low_part)
	{
		uint64_t * data_ptr = (uint64_t *)(&data);
		*data_ptr = ( (uint64_t)(high_part) << 32 ) | (uint64_t)(low_part);
		*((uint32_t *)(bytes)) = high_part;
		*((uint32_t *)(bytes) + 1) = low_part;
	};

	void printBytes(void)
	{
		for(uint32_t i = 0; i < 8; i++) fprintf(stderr, "%02X ", bytes[i]);
		fprintf(stderr, "\n");
	};

	void printDouble(void)
	{
		fprintf(stderr, "%.16f\n", data);
	};
};

void packWindVelocity(uint32_t & velocity, MeteoPoint & point)
{

}

int32_t main(void)
{

	DoubleBytes tmp;
	
	double val = 1.5;
	tmp(val);
	
	tmp.printBytes();

	uint32_t low_part = 0x00EE00FF,
	high_part = 0xAABB0000;

	tmp(high_part, low_part);
	tmp.printBytes();
	tmp.printDouble();

	return 0;
}