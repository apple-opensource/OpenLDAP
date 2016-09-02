/* bind.c - ldbm backend bind and unbind routines */
/* $OpenLDAP: pkg/ldap/servers/slapd/back-ldbm/sasl.c,v 1.4 2002/01/04 20:17:53 kurt Exp $ */
/*
 * Copyright 1998-2002 The OpenLDAP Foundation, All Rights Reserved.
 * COPYING RESTRICTIONS APPLY, see COPYRIGHT file
 */


#include "portable.h"

#if 0

#include <stdio.h>

#include <ac/krb.h>
#include <ac/socket.h>
#include <ac/string.h>
#include <ac/unistd.h>

#include "slap.h"
#include "back-ldbm.h"
#include "proto-back-ldbm.h"

int
back_ldbm_sasl_authorize(
	BackendDB *be,
	const char *auth_identity,
	const char *requested_user,
	const char **user,
	const char **errstring)
{
	return SASL_FAIL;
}

int
back_ldbm_sasl_getsecret(
	Backend *be,
	const char *mechanism,
	const char *auth_identity,
	const char *realm,
	sasl_secret_t **secret)
{
	return SASL_FAIL;
}

int
back_ldbm_sasl_putsecret(
	Backend *be,
	const char *mechanism,
	const char *auth_identity,
	const char *realm,
	const sasl_secret_t *secret)
{
	return SASL_FAIL;
}

#else
static int dummy = 1;
#endif

