/**/
/* Ficheiro: time.c **/

/* Descri��o:
   Cont�m fun��es para permitir a marca��o de tempo, tendo por base uma
  interrup��o que ocorre a cada 200us.  (:avr)
   Permite marcar 200us, 10ms, 1s, etc (ver >>:00).
*/
/* Autor: Renato Jorge Caleira Nunes */


/*  Historial:
03/07/2002 - Cria��o deste m�dulo.
03/09/2002 - Vers�o inicial da template deste m�dulo.
16/10/2002 - Adapta��o ao uso com a NET.
06/11/2002 - Acrescentei SYS_msg_timer e activei marca��o de 100ms.
--/--/2005 - Passou a ser usado o Timer 0 em vez do Timer 1. Ver >>:07
24/08/2010 - Efectuei pequenas correc��es/optimiza��es. Corrigi erro na
 marca��o de minutos (vari�vel trocada; nunca foi usado...).
 Adaptei ao m�dulo de simula��o (SIMUL).
03/11/2011 - Adapta��o � placa Arduino Duemilanove (2009).
*/ /* ::hist */


/*  Notas:
:cfg - Assinala op��es de configura��o
:avr - Assinala particularidades ligadas ao tipo de microcontrolador usado
:init - Assinala particularidades ligadas � inicializa��o de vari�veis
ATT - Assinala uma particularidade a ter em aten��o
!!  - Assinala uma instru��o que n�o deve ser alterada
:err - Assinala um erro interno
cast - Assinala um cast
:OLD - C�digo antigo desactivado
:dbg - Assinala c�digo usado para debug
*/


/* includes globais */

#include "node.h"

#if _SIMUL_
 #include "simul.h"
#endif


/* includes globais do compilador WinAVR */

#if ! _SIMUL_
 #include <avr/io.h>
 #include <avr/interrupt.h>
#endif


/* includes espec�ficos deste m�dulo */

#define _TIME_TASK_

#include "time.h"

/* include dos m�dulos que usam "timers" */

#include "sys0.h"
#include "comm.h"
/*
 #include "switch.h"
 #include "relay.h"
*/


	/* ::defines **/


	/* Vari�veis globais ::vars **/


	/* Vari�veis locais **/

static uint8 TIME_curr_time; /* incrementado a cada interrup��o de 200 us */
static uint8 TIME_last_time;



/* Inicializa o Timer.
+------------------------------------------------------------------------*/
void /**/TIME_init(void) /*:avr*/
{
#if ! _SIMUL_  /* [ */

#if (_NODE_BOARD_TYPE_ == NODE_BOARD_CM || _NODE_BOARD_TYPE_ == NODE_BOARD_CM2)
/* AT90S8515 */

  /* desnecess�rio pois o reset for�a a 0 */
  /*TIFR |= 0x02; /* Timer Interrupt Flag Register (p.28) */
    /* limpa a flag "Timer/Counter0 Output Overflow" interrupt (TOV0) */

  TCCR0 = 0X02; /* Timer/Counter0 Control Register (p.33) */
	/* clock select: CLK/8 (8MHz/8=1MHz -> 1us) */

  TCNT0 = 56; /* timer 0 value (counts up) (p.34) */ /*::02*/ /*:cfg*/
	/* 256-56 = 200 unidades de 1us (ver acima) = 200us */

  TIMSK |= 0x02; /* Timer Interrupt Mask Register (p.27) */
	/* enable "Timer/Counter0 Overflow" interrupt */
	/* s� afecta bit 1; demais bits mant�m valor */
#endif 


#if (_NODE_BOARD_TYPE_ == NODE_BOARD_ARDUINO)
/* ATmega328 */

  /* desnecess�rio pois o reset for�a a 0 */
  /*TIFR0 |= 0x02; /* Timer/Counter0 Interrupt Flag Register (p.113) */
    /* limpa a flag "Timer/Counter0 Compare Match A" interrupt (OCF0A) */

  TCCR0B |= 0X03; /* Timer/Counter Control Register (p.111-112) */
	/* clock select: CLK/64 (16MHz/64=250KHZ -> 4us) */
 	
  OCR0A = 50; /* 50 unidades de 4us (ver acima) = 200us */ /*::02*/ /*:cfg*/

  TIMSK0 |= 0x02; /* Timer/Counter Interrupt Mask Register (p.113) */
	/* enable "Timer/Counter0 Compare Match A" interrupt */
#endif

#endif  /* ! _SIMUL_ */ /* ] */


#if 0  /*## desnecess�rio; compilador inicializa vars globais a 0 */ /*:init*/
  TIME_curr_time = 0;
  TIME_last_time = 0;
#endif

#if _SIMUL_  /* [ */
  printf("TIME_init(): TIME_curr_time=%u\n",TIME_curr_time);
  printf("TIME_init(): Done!\n");
#endif  /* _SIMUL_ */ /* ] */
}



