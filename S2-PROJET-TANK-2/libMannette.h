#pragma once

using namespace std;
#include <iostream>
#include <string>


/*-------------------------- Librairies externes ----------------------------*/
#include "SerialPort.h"
#include "json.hpp"

#ifndef LibMannette_H
#define LibMannette_H

class LibMannette
{
    using json = nlohmann::json;

    /*------------------------------ Constantes ---------------------------------*/
#define BAUD 9600           // Frequence de transmission serielle
#define MSG_MAX_SIZE 1024   // Longueur maximale d'un message

    json j_msg_send, j_msg_rcv;



    /*---------------------------- Variables globales ---------------------------*/
    SerialPort* arduino; //doit etre un objet global!
    /*------------------------- Prototypes de fonctions -------------------------*/

    bool SendToSerial(SerialPort* arduino, json j_msg);
    bool RcvFromSerial(SerialPort* arduino, string& msg);
    void Initialiser_connection(const string nom_port);
    bool reception_Donne();
    bool Tranfere_donne();

    int accelerometre;
    bool switch1;
    bool switch2;
    bool switch3;
    bool switch4;


    int Gauche_X;
    int Gauche_Y;
    int vie = 0;
    bool etat_moteur = false;

    //string Initialiser_connection(const string nom_port);

    void set_accelerometre(double val);
    void set_switch1(bool val);
    void set_switch2(bool val);
    void set_switch3(bool val);
    void set_switch4(bool val);

    void set_Gauche_X(int val);
    void set_Gauche_Y(int val);


public:

    LibMannette(bool manetteActive);
    LibMannette(string nom_port, bool manetteActive);


    int get_accelerometre();
    bool get_switch1();
    bool get_switch2();
    bool get_switch3();
    bool get_switch4();


    int get_joyStrick_Gauche_X();
    int get_joyStrick_Gauche_Y();



    void modifier_vie(int vie);
    void activer_moteur(bool etat);

};

#endif