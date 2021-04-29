/*
	while (nBluetoothCmdStatus!=ioRsltSuccess)   // tant que la derniere commande n'est pas realisee (ici btConnect(stream,slave); )
	                                             // eviter de stoquer le resultat de nBluetoothCmdStatus dans un TFileIOResult
	  	                                         //car le resultat peut rester egal a ioRsltInProgress
	                                             //crash si robots deja connectes sur un autre port

	probleme avec nBluetoothState==BT_STATE_CONNECTED (des fois il prend l'etat inverse)
*/

/*
programme pour Nxt2
port=1
mailbox1
*/

//int NumNXT=2;
int    kMainBtStream =1;
string NameNXT="NXT2";                //PC  ou "NXT2"
string Poste_SV="ASPIRE";             //Bluetooth device


int datas[4][2]={{4,2},{40,20},{5,2},{77,77}};//stoque les donnes des NXT

int hThreshold=7000;//high threshlod: low battery level
int lThreshold=6300; //low threshlod: very low battery level


/*

datas[0][0]= nxt1Dist=1
datas[1][0]= nxt1beta=7

ON MET LES COORDONNEES D'UN Peripherique SUR UNE COLONNE

*/

ubyte nXmitBuffer[16];                //buffer a envoye
ubyte nRcvBuffer[16];                 //buffer pour la reception
//char rcvMsgType;                    //ID du message recu
//maxSizeOfMessage16
//pour la reconstruction des donnees necessitant 2 octets


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//pour regarder le type du message
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char CheckMsgType()
{
	int nSizeOfMessage = cCmdMessageGetSize(mailbox1);            //size of message on top of mailbox20
	cCmdMessageRead(nRcvBuffer, nSizeOfMessage, mailbox1);
	while(nBluetoothCmdStatus!=ioRsltSuccess && nBTCurrentStreamIndex >= 0)
	{
	  cCmdMessageRead(nRcvBuffer, nSizeOfMessage, mailbox1);
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
	cCmdMessageWriteToBluetooth(nXmitBuffer,16, mailbox1);//BT sending
	while (nBluetoothCmdStatus!=ioRsltSuccess && nBTCurrentStreamIndex >= 0)
	{
		while(bBTBusy) //attendre que le BT se libere
    {
	    nxtDisplayTextLine(5,"Write-BT busy");
		  wait10Msec(10);
		}
		cCmdMessageWriteToBluetooth(nXmitBuffer,16, mailbox1);//BT sending
		wait10Msec(10);
	}
	eraseDisplay();
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//CREATION ET ENVOIE DES DONNEES
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char readDataMsg(int stream);

void makeBuffer(int sendMsgType,int stream,char receiver)
{
  string receiver0;
  if (receiver==65)
    	receiver0="NXT1";
  if (receiver==67)
  	  receiver0=Poste_SV;

	if (sendMsgType==1)                                   //requete de donnees
	{
		nXmitBuffer[0]=82;                                  //ID d'une requete
		nXmitBuffer[1]=66;                                  //NXT2 is the sender
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
		nXmitBuffer[15]=0x00;                             //end of buffer
		nxtDisplayTextLine(5,"Request %s-Data",receiver0);
		wait10Msec(200);
    sendBuffer();
	}

		if (sendMsgType==2)                                  //requete Niveau de batterie
	{
		char RequBattID=81;
		nXmitBuffer[0]=RequBattID;                                  //ID d'une requete
		nXmitBuffer[1]=66;                                  //NXT2 is the sender
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
		nXmitBuffer[15]=0x00;                             //end of buffer
		nxtDisplayTextLine(5,"Request %s-Batt",receiver0);
		wait10Msec(200);
    sendBuffer();
	}

	else if (sendMsgType==3)                            //Niveau de batterie
	{
				//Niveau de batterie actuel
		if (nAvgBatteryLevel<=hThreshold)//very low or low battery level
	   {
	      if (nAvgBatteryLevel<=lThreshold)
			    {
				    datas[3][1]=78;//very low battery level
		     	}
	     	else
			    {
				    datas[3][1]=77;//low battery level
			    }
	    }
    else // nAvgBatteryLevel>hThreshold
	    {
		    datas[3][1]=76;//batterie OK
	    }
		char BattID=87;
		nXmitBuffer[0]=BattID;
		nXmitBuffer[1]=66;
		nXmitBuffer[2]=receiver;
		nXmitBuffer[3]=datas[3][1];
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
		nxtDisplayTextLine(5,"Batt Lvl to %s",receiver0);
		nxtDisplayTextLine(6,"%c",datas[3][1]);
		wait10Msec(200);
		eraseDisplay();
    sendBuffer();
	}

  else if (sendMsgType==4)                      //ACK batterie ID
	{
		char ACKidB=73;
		nXmitBuffer[0]=ACKidB;
		nXmitBuffer[1]=66;
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
		nXmitBuffer[14]=0;
		nXmitBuffer[15]=0x00;
		nxtDisplayTextLine(5,"BattACK for %s",receiver0);
		wait10Msec(200);
		eraseDisplay();
    sendBuffer();
	}

  else if (sendMsgType==5)                       //ACK donnees ID
	{
		char ACKidD=71;
		nXmitBuffer[0]=ACKidD;
		nXmitBuffer[1]=66;
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
		nxtDisplayTextLine(5,"DataACK for %s",receiver0);
		wait10Msec(200);
		eraseDisplay();
    sendBuffer();
	}
  wait10Msec(500);

}//end "makeBuffer" function


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////RECEPTION DE MESSAGES
//
//En sortie de la fonction on a un char corresondant au type du message.
////////(((Cette sortie permettra aux expediteurs de donnees de savoir s'il y a bien eu recetion [reception de ACK en retour])))
//La lecture des messages ne peut se faire qu'une fois la connexion etablie et le bluetooth innocupe
///////ATTENTION A NE PAS SE DECONNECTER PENDANT LA LECTURE
//Si le message correpond a un ENVOI de donnees
///////L'esclave reconstitue les donnees en operant sur les bits et les stocke dans la colonne de datas corresondant a l'expediteur
/////// Si l'expediteur est le Poste de SV, il les stocke dans sa propre colonne
///////Ensuite il envoie un ACK a l'expediteur initial (excepte le poste de supervision)
//Si le message correspond a une REQUETE de donnees il repond
//Si le message correspond a un ACK il affiche juste que ses donnees ont ete recues
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char readDataMsg(int stream)
{
  nxtDisplayTextLine(1,"Reading");
  wait10Msec(500);
	int nSizeOfMessage = cCmdMessageGetSize(mailbox1);            //size of message on top of mailbox1
	cCmdMessageRead(nRcvBuffer, nSizeOfMessage, mailbox1);
  while (nBluetoothCmdStatus!=ioRsltSuccess && nBTCurrentStreamIndex >= 0)
	{
	  cCmdMessageRead(nRcvBuffer, nSizeOfMessage, mailbox1);
		wait10Msec(10);
	}

	char rcvMsgType;
	rcvMsgType = nRcvBuffer[0];                                   //id of the type de msg, pb si pas de message

  string sender0;
	char sender=nRcvBuffer[1];
  if (sender==65)
  	  sender0="NXT1";
  if (sender==67)
  	  sender0=Poste_SV;

if (sender!=66)                                                //eviter qu'il n'essaie de se repondre a lui-meme, on ne sait pas s'il peut lire ses propres messages
{
	if (rcvMsgType == 80) //Si Reception de donnees
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
			 colonne=1;
		if (sender0=="NXT1")
			colonne=0;
		datas[0][colonne]=DIST;
		datas[1][colonne]=BETA;
		datas[2][colonne]=Qr;
		nxtDisplayTextLine(5,"DISTread =%f",datas[0][colonne]);
		nxtDisplayTextLine(6,"BETAread = %f",datas[1][colonne]);
		nxtDisplayTextLine(7,"QrNUMread= %d",datas[2][colonne]);
		wait10Msec(200);
		if (sender!=67)
		  makeBuffer(5,kMainBtStream,sender);                              //envoi de l'ACK sauf si expediteur=poste_SV, NXT2 devient expediteur
	}//end of data storage

	else if (rcvMsgType==81)                                             //request received for Battery Level
	{
		nxtDisplayTextLine(5,"%s Requests",sender0);
    nxtDisplayTextLine(6,"NXT2-BattLvl");
    wait10Msec(200);
		int essais=0;
		  if (sender!=67)  //On ne va pas attendre l'ACK du Poste car il n'en envoie pas                                                    //on attendra l'ACK de l'expediteur que s'il s'agissait d'un robot
		  {
			    while (CheckMsgType()!=73 && essais<5)                           // en attente d'un ACK
		       {
             makeBuffer(2,kMainBtStream,sender);                  //send Battery level; NXT1 becomes sender
             essais++;
           }
          if (essais==5)
      	       nxtDisplayTextLine(5,"BattACK NON recu");
          else nxtDisplayTextLine(5,"BattACK recu ");
	      	wait10Msec(200);
	    }
	    else makeBuffer(3,kMainBtStream,sender);
	}

	else if (rcvMsgType==87)                                             //Battery Level Received
	{
		int colonne=0;
		if (sender0=="NXT1")
			colonne=0;
	  datas[3][colonne]=nRcvBuffer[3];
	  nxtDisplayTextLine(5,"%s-BattLvl-%c",sender0,datas[3][colonne]);
		wait10Msec(200);
		if (sender!=67)
		 makeBuffer(4,kMainBtStream,sender);                                //envoi de l'ACK sauf si expediteur=poste_SV, NXT2 devient expediteur
  }


	else if (rcvMsgType==73)
	{
		nxtDisplayTextLine(5,"%s-BattACK",sender0);
		wait10Msec(200);
	}
	else nxtDisplayTextLine(5,"No Id msg known");                          //Message ID unknown or no ID
  wait10Msec(200);
	return rcvMsgType;
 }
 else
 {nxtDisplayTextLine(5,"MY MESSAGE???");                                  //On ne sait pas si cela est possible
  wait10Msec(200);
  return 0;}
  wait10Msec(500);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//MAIN
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

task main()
{
  eraseDisplay();
  while(nBluetoothState==BT_STATE_OFF)                     // BT_STATE_OFF true si BT OFF (pas de probleme contrairement a BT_STATE_CONNECTED)
	{
		nxtDisplayTextLine(1,"BT OFF");
		wait10Msec(200);
		setBluetoothOn();
  }
  nxtDisplayTextLine(1,"BT ON");
  wait10Msec(200);
  eraseDisplay();
  while (nBTCurrentStreamIndex<0)
  	wait10Msec(200);
  nxtDisplayTextLine(5,"First MsgType: %c",readDataMsg(kMainBtStream));                  //NXT2 verifie d'abord s'il n'a pas un message en attente
  wait10Msec(100);
  while (1)                                                                              //boucle infinie
  {
   eraseDisplay();
   if (nBTCurrentStreamIndex>= 0)
   {
    //makeBuffer(2,kMainBtStream,65);                                                     // testNXT2 envoie une Battrequete a NXT1 qui devra lui repondre
    eraseDisplay();
    readDataMsg(kMainBtStream);
   }
  }
	StopAllTasks();
}
