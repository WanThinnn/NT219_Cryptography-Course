using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace aes_manual_gui
{
    public partial class aes_cbc_manual : Form
    {
        string KeyFile = "";
        string plaintextFile = "";
        string ciphertextFile = "";
        string rcvFile = "";
        string keyformat = "";
        string pltformat = "";
        string cptformat = "";
        string rcvtformat = "";
        string mode = "";
        int keySize = 0;
        public aes_cbc_manual()
        {
            InitializeComponent();
        }
        [DllImport("aes_manual_dll.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "GenerateKeyandIV")]
        public static extern void GenerateKeyandIV(int keysize, string keyformat, string keyfile);

        [DllImport("aes_manual_dll.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "Encryption")]
        public static extern void Encryption(string keyformat, string keyfile, string plaintextformat, string plaintextfile, string ciphertextformat, string ciphertextfile);


        [DllImport("aes_manual_dll.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "Decryption")]
        public static extern void Decryption(string keyformat, string keyfile, string ciphertextformat, string ciphertextfile, string rcvtextformat, string rcvtextfile);

        private void get_key_file()
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "All files (*.*)|*.*";

            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                string filePath = openFileDialog.FileName;
                KeyFile = filePath; // Copy đường dẫn của tệp vào clipboard
                txbPri.Text = KeyFile;


            }
            else
            {
                MessageBox.Show("Không thể mở File Explorer ", "Lỗi", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        private void btnReadPlain_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "All files (*.*)|*.*";

            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                string filePath = openFileDialog.FileName;
                plaintextFile = filePath; // Copy đường dẫn của tệp vào clipboard
                txbPlain.Text = plaintextFile;

            }
            else
            {
                MessageBox.Show("Không thể mở File Explorer ", "Lỗi", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }


        private void btnRead_Click(object sender, EventArgs e)
        {
            get_key_file();
        }

        private void btnReadPlain_Click_1(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "All files (*.*)|*.*";

            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                string filePath = openFileDialog.FileName;
                plaintextFile = filePath; // Copy đường dẫn của tệp vào clipboard
                txbPlain.Text = plaintextFile;

            }
            else
            {
                MessageBox.Show("Không thể mở File Explorer ", "Lỗi", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void btnReadCipher_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "All files (*.*)|*.*";

            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                string filePath = openFileDialog.FileName;
                ciphertextFile = filePath; // Copy đường dẫn của tệp vào clipboard
                txbCipher.Text = ciphertextFile;

            }
            else
            {
                MessageBox.Show("Không thể mở File Explorer ", "Lỗi", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void btnReadRcv_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "All files (*.*)|*.*";

            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                string filePath = openFileDialog.FileName;
                rcvFile = filePath; // Copy đường dẫn của tệp vào clipboard
                txbRcv.Text = rcvFile;
            }
            else
            {
                MessageBox.Show("Không thể mở File Explorer ", "Lỗi", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void btnGenKey_Click(object sender, EventArgs e)
        {
            keySize = int.Parse(cbSize.SelectedItem.ToString());

            keyformat = cbFormat.SelectedItem.ToString();
            GenerateKeyandIV(keySize, keyformat, KeyFile);
            MessageBox.Show("Key Gennertation successfull!", "Thông báo", MessageBoxButtons.OK, MessageBoxIcon.Information);
            string content = "Key and IV saved to: \n" + KeyFile;
            richTextBox1.Text = content;
        }

        private void btnEnc_Click(object sender, EventArgs e)
        {

            keyformat = cbFormat.SelectedItem.ToString();
            cptformat = cbCPtextFormat.SelectedItem.ToString();
            pltformat = cbPlaintextFormat.SelectedItem.ToString();
            Encryption(keyformat, KeyFile, pltformat, plaintextFile, cptformat, ciphertextFile);

            MessageBox.Show("Encyption successfull!", "Thông báo", MessageBoxButtons.OK, MessageBoxIcon.Information);
            string content = "Cipher Text saved to:\n" + ciphertextFile;
            richTextBox1.Text = content;
        }

        private void btnDec_Click(object sender, EventArgs e)
        {
            keyformat = cbFormat.SelectedItem.ToString();
            cptformat = cbCPtextFormat.SelectedItem.ToString();
            rcvtformat = cbRCVtextFormat.SelectedItem.ToString();
            Decryption(keyformat, KeyFile, cptformat, ciphertextFile, rcvtformat, rcvFile);
            MessageBox.Show("Decryption successfull!", "Thông báo", MessageBoxButtons.OK, MessageBoxIcon.Information);
            string content = "This is Recover Text:\n" + File.ReadAllText(rcvFile);
            string content_2 = "Recover Text saved to:\n" + rcvFile;
            richTextBox1.Text = content + "\n\n" + content_2;
        }
    }
}