#if ! _SIMUL_  /* [ */
#if (_NODE_BOARD_TYPE_ == NODE_BOARD_CM || _NODE_BOARD_TYPE_ == NODE_BOARD_CM2)
/* Rotina de tratamento da interrup��o "Overflow" do timer 0.
  (A declara��o da rotina est� de acordo com o compilador WinAVR / avr-gcc).
   � gerada uma interrup��o a cada 200us (para cristal de 8MHz).
+------------------------------------------------------------------------*/
ISR(TIMER0_OVF_vect) /*:avr*/ /*::08*/  /* placas CM e CM2 (AT90S8515) */
{
  TCNT0 += 56; /* ver >>:02 */ /* :cfg */

  ++TIME_curr_time;
}
#endif /* (NODE_BOARD_CM || NODE_BOARD_CM2) */

#if (_NODE_BOARD_TYPE_ == NODE_BOARD_ARDUINO)
/* Rotina de tratamento da interrup��o "Compare Match A" do timer 0.
  (A declara��o da rotina est� de acordo com o compilador WinAVR / avr-gcc).
   � gerada uma interrup��o a cada 200us (para cristal de 16MHz).
+------------------------------------------------------------------------*/
ISR(TIMER0_COMPA_vect) /*:avr*/ /*::08*/  /* placa Arduino (ATmega328) */
{
  OCR0A += 50; /* (p.112) ver >>:02 */ /* :cfg */

  ++TIME_curr_time;
}
#endif /* (NODE_BOARD_ARDUINO) */
#endif  /* ! _SIMUL_ */ /* ] */



#if _SIMUL_  /* [ */
/* Marca��o de tempo em modo de simula��o. "time_value" representa N unidades
  de 200us.
+------------------------------------------------------------------------*/
int /**/TIME_simul_update_time(uint8 time_value) /*:simul*/
{
  TIME_curr_time += time_value;
  return TIME_curr_time;
}
#endif  /* _SIMUL_ */ /* ] */



/**/



#define TIME_1MS_N200US    5  /* 1 ms (5*200us) */
#define TIME_10MS_N200US  50  /* 10 ms (50*200us) */
#define TIME_50MS_N10MS    5  /* 50 ms (5*10ms) */
#define TIME_100MS_N10MS  10  /* 100 ms (10*10ms) */
#define TIME_1S_N10MS    100  /* 1 s (100*10ms) */
#define TIME_1M_N1S       60  /* 1 min (60*1s) */


