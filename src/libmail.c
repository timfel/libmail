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

#include "libmail.h"

mail_account* mail_new(enum mail_type x) {
  mail_account* em = (mail_account*)calloc(sizeof(mail_account), 1);
  if (em == NULL) {
    return NULL;
  }

  switch(x) {
  case OXWS: return mail_new_oxws(em);
  default: return NULL;
  }
}

bool mail_discover_settings(mail_account* a, ...) {
  va_list args;
  va_start(args, a);
  int error_code = a->settings_autodiscover(a, args);
  va_end(args);

  if (error_code) {
    mail_errno = error_code;
    return false;
  }
  return true;
}

/* 
 * Local Variables:
 * before-save-hook: copyright-update
 * c-basic-offset: 2
 * End:
 */
