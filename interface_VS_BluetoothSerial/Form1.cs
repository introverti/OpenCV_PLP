using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;       //Pour SerialPort

//REFERENCES
// https://www.youtube.com/watch?v=Fer_q9LXDnQ&ab_channel=FoxLearn

//Ajouter un port COM pour le bluetooth
//https://www.youtube.com/watch?v=4ygE_0NlGQ8&ab_channel=tech804
//https://www.youtube.com/watch?v=Fg1dDEjk9UA&ab_channel=AyushJain

namespace interface_VS
{        
    public partial class Form1 : Form
    {
        //create a new Serial Object with default settings
        SerialPort serialPort1 = new SerialPort();
        byte[] RcvData = new byte[16];
        byte [] SentData = new byte [22];
        


        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            string[] ports = SerialPort.GetPortNames(); 
            cboPort.Items.AddRange(ports);
            cboPort.SelectedIndex = 0;
            btnClose.Enabled = false;
            btnSend.Enabled = false;

            //Mise en forme du tableau txtData
            txtData.Columns.Add("parameters", "PARAMETERS");
            txtData.Columns.Add("NXT1","NXT1");
            txtData.Columns.Add("NXT2", "NXT2");
            int n = txtData.Rows.Add();
            txtData.Rows[n].Cells[0].Value = "Distance";
            txtData.Rows[n].Cells[1].Value = 50;
            txtData.Rows[n].Cells[2].Value = 12000;
            n = txtData.Rows.Add();
            txtData.Rows[n].Cells[0].Value = "Beta";
            txtData.Rows[n].Cells[1].Value = 1500;
            txtData.Rows[n].Cells[2].Value = 1200;
            n = txtData.Rows.Add();
            txtData.Rows[n].Cells[0].Value ="QrNum";
            txtData.Rows[n].Cells[1].Value = 300;
            txtData.Rows[n].Cells[2].Value = 4;
            n = txtData.Rows.Add();
            txtData.Rows[n].Cells[0].Value = "Batt.Level";
            txtData.Rows[n].Cells[1].Value = "LOW";
            txtData.Rows[n].Cells[2].Value = "LOW";

            //Mise en forme du tableau txtMessage
            //Colonnes
            for (int j = 0; j < 22; j++)
            {
                txtMessage.Columns.Add("byte", "byte"+j);
            }
            //lignes
            txtMessage.Rows.Add();

            //ComboBoxes
            cboMsgType.Items.Add("Donnees");
            cboMsgType.Items.Add("BattReq");
            cboReceiver.Items.Add("NXT1");
            cboReceiver.Items.Add("NXT2");

            //Mise en forme du tableau txtReceive
            //Colonnes
            txtReceive.Columns.Add("", "");
            for (int j = 0; j < 16; j++)
            {
                txtReceive.Columns.Add("byte", "byte" + j);
            }
            //lignes
            txtReceive.Rows.Add();
        }
        //Connexion Sortant: PC ouvre le port et lance la connexion
        //Si la connexion BT est établie depuis RobotC, l'accès au port peut être interdite.

