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

    void execute(int option)
    {
        // executar a opcao de comando
        switch (option)
        {
        case 0: // terminar
            // nao fazer nada
            break;
        case 1: // virar para a esquerda
            if (leftIsClear())
            {
                turnLeft();
            } // end if
            break;
        case 2: // virar para o sul
            while (!facingSouth())
            {
                turnLeft();
            } // end while
            break;
        case 3: // virar para a direita
            if (rightIsClear())
            {
                turnRight();
            } // end if
            break;
        case 4: // virar para o oeste
            while (!facingWest())
            {
                turnLeft();
            } // end while
            break;
        case 5: // mover
            if (frontIsClear())
            {
                move();
            } // end if
            break;
        case 6: // virar para o leste
            while (!facingEast())
            {
                turnLeft();
            } // end while
            break;
        case 7: // pegar marcador
            if (nextToABeeper())
            {
                pickBeeper();
            } // end if
            break;
        case 8: // virar para o norte
            while (!facingNorth())
            {
                turnLeft();
            } // end while
            break;
        case 9: // colocar marcador
            if (beepersInBag())
            {
                putBeeper();
            } // end if
            break;
        default: // nenhuma das alternativas anteriores
            // comando invalido
            show_Error("ERROR: Invalid command.");
        } // end switch
    }     // end execute( )

    void playActions(const char *fileName)
    {
        // definir dados
        int action;
        // definir arquivos de onde ler dados
        std::ifstream archive(fileName);
        // repetir enquanto houver dados
        archive >> action;     // tentar ler a primeira linha
        while (!archive.eof()) // testar se nao encontrado o fim
        {
            // mostrar mais um comando
            IO_print(IO_toString(action));
            delay(stepDelay);
            // executar mais um comando
            execute(action);
            // tentar ler a proxima linha
            archive >> action; // tentar ler a primeira linha
        }                      // end for
        // fechar o arquivo
        // RECOMENDAVEL para a leitura
        archive.close();
    } // end playActions ( )
};    // end class MyRobot
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
    decorateWorld("Guia0215.txt");
    world->show();
    // preparar o ambiente para uso
    world->reset();              // limpar configuracoes
    world->read("Guia0215.txt"); // ler configuracao atual para o ambiente
    world->show();               // mostrar a configuracao atual
    set_Speed(1);                // definir velocidade padrao
                                 // criar robo
    MyRobot *robot = new MyRobot();
    // posicionar robo no ambiente (situacao inicial):
    // posicao(x=1,y=1), voltado para direita, com zero marcadores, nome escolhido )
    robot->create(1, 1, EAST, 0, "Karel");
    robot->playActions("Tarefa0215.txt");
    // encerrar operacoes no ambiente
    world->close();
    // encerrar programa
    getchar();
    return (0);
} // end main ( )
