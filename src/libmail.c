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

char* mail_get_error_str() {
  if (!mail_errno) {
    return NULL;
  } else {
    char* cpy = (char*)calloc(strlen(mail_errno) + 1, sizeof(char));
    strcpy(cpy, mail_errno);
    printf("%s -> %s\n", mail_errno, cpy);
    return cpy;
  }
}

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

#define WRAP_FUNCTION(FUNC_NAME, METHOD_NAME) \
  bool FUNC_NAME(mail_account* a, ...) { \
    if (a->METHOD_NAME == NULL) { \
      mail_set_error_str("Internal error: pure virtual function call."); \
      return false; \
    } \
    \
    va_list args; \
    va_start(args, a); \
    bool result = a->METHOD_NAME(a, args); \
    va_end(args); \
    return result; \
  }

WRAP_FUNCTION(mail_discover_settings, settings_autodiscover)
WRAP_FUNCTION(mail_set_settings, settings_set)
WRAP_FUNCTION(mail_connect, connect)

/* 
 * Local Variables:
 * before-save-hook: copyright-update
 * c-basic-offset: 2
 * End:
 */
