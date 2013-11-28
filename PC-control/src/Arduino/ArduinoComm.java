package Arduino;

import java.io.DataInputStream;
import java.io.IOException;

import ArduinoFunctions.*;

public class ArduinoComm extends SerialComm
{
	
	public ArduinoComm()
	{
		
	}
	
	public static void main(String[] args)
	{
		long time = System.currentTimeMillis(); //Iniciando leitura serial
		String ch = "0";
		//SerialCommLeitura leitura = new SerialCommLeitura("COM7", 9600, 0);
		DataInputStream teclado = new DataInputStream(System.in);  
		
		while(!ch.equals("exit")){
			
		try {
			ch = teclado.readLine();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		if(ch.equals("1")||ch.equals("2")||ch.equals("3") ){
			if(ch.equals("1"))System.out.println("Luz\n");
			if(ch.equals("2"))System.out.println("Temp1\n");
			if(ch.equals("3"))System.out.println("Temp2\n");
		SerialCommLeitura leitura = new SerialCommLeitura("COM7", 9600, 0);
		leitura.HabilitarEscrita();
        leitura.ObterIdDaPorta();
        leitura.AbrirPorta();
        leitura.EnviarUmaString(ch);
       
        
       
        leitura.HabilitarLeitura();
      //  leitura.ObterIdDaPorta();
      //  leitura.AbrirPorta(); 
        leitura.LerDados();
        try {
            Thread.sleep(1000);
        } catch (InterruptedException ex) {
            System.out.println("Erro na Thread: " + ex);
        }
        leitura.FecharCom();
    
		}
       

        //Controle de tempo da leitura aberta na serial

        try {
            Thread.sleep(1000);
        } catch (InterruptedException ex) {
            System.out.println("Erro na Thread: " + ex);
        }
		}
       
        
      /* 
        //Iniciando escrita serial
        SerialCommLeitura escrita = new SerialCommLeitura("COM7", 9600, 0);
        escrita.HabilitarEscrita();
        escrita.ObterIdDaPorta();
        escrita.AbrirPorta();
        escrita.EnviarUmaString("Olá mundo via porta serial!");
        escrita.FecharCom();
        */
    }

}
/*
long time = System.currentTimeMillis(); //Iniciando leitura serial
String ch = "0";
SerialCommLeitura leitura = new SerialCommLeitura("COM7", 9600, 0);
DataInputStream teclado = new DataInputStream(System.in);  
leitura.HabilitarLeitura();
leitura.ObterIdDaPorta();
leitura.AbrirPorta(); 
leitura.LerDados();

//Controle de tempo da leitura aberta na serial

try {
    Thread.sleep(1000);
} catch (InterruptedException ex) {
    System.out.println("Erro na Thread: " + ex);
}

leitura.FecharCom();
*/