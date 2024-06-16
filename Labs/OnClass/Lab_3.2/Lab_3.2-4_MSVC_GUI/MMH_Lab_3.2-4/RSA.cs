using System.Runtime.InteropServices;

namespace MMH_Lab_3._2_4
{
    public partial class RSA : Form
    {
        public RSA()
        {
            InitializeComponent();
        }
        [DllImport("Lab_3.2-2_MSVC.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "GenerationAndSaveRSAKeys")]
        public static extern void GenerationAndSaveRSAKeys(int keySize, string format, string privateKeyFile, string publicKeyFile);

        [DllImport("Lab_3.2-2_MSVC.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "RSAencrypt")]
        public static extern void RSAencrypt(string keyformat, string publicKeyFile, string PlaintextFormat, string PlaintextFile, string CipherFormat, string CipherFile);


        [DllImport("Lab_3.2-2_MSVC.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "RSAdecrypt")]
        public static extern void RSAdecrypt(string keyformat, string privateKeyFile, string CipherFormat, string CipherFile, string RecoveredFormat, string RecoverFile);

        string priKeyFile ="";
        string pubKeyFile = "";
        string plaintextFile = "";
        string ciphertextFile = "";
        string rcvFile = "";
        string format = "";
        string pltformat = "";
        string cptformat = "";
        string rcvtformat = "";


        private void btnRead_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "Text files (*.txt)|*.txt|All files (*.*)|*.*";

            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                string filePath = openFileDialog.FileName;
                priKeyFile = filePath; // Copy đường dẫn của tệp vào clipboard
                txbPri.Text = priKeyFile;


            }
            else
            {
                MessageBox.Show("Không thể mở File Explorer ", "Lỗi", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }

        }

        private void btnReadPub_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "Text files (*.txt)|*.txt|All files (*.*)|*.*";

            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                string filePath = openFileDialog.FileName;
                pubKeyFile = filePath; // Copy đường dẫn của tệp vào clipboard
                txbPubKey.Text = pubKeyFile;

            }
            else
            {
                MessageBox.Show("Không thể mở File Explorer ", "Lỗi", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void btnReadPlain_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "Text files (*.txt)|*.txt|All files (*.*)|*.*";

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
            openFileDialog.Filter = "Text files (*.txt)|*.txt|All files (*.*)|*.*";

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
            openFileDialog.Filter = "Text files (*.txt)|*.txt|All files (*.*)|*.*";

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

        private void btnEnc_Click(object sender, EventArgs e)
        {
            format = cbFormat.SelectedItem.ToString();
            pltformat = cbPlaintextFormat.SelectedItem.ToString();
            cptformat = cbCPtextFormat.SelectedItem.ToString();
            RSAencrypt(format, pubKeyFile, pltformat, plaintextFile, cptformat, ciphertextFile);
            MessageBox.Show("Encyption successfull!", "Thông báo", MessageBoxButtons.OK, MessageBoxIcon.Information);
            string content = "This is Cipher Text:\n\n\n" + File.ReadAllText(ciphertextFile);
            richTextBox1.Text = content;
        }

        private void btnDec_Click(object sender, EventArgs e)
        {
            format = cbFormat.SelectedItem.ToString();
            cptformat = cbCPtextFormat.SelectedItem.ToString();
            rcvtformat = cbRCVtextFormat.SelectedItem.ToString();
            RSAdecrypt(format, priKeyFile, cptformat, ciphertextFile, rcvtformat, rcvFile);
            string content = "This is Recover Text:\n\n\n" + File.ReadAllText(rcvFile);
            richTextBox1.Text = content;
            MessageBox.Show("Decryption successfull!", "Thông báo", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void btnGenKey_Click(object sender, EventArgs e)
        {
            format = cbFormat.SelectedItem.ToString();
            int keySize = int.Parse(txbKeySize.Text);
            GenerationAndSaveRSAKeys(keySize, format, priKeyFile, pubKeyFile);
            MessageBox.Show("Key Gennertation successfull!", "Thông báo", MessageBoxButtons.OK, MessageBoxIcon.Information);
            string content = "This is Publickey:\n\n\n" + File.ReadAllText(pubKeyFile);
            richTextBox1.Text = content;
        }
    }
}
