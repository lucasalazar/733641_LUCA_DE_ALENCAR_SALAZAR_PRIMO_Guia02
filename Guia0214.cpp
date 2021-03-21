/*
 Guia_0201 - v0.0. - __ / __ / _____
 Author: _____________________
 Para compilar em uma janela de comandos (terminal):

 No Linux : gcc -o Guia0201 ./Guia0201.cpp
 No Windows: gcc -o Guia0201.exe Guia0201.cpp
 Para executar em uma janela de comandos (terminal):

 No Linux : ./Guia0201
 No Windows: Guia0201
*/
// lista de dependencias
#include "karel.hpp"
#include "io.hpp" // para entradas e saídas
// --------------------------- definicoes de metodos
/**
 decorateWorld - Metodo para preparar o cenario.
 @param fileName - nome do arquivo para guardar a descricao.
*/
void decorateWorld(const char *fileName)
{
    // colocar paredes no mundo
    // colocar paredes no mundo
    world->set(2, 3, VWALL);
    world->set(2, 4, VWALL);
    world->set(2, 5, VWALL);
    world->set(2, 6, VWALL);
    world->set(2, 7, VWALL);
    world->set(2, 8, VWALL);
    world->set(3, 3, VWALL);
    world->set(3, 4, VWALL);
    world->set(3, 5, VWALL);
    world->set(3, 6, VWALL);
    world->set(3, 7, VWALL);
    world->set(5, 3, VWALL);
    world->set(5, 4, VWALL);
    world->set(5, 5, VWALL);
    world->set(5, 6, VWALL);
    world->set(5, 7, VWALL);
    world->set(5, 8, VWALL);
    world->set(4, 3, VWALL);
    world->set(4, 4, VWALL);
    world->set(4, 5, VWALL);
    world->set(4, 6, VWALL);
    world->set(4, 7, VWALL);
    world->set(3, 2, HWALL);
    world->set(4, 2, HWALL);
    world->set(5, 2, HWALL);
    world->set(3, 8, HWALL);
    world->set(5, 8, HWALL);

    // colocar um marcador no mundo
    world->set(3, 3, BEEPER);
    world->set(3, 3, BEEPER);
    world->set(3, 3, BEEPER);
    world->set(4, 3, BEEPER);
    world->set(4, 3, BEEPER);
    world->set(4, 3, BEEPER);
    world->set(5, 3, BEEPER);
    world->set(5, 3, BEEPER);
    world->set(5, 3, BEEPER);
    world->set(4, 4, BEEPER);
    world->set(4, 4, BEEPER);
    world->set(5, 4, BEEPER);
    world->set(5, 4, BEEPER);
    world->set(5, 5, BEEPER);
    // salvar a configuracao atual do mundo
    world->save(fileName);
} // decorateWorld ( )
/**
 Classe para definir robo particular (MyRobot),
 a partir do modelo generico (Robot)
 Nota: Todas as definicoes irao valer para qualquer outro robo
 criado a partir dessa nova descricao de modelo.
*/
class MyRobot : public Robot
{
public:
    /**
 turnRight - Procedimento para virar 'a direita.
 */
    void turnRight()
    {
        // definir dado local
        int step = 0;
        // testar se o robo esta' ativo
        if (checkStatus())
        {
            // o agente que executar esse metodo
            // devera' virar tres vezes 'a esquerda
            for (step = 1; step <= 3; step = step + 1)
            {
                turnLeft();
            } // end for
        }     // end if
    }         // end turnRight ( )
    /**
 moveN - Metodo para mover certa quantidade de passos.
 @param steps - passos a serem dados.
 */
    void moveN(int steps)
    {
        // definir dado local
        int step = 0;
        // testar se a quantidade de passos e' maior que zero
        for (step = steps; step > 0; step = step - 1)
        {
            // dar um passo
            move();
        } // end if
    }     // end moveN( )
          /**
 * pickBeepers - Metodo para coletar marcadores.
 */
    int pickBeepers()
    {
        int n = 0;
        // repetir (com teste no inicio)
        // enquanto houver marcador proximo
        while (nextToABeeper())
        {
            // coletar um marcador
            pickBeeper();
            n = n + 1;
        } // end while
        return (n);
    } // end pickBeepers( )

