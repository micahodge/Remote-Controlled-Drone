using System;
using System.CodeDom;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FinalSHI
{
    public partial class Form1 : Form
    {
        SerialPort hippo = new SerialPort(); // to read serial port
        int sixclick = 0; // initialize variables
        public Form1() // form function
        {
            InitializeComponent();
            button2.Enabled = false; // turn off button 2
            label1.BackColor = Color.Red; // turn label red
        }

        private void button1_Click(object sender, EventArgs e) // button 1 function
        {
            hippo.PortName = "COM4"; // port name is alwyas COM4 for my arduino
            hippo.BaudRate = 9600; // so the arduino and the C# window and computer can communicate clearly
            hippo.Open(); // open the port
            button2.Enabled = true; // turn on button 2
            button1.Enabled = false; // turn off button 1
            label1.BackColor = Color.Green; // make label green
        }

        private void button2_Click(object sender, EventArgs e) // button 2 function
        {
            label1.BackColor = Color.Red; // turn label red
            hippo.Close(); // close the port
            button1.Enabled = true; // re-enable the button
        }

        private void button3_Click(object sender, EventArgs e) // button 3 function
        {
            hippo.Write("3"); // write 3 to serial monitor
            button3.BackColor = Color.Green; // turn button green
            button4.BackColor = Color.White; // turn button white
            button5.BackColor = Color.White; // turn button white
            button7.BackColor = Color.White; // turn button white
        }

        private void button4_Click(object sender, EventArgs e) // button 4 function
        {
            hippo.Write("4"); // write 4 to serial monitor
            button4.BackColor = Color.Green;// turn button green
            button3.BackColor = Color.White;// turn button white
            button5.BackColor = Color.White;// turn button white
            button7.BackColor = Color.White;// turn button white
        }

        private void button5_Click(object sender, EventArgs e) // button 5 function
        {
            button4.BackColor = Color.White;// turn button white
            button3.BackColor = Color.White;// turn button white
            button5.BackColor = Color.Red;// turn button red
            button7.BackColor = Color.White;// turn button white
            hippo.Write("5"); // write 5 to serial monitor
        }

        private void button6_Click(object sender, EventArgs e) // button 6 function
        {
            sixclick++; // add one every click
            if (sixclick % 2 == 1) // if the raminder is 1
            { hippo.Write("1"); } // write 1 to serial moniotor
            else if (sixclick % 2 == 0) // if remainder is 0
            { hippo.Write("2"); } // write 2 to serial monitor
        }

        private void button7_Click(object sender, EventArgs e)
        {
            hippo.Write("6"); // write 6 to serial monitor
            button7.BackColor = Color.Green;// turn button green
            button3.BackColor= Color.White;// turn button white
            button5.BackColor = Color.White;// turn button white
            button4.BackColor = Color.White;// turn button white
        }
    }
}
