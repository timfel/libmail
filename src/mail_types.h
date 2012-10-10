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

#ifndef LIBMAIL_MAIL_TYPES_H
#define LIBMAIL_MAIL_TYPES_H

//#include "config.h"
#include "stdbool.h"
#include "stdarg.h"
#include "string.h"
#include <libetpan/libetpan.h>

enum mail_type {
  POP3,
  IMAP,
  SMTP,
  OXWS
};

enum mail_capabilities {
  MAIL_CAN_SEND,
  MAIL_CAN_RECEIVE,
  MAIL_CAN_SEARCH = 0x4
};

typedef struct _mail_account {
  union {
    oxws* oxws;
    mailimap* imap;
    mailpop3* pop3;
    mailsmtp* smtp;
  } self;

  int mail_capabilities;
  bool (*settings_autodiscover)(struct _mail_account*, va_list);
  bool (*settings_set)(struct _mail_account*, va_list);
  bool (*connect)(struct _mail_account*, va_list);
  bool (*find)(struct _mail_account*, va_list);
} mail_account;

static char* mail_errno = NULL;
static void mail_set_error_str(char* msg) {
  if(mail_errno == msg) return;

  free(mail_errno);
  mail_errno = NULL;

  if(msg != NULL) {
    mail_errno = (char*)calloc(strlen(msg) + 1, sizeof(char));
    strcpy(mail_errno, msg);
  }
}

#endif

/*
 * Local Variables:
 * before-save-hook: copyright-update
 * c-basic-offset: 2
 * End:
 */