/* Tarefa que trata da actualiza��o das vari�veis das tarefas que
  contabilizam a passagem do tempo. Essas vari�veis s�o designadas de timers.
  Notar que os timers s�o actualizados em tempo de tarefa e n�o em tempo
  de interrup��o. Se houver necessidade de marcar tempo numa parte de c�digo
  que esteja em ciclo (eventualmente) infinito (por exemplo, numa espera
  activa), a vari�vel em quest�o necessita ser actualizada directamente na
  rotina de interrup��o - ver >>:04.
   A unidade de base de marca��o de tempo � 200us. Permite tamb�m a marca��o
  de 1ms, 10ms, 50ms, 100ms, 1s e 1min dependendo da configura��o usada.
+------------------------------------------------------------------------*/
void /**/TIME_task(void)
{
  uint8 elapsed_time; /* N * 200us */


    /* :cfg*/
  static uint8 t10ms_n200us = 0;
  static uint8 t100ms_n10ms = 0;

#if 0  /*  ## :cfg
   Copiar para cima as vari�veis necess�rias consoante as unidades de tempo
  desejadas (1ms, 10ms, 100ms, etc). Notar que para se ter 100ms, por
  exemplo, � necess�rio ter 10ms. A unidade 200us est� sempre dispon�vel.
*/
  static uint8 t1ms_n200us = 0;
  static uint8 t10ms_n200us = 0;  <--
  static uint8 t50ms_n10ms = 0;
  static uint8 t100ms_n10ms = 0;  <--
  static uint8 t1s_n10ms = 0;
  static uint8 t1m_n1s = 0;
#endif

		/* ver node.h */
  disable_interrupts; /* desactiva todas as interrup��es */ /* ver >>::06 */
/**/

  elapsed_time = TIME_curr_time - TIME_last_time;
  TIME_last_time = TIME_curr_time;

  enable_interrupts; /* activa todas as interrup��es */
		/* ver node.h */



/* [ */ /* Timers de  200us */

/* var char:  1-255 => 0.2ms - 51.0ms (~0.05s) */
/* var int: 1-65535 => 0.2ms - 13107ms (~13s) */

							/* 200us **/
#if 0 /*##*/
  NET_timer += elapsed_time; /*:cfg*/
#endif /*##*/
  /*MMM_timer += elapsed_time;*/ /*:cfg*/

/* ] */



#if 0  /* :cfg [ */  /* Timers de  1ms */

/* var char:  1-255 => 1ms - 255ms (~0.25s) */
/* var int: 1-65535 => 1ms - 65535ms (~65.5s) */

  t1ms_n200us += elapsed_time;
  if(t1ms_n200us >= TIME_1MS_N200US)
  {
    t1ms_n200us -= TIME_1MS_N200US; /*!!*/
						/* 1 ms  (5*200us) **/
    /*++MMM_timer;*/ /*:cfg*/
    /*++MMM_timer;*/ /*:cfg*/
  }
#endif /* ] */



#if 1  /* :cfg [ */  /* Timers de  10ms */

/* var char:  1-255 => 0.01s - 2.55s */
/* var int: 1-65535 => 0.01s - 655.35s (~10.9m) */

  t10ms_n200us += elapsed_time;
  if(t10ms_n200us >= TIME_10MS_N200US)
  {
    t10ms_n200us -= TIME_10MS_N200US; /*!!*/
						/* 10 ms  (50*200us) **/
    ++SYS0_led_timer;
    ++COMM_timer;
	
#if 0 /*[##*/ /*:cfg*/
    ++SWITCH_read_timer;
    ++RELAY_timer;
#endif /*]##*/

    /*++MMM_timer;*/ /*:cfg*/
    /*++MMM_timer;*/ /*:cfg*/


#if 0  /* :cfg [ */  /* Timers de  50ms  (necessita de 10ms) */

/* var char:  1-255 => 0.05s - 12.75s */
/* var int: 1-65535 => 0.05s - 3276.75s (~54.6m) */

    ++t50ms_n10ms;
    if(t50ms_n10ms >= TIME_50MS_N10MS)
    {
      t50ms_n10ms = 0;
						/* 50 ms  (5*10ms) **/
      /*++MMM_timer;*/ /*:cfg*/
      /*++MMM_timer;*/ /*:cfg*/
    }
#endif /* ] */


#if 0  /* :cfg [ */  /* Timers de  100ms  (necessita de 10ms) */
					/* (precis�o: ver >>:00) */
/* var char:  1-255 => 0.1s - 25.5s */
/* var int: 1-65535 => 0.1s - 6553.5s (~109m, ~1.8h) */

    ++t100ms_n10ms;
    if(t100ms_n10ms >= TIME_100MS_N10MS)
    {
      t100ms_n10ms = 0;
						/* 100 ms  (10*10ms) **/
#if 0 /*[##*/ /*:cfg*/
      ++MSG_curr_time; /* contador circular de 100ms */
      ++MSG_timer; /*## ???*/

      ++SYS_msg_timer;
      ++SWITCH_msg_timer;
      ++RELAY_msg_timer;
#endif /*]##*/

      /*++MMM_timer;*/ /*:cfg*/
      /*++MMM_timer;*/ /*:cfg*/
    }
#endif /* ] */



#if 0  /* :cfg [ */  /* Timers de  1 s  (necessita de 10ms) */

/* var char:  1-255 => 1s - 255s (~4.2m) */
/* var int: 1-65535 => 1s - 65535s (~1092m, ~18.2h) */

    ++t1s_n10ms;
    if(t1s_n10ms >= TIME_1S_N10MS)
    {
      t1s_n10ms = 0;
						/* 1 s  (100*10ms) **/
      /*++MMM_timer;*/ /*:cfg*/
      /*++MMM_timer;*/ /*:cfg*/


#if 0  /* :cfg [ */  /* Timers de  1 min  (necessita de 1 s) */

/* var char:  1-255 => 1m - 255m (~4.2h) */
/* var int: 1-65535 => 1m - 65535m (~1092h, ~45.5d) */

      ++t1m_n1s;
      if(t1m_n1s >= TIME_1M_N1S)
      {
        t1m_n1s = 0;
						/* 1 min  (60*1s) **/
        /*++MMM_timer;*/ /*:cfg*/
        /*++MMM_timer;*/ /*:cfg*/
      }
#endif /* ] */
    }
#endif /* ] */
  }
#endif /* ] */
}



/**/



/* Fim do ficheiro time.c **/
/* Autor: Renato Jorge Caleira Nunes */

#if 0
::07::10::11::12::13::14::15::16::17::18::19
#endif
