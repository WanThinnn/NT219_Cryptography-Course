using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace aes_console_app_c_
{
    internal class Program
    {
        [DllImport("AES_DLL.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "GenerateAndSaveIV_Keys")]
        public static extern void GenerateAndSaveIV_Keys(int KeySize, string KeyFormat, string KeyFileName);

        [DllImport("AES_DLL.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "Encryption")]
        public static extern void Encryption(string mode, string KeyFile, string KeyFormat, string PlaintextFile, string PlaintextFormat, string CipherFile, string CipherFormat);


        [DllImport("AES_DLL.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "Decryption")]
        public static extern void Decryption(string mode, string KeyFile, string KeyFormat, string RecoveredFile, string RecoveredFormat, string CipherFile, string CipherFormat);

        static long getFileSize(string filePath)
        {
            FileInfo fileInfo = new FileInfo(filePath);
            return fileInfo.Length;
        }
        static void ProcessInput(string action, string[] args)
        {
            if (action == "genkey")
            {
                int size = int.Parse(args[1]);
                if (args.Length != 4)
                {
                    Console.Error.WriteLine("Usage:");
                    Console.Error.WriteLine("\t {0} genkey <KeySize> <KeyFileFormat> <KeyFile>", Environment.GetCommandLineArgs()[0]);
                    return;
                }
                GenerateAndSaveIV_Keys(size/8, args[2], args[3]);
            }
            else if (action == "encrypt")
            {
                if (args.Length != 8)
                {
                    Console.Error.WriteLine("Usage:");
                    Console.Error.WriteLine($"\t {Environment.GetCommandLineArgs()[0]} encrypt <Mode> <KeyFile> <KeyFileFormat> <PlaintextFile> <PlaintextFormat> <CipherFile> <CipherFormat>");
                    return;
                }

                Stopwatch stopwatch = new Stopwatch();
                stopwatch.Start();

                Encryption(args[1], args[2], args[3], args[4], args[5], args[6], args[7]);

                stopwatch.Stop();
                TimeSpan duration = stopwatch.Elapsed;

                string plaintextFile = args[4];
                string ciphertextFile = args[6];
                long plain = getFileSize(plaintextFile);
                long cipher = getFileSize(ciphertextFile);

                Console.WriteLine("Overview DES Encryption Test");
                Console.WriteLine($"Mode: {args[2]}");
                Console.WriteLine($"Plaintext file: {plaintextFile}");
                Console.WriteLine($"Size of plaintext file: {plain} bytes");
                Console.WriteLine($"Ciphertext file: {ciphertextFile}");
                Console.WriteLine($"Size of ciphertext file: {cipher} bytes");
                Console.WriteLine($"Encryption time: {duration.TotalMilliseconds} milliseconds");
            }
            else if (action == "decrypt")
            {
                if (args.Length != 8)
                {
                    Console.WriteLine("Usage:");
                    Console.WriteLine($"\t {args[0]} decrypt <Mode> <KeyFile> <KeyFileFormat> <RecoveredFile> <RecoveredFileFormat> <CipherFile> <CipherFormat>");
                    return;
                }

                Stopwatch stopwatch = new Stopwatch();
                stopwatch.Start();

                Decryption(args[1], args[2], args[3], args[4], args[5], args[6], args[7]);

                stopwatch.Stop();
                TimeSpan duration = stopwatch.Elapsed;

                string rcvTextFile = args[4];
                long rcv = getFileSize(rcvTextFile);

                string ciphertextFile = args[6];
                long cipher = getFileSize(ciphertextFile);

                Console.WriteLine("Overview DES Decryption Test");
                Console.WriteLine($"Mode: {args[2]}");
                Console.WriteLine($"Ciphertext file: {ciphertextFile}");
                Console.WriteLine($"Size of cipher text file: {cipher} bytes");
                Console.WriteLine($"Recovered text file: {rcvTextFile}");
                Console.WriteLine($"Size of recovered text file: {rcv} bytes");
                Console.WriteLine($"Decryption time: {duration.TotalMilliseconds} milliseconds");
            }
            else
            {
                Console.WriteLine("Invalid action. Please choose 'genkey', 'encrypt', or 'decrypt'.");
            }
        }
        static void Main(string[] args)
        {
            if (Environment.OSVersion.Platform == PlatformID.Win32NT)
                if (Environment.OSVersion.Platform == PlatformID.Win32NT)
                {
                    Console.OutputEncoding = System.Text.Encoding.UTF8;
                    Console.InputEncoding = System.Text.Encoding.UTF8;
                }
            if (args.Length < 2)
            {
                Console.Error.WriteLine("Usage:");
                Console.Error.WriteLine(" {0} genkey <KeySize> <KeyFileFormat> <KeyFile>", Environment.GetCommandLineArgs()[0]);
                Console.Error.WriteLine(" {0} encrypt <Mode> <KeyFile> <KeyFileFormat> <PlaintextFile> <PlaintextFormat> <CipherFile> <CipherFormat>", Environment.GetCommandLineArgs()[0]);
                Console.Error.WriteLine(" {0} decrypt <Mode> <KeyFile> <KeyFileFormat> <RecoveredFile> <RecoveredFileFormat> <CipherFile> <CipherFormat>", Environment.GetCommandLineArgs()[0]);
                Environment.Exit(-1);
            }
            string action = args[0];
            ProcessInput(action, args);
        }
    }
}
