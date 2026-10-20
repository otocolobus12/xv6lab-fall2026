#include "kernel/types.h"
#include "user/user.h"

// 사용법: priotest [A] [B] [C]  (기본값 1 10 10)
// 값이작을수록먼저실행. CPUS=1로실행할것.
#define N 3

int
main(int argc, char *argv[])
{
 int prio[N] = {1, 10, 10};  //우선순위 기본값
 for (int i = 0; i < N && i + 1 < argc; i++)
  prio[i] = atoi(argv[i + 1]);  //입력 값으로 우선순위 지정

 int start = uptime();  //시작 시간
 for (int i = 0; i < N; i++) {
  if (fork() == 0) {                  // 자식A, B, C
   set_priority(prio[i]);  //우선순위 설정
   volatile unsigned long x = 0;  //계산 결과 저장
   for (unsigned long j = 0; j < 1500000000UL; j++)
    x += j;                         // 계산만한다
   printf("%c (pid %d, prio %d) done at %d ticks\n",
	'A' + i, getpid(), prio[i], uptime() - start);  //출력 형식 지정
   exit(0);  //자식 종료
  }
 }
 for (int i = 0; i < N; i++)
  wait(0);  //자식 종료 대기
 exit(0);  //부모 종료
}
