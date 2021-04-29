
/*
programme pour Nxt1
port=1
mailbox1
*/

//int NumNXT=1;
string Poste_SV="ASPIRE";                          //Bluetooth device :  LAPTOP-S8T41VR6   ASPIRE
int kMainBtStream = 1;
char esclave_actuel=0;                             // change de valeur une fois la connexion etablie

int datas[4][2]={{3,2},{30,20},{1,2},{77,77}};    //stoque toutes les donnes des NXTs

int hThreshold=7000;                               //high threshlod: low battery level
int lThreshold=6300;                               //low threshlod: very low battery level

/*

datas[0][0]= nxt1Dist=1
datas[1][0]= nxt1beta=10

ON MET LES COORDONNEES D'UN Peripherique SUR UNE COLONNE

*/
//maxSizeOfMessage16
ubyte nXmitBuffer[16];                //buffer a envoye
ubyte nRcvBuffer[16];                 //buffer pour la reception

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//lancer la communication par bluetooth
//Se deconnecter du peripherique actuel sauf s'il correspond deja a celui auquel on veut se connecter
//Se connecter
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Disconnect_from_Stream(int stream);                                  // seul le maitre lance l'appairage;

void Connect_with_Slave(int stream,char slave)
{
	if (slave!=esclave_actuel ||nBTCurrentStreamIndex <0)                   //tester si on est deja connecte au peripherique
 {
  Disconnect_from_Stream(stream);
  string slave0;
  if (slave==66)
  	   slave0="NXT2";
  if (slave==67)
  	  slave0=Poste_SV;
  if (slave0==Poste_SV || slave0=="NXT2")       //eviter de se connecter a un peripherique inconnu
  {
	 btConnect(stream,slave0);                    //IMPOSSIBLE si robots deja connectes sur un autre port d'ou la deconnexion realisee juste au-dessus
	 wait10Msec(500);
	 while(nBTCurrentStreamIndex <0)              //regarde s'il y a une connexion etablie
   {
	  nxtDisplayTextLine(1,"Must Connect to");
	  nxtDisplayTextLine(2,"%s",slave0);
	  btConnect(stream,slave0);
	  wait10Msec(500);                           //On attend 5s avant de reessayer
	 }
   eraseDisplay();
   nxtDisplayTextLine(1,"Connected to ");
	 nxtDisplayTextLine(2,"%s",slave0);
	 esclave_actuel=slave;
	 wait10Msec(600);                            //Une fois connecte au peripherique, on laisse a ce dernier le temps d'ecrire sur la mailbox1 du maitre
	 eraseDisplay();
  }
 }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//pour regarder le type du message
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char CheckMsgType()
{
	int nSizeOfMessage = cCmdMessageGetSize(mailbox1);                      //size of the message on top of mailbox1
	cCmdMessageRead(nRcvBuffer, nSizeOfMessage, mailbox1);
	while(nBluetoothCmdStatus!=ioRsltSuccess && nBTCurrentStreamIndex >= 0)
	{
	  cCmdMessageRead(nRcvBuffer, nSizeOfMessage, mailbox1);                // Lis le 1er messgae de la mailbox1
		wait10Msec(10);
	}
	return nRcvBuffer[0];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ENVOI DES BUFFERS
//Tant qu'on est connecte on va essayer d'envoyer
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void sendBuffer()
{
	cCmdMessageWriteToBluetooth(nXmitBuffer,16, mailbox1);                     //envoi du buffer sur le seul port actif BT sending dans la file d'attente mailbox1
	while (nBluetoothCmdStatus!=ioRsltSuccess && nBTCurrentStreamIndex >= 0)
	{
		while(bBTBusy) //attendre que le BT se libere
    {
	    nxtDisplayTextLine(5,"W - BT busy");
		  wait10Msec(10);
		}
		cCmdMessageWriteToBluetooth(nXmitBuffer,16, mailbox1);                   //BT sending
		wait10Msec(10);
	}
	wait10Msec(500);
	eraseDisplay();
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//CREATION ET ENVOIE DES DONNEES; pour l'interface il faut envoyer tout le temps 16 bits meme s'ils sont nuls
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void readDataMsg(int stream,char sender1);

void makeBuffer(int sendMsgType,int stream,char receiver,char sender)
{

  string receiver0;
  if (receiver==66)
    	receiver0="NXT2";
  if (receiver==67)
  	  receiver0=Poste_SV;

  string sender0;
  if (sender==66)
  	  sender0="NXT2";
  if (sender==65)
  	  sender0="NXT1";
  if (sender==67)
  	  sender0=Poste_SV;

  Connect_with_Slave(stream,receiver);                // Se deconnecte du port1 et se reconnecte au nouveau receveur sur le port1

	if (sendMsgType==1)                                  //requete Niveau de Batterie
	{
		nXmitBuffer[0]=81;                                 //ID d'une requete de Batterie
		nXmitBuffer[1]=sender;
		nXmitBuffer[2]=receiver;
		nXmitBuffer[3]=0;
		nXmitBuffer[4]=0;
		nXmitBuffer[5]=0;
		nXmitBuffer[6]=0;
		nXmitBuffer[7]=0;
		nXmitBuffer[8]=0;
		nXmitBuffer[9]=0;
		nXmitBuffer[10]=0;
		nXmitBuffer[11]=0;
		nXmitBuffer[12]=0;
		nXmitBuffer[13]=0;
		nXmitBuffer[14]=0;
		nXmitBuffer[15]=0x00; //end of buffer
		nxtDisplayTextLine(5,"Request Created");
		wait10Msec(200);
    sendBuffer();
	}

	else if (sendMsgType==2)                      //envoie de donnees
	{
		//robot data sending
		char DistID=100;                            // CODE ASCII
		char betaID=98;
		char QrID=113;

		int colonne=0;                              //initialisation
		if (receiver0=="NXT2" && sender0=="NXT1")
			 colonne=0;
		if (receiver0=="NXT2" && sender==67)
		   colonne=1;

		int Dist=datas[0][colonne];           //integer value  of x position of kNxt
		int beta= datas[1][colonne];          //value of beta angle of kNxt
		int Qr=datas[2][colonne];

		nXmitBuffer[0]=80;                                //type of msg ID
		nXmitBuffer[1]=sender;                            //SENDER ID
		nXmitBuffer[2]=receiver;                          //CONTACT ID
		nXmitBuffer[3]=DistID;                            //Dist on 10bits
		nXmitBuffer[4]=(Dist>>8);                         //MSB of Dist
		nXmitBuffer[5]=(Dist & 255);                        //LSB of Dist
		nXmitBuffer[6]=betaID;
		nXmitBuffer[7]=(beta>>8);
		nXmitBuffer[8]=(beta & 255);
		nXmitBuffer[9]=QrID;
		nXmitBuffer[10]=Qr>>4;
		nXmitBuffer[11]=Qr&15;
		nXmitBuffer[12]=0;
		nXmitBuffer[13]=0;
		nXmitBuffer[14]=0;
		nXmitBuffer[15]=0x00;                              //end of buffer
		nxtDisplayTextLine(4,"%s's data buffer",receiver0);
		nxtDisplayTextLine(5,"Dist %f",datas[0][colonne]);
		nxtDisplayTextLine(6,"Beta %f",datas[1][colonne]);
		nxtDisplayTextLine(7,"Qr %f",datas[2][colonne]);
		wait10Msec(300);
		eraseDisplay();
		sendBuffer();
	}

	else if (sendMsgType==3)                           //envoi d'un niveau de batterie
	{
		if (sender==65)
		{
		  //Niveau de batterie actuel
		  if (nAvgBatteryLevel<=hThreshold)//very low or low battery level
	    {
	      if (nAvgBatteryLevel<=lThreshold)
			    {
				    datas[3][0]=78;//very low battery level
		     	}
	     	else
			    {
				    datas[3][0]=77;//low battery level
			    }
	    }
       else // nAvgBatteryLevel>hThreshold
	    {
		    datas[3][0]=76;//batterie OK
	    }
	  }

	  int colonne=0;                              //initialisation
		if (receiver0=="NXT2" && sender0=="NXT1")
			 colonne=0;
		if (receiver==67 && sender0=="NXT1")
		   colonne=0;
		if (receiver==67 && sender0=="NXT2")
		   colonne=1;
		nXmitBuffer[0]=87;
		nXmitBuffer[1]=sender;
		nXmitBuffer[2]=receiver;
		nXmitBuffer[3]=datas[3][colonne];
		nXmitBuffer[5]=0;
		nXmitBuffer[6]=0;
		nXmitBuffer[7]=0;
		nXmitBuffer[8]=0;
		nXmitBuffer[9]=0;
		nXmitBuffer[10]=0;
		nXmitBuffer[11]=0;
		nXmitBuffer[12]=0;
		nXmitBuffer[13]=0;
		nXmitBuffer[14]=0;
		nXmitBuffer[15]=0x00;
		nxtDisplayTextLine(5,"%s BattLvl to %s",sender0);
		nxtDisplayTextLine(6," to %s",receiver0);
		nxtDisplayTextLine(7,"%c",datas[3][colonne]);
		wait10Msec(200);
		eraseDisplay();
    sendBuffer();
  }

  else if (sendMsgType==4)              //ACK batt ID
	{
		nXmitBuffer[0]=73;                  //ACK batt type
		nXmitBuffer[1]=sender;
		nXmitBuffer[2]=receiver;
		nXmitBuffer[3]=0;
		nXmitBuffer[5]=0;
		nXmitBuffer[6]=0;
		nXmitBuffer[7]=0;
		nXmitBuffer[8]=0;
		nXmitBuffer[9]=0;
		nXmitBuffer[10]=0;
		nXmitBuffer[11]=0;
		nXmitBuffer[12]=0;
		nXmitBuffer[13]=0;
		nXmitBuffer[14]=0;                           //Message recu ID
		nXmitBuffer[15]=0x00;
		nxtDisplayTextLine(5,"BattACK for %s",receiver0);
		wait10Msec(200);
		eraseDisplay();
		sendBuffer();
	}

 	wait10Msec(800);

}//end "makeBuffer" function


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//RECEPTION DE MESSAGES

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void readDataMsg(int stream,char sender1)
{
	Connect_with_Slave(stream,sender1);
  nxtDisplayTextLine(1,"Reading");
  wait10Msec(500);
  while(bBTBusy) //laisser le temps  l'expditeur d'envoyer
    {
	    nxtDisplayTextLine(5,"W - BT busy");
		  wait10Msec(100);
		}
	int nSizeOfMessage = cCmdMessageGetSize(mailbox1);            //size of message on top of mailbox20
	cCmdMessageRead(nRcvBuffer, nSizeOfMessage, mailbox1);
	while(nBluetoothCmdStatus!=ioRsltSuccess && nBTCurrentStreamIndex >= 0)
	{
	  cCmdMessageRead(nRcvBuffer, nSizeOfMessage, mailbox1);
		wait10Msec(10);
	}
	char rcvMsgType;
	rcvMsgType = nRcvBuffer[0];                                   //id of the type de msg

	//Determiner le destinataire final

  string sender0;
  string receiver0;
  char receiver=nRcvBuffer[2];
	char sender=nRcvBuffer[1];
  if (sender==66)
  	  sender0="NXT2";
  if (sender==67)
  	  sender0=Poste_SV;

  if (receiver==65)
  	  receiver0="NXT1";
  if (receiver==66)
  	  receiver0="NXT2";
  if (receiver==67)
  	  receiver0=Poste_SV;

if (sender!=65)
{
	  if (rcvMsgType == 80)                                                 //Si Reception de donnees
	  {
		nxtDisplayTextLine(4,"Data From %s",sender0);
		wait10Msec(200);
		//reconstitution of data
		int DIST =((nRcvBuffer[4]<<8)|(nRcvBuffer[5]));
		int BETA =(nRcvBuffer[7]<<8)|(nRcvBuffer[8]);
		int Qr = (nRcvBuffer[10]<<8)|(nRcvBuffer[11]);
		//storage of data
		int colonne=0;  //initialisation
		if (sender0==Poste_SV)
	      {
	      if (receiver==66)  //si destinataire=NXT2
			    colonne=1;
			  if (receiver==65)
			     colonne=0;
	      }
		datas[0][colonne]=DIST;
		datas[1][colonne]=BETA;
    datas[2][colonne]=Qr;

		nxtDisplayTextLine(5,"DIST_%s= %f for %s",sender0,datas[0][colonne],receiver0);
	  nxtDisplayTextLine(6,"BETA_%s= %f for %s",sender0,datas[1][colonne],receiver0);
		nxtDisplayTextLine(7,"Qr_%s= %f for %s",sender0,datas[2][colonne],receiver0);
		wait10Msec(300);
	  if (receiver!=65)
	  {
	    makeBuffer(2,kMainBtStream,receiver,sender);                           //envoyer les donnees au destinataire final
	    nxtDisplayTextLine(5,"%s-Data to",sender0,receiver0);
      wait10Msec(200);
    }
	 }

	 	else if (rcvMsgType == 87)                                                 //Si Reception de niveau de batterie
	  {
		nxtDisplayTextLine(4,"BatteryLvl from %s",sender0);
		wait10Msec(200);
		//reconstitution of data
    char batt=nRcvBuffer[3];
		//storage of data
		int colonne=0;  //initialisation
	  if (sender==66)
			  colonne=1;
		datas[3][colonne]=batt;
		nxtDisplayTextLine(5,"Batt_%s= %f for %s",sender0,datas[3][colonne]);
		nxtDisplayTextLine(6,"for %s",receiver0);
	  if (receiver!=65)
	  {
	    makeBuffer(3,kMainBtStream,receiver,sender);                          //envoyer les donnees au destinataire final
	    nxtDisplayTextLine(5,"%s-Batt to %s",sender0,receiver0);
      wait10Msec(200);
    }
	 }

	 else if (rcvMsgType==82 && receiver==65)                                //request received
	 {
		  nxtDisplayTextLine(5,"%s's DataRequest",sender0);

		  int essais=0;
		  if (sender!=67)  //On ne va pas attendre l'ACK du Poste car il n'en envoie pas                                                    //on attendra l'ACK de l'expediteur que s'il s'agissait d'un robot
		  {
			    while (CheckMsgType()!=71 && essais<5)                           // en attente d'un ACK
		       {
             makeBuffer(2,kMainBtStream,sender,receiver);                  //send data; NXT1 becomes sender
             essais++;
           }
          if (essais==5)
      	       nxtDisplayTextLine(5,"DataACK NON recu");
          else nxtDisplayTextLine(5,"DataACK recu ");
	      	wait10Msec(200);
	    }
   }

  else if (rcvMsgType==81 && receiver==65)                                //request received
	 {
		  nxtDisplayTextLine(5,"%s Requests",sender0);
      nxtDisplayTextLine(6,"%s-BLvl",receiver0);
      wait10Msec(200);
		  int essais=0;
		  if (sender!=67)  //On ne va pas attendre l'ACK du Poste car il n'en envoie pas                                                    //on attendra l'ACK de l'expediteur que s'il s'agissait d'un robot
		  {
			    while (CheckMsgType()!=73 && essais<5)                           // en attente d'un ACK
		       {
             makeBuffer(3,kMainBtStream,sender,receiver);                  //send Battery level; NXT1 becomes sender
             essais++;
           }
          if (essais==5)
      	       nxtDisplayTextLine(5,"BattACK NON recu");
          else nxtDisplayTextLine(5,"BattACK recu ");
	      	wait10Msec(200);
	    }
	    else makeBuffer(3,kMainBtStream,sender,receiver);
    }
   else if (rcvMsgType==81 && receiver!=65)
    {
    	makeBuffer(1,kMainBtStream,receiver,sender);
      nxtDisplayTextLine(5,"%s Requests",sender0);
      nxtDisplayTextLine(6,"%s-Batt",receiver0);
      wait10Msec(200);
    }


	 else if (rcvMsgType==71 && receiver==65)                                //DataACK for NXT1
	 {
		   nxtDisplayTextLine(5,"DataACK received");
		   wait10Msec(200);
	 }
	 	 else if (rcvMsgType==73 && receiver==65)                              //ACK for NXT1
	 {
		   nxtDisplayTextLine(5,"BattACK received");
		   wait10Msec(200);
	 }
	 else
	 {nxtDisplayTextLine(5,"No Id msg known");                              //Message ID unknown or no ID;
    nxtDisplayTextLine(6,"MsgType rcvd: %c",nRcvBuffer[0]);
    nxtDisplayTextLine(7,"sizeOfMessage %d",nSizeOfMessage);
   }
	 wait10Msec(200);
 }
 else nxtDisplayTextLine(5,"MY MESSAGE???");
 wait10Msec(300);
 eraseDisplay();
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Essayer indefiniment de se deconnecter d'un port/stream quand il n'est pas occupe
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Disconnect_from_Stream(int stream)
{
	int essais6=0;
	eraseDisplay();
	nxtDisplayTextLine(1,"Disconnexion");
	while(bBTBusy && essais6<3) //attendre que le BT se libere
  {
	 nxtDisplayTextLine(5,"D - BT busy");
	 essais6++;
	 wait10Msec(10);
	}
	essais6=0;
	btDisconnect(stream);                           // BT_STATE_OFF true si BT OFF (pas de probleme contrairement a BT_STATE_CONNECTED)
	while (nBluetoothCmdStatus!=ioRsltSuccess)
  {
  	while(bBTBusy && essais6<4 )                  //attendre que le BT se libere
     {
	    nxtDisplayTextLine(5,"D - BT busy");
	    wait10Msec(200);
	    eraseDisplay();
	    essais6++;
	   }
  	btDisconnect(stream);
  }
  eraseDisplay();
	nxtDisplayTextLine(1,"Disconnected");
	nxtDisplayTextLine(2,"from stream %d",stream);
	wait10Msec(200);
	eraseDisplay();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//MAIN
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
task main()
{
  eraseDisplay();
  while(nBluetoothState==BT_STATE_OFF)
	{
		nxtDisplayTextLine(1,"BT OFF");
		wait10Msec(200);
		setBluetoothOn();
  }
  nxtDisplayTextLine(1,"BT ON");
  makeBuffer(3,kMainBtStream,67,65);          //envoi son niveau de batterie au PC
  while (1)                                   //boucle infinie
  {
  eraseDisplay();

  readDataMsg(kMainBtStream,67);
	//readDataMsg(kMainBtStream,66);
  //makeBuffer(1,kMainBtStream,66,65) //requete du niveau de batterie de NXT2
  }
	Disconnect_from_Stream(kMainBtStream);
	StopAllTasks();
}
