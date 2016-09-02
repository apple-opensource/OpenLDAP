/* charray.c - routines for dealing with char * arrays */
/* $OpenLDAP: pkg/ldap/servers/slapd/charray.c,v 1.29.2.1 2002/02/23 22:08:04 kurt Exp $ */
/*
 * Copyright 1998-2002 The OpenLDAP Foundation, All Rights Reserved.
 * COPYING RESTRICTIONS APPLY, see COPYRIGHT file
 */

#include "portable.h"

#include <stdio.h>

#include <ac/string.h>
#include <ac/socket.h>

#include "slap.h"

void
charray_add(
    char	***a,
    const char	*s
)
{
	int	n;

	if ( *a == NULL ) {
		*a = (char **) ch_malloc( 2 * sizeof(char *) );
		n = 0;
	} else {
		for ( n = 0; *a != NULL && (*a)[n] != NULL; n++ ) {
			;	/* NULL */
		}

		*a = (char **) ch_realloc( (char *) *a,
		    (n + 2) * sizeof(char *) );
	}

	(*a)[n++] = ch_strdup(s);
	(*a)[n] = NULL;
}

void
charray_add_n(
    char	***a,
    const char	*s,
    int         l
)
{
	int	n;

	if ( *a == NULL ) {
		*a = (char **) ch_malloc( 2 * sizeof(char *) );
		n = 0;
	} else {
		for ( n = 0; *a != NULL && (*a)[n] != NULL; n++ ) {
			;	/* NULL */
		}

		*a = (char **) ch_realloc( (char *) *a,
		    (n + 2) * sizeof(char *) );
	}

	(*a)[n] = (char *) ch_malloc( ( l + 1 ) * sizeof( char ) );
	strncpy( (*a)[n], s, l );
	(*a)[n][l] = '\0';
	(*a)[++n] = NULL;
}

void
charray_merge(
    char	***a,
    char	**s
)
{
	int	i, n, nn;

	for ( n = 0; *a != NULL && (*a)[n] != NULL; n++ ) {
		;	/* NULL */
	}
	for ( nn = 0; s[nn] != NULL; nn++ ) {
		;	/* NULL */
	}

	*a = (char **) ch_realloc( (char *) *a, (n + nn + 1) * sizeof(char *) );

	for ( i = 0; i < nn; i++ ) {
		(*a)[n + i] = ch_strdup(s[i]);
	}
	(*a)[n + nn] = NULL;
}

void
charray_free( char **array )
{
	char	**a;

	if ( array == NULL ) {
		return;
	}

	for ( a = array; *a != NULL; a++ ) {
		if ( *a != NULL ) {
			free( *a );
		}
	}
	free( (char *) array );
}

int
charray_inlist(
    char	**a,
    const char	*s
)
{
	int	i;

	if( a == NULL ) return 0;

	for ( i = 0; a[i] != NULL; i++ ) {
		if ( strcasecmp( s, a[i] ) == 0 ) {
			return( 1 );
		}
	}

	return( 0 );
}

char **
charray_dup( char **a )
{
	int	i;
	char	**new;

	for ( i = 0; a[i] != NULL; i++ )
		;	/* NULL */

	new = (char **) ch_malloc( (i + 1) * sizeof(char *) );

	for ( i = 0; a[i] != NULL; i++ ) {
		new[i] = ch_strdup( a[i] );
	}
	new[i] = NULL;

	return( new );
}


char **
str2charray( const char *str_in, const char *brkstr )
{
	char	*str;
	char	**res;
	char	*s;
	char	*lasts;
	int	i;

	/* protect the input string from strtok */
	str = ch_strdup( str_in );

	i = 1;
	for ( s = str; *s; s++ ) {
		if ( strchr( brkstr, *s ) != NULL ) {
			i++;
		}
	}

	res = (char **) ch_malloc( (i + 1) * sizeof(char *) );
	i = 0;

	for ( s = ldap_pvt_strtok( str, brkstr, &lasts );
		s != NULL;
		s = ldap_pvt_strtok( NULL, brkstr, &lasts ) )
	{
		res[i++] = ch_strdup( s );
	}

	res[i] = NULL;

	free( str );
	return( res );
}

int
charray_strcmp( const char **a1, const char **a2 )
{
	for ( ; a1[0] && a2[0]; a1++, a2++ ) {
		if ( strcmp( a1[0], a2[0] ) ) {
			return( !0 );
		}
	}

	if ( a1[0] || a2[0] ) {
		return( !0 );
	}

	return 0;
}


int
charray_strcasecmp( const char **a1, const char **a2 )
{
	for ( ; a1[0] && a2[0]; a1++, a2++ ) {
		if ( strcasecmp( a1[0], a2[0] ) ) {
			return( !0 );
		}
	}

	if ( a1[0] || a2[0] ) {
		return( !0 );
	}

	return 0;
}

/* strcopy is like strcpy except it returns a pointer to the trailing NUL of
 * the result string. This allows fast construction of catenated strings
 * without the overhead of strlen/strcat.
 */
char *
slap_strcopy(
	char *a,
	const char *b
)
{
	if (!a || !b)
		return a;
	
	while (*a++ = *b++) ;
	return a-1;
}

/* strncopy is like strcpy except it returns a pointer to the trailing NUL of
 * the result string. This allows fast construction of catenated strings
 * without the overhead of strlen/strcat.
 */
char *
slap_strncopy(
	char *a,
	const char *b,
	size_t n
)
{
	if (!a || !b || n == 0)
		return a;
	
	while ((*a++ = *b++) && n-- > 0) ;
	return a-1;
}