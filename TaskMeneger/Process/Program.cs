﻿#define SINGLE_PROCESS
//#define ALL_PROCESSES
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;
using System.Runtime.InteropServices;


namespace Process
{
	internal class Program
	{
		static void Main(string[] args)
		{
#if SINGLE_PROCESS
			Console.WriteLine("Введите имя программы");
			string process_name = Console.ReadLine();
			System.Diagnostics.Process process = new System.Diagnostics.Process();
			process.StartInfo.FileName = process_name;
			process.Start();

			Console.WriteLine(process.ProcessName);
			Console.WriteLine(process.Id);
			Console.WriteLine(process.MainModule.FileName);

			IntPtr handel = IntPtr.Zero;
			OpenProcessToken(process.Handle, 8, out handel);
			System.Security.Principal.WindowsIdentity wi = new System.Security.Principal.WindowsIdentity(handel);
			CloseHandle(handel);
			Console.WriteLine($"Username:{wi.Name}");

			Console.WriteLine($"SessionID: {process.SessionId}");
			Console.WriteLine($"Threads:{process.Threads}");
			Console.WriteLine($"Priority:{process.PriorityClass}"); 

			PerformanceCounter counter = new PerformanceCounter("Process", "% Processor Time", process.ProcessName, true);
			Console.WriteLine("Press any key to continue...");
			while(!Console.KeyAvailable)
			{
				Console.Clear();
				double procent = counter.NextValue();
				Console.WriteLine($"{process.ProcessName} CPU load: {procent/10} %");
				int units = 1024 * 1024;
				Console.WriteLine($"Working set:	{process.WorkingSet64/units}");
				Console.WriteLine($"Private Working set:	{process.PrivateMemorySize64/units}");
				System.Threading.Thread.Sleep(100);
			}
			process.CloseMainWindow();
			process.Dispose();
			process = null;
#endif

#if ALL_PROCESSES
			Console.Clear();
			System.Diagnostics.Process[] processes = System.Diagnostics.Process.GetProcesses(); // возвращает массив всех заппущенных процессов
			for (int i = 0; i < processes.Length; i++)
			{
				Console.WriteLine($"{processes[i].Id}\t{processes[i].MainModule.FileName}");
				//Console.Write($"Name: {processes[i].ProcessName}\t");
				//Console.Write($"PID: {processes[i].Id}\t");
				Console.Write($"Path: {processes[i].MainModule.FileName}\t");
				//Console.WriteLine();
			}
#endif
		}
		[DllImport("advapi32.dll", SetLastError = true)]
		private static extern bool OpenProcessToken(IntPtr processHandle, uint desiredAccess, out IntPtr handle);
		[DllImport("kernel32.dll", SetLastError = true)]
		[return: MarshalAs(UnmanagedType.Bool)]
		private static extern bool CloseHandle(IntPtr handle);
	}
}
