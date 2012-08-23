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
  em->settings_set = &mail_settings_set_oxws;
  em->connect = &mail_connect_oxws;
  /* em->find = &mail_find_oxws; */
  return em;
}

bool mail_settings_autodiscover_oxws(mail_account* a, va_list args) {
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

  result = oxws_autodiscover_connection_settings(a->self.oxws, url, mail, user, pw, domain);

  switch (result) {
  case OXWS_NO_ERROR:
    return true;
  case OXWS_ERROR_INVALID_PARAMETER:
    mail_set_error_str("a required parameter is missing, no host given, or host cannot be extracted from email_address");
    break;
  case OXWS_ERROR_AUTODISCOVER_UNAVAILABLE:
    mail_set_error_str("autodiscovering the connection settings failed");
    break;
  default:
    mail_set_error_str ("an unknown error occurred");
  }
  return false;
}

bool mail_settings_set_oxws(mail_account* a, va_list args) {
  char* url;
  oxws_connection_settings* settings;
  oxws_result result;

  settings = (oxws_connection_settings*)calloc(sizeof(oxws_connection_settings), 1);

  url = va_arg(args, char*);
  if (url) settings->as_url = url;
  url = va_arg(args, char*);
  if (url) settings->oof_url = url;
  url = va_arg(args, char*);
  if (url) settings->um_url = url;
  url = va_arg(args, char*);
  if (url) settings->oab_url = url;

  result = oxws_set_connection_settings(a->self.oxws, settings);
  switch (result) {
  case OXWS_NO_ERROR:
    return true;
  case OXWS_ERROR_INVALID_PARAMETER:
    mail_set_error_str("a required parameter is missing");
    break;
  case OXWS_ERROR_BAD_STATE:
    mail_set_error_str("state is not OXWS_STATE_NEW");
    break;
  default:
    mail_set_error_str("internal, undefined error");
  }
  return false;
}

bool mail_connect_oxws(mail_account* a, va_list args) {
  char *user, *pw, *domain;
  oxws_result result;

  user = va_arg(args, char*);
  pw = va_arg(args, char*);
  domain = va_arg(args, char*);

  result = oxws_connect(a->self.oxws, user, pw, domain);
  if (result != OXWS_NO_ERROR) return false;
  return true;
}

/* 
 * Local Variables:
 * before-save-hook: copyright-update
 * c-basic-offset: 2
 * End:
 */
