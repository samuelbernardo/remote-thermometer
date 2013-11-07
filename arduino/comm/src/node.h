/* Ficheiro: node.h **/

/* Descri��o:
   Cont�m as defini��es globais de um n�. Este ficheiro NECESSITA ser
  devidamente configurado face �s caracter�sticas espec�ficas de cada n�.
  Ver indica��es abaixo.
*/

/* Autor: Renato Jorge Caleira Nunes */

/*  Historial:
12/04/08 - Cria��o deste m�dulo e vers�o inicial.
*/ /* ::hist */

/*  Notas:
:cfg - Assinala op��es de configura��o
ATT - Assinala uma particularidade a ter em aten��o
!!  - Assinala uma instru��o que n�o deve ser alterada
:err - Assinala um erro interno
cast - Assinala um cast
:dbg - Assinala c�digo usado para debug
*/


#define _SIMUL_  0  /* ##:cfg  0=Simulacao INACTIVA; 1=Simulacao ACTIVA */


  /* constantes que identificam o tipo de placa; ver _NODE_BOARD_TYPE_ */
#define NODE_BOARD_CM       0  /* placa CM */
#define NODE_BOARD_CM2      1  /* placa CM2 */
#define NODE_BOARD_ARDUINO  2  /* placa Arduino 2009 */
#define NODE_BOARD_xxx      3  /* placa ... (new board...) */

#define _NODE_BOARD_TYPE_   2  /*##:cfg (ver acima) */


#define _NODE_USES_MSG_  1  /*##:cfg  0:n�o usa MSG  1: usa MSG */


#include "v_types.h"

#define disable_interrupts cli()
#define enable_interrupts  sei()

/*	ATT:	::05
   A identifica��o das aplica��es come�a em 0 e necessita ser sequencial;
  no m�ximo podem existir 8 aplica��es (entre 0 e 7).
   A obrigatoriedade de a numera��o ser sequencial visa poupar mem�ria.
  (ver m�dulo prop.c).
*/
			/* ATT:  ver  NODE_BROADCAST_APP_INDEX  abaixo */
#define NODE_APP_SYS     0  /*:cfg*/ /* !! � partida SYS � sempre a app 0 */
#define NODE_APP_SWITCH  1  /*##:cfg*/
#define NODE_APP_RELAY   2

#define NODE_NUM_APPS    3  /*##:cfg (ver acima) ::00*/
		/* ATT: n�o pode ser superior 8 */  /* ver >>>net.c */




#ifdef _MAIN_  /* [ */
	
	/* ::global vars **/

#endif  /* ] */



#ifndef _MAIN_  /* [ */

	/* ::extern declarations **/


#endif  /* ] */







/* Fim do ficheiro node.h **/
/* Autor: Renato Jorge Caleira Nunes */

/*
  ::next -> ::08
*/
