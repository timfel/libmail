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

#ifndef LIBMAIL_OXWS_H
#define LIBMAIL_OXWS_H

#include "mail_types.h"

mail_account* mail_new_oxws(mail_account* a);
void mail_free_oxws(mail_account* a, va_list args);

bool mail_settings_autodiscover_oxws(mail_account* a, va_list args);
bool mail_settings_set_oxws(mail_account* a, va_list args);
bool mail_connect_oxws(mail_account* a, va_list args);

#endif

/* 
 * Local Variables:
 * before-save-hook: copyright-update
 * c-basic-offset: 2
 * End:
 */
