/* -*- Mode: C; c-basic-offset: 4; -*-
 *
 * Sun rise/set library.
 *
 * $Id$
 *
 * $Log:
 *
 */

/**
 *  * @file sunriset.h Sun rise/set library header.
 **/



#ifndef SUNREISET_H_INCLUDED
#define SUNREISET_H_INCLUDED



double day_length( int year, int month, int day,
		   double lon, double lat );

double day_civil_twilight_length( int year, int month, int day,
				  double lon, double lat );

double day_nautical_twilight_length( int year, int month, int day,
				     double lon, double lat );

double day_astronomical_twilight_length( int year, int month, int day,
					 double lon, double lat );


int sun_rise_set( int year, int month, int day,
		  double lon, double lat,
		  double * rise, double * set );

int civil_twilight( int year, int month, int day,
		    double lon, double lat,
		    double * start, double * end );

int nautical_twilight( int year, int month, int day,
		       double lon, double lat,
		       double * start, double * end );

int astronomical_twilight( int year, int month, int day,
			   double lon, double lat,
			   double * start, double * end );


#endif

