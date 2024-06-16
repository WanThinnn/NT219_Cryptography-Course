namespace des_gui_c_
{
    partial class DES
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
            btnRead = new Button();
            cbFormat = new ComboBox();
            txbPri = new TextBox();
            cbRCVtextFormat = new ComboBox();
            cbCPtextFormat = new ComboBox();
            cbPlaintextFormat = new ComboBox();
            txbRcv = new TextBox();
            txbCipher = new TextBox();
            txbPlain = new TextBox();
            btnReadRcv = new Button();
            btnReadCipher = new Button();
            btnReadPlain = new Button();
            richTextBox1 = new RichTextBox();
            btnGenKey = new Button();
            btnDec = new Button();
            btnEnc = new Button();
            cbMode = new ComboBox();
            btnMode = new Button();
            SuspendLayout();
            // 
            // btnRead
            // 
            btnRead.BackColor = Color.SteelBlue;
            btnRead.Font = new Font("Segoe UI", 9F, FontStyle.Bold, GraphicsUnit.Point, 0);
            btnRead.ForeColor = Color.White;
            btnRead.Location = new Point(53, 196);
            btnRead.Name = "btnRead";
            btnRead.Size = new Size(200, 46);
            btnRead.TabIndex = 2;
            btnRead.Text = "Private Key File";
            btnRead.UseVisualStyleBackColor = false;
            btnRead.Click += btnRead_Click;
            // 
            // cbFormat
            // 
            cbFormat.DropDownStyle = ComboBoxStyle.DropDownList;
            cbFormat.FlatStyle = FlatStyle.Flat;
            cbFormat.FormattingEnabled = true;
            cbFormat.Items.AddRange(new object[] { "DER", "Base64", "HEX" });
            cbFormat.Location = new Point(53, 252);
            cbFormat.Name = "cbFormat";
            cbFormat.Size = new Size(200, 40);
            cbFormat.TabIndex = 19;
            // 
            // txbPri
            // 
            txbPri.BackColor = Color.White;
            txbPri.Location = new Point(268, 196);
            txbPri.Multiline = true;
            txbPri.Name = "txbPri";
            txbPri.ReadOnly = true;
            txbPri.Size = new Size(428, 96);
            txbPri.TabIndex = 22;
            // 
            // cbRCVtextFormat
            // 
            cbRCVtextFormat.DropDownStyle = ComboBoxStyle.DropDownList;
            cbRCVtextFormat.FlatStyle = FlatStyle.Flat;
            cbRCVtextFormat.FormattingEnabled = true;
            cbRCVtextFormat.Items.AddRange(new object[] { "Text", "Base64", "PEM" });
            cbRCVtextFormat.Location = new Point(53, 792);
            cbRCVtextFormat.Name = "cbRCVtextFormat";
            cbRCVtextFormat.Size = new Size(200, 40);
            cbRCVtextFormat.TabIndex = 32;
            // 
            // cbCPtextFormat
            // 
            cbCPtextFormat.DropDownStyle = ComboBoxStyle.DropDownList;
            cbCPtextFormat.FlatStyle = FlatStyle.Flat;
            cbCPtextFormat.FormattingEnabled = true;
            cbCPtextFormat.Items.AddRange(new object[] { "DER", "Base64", "HEX" });
            cbCPtextFormat.Location = new Point(53, 613);
            cbCPtextFormat.Name = "cbCPtextFormat";
            cbCPtextFormat.Size = new Size(200, 40);
            cbCPtextFormat.TabIndex = 31;
            // 
            // cbPlaintextFormat
            // 
            cbPlaintextFormat.DropDownStyle = ComboBoxStyle.DropDownList;
            cbPlaintextFormat.FlatStyle = FlatStyle.Flat;
            cbPlaintextFormat.FormattingEnabled = true;
            cbPlaintextFormat.Items.AddRange(new object[] { "Text", "DER", "Base64", "HEX" });
            cbPlaintextFormat.Location = new Point(53, 423);
            cbPlaintextFormat.Name = "cbPlaintextFormat";
            cbPlaintextFormat.Size = new Size(200, 40);
            cbPlaintextFormat.TabIndex = 30;
            // 
            // txbRcv
            // 
            txbRcv.BackColor = Color.White;
            txbRcv.Location = new Point(268, 721);
            txbRcv.Multiline = true;
            txbRcv.Name = "txbRcv";
            txbRcv.ReadOnly = true;
            txbRcv.Size = new Size(428, 111);
            txbRcv.TabIndex = 29;
            // 
            // txbCipher
            // 
            txbCipher.BackColor = Color.White;
            txbCipher.Location = new Point(268, 542);
            txbCipher.Multiline = true;
            txbCipher.Name = "txbCipher";
            txbCipher.ReadOnly = true;
            txbCipher.Size = new Size(428, 111);
            txbCipher.TabIndex = 28;
            // 
            // txbPlain
            // 
            txbPlain.BackColor = Color.White;
            txbPlain.Location = new Point(268, 352);
            txbPlain.Multiline = true;
            txbPlain.Name = "txbPlain";
            txbPlain.ReadOnly = true;
            txbPlain.Size = new Size(428, 111);
            txbPlain.TabIndex = 27;
            // 
            // btnReadRcv
            // 
            btnReadRcv.BackColor = Color.SteelBlue;
            btnReadRcv.Font = new Font("Segoe UI", 9F, FontStyle.Bold, GraphicsUnit.Point, 0);
            btnReadRcv.ForeColor = Color.White;
            btnReadRcv.Location = new Point(53, 714);
            btnReadRcv.Name = "btnReadRcv";
            btnReadRcv.Size = new Size(200, 46);
            btnReadRcv.TabIndex = 26;
            btnReadRcv.Text = "Recover File";
            btnReadRcv.UseVisualStyleBackColor = false;
            btnReadRcv.Click += btnReadRcv_Click;
            // 
            // btnReadCipher
            // 
            btnReadCipher.BackColor = Color.SteelBlue;
            btnReadCipher.Font = new Font("Segoe UI", 9F, FontStyle.Bold, GraphicsUnit.Point, 0);
            btnReadCipher.ForeColor = Color.White;
            btnReadCipher.Location = new Point(53, 538);
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
            btnReadPlain.Location = new Point(53, 352);
            btnReadPlain.Name = "btnReadPlain";
            btnReadPlain.Size = new Size(200, 46);
            btnReadPlain.TabIndex = 24;
            btnReadPlain.Text = "Plaintext File";
            btnReadPlain.UseVisualStyleBackColor = false;
            btnReadPlain.Click += btnReadPlain_Click;
            // 
            // richTextBox1
            // 
            richTextBox1.BorderStyle = BorderStyle.None;
            richTextBox1.Location = new Point(736, 82);
            richTextBox1.Name = "richTextBox1";
            richTextBox1.Size = new Size(642, 854);
            richTextBox1.TabIndex = 33;
            richTextBox1.Text = "";
            // 
            // btnGenKey
            // 
            btnGenKey.BackColor = Color.SteelBlue;
            btnGenKey.Font = new Font("Segoe UI", 9F, FontStyle.Bold, GraphicsUnit.Point, 0);
            btnGenKey.ForeColor = Color.White;
            btnGenKey.Location = new Point(56, 890);
            btnGenKey.Name = "btnGenKey";
            btnGenKey.Size = new Size(200, 46);
            btnGenKey.TabIndex = 36;
            btnGenKey.Text = "Genkey";
            btnGenKey.UseVisualStyleBackColor = false;
            btnGenKey.Click += btnGenKey_Click;
            // 
            // btnDec
            // 
            btnDec.BackColor = Color.SteelBlue;
            btnDec.Font = new Font("Segoe UI", 9F, FontStyle.Bold, GraphicsUnit.Point, 0);
            btnDec.ForeColor = Color.White;
            btnDec.Location = new Point(499, 890);
            btnDec.Name = "btnDec";
            btnDec.Size = new Size(200, 46);
            btnDec.TabIndex = 35;
            btnDec.Text = "Decrypt";
            btnDec.UseVisualStyleBackColor = false;
            btnDec.Click += btnDec_Click;
            // 
            // btnEnc
            // 
            btnEnc.BackColor = Color.SteelBlue;
            btnEnc.Font = new Font("Segoe UI", 9F, FontStyle.Bold, GraphicsUnit.Point, 0);
            btnEnc.ForeColor = Color.White;
            btnEnc.Location = new Point(281, 890);
            btnEnc.Name = "btnEnc";
            btnEnc.Size = new Size(200, 46);
            btnEnc.TabIndex = 34;
            btnEnc.Text = "Encrypt";
            btnEnc.UseVisualStyleBackColor = false;
            btnEnc.Click += btnEnc_Click;
            // 
            // cbMode
            // 
            cbMode.DropDownStyle = ComboBoxStyle.DropDownList;
            cbMode.FlatStyle = FlatStyle.Flat;
            cbMode.FormattingEnabled = true;
            cbMode.Items.AddRange(new object[] { "ECB", "CBC", "CFB", "OFB", "CTR" });
            cbMode.Location = new Point(268, 82);
            cbMode.Name = "cbMode";
            cbMode.Size = new Size(428, 40);
            cbMode.TabIndex = 37;
            // 
            // btnMode
            // 
            btnMode.BackColor = Color.SteelBlue;
            btnMode.Font = new Font("Segoe UI", 9F, FontStyle.Bold, GraphicsUnit.Point, 0);
            btnMode.ForeColor = Color.White;
            btnMode.Location = new Point(53, 78);
            btnMode.Name = "btnMode";
            btnMode.Size = new Size(200, 46);
            btnMode.TabIndex = 38;
            btnMode.Text = "Mode";
            btnMode.UseVisualStyleBackColor = false;
            // 
            // DES
            // 
            AutoScaleDimensions = new SizeF(13F, 32F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(1442, 973);
            Controls.Add(btnMode);
            Controls.Add(cbMode);
            Controls.Add(btnGenKey);
            Controls.Add(btnDec);
            Controls.Add(btnEnc);
            Controls.Add(richTextBox1);
            Controls.Add(cbRCVtextFormat);
            Controls.Add(cbCPtextFormat);
            Controls.Add(cbPlaintextFormat);
            Controls.Add(txbRcv);
            Controls.Add(txbCipher);
            Controls.Add(txbPlain);
            Controls.Add(btnReadRcv);
            Controls.Add(btnReadCipher);
            Controls.Add(btnReadPlain);
            Controls.Add(txbPri);
            Controls.Add(cbFormat);
            Controls.Add(btnRead);
            Name = "DES";
            Text = "DES Encyption";
            Load += DES_Load;
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Button btnRead;
        private ComboBox cbFormat;
        private TextBox txbPri;
        private ComboBox cbRCVtextFormat;
        private ComboBox cbCPtextFormat;
        private ComboBox cbPlaintextFormat;
        private TextBox txbRcv;
        private TextBox txbCipher;
        private TextBox txbPlain;
        private Button btnReadRcv;
        private Button btnReadCipher;
        private Button btnReadPlain;
        private RichTextBox richTextBox1;
        private Button btnGenKey;
        private Button btnDec;
        private Button btnEnc;
        private ComboBox cbMode;
        private Button btnMode;
    }
}
