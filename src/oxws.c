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

mail_account* mail_new_oxws(mail_account* a) {
  a->self.oxws = oxws_new();
  if (a->self.oxws == NULL)
    return NULL;

  a->mail_capabilities = 0; /* MAIL_CAN_SEND | MAIL_CAN_RECEIVE | MAIL_CAN_SEARCH */
  
  a->free = &mail_free_oxws;
  
  a->settings_autodiscover = &mail_settings_autodiscover_oxws;
  a->settings_set = &mail_settings_set_oxws;
  a->connect = &mail_connect_oxws;
  /* a->find = &mail_find_oxws; */

  return a;
}

void mail_free_oxws(mail_account* a, va_list args) {
  if(a == NULL) return;
  oxws_free(a->self.oxws);
}


#define DECLARE_ERROR_CASE(result, error_message) \
  case result: mail_set_error_str(error_message); break;
#define DECLARE_DEFAULT_ERROR_CASE() \
  default: mail_set_error_str("An unknown error occurred."); break;

bool mail_settings_autodiscover_oxws(mail_account* a, va_list args) {
  char *host, *email, *user, *pw, *domain;
  oxws_result result;

  host = va_arg(args, char*);
  email = va_arg(args, char*);
  user = va_arg(args, char*);
  pw = va_arg(args, char*);
  domain = va_arg(args, char*);

  result = oxws_autodiscover_connection_settings(a->self.oxws, host, email, user, pw, domain);
  switch (result) {
    case OXWS_NO_ERROR: return true;

    DECLARE_ERROR_CASE(OXWS_ERROR_INVALID_PARAMETER, "A required parameter is missing, no host or username given, or they cannot be extracted from email_address.");
    DECLARE_ERROR_CASE(OXWS_ERROR_BAD_STATE, "Object is in wrong state. Probably the connection settings have already been configured.");
    DECLARE_ERROR_CASE(OXWS_ERROR_AUTH_FAILED, "The provided credentials are invalid.");
    DECLARE_ERROR_CASE(OXWS_ERROR_AUTODISCOVER_UNAVAILABLE, "Autodiscovering the connection settings failed.");
    DECLARE_DEFAULT_ERROR_CASE();
  }
  return false;
}

bool mail_settings_set_oxws(mail_account* a, va_list args) {
  oxws_connection_settings* settings;
  oxws_result result;

  settings = (oxws_connection_settings*)calloc(sizeof(oxws_connection_settings), 1);
  settings->as_url = va_arg(args, char*);
  settings->oof_url = va_arg(args, char*);
  settings->um_url = va_arg(args, char*);
  settings->oab_url = va_arg(args, char*);

  result = oxws_set_connection_settings(a->self.oxws, settings);
  switch (result) {
    case OXWS_NO_ERROR: return true;
      
    DECLARE_ERROR_CASE(OXWS_ERROR_INVALID_PARAMETER, "A required parameter is missing.");
    DECLARE_ERROR_CASE(OXWS_ERROR_BAD_STATE, "Object is in wrong state. Probably the connection settings have already been configured.");
    DECLARE_DEFAULT_ERROR_CASE();
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
  switch (result) {
    case OXWS_NO_ERROR: return true;
      
    DECLARE_ERROR_CASE(OXWS_ERROR_INVALID_PARAMETER, "A required parameter is missing.");
    DECLARE_ERROR_CASE(OXWS_ERROR_BAD_STATE, "Object is in wrong state. Probably the connection settings have not been configured, or the connection has already been established.");
    DECLARE_ERROR_CASE(OXWS_ERROR_CONNECT, "Failed to connect to the Exchange server using configured connection settings.");
    DECLARE_ERROR_CASE(OXWS_ERROR_AUTH_FAILED, "The provided credentials are invalid.");
    DECLARE_ERROR_CASE(OXWS_ERROR_NO_EWS, "The configured connection settings do not seem to refer to an Exchange server.");
    DECLARE_DEFAULT_ERROR_CASE();
  }
  return false;
}

/* 
 * Local Variables:
 * before-save-hook: copyright-update
 * c-basic-offset: 2
 * End:
 */
