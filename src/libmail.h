/* 
 * Copyright (C) 2012 by Tim Felgentreff
 * 
 * This file is part of libmail.
 * 
 * libmail is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.  libmail is distributed in the
 * hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU Lesser General Public License for more details.
 * You should have received a copy of the GNU Lesser General Public
 * License along with libmail.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LIBMAIL_H
#define LIBMAIL_H

#include "mail_types.h"
#include "oxws.h"

#if defined(__WIN32__) || defined(__MINGW32__)
# define DLLImport __declspec(dllimport)
#else
# define DLLImport
#endif

DLLImport mail_account* mail_new(enum mail_type x);

#endif
