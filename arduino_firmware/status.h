


typedef struct
{
	float azimuth;
} StatusInterface;
StatusInterface status = {
	0.0		// azimuth
};


typedef struct
{
	float compass_angle;
	float compass_offset;
	float gps_azimuth;
} StatusInternals;
StatusInternals _status = {
	0.0,	// compass_angle
	0.0,	// compass_offset
	0.0		// gps_azimuth
};

