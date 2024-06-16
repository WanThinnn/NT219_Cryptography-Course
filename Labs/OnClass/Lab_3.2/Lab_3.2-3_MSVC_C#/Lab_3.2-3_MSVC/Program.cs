using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using System.Runtime.ConstrainedExecution;

namespace Lab_3._2_3_MSVC
{
    internal class Program
    {
        [DllImport("Lab_3.2-2_MSVC.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "GenerationAndSaveRSAKeys")]
        public static extern void GenerationAndSaveRSAKeys(int keySize, string format, string privateKeyFile, string publicKeyFile);

        [DllImport("Lab_3.2-2_MSVC.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "RSAencrypt")]
        public static extern void RSAencrypt(string keyformat, string publicKeyFile, string PlaintextFormat, string PlaintextFile, string CipherFormat, string CipherFile);


        [DllImport("Lab_3.2-2_MSVC.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "RSAdecrypt")]
        public static extern void RSAdecrypt(string keyformat, string privateKeyFile, string CipherFormat, string CipherFile, string RecoveredFormat, string RecoverFile);

        static void Main(string[] args)
        {
            // Set console to UTF-8 for Windows environments 

            if (Environment.OSVersion.Platform == PlatformID.Win32NT)
            if (Environment.OSVersion.Platform == PlatformID.Win32NT)
            {
                Console.OutputEncoding = System.Text.Encoding.UTF8;
                Console.InputEncoding = System.Text.Encoding.UTF8;
            }
            if (args.Length < 2)
            {
                Console.Error.WriteLine("Usage:");
                Console.Error.WriteLine(" {0} genkey <keysize> <format> <privateKeyFile> <publicKeyFile>", Environment.GetCommandLineArgs()[0]);
                Console.Error.WriteLine(" {0} encrypt <KeyFormat> <PublicKeyFile> <PlainTextFormat> <PlainTextFile> <CipherTextFormat> <CipherFile>", Environment.GetCommandLineArgs()[0]);
                Console.Error.WriteLine(" {0} decrypt <KeyFormat> <PrivateKeyFile> <CiphertextFormat> <CipherFile> <rcvTextFormat> <rcvTextFile>", Environment.GetCommandLineArgs()[0]);
                Environment.Exit(-1);
            }

            string mode = args[0];

            if (mode.Equals("genkey") && args.Length == 5)
            {
                int keySize = int.Parse(args[1]);
                GenerationAndSaveRSAKeys(keySize, args[2], args[3], args[4]);
            }
            else if (mode.Equals("encrypt") && args.Length == 7)
            {
                RSAencrypt(args[1], args[2], args[3], args[4], args[5], args[6]);
            }
            else if (mode.Equals("decrypt") && args.Length == 7)
            {
                RSAdecrypt(args[1], args[2], args[3], args[4], args[5], args[6]);
            }
            else
            {
                Console.Error.WriteLine("Invalid arguments. Please check the usage instructions.");
                Environment.Exit(-1);
            }
            Console.WriteLine("Operation completed sucessfully!");

            Environment.Exit(0);
        }
    }
}
