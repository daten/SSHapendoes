#include <nss.h>
#include <pwd.h>
#include <stdio.h>
#include <shadow.h>
#include <errno.h>

char *gecos = "CANARY";
char *dir = "/home/SSHapendoes";
char *shell = "/bin/false";
char *spasswd = "*";

enum nss_status _nss_canary_setpwent(void) {
//  printf("@ %s\n", __FUNCTION__) ;
  return NSS_STATUS_SUCCESS;
}

enum nss_status _nss_canary_endpwent(void) {
//  printf("@ %s\n", __FUNCTION__) ;
  return NSS_STATUS_SUCCESS;
}

enum nss_status _nss_canary_getpwent_r(struct passwd *result_buf, char *buffer, size_t buflen, int *errnop) {
//  printf("@ %s\n", __FUNCTION__) ;
  return NSS_STATUS_NOTFOUND;
}

enum nss_status _nss_canary_getpwnam(const char *name, struct passwd *result, char *buffer, size_t buflen, int *errnop) {
//  printf("@ %s\n", __FUNCTION__);

  return _getpwnam(name, result, buffer, buflen, errnop);
}

enum nss_status _nss_canary_getpwnam_r(const char *name, struct passwd *result, char *buffer, size_t buflen, int *errnop) {
//  printf("@ %s\n", __FUNCTION__);

  return _getpwnam(name, result, buffer, buflen, errnop);
}

enum nss_status _getpwnam(const char *name, struct passwd *result, char *buffer, size_t buflen, int *errnop) {
  if(name == NULL) {
    *errnop = EINVAL;
    return NSS_STATUS_UNAVAIL;
  }

  result->pw_name=name;
  result->pw_uid=32767;
  result->pw_gid=32767;
  result->pw_gecos=gecos;
  result->pw_dir=dir;
  result->pw_passwd=spasswd;
  result->pw_shell=shell;
  snprintf(buffer, buflen, "%s", name);

  return NSS_STATUS_SUCCESS;
}
