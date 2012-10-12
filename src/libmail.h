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
# define DLLImport __declspec(dllexport)
#else
# define DLLImport
#endif


DLLImport char* mail_get_error_str();

DLLImport mail_account* mail_new(enum mail_type x);
DLLImport void mail_free(mail_account* x, ...);

DLLImport bool mail_discover_settings(mail_account* x, ...);
DLLImport bool mail_set_settings(mail_account* x, ...);
DLLImport bool mail_connect(mail_account* x, ...);


#endif

/* 
 * Local Variables:
 * before-save-hook: copyright-update
 * c-basic-offset: 2
 * End:
 */
