/* -*- Mode: C; c-basic-offset: 4; -*-
 *
 * Sun rise/set table.
 */

/**
 * @file main.c Sun rise/set table implementation.
 */


#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <time.h>
#include <math.h>

#include "sunriset.h"


#define RADEG    ( 180. / M_PI )
#define DEGRAD   ( M_PI / 180. )
#define DEGHOUR  ( 24. / 360. )


static int parse_cmdline( int argc, char **argv );
static void print_table( void );
static void print_csv_header( void );
static void print_row( int year, int month, int day );
static void print_eot( int day );
static double get_eot( int day );
static void hh2hms( double hh, int * h, int * m, int * s );
static void dd2dms( double dd, int * d, int * m, double * s );


static int     opt_offset    = 0;
static double  opt_latitude  = 0.;
static double  opt_longitude = 0.;

static int  opt_year  = -1;
static int  opt_month = -1;
static int  opt_day   = -1;

static int  opt_eot = 0;

static int  opt_noon_time             = 0;
static int  opt_civil_twilight        = 0;
static int  opt_nautical_twilight     = 0;
static int  opt_astronomical_twilight = 0;

static int  opt_out_csv = 0;
static int  opt_debug   = 0;

static char * delimiter = "    ";


int main( int argc, char ** argv )
{
    if( !parse_cmdline( argc, argv ) )
	return 1;

    print_table();

    return 0;
}


static void print_table( void )
{
    time_t t;
    struct tm *tm;

    t = time( NULL );
    tm = gmtime( &t );

    if( opt_year != -1 )
	tm->tm_year = opt_year - 1900;

    if( opt_month != -1 )
	tm->tm_mon = opt_month - 1;
    else if( opt_day == -1 )
	tm->tm_mon = 0;

    if( opt_day != -1 )
	tm->tm_mday = opt_day;
    else
	tm->tm_mday = 1;

    if( opt_out_csv )
	print_csv_header();

    t = mktime( tm );
    tm = localtime( &t );

    while( 1 ) {
	if( opt_eot )
	    print_eot( tm->tm_yday );
	else
	    print_row( tm->tm_year + 1900,
		       tm->tm_mon + 1,
		       tm->tm_mday );

	tm->tm_mday++;
	t = mktime( tm );
	tm = localtime( &t );

	if( opt_day != -1 )
	    break;
	if( opt_month != -1 && tm->tm_mon == opt_month )
	    break;
	if( tm->tm_mon == 0 && tm->tm_mday == 1 )
	    break;
    }
}