    void putBeepers()
    {
        while (beepersInBag())
        {
            putBeeper();
        }
    }
    /**
    * recordActions - Metodo para mover o robot interativamente
    * e guardar a descricao a tarefa em arquivo
    * @param fileName - nome do arquivo
    */
    void recordActions(const char *fileName)
    {
        //definir dados
        int x = xAvenue(); //obter posicao atual(avenue)
        int y = yStreet(); //obter posicao atual(street)

        //definir arquivo onde gravar comandos
        std::ofstream archive(fileName);

        //testar se opcao valida
        if (nextToABeeper())
        {
            //guardar o comando em arquivo e salta uma linha depois
            archive << x << "\n";
            archive << y << "\n";
        } //end if

        //fechar o arquivo INDISPENSAVEL para a gravacao
        archive.close();
    } //end recordActions()

    /**
    * appendActions - Metodo para acrescentar comandos ao arquivo e traduzi-los
    * @param fileName - nome do arquivo
    */
    void appendActions(const char *fileName)
    {
        //definir dados
        int x = xAvenue(); //obter posicao atual(avenue)
        int y = yStreet(); //obter posicao atual(street)

        //definir arquivo para receber acrescimos ao final
        std::fstream archive(fileName, std::ios::app);

        if (nextToABeeper())
        {
            archive << x << "\n";
            archive << y << "\n";
        } //end if
        archive.close();
    } //end appendActions()

    void doTask()
    {
        move();
        turnLeft();
        moveN(8);
        turnRight();
        moveN(2);
        turnRight();
        move();
        turnLeft();
        move();
        turnRight();
        moveN(3);
        recordActions("Tarefa0214b.txt");
        pickBeepers();
        move();
        appendActions("Tarefa0214b.txt");
        pickBeepers();
        move();
        appendActions("Tarefa0214b.txt");
        pickBeepers();
        turnLeft();
        turnLeft();
        moveN(5);
        turnLeft();
        move();
        turnLeft();
        moveN(4);
        appendActions("Tarefa0214b.txt");
        pickBeepers();
        move();
        appendActions("Tarefa0214b.txt");
        pickBeepers();
        turnLeft();
        turnLeft();
        moveN(5);
        turnLeft();
        move();
        turnLeft();
        moveN(5);
        appendActions("Tarefa0214b.txt");
        pickBeepers();
        turnLeft();
        turnLeft();
        moveN(5);
        turnRight();
        move();
        turnLeft();
        move();
        turnRight();
        moveN(3);
        turnRight();
        moveN(8);
        putBeepers();
        turnRight();
        moveN(6);
        turnLeft();
        turnLeft();
    }
}; // end class MyRobot
/**
 Acao principal: executar a tarefa descrita acima.
*/
int main()
{
    // definir o contexto
    // criar o ambiente e decorar com objetos
    // OBS.: executar pelo menos uma vez,
    // antes de qualquer outra coisa
    // (depois de criado, podera' ser comentado)
    world->create(""); // criar o mundo
    decorateWorld("Guia0214.txt");
    world->show();
    // preparar o ambiente para uso
    world->reset();              // limpar configuracoes
    world->read("Guia0214.txt"); // ler configuracao atual para o ambiente
    world->show();               // mostrar a configuracao atual
    set_Speed(1);                // definir velocidade padrao
                                 // criar robo
    MyRobot *robot = new MyRobot();
    // posicionar robo no ambiente (situacao inicial):
    // posicao(x=1,y=1), voltado para direita, com zero marcadores, nome escolhido )
    robot->create(1, 1, EAST, 0, "Karel");
    // executar tarefa
    robot->doTask();
    // encerrar operacoes no ambiente
    world->close();
    // encerrar programa
    getchar();
    return (0);
} // end main ( )
