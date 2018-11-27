/*
 * Copyright (c) 2016, Citrix Systems, Inc.
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *  3. Neither the name of the copyright holder nor the names of its 
 *     contributors may be used to endorse or promote products derived from 
 *     this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <libgen.h>
#include <iconv.h>
#include <limits.h>
#include <syslog.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>

int 
main()
{
	char name[] = "u.vhd";

	iconv_t cd;
	int len, err;
	size_t ibl, obl;
	char *uri, *urip, *uri_utf8, *uri_utf8p, *ret;

	err     = 0;
	ret     = NULL;
	len     = strlen(name) + strlen("file://");

	ibl     = len;
	obl     = len;

	uri = urip = malloc(ibl + 1);
	uri_utf8 = uri_utf8p = malloc(obl);

	if (!uri || !uri_utf8)
		return -ENOMEM;

	cd = iconv_open("UTF-8", "ASCII");
	if (cd == (iconv_t)-1) {
		err = -errno;
		goto out;
	}

	sprintf(uri, "file://%s", name);

	if (iconv(cd, &urip, &ibl, &uri_utf8p, &obl) == (size_t)-1 ||
	    ibl || obl) {
		err = (errno ? -errno : -EIO);
		goto out;
	}

	ret = malloc(len);
	if (!ret) {
		err = -ENOMEM;
		goto out;
	}

	memcpy(ret, uri_utf8, len);

 out:
	free(uri);
	free(uri_utf8);
	if (cd != (iconv_t)-1)
		iconv_close(cd);

	return err;
}
