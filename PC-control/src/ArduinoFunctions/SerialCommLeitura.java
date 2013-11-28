package ArduinoFunctions;

import gnu.io.CommPortIdentifier;
import gnu.io.SerialPort;
import gnu.io.SerialPortEvent;
import gnu.io.SerialPortEventListener;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.sql.ResultSet;
import java.util.ArrayList;
import java.util.Iterator;

public class SerialCommLeitura implements Runnable, SerialPortEventListener
{
	public String DadosLidos;
	public int nodeBytes;
	private int baudrate;
	private int timeout;
	private CommPortIdentifier cp;
	private SerialPort porta;
	private OutputStream saida;
	private InputStream entrada;
	private Thread threadLeitura;
	private boolean IDPortaOK;
	private boolean PortaOK;
	private boolean leitura;
	private boolean escrita;
	private String Porta;
	protected String peso;
	
	/* Construtor da classe SerialCommLeitura
	 * String p: Porta
	 * int b: baudrate
	 * int t: timeout*/
	public SerialCommLeitura(String p, int b, int t)
	{
		this.Porta=p;
		this.baudrate=b;
		this.timeout=t;
		
	}
	
	/* Função para definir o valor da variável peso*/
	public void setPeso(String peso)
	{
		this.peso=peso;
	}
	/* Função para obter o valor da variável peso*/
	public String getPeso()
	{
		return this.peso;
	}
	
	/*Funções para permitir ora a escrita ora a leitura,
	 *pois a interface serial não permite que se execute as duas funções ao mesmo tempo*/
	public void HabilitarEscrita(){
		escrita = true;
		leitura = false;
	}
	
	public void HabilitarLeitura()
	{
		escrita=false;
		leitura=true;
	}
	
	/* Função para obter o ID da porta para ser utilizado na identificação da mesma*/
	public void ObterIdDaPorta()
	{
		try{
			cp = CommPortIdentifier.getPortIdentifier(Porta);
			
			if(cp == null)
			{
				System.out.println("Erro na Porta");
				IDPortaOK = false;
				System.exit(1);
			}
			
			IDPortaOK=true;
			
		}catch (Exception e) {
			// TODO: handle exception
			System.out.println("Erro obtendo ID da Porta:" + e);
			IDPortaOK = false;
			System.exit(1);
		}
	}
	/*Função para abrir a comunicação com a porta serial*/
	public void AbrirPorta()
	{
		try{
			porta = (SerialPort)cp.open("SerialCommLeitura", timeout);
			PortaOK = true;
			//configuar parametros
			porta.setSerialPortParams(baudrate, porta.DATABITS_8, porta.STOPBITS_1, porta.PARITY_NONE);
			porta.setFlowControlMode(SerialPort.FLOWCONTROL_NONE);
			
		}catch (Exception e) {
			// TODO: handle exception
			PortaOK = false;
			System.out.println("Erro abrindo comunicação:"+e);
			System.exit(1);
		}
	}
	/*Função para habilitar a leitura da porta serial*/
	public void LerDados()
	{
		if(escrita==false)
		{
			try{
				entrada = porta.getInputStream();
			}catch (Exception e) {
				// TODO: handle exception
				System.out.println("Erro de Stream:"+e);
				System.exit(1);
			}
			try{
				porta.addEventListener(this);
			}catch (Exception e) {
				// TODO: handle exception
				System.out.println("Erro de listener:"+e);
				System.exit(1);
			}
			
			porta.notifyOnDataAvailable(true);
			
			try{
				threadLeitura = new Thread(this);
				threadLeitura.start();
				run();
			}catch (Exception e) {
				// TODO: handle exception
				System.out.println("Erro de Thread:"+e);
			}
		}
	}
	/*Função para enviar uma String para a porta serial*/
	public void EnviarUmaString(String msg)
	{
		if(escrita == true)
		{
			try{
				saida = porta.getOutputStream();
				System.out.println("FLUXO OK!");
				
			}catch (Exception e) {
				// TODO: handle exception
				System.out.println("Erro.STATUS:"+e);
			}
			try{
				System.out.println("Enviando um byte para "+Porta);
				System.out.println("Enviando: "+msg);
				saida.write(msg.getBytes());
				Thread.sleep(100);
				saida.flush();
			}catch (Exception e) {
				// TODO: handle exception
				System.out.println("Houve um erro durante o envio.");
				System.out.println("STATUS: "+e);
				System.exit(1);
			}
		}else
		{
			System.exit(1);
		}
	}
	
	@Override
	public void run() {
		// TODO Auto-generated method stub
		try{
			Thread.sleep(5);
		}catch (Exception e) {
			// TODO: handle exception
			System.out.println("Erro de Thread:"+e);
			
		}
	}
	
	@Override
	public void serialEvent(SerialPortEvent ev) {
		// TODO Auto-generated method stub
		StringBuffer bufferLeitura = new StringBuffer();
		int novoDado =0;
		
		switch(ev.getEventType())
		{
		  case SerialPortEvent.BI:

          case SerialPortEvent.OE:

          case SerialPortEvent.FE:

          case SerialPortEvent.PE:

          case SerialPortEvent.CD:

          case SerialPortEvent.CTS:

          case SerialPortEvent.DSR:

          case SerialPortEvent.RI:

          case SerialPortEvent.OUTPUT_BUFFER_EMPTY:
        	  
        	  break;
          
          case SerialPortEvent.DATA_AVAILABLE:
        	  //Novo algoeritmo de leitura
        	  long time = System.currentTimeMillis();
        	  long timeout = 1000;
        	  long timeNow = System.currentTimeMillis();
        	  while(novoDado != -1 &&  (timeNow - time) < timeout)
        	  {
        		  try{
        			  novoDado = entrada.read();
        			  if(novoDado == -1){ break;}
        			  
        			  if('\r' == (char)novoDado)
        			  {
        				  bufferLeitura.append('\n');
        				  setPeso(new String(bufferLeitura));
        	        	  System.out.println(getPeso());
        				  bufferLeitura = new StringBuffer();
        				
        			  }else
        			  {
        				  bufferLeitura.append((char)novoDado);
        				  
        			  }
        		  }catch (Exception e) {
					// TODO: handle exception
        			  System.out.println("Erro de leitura serial:"+e);
        		  }
        		 timeNow = System.currentTimeMillis();
        	  }
        	 // setPeso(new String(bufferLeitura));
        	 // System.out.println(getPeso());
        	  break;
		}
		
	}

	
	/* Função para fechar a porta*/
	public void FecharCom()
	{
        try {
            porta.close();
        } catch (Exception e) {
            System.out.println("Erro fechando porta: " + e);
            System.exit(0);
        }
	}
	/* Função para obter a porta*/
	public String obterPorta()
	{
	    return Porta;
	}

	/* Função para obter o baudrate*/
	public int obterBaudrate()
	{
	    return baudrate;
	}


}
