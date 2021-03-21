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
    world->set(2, 1, VWALL);
    world->set(3, 1, HWALL);
    world->set(3, 2, VWALL);
    world->set(4, 2, HWALL);
    world->set(4, 3, VWALL);
    world->set(5, 3, HWALL);
    world->set(6, 3, HWALL);
    world->set(6, 3, VWALL);
    world->set(7, 2, HWALL);
    world->set(7, 2, VWALL);
    world->set(8, 1, HWALL);
    world->set(8, 1, VWALL);
    // colocar um marcador no mundo
    world->set(7, 3, BEEPER);
    world->set(8, 2, BEEPER);
    world->set(8, 2, BEEPER);
    world->set(9, 1, BEEPER);
    world->set(9, 1, BEEPER);
    world->set(9, 1, BEEPER);
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

    void stepUpRight()
    {
        while (!facingNorth())
        {
            turnLeft();
        }
        move();
        turnRight();
        move();
    }
    void stepDownRight()
    {
        while (!facingEast())
        {
            turnLeft();
        }
        move();
        turnRight();
        move();
    }
    void stepUpLeft(){
        while (!facingNorth())
        {
            turnLeft();
        }
        move();
        turnLeft();
        move();
    }
    void stepDownLeft(){
        while (!facingWest())
        {
        turnLeft();
        }
        move();
        turnLeft();
        move();
    }
    void doTask(){
        move();
        stepUpRight();
        stepUpRight();
        stepUpRight();
        move();
        stepDownRight();
        pickBeepers();
        stepDownRight();
        pickBeepers();
        stepDownRight();
        pickBeepers();
        stepUpLeft();
        stepUpLeft();
        stepUpLeft();
        move();
        stepDownLeft();
        putBeeper();
        stepDownLeft();
        putBeeper();
        putBeeper();
        stepDownLeft();
        putBeeper();
        putBeeper();
        putBeeper();
        turnRight();
        move();
        turnLeft();
        turnLeft();
        turnOff();
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
    decorateWorld("Guia0211.txt");
    world->show();
    // preparar o ambiente para uso
    world->reset();              // limpar configuracoes
    world->read("Guia0211.txt"); // ler configuracao atual para o ambiente
    world->show();               // mostrar a configuracao atual
    set_Speed(3);                // definir velocidade padrao
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
