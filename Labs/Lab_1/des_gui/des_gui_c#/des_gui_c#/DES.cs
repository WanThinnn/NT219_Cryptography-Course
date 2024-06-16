using System.Runtime.InteropServices;
using static System.Windows.Forms.DataFormats;

namespace des_gui_c_
{
    public partial class DES : Form
    {
        public DES()
        {
            InitializeComponent();
        }
        [DllImport("des_2.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "GenerateAndSaveIV_Keys")]
        public static extern void GenerateAndSaveIV_Keys(string KeyFormat, string KeyFileName);

        [DllImport("des_2.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "Encryption")]
        public static extern void Encryption(string mode, string KeyFile, string KeyFormat, string PlaintextFile, string PlaintextFormat, string CipherFile, string CipherFormat);


        [DllImport("des_2.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "Decryption")]
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
            keyformat = cbFormat.SelectedItem.ToString();
            GenerateAndSaveIV_Keys(keyformat, KeyFile);
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
            Encryption(mode, KeyFile, keyformat, plaintextFile, pltformat, ciphertextFile, cptformat );

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

        private void DES_Load(object sender, EventArgs e)
        {

        }
    }
}
