
namespace interface_VS
{
    //FERMER ROBOTC AU LANCEMENT
    partial class Form1
    {
        /// <summary>
        /// Variable nécessaire au concepteur.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Nettoyage des ressources utilisées.
        /// </summary>
        /// <param name="disposing">true si les ressources managées doivent être supprimées ; sinon, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Code généré par le Concepteur Windows Form

        /// <summary>
        /// Méthode requise pour la prise en charge du concepteur - ne modifiez pas
        /// le contenu de cette méthode avec l'éditeur de code.
        /// </summary>
        private void InitializeComponent()
        {
            this.btnOpen = new System.Windows.Forms.Button();
            this.btnClose = new System.Windows.Forms.Button();
            this.btnSend = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.cboPort = new System.Windows.Forms.ComboBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.btnReceive = new System.Windows.Forms.Button();
            this.txtData = new System.Windows.Forms.DataGridView();
            this.label5 = new System.Windows.Forms.Label();
            this.txtReceive = new System.Windows.Forms.DataGridView();
            this.txtMessage = new System.Windows.Forms.DataGridView();
            this.cboMsgType = new System.Windows.Forms.ComboBox();
            this.cboReceiver = new System.Windows.Forms.ComboBox();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.txtData)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtReceive)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtMessage)).BeginInit();
            this.SuspendLayout();
            // 
            // btnOpen
            // 
            this.btnOpen.Location = new System.Drawing.Point(332, 18);
            this.btnOpen.Name = "btnOpen";
            this.btnOpen.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.btnOpen.Size = new System.Drawing.Size(75, 31);
            this.btnOpen.TabIndex = 0;
            this.btnOpen.Text = "Open";
            this.btnOpen.UseVisualStyleBackColor = true;
            this.btnOpen.Click += new System.EventHandler(this.btnOpen_Click);
            // 
            // btnClose
            // 
            this.btnClose.Location = new System.Drawing.Point(447, 22);
            this.btnClose.Name = "btnClose";
            this.btnClose.Size = new System.Drawing.Size(75, 31);
            this.btnClose.TabIndex = 1;
            this.btnClose.Text = "Close";
            this.btnClose.UseVisualStyleBackColor = true;
            this.btnClose.Click += new System.EventHandler(this.btnClose_Click);
            // 
            // btnSend
            // 
            this.btnSend.Location = new System.Drawing.Point(87, 82);
            this.btnSend.Name = "btnSend";
            this.btnSend.Size = new System.Drawing.Size(75, 27);
            this.btnSend.TabIndex = 2;
            this.btnSend.Text = "Send";
            this.btnSend.UseVisualStyleBackColor = true;
            this.btnSend.Click += new System.EventHandler(this.btnSend_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(135, 22);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(34, 17);
            this.label2.TabIndex = 4;
            this.label2.Text = "Port";
            // 
            // cboPort
            // 
            this.cboPort.FormattingEnabled = true;
            this.cboPort.Location = new System.Drawing.Point(175, 22);
            this.cboPort.Name = "cboPort";
            this.cboPort.Size = new System.Drawing.Size(131, 24);
            this.cboPort.TabIndex = 5;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(98, 135);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(71, 17);
            this.label3.TabIndex = 8;
            this.label3.Text = "Sent Data";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(124, 327);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(38, 17);
            this.label4.TabIndex = 9;
            this.label4.Text = "Data";
            // 
            // btnReceive
            // 
            this.btnReceive.ForeColor = System.Drawing.Color.Black;
            this.btnReceive.Location = new System.Drawing.Point(87, 205);
            this.btnReceive.Name = "btnReceive";
            this.btnReceive.Size = new System.Drawing.Size(75, 23);
            this.btnReceive.TabIndex = 10;
            this.btnReceive.Text = "Receive";
            this.btnReceive.UseVisualStyleBackColor = true;
            this.btnReceive.Click += new System.EventHandler(this.btnReceive_Click);
            // 
            // txtData
            // 
            this.txtData.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.txtData.Location = new System.Drawing.Point(175, 327);
            this.txtData.Name = "txtData";
            this.txtData.RowHeadersWidth = 51;
            this.txtData.RowTemplate.Height = 24;
            this.txtData.Size = new System.Drawing.Size(347, 131);
            this.txtData.TabIndex = 11;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(95, 256);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(74, 17);
            this.label5.TabIndex = 13;
            this.label5.Text = "Rcvd Data";
            // 
            // txtReceive
            // 
            this.txtReceive.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.txtReceive.Location = new System.Drawing.Point(175, 205);
            this.txtReceive.Name = "txtReceive";
            this.txtReceive.RowHeadersWidth = 51;
            this.txtReceive.RowTemplate.Height = 24;
            this.txtReceive.Size = new System.Drawing.Size(347, 76);
            this.txtReceive.TabIndex = 14;
            // 
            // txtMessage
            // 
            this.txtMessage.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.txtMessage.Location = new System.Drawing.Point(175, 82);
            this.txtMessage.Name = "txtMessage";
            this.txtMessage.RowHeadersWidth = 51;
            this.txtMessage.RowTemplate.Height = 24;
            this.txtMessage.Size = new System.Drawing.Size(347, 83);
            this.txtMessage.TabIndex = 15;
            // 
            // cboMsgType
            // 
            this.cboMsgType.FormattingEnabled = true;
            this.cboMsgType.Location = new System.Drawing.Point(624, 82);
            this.cboMsgType.Name = "cboMsgType";
            this.cboMsgType.Size = new System.Drawing.Size(121, 24);
            this.cboMsgType.TabIndex = 16;
            // 
            // cboReceiver
            // 
            this.cboReceiver.FormattingEnabled = true;
            this.cboReceiver.Location = new System.Drawing.Point(624, 132);
            this.cboReceiver.Name = "cboReceiver";
            this.cboReceiver.Size = new System.Drawing.Size(121, 24);
            this.cboReceiver.TabIndex = 17;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(552, 85);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(66, 17);
            this.label6.TabIndex = 18;
            this.label6.Text = "MsgType";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(555, 134);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(64, 17);
            this.label7.TabIndex = 19;
            this.label7.Text = "Receiver";
            // 
            // Form1
            // 
            this.ClientSize = new System.Drawing.Size(760, 550);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.cboReceiver);
            this.Controls.Add(this.cboMsgType);
            this.Controls.Add(this.txtMessage);
            this.Controls.Add(this.txtReceive);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.txtData);
            this.Controls.Add(this.btnReceive);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.cboPort);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.btnSend);
            this.Controls.Add(this.btnClose);
            this.Controls.Add(this.btnOpen);
            this.Name = "Form1";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.txtData)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtReceive)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtMessage)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox pPort;
        private System.Windows.Forms.TextBox pSend;
        private System.Windows.Forms.TextBox pReceive;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.Button button5;
        private System.Windows.Forms.Button btnOpen;
        private System.Windows.Forms.Button btnClose;
        private System.Windows.Forms.Button btnSend;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox cboPort;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button btnReceive;
        private System.Windows.Forms.DataGridView txtData;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.DataGridView txtReceive;
        private System.Windows.Forms.DataGridView txtMessage;
        private System.Windows.Forms.ComboBox cboMsgType;
        private System.Windows.Forms.ComboBox cboReceiver;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
    }
}