static void print_row( int year, int month, int day )
{
    double rise, set, daylen,
	civ_start, civ_end,
        naut_start, naut_end,
        astr_start, astr_end;
    int h, m, s;
    int rs, civ, naut, astr;

    fprintf( stdout, "%d-%02d-%02d",
	     year, month, day );

    if( opt_astronomical_twilight ) {
	astr = astronomical_twilight( year, month, day,
				      opt_longitude, opt_latitude,
				      &astr_start, &astr_end );
	switch( astr ) {
        case 0:
            hh2hms( astr_start + ( opt_offset / 3600 ),
		    &h, &m, &s );
            fprintf( stdout, "%s%02d:%02d:%02d",
		     delimiter, h, m, s );
            break;
        case +1:
            fprintf( stdout, "%s%s",
		     delimiter, opt_out_csv ? "" : "++:++:++" );
            break;
        case -1:
            fprintf( stdout, "%s%s",
		     delimiter, opt_out_csv ? "" : "--:--:--" );
            break;
        }
    }

    if( opt_nautical_twilight ) {
	naut = nautical_twilight( year, month, day,
				  opt_longitude, opt_latitude,
				  &naut_start, &naut_end );
	switch( naut ) {
        case 0:
            hh2hms( naut_start + ( opt_offset / 3600 ),
		    &h, &m, &s );
            fprintf( stdout, "%s%02d:%02d:%02d",
		     delimiter, h, m, s );
            break;
        case +1:
            fprintf( stdout, "%s%s",
		     delimiter, opt_out_csv ? "" : "++:++:++" );
            break;
        case -1:
            fprintf( stdout, "%s%s",
		     delimiter, opt_out_csv ? "" : "--:--:--" );
            break;
        }
    }

    if( opt_civil_twilight ) {
	civ = civil_twilight( year, month, day,
			      opt_longitude, opt_latitude,
			      &civ_start, &civ_end );
	switch( civ ) {
        case 0:
            hh2hms( civ_start + ( opt_offset / 3600 ),
		    &h, &m, &s );
            fprintf( stdout, "%s%02d:%02d:%02d",
		     delimiter, h, m, s );
            break;
        case +1:
            fprintf( stdout, "%s%s",
		     delimiter, opt_out_csv ? "" : "++:++:++" );
            break;
        case -1:
            fprintf( stdout, "%s%s",
		     delimiter, opt_out_csv ? "" : "--:--:--" );
            break;
        }
    }

    rs = sun_rise_set( year, month, day,
		       opt_longitude, opt_latitude,
		       &rise, &set );
    switch( rs ) {
    case 0:
	hh2hms( rise + ( opt_offset / 3600 ), &h, &m, &s );
	fprintf( stdout, "%s%02d:%02d:%02d",
		 delimiter, h, m, s );
	if( opt_noon_time ) {
	    hh2hms( ( rise + set ) / 2. + ( opt_offset / 3600 ),
		    &h, &m, &s );
	    fprintf( stdout, "%s%02d:%02d:%02d",
		     delimiter, h, m, s );
	}
	hh2hms( set + ( opt_offset / 3600 ), &h, &m, &s );
	fprintf( stdout, "%s%02d:%02d:%02d",
		 delimiter, h, m, s );
	break;
    case +1:
	fprintf( stdout, "%s%s",
		 delimiter, opt_out_csv ? "" : "++:++:++" );
	if( opt_noon_time ) {
	    hh2hms( ( rise + set ) / 2 + ( opt_offset / 3600 ),
		    &h, &m, &s );
	    fprintf( stdout, "%s%02d:%02d:%02d",
		     delimiter, h, m, s );
	}
	fprintf( stdout, "%s%s",
		 delimiter, opt_out_csv ? "" : "++:++:++" );
	break;
    case -1:
	fprintf( stdout, "%s%s",
		 delimiter, opt_out_csv ? "" : "--:--:--" );
	if( opt_noon_time ) {
	    hh2hms( ( rise + set ) / 2 + ( opt_offset / 3600 ),
		    &h, &m, &s );
	    fprintf( stdout, "%s%02d:%02d:%02d",
		     delimiter, h, m, s );
	}
	fprintf( stdout, "%s%s",
		 delimiter, opt_out_csv ? "" : "--:--:--" );
	break;
    }

    if( opt_civil_twilight ) {
	switch( civ ) {
        case 0:
            hh2hms( civ_end + ( opt_offset / 3600 ),
		    &h, &m, &s );
            fprintf( stdout, "%s%02d:%02d:%02d",
		     delimiter, h, m, s );
            break;
        case +1:
            fprintf( stdout, "%s%s",
		     delimiter, opt_out_csv ? "" : "++:++:++" );
            break;
        case -1:
            fprintf( stdout, "%s%s",
		     delimiter, opt_out_csv ? "" : "--:--:--" );
            break;
        }
    }

    if( opt_nautical_twilight ) {
	switch( naut ) {
        case 0:
            hh2hms( naut_end + ( opt_offset / 3600 ),
		    &h, &m, &s );
            fprintf( stdout, "%s%02d:%02d:%02d",
		     delimiter, h, m, s );
            break;
        case +1:
            fprintf( stdout, "%s%s",
		     delimiter, opt_out_csv ? "" : "++:++:++" );
            break;
        case -1:
            fprintf( stdout, "%s%s",
		     delimiter, opt_out_csv ? "" : "--:--:--" );
            break;
        }
    }

    if( opt_astronomical_twilight ) {
	switch( astr ) {
        case 0:
            hh2hms( astr_end + ( opt_offset / 3600 ),
		    &h, &m, &s );
            fprintf( stdout, "%s%02d:%02d:%02d",
		     delimiter, h, m, s );
            break;
        case +1:
            fprintf( stdout, "%s%s",
		     delimiter, opt_out_csv ? "" : "++:++:++" );
            break;
        case -1:
            fprintf( stdout, "%s%s",
		     delimiter, opt_out_csv ? "" : "--:--:--" );
            break;
        }
    }

    daylen = day_length( year, month, day,
			 opt_longitude, opt_latitude );
    hh2hms( daylen, &h, &m, &s );
    fprintf( stdout, "%s%02d:%02d:%02d\n",
	     delimiter, h, m, s );
}

static void print_csv_header( void )
{
    if( opt_eot ) {
	fprintf( stdout, "doy,eot\n" );
    } else {
	fprintf( stdout, "data" );

	if( opt_astronomical_twilight )
	    fprintf( stdout, "%sastr_start", delimiter );

	if( opt_nautical_twilight )
	    fprintf( stdout, "%snaut_start", delimiter );

	if( opt_civil_twilight )
	    fprintf( stdout, "%sciv_start", delimiter );

	fprintf( stdout, "%srise", delimiter );

	if( opt_noon_time )
	    fprintf( stdout, "%snoon", delimiter );

	fprintf( stdout, "%sset", delimiter );

	if( opt_civil_twilight )
	    fprintf( stdout, "%sciv_end", delimiter );

	if( opt_nautical_twilight )
	    fprintf( stdout, "%snaut_end", delimiter );

	if( opt_astronomical_twilight )
	    fprintf( stdout, "%sastr_end", delimiter );

	fprintf( stdout, "%sday_length\n", delimiter );
    }
}

