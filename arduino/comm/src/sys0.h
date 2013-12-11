/* Ficheiro: sys0.h **/

/* Autor: Renato Jorge Caleira Nunes */


/*  Historial:
03/11/2011 - Cria��o deste m�dulo tendo por base SYS.H
*/ /* ::hist */


/*  Notas:
:cfg - Assinala op��es de configura��o
ATT - Assinala uma particularidade a ter em aten��o
!!  - Assinala uma instru��o que n�o deve ser alterada
:err - Assinala um erro interno
cast - Assinala um cast
:dbg - Assinala c�digo usado para debug
*/


/* ::define **/


#define SYS0_TRUE   1
#define SYS0_FALSE  0


#ifndef _SYS0_TASK_
/* ::extern vars **/

extern uint8 SYS0_led_timer;  /* 10 ms */


/* public functions **/

void SYS0_init(void);
void SYS0_task(void);
void SYS0_led_num_pulses(uint8 num_pulses);

#endif


/* Fim do ficheiro sys0.h **/
/* Autor: Renato Jorge Caleira Nunes */


#if 0
::00::01::02::03::04::05::06::07::08::09
#endif
