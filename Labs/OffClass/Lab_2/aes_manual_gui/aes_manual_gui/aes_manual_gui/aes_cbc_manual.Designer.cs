namespace aes_manual_gui
{
    partial class aes_cbc_manual
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
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
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            cbSize = new ComboBox();
            btnMode = new Button();
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
            SuspendLayout();
            // 
            // cbSize
            // 
            cbSize.DropDownStyle = ComboBoxStyle.DropDownList;
            cbSize.FlatStyle = FlatStyle.Flat;
            cbSize.FormattingEnabled = true;
            cbSize.Items.AddRange(new object[] { "128", "192", "256" });
            cbSize.Location = new Point(400, 89);
            cbSize.Name = "cbSize";
            cbSize.Size = new Size(297, 40);
            cbSize.TabIndex = 76;
            // 
            // btnMode
            // 
            btnMode.BackColor = Color.SteelBlue;
            btnMode.Font = new Font("Segoe UI", 9F, FontStyle.Bold, GraphicsUnit.Point, 0);
            btnMode.ForeColor = Color.White;
            btnMode.Location = new Point(54, 89);
            btnMode.Name = "btnMode";
            btnMode.Size = new Size(340, 46);
            btnMode.TabIndex = 75;
            btnMode.Text = "Key size for CBC Mode";
            btnMode.UseVisualStyleBackColor = false;
            // 
            // btnGenKey
            // 
            btnGenKey.BackColor = Color.SteelBlue;
            btnGenKey.Font = new Font("Segoe UI", 9F, FontStyle.Bold, GraphicsUnit.Point, 0);
            btnGenKey.ForeColor = Color.White;
            btnGenKey.Location = new Point(57, 856);
            btnGenKey.Name = "btnGenKey";
            btnGenKey.Size = new Size(200, 46);
            btnGenKey.TabIndex = 73;
            btnGenKey.Text = "Genkey";
            btnGenKey.UseVisualStyleBackColor = false;
            btnGenKey.Click += btnGenKey_Click;
            // 
            // btnDec
            // 
            btnDec.BackColor = Color.SteelBlue;
            btnDec.Font = new Font("Segoe UI", 9F, FontStyle.Bold, GraphicsUnit.Point, 0);
            btnDec.ForeColor = Color.White;
            btnDec.Location = new Point(500, 856);
            btnDec.Name = "btnDec";
            btnDec.Size = new Size(200, 46);
            btnDec.TabIndex = 72;
            btnDec.Text = "Decrypt";
            btnDec.UseVisualStyleBackColor = false;
            btnDec.Click += btnDec_Click;
            // 
            // btnEnc
            // 
            btnEnc.BackColor = Color.SteelBlue;
            btnEnc.Font = new Font("Segoe UI", 9F, FontStyle.Bold, GraphicsUnit.Point, 0);
            btnEnc.ForeColor = Color.White;
            btnEnc.Location = new Point(282, 856);
            btnEnc.Name = "btnEnc";
            btnEnc.Size = new Size(200, 46);
            btnEnc.TabIndex = 71;
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
            richTextBox1.TabIndex = 70;
            richTextBox1.Text = "";
            // 
            // cbRCVtextFormat
            // 
            cbRCVtextFormat.DropDownStyle = ComboBoxStyle.DropDownList;
            cbRCVtextFormat.FlatStyle = FlatStyle.Flat;
            cbRCVtextFormat.FormattingEnabled = true;
            cbRCVtextFormat.Items.AddRange(new object[] { "Text", "Binary", "HEX" });
            cbRCVtextFormat.Location = new Point(54, 758);
            cbRCVtextFormat.Name = "cbRCVtextFormat";
            cbRCVtextFormat.Size = new Size(200, 40);
            cbRCVtextFormat.TabIndex = 69;
            // 
            // cbCPtextFormat
            // 
            cbCPtextFormat.DropDownStyle = ComboBoxStyle.DropDownList;
            cbCPtextFormat.FlatStyle = FlatStyle.Flat;
            cbCPtextFormat.FormattingEnabled = true;
            cbCPtextFormat.Items.AddRange(new object[] { "Binary", "HEX" });
            cbCPtextFormat.Location = new Point(54, 579);
            cbCPtextFormat.Name = "cbCPtextFormat";
            cbCPtextFormat.Size = new Size(200, 40);
            cbCPtextFormat.TabIndex = 68;
            // 
            // cbPlaintextFormat
            // 
            cbPlaintextFormat.DropDownStyle = ComboBoxStyle.DropDownList;
            cbPlaintextFormat.FlatStyle = FlatStyle.Flat;
            cbPlaintextFormat.FormattingEnabled = true;
            cbPlaintextFormat.Items.AddRange(new object[] { "Binary", "HEX", "Text" });
            cbPlaintextFormat.Location = new Point(54, 389);
            cbPlaintextFormat.Name = "cbPlaintextFormat";
            cbPlaintextFormat.Size = new Size(200, 40);
            cbPlaintextFormat.TabIndex = 67;
            // 
            // txbRcv
            // 
            txbRcv.BackColor = Color.White;
            txbRcv.Location = new Point(269, 687);
            txbRcv.Multiline = true;
            txbRcv.Name = "txbRcv";
            txbRcv.ReadOnly = true;
            txbRcv.Size = new Size(428, 111);
            txbRcv.TabIndex = 66;
            // 
            // txbCipher
            // 
            txbCipher.BackColor = Color.White;
            txbCipher.Location = new Point(269, 508);
            txbCipher.Multiline = true;
            txbCipher.Name = "txbCipher";
            txbCipher.ReadOnly = true;
            txbCipher.Size = new Size(428, 111);
            txbCipher.TabIndex = 65;
            // 
            // txbPlain
            // 
            txbPlain.BackColor = Color.White;
            txbPlain.Location = new Point(269, 318);
            txbPlain.Multiline = true;
            txbPlain.Name = "txbPlain";
            txbPlain.ReadOnly = true;
            txbPlain.Size = new Size(428, 111);
            txbPlain.TabIndex = 64;
            // 
            // btnReadRcv
            // 
            btnReadRcv.BackColor = Color.SteelBlue;
            btnReadRcv.Font = new Font("Segoe UI", 9F, FontStyle.Bold, GraphicsUnit.Point, 0);
            btnReadRcv.ForeColor = Color.White;
            btnReadRcv.Location = new Point(54, 680);
            btnReadRcv.Name = "btnReadRcv";
            btnReadRcv.Size = new Size(200, 46);
            btnReadRcv.TabIndex = 63;
            btnReadRcv.Text = "Recover File";
            btnReadRcv.UseVisualStyleBackColor = false;
            btnReadRcv.Click += btnReadRcv_Click;
            // 
            // btnReadCipher
            // 
            btnReadCipher.BackColor = Color.SteelBlue;
            btnReadCipher.Font = new Font("Segoe UI", 9F, FontStyle.Bold, GraphicsUnit.Point, 0);
            btnReadCipher.ForeColor = Color.White;
            btnReadCipher.Location = new Point(54, 504);
            btnReadCipher.Name = "btnReadCipher";
            btnReadCipher.Size = new Size(200, 46);
            btnReadCipher.TabIndex = 62;
            btnReadCipher.Text = "Ciphertext File";
            btnReadCipher.UseVisualStyleBackColor = false;
            btnReadCipher.Click += btnReadCipher_Click;
            // 
            // btnReadPlain
            // 
            btnReadPlain.BackColor = Color.SteelBlue;
            btnReadPlain.Font = new Font("Segoe UI", 9F, FontStyle.Bold, GraphicsUnit.Point, 0);
            btnReadPlain.ForeColor = Color.White;
            btnReadPlain.Location = new Point(54, 318);
            btnReadPlain.Name = "btnReadPlain";
            btnReadPlain.Size = new Size(200, 46);
            btnReadPlain.TabIndex = 61;
            btnReadPlain.Text = "Plaintext File";
            btnReadPlain.UseVisualStyleBackColor = false;
            btnReadPlain.Click += btnReadPlain_Click_1;
            // 
            // txbPri
            // 
            txbPri.BackColor = Color.White;
            txbPri.Location = new Point(269, 162);
            txbPri.Multiline = true;
            txbPri.Name = "txbPri";
            txbPri.ReadOnly = true;
            txbPri.Size = new Size(428, 96);
            txbPri.TabIndex = 60;
            // 
            // cbFormat
            // 
            cbFormat.DropDownStyle = ComboBoxStyle.DropDownList;
            cbFormat.FlatStyle = FlatStyle.Flat;
            cbFormat.FormattingEnabled = true;
            cbFormat.Items.AddRange(new object[] { "Binary", "HEX" });
            cbFormat.Location = new Point(54, 218);
            cbFormat.Name = "cbFormat";
            cbFormat.Size = new Size(200, 40);
            cbFormat.TabIndex = 59;
            // 
            // btnRead
            // 
            btnRead.BackColor = Color.SteelBlue;
            btnRead.Font = new Font("Segoe UI", 9F, FontStyle.Bold, GraphicsUnit.Point, 0);
            btnRead.ForeColor = Color.White;
            btnRead.Location = new Point(54, 162);
            btnRead.Name = "btnRead";
            btnRead.Size = new Size(200, 46);
            btnRead.TabIndex = 58;
            btnRead.Text = "Key File";
            btnRead.UseVisualStyleBackColor = false;
            btnRead.Click += btnRead_Click;
            // 
            // aes_cbc_manual
            // 
            AutoScaleDimensions = new SizeF(13F, 32F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(1442, 973);
            Controls.Add(cbSize);
            Controls.Add(btnMode);
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
            Name = "aes_cbc_manual";
            StartPosition = FormStartPosition.CenterScreen;
            Text = "aes_cbc_manuak";
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private ComboBox cbSize;
        private Button btnMode;
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
    }
}