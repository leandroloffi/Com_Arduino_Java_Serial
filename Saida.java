import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author LEANDRO
 */
public class Saida extends Thread {

    private final syn_Valores cubbyhole;
    private final int number;

    public Saida(syn_Valores c, int number) {
        
        cubbyhole = c;
        this.number = number;
    }
    
    LocalShell shell = new LocalShell();

    @Override
    public void run() {
        while (true) {
            try {
                Thread.sleep(10000);
            } catch (InterruptedException e) {
                System.out.println("ERRO! NA SAIDA");
            }
            //System.out.println("GRAVANDO!");
            ArrayList<Lista> listaSaida = cubbyhole.get(); // LISTA SAIDA!!
            String saidaT = saida(listaSaida);
            System.out.println("GRAVADO >> " + saidaT);
            gravarTXT(saidaT);
            try {
                shell.executeCommand("sudo node /home/pi/Desktop/deviceSDK/JS/node_modules/aws-iot-device-sdk/examples/conexao.js");
            } catch (IOException ex) {
                Logger.getLogger(Saida.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }

    private String saida(ArrayList<Lista> listaSaida) {
        int i = 0;
        String saida = "";
        System.out.println(">> " + listaSaida.size());
        while (i < listaSaida.size()){
            saida += listaSaida.get(i).Temp1 + ";";
            saida += listaSaida.get(i).Temp2 + ";";
            saida += listaSaida.get(i).Umid + ";";
            saida += listaSaida.get(i).Pressao + ";";
            saida += listaSaida.get(i).Altitude + ";";
            saida += listaSaida.get(i).Pluv + ";\n";
            i++;
        }
        listaSaida.removeAll(listaSaida);
        return saida;
    }
    
    public void gravarTXT(String texto) {
        try {
            FileWriter arq;

            arq = new FileWriter("d:\\arquivo_Buffer.lol"); // MUDAR DEPOIS NO LINUX

            PrintWriter gravarArq = new PrintWriter(arq);

            gravarArq.printf(texto);

            arq.close();

        } catch (IOException ex) {
            Logger.getLogger(Saida.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
}
