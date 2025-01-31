#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
/* Copyright (C) 1991-2024 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 10.0.0.  Version 10.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2017, fifth edition, plus
   the following additions from Amendment 1 to the fifth edition:
   - 56 emoji characters
   - 285 hentaigana
   - 3 additional Zanabazar Square characters */
/**
 * Dependencies
 */
/**
 * url.h version
 */
/**
 * Max length of a url protocol scheme
 */
/**
 * Max length of a url host part
 */
/**
 * Max length of a url tld part
 */
/**
 * Max length of a url auth part
 */
struct url_key_value;
/**
 * `url_data` struct that defines parts
 * of a parsed URL such as host and protocol
 */
typedef struct url_data {
  char* whole_url; // holds the whole URL, but with '\0' to separae the parts of the URL
  const char* protocol; // URL scheme
  const char* userinfo; // can be NULL
  const char* host;
  const char* port; // can be NULL
  const char* path;
  const struct url_key_value* query; // can be NULL
  const char* fragment; // can be NULL
} url_data_t;
// prototype
/**
 * Parses a url into parts and returns
 * a `url_data_t *` pointer
 */
url_data_t *
url_parse (const char* url);
// Parses url, returns the "scheme" (a.k.a. "protocol") of the URL.
// Caller must free() the returned string.
char *
url_get_scheme (const char* url);
// Parses url, returns the protocol (a.k.a. URL "scheme") of the URL.
// Caller must free() the returned string.
// DEPRECATED! Use url_get_scheme() instead.
inline
char *
url_get_protocol (const char* url) { return url_get_scheme(url); }
// Parses url, returns "username:password" of the URL if present or NULL.
// Caller must free() the returned string if not NULL.
char *
url_get_userinfo (const char* url);
// Parses url, returns the hostname of the URL.
// Caller must free() the returned string.
char *
url_get_hostname (const char* url);
// Parses url, returns the path of the URL.
// Caller must free() the returned string.
char *
url_get_path (const char* url);
// returns the value for the URL query key, if present.
// returns NULL if URL query does not contain this key.
// value belongs to url, caller MUST NOT free() the string!
const char *
url_get_query_value (const url_data_t* url, const char* key);
// Parses url, returns the fragment (after the "#") of the URL if present or NULL.
// Caller must free() the returned string if not NULL.
char *
url_get_fragment (const char* url);
// Parses url, returns the fragment (after the "#") of the URL if present or NULL.
// Caller must free() the returned string if not NULL.
// DEPRECATED! Use url_get_fragment() instead.
inline
char *
url_get_hash (const char* url) { return url_get_fragment(url); }
// Parses url, returns the port of the URL if present or NULL.
// Caller must free() the returned string if not NULL.
char *
url_get_port (const char* url);
// Frees the data and its members appropiately.
void
url_free (url_data_t* data);
// Returns 'true' if the str is the name of a well-known URL scheme.
bool
url_is_protocol (const char* str);
// Returns 'true' if the string is "ssh" or "git"
bool
url_is_ssh (const char* str);
// Parses the URL and prints its members to stdout.
void
url_inspect (const char* url);
// Prints the members to stdout.
void
url_data_inspect (const url_data_t* data);
enum Category
{
  Scheme = 0x01, // alnum + - .
  Unreserved = 0x02, // alnum - . _ ~
  GenDelim = 0x04, // alnum : / ? # [ ] @
  SubDelim = 0x08, // alnum ! $ & ' ( ) * + , ; =
  PCharSlash = 0x10, // alnum unreserved subdelim : @ /
  HexDigit = 0x20, // 0-9 a-f A-F
  Query = 0x40, // pchar / ?
  Fragment = 0x40, // same as Query :-)
  Userinfo = 0x80, // alnum unreserved subdelim :
  IPv6Char = 0x100, // hexdigit :
};
// This file is generated by gen_char_category_table. DO NOT EDIT IT BY HAND!
static const unsigned short char_cat[256] = {
//   .0     .1     .2     .3     .4     .5     .6     .7     .8     .9     .A     .B     .C     .D     .E     .F
  0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, // 00 ... 0F
  0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, // 10 ... 1F
  0x000, 0x0d8, 0x000, 0x004, 0x0d8, 0x0d0, 0x0d8, 0x0d8, 0x0d8, 0x0d8, 0x0d8, 0x0d9, 0x0d8, 0x0d3, 0x0d3, 0x054, // 20 ... 2F
  0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1d4, 0x0d8, 0x000, 0x0d8, 0x000, 0x044, // 30 ... 3F
  0x054, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, // 40 ... 4F
  0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x004, 0x000, 0x004, 0x000, 0x0d2, // 50 ... 5F
  0x000, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, // 60 ... 6F
  0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x000, 0x000, 0x000, 0x0d2, 0x000, // 70 ... 7F
  0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, // 80 ... 8F
  0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, // 90 ... 9F
  0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, // A0 ... AF
  0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, // B0 ... BF
  0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, // C0 ... CF
  0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, // D0 ... DF
  0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, // E0 ... EF
  0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000 // F0 ... FF
};
/**
 * URI Schemes
 * http://en.wikipedia.org/wiki/URI_scheme
 */
