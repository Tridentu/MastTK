#include <pwd.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include "ExecUtils.h"


namespace MastTK {
  bool runAsUser(std::string username, std::function<void()> action){
    struct passwd pwd;
    struct passwd *result;
    char *buf;
    size_t bufsize;
    int s;
    bufsize = sysconf(_SC_GETPW_R_SIZE_MAX);
    if(bufsize == -1)
      bufsize = 16384;

    buf = (char*)malloc(bufsize);
    if(buf == NULL) {
      return false;
    }

    s = getpwnam_r(username.c_str(), &pwd, buf, bufsize, &result);
    if(result == NULL)
      return false;

    int child = fork();
    if (child == 0){
      setgid(pwd.pw_gid);
      setuid(pwd.pw_uid);
      action();
    } else if (child > 0) {
      return false;
    } else {
      return false;
    }
  }
}
