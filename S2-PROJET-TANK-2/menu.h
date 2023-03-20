#ifndef MENU_JEU_H
#define MENU_JEU_H

#include <string>
#include <vector>

class Menu {
public:
    Menu();
    void show();
    void executeChoice();
    int getChoix();
    void showCommande();
    void setChoix(int m_choix);
private:
    int choix ;
};

#endif // MENU_H
