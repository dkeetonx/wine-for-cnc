/*
 * Copyright 2008 Juan Lang
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */
#ifndef __CRYPTUIRES_H_
#define __CRYPTUIRES_H_

#define IDS_CERTIFICATE 1000
#define IDS_CERTIFICATEINFORMATION 1001
#define IDS_CERT_INFO_BAD_SIG 1002
#define IDS_CERT_INFO_UNTRUSTED_CA 1003
#define IDS_CERT_INFO_UNTRUSTED_ROOT 1004
#define IDS_CERT_INFO_PARTIAL_CHAIN 1005
#define IDS_CERT_INFO_BAD_PURPOSES 1006
#define IDS_CERT_INFO_PURPOSES 1007

#define IDS_SUBJECT_HEADING 1010
#define IDS_ISSUER_HEADING 1011
#define IDS_VALID_FROM 1012
#define IDS_VALID_TO 1013

#define IDS_PURPOSE_SERVER_AUTH 1100
#define IDS_PURPOSE_CLIENT_AUTH 1101
#define IDS_PURPOSE_CODE_SIGNING 1102
#define IDS_PURPOSE_EMAIL_PROTECTION 1103
#define IDS_PURPOSE_IPSEC 1104
#define IDS_PURPOSE_TIMESTAMP_SIGNING 1105
#define IDS_PURPOSE_CTL_USAGE_SIGNING 1106
#define IDS_PURPOSE_EFS 1107
#define IDS_PURPOSE_EFS_RECOVERY 1108
#define IDS_PURPOSE_WHQL 1109
#define IDS_PURPOSE_NT5 1110
#define IDS_PURPOSE_OEM_WHQL 1111
#define IDS_PURPOSE_EMBEDDED_NT 1112
#define IDS_PURPOSE_ROOT_LIST_SIGNER 1113
#define IDS_PURPOSE_QUALIFIED_SUBORDINATION 1114
#define IDS_PURPOSE_KEY_RECOVERY 1115
#define IDS_PURPOSE_DOCUMENT_SIGNING 1116
#define IDS_PURPOSE_LIFETIME_SIGNING 1117
#define IDS_PURPOSE_DRM 1118
#define IDS_PURPOSE_LICENSES 1119
#define IDS_PURPOSE_LICENSE_SERVER 1120
#define IDS_PURPOSE_ENROLLMENT_AGENT 1121
#define IDS_PURPOSE_SMARTCARD_LOGON 1122
#define IDS_PURPOSE_CA_EXCHANGE 1123
#define IDS_PURPOSE_KEY_RECOVERY_AGENT 1124
#define IDS_PURPOSE_DS_EMAIL_REPLICATION 1125

#define IDD_GENERAL 100
#define IDD_DETAIL 101
#define IDD_USERNOTICE 103

#define IDB_CERT 201
#define IDB_CERT_ERROR 202
#define IDB_CERT_WARNING 203
#define IDB_CHECKS 204

#define IDC_STATIC 2000
#define IDC_CERTIFICATE_ICON 2001
#define IDC_CERTIFICATE_INFO 2002
#define IDC_CERTIFICATE_STATUS 2003
#define IDC_CERTIFICATE_NAMES 2004
#define IDC_ADDTOSTORE 2005
#define IDC_ISSUERSTATEMENT 2006

#define IDC_DETAIL_SELECT 2100
#define IDC_DETAIL_LIST 2101
#define IDC_DETAIL_VALUE 2102
#define IDC_EDITPROPERTIES 2103
#define IDC_EXPORT 2104

#define IDC_USERNOTICE 2300
#define IDC_CPS 2301

#endif /* ndef __CRYPTUIRES_H_ */
