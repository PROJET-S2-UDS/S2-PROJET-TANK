/*
 * Auteurs: Jean-Samuel Lauzon
 * Date: Fevrier 2022
 * Modif : Janvier 2023, Compatible VisualStudio, JpGouin
*/

/*------------------------------ Librairies ---------------------------------*/
#include <iostream>
#include <string>

using namespace std;

/*-------------------------- Librairies externes ----------------------------*/
#include "SerialPort.hpp"
#include "json.hpp"
using json = nlohmann::json;


/*------------------------------ Constantes ---------------------------------*/
#define BAUD 9600           // Frequence de transmission serielle
#define MSG_MAX_SIZE 1024   // Longueur maximale d'un message

#ifndef MANETTE_H
#define MANETTE_H

class lib_manette
{
    /*------------------------- Prototypes de fonctions -------------------------*/
    bool SendToSerial(SerialPort* arduino, json j_msg);
    bool RcvFromSerial(SerialPort* arduino, string& msg);
    void set_accelerometre(double val);
    void set_switch1(bool val);
    void set_switch2(bool val);
    void set_switch3(bool val);
    void set_switch4(bool val);

    void set_Gauche_X(int val);
    void set_Gauche_Y(int val);
public:
    int get_accelerometre();
    bool get_switch1();
    bool get_switch2();
    bool get_switch3();
    bool get_switch4();


    int get_joyStrick_Gauche_X();
    int get_joyStrick_Gauche_Y();



    void modifier_vie(int vie);
    void activer_moteur(bool etat);
    void comm();


    /*---------------------------- Variables globales ---------------------------*/
    SerialPort* arduino; //doit etre un objet global!
    int S1 = 0;
    int S2 = 0;
    int S3 = 0;
    int S4 = 0;

    int accelerometre;
    int PX = 0;
    int PY = 0;
    int aX = 0;
    int aY = 0;
    int aZ = 0;

    int Gauche_X;
    int Gauche_Y;
    int vie = 10;
    bool etat_moteur = false;
    /*----------------------------- Fonction "Main" -----------------------------*/
    lib_manette(bool manetteActive)
    {
        if (manetteActive) {
            string com = "COM4";
            //cout << "Entrer le port de communication du Arduino: ";
            //cin >> com;
            arduino = new SerialPort(com.c_str(), BAUD);

            //const char com = "\\\\.\\COM3";
            //SerialPort arduino = SerialPort("\\\\.\\COM3");
            if (!arduino->isConnected()) {
                cerr << "Impossible de se connecter au port " << string(com) << ". Fermeture du programme!" << endl;
                exit(1);
            }
        }
    }
    string raw_msg;

    // Initialisation du port de communication


    // Structure de donnees JSON pour envoie et reception
    bool led_state = 1;



};
#endif
