

/**
 *
 * @author LEANDRO
 */
public class Buffer_main {

    public static void main(String[] args) {

        syn_Valores c = new syn_Valores();

        Entrada comArd = new Entrada(c); // INICIANDO CONEXAO SERIAL
        comArd.initialize();
        Saida c1 = new Saida(c, 1);

        comArd.t.start();
        c1.start();
    }
}
