#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( int argc, char *argv[] )
{
    char s[4];
    scanf( "%s", s );
    if( ! strcmp( s, "RRR" ) ) {
        puts( "3" ); exit( 0 );
    } else if( ! strcmp( s, "RRS" ) ) {
        puts( "2" ); exit( 0 );
    } else if( ! strcmp( s, "RSR" ) ) {
        puts( "1" ); exit( 0 );
    } else if( ! strcmp( s, "RSS" ) ) {
        puts( "1" ); exit( 0 );
    } else if( ! strcmp( s, "SSS" ) ) {
        puts( "0" ); exit( 0 );
    } else if( ! strcmp( s, "SSR" ) ) {
        puts( "1" ); exit( 0 );
    } else if( ! strcmp( s, "SRS" ) ) {
        puts( "1" ); exit( 0 );
    } else if( ! strcmp( s, "SRR" ) ) {
        puts( "2" ); exit( 0 );
    }
    puts( "0" );
}
