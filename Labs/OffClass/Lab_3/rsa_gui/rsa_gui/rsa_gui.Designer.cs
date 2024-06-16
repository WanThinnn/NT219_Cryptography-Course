namespace rsa_gui
{
    partial class rsa_gui
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            cbRCVtextFormat = new ComboBox();
            cbCPtextFormat = new ComboBox();
            cbPlaintextFormat = new ComboBox();
            label1 = new Label();
            txbRcv = new TextBox();
            txbCipher = new TextBox();
            txbPlain = new TextBox();
            txbPubKey = new TextBox();
            txbPri = new TextBox();
            btnGenKey = new Button();
            txbKeySize = new TextBox();
            btnDec = new Button();
            btnEnc = new Button();
            btnReadRcv = new Button();
            richTextBox1 = new RichTextBox();
            cbFormat = new ComboBox();
            btnReadCipher = new Button();
            btnReadPlain = new Button();
            btnReadPub = new Button();
            btnRead = new Button();
            SuspendLayout();
            // 
            // cbRCVtextFormat
            // 
            cbRCVtextFormat.DropDownStyle = ComboBoxStyle.DropDownList;
            cbRCVtextFormat.FlatStyle = FlatStyle.Flat;
            cbRCVtextFormat.FormattingEnabled = true;
            cbRCVtextFormat.Items.AddRange(new object[] { "Text", "Base64", "PEM" });
            cbRCVtextFormat.Location = new Point(51, 767);
            cbRCVtextFormat.Name = "cbRCVtextFormat";
            cbRCVtextFormat.Size = new Size(200, 40);
            cbRCVtextFormat.TabIndex = 41;
            // 
            // cbCPtextFormat
            // 
            cbCPtextFormat.DropDownStyle = ComboBoxStyle.DropDownList;
            cbCPtextFormat.FlatStyle = FlatStyle.Flat;
            cbCPtextFormat.FormattingEnabled = true;
            cbCPtextFormat.Items.AddRange(new object[] { "DER", "Base64", "HEX" });
            cbCPtextFormat.Location = new Point(51, 588);
            cbCPtextFormat.Name = "cbCPtextFormat";
            cbCPtextFormat.Size = new Size(200, 40);
            cbCPtextFormat.TabIndex = 40;
            // 
            // cbPlaintextFormat
            // 
            cbPlaintextFormat.DropDownStyle = ComboBoxStyle.DropDownList;
            cbPlaintextFormat.FlatStyle = FlatStyle.Flat;
            cbPlaintextFormat.FormattingEnabled = true;
            cbPlaintextFormat.Items.AddRange(new object[] { "Text", "DER", "Base64", "HEX" });
            cbPlaintextFormat.Location = new Point(51, 398);
            cbPlaintextFormat.Name = "cbPlaintextFormat";
            cbPlaintextFormat.Size = new Size(200, 40);
            cbPlaintextFormat.TabIndex = 39;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Font = new Font("Segoe UI", 9F, FontStyle.Bold, GraphicsUnit.Point, 0);
            label1.Location = new Point(51, 70);
            label1.Name = "label1";
            label1.Size = new Size(151, 32);
            label1.TabIndex = 38;
            label1.Text = "Format Key:";
            // 
            // txbRcv
            // 
            txbRcv.BackColor = Color.White;
            txbRcv.Location = new Point(266, 696);
            txbRcv.Multiline = true;
            txbRcv.Name = "txbRcv";
            txbRcv.ReadOnly = true;
            txbRcv.Size = new Size(428, 111);
            txbRcv.TabIndex = 37;
            // 
            // txbCipher
            // 
            txbCipher.BackColor = Color.White;
            txbCipher.Location = new Point(266, 517);
            txbCipher.Multiline = true;
            txbCipher.Name = "txbCipher";
            txbCipher.ReadOnly = true;
            txbCipher.Size = new Size(428, 111);
            txbCipher.TabIndex = 36;
            // 
            // txbPlain
            // 
            txbPlain.BackColor = Color.White;
            txbPlain.Location = new Point(266, 327);
            txbPlain.Multiline = true;
            txbPlain.Name = "txbPlain";
            txbPlain.ReadOnly = true;
            txbPlain.Size = new Size(428, 111);
            txbPlain.TabIndex = 35;
            // 
            // txbPubKey
            // 
            txbPubKey.BackColor = Color.White;
            txbPubKey.Location = new Point(266, 229);
            txbPubKey.Name = "txbPubKey";
            txbPubKey.ReadOnly = true;
            txbPubKey.Size = new Size(428, 39);
            txbPubKey.TabIndex = 34;
            // 
            // txbPri
            // 
            txbPri.BackColor = Color.White;
            txbPri.Location = new Point(266, 143);
            txbPri.Name = "txbPri";
            txbPri.ReadOnly = true;
            txbPri.Size = new Size(428, 39);
            txbPri.TabIndex = 33;
            // 
            // btnGenKey
            // 
            btnGenKey.BackColor = Color.SteelBlue;
            btnGenKey.Font = new Font("Segoe UI", 9F, FontStyle.Bold, GraphicsUnit.Point, 0);
            btnGenKey.ForeColor = Color.White;
            btnGenKey.Location = new Point(51, 893);
            btnGenKey.Name = "btnGenKey";
            btnGenKey.Size = new Size(200, 46);
            btnGenKey.TabIndex = 32;
            btnGenKey.Text = "Genkey";
            btnGenKey.UseVisualStyleBackColor = false;
            btnGenKey.Click += btnGenKey_Click;
            // 
            // txbKeySize
            // 
            txbKeySize.Location = new Point(494, 68);
            txbKeySize.Name = "txbKeySize";
            txbKeySize.PlaceholderText = "Key Size";
            txbKeySize.Size = new Size(200, 39);
            txbKeySize.TabIndex = 31;
            // 
            // btnDec
            // 
            btnDec.BackColor = Color.SteelBlue;
            btnDec.Font = new Font("Segoe UI", 9F, FontStyle.Bold, GraphicsUnit.Point, 0);
            btnDec.ForeColor = Color.White;
            btnDec.Location = new Point(494, 893);
            btnDec.Name = "btnDec";
            btnDec.Size = new Size(200, 46);
            btnDec.TabIndex = 30;
            btnDec.Text = "Decrypt";
            btnDec.UseVisualStyleBackColor = false;
            btnDec.Click += btnDec_Click;
            // 
            // btnEnc
            // 
            btnEnc.BackColor = Color.SteelBlue;
            btnEnc.Font = new Font("Segoe UI", 9F, FontStyle.Bold, GraphicsUnit.Point, 0);
            btnEnc.ForeColor = Color.White;
            btnEnc.Location = new Point(276, 893);
            btnEnc.Name = "btnEnc";
            btnEnc.Size = new Size(200, 46);
            btnEnc.TabIndex = 29;
            btnEnc.Text = "Encrypt";
            btnEnc.UseVisualStyleBackColor = false;
            btnEnc.Click += btnEnc_Click;
            // 
            // btnReadRcv
            // 
            btnReadRcv.BackColor = Color.SteelBlue;
            btnReadRcv.Font = new Font("Segoe UI", 9F, FontStyle.Bold, GraphicsUnit.Point, 0);
            btnReadRcv.ForeColor = Color.White;
            btnReadRcv.Location = new Point(51, 689);
            btnReadRcv.Name = "btnReadRcv";
            btnReadRcv.Size = new Size(200, 46);
            btnReadRcv.TabIndex = 28;
            btnReadRcv.Text = "Recover File";
            btnReadRcv.UseVisualStyleBackColor = false;
            btnReadRcv.Click += btnReadRcv_Click;
            // 
            // richTextBox1
            // 
            richTextBox1.BorderStyle = BorderStyle.None;
            richTextBox1.Location = new Point(729, 63);
            richTextBox1.Name = "richTextBox1";
            richTextBox1.Size = new Size(642, 876);
            richTextBox1.TabIndex = 27;
            richTextBox1.Text = "";
            // 
            // cbFormat
            // 
            cbFormat.DropDownStyle = ComboBoxStyle.DropDownList;
            cbFormat.FlatStyle = FlatStyle.Flat;
            cbFormat.FormattingEnabled = true;
            cbFormat.Items.AddRange(new object[] { "DER", "Base64", "PEM" });
            cbFormat.Location = new Point(266, 67);
            cbFormat.Name = "cbFormat";
            cbFormat.Size = new Size(200, 40);
            cbFormat.TabIndex = 26;
            // 
            // btnReadCipher
            // 
            btnReadCipher.BackColor = Color.SteelBlue;
            btnReadCipher.Font = new Font("Segoe UI", 9F, FontStyle.Bold, GraphicsUnit.Point, 0);
            btnReadCipher.ForeColor = Color.White;
            btnReadCipher.Location = new Point(51, 513);
            btnReadCipher.Name = "btnReadCipher";
            btnReadCipher.Size = new Size(200, 46);
            btnReadCipher.TabIndex = 25;
            btnReadCipher.Text = "Ciphertext File";
            btnReadCipher.UseVisualStyleBackColor = false;
            btnReadCipher.Click += btnReadCipher_Click;
            // 
            // btnReadPlain
            // 
            btnReadPlain.BackColor = Color.SteelBlue;
            btnReadPlain.Font = new Font("Segoe UI", 9F, FontStyle.Bold, GraphicsUnit.Point, 0);
            btnReadPlain.ForeColor = Color.White;
            btnReadPlain.Location = new Point(51, 327);
            btnReadPlain.Name = "btnReadPlain";
            btnReadPlain.Size = new Size(200, 46);
            btnReadPlain.TabIndex = 24;
            btnReadPlain.Text = "Plaintext File";
            btnReadPlain.UseVisualStyleBackColor = false;
            btnReadPlain.Click += btnReadPlain_Click;
            // 
            // btnReadPub
            // 
            btnReadPub.BackColor = Color.SteelBlue;
            btnReadPub.Font = new Font("Segoe UI", 9F, FontStyle.Bold, GraphicsUnit.Point, 0);
            btnReadPub.ForeColor = Color.White;
            btnReadPub.Location = new Point(51, 225);
            btnReadPub.Name = "btnReadPub";
            btnReadPub.Size = new Size(200, 46);
            btnReadPub.TabIndex = 23;
            btnReadPub.Text = "Public Key File";
            btnReadPub.UseVisualStyleBackColor = false;
            btnReadPub.Click += btnReadPub_Click;
            // 
            // btnRead
            // 
            btnRead.BackColor = Color.SteelBlue;
            btnRead.Font = new Font("Segoe UI", 9F, FontStyle.Bold, GraphicsUnit.Point, 0);
            btnRead.ForeColor = Color.White;
            btnRead.Location = new Point(51, 139);
            btnRead.Name = "btnRead";
            btnRead.Size = new Size(200, 46);
            btnRead.TabIndex = 22;
            btnRead.Text = "Private Key File";
            btnRead.UseVisualStyleBackColor = false;
            btnRead.Click += btnRead_Click;
            // 
            // rsa_gui
            // 
            AutoScaleDimensions = new SizeF(13F, 32F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(1423, 1002);
            Controls.Add(cbRCVtextFormat);
            Controls.Add(cbCPtextFormat);
            Controls.Add(cbPlaintextFormat);
            Controls.Add(label1);
            Controls.Add(txbRcv);
            Controls.Add(txbCipher);
            Controls.Add(txbPlain);
            Controls.Add(txbPubKey);
            Controls.Add(txbPri);
            Controls.Add(btnGenKey);
            Controls.Add(txbKeySize);
            Controls.Add(btnDec);
            Controls.Add(btnEnc);
            Controls.Add(btnReadRcv);
            Controls.Add(richTextBox1);
            Controls.Add(cbFormat);
            Controls.Add(btnReadCipher);
            Controls.Add(btnReadPlain);
            Controls.Add(btnReadPub);
            Controls.Add(btnRead);
            Name = "rsa_gui";
            Text = "RSA Encryption";
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private ComboBox cbRCVtextFormat;
        private ComboBox cbCPtextFormat;
        private ComboBox cbPlaintextFormat;
        private Label label1;
        private TextBox txbRcv;
        private TextBox txbCipher;
        private TextBox txbPlain;
        private TextBox txbPubKey;
        private TextBox txbPri;
        private Button btnGenKey;
        private TextBox txbKeySize;
        private Button btnDec;
        private Button btnEnc;
        private Button btnReadRcv;
        private RichTextBox richTextBox1;
        private ComboBox cbFormat;
        private Button btnReadCipher;
        private Button btnReadPlain;
        private Button btnReadPub;
        private Button btnRead;
    }
}
