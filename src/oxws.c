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

#include "oxws.h"

mail_account* mail_new_oxws(mail_account* em) {
  em->self.oxws = oxws_new();
  if (em->self.oxws == NULL) {
    return NULL;
  }

  em->mail_capabilities = MAIL_CAN_SEND | MAIL_CAN_SEND | MAIL_CAN_SEARCH;
  em->settings_autodiscover = &mail_settings_autodiscover_oxws;
  /* 
   * em->settings_set = &mail_settings_set_oxws;
   * em->connect = &mail_connect_oxws;
   * em->find = &mail_find_oxws;
   */
  return em;
}

bool mail_settings_autodiscover_oxws(mail_account* self, va_list args) {
  char *url, *mail, *user, *pw, *domain;
  oxws_result result;

  url = va_arg(args, char*);
  if (!url) return false;
  mail = va_arg(args, char*);
  if (!mail) return false;
  user = va_arg(args, char*);
  if (!user) return false;
  pw = va_arg(args, char*);
  if (!pw) return false;
  domain = va_arg(args, char*);

  result = oxws_autodiscover_connection_settings((oxws*)self, url, mail, user, pw, domain);
  if (result != OXWS_NO_ERROR) return false;
}
