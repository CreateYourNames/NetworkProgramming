using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace TaskMeneger
{
	public partial class CommandLine : Form
	{
		public ComboBox ComboBoxFileName
		{
			get
			{
				return comboBoxFileName;
			}
		}
		public CommandLine()
		{
			InitializeComponent();
			Load();
		}
		public void Load()
		{
			StreamReader sr = new StreamReader("ProgramList.txt");

			while (!sr.EndOfStream)
			{
				string item = sr.ReadLine();
				comboBoxFileName.Items.Add(item);
			}
			comboBoxFileName.Text = comboBoxFileName.Items[0].ToString();
			sr.Close();
		}

		private void buttonOK_Click(object sender, EventArgs e)
		{
			try
			{
				string text = comboBoxFileName.Text;
				System.Diagnostics.ProcessStartInfo startInfo = new System.Diagnostics.ProcessStartInfo(text);
				System.Diagnostics.Process process = new System.Diagnostics.Process();
				process.StartInfo = startInfo;
				process.Start();
				//if(!comboBoxFileName.Items.Contains(comboBoxFileName.Text))
				//	comboBoxFileName.Items.Insert(0, comboBoxFileName.Text);
				comboBoxFileName.Items.Remove(text);
				comboBoxFileName.Text = (text);   //показывает что было последнее не открывая список
				comboBoxFileName.Items.Insert(0, text);
				this.Close();
			}
			catch (Exception ex)
			{
				MessageBox.Show(this, ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
			}
		}

		private void comboBoxFileName_KeyPress(object sender, KeyPressEventArgs e)
		{
			//if(e.KeyChar == (char)Keys.Enter) buttonOK_Click(sender, e);
			//if (e.KeyChar == (char)Keys.Escape) Close();
		}

		private void CommandLine_FormClosing(object sender, FormClosingEventArgs e)
		{
			comboBoxFileName.Focus();
		}

		private void comboBoxFileName_KeyUp(object sender, KeyEventArgs e)
		{
			
		}

		private void comboBoxFileName_KeyDown(object sender, KeyEventArgs e)
		{
			if (e.KeyValue == (char)Keys.Enter) buttonOK_Click(sender, e);
			//if (e.KeyValue == (char)Keys.Escape) Close();
		}

		private void CommandLine_KeyDown(object sender, KeyEventArgs e)
		{
			if (e.KeyValue == (char)Keys.Escape) Close();
		}

		private void buttonBrowse_Click(object sender, EventArgs e)
		{
			OpenFileDialog open = new OpenFileDialog();
			open.Filter = "Executable files (*.exe)|*.exe|All files (*.*)|*.*";
			DialogResult result = open.ShowDialog();
			if(result == DialogResult.OK)
			{
				comboBoxFileName.Text = open.FileName;
			}
		}

		//private void CommandLine_KeyPress(object sender, KeyPressEventArgs e)
		//{
		//	if (e.KeyChar == (char)Keys.Enter)
		//	{
		//		buttonOK_Click(sender, e);
		//	}
		//	if (e.KeyChar == (char)Keys.Escape) Close();
		//}
	}
}
