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

#include "imap.h"

mail_account* mail_new_imap(mail_account* em) {
  em->self.imap = mailimap_new(0, NULL);
  if (em->self.imap == NULL)
    return NULL;
  
  em->mail_capabilities = 0; /* MAIL_CAN_SEND | MAIL_CAN_RECEIVE | MAIL_CAN_SEARCH */
  em->connect = &mail_connect_imap;
  
  return em;
}

bool mail_connect_imap(mail_account* a, va_list args) {
  char *host, *user, *pw; uint16_t port;
  int result;
  
  host = va_arg(args, char*);
  port = (uint16_t) va_arg(args, uint);
  user = va_arg(args, char*);
  pw = va_arg(args, char*);
  
  result = mailimap_ssl_connect(a->self.imap, host, port);
  switch (result) {
    case MAILIMAP_NO_ERROR:
    case MAILIMAP_NO_ERROR_AUTHENTICATED:
    case MAILIMAP_NO_ERROR_NON_AUTHENTICATED:
      break;
      
    default:
      /* TODO handle other return values */
      return false;
  }
  
  result = mailimap_login(a->self.imap, user, pw);
  switch (result) {
    case MAILIMAP_NO_ERROR:
    case MAILIMAP_NO_ERROR_AUTHENTICATED:
    case MAILIMAP_NO_ERROR_NON_AUTHENTICATED:
      return true;
      
    default:
      /* TODO handle other return values */
      return false;
  }
}

/*
 * Local Variables:
 * before-save-hook: copyright-update
 * c-basic-offset: 2
 * End:
 */
