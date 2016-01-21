/*
* Copyright © 2016 Pope Kim
*
* This library is free software; you can redistribute it and/or
* modify it either under the terms of the GNU Lesser General Public
* License version 2.1 as published by the Free Software Foundation
* (the "LGPL") or, at your option, under the terms of the Mozilla
* Public License Version 1.1 (the "MPL"). If you do not alter this
* notice, a recipient may use your version of this file under either
* the MPL or the LGPL.
*
* You should have received a copy of the LGPL along with this library
* in the file COPYING-LGPL-2.1; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Suite 500, Boston, MA 02110-1335, USA
* You should have received a copy of the MPL along with this library
* in the file COPYING-MPL-1.1
*
* The contents of this file are subject to the Mozilla Public License
* Version 1.1 (the "License"); you may not use this file except in
* compliance with the License. You may obtain a copy of the License at
* http://www.mozilla.org/MPL/
*
* This software is distributed on an "AS IS" basis, WITHOUT WARRANTY
* OF ANY KIND, either express or implied. See the LGPL or the MPL for
* the specific language governing rights and limitations.
*
* Contributor(s):
*  Pope Kim <popekim@gmail.com>
*/
#include "cairoint.h"

#include "cairo-membuffer.h"


const cairo_membuffer_t _cairo_membuffer_nil = {
	NULL, /* buffer */
	0, /* length */
	0, /* position */
};

cairo_status_t cairo_membuffer_write(void *closure, const unsigned char *data, unsigned int length) {
	cairo_membuffer_t* buffer = (cairo_membuffer_t*)closure;
	if (length > buffer->length - buffer->position) {
		void* newmem = realloc(buffer->data, buffer->length * 2);
		if (unlikely(newmem == 0)) {
			_cairo_error_throw(CAIRO_STATUS_NO_MEMORY);
			return CAIRO_STATUS_NO_MEMORY;
		}
		buffer->data = newmem;
		buffer->length *= 2;
	}

	memcpy(buffer->data + buffer->position, data, length);
	buffer->position += length;

	return CAIRO_STATUS_SUCCESS;
}

cairo_membuffer_t * cairo_membuffer_create(unsigned int initial_size)
{
	cairo_membuffer_t* membuffer = malloc(sizeof(cairo_membuffer_t));
	if (unlikely(membuffer == NULL)) {
		_cairo_error_throw(CAIRO_STATUS_NO_MEMORY);
		return (cairo_membuffer_t *)&_cairo_membuffer_nil;
	}

	membuffer->position = 0;
	membuffer->data = malloc(initial_size);
	if (unlikely(membuffer == NULL)) {
		_cairo_error_throw(CAIRO_STATUS_NO_MEMORY);
		membuffer->length = 0;
	}
	else {
		membuffer->length = initial_size;
	}

	return membuffer;
}

void cairo_membuffer_destroy(cairo_membuffer_t* buffer) {
	free(buffer->data);
	buffer->data = NULL;
	free(buffer);
}

unsigned int cairo_membuffer_used(cairo_membuffer_t* buffer) {
	return buffer->position;
}

void* cairo_membuffer_data(cairo_membuffer_t* buffer) {
	return buffer->data;
}

