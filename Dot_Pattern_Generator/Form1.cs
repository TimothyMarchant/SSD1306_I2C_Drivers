//Made by Timothy Marchant
//This project exists for the purpose of creating 5x8 dot patterns for writting text to the SSD1306 OLED screen.
//
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
namespace DotPatternGenerator
{

    public partial class Form1 : Form
    {
        //the data bytes that will be sent for the SSD1306 OLED
        //Copy these values for making the character display on the screen
        private int[] Lines;
        //These labels change based on what the buttons current value is.  It gives essentially what the proposed character will look like
        //with the given binary numbers.
        private Label[] pixels;
        //All the buttons are put into an array so that the buttons can all call the same click event method.
        private Button[] Buttons;
        public Form1()
        {
            InitializeComponent();
            //Holds the labels that will be modified
            pixels= new[] {label20,label26,label32,label38,label44,label50,label56,label62,
                label19,label25,label31,label37,label43,label49,label55,label61,
                label18,label24,label30,label36,label42,label48,label54,label60,
                label17,label23,label29,label35,label41,label47,label53,label59,
                label16,label22,label28,label34,label40,label46,label52,label58 };
            //The buttons that change the above labels.
            //The ith position in the buttons array corresponds to the ith position in the pixels array.
            Buttons= new[] {button1,button2,button3,button4,button5,button6,button7,button8,
            button9,button10,button11,button12,button13,button14,button15,button16,
            button17,button18,button19,button20,button21,button22,button23,button24,
            button25,button26,button27,button28,button29,button30,button31,button32,
            button33,button34,button35,button36,button37,button38,button39,button40};
            
            //declare the lines array.  There are only 5 such items.
            Lines = new int[5];
            //reset all text
            Reset();

        }
        //update the hexdecimal label
        void changehex()
        {
            HexString.Text = "";
            for (int i = 0; i < Lines.Length; i++)
            {
                //print each line in hex.  Also put "0x" before it, so that when it's copied no work needs to be done in MPLAB.
                HexString.Text += "0x"+Lines[i].ToString("X");
                if (i + 1 != Lines.Length)
                {
                    HexString.Text += ",";
                }
            }
        }
        //general method for changing label/button text and the line value.
        private void changebyte(Label labeltochange,int index,ref int Line,Button button)
        {
            int And=Line&(0b_0000_0001 << index);
            //if this index is already 1 turn it into a zero.
            if (And>0)
            {
                button.Text = "0";
                //bitwrite 0 to the corresponding number.
                int temp = 0x01;
                temp = 0x01 << index;
                temp = ~temp;
                Line = Line & temp;
            }
            else
            {
                //bitwrite 1 to the number.
                button.Text = "1";
                Line = Line | 0x01<<(index);
            }
            //If the button text is 1 update the label to display * otherwise make it blank.
            if (button.Text == "1")
            {
                labeltochange.Text = "*";
            }
            else
            {
                labeltochange.Text = "";
            }
        }
        /*This method is for all the buttons (excluding reset).
        //Instead of making seperate methods for each button there is one main method and uses a for loop to search through the
        //Buttons array and do something based on which button it is.  This is why we made the two arrays like we did.
        //It made it more convient to write just one method instead of 40+ button methods.*/
        private void GeneralButtonClick(object sender, EventArgs e)
        {
            for (int i = 0; i < Buttons.Length; i++)
            {
                //check for which button was clicked.  
                if (sender == Buttons[i])
                {
                    //the bit that will be modified in the Lines[].
                    int index = i % 8;
                    changebyte(pixels[i], index, ref Lines[i / 8], Buttons[i]);
                }
            }
            changehex();
        }
        //reset everything to normal (also called on startup).
        private void Reset()
        {
            for (int i = 0; i < Buttons.Length; i++)
            {
                Buttons[i].Text = "0";
                pixels[i].Text = "";
            }
            for (int i = 0; i < Lines.Length; i++)
            {
                Lines[i] = 0;
            }
            changehex();
        }
        //reset everything
        private void Reset_Click(object sender, EventArgs e)
        {
            Reset();
        }
    }
}