static const char *URL_SCHEMES[] = {
  // official IANA registered schemes
  "aaa", "aaas", "about", "acap", "acct", "adiumxtra", "afp", "afs", "aim", "apt", "attachment", "aw",
  "beshare", "bitcoin", "bolo", "callto", "cap", "chrome", "crome-extension", "com-evenbrite-attendee",
  "cid", "coap", "coaps","content", "crid", "cvs", "data", "dav", "dict", "lna-playsingle", "dln-playcontainer",
  "dns", "dtn", "dvb", "ed2k", "facetime", "fax", "feed", "file", "finger", "fish","ftp", "geo", "gg","git",
  "gizmoproject", "go", "gopher", "gtalk", "h323", "hcp", "http", "https", "iax", "icap", "icon","im",
  "imap", "info", "ipn", "ipp", "irc", "irc6", "ircs", "iris", "iris.beep", "iris.xpc", "iris.xpcs","iris.lws",
  "itms", "jabber", "jar", "jms", "keyparc", "lastfm", "ldap", "ldaps", "magnet", "mailserver","mailto",
  "maps", "market", "message", "mid", "mms", "modem", "ms-help", "mssettings-power", "msnim", "msrp",
  "msrps", "mtqp", "mumble", "mupdate", "mvn", "news", "nfs", "ni", "nih", "nntp", "notes","oid",
  "paquelocktoken", "pack", "palm", "paparazzi", "pkcs11", "platform", "pop", "pres", "prospero", "proxy",
  "psyc","query", "reload", "res", "resource", "rmi", "rsync", "rtmp","rtsp", "secondlife", "service","session",
  "sftp", "sgn", "shttp", "sieve", "sip", "sips", "skype", "smb", "sms", "snews", "snmp", "soap.beep","soap.beeps",
  "soldat", "spotify", "ssh", "steam", "svn", "tag", "teamspeak", "tel", "telnet", "tftp", "things","thismessage",
  "tn3270", "tip", "tv", "udp", "unreal", "urn", "ut2004", "vemmi","ventrilo", "videotex", "view-source", "wais","webcal",
  "ws", "wss", "wtai", "wyciwyg", "xcon", "xcon-userid", "xfire","xmlrpc.beep", "xmlrpc.beeps", "xmpp", "xri","ymsgr",
  // unofficial schemes
  "javascript", "jdbc", "doi"
};
// non C99 standard functions
char *
strdup (const char *str) {
  const int n = strlen(str) + 1;
  char *dup = (char *) malloc(n);
  if (dup) strcpy(dup, str);
  return dup;
}
struct url_key_value
{
  const char* key;
  const char* value;
};
static
int unhex(const char* s)
{
  if(*s>='0' && *s<='9')
    return *s - '0';
  if(*s>='A' && *s<='F')
    return *s - 'A' + 10;
  if(*s>='a' && *s<='f')
    return *s - 'a' + 10;
  return -1;
}
// decode %xx encoding inplace.
// return NULL in case of error
static
char* decode_percent(char* s)
{
  char* in = s;
  char* out = s;
  while(*in)
  {
    if(*in=='%')
    {
      const int high = unhex(++in); if(high<0 || *in=='\0') return NULL;
      const int low = unhex(++in); if(low <0 || *in=='\0') return NULL;
      *out = (char)(high*16u + low);
      ++out;
      ++in;
    }else{
      *out++ = *in++; // usual string copy idiom. :-)
    }
  }
  *out = '\0';
  return s;
}
static
char*
scan_part(char* start, enum Category category, char delimiter1, char delimiter2) {
  char* p = start;
  for(;;)
  {
    if( *p=='\0' || *p==delimiter1 || *p==delimiter2)
       return p; // success! :-)
    if(char_cat[ (unsigned char) *p ] & category) {
      ++p;
    }else{
      return NULL; // illegal character in URL string -> Abort!
    }
  }
}
static
char*
scan_decimal_number(char* start)
{
  char* p = start;
  while(*p >='0' && *p<='9')
  {
    ++p;
  }
  return (p!=start) ? p : NULL;
}
static
struct url_key_value* parse_query_string(char* begin, char* end)
{
  unsigned elements = 1; // each query has at least 1 element,
  for(const char* p = begin; p!=end; ++p)
  {
    if(*p=='&' || *p==';')
      ++elements;
  }
  struct url_key_value* kv = calloc(elements+1, sizeof(struct url_key_value)); // add one {NULL,NULL} element as array terminator.
  if(!kv)
    return NULL;
  char* p = begin;
  for(unsigned element=0; (element<=elements) && (p<end); ++element)
  {
    char* key = p;
    char* kv_end = scan_part(p, Query, '&', ';');
    if(!kv_end)
      do{ fprintf(stderr, "ERROR %s Line %u! p=«%s»\n", "/tmp/expand_macro/url.c", 337 , p); goto error; }while(0);
    *kv_end = '\0';
    char* key_end = scan_part(p, Query, '=', '\0');
    const bool has_value = (*key_end == '=');
    *key_end = '\0';
    kv[element].key = decode_percent(key);
    if(has_value) // real key-value pair
    {
      char* value = key_end+1;
      kv[element].value = decode_percent(value);
    }else{
      kv[element].value = key_end;
    }
    p = kv_end+1;
  }
  return kv;
error:
  free(kv);
  return NULL;
}
url_data_t*
url_parse (const char* url) {
  url_data_t *data = (url_data_t *) calloc(1, sizeof(url_data_t));
  if (!data) return NULL;
  char* p = strdup(url);
  if(!p)
    do{ fprintf(stderr, "ERROR %s Line %u! p=«%s»\n", "/tmp/expand_macro/url.c", 374 , p); goto error; }while(0);
  data->whole_url = p;
  const char* const p_end = p + strlen(p);
  char* protocol_end = scan_part(p, Scheme, ':', '\0');
  if (!protocol_end || *protocol_end=='\0')
    do{ fprintf(stderr, "ERROR %s Line %u! p=«%s»\n", "/tmp/expand_macro/url.c", 381 , p); goto error; }while(0);
  *protocol_end = '\0';
  data->protocol = p;
  const bool is_ssh = url_is_ssh(data->protocol);
  p = protocol_end + 1;
  if(p>=p_end || *p != '/')
    do{ fprintf(stderr, "ERROR %s Line %u! p=«%s»\n", "/tmp/expand_macro/url.c", 389 , p); goto error; }while(0);
  ++p; // consume first slash
  if(p>=p_end || *p != '/')
    do{ fprintf(stderr, "ERROR %s Line %u! p=«%s»\n", "/tmp/expand_macro/url.c", 393 , p); goto error; }while(0);
  char* const second_slash = p;
  ++p; // consume second slash
  if(p>=p_end)
    do{ fprintf(stderr, "ERROR %s Line %u! p=«%s»\n", "/tmp/expand_macro/url.c", 399 , p); goto error; }while(0);
  char* userinfo_end = scan_part(p, Userinfo, '@', '\0');
  if(userinfo_end && *userinfo_end == '@') { // userinfo found
    *userinfo_end = '\0';
    data->userinfo = p;
    p = userinfo_end + 1;
  }
  if(p>=p_end)
    do{ fprintf(stderr, "ERROR %s Line %u! p=«%s»\n", "/tmp/expand_macro/url.c", 409 , p); goto error; }while(0);
  char* hostname_end = NULL;
  if(*p == '[') // IPv6 literal address
  {
    ++p;
    hostname_end = scan_part( p, IPv6Char, ']', '\0' );
    if(!hostname_end)
      do{ fprintf(stderr, "ERROR %s Line %u! p=«%s»\n", "/tmp/expand_macro/url.c", 418 , p); goto error; }while(0);
    *hostname_end = '\0'; // eliminate ']'
    data->host = p;
    ++hostname_end;
    if(hostname_end < p_end && !is_ssh && *hostname_end==':') // port number follows the host
    {
      char* port_end = scan_decimal_number( hostname_end+1 );
      if(port_end)
      {
        data->port = hostname_end+1;
        p = port_end;
      }else{
        do{ fprintf(stderr, "ERROR %s Line %u! p=«%s»\n", "/tmp/expand_macro/url.c", 431 , p); goto error; }while(0);
      }
    }else{ // no port number
      p = hostname_end;
    }
  }else{ // alphanumeric hostname or IPv4 address
    hostname_end = scan_part( p, Unreserved | SubDelim, ':', '/' );
    if (!hostname_end)
      do{ fprintf(stderr, "ERROR %s Line %u! p=«%s»\n", "/tmp/expand_macro/url.c", 439 , p); goto error; }while(0);
    data->host = p;
    if(!is_ssh && *hostname_end==':') // we have a port number
    {
      *hostname_end = '\0';
      char* port_end = scan_decimal_number( hostname_end+1 );
      if(port_end)
      {
        data->port = hostname_end+1;
        p = port_end;
      }else{
        do{ fprintf(stderr, "ERROR %s Line %u! p=«%s»\n", "/tmp/expand_macro/url.c", 451 , p); goto error; }while(0);
      }
    }else{ // no port number
      p = hostname_end;
    }
  }
  // HACK: move userinfo, host and port by one char to add a \0 before the first '/' in the path:
  memmove(second_slash, second_slash+1, p-second_slash);
  if(data->userinfo)
    --(data->userinfo);
  --(data->host);
  if(data->port)
    --(data->port);
  p[-1] = '\0';
  // END HACK
  if(is_ssh && *p == ':')
  {
    ++p; // omit the first ':' from ssh URL's path
  }
  // FIXME: accepts _any_ sequence of "PChar"s and slashes, which is not RFC compliant
  char* path_end = scan_part( p, PCharSlash, '?', '#' );
  if(!path_end)
    do{ fprintf(stderr, "ERROR %s Line %u! p=«%s»\n", "/tmp/expand_macro/url.c", 479 , p); goto error; }while(0);
  const bool has_query = (*path_end == '?');
  const bool has_fragment = (*path_end == '#');
  *path_end = '\0';
  data->path = decode_percent(p);
  p = path_end + 1;
  if(has_query)
  {
    char* query_end = scan_part( p, Query, '#', '\0' );
    if(query_end)
    {
      const bool has_fragment = (*query_end == '#');
      *query_end = '\0';
      data->query = parse_query_string(p, query_end);
      if(has_fragment) // fragment followes query: ...?query#fragment
      {
        char* fragment_end = scan_part( query_end+1, Fragment, '\0', '\0' );
        if(fragment_end)
        {
          data->fragment = decode_percent(query_end+1);
        }else{
          do{ fprintf(stderr, "ERROR %s Line %u! p=«%s»\n", "/tmp/expand_macro/url.c", 503 , p); goto error; }while(0);
        }
      }
    }else{
      do{ fprintf(stderr, "ERROR %s Line %u! p=«%s»\n", "/tmp/expand_macro/url.c", 507 , p); goto error; }while(0); // no valid query string
    }
  }else if(has_fragment) // ...#fragment
  {
        char* fragment_end = scan_part( p, Fragment, '\0', '\0' );
        if(fragment_end)
        {
          data->fragment = decode_percent(p);
        }else{
          do{ fprintf(stderr, "ERROR %s Line %u! p=«%s»\n", "/tmp/expand_macro/url.c", 516 , p); goto error; }while(0);
        }
  }
//finished:
  return data;
error:
  url_free(data);
  return NULL;
}
bool
url_is_protocol (const char* str) {
  const unsigned count = sizeof(URL_SCHEMES) / sizeof(URL_SCHEMES[0]);
  for (unsigned i = 0; i < count; ++i) {
    if (0 == strcmp(URL_SCHEMES[i], str)) {
      return true;
    }
  }
  return false;
}
bool
url_is_ssh (const char* str) {
  if (0 == strcmp(str, "ssh") || 0 == strcmp(str, "git")) {
    return true;
  }
  return false;
}
char *
url_get_scheme (const char* url) {
  char *protocol = (char *) malloc(32);
  if (!protocol) return NULL;
  sscanf(url, "%[^://]", protocol);
  if (url_is_protocol(protocol)) return protocol;
  free(protocol);
  return NULL;
}
char *
url_get_userinfo (const char* url) {
  do{ url_data_t* data = url_parse(url); char* out = data && data->userinfo ? strdup(data->userinfo) : NULL; url_free(data); return out; }while(0);
}
char *
url_get_hostname (const char* url) {
  do{ url_data_t* data = url_parse(url); char* out = data && data->host ? strdup(data->host) : NULL; url_free(data); return out; }while(0);
}
char *
url_get_host (const char* url) {
  do{ url_data_t* data = url_parse(url); char* out = data && data->host ? strdup(data->host) : NULL; url_free(data); return out; }while(0);
}
char *
url_get_pathname (const char* url) {
  do{ url_data_t* data = url_parse(url); char* out = data && data->path ? strdup(data->path) : NULL; url_free(data); return out; }while(0);
}
char *
url_get_path (const char* url) {
  do{ url_data_t* data = url_parse(url); char* out = data && data->path ? strdup(data->path) : NULL; url_free(data); return out; }while(0);
}
const char *
url_get_query_value (const url_data_t* url, const char* key)
{
  if(url->query == NULL)
    return NULL;
  for( const struct url_key_value* kv = url->query; kv->key; ++kv)
  {
     if(strcmp(kv->key, key) == 0)
       return kv->value;
  }
  return NULL;
}
char *
url_get_fragment (const char* url) {
  do{ url_data_t* data = url_parse(url); char* out = data && data->fragment ? strdup(data->fragment) : NULL; url_free(data); return out; }while(0);
}
char *
url_get_port (const char* url) {
  do{ url_data_t* data = url_parse(url); char* out = data && data->port ? strdup(data->port) : NULL; url_free(data); return out; }while(0);
}
void
url_inspect (const char* url) {
  url_data_inspect(url_parse(url));
}
void
url_data_inspect (const url_data_t* data) {
  printf("#url =>\n");
  do{ if(data->protocol) printf("    ." "protocol" ": \"%s\"\n", data->protocol); else printf("    ." "protocol" ": (NULL)\n"); }while(0);
  do{ if(data->host) printf("    ." "host" ": \"%s\"\n", data->host); else printf("    ." "host" ": (NULL)\n"); }while(0);
  do{ if(data->userinfo) printf("    ." "userinfo" ": \"%s\"\n", data->userinfo); else printf("    ." "userinfo" ": (NULL)\n"); }while(0);
  do{ if(data->host) printf("    ." "host" ": \"%s\"\n", data->host); else printf("    ." "host" ": (NULL)\n"); }while(0);
  do{ if(data->port) printf("    ." "port" ": \"%s\"\n", data->port); else printf("    ." "port" ": (NULL)\n"); }while(0);
  do{ if(data->path) printf("    ." "path" ": \"%s\"\n", data->path); else printf("    ." "path" ": (NULL)\n"); }while(0);
  if(data->query)
  {
     for(unsigned nr=0; data->query[nr].key; ++nr)
     {
        printf("    .query[%u]: \"%s\" -> ", nr, data->query[nr].key);
        if(data->query[nr].value)
          printf("\"%s\"\n", data->query[nr].value);
        else
          printf("(NULL)\n");
     }
  }
  do{ if(data->fragment) printf("    ." "fragment" ": \"%s\"\n", data->fragment); else printf("    ." "fragment" ": (NULL)\n"); }while(0);
}
void
url_free (url_data_t *data) {
  if (!data) return;
  free(data->whole_url);
  free((void*)data->query);
  free(data);
}
// C99 is brain-dead, so we need these:
extern inline
char* url_get_protocol (const char* url);
extern inline
char* url_get_hash (const char* url);
