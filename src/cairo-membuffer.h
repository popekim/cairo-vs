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

#ifndef CAIRO_MEMBUFFER_H
#define CAIRO_MEMBUFFER_H

#include "cairo.h"

struct _cairo_membuffer {
	char* data;
	unsigned int length;
	unsigned int position;
};

typedef struct _cairo_membuffer cairo_membuffer_t;

cairo_public cairo_status_t cairo_membuffer_write(void *closure, const unsigned char *data, unsigned int length);

cairo_public cairo_membuffer_t * cairo_membuffer_create(unsigned int initial_size);
cairo_public void cairo_membuffer_destroy(cairo_membuffer_t* buffer);

cairo_public unsigned int cairo_membuffer_used(cairo_membuffer_t* buffer);
cairo_public void* cairo_membuffer_data(cairo_membuffer_t* buffer);

#endif