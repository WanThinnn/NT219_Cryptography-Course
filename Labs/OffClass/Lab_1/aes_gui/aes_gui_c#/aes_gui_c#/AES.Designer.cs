namespace aes_gui_c_
{
    partial class AES
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
            btnMode = new Button();
            cbMode = new ComboBox();
            btnGenKey = new Button();
            btnDec = new Button();
            btnEnc = new Button();
            richTextBox1 = new RichTextBox();
            cbRCVtextFormat = new ComboBox();
            cbCPtextFormat = new ComboBox();
            cbPlaintextFormat = new ComboBox();
            txbRcv = new TextBox();
            txbCipher = new TextBox();
            txbPlain = new TextBox();
            btnReadRcv = new Button();
            btnReadCipher = new Button();
            btnReadPlain = new Button();
            txbPri = new TextBox();
            cbFormat = new ComboBox();
            btnRead = new Button();
            cbSize = new ComboBox();
            SuspendLayout();
            // 
            // btnMode
            // 
            btnMode.BackColor = Color.SteelBlue;
            btnMode.Font = new Font("Segoe UI", 9F, FontStyle.Bold, GraphicsUnit.Point, 0);
            btnMode.ForeColor = Color.White;
            btnMode.Location = new Point(59, 57);
            btnMode.Name = "btnMode";
            btnMode.Size = new Size(200, 46);
            btnMode.TabIndex = 56;
            btnMode.Text = "Size - Mode";
            btnMode.UseVisualStyleBackColor = false;
            // 
            // cbMode
            // 
            cbMode.DropDownStyle = ComboBoxStyle.DropDownList;
            cbMode.FlatStyle = FlatStyle.Flat;
            cbMode.FormattingEnabled = true;
            cbMode.Items.AddRange(new object[] { "ECB", "CBC", "CFB", "OFB", "CTR", "XTS", "CCM", "GCM" });
            cbMode.Location = new Point(505, 61);
            cbMode.Name = "cbMode";
            cbMode.Size = new Size(197, 40);
            cbMode.TabIndex = 55;
            // 
            // btnGenKey
            // 
            btnGenKey.BackColor = Color.SteelBlue;
            btnGenKey.Font = new Font("Segoe UI", 9F, FontStyle.Bold, GraphicsUnit.Point, 0);
            btnGenKey.ForeColor = Color.White;
            btnGenKey.Location = new Point(62, 869);
            btnGenKey.Name = "btnGenKey";
            btnGenKey.Size = new Size(200, 46);
            btnGenKey.TabIndex = 54;
            btnGenKey.Text = "Genkey";
            btnGenKey.UseVisualStyleBackColor = false;
            btnGenKey.Click += btnGenKey_Click;
            // 
            // btnDec
            // 
            btnDec.BackColor = Color.SteelBlue;
            btnDec.Font = new Font("Segoe UI", 9F, FontStyle.Bold, GraphicsUnit.Point, 0);
            btnDec.ForeColor = Color.White;
            btnDec.Location = new Point(505, 869);
            btnDec.Name = "btnDec";
            btnDec.Size = new Size(200, 46);
            btnDec.TabIndex = 53;
            btnDec.Text = "Decrypt";
            btnDec.UseVisualStyleBackColor = false;
            btnDec.Click += btnDec_Click;
            // 
            // btnEnc
            // 
            btnEnc.BackColor = Color.SteelBlue;
            btnEnc.Font = new Font("Segoe UI", 9F, FontStyle.Bold, GraphicsUnit.Point, 0);
            btnEnc.ForeColor = Color.White;
            btnEnc.Location = new Point(287, 869);
            btnEnc.Name = "btnEnc";
            btnEnc.Size = new Size(200, 46);
            btnEnc.TabIndex = 52;
            btnEnc.Text = "Encrypt";
            btnEnc.UseVisualStyleBackColor = false;
            btnEnc.Click += btnEnc_Click;
            // 
            // richTextBox1
            // 
            richTextBox1.BorderStyle = BorderStyle.None;
            richTextBox1.Location = new Point(742, 61);
            richTextBox1.Name = "richTextBox1";
            richTextBox1.Size = new Size(642, 854);
            richTextBox1.TabIndex = 51;
            richTextBox1.Text = "";
            // 
            // cbRCVtextFormat
            // 
            cbRCVtextFormat.DropDownStyle = ComboBoxStyle.DropDownList;
            cbRCVtextFormat.FlatStyle = FlatStyle.Flat;
            cbRCVtextFormat.FormattingEnabled = true;
            cbRCVtextFormat.Items.AddRange(new object[] { "Text", "Base64", "PEM" });
            cbRCVtextFormat.Location = new Point(59, 771);
            cbRCVtextFormat.Name = "cbRCVtextFormat";
            cbRCVtextFormat.Size = new Size(200, 40);
            cbRCVtextFormat.TabIndex = 50;
            // 
            // cbCPtextFormat
            // 
            cbCPtextFormat.DropDownStyle = ComboBoxStyle.DropDownList;
            cbCPtextFormat.FlatStyle = FlatStyle.Flat;
            cbCPtextFormat.FormattingEnabled = true;
            cbCPtextFormat.Items.AddRange(new object[] { "DER", "Base64", "HEX" });
            cbCPtextFormat.Location = new Point(59, 592);
            cbCPtextFormat.Name = "cbCPtextFormat";
            cbCPtextFormat.Size = new Size(200, 40);
            cbCPtextFormat.TabIndex = 49;
            // 
            // cbPlaintextFormat
            // 
            cbPlaintextFormat.DropDownStyle = ComboBoxStyle.DropDownList;
            cbPlaintextFormat.FlatStyle = FlatStyle.Flat;
            cbPlaintextFormat.FormattingEnabled = true;
            cbPlaintextFormat.Items.AddRange(new object[] { "Text", "DER", "Base64", "HEX" });
            cbPlaintextFormat.Location = new Point(59, 402);
            cbPlaintextFormat.Name = "cbPlaintextFormat";
            cbPlaintextFormat.Size = new Size(200, 40);
            cbPlaintextFormat.TabIndex = 48;
            // 
            // txbRcv
            // 
            txbRcv.BackColor = Color.White;
            txbRcv.Location = new Point(274, 700);
            txbRcv.Multiline = true;
            txbRcv.Name = "txbRcv";
            txbRcv.ReadOnly = true;
            txbRcv.Size = new Size(428, 111);
            txbRcv.TabIndex = 47;
            // 
            // txbCipher
            // 
            txbCipher.BackColor = Color.White;
            txbCipher.Location = new Point(274, 521);
            txbCipher.Multiline = true;
            txbCipher.Name = "txbCipher";
            txbCipher.ReadOnly = true;
            txbCipher.Size = new Size(428, 111);
            txbCipher.TabIndex = 46;
            // 
            // txbPlain
            // 
            txbPlain.BackColor = Color.White;
            txbPlain.Location = new Point(274, 331);
            txbPlain.Multiline = true;
            txbPlain.Name = "txbPlain";
            txbPlain.ReadOnly = true;
            txbPlain.Size = new Size(428, 111);
            txbPlain.TabIndex = 45;
            // 
            // btnReadRcv
            // 
            btnReadRcv.BackColor = Color.SteelBlue;
            btnReadRcv.Font = new Font("Segoe UI", 9F, FontStyle.Bold, GraphicsUnit.Point, 0);
            btnReadRcv.ForeColor = Color.White;
            btnReadRcv.Location = new Point(59, 693);
            btnReadRcv.Name = "btnReadRcv";
            btnReadRcv.Size = new Size(200, 46);
            btnReadRcv.TabIndex = 44;
            btnReadRcv.Text = "Recover File";
            btnReadRcv.UseVisualStyleBackColor = false;
            btnReadRcv.Click += btnReadRcv_Click;
            // 
            // btnReadCipher
            // 
            btnReadCipher.BackColor = Color.SteelBlue;
            btnReadCipher.Font = new Font("Segoe UI", 9F, FontStyle.Bold, GraphicsUnit.Point, 0);
            btnReadCipher.ForeColor = Color.White;
            btnReadCipher.Location = new Point(59, 517);
            btnReadCipher.Name = "btnReadCipher";
            btnReadCipher.Size = new Size(200, 46);
            btnReadCipher.TabIndex = 43;
            btnReadCipher.Text = "Ciphertext File";
            btnReadCipher.UseVisualStyleBackColor = false;
            btnReadCipher.Click += btnReadCipher_Click;
            // 
            // btnReadPlain
            // 
            btnReadPlain.BackColor = Color.SteelBlue;
            btnReadPlain.Font = new Font("Segoe UI", 9F, FontStyle.Bold, GraphicsUnit.Point, 0);
            btnReadPlain.ForeColor = Color.White;
            btnReadPlain.Location = new Point(59, 331);
            btnReadPlain.Name = "btnReadPlain";
            btnReadPlain.Size = new Size(200, 46);
            btnReadPlain.TabIndex = 42;
            btnReadPlain.Text = "Plaintext File";
            btnReadPlain.UseVisualStyleBackColor = false;
            btnReadPlain.Click += btnReadPlain_Click;
            // 
            // txbPri
            // 
            txbPri.BackColor = Color.White;
            txbPri.Location = new Point(274, 175);
            txbPri.Multiline = true;
            txbPri.Name = "txbPri";
            txbPri.ReadOnly = true;
            txbPri.Size = new Size(428, 96);
            txbPri.TabIndex = 41;
            // 
            // cbFormat
            // 
            cbFormat.DropDownStyle = ComboBoxStyle.DropDownList;
            cbFormat.FlatStyle = FlatStyle.Flat;
            cbFormat.FormattingEnabled = true;
            cbFormat.Items.AddRange(new object[] { "DER", "Base64", "HEX" });
            cbFormat.Location = new Point(59, 231);
            cbFormat.Name = "cbFormat";
            cbFormat.Size = new Size(200, 40);
            cbFormat.TabIndex = 40;
            // 
            // btnRead
            // 
            btnRead.BackColor = Color.SteelBlue;
            btnRead.Font = new Font("Segoe UI", 9F, FontStyle.Bold, GraphicsUnit.Point, 0);
            btnRead.ForeColor = Color.White;
            btnRead.Location = new Point(59, 175);
            btnRead.Name = "btnRead";
            btnRead.Size = new Size(200, 46);
            btnRead.TabIndex = 39;
            btnRead.Text = "Key File";
            btnRead.UseVisualStyleBackColor = false;
            btnRead.Click += btnRead_Click;
            // 
            // cbSize
            // 
            cbSize.DropDownStyle = ComboBoxStyle.DropDownList;
            cbSize.FlatStyle = FlatStyle.Flat;
            cbSize.FormattingEnabled = true;
            cbSize.Items.AddRange(new object[] { "128", "192", "256" });
            cbSize.Location = new Point(274, 58);
            cbSize.Name = "cbSize";
            cbSize.Size = new Size(200, 40);
            cbSize.TabIndex = 57;
            // 
            // AES
            // 
            AutoScaleDimensions = new SizeF(13F, 32F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(1442, 973);
            Controls.Add(cbSize);
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
            Name = "AES";
            Text = "AES Encryption";
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Button btnMode;
        private ComboBox cbMode;
        private Button btnGenKey;
        private Button btnDec;
        private Button btnEnc;
        private RichTextBox richTextBox1;
        private ComboBox cbRCVtextFormat;
        private ComboBox cbCPtextFormat;
        private ComboBox cbPlaintextFormat;
        private TextBox txbRcv;
        private TextBox txbCipher;
        private TextBox txbPlain;
        private Button btnReadRcv;
        private Button btnReadCipher;
        private Button btnReadPlain;
        private TextBox txbPri;
        private ComboBox cbFormat;
        private Button btnRead;
        private ComboBox cbSize;
    }
}
