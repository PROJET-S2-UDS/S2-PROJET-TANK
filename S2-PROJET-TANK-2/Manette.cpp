#include "Manette.hpp"

/*---------------------------Definition de fonctions ------------------------*/
bool  lib_manette::SendToSerial(SerialPort* arduino, json j_msg) {
    // Return 0 if error
    string msg = j_msg.dump();
    bool ret = arduino->writeSerialPort(msg.c_str(), msg.length());
    return ret;
}

void  lib_manette::comm()
{
    json j_msg_send, j_msg_rcv;



    // Boucle pour tester la communication bidirectionnelle Arduino-PC
    while (true)
    {
        // Envoie message Arduino
        //led_state = !led_state;
        //motorState= !motorState;
        //j_msg_send["ledR1"] = led_state;

        //j_msg_send["ledR2"] = led_state;

        //j_msg_send["ledJ1"] = led_state;

        //j_msg_send["ledJ2"] = led_state;

        //j_msg_send["ledB"] = led_state;



        j_msg_send["vie"] = vie;
        j_msg_send["M"] = etat_moteur;



        if (!SendToSerial(arduino, j_msg_send)) {
            cerr << "Erreur lors de l'envoie du message. " << endl;
        }
        // Reception message Arduino
        j_msg_rcv.clear(); // effacer le message precedent
        if (!RcvFromSerial(arduino, raw_msg)) {
            cerr << "Erreur lors de la reception du message. " << endl;
        }
        // cout << "----------------------" << endl;
         // Impression du message de l'Arduino si valide
        if (raw_msg.size() > 0)
        {
            //cout << "raw_msg: " << raw_msg << endl;  // debug
            // Transfert du message en json
            j_msg_rcv = json::parse(raw_msg);


            if (!j_msg_rcv["S1"].is_null())
            {
                set_switch1(j_msg_rcv["S1"]);
                //cout << "S1" << endl;
                //cout << j_msg_rcv["S1"] << endl;
            }

            if (!j_msg_rcv["S2"].is_null())
            {
                set_switch2(j_msg_rcv["S2"]);
                //cout << "S2" << endl;
                //cout << j_msg_rcv["S2"] << endl;
            }

            if (!j_msg_rcv["S3"].is_null())
            {
                set_switch3(j_msg_rcv["S3"]);
                //cout << "S3" << endl;
                //cout << j_msg_rcv["S3"] << endl;
            }

            if (!j_msg_rcv["S4"].is_null())
            {
                set_switch4(j_msg_rcv["S4"]);
                //cout << "S4" << endl;
                //cout << j_msg_rcv["S4"] << endl;
            }


            if (!j_msg_rcv["jy"].is_null())
            {
                set_Gauche_Y(j_msg_rcv["jy"]);
                //cout << "jy" << endl;
                //cout << j_msg_rcv["jy"] << endl;
            }

            if (!j_msg_rcv["jx"].is_null())
            {
                set_Gauche_X(j_msg_rcv["jx"]);
                //cout << "jx" << endl;
                //cout << j_msg_rcv["jx"] << endl;
            }

            if (!j_msg_rcv["A"].is_null())
            {
                set_accelerometre(j_msg_rcv["A"]);
                //cout << "A" << endl;
                //cout << j_msg_rcv["A"] << endl;
            }

            // aX=j_msg_rcv["aX"];
             //aY=j_msg_rcv["aY"];
             //aZ=j_msg_rcv["aZ"];

            // PX=j_msg_rcv["PX"];
            // PY=j_msg_rcv["PY"];

            //cout << " La valeur de S1:" << S1 << " \n La valeur de S2: " << S2 << endl;
            //cout << " La valeur de S3:" << S3 << " \n La valeur de S4: " << S4 << endl;
            //cout << "Potientiometre X : " << get_joyStrick_Gauche_X() << "\n" << endl;
            //cout << "Potentiometre Y : " << get_joyStrick_Gauche_Y() << "\n" << endl;
            //cout << "AccX : " << aX << "\n" << endl;
            //cout << "AccY : " << aY << "\n" << endl;
            //cout << "AccZ: " << aZ << "\n" << endl;
            //cout << etat_moteur << endl;
            //cout << vie << endl;


            //Changement de l'etat led

        }


        // Bloquer le fil pour environ 1 sec
        Sleep(100); // 1000ms

        S1 = 0;
        S2 = 0;
        S3 = 0;
        S4 = 0;

    }


}


bool  lib_manette::RcvFromSerial(SerialPort* arduino, string& msg) {
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

int  lib_manette::get_accelerometre()
{
    return accelerometre;
}

bool   lib_manette::get_switch1()
{
    return S1;
}

bool   lib_manette::get_switch2()
{
    return S2;
}

bool   lib_manette::get_switch3()
{
    return S3;
}

bool   lib_manette::get_switch4()
{
    return S4;
}


int  lib_manette::get_joyStrick_Gauche_X()
{
    return Gauche_X;
}

int   lib_manette::get_joyStrick_Gauche_Y()
{
    return Gauche_Y;
}



void  lib_manette::set_accelerometre(double val)
{
    double new_val = abs(val);

    if (new_val > 1023)
        accelerometre = 1;
    else
        accelerometre = 0;
}

void   lib_manette::set_switch1(bool val)
{
    S1 = val;
}

void   lib_manette::set_switch2(bool val)
{
    S2 = val;
}
void   lib_manette::set_switch3(bool val)
{
    S3 = val;
}
void   lib_manette::set_switch4(bool val)
{
    S4 = val;
}


void  lib_manette::set_Gauche_X(int val)
{
    Gauche_X = val;
}

void  lib_manette::set_Gauche_Y(int val)
{
    Gauche_Y = val;
}

void  lib_manette::modifier_vie(int nouvelle_vie)
{
    vie = nouvelle_vie;
}

void  lib_manette::activer_moteur(bool nouvelle_etat)
{
    etat_moteur = nouvelle_etat;
}