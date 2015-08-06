#ifndef _INCL_C1_STATUS
#define _INCL_C1_STATUS

typedef struct
{
	float azimuth;			// current arrow azimuth
	float azimuth_delta;	// difference between desired and current arrow azimuths
} StatusInterface;
StatusInterface status = {
	0.0,		// azimuth
	0.0,		// azimuth_delta
};


typedef struct
{
	int ttt;
} StatusInternals;
StatusInternals _status = {
	1, 		// TODO remove
};

#endif
