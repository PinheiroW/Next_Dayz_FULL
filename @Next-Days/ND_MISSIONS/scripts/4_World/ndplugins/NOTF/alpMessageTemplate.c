/**
 * alpMessageTemplate.c
 * * NOTIFICATION TEMPLATE - Módulo ND_MISSIONS (NOTF)
 * Define a estrutura para mensagens automáticas e agendadas do servidor.
 */

class alpServerMessageTemplate 
{
	int            Type;      // 0-1: Mensagem global do servidor, 2: Mensagem pessoal (OnConnect)
	string         Message;   // Texto da mensagem
	ref array<int> Time;      // Horário de execução: [HH, MM, SS]
	int            Loop;      // Contador de loops: -1 (infinito), 0 (uma vez), X (X+1 vezes)
	int            LoopTime;  // Tempo de espera entre cada repetição

	/**
	 * Construtor da classe de template de mensagem.
	 * Inicializa os parâmetros de texto, tempo e repetição.
	 */
	void alpServerMessageTemplate(int type, string text, ref array<int> time, int loop, int looptime)
	{
		Type     = type;
		Message  = text;
		Time     = time;
		Loop     = loop;
		LoopTime = looptime;
	}
}