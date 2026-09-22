#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/sysinfo.h"
#include "user/user.h"

int
main(void)
{
  struct sysinfo info;

  if (sysinfo(&info) < 0) {
    printf("sysinfo failed\n");
    exit(1);
  }
  printf("freepages = %lu pages\n", info.freepages);
  printf("nproc     = %lu\n", info.nproc);

  int pid = fork();	//fork를 호출하여 자식 프로세스를 생성하고 pid에 저장한다.

  if (pid < 0) {	//만약 fork가 실패한다면
    printf("fork failed\n");	//fork failed 메시지를 출력한다.
    exit(1);	//프로세스 종료
  }

  if (pid == 0) {	//만역 자식 프로세스라면
    if (sysinfo(&info) < 0) {	//만약 sysinfo 호출에 실패한다면
      printf("sysinfo failed\n");	//sysinfo failed 메시지를 출력한다.
      exit(1);	//프로세스 종료
    }

    printf("child nproc = %lu\n", info.nproc);	//자식 프로세스 생성 후 프로세스 수를 출력한다.
    exit(0);	//프로그램 종료
  }

  wait(0);	//자식 종료까지 부모 대기

  exit(0);
}

