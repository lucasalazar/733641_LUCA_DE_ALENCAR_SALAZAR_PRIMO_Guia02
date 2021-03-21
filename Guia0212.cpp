/*
 Matricula: 733641
 Author: LUCA DE ALENCAR SALAZAR PRIMO
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
    world->set(2, 8, VWALL);
    world->set(2, 7, VWALL);
    world->set(2, 6, VWALL);
    world->set(2, 4, VWALL);
    world->set(2, 3, VWALL);
    world->set(2, 2, VWALL);
    world->set(7, 8, VWALL);
    world->set(7, 7, VWALL);
    world->set(7, 6, VWALL);
    world->set(7, 4, VWALL);
    world->set(7, 3, VWALL);
    world->set(7, 2, VWALL);
    world->set(5, 5, VWALL);
    world->set(4, 5, VWALL);
    world->set(3, 8, HWALL);
    world->set(4, 8, HWALL);
    world->set(6, 8, HWALL);
    world->set(7, 8, HWALL);
    world->set(5, 6, HWALL);
    world->set(3, 1, HWALL);
    world->set(4, 1, HWALL);
    world->set(6, 1, HWALL);
    world->set(7, 1, HWALL);
    world->set(5, 3, HWALL);
    world->set(3, 4, HWALL);
    world->set(4, 4, HWALL);
    world->set(6, 4, HWALL);
    world->set(7, 4, HWALL);
    world->set(3, 5, HWALL);
    world->set(4, 5, HWALL);
    world->set(6, 5, HWALL);
    world->set(7, 5, HWALL);
    world->set(4, 2, VWALL);
    world->set(4, 3, VWALL);
    world->set(5, 2, VWALL);
    world->set(5, 3, VWALL);
    world->set(4, 8, VWALL);
    world->set(4, 7, VWALL);
    world->set(5, 7, VWALL);
    world->set(5, 8, VWALL);
    // colocar um marcador no mundo
    world->set(5, 3, BEEPER);
    world->set(4, 5, BEEPER);
    world->set(5, 7, BEEPER);
    world->set(6, 5, BEEPER);
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

    
    void doTask(){
        move();
        turnLeft();
        move();
        while (!rightIsClear())
        {
            move();
        }
        turnRight();
        moveN(2);
        pickBeepers();
        turnLeft();
        turnLeft();
        moveN(2);
        turnRight();
        move();
        while (!rightIsClear())
        {
            move();
        }
        turnRight();
        move();
        while (!rightIsClear())
        {
            move();
        }
        turnRight();
        moveN(2);
        pickBeepers();
        turnLeft();
        turnLeft();
        moveN(2);
        turnRight();
        move();
        while (!rightIsClear())
        {
            move();
        }
        turnRight();
        move();
        while (!rightIsClear())
        {
            move();
        }
        turnRight();
        moveN(2);
        pickBeepers();
        turnLeft();
        turnLeft();
        moveN(2);
        turnRight();
        move();
        while (!rightIsClear())
        {
            move();
        }
        turnRight();
        move();
        while (!rightIsClear())
        {
            move();
        }
        turnRight();
        moveN(2);
        pickBeepers();
        turnLeft();
        turnLeft();
        moveN(2);
        turnRight();
        moveN(4);
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
    decorateWorld("Guia0212.txt");
    world->show();
    // preparar o ambiente para uso
    world->reset();              // limpar configuracoes
    world->read("Guia0212.txt"); // ler configuracao atual para o ambiente
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