        //Connexion entrante: Ouvrir le port avant; le robot lance la connexion
        private void btnOpen_Click(object sender, EventArgs e)
        {

            try
            {
                //Allow the user to set the appropriate properties.
                //https://docs.microsoft.com/fr-fr/dotnet/api/system.io.ports.serialport.stopbits?view=dotnet-plat-ext-5.0
                serialPort1.PortName = cboPort.Text;
                serialPort1.BaudRate = 9600;
                serialPort1.Parity=Parity.None;
                serialPort1.DataBits = 8;
                serialPort1.StopBits = StopBits.One;
                serialPort1.Handshake = Handshake.None;  //Handshaking is a low level communication, to control when to send data or not.
                //serialPort1.ReadTimeout = 3000;
                //serialPort1.WriteTimeout = 500;

                serialPort1.Open();
                if (serialPort1.IsOpen)
                {
                    btnSend.Enabled = true;
                    btnOpen.Enabled = false;
                    btnClose.Enabled = true;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Message", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void btnClose_Click(object sender, EventArgs e)
        {
            try
            {
                serialPort1.Close();
                if (!serialPort1.IsOpen)
                {
                    btnSend.Enabled = false;
                    btnOpen.Enabled = true;
                    btnClose.Enabled = false;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Message", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }


        private void btnSend_Click(object sender, EventArgs e)  //attention peut freezer l'application jusqu'à 'écriture
        {
            //fonction Convert.ToInt32 https://docs.microsoft.com/en-us/dotnet/api/system.convert.toint32?view=net-5.0
            //fonction write https://docs.microsoft.com/en-us/dotnet/api/system.io.ports.serialport.write?view=dotnet-plat-ext-5.0
            //20 0 128 9 0 16 à rajouter au début

            try
            {
                int colonne = 0;
                byte receiver=65;
                if (cboReceiver.Text == "NXT1")
                {
                    colonne = 0;
                    receiver = 65;
                }
                if (cboReceiver.Text == "NXT2")
                {
                    colonne = 1;
                    receiver = 66;
                }

                byte MsgType=80;
                if (cboMsgType.Text == "Donnees")
                    MsgType = 80;
                if (cboMsgType.Text == "BattReq")
                    MsgType = 81;

                if (serialPort1.IsOpen)
                {
                    int type = Convert.ToInt32(MsgType); // pour éviter l'erreur "le cast spécifié n'est pas valide"
                    int nxt = Convert.ToInt32(receiver);
                    SentData[0] = 20;
                    SentData[1] = 0;
                    SentData[2] = 128;
                    SentData[3] = 9;
                    SentData[4] = 0;
                    SentData[5] = 16;
                    SentData[6] = (byte)type;
                    SentData[7] = 67;
                    SentData[8] = (byte) nxt;
                    if (type==80) //envoi de donnees
                    {
                        int Dist = Convert.ToInt32(txtData.Rows[0].Cells[colonne + 1].Value);
                        int Beta = Convert.ToInt32(txtData.Rows[1].Cells[colonne + 1].Value);
                        int QR = Convert.ToInt32(txtData.Rows[2].Cells[colonne + 1].Value);
                        SentData[9] = 100;    //DistID
                        SentData[10] = (byte)(Dist >> 8);
                        SentData[11] = (byte)(Dist & 255);
                        SentData[12] = 98;    //BetaID
                        SentData[13] = (byte)(Beta >> 8);
                        SentData[14] = (byte)(Beta & 255);
                        SentData[15] = 113;    //QrID
                        SentData[16] = (byte)(QR >> 8);
                        SentData[17] = (byte)(QR & 255);
                        SentData[18] = 0x00;
                    }
                    else if (type == 81)  //requete d'un niveau de batterie
                    {
                        SentData[9] = 0x00; 
                    }

                    for (int k = 0; k < 16; k++)
                    {
                        txtMessage.Rows[0].Cells[k].Value = SentData[k];
                    }
                    serialPort1.Write(SentData, 0, 22);
                }
            }
             catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Message", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (serialPort1.IsOpen)
                serialPort1.Close();                                               //Fermeture du port à la fermeture de l'application
        }

        private void btnReceive_Click(object sender, EventArgs e)                 //attention peut freezer l'application jusqu'à la lecture
        {
            if (serialPort1.IsOpen)
            {
                try
                {   

                    //string MsgRcv = serialPort1.ReadLine();                 //ne marche pas bien
                    //string MsgRcv = serialPort1.Existing().ToCharArray();   //

                    ////////////////////////////////////////////////////////////premiers octets reçus 20 0 128 9 0 16
                    /////Comment éviter les décalages sur la lecture?
                    int MsgRcv1 = serialPort1.ReadByte();
                    int MsgRcv2 = serialPort1.ReadByte();
                    int MsgRcv3 = serialPort1.ReadByte();
                    int MsgRcv4 = serialPort1.ReadByte();
                    int MsgRcv5 = serialPort1.ReadByte();
                    int MsgRcv6 = serialPort1.ReadByte();
                    while (MsgRcv1 != 20 && MsgRcv2 != 0 && MsgRcv3 != 128 && MsgRcv4 != 9 && MsgRcv5 != 0 && MsgRcv6 != 16) 
                    {
                        MsgRcv1 = serialPort1.ReadByte();
                        MsgRcv2 = serialPort1.ReadByte();
                        MsgRcv3 = serialPort1.ReadByte();
                        MsgRcv4 = serialPort1.ReadByte();
                        MsgRcv5 = serialPort1.ReadByte();
                        MsgRcv6 = serialPort1.ReadByte();
                    }
                    ////////////////////////////////////////////////////////////
                    int MsgRcv = serialPort1.ReadByte();
                    if (MsgRcv != 0) ///////////////////////////////////////////le premier caractère du message (id du type) doit être différent de 0
                    {
                        RcvData[0] = (byte)MsgRcv;
                        txtReceive.Rows[0].Cells[1].Value = (RcvData[0]);
                        for (int k = 1; k < 16; k++)
                        {
                            RcvData[k] = (byte)serialPort1.ReadByte();
                            txtReceive.Rows[0].Cells[k+1].Value = (RcvData[k]);
                        }

                        string Battlvl = "Moyen";
                        if (RcvData[3]==76)
                            Battlvl = "Good";
                        else if (RcvData[3] == 77)
                            Battlvl = "Low";
                        else if (RcvData[3] == 77)
                            Battlvl = "Very_Low";
                        if (RcvData[0] == 87)  //Si reception d'un niveau de batterie
                        {
                            if (RcvData[1] == 65)  // si expéditeur=NXT1
                                txtData.Rows[3].Cells[1].Value = Battlvl;
                            if (RcvData[1] == 66)  // si expéditeur=NXT2
                                txtData.Rows[3].Cells[2].Value = Battlvl;
                        }
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message, "Message", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
        }


    }
}
