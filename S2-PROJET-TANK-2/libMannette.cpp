#include "libMannette.h"

LibMannette::LibMannette(bool manetteActive)
{
    if (manetteActive) {
        Initialiser_connection("COM5");
    }
}

LibMannette::LibMannette(string nom_port, bool manetteActive)
{
    if (manetteActive) {
        Initialiser_connection(nom_port);
    }

}

void LibMannette::Initialiser_connection(const string nom_port)
{
    string raw_msg;

    // Initialisation du port de communication
   /*

    cout << "Entrer le port de communication du Arduino: ";
    cin >> com;
    �*/
    string com;
    com = nom_port;
    arduino = new SerialPort(com.c_str(), BAUD);

    //const char com = "\\\\.\\COM3";
    //SerialPort arduino = SerialPort("\\\\.\\COM3");
    if (!arduino->isConnected()) {
        cerr << "Impossible de se connecter au port " << string(com) << ". Fermeture du programme!" << endl;
        exit(1);
    }
    Tranfere_donne();
}

bool LibMannette::Tranfere_donne()
{

    string raw_msg;

    while (true)
    {
        cout << "debut de la boucle" << endl;
        j_msg_send["vie"] = vie;
        j_msg_send["etat_moteur"] = etat_moteur;

        if (!SendToSerial(arduino, j_msg_send)) {
            cerr << "Erreur lors de l'envoie du message. " << endl;
        }
        j_msg_rcv.clear(); // effacer le message precedent

        if (!RcvFromSerial(arduino, raw_msg)) {
            cerr << "Erreur lors de la reception du message. " << endl;
        }

        cout << "----------------------" << endl;

        if (raw_msg.size() > 0)
        {
            //cout << "raw_msg: " << raw_msg << endl;  // debug
            // Transfert du message en json
            j_msg_rcv = json::parse(raw_msg);


            if (!j_msg_rcv["S1"].is_null())
            {
                set_switch1(j_msg_rcv["S1"]);
                cout << "S1" << endl;
                cout << j_msg_rcv["S1"] << endl;

            }
            else
            {
                set_switch1(false);
            }

            if (!j_msg_rcv["S2"].is_null())
            {
                set_switch2(j_msg_rcv["S2"]);
                cout << "S2" << endl;
                cout << j_msg_rcv["S2"] << endl;
            }
            else
            {
                set_switch2(false);
            }

            if (!j_msg_rcv["S3"].is_null())
            {
                set_switch3(j_msg_rcv["S3"]);
                cout << "S3" << endl;
                cout << j_msg_rcv["S3"] << endl;
            }
            else
            {
                set_switch3(false);
            }

            if (!j_msg_rcv["S4"].is_null())
            {
                set_switch4(j_msg_rcv["S4"]);
                cout << "S4" << endl;
                cout << j_msg_rcv["S4"] << endl;
            }
            else
            {
                set_switch4(false);
            }

            if (!j_msg_rcv["jy"].is_null())
            {
                set_Gauche_Y(j_msg_rcv["jy"]);
                cout << "jy" << endl;
                cout << j_msg_rcv["jy"] << endl;
            }

            if (!j_msg_rcv["jx"].is_null())
            {
                set_Gauche_X(j_msg_rcv["jx"]);
                cout << "jx" << endl;
                cout << j_msg_rcv["jx"] << endl;
            }

            if (!j_msg_rcv["A"].is_null())
            {
                set_accelerometre(j_msg_rcv["A"]);
                cout << "A" << endl;
                cout << j_msg_rcv["A"] << endl;
            }


        }
    }


    Sleep(50);

    return 0;
}



int LibMannette::get_accelerometre()
{
    return accelerometre;
}
bool  LibMannette::get_switch1()
{
    return switch1;
}
bool  LibMannette::get_switch2()
{
    return switch2;
}
bool  LibMannette::get_switch3()
{
    return switch3;
}
bool  LibMannette::get_switch4()
{
    return switch4;
}


int LibMannette::get_joyStrick_Gauche_X()
{
    return Gauche_X;
}

int LibMannette::get_joyStrick_Gauche_Y()
{
    return Gauche_Y;
}



void LibMannette::set_accelerometre(double val)
{
    double new_val = abs(val);

    if (new_val > 1023)
        accelerometre = 1;
    else
        accelerometre = 0;
}

void  LibMannette::set_switch1(bool val)
{
    switch1 = val;
}
void  LibMannette::set_switch2(bool val)
{
    switch2 = val;
}
void  LibMannette::set_switch3(bool val)
{
    switch3 = val;
}
void  LibMannette::set_switch4(bool val)
{
    switch4 = val;
}


void LibMannette::set_Gauche_X(int val)
{
    Gauche_X = val;
}

void LibMannette::set_Gauche_Y(int val)
{
    Gauche_Y = val;
}

void LibMannette::modifier_vie(int nouvelle_vie)
{
    vie = nouvelle_vie;
}

void LibMannette::activer_moteur(bool nouvelle_etat)
{
    etat_moteur = nouvelle_etat;
}

/*---------------------------Definition de fonctions ------------------------*/
bool LibMannette::SendToSerial(SerialPort* arduino, json j_msg) {
    // Return 0 if error
    string msg = j_msg.dump();
    bool ret = arduino->writeSerialPort(msg.c_str(), msg.length());
    return ret;
}


bool LibMannette::RcvFromSerial(SerialPort* arduino, string& msg) {
    // Return 0 if error
    // Message output in msg
    string str_buffer;
    char char_buffer[MSG_MAX_SIZE];
    int buffer_size;

    msg.clear(); // clear string
    // Read serialport until '\n' character (Blocking)

    // Version fonctionnel dans VScode, mais non fonctionnel avec Visual Studio
/*
    while(msg.back()!='\n'){
        if(msg.size()>MSG_MAX_SIZE){
            return false;
        }

        buffer_size = arduino->readSerialPort(char_buffer, MSG_MAX_SIZE);
        str_buffer.assign(char_buffer, buffer_size);
        msg.append(str_buffer);
    }
*/

// Version fonctionnelle dans VScode et Visual Studio
    buffer_size = arduino->readSerialPort(char_buffer, MSG_MAX_SIZE);
    str_buffer.assign(char_buffer, buffer_size);
    msg.append(str_buffer);

    //msg.pop_back(); //remove '/n' from string

    return true;
}