static void print_eot( int day )
{
    double e;

    e = get_eot( day );

    // ./srstable -e | graph -T ps -X "day of the year" -Y "minutes" -f 0.02 -g 3 -x 0 365 > eot.ps
    fprintf( stdout, "%d%s%lf\n", day, delimiter, e );
}

static double get_eot( int day )
{
    double a = ( 360. / 365.24 ) * ( day + 10 );
    double b = a + ( 360. / M_PI ) * .0167 *
	sin( 360. / 365.24 * ( day - 2 ) * DEGRAD );
    double c = ( a - RADEG * atan( tan( b * DEGRAD ) / cos( 23.44 * DEGRAD ) ) ) / 180.;
    double e = 720. * ( c - round( c ) );

    return -e;
}


static void hh2hms( double hh, int * h, int * m, int * s )
{
    if( h )
	*h = ( int )hh;
    if( m )
	*m = ( int )( hh * 60 ) % 60;
    if( s )
	*s = ( int )( hh * 3600 ) % 60;
}

static void dd2dms( double dd, int * d, int * m, double * s )
{
    int _d = ( int )dd;
    int _m = ( int )( ( dd - ( double )_d ) * 60. );
    double _s = ( dd - ( double )_d - ( double )_m / 60. ) * 3600.;

    if( d )
	*d = _d;
    if( m )
	*m = _m;
    if( s )
	*s = _s;
}


static const char *usage =
    "srstable v. 0.2\n"
    "\n"
    " usage: srstable <options>"
    "\n"
    "  -h,        --help              - This help\n"
    "\n"
    "  -l <num>,  --latitude=<num>    - latitude (in decimal degrees, + is north)\n"
    "  -L <num>,  --longitude=<num>   - longitude (in decimal degrees, + is east)\n"
    "  -O <num>,  --offset=<num>      - offset from UTC (in seconds)\n"
    "  -Y <num>,  --year=<num>        - set year (default - current)\n"
    "  -M <num>,  --month=<num>       - set month (default - all)\n"
    "  -D <num>,  --day=<num>         - set day (default - all)\n"
    "  -n,        --noon              - print noon time\n"
    "  -C,        --civil             - print civil twilight times\n"
    "  -N,        --nautical          - print nautical twilight times\n"
    "  -A,        --astronomical      - print astronomical twilight times\n"
    "  -e,        --eot               - print Equation of Time\n"
    "  -c,        --csv               - out in CSV format\n";


static int parse_cmdline( int argc, char **argv )
{
    struct option long_options[] = {
        { "help",          no_argument,        0,  'h' },
        { "debug",         no_argument,        0,  'd' },
        { "latitude",      required_argument,  0,  'l' },
        { "longitude",     required_argument,  0,  'L' },
        { "offset",        required_argument,  0,  'O' },
        { "year",          required_argument,  0,  'Y' },
        { "month",         required_argument,  0,  'M' },
        { "day",           required_argument,  0,  'D' },
        { "noon",          no_argument,        0,  'n' },
        { "civil",         no_argument,        0,  'C' },
        { "nautical",      no_argument,        0,  'N' },
        { "astronomical",  no_argument,        0,  'A' },
        { "eot",           no_argument,        0,  'e' },
        { "csv",           no_argument,        0,  'c' },
        { 0,               0,                  0,   0  }
    };
    const char *short_options = "hdl:L:O:Y:M:D:nCNAce";
    int opt = 0, option_index = 0;
    int help = 0, err = 0;

    opterr = 1;
    while( ( opt = getopt_long( argc,
                                argv,
                                short_options,
                                long_options,
                                &option_index ) ) != -1 ) {
        switch( opt ) {
        case 'h':
            help = 1;
            break;
        case 'd':
            opt_debug = 1;
            break;
        case 'l':
	    opt_latitude = atof( optarg );
            break;
        case 'L':
	    opt_longitude = atof( optarg );
            break;
	case 'O':
	    opt_offset = atoi( optarg );
	    break;
	case 'Y':
	    opt_year = atoi( optarg );
	    break;
	case 'M':
	    opt_month = atoi( optarg );
	    break;
	case 'D':
	    opt_day = atoi( optarg );
	    break;
	case 'n':
	    opt_noon_time = 1;
	    break;
	case 'C':
	    opt_civil_twilight = 1;
	    break;
	case 'N':
	    opt_nautical_twilight = 1;
	    break;
	case 'A':
	    opt_astronomical_twilight = 1;
	    break;
	case 'e':
	    opt_eot = 1;
	    break;
	case 'c':
	    opt_out_csv = 1;
	    delimiter = ",";
	    break;
        default:
            err = 1;
            break;
        }
    }

    if( err || help || argc == 1 ) {
        fprintf( stderr, "%s", usage );
        return 0;
    }

    if( optind < argc ) {
        fprintf( stderr, "non-options elements:" );
        while( optind < argc )
            fprintf( stderr, " %s", argv[optind++] );
        fprintf( stderr, "\n\n" );
        fprintf( stderr, "%s", usage );
        return 0;
    }

    return 1;
}

