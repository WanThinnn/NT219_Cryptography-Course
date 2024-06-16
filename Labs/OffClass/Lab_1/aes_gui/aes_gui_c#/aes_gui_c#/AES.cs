using System.Drawing;
using System.Runtime.InteropServices;

namespace aes_gui_c_
{
    public partial class AES : Form
    {
        public AES()
        {
            InitializeComponent();
        }
        [DllImport("AES_DLL.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "GenerateAndSaveIV_Keys")]
        public static extern void GenerateAndSaveIV_Keys(int KeySize, string KeyFormat, string KeyFileName);

        [DllImport("AES_DLL.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "Encryption")]
        public static extern void Encryption(string mode, string KeyFile, string KeyFormat, string PlaintextFile, string PlaintextFormat, string CipherFile, string CipherFormat);


        [DllImport("AES_DLL.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "Decryption")]
        public static extern void Decryption(string mode, string KeyFile, string KeyFormat, string RecoveredFile, string RecoveredFormat, string CipherFile, string CipherFormat);

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
        private void btnRead_Click(object sender, EventArgs e)
        {
            get_key_file();

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
            GenerateAndSaveIV_Keys(keySize/8, keyformat, KeyFile);
            MessageBox.Show("Key Gennertation successfull!", "Thông báo", MessageBoxButtons.OK, MessageBoxIcon.Information);
            string content = "Key and IV saved to: \n" + KeyFile;
            richTextBox1.Text = content;
        }

        private void btnEnc_Click(object sender, EventArgs e)
        {
            mode = cbMode.SelectedItem.ToString();
            keyformat = cbFormat.SelectedItem.ToString();
            cptformat = cbCPtextFormat.SelectedItem.ToString();
            pltformat = cbPlaintextFormat.SelectedItem.ToString();
            Encryption(mode, KeyFile, keyformat, plaintextFile, pltformat, ciphertextFile, cptformat);

            MessageBox.Show("Encyption successfull!", "Thông báo", MessageBoxButtons.OK, MessageBoxIcon.Information);
            string content = "Cipher Text saved to:\n" + ciphertextFile;
            richTextBox1.Text = content;
        }

        private void btnDec_Click(object sender, EventArgs e)
        {

            mode = cbMode.SelectedItem.ToString();
            keyformat = cbFormat.SelectedItem.ToString();
            cptformat = cbCPtextFormat.SelectedItem.ToString();
            rcvtformat = cbRCVtextFormat.SelectedItem.ToString();
            Decryption(mode, KeyFile, keyformat, rcvFile, rcvtformat, ciphertextFile, cptformat);
            MessageBox.Show("Decryption successfull!", "Thông báo", MessageBoxButtons.OK, MessageBoxIcon.Information);
            string content = "This is Recover Text:\n" + File.ReadAllText(rcvFile);
            string content_2 = "Recover Text saved to:\n" + rcvFile;
            richTextBox1.Text = content + "\n\n" + content_2;
        }

    }
}
