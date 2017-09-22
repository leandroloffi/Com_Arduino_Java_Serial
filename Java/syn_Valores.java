import java.util.ArrayList;

/**
 *
 * @author LEANDRO
 */
class Lista { // VARIAVEIS DA LISTA 

    double Temp1, Temp2, Umid, Altitude, Pressao, Pluv;

    Lista(double Temp1E, double Temp2E, double UmidE, double AltE, double PresE, double PluvE) {
        Temp1 = Temp1E;
        Temp2 = Temp2E;
        Umid = UmidE;
        Altitude = AltE;
        Pressao = PresE;
        Pluv = PluvE;
    }
}

public class syn_Valores {

    private boolean available = false;
    public int quant;
    private final ArrayList<Lista> lista = new ArrayList<>();

    public synchronized ArrayList<Lista> get() { // SAIDA
        ArrayList<Lista> ListaAux = lista;
        if (quant > 0) {
            while (available == false) { // ENTRA COM TRUE
                System.out.println("ESPERANDO PARA PRODUZIR - PROCESSANDO");
                try {
                    wait();
                } catch (InterruptedException e) {
                }
            }
            available = false;

            //lista.removeAll(lista); // REMOVE TODA A LISTA.
            quant = 0;
            notifyAll();
        }
        return ListaAux;
    }

    public synchronized void put(double Temp1E, double Temp2E, double UmidadeE, double AltitudeE, double PressaoE, double PluvE) { // ENTRADA
        available = true;
        lista.add(new Lista(Temp1E, Temp2E, UmidadeE, AltitudeE, PressaoE, PluvE));
        quant++;
        System.out.println(" PRODUZIU TEMP1: " + lista.get((lista.size() - 1)).Temp1
                + " - TEMP2: " + lista.get((lista.size() - 1)).Temp2 + " - UMID: "
                + lista.get((lista.size() - 1)).Umid + " - ALTITUDE: "
                + lista.get((lista.size() - 1)).Altitude + " - PRESSAO: "
                + lista.get((lista.size() - 1)).Pressao + " - PLUV: "
                + lista.get((lista.size() - 1)).Pluv); // TESTANDO
        notifyAll();
    }
}
